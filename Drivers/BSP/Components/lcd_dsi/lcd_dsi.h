#pragma once
#include "bsp_defs.h"
#include <stdbool.h>

#define LCD_DSI_FRAMEBUFFER0_SIZE 184320
#define LCD_DSI_FRAMEBUFFER1_SIZE 184320
extern uint32_t lcd_dsi_framebuffer0[LCD_DSI_FRAMEBUFFER0_SIZE];
extern uint32_t lcd_dsi_framebuffer1[LCD_DSI_FRAMEBUFFER1_SIZE];

typedef void (*on_vsync_t)();
typedef void (*wait_until_vsync_t)();
typedef void (*on_nonblocking_draw_finish_t)();
typedef void (*wait_until_nonblocking_draw_finish_t)();

bsp_result_t lcd_dsi_init();

/* Controls */
void lcd_dsi_set_vsync_ctrl(on_vsync_t on_vsync, wait_until_vsync_t wait_until_vsync);
void lcd_dsi_set_draw_ctrl(on_nonblocking_draw_finish_t on_nonblocking_draw_finish, wait_until_nonblocking_draw_finish_t wait_until_nonblocking_draw_finish);
void lcd_dsi_wait_until_vsync();

/* Tools */
void lcd_dsi_clearscreen(uint32_t color);
void lcd_dsi_draw_fillrect(uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void lcd_dsi_draw_bitmap_blocking(uint32_t *pSrc, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void lcd_dsi_draw_hline(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color);
void lcd_dsi_draw_vline(uint32_t y1, uint32_t y2, uint32_t x, uint32_t color);


