# ZMK config for beekeeb Toucan2 Keyboard

[The beekeeb Toucan2 Keyboard](https://beekeeb.com/introducing-toucan2/) is a wireless split 42-key column‑stagger keyboard that a display and a trackpad, with an aggressive stagger on the pinky columns.

# Customizations

- **Keymap**: [config/toucan.keymap](config/toucan.keymap)
- **General configs**: [boards/shields/toucan/toucan_left.conf](boards/shields/toucan/toucan_left.conf) and [boards/shields/toucan/toucan_right.conf](boards/shields/toucan/toucan_right.conf)
- **Swipe shortcuts**: the `swipe_button_mapper` node in [boards/shields/toucan/toucan.dtsi](boards/shields/toucan/toucan.dtsi)
- **Invert scroll / trackpad settings**: the `tps43_trackpad` node in [boards/shields/toucan/toucan_right.overlay](boards/shields/toucan/toucan_right.overlay)

## Hillside layout on the Toucan2

The inner five columns on each hand use the personal Hillside keymap. The extra pinky columns keep the Toucan defaults: Tab, Ctrl, Shift on the left and Backspace, quote, Esc on the right.

The thumbs below are in physical order, left to right:

| Mode | Left outer | Left middle | Left inner | Right inner | Right middle | Right outer |
| --- | --- | --- | --- | --- | --- | --- |
| Typing | Hold: WM | Sticky SYM | Space / hold: NAV | Backspace / hold: Shift | Enter | Right Alt |
| Mouse | Middle click | Left click | Right click | Left click | Right click | Middle click |

One Space/NAV and one Backspace/Shift replace the two identical Hillside keys of each kind. The upper A and Esc thumbs are gone; A stays on the home row and Esc is on the outer column and the R + S combo.

- **NAV:** Hold Space for the number row, arrows, wheel, brightness, volume and connection controls. As on the Hillside, NAV + either outer thumb enters that half’s bootloader.
- **SYM:** Tap the left middle thumb for one symbol, or hold it for the layer. **ADJ:** Hold NAV and SYM together for the Toucan function and media keys. On ADJ, Z unlocks Studio and the five right home-row keys (M through O) select Bluetooth profiles 0–4.
- **WM:** Hold the left outer thumb for the Hillside Alt shortcuts. On WM the right inner thumb is Shift; the left middle thumb enters the bootloader.
- **NUM:** The key immediately left of the top-right Backspace taps keypad 0. Hold it and the other nine Hillside top-row keys send keypad 1–9.
- **MOU:** In pointing mode, touching the trackpad activates the mouse row above; lifting your finger returns to typing. J and L send Alt+Left and Alt+Right. NAV and SYM keep the Toucan’s trackpad scrolling override; gestures, zoom and sensitivity are unchanged.

| Base-layer combo | Action |
| --- | --- |
| R + S | Esc (also works at the same positions on SYM) |
| W + F | Tab |
| U + Y | Alt+Backspace (delete word) |
| SYM thumb + Enter thumb | Ctrl |
| S + T | Left click (after 50 ms idle) |
| F + P | Tap: right click; hold: mouse layer |

Edit [config/toucan.keymap](config/toucan.keymap) for this layout; the shield’s fallback keymap is unchanged. If you previously saved a layout in ZMK Studio, **Restore Stock Settings** in Studio loads the newly flashed keymap in place of those edits.

# License

The code in this repo is available under the MIT license.

The included shield nice_view_gem is modified from https://github.com/M165437/nice-view-gem licensed under the MIT License.

The linked trackpad module is based on https://github.com/geeksville/zmk_driver_azoteq

ZMK code snippets are taken from the ZMK documentation under the MIT license.

The embedded font QuinqueFive is designed by GGBotNet, licensed under under the SIL Open Font License, Version 1.1.
