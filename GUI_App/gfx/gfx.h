#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void (*gfx_clearscreen_t)(uint32_t color);
typedef void (*gfx_draw_fillrect_t)(uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
typedef void (*gfx_draw_hline_t)(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color);
typedef void (*gfx_draw_vline_t)(uint32_t y1, uint32_t y2, uint32_t x, uint32_t color);
typedef void (*gfx_draw_bitmap_t)(uint32_t *pSrc, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

typedef struct gfx_ctrl_t {
	gfx_clearscreen_t clearscreen;
	gfx_draw_fillrect_t gfx_draw_fillrect;
	gfx_draw_hline_t gfx_draw_hline;
	gfx_draw_vline_t gfx_draw_vline;
	gfx_draw_bitmap_t gfx_draw_bitmap;
} gfx_ctrl_t;

#ifdef __cplusplus
}
#endif
