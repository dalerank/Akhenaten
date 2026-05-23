// Native JS bindings used only by the integraltests driver (see
// src/platform/integral_tests.cpp and tests/*.js). Split out from js_game.cpp
// to keep the test-only surface in one place and make it easy to audit /
// disable later without touching the main game bindings.

#include "js_game.h"

#include "core/app.h"
#include "core/log.h"
#include "js.h"
#include "js_defines.h"
#include "mujs/mujs.h"
#include "platform/arguments.h"
#include "platform/integral_tests.h"
#include "widget/debug_console.h"

#include <SDL.h>
#include <cstring>
#include <fstream>
#include <string>

static bool file_contains_marker(pcstr path, pcstr marker, const size_t marker_len) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return false;
    }

    std::string chunk;
    chunk.reserve(8192 + marker_len);
    std::string tail;
    char buf[8192];
    bool strip_bom = true;

    while (in) {
        in.read(buf, sizeof(buf));
        const std::streamsize got = in.gcount();
        if (got <= 0) {
            break;
        }

        chunk = tail;
        chunk.append(buf, static_cast<size_t>(got));

        if (strip_bom && chunk.size() >= 3
            && (unsigned char) chunk[0] == 0xEF
            && (unsigned char) chunk[1] == 0xBB
            && (unsigned char) chunk[2] == 0xBF) {
            chunk.erase(0, 3);
        }
        strip_bom = false;

        if (chunk.find(marker) != std::string::npos) {
            return true;
        }

        if (marker_len <= 1) {
            tail.clear();
        } else if (chunk.size() >= marker_len - 1) {
            tail = chunk.substr(chunk.size() - (marker_len - 1));
        } else {
            tail = chunk;
        }
    }

    return tail.find(marker) != std::string::npos;
}

static bool log_contains_marker(pcstr marker) {
    if (!marker || !*marker) {
        return false;
    }

    logs::flush();

    const size_t marker_len = std::strlen(marker);
    return file_contains_marker(logs::output_path(), marker, marker_len);
}

static void js_test_find_inlog_native(js_State *J) {
    if (js_isundefined(J, 1)) {
        js_pushboolean(J, 0);
        return;
    }
    pcstr marker = js_strnode_cstr(js_tostring(J, 1));
    js_pushboolean(J, log_contains_marker(marker) ? 1 : 0);
}

static void test_pump(int n) {
    for (int i = 0; i < n && !g_app.quit; ++i) {
        g_app.pump_one_frame();
    }
}

void js_log_test_marker_native(js_State *J) {
    if (js_isundefined(J, 1)) {
        logs::info("log() Try to print undefined object", 0, 0);
        J->pushundefined();
        return;
    }

    if (g_args.is_integral_tests()) {
        logs::info("[test-marker] %s", js_strnode_cstr(js_tostring(J, 1)));
        J->pushundefined();
        return;
    }

    logs::info("%s", js_strnode_cstr(js_tostring(J, 1)));
    J->pushundefined();
    return;
}

static void js_test_pump_frames_native(js_State *J) {
    int n = js_tointeger(J, 1);
    if (n < 0) { n = 0; }
    if (n > 240) { n = 240; } // safety bound: ~4s at 60fps
    test_pump(n);
    J->pushundefined();
}

static void push_mouse_motion(int x, int y) {
    SDL_Event e{};
    e.type = SDL_MOUSEMOTION;
    e.motion.which = 0; // not SDL_TOUCH_MOUSEID
    e.motion.x = x;
    e.motion.y = y;
    e.motion.xrel = 0;
    e.motion.yrel = 0;
    SDL_PushEvent(&e);
}

static void push_mouse_button(Uint32 type, Uint8 button, int x, int y) {
    SDL_Event e{};
    e.type = type;
    e.button.which = 0;
    e.button.button = button;
    e.button.state = (type == SDL_MOUSEBUTTONDOWN) ? SDL_PRESSED : SDL_RELEASED;
    e.button.clicks = 1;
    e.button.x = x;
    e.button.y = y;
    SDL_PushEvent(&e);
}

static void do_synthetic_click(Uint8 sdl_button, int x, int y) {
    push_mouse_motion(x, y);
    push_mouse_button(SDL_MOUSEBUTTONDOWN, sdl_button, x, y);
    test_pump(2);
    push_mouse_button(SDL_MOUSEBUTTONUP, sdl_button, x, y);
    test_pump(8);
}

static void js_test_mouse_click_native(js_State *J) {
    int x = js_tointeger(J, 1);
    int y = js_tointeger(J, 2);
    do_synthetic_click(SDL_BUTTON_LEFT, x, y);
    J->pushundefined();
}

static void js_test_mouse_right_click_native(js_State *J) {
    int x = js_tointeger(J, 1);
    int y = js_tointeger(J, 2);
    do_synthetic_click(SDL_BUTTON_RIGHT, x, y);
    J->pushundefined();
}

static void js_test_signal_ready_native(js_State *J) {
    g_test_signal_ready = true;
    J->pushundefined();
}

static void js_test_run_console_command_native(js_State *J) {
    if (js_isundefined(J, 1)) {
        J->pushundefined();
        return;
    }
    pcstr line = js_strnode_cstr(js_tostring(J, 1));
    run_debug_command(line);
    J->pushundefined();
}

ANK_DECLARE_JSFUNCTION_ITERATOR(register_test_js_functions);
inline void register_test_js_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_test_find_inlog_native,      "__test_find_inlog",      1);
    REGISTER_GLOBAL_FUNCTION(J, js_test_signal_ready_native,    "__test_signal_ready",    0);
    REGISTER_GLOBAL_FUNCTION(J, js_test_pump_frames_native,     "__test_pump_frames",     1);
    REGISTER_GLOBAL_FUNCTION(J, js_test_mouse_click_native,     "__test_mouse_click",     2);
    REGISTER_GLOBAL_FUNCTION(J, js_test_mouse_right_click_native,"__test_mouse_right_click", 2);
    REGISTER_GLOBAL_FUNCTION(J, js_test_run_console_command_native,"__test_run_console_command", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_log_test_marker_native,      "__log_marker",      1);
}
