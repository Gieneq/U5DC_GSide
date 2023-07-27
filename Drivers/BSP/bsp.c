#include "lcd_dsi.h"
#include "bsp.h"
#include "status_led.h"
#include "i2c_bus.h"
#include "microtimer.h"
#include "my_stts22h.h"

bsp_result_t bsp_init() {
	bsp_result_t ret = BSP_OK;

	ret = microtimer_init();
	if(ret != BSP_OK) {
		return ret;
	}

	ret = status_led_init();
	if(ret != BSP_OK) {
		return ret;
	}

	ret = i2c_bus_init();
	if(ret != BSP_OK) {
		return ret;
	}

	ret = my_stts22h_init();
	if(ret != BSP_OK) {
		return ret;
	}

	ret = lcd_dsi_init();
	if(ret != BSP_OK) {
		return ret;
	}

	return BSP_OK;
}

void bsp_update() {
	my_stts2h_update();
}





