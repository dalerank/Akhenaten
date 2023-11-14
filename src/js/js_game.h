#pragma once

#include "mujs/mujs.h"
#include "core/bstring.h"
#include "js/js_defines.h"

#include <vector>

struct archive {
    js_State *vm;
    inline archive(js_State *_vm) : vm(_vm) {}

    template<typename T>
    inline void load_global_array(pcstr name, T read_func) {
        js_getglobal(vm, name);
        if (js_isarray(vm, -1)) {
            int length = js_getlength(vm, -1);

            for (int i = 0; i < length; ++i) {
                js_getindex(vm, -1, i);

                if (js_isobject(vm, -1)) {
                    read_func(vm);
                }

                js_pop(vm, 1);
            }
            js_pop(vm, 1);
        }
    }

    inline pcstr read_string(pcstr name) {
        js_getproperty(vm, -1, name);
        const char *result = js_tostring(vm, -1);
        js_pop(vm, 1);
        return result;
    }

    template<typename T = int>
    inline std::vector<T> read_integer_array(pcstr name) {
        js_getproperty(vm, -1, name);
        std::vector<T> result;
        if (js_isarray(vm, -1)) {
            int length = js_getlength(vm, -1);

            for (int i = 0; i < length; ++i) {
                js_getindex(vm, -1, i);
                int v = js_tointeger(vm, -1);
                result.push_back((T)v);
                js_pop(vm, 1);
            }
            js_pop(vm, 1);
        }
        return result;
    }

    inline int read_integer(pcstr name) {
        js_getproperty(vm, -1, name);
        int result = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        return result;
    }
};

void js_register_game_functions(js_State *J);
void js_config_load_building_sounds(archive arch);
void js_config_load_mission_sounds(archive arch);
void js_config_load_walker_sounds(archive arch);
void js_config_load_city_sounds(archive arch);
void js_config_load_building_info(archive arch);
void js_config_load_city_overlays(archive arch);
void js_config_load_images_info(archive arch);

namespace config {

void refresh(archive);

typedef void (*config_iterator_function_cb)(archive);

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

#define ANK_REGISTER_CONFIG_ITERATOR(func) void func(archive); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::FuncLinkedList ANK_CONFIG_CC1(config_handler, __LINE__)(func)
