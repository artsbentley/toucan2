#include <zephyr/devicetree.h>
#include <zephyr/input/input.h>
#include <zmk/events/activity_state_changed.h>
#include <zmk/keymap.h>

// Use the same stable layer ID as the trackpad's &mo binding.
#define TOUCH_LAYER DT_PHA_BY_IDX(DT_NODELABEL(is_touching_processor), bindings, 0, param1)

static void toucan_trackpad_release(struct input_event *event) {
    // The NAV/SYM scroller bypasses the normal touch processor. Observe releases
    // on the split device regardless of which layer-specific chain ran.
    if (event->type == INPUT_EV_KEY && event->code == INPUT_BTN_TOUCH && event->value == 0) {
        zmk_keymap_layer_deactivate(TOUCH_LAYER);
    }
}
INPUT_CALLBACK_DEFINE(DEVICE_DT_GET(DT_NODELABEL(trackpad_split)), toucan_trackpad_release);

static int toucan_activity_changed(const zmk_event_t *eh) {
    const struct zmk_activity_state_changed *ev = as_zmk_activity_state_changed(eh);
    if (ev && (ev->state == ZMK_ACTIVITY_IDLE || ev->state == ZMK_ACTIVITY_SLEEP)) {
        // The peripheral may have stopped reporting before its final touch-up.
        zmk_keymap_layer_deactivate(TOUCH_LAYER);
    }
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(toucan_mouse_guard, toucan_activity_changed);
ZMK_SUBSCRIPTION(toucan_mouse_guard, zmk_activity_state_changed);
