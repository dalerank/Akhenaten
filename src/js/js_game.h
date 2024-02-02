#pragma once

#include "mujs/mujs.h"

#include "core/bstring.h"
#include "js/js_defines.h"
#include "core/vec2i.h"

#include <vector>
#include <string>

#include "core/archive.h"

void js_register_game_functions(js_State *J);
void js_register_game_objects(js_State *J);

namespace config {

void refresh(archive);
archive load(pcstr filename);

typedef void (*config_iterator_function_cb)();

struct FuncLinkedList {
    FuncLinkedList(config_iterator_function_cb cb) : func(cb) {
        next = tail;
        tail = this;
    }

protected:
    FuncLinkedList *next = nullptr; // slist
    config_iterator_function_cb func;
    static FuncLinkedList *tail;
    friend void refresh(archive);
};

} // end namespace config

#define ANK_CONFIG_CC0(a, b) a##b
#define ANK_CONFIG_CC1(a, b) ANK_CONFIG_CC0(a, b)
#define ANK_CONFIG_PULL_VAR_NAME(func) ANK_CONFIG_CC1(config_pull, func)

#define ANK_REGISTER_CONFIG_ITERATOR(func) void func(); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::FuncLinkedList ANK_CONFIG_CC1(config_handler, __LINE__)(func)
