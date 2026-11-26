#pragma once

#include <stdbool.h>
#include <stdint.h>

/* Per device, used only from its serialized touch handler. */
struct tps43_timing {
    bool active;
    uint32_t start_ms;
    uint32_t span_ms;
    uint32_t samples;
    uint32_t moving;
    uint32_t missed;
    uint64_t cycle_sum_ms;
    uint8_t max_cycle_ms;
};

void tps43_timing_observe(struct tps43_timing *s, uint32_t now_ms, bool active_one_finger,
                          bool moved, uint8_t previous_cycle_ms, bool missed);
