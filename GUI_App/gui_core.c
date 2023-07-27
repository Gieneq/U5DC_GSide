#include "lcd_dsi.h"
#include "gui_core.h"
#include "gfx.h"
#include <stdbool.h>
#include "microtimer.h"
#include "main.h"

static microtimer_simple_t gui_microtimer_performance;
static TX_THREAD gui_thread;

static void gui_thread_entry();

extern void gui_init(gfx_ctrl_t* gfx);
extern void gui_tick(gfx_ctrl_t* gfx);

TX_SEMAPHORE vsync_semaphore;
static gfx_ctrl_t gfx;

void on_vsync() {
	tx_semaphore_put(&vsync_semaphore);
}

void wait_until_vsync() {
	if(tx_semaphore_get(&vsync_semaphore, TX_WAIT_FOREVER) != TX_SUCCESS) {
		Error_Handler();
	}
}

UINT gui_core_thread_create(TX_BYTE_POOL *byte_pool) {
	CHAR *pointer;
	UINT ret = TX_SUCCESS;

	/* Create semaphore to vsync with interrupt from display driver */
	ret = tx_semaphore_create(&vsync_semaphore, "vsync_sem", 1);
	if(ret != TX_SUCCESS) {
		return TX_SEMAPHORE_ERROR;
	}


	/* Connect drawing API with low level driver */
	lcd_dsi_set_vsync_ctrl(on_vsync, wait_until_vsync);
	gfx.clearscreen        = lcd_dsi_clearscreen;
	gfx.gfx_draw_bitmap    = lcd_dsi_draw_bitmap_blocking;
	gfx.gfx_draw_fillrect  = lcd_dsi_draw_fillrect;
	gfx.gfx_draw_hline     = lcd_dsi_draw_hline;
	gfx.gfx_draw_vline     = lcd_dsi_draw_vline;

	/* Allocate the stack for the thread  */
	ret = tx_byte_allocate(byte_pool, (VOID**) &pointer, GUI_THREAD_STACK_SIZE, TX_NO_WAIT);
	if (ret != TX_SUCCESS) {
		return TX_POOL_ERROR;
	}

	/* Create tx app thread.  */
	ret = tx_thread_create(&gui_thread,
			GUI_THREAD_NAME,
			gui_thread_entry,
			0,
			pointer,
			GUI_THREAD_STACK_SIZE,
			GUI_THREAD_PRIORITY,
			GUI_THREAD_PREEMPTION_THRESHOLD,
			TX_NO_TIME_SLICE,
			TX_AUTO_START);

	if (ret != TX_SUCCESS) {
		return TX_THREAD_ERROR;
	}

	return ret;
}


static void gui_thread_entry() {
	gui_init(&gfx);
	microtimer_simple_init(&gui_microtimer_performance);
	while(1) {
		lcd_dsi_wait_until_vsync();
		microtimer_simple_start(&gui_microtimer_performance);
		gui_tick(&gfx);
		microtimer_simple_stop(&gui_microtimer_performance);
	}
}

