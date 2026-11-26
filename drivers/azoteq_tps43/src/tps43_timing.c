#include "tps43_timing.h"
#include <zephyr/logging/log.h>

/* Separate from the input logger: leave its per-event messages off during capture. */
LOG_MODULE_REGISTER(tps43_timing, LOG_LEVEL_INF);

void tps43_timing_observe(struct tps43_timing *s, uint32_t now_ms, bool active_one_finger,
                          bool moved, uint8_t previous_cycle_ms, bool missed) {
    if (!active_one_finger) {
        if (s->active && s->span_ms >= 1000 && s->moving > 0) {
            uint32_t moving_hz = (uint64_t)s->moving * 1000 / s->span_ms;
            uint32_t mean_us = s->cycle_sum_ms * 1000 / s->samples;
            LOG_INF("TPS43_TIMING span_ms=%u samples=%u moving=%u moving_hz=%u "
                    "cycle_mean_us=%u cycle_max_ms=%u rr_missed=%u",
                    s->span_ms, s->samples, s->moving, moving_hz,
                    mean_us, (unsigned int)s->max_cycle_ms, s->missed);
        }
        s->active = false;
        return;
    }

    if (!s->active) {
        /* First frame starts the clock; its previous cycle predates this stretch. */
        *s = (struct tps43_timing){.active = true, .start_ms = now_ms};
        return;
    }

    s->span_ms = now_ms - s->start_ms;
    s->samples++;
    s->moving += moved;
    s->missed += missed;
    s->cycle_sum_ms += previous_cycle_ms;
    if (previous_cycle_ms > s->max_cycle_ms) {
        s->max_cycle_ms = previous_cycle_ms;
    }
}
