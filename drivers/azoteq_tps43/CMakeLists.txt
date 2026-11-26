# Vendored Azoteq TPS43 (IQS5xx) trackpad driver, see README.md in this directory.
# Both files go into the ZMK `app` target: tps43_idle_sleeper.c needs ZMK's app-private headers,
# and keeping tps43.c next to it avoids depending on an in-tree Zephyr library name
# (upstream used zephyr_library_amend(), which only works at the module's drivers/input path).
target_sources_ifdef(CONFIG_INPUT_TPS43 app PRIVATE src/tps43.c src/tps43_idle_sleeper.c)
