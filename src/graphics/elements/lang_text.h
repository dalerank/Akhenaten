#pragma once

#include "graphics/color.h"
#include "core/vec2i.h"
#include "graphics/font.h"
#include "core/xstring.h"
#include "ui.h"

struct game_language {
    xstring key;
    xstring lang;
    xstring caption;
    xstring base_table;
    xstring table;
    xstring message_table;
    xstring game_messages;
    xstring symbols;
    xstring font;
    bool is_bitmap_font = false;
    font_configs_t font_configs;

    void decode_symbols(font_utf8_symbols_t& out) const;
};
ANK_CONFIG_STRUCT(game_language, lang, caption, key, base_table, table, message_table, game_messages, symbols, font,
  is_bitmap_font, font_configs)

using game_languages_vec = svector<game_language, 16>;

const game_languages_vec & get_available_languages();

pcstr lang_text_from_key(pcstr key);
xstring lang_xtext_from_key(const xstring& key);
textid loc_text_from_key(pcstr key);
xstring lang_text_from_message(int id);
pcstr lang_text_month(int month);

int lang_text_get_width(int group, int number, e_font font);
int lang_text_get_width(const char* str, e_font font);

int lang_text_draw(int group, int number, int x_offset, int y_offset, e_font font, int box_width = 0);
inline int lang_text_draw(int group, int number, vec2i offset, e_font font, int box_width = 0) { return lang_text_draw(group, number, offset.x, offset.y, font, box_width); }

bool lang_reload_localized_files();
bool lang_reload_localized_tables();

#if defined(GAME_PLATFORM_ANDROID)
bool lang_android_load_localization_base_en_direct(pcstr path);
#endif

game_language lang_get_current_language();
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