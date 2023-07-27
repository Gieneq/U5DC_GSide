#include "game_core.h"
#include "bsp.h"

static TX_THREAD game_thread;

static void game_thread_entry();

extern void game_init();
extern void game_tick();

UINT game_core_thread_create(TX_BYTE_POOL *byte_pool) {
	CHAR *pointer;
	UINT ret = TX_SUCCESS;

	/* Allocate the stack for the thread  */
	ret = tx_byte_allocate(byte_pool, (VOID**) &pointer, GAME_THREAD_STACK_SIZE, TX_NO_WAIT);
	if (ret != TX_SUCCESS) {
		return TX_POOL_ERROR;
	}

	/* Create tx app thread.  */
	ret = tx_thread_create(&game_thread,
			GAME_THREAD_NAME,
			game_thread_entry,
			0,
			pointer,
			GAME_THREAD_STACK_SIZE,
			GAME_THREAD_PRIORITY,
			GAME_THREAD_PREEMPTION_THRESHOLD,
			TX_NO_TIME_SLICE,
			TX_AUTO_START);

	if (ret != TX_SUCCESS) {
		return TX_THREAD_ERROR;
	}

	return ret;
}


static void game_thread_entry() {
	game_init();
	while(1) {
		bsp_update();
		game_tick();
		tx_thread_sleep(1);
	}
}
