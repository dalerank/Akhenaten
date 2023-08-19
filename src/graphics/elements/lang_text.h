#ifndef GRAPHICS_LANG_TEXT_H
#define GRAPHICS_LANG_TEXT_H

#include "graphics/color.h"
#include "graphics/font.h"

int lang_text_get_width(int group, int number, font_t font);
int lang_text_get_width(const char* str, font_t font);

int lang_text_draw(int group, int number, int x_offset, int y_offset, font_t font);
int lang_text_draw(const char* str, int x_offset, int y_offset, font_t font);
int lang_text_draw_colored(int group, int number, int x_offset, int y_offset, font_t font, color color);

int lang_text_draw_left(int group, int number, int x_offset, int y_offset, font_t font);
int lang_text_draw_left_colored(int group, int number, int x_offset, int y_offset, font_t font, color color);

void lang_text_draw_centered(int group, int number, int x_offset, int y_offset, int box_width, font_t font);
void lang_text_draw_centered(const char* text, int x_offset, int y_offset, int box_width, font_t font);

void lang_text_draw_centered_colored(int group,
                                     int number,
                                     int x_offset,
                                     int y_offset,
                                     int box_width,
                                     font_t font,
                                     color color);

int lang_text_draw_amount(int group,
                          int number,
                          int amount,
                          int x_offset,
                          int y_offset,
                          font_t font,
                          const char* postfix = " ");

int lang_text_draw_year(int year, int x_offset, int y_offset, font_t font);
void lang_text_draw_month_year_max_width(int month,
                                         int year,
                                         int x_offset,
                                         int y_offset,
                                         int box_width,
                                         font_t font,
                                         color color);

int lang_text_draw_multiline(int group, int number, int x_offset, int y_offset, int box_width, font_t font);

#endif // GRAPHICS_LANG_TEXT_H
