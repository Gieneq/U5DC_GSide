#include "microtimer.h"
#include "tim.h"

extern TIM_HandleTypeDef htim3;
#define TIM_MICROTIMER htim3

static volatile uint32_t microtimer_last_time;

static struct {
	volatile uint32_t idle_start_time_us;
	volatile uint32_t updating_start_time_us;
	volatile uint32_t updating_end_time_us;
	volatile uint32_t drawing_start_time_us;
	volatile uint32_t end_loop_time_us;

	volatile uint32_t idle_duration_us;
	volatile uint32_t update_duration_us;
	volatile uint32_t clearing_duration_us;
	volatile uint32_t draw_duration_us;
	volatile uint32_t total_duration_us;
	volatile float    usage;
} microperformance_obj;

bsp_result_t microtimer_init() {
	MX_TIM3_Init();
	HAL_TIM_Base_MspInit(&TIM_MICROTIMER);
	HAL_TIM_Base_Start(&htim3);
	microtimer_last_time = __HAL_TIM_GET_COUNTER(&TIM_MICROTIMER);

	/* Microperformance */
	microperformance_obj.idle_start_time_us = 0;
	microperformance_obj.updating_start_time_us = 0;
	microperformance_obj.updating_end_time_us = 0;
	microperformance_obj.drawing_start_time_us = 0;
	microperformance_obj.end_loop_time_us = 0;

	microperformance_obj.idle_duration_us = 0;
	microperformance_obj.update_duration_us = 0;
	microperformance_obj.clearing_duration_us = 0;
	microperformance_obj.draw_duration_us = 0;
	microperformance_obj.total_duration_us = 0;
	microperformance_obj.usage = 0.0F;

	return BSP_OK;
}

uint32_t microtimer_get_us() {
	return __HAL_TIM_GET_COUNTER(&TIM_MICROTIMER);
}



void microtimer_start() {
	microtimer_last_time = __HAL_TIM_GET_COUNTER(&TIM_MICROTIMER);
}

uint32_t microtimer_stop() {
	return (__HAL_TIM_GET_COUNTER(&TIM_MICROTIMER) - microtimer_last_time);
}


void microtimer_simple_init(microtimer_simple_t* mts) {
	mts->duty_perc = 0;
	mts->interval_us = microtimer_get_us();
	mts->_vars.start_time_us = 0;
	mts->_vars.stop_time_us = mts->interval_us;
}

void microtimer_simple_start(microtimer_simple_t* mts) {
	uint32_t current_us = microtimer_get_us();
	mts->interval_us = current_us - mts->_vars.start_time_us;
	mts->frequency_hz = 1000000.0F / mts->interval_us;
	mts->_vars.start_time_us = current_us;
}

void microtimer_simple_stop(microtimer_simple_t* mts) {
	mts->_vars.stop_time_us = microtimer_get_us();
	if(mts->interval_us <= 0) {
		mts->duty_perc = 100.0F;
	}
	else {
		mts->duty_perc = 100.0F * (mts->_vars.stop_time_us - mts->_vars.start_time_us) / mts->interval_us;
	}
}



void microperformance_start_idle() {
	microperformance_obj.idle_start_time_us = microtimer_get_us();
}

void microperformance_start_update() {
	microperformance_obj.updating_start_time_us = microtimer_get_us();
}

void microperformance_end_update() {
	microperformance_obj.updating_end_time_us = microtimer_get_us();
}

void microperformance_start_draw() {
	microperformance_obj.drawing_start_time_us = microtimer_get_us();
}

void microperformance_end_loop() {
	microperformance_obj.end_loop_time_us = microtimer_get_us();

	microperformance_obj.total_duration_us = microperformance_obj.end_loop_time_us - microperformance_obj.idle_start_time_us;
	microperformance_obj.idle_duration_us = microperformance_obj.updating_start_time_us - microperformance_obj.idle_start_time_us;
	microperformance_obj.update_duration_us = microperformance_obj.updating_end_time_us - microperformance_obj.updating_start_time_us;
	microperformance_obj.clearing_duration_us = microperformance_obj.drawing_start_time_us - microperformance_obj.updating_start_time_us;
	microperformance_obj.draw_duration_us = microperformance_obj.end_loop_time_us - microperformance_obj.drawing_start_time_us;
	microperformance_obj.usage = 100.0F - (100.0F * microperformance_obj.idle_duration_us / microperformance_obj.total_duration_us);

}

float microperformance_get_usage() {
	return microperformance_obj.usage;
}
