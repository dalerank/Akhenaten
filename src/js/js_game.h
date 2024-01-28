#pragma once

#include "mujs/mujs.h"
#include "core/bstring.h"
#include "js/js_defines.h"
#include "core/vec2i.h"

#include <vector>

enum e_image_id : uint16_t;

struct archive {
    js_State *vm;
    inline archive(js_State *_vm) : vm(_vm) {}

    inline pcstr r_string(pcstr name) {
        js_getproperty(vm, -1, name);
        const char *result = js_isundefined(vm, -1) ? "" : js_tostring(vm, -1);
        js_pop(vm, 1);
        return result;
    }

    template<typename T = int>
    inline std::vector<T> r_array_num(pcstr name) {
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

    inline int r_int(pcstr name) {
        js_getproperty(vm, -1, name);
        int result = js_isundefined(vm, -1) ? 0 : js_tointeger(vm, -1);
        js_pop(vm, 1);
        return result;
    }

    inline e_image_id r_image(pcstr name) { return (e_image_id)r_int(name); }

    inline bool r_bool(pcstr name) {
        js_getproperty(vm, -1, name);
        bool result = js_isundefined(vm, -1) ? 0 : js_toboolean(vm, -1);
        js_pop(vm, 1);
        return result;
    }

    inline vec2i r_size2i(pcstr name, pcstr w = "w", pcstr h = "h") {
        return r_vec2i(name, w, h);
    }

    inline vec2i r_vec2i(pcstr name, pcstr x = "x", pcstr y = "y") {
        vec2i result(0, 0);
        r_section(name, [&] (archive arch) {
            result.x = arch.r_int(x);
            result.y = arch.r_int(y);
        });
        return result;
    }

    template<typename T>
    inline void r_section(pcstr name, T read_func) {
        js_getproperty(vm, -1, name);
        if (js_isobject(vm, -1)) {
            read_func(vm);
        }
        js_pop(vm, 1);
    }

    template<typename T>
    inline void r_array(pcstr name, T read_func) {
        js_getproperty(vm, -1, name);
        r_array_impl(read_func);
        js_pop(vm, 1);
    }

protected:
    template<typename T>
    inline bool r_array_impl(T read_func) {
        if (!js_isarray(vm, -1)) {
            return false;
        }

        int length = js_getlength(vm, -1);
        for (int i = 0; i < length; ++i) {
            js_getindex(vm, -1, i);

            if (js_isobject(vm, -1)) {
                read_func(vm);
            }

            js_pop(vm, 1);
        }
        return true;
    }
};

struct g_archive : public archive {
    template<typename T>
    inline void r_array(pcstr name, T read_func) {
        js_getglobal(vm, name);
        if (r_array_impl(read_func)) {
            js_pop(vm, 1);
        }
    }

    template<typename T>
    inline void r_section(pcstr name, T read_func) {
        js_getglobal(vm, name);
        if (js_isobject(vm, -1)) {
            read_func(vm);
            js_pop(vm, 1);
        }
    }
};
extern g_archive g_config_arch;

void js_register_game_functions(js_State *J);

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
