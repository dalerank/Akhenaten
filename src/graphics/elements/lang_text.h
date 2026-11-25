#pragma once

#include "graphics/color.h"
#include "core/vec2i.h"
#include "graphics/font.h"
#include "core/xstring.h"
#include "game/localization.h"
#include "ui.h"

int lang_text_get_width(int group, int number, e_font font);
int lang_text_get_width(const char* str, e_font font);

int lang_text_draw(int group, int number, int x_offset, int y_offset, e_font font, int box_width = 0);
inline int lang_text_draw(int group, int number, vec2i offset, e_font font, int box_width = 0) { return lang_text_draw(group, number, offset.x, offset.y, font, box_width); }

int lang_text_draw(pcstr str, vec2i pos, e_font font, int box_width = 0);

template<typename ... Args>
inline int lang_text_draw(vec2i offset, e_font font, int box_width, pcstr fmt, const Args&... args) {
    bstring1024 s;
    s.printf(fmt, args...);
    return lang_text_draw(s.c_str(), offset, font, box_width);
}

int lang_text_draw_colored(int group, int number, int x_offset, int y_offset, e_font font, color color);
int lang_text_draw_colored(pcstr tx, int x_offset, int y_offset, e_font font, color color);

int lang_text_draw_left(int group, int number, int x_offset, int y_offset, e_font font);
int lang_text_draw_left_colored(int group, int number, int x_offset, int y_offset, e_font font, color color);

int lang_text_draw_year(int year, int x_offset, int y_offset, e_font font);
