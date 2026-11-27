# ZMK config for the 36-key beekeeb Toucan2

This firmware targets the **36-key** [Toucan2](https://beekeeb.com/introducing-toucan2/): three rows of five finger keys and three thumb keys per half. Download the `firmware` artifact from [Build ZMK firmware](https://github.com/artsbentley/toucan2/actions/workflows/build.yml) and flash `toucan2_36_left.uf2` to the left half and `toucan2_36_right.uf2` to the right.

# Customizations

- **Keymap**: [config/toucan.keymap](config/toucan.keymap)
- **General configs**: [boards/shields/toucan/toucan_left.conf](boards/shields/toucan/toucan_left.conf) and [boards/shields/toucan/toucan_right.conf](boards/shields/toucan/toucan_right.conf)
- **Swipe shortcuts**: the `swipe_button_mapper` node in [boards/shields/toucan/toucan.dtsi](boards/shields/toucan/toucan.dtsi)
- **Layer scrolling**: `nav_scroller` and `sym_scroller` in [boards/shields/toucan/toucan.dtsi](boards/shields/toucan/toucan.dtsi) set the direction when pad movement is mapped to scrolling. NAV scrolls in the opposite direction from SYM on both axes.
- **Two-finger scrolling / trackpad settings**: the `tps43_trackpad` node in [boards/shields/toucan/toucan_right.overlay](boards/shields/toucan/toucan_right.overlay)

## Hillside layout on the Toucan2

All 30 finger keys use the personal Hillside keymap. There are no extra pinky columns: the three finger rows use positions 0–29, then the thumbs use positions 30–35.

The thumbs below are in physical order, left to right:

| Left outer | Left middle | Left inner | Right inner | Right middle | Right outer |
| --- | --- | --- | --- | --- | --- |
| Hold: WM | Sticky SYM | Space / hold: NAV | Backspace / hold: Shift | Enter | Right Alt |

One Space/NAV and one Backspace/Shift replace the two identical Hillside keys of each kind. The upper A and Esc thumbs are gone; A stays on the home row and R + S gives Esc.

- **Finger modifiers:** X and `.` double as Cmd; Z and `-` double as Shift. Hold `.` and press T with the other hand for Cmd+T, with no need to pause after typing or wait out the 170 ms hold time. To type `.t` literally, release `.` before pressing T. A quick same-hand roll still types both keys; for a same-hand shortcut, hold the modifier for 170 ms first. The same rule applies to the finger mod-taps on NAV and SYM, but not to the Backspace/Shift thumb.
- **NAV:** Hold Space for the number row, arrows, wheel, brightness, volume and connection controls. As on the Hillside, NAV + either outer thumb enters that half’s bootloader.
- **SYM:** Tap the left middle thumb for one symbol, or hold it for the layer. **ADJ:** Hold NAV and SYM together for the Toucan function and media keys. On ADJ, Z unlocks Studio and the five right home-row keys (M through O) select Bluetooth profiles 0–4.
- **WM:** Hold the left outer thumb for the Hillside Alt shortcuts. On WM the right inner thumb is Shift; the left middle thumb enters the bootloader.
- **NUM:** The top-right finger key taps keypad 0. Hold it and the other nine top-row keys send keypad 1–9.
- **MOU:** In pointing mode, touching the trackpad activates MOU. Tap the **T** position to lock left click for dragging; the other keys pass through to the layer underneath. While locked, you can lift and reposition your finger. Tap **T** again to release, on or off the pad. **R + S** releases the lock and leaves MOU without sending Esc. S + T and F + P still click. R + S leaves MOU without sending Escape or resetting other layers. NAV and SYM keep the Toucan’s trackpad scrolling override. Two fingers scroll vertically or tap to right-click. Horizontal two-finger scrolling and pinch-to-zoom are disabled.

| Base-layer combo | Action |
| --- | --- |
| R + S | Esc on BASE/SYM; leave MOU and cancel any drag lock on MOU/DRAG |
| W + F | Tab |
| U + Y | Alt+Backspace (delete word) |
| SYM thumb + Enter thumb | Ctrl |
| S + T | Left mouse button (BASE and MOU) |
| F + P | Right mouse button (BASE and MOU) |

Both click combos press the button as soon as the second key completes the chord, even immediately after typing. Hold both keys to keep the button down; release either key to let go. Touch the trackpad, not F + P, to activate MOU.

Edit [config/toucan.keymap](config/toucan.keymap) for bindings. [config/toucan_36_layout.dtsi](config/toucan_36_layout.dtsi) maps the PCB to 36 positions for firmware and Studio; [config/toucan.json](config/toucan.json) mirrors that geometry for the keymap editor. The upstream shield’s 42-key fallback is unchanged and is not the layout used by this build. If you previously saved a layout in ZMK Studio, **Restore Stock Settings** in Studio loads the newly flashed keymap in place of those edits.

### If the keyboard stays on MOU

The left half owns the layer state. Lifting your finger clears MOU even if you started scrolling on NAV/SYM during the touch. If the release never arrives, regular keyboard idle (about 30 seconds without input) or deep sleep clears MOU. You can also press **R + S together on the left** to clear it immediately. Lift and touch again to start a fresh mouse session.

If the cursor **and** right-hand letters stop working until reset, clearing a layer cannot revive the right half. The [patched TPS43 driver](drivers/azoteq_tps43/README.md) keeps the trackpad's Bluetooth traffic from blocking the worker used for key scanning. Flash **both** normal UF2s from the same build: the driver fix is on the right, layer recovery is on the left. Do not flash `settings_reset` for this.

After flashing, check that the Space thumb still types Space while touching the pad. To test recovery, touch the pad, hold Space for NAV, lift your finger, then release Space: the display should return to BASE and W + F should send Tab. Also check that right-hand letters still type after leaving the board idle following trackpad use.

# License

The code in this repo is available under the MIT license.

The included shield nice_view_gem is modified from https://github.com/M165437/nice-view-gem licensed under the MIT License.

The vendored TPS43 driver is based on [beekeeb/zmk_driver_azoteq](https://github.com/beekeeb/zmk_driver_azoteq), with [Mike’s work-queue fix](https://github.com/myanhon/toucan2-config/commit/3b72dd3). Its [MIT license](drivers/azoteq_tps43/LICENSE) is included.

ZMK code snippets are taken from the ZMK documentation under the MIT license.

The embedded font QuinqueFive is designed by GGBotNet, licensed under under the SIL Open Font License, Version 1.1.
