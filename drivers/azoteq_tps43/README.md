# Vendored Azoteq TPS43 trackpad driver

Imported from [Mike’s work-queue fix, `3b72dd3`](https://github.com/myanhon/toucan2-config/commit/3b72dd3).
Only this driver subtree is used, not his keymap, power settings or later touch-up retries.

This is the TPS43 / IQS5xx trackpad driver from
[beekeeb/zmk_driver_azoteq](https://github.com/beekeeb/zmk_driver_azoteq), branch `main`
(the branch `config/west.yml` used to build; the repo's default branch is `master`), copied at
commit `c329f309b7481e5723603550b15f48e24d0c8a6a` (2026-07-11, "Add three_finger_swipe
throttle"), with local changes for the work queue, the I²C session handshake and vertical-only two-finger scrolling. It replaces the
`zmk_driver_azoteq` entry that used to be in `config/west.yml`. The files are unchanged from
upstream except where marked `LOCAL PATCH`, plus the new `CMakeLists.txt`, the two
`INPUT_TPS43_WORK_QUEUE_*` options in `Kconfig`, and this README.

## Why

With the upstream driver the right half of the Toucan2 froze after some seconds of trackpad use:
cursor stopped, right-half keys stopped typing, and only a reset brought it back. The left half
kept working, so the mouse layer (held while a finger touches the pad) stayed on, which is what
looked like a "stuck layer".

Cause, a deadlock on the right half (split peripheral):

1. The driver's work handler runs on the **system work queue** and reports events with
   `input_report_*(..., K_FOREVER)` into Zephyr's input queue (16 events).
2. The input thread forwards each event to the left half with `bt_gatt_notify()`, which waits
   forever for an ATT TX context and a connection TX context (3 of each by default).
3. Zephyr frees those contexts **only on the system work queue** (Bluetooth TX-complete work).
4. When the split link is slow for roughly 100 ms, the TX contexts run out, the input queue
   fills, and the work handler blocks the system work queue on step 1. The contexts that would
   unblock everything are then only freed if the left half happens to send data to the right
   half, which in practice it does not. Everything else on the system work queue, including the
   key matrix scan, stops too.

## Fix

`tps43_work_handler` now runs on its own work queue (`tps43_work_q`), so the system work queue is
never blocked by the trackpad and always processes Bluetooth TX completions. Under a slow link the
trackpad handler still waits, which is harmless back-pressure. The lock and work item are also
initialised before the RDY interrupt is enabled.

## Trackpad read timing

After reading a touch frame, the driver writes `EE EE 00` (register `0xEEEE`, one data byte)
with a STOP, as specified in [IQS5xx-B000 §8.7](https://www.azoteq.com/images/stories/pdf/iqs5xx-b000_trackpad_datasheet.pdf).
It does this before reporting any buffered touch, gesture or motion events, so waiting on the
input queue doesn't keep the sensor's communication window open. A failed read still gets one
best-effort close, but its data is not reported. The active interval remains 10 ms.

## Updating

To pick up upstream changes, copy the new files from the upstream `main` branch over `src/`,
`dts/` and `Kconfig`, then re-apply the `LOCAL PATCH` hunks and the two work-queue Kconfig options. Once
upstream supports these changes, delete this directory, restore the `cmake`, `kconfig` and
`dts_root` lines in `zephyr/module.yml` to only `board_root: .`, and add `zmk_driver_azoteq`
back to `config/west.yml`.
