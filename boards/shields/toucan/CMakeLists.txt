# Only the central owns the keymap and receives the split trackpad's input.
target_sources_ifdef(CONFIG_SHIELD_TOUCAN_LEFT app PRIVATE mouse_layer_guard.c)
