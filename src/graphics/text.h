#pragma once

#include "graphics/color.h"
#include "graphics/font.h"
#include "graphics/view/view.h"
#include "core/bstring.h"
#include "input/mouse.h"

#include <stdint.h>

struct painter;

void text_capture_cursor(int cursor_position, int offset_start, int offset_end);
void text_draw_cursor(int x_offset, int y_offset, int is_insert);

int get_letter_height(const uint8_t *str, e_font font);
int get_letter_width(const uint8_t *str, const font_definition *def, int *num_bytes);
int text_get_width(const uint8_t* str, e_font font);
inline int text_get_width(pcstr str, e_font font) { return text_get_width((const uint8_t*)str, font); }
uint32_t text_get_max_length_for_width(const uint8_t* str, int length, e_font font, unsigned int requested_width, int invert);
void text_ellipsize(uint8_t* str, e_font font, int requested_width);

int text_draw(painter &ctx, const uint8_t* str, int x, int y, e_font font, color color, float scale = 1.f);
int text_draw(const uint8_t* str, int x, int y, e_font font, color color);
inline int text_draw(pcstr str, int x, int y, e_font font, color color) { return text_draw((const uint8_t*)str, x, y, font, color); }
void text_draw_centered(const uint8_t* str, int x, int y, int box_width, e_font font, color color);
inline void text_draw_centered(pcstr str, int x, int y, int box_width, e_font font, color color) { text_draw_centered((const uint8_t*)str, x, y, box_width, font, color); }
int text_draw_left(pcstr str, int x, int y, e_font font, color color);

int text_draw_number(int value, char prefix, const char* postfix, int x_offset, int y_offset, e_font font);
int text_draw_number_colored(int value, char prefix, const char* postfix, int x_offset, int y_offset, e_font font, color color);
int text_draw_money(int value, int x_offset, int y_offset, e_font font);
int text_draw_percentage(int value, int x_offset, int y_offset, e_font font);

int text_draw_label_and_number(const char* label, int value, const char* postfix, int x_offset, int y_offset, e_font font, color color);
void text_draw_label_and_number_centered(const char* label, int value, const char* postfix, int x_offset, int y_offset, int box_width, e_font font, color color);

void text_draw_number_centered(int value, int x_offset, int y_offset, int box_width, e_font font);
inline void text_draw_number_centered(int value, vec2i offset, int box_width, e_font font) { text_draw_number_centered(value, offset.x, offset.y, box_width, font); }
void text_draw_number_centered_prefix(int value, char prefix, int x_offset, int y_offset, int box_width, e_font font);
void text_draw_number_centered_colored(int value, int x_offset, int y_offset, int box_width, e_font font, color color);

int text_draw_multiline(const uint8_t* str, int x_offset, int y_offset, int box_width, e_font font, uint32_t color);
int text_measure_multiline(const uint8_t* str, int box_width, e_font font);
