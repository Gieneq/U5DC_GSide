#pragma once
#include "bsp_defs.h"

#define LCD_FRAMEBUFFER0_SIZE 184320
#define LCD_FRAMEBUFFER1_SIZE 184320
extern uint32_t lcd_framebuffer0[LCD_FRAMEBUFFER0_SIZE];
extern uint32_t lcd_framebuffer1[LCD_FRAMEBUFFER1_SIZE];

bsp_result_t graphics_init();


typedef void (*on_vsync_handle_t)()

void gfx_set_on_vsync_listener(on_vsync_handle_t handle);
void gfx_wait_until_vsync();
void gfx_start_clearscreen();
void gfx_wait_until_clearscreen();
void gfx_finish();

void gfx_draw_fillrect(uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void gfx_draw_bitmap_blocking(uint32_t *pSrc, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void gfx_draw_hline(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color);
void gfx_draw_vline(uint32_t y1, uint32_t y2, uint32_t x, uint32_t color);


