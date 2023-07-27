#include "gui_core.h"
#include "gfx.h"
#include <array>

extern "C" void gui_init(gfx_ctrl_t* gfx);
extern "C" void gui_tick(gfx_ctrl_t* gfx);

void gui_init(gfx_ctrl_t* gfx) {
}

void gui_tick(gfx_ctrl_t* gfx) {
	gfx->clearscreen(0xFF0000FF);
}
