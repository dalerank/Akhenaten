#pragma once

#include "graphics/color.h"
#include "core/vec2i.h"
#include "graphics/font.h"
#include "core/string.h"
#include "ui.h"

int lang_text_get_width(int group, int number, font_t font);
int lang_text_get_width(const char* str, font_t font);

int lang_text_draw(int group, int number, int x_offset, int y_offset, font_t font);
inline int lang_text_draw(int group, int number, vec2i offset, font_t font) { return lang_text_draw(group, number, offset.x, offset.y, font); }
int lang_text_draw(pcstr str, vec2i pos, font_t font);
int lang_text_draw_colored(int group, int number, int x_offset, int y_offset, font_t font, color color);

int lang_text_draw_left(int group, int number, int x_offset, int y_offset, font_t font);
int lang_text_draw_left_colored(int group, int number, int x_offset, int y_offset, font_t font, color color);

void lang_text_draw_centered(int group, int number, int x_offset, int y_offset, int box_width, font_t font);
void lang_text_draw_centered(const char* text, int x_offset, int y_offset, int box_width, font_t font);

void lang_text_draw_centered_colored(int group, int number, int x_offset, int y_offset, int box_width, font_t font, color color);

int lang_text_draw_amount(int group, int number, int amount, int x_offset, int y_offset, font_t font, const char* postfix = " ");
inline int lang_text_draw_amount(int group, int number, int amount, vec2i offset, font_t font, const char *postfix = " ") {
    return lang_text_draw_amount(group, number, amount, offset.x, offset.y, font, postfix);
}

int lang_text_draw_year(int year, int x_offset, int y_offset, font_t font);
void lang_text_draw_month_year_max_width(int month, int year, int x_offset, int y_offset, int box_width, font_t font, color color);

int lang_text_draw_multiline(int group, int number, vec2i offset, int box_width, font_t font);

namespace ui {
    int label(int group, int number, vec2i pos, font_t font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_ flags = UiFlags_None, int box_width = 0);
    int label(pcstr, vec2i pos, font_t font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_ flags = UiFlags_None, int box_width = 0);
    int label_amount(int group, int number, int amount, vec2i pos, font_t font = FONT_NORMAL_BLACK_ON_LIGHT, pcstr postfix = "");
    int label_percent(int amount, vec2i pos, font_t font = FONT_NORMAL_BLACK_ON_LIGHT);
    void image(e_image_id img, vec2i pos);
}