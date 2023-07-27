#pragma once
#include "bsp_defs.h"
#include <stdint.h>

typedef struct microtimer_simple_t {
	struct {
		uint32_t start_time_us;
		uint32_t stop_time_us;
	} _vars;

	uint32_t interval_us;
	float frequency_hz;
	float duty_perc;
} microtimer_simple_t;


bsp_result_t microtimer_init();
uint32_t microtimer_get_us();

void microtimer_start();
uint32_t microtimer_stop();


void microtimer_simple_init(microtimer_simple_t* mts);
void microtimer_simple_start(microtimer_simple_t* mts);
void microtimer_simple_stop(microtimer_simple_t* mts);

void microperformance_start_idle();
void microperformance_start_update();
void microperformance_end_update();
void microperformance_start_draw();
void microperformance_end_loop();

float microperformance_get_usage();


static inline void microdelay(uint32_t micros) {
	uint32_t microdelay_last_time = microtimer_get_us();
	while((microtimer_get_us() - microdelay_last_time) < micros) {
		;//__NOP;
	}
}
