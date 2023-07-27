#include "gui_core.h"
#include "graphics.h"

static TX_THREAD gui_thread;

static void gui_thread_entry();

extern void gui_init();
extern void gui_tick();

TX_SEMAPHORE vsync_semaphore;

void on_vsync() {
	tx_semaphore_put(&vsync_semaphore);
}

void wait_until_vsync() {
	tx_semaphore_get(&vsync_semaphore, TX_WAIT_FOREVER);
}

UINT gui_core_thread_create(TX_BYTE_POOL *byte_pool) {
	CHAR *pointer;
	UINT ret = TX_SUCCESS;

	/* Create semaphore to vsync with interrupt from display driver */
	ret = tx_semaphore_create(&vsync_semaphore, "vsync_sem", 1);
	if(ret != TX_SUCCESS) {
		return TX_SEMAPHORE_ERROR;
	}

	gfx_set_on_vsync_listener(on_vsync);

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
	gui_init();
	while(1) {
		gfx_wait_until_vsync();
		gfx_start_clearscreen();
		gfx_wait_until_clearscreen();
		gui_tick();
		gfx_finish();
//		tx_thread_sleep(1);
	}
}

