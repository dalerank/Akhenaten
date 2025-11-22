#pragma once

#include "core/xstring.h"

struct js_State;
void js_register_game_constants(js_State *J);
void js_register_menu(js_State *J);

void js_register_token(int id, pcstr name);

template<typename T>
bool js_register_tokens(const T &tokens) {
    for (const auto &btype : tokens.values) {
        js_register_token(btype.id, btype.name);
    }

    return true;
}