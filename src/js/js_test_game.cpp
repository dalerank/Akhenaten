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

#include "building/building.h"
#include "building/building_static_params.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "graphics/color.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "game/game.h"
#include "io/gamestate/boilerplate.h"
#include "game/game_events.h"
#include "scenario/scenario.h"
#include "window/window_info.h"
#include "empire/empire.h"

#include <SDL.h>
#include <algorithm>
#include <cstdio>
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

bool test_log_contains(pcstr marker) {
    if (!marker || !*marker) {
        return false;
    }

    logs::flush();

    const size_t marker_len = std::strlen(marker);
    return file_contains_marker(logs::output_path(), marker, marker_len);
}

static bool __test_find_inlog(pcstr marker) {
    return test_log_contains(marker);
}
ANK_FUNCTION_1(__test_find_inlog);

static void test_pump(int n) {
    for (int i = 0; i < n && !g_app.quit; ++i) {
        g_app.pump_one_frame();
    }
}

void __log_marker(pcstr message) {
    if (g_args.is_integral_tests()) {
        logs::info("[test-marker] %s", message);
    }

    logs::info("%s", message);
}
ANK_FUNCTION_1(__log_marker);

void __test_pump_frames(int n) {
    n = std::clamp(n, 0, 240); // safety bound: ~4s at 60fps
    test_pump(n);
}
ANK_FUNCTION_1(__test_pump_frames);

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

void __test_mouse_click(int x, int y) {
    do_synthetic_click(SDL_BUTTON_LEFT, x, y);
}
ANK_FUNCTION_2(__test_mouse_click);

void __test_mouse_right_click(int x, int y) {
    do_synthetic_click(SDL_BUTTON_RIGHT, x, y);
}
ANK_FUNCTION_2(__test_mouse_right_click);

void __test_signal_ready() {
    g_test_signal_ready = true;
}
ANK_FUNCTION(__test_signal_ready);

void __test_run_console_command(pcstr command) {
    run_debug_command(command);
}
ANK_FUNCTION_1(__test_run_console_command);

bool __test_start_city_session(pcstr map_path) {
    if (game.session.active) {
        return true;
    }

    if (!GamestateIO::load_map(map_path, false, true)) {
        logs::error("test_start_city_session: load_map(%s) failed", map_path);
        return false;
    }

    GamestateIO::start_loaded_file();
    auto cities = g_empire.get_cities();
    cities[0].type = EMPIRE_CITY_OURS;
    cities[0].in_use = true;

    return game.session.active;
}
ANK_FUNCTION_1(__test_start_city_session);

void __test_end_city_session() {
    game.session.active = false;
}
ANK_FUNCTION(__test_end_city_session);

void __test_set_treasury(int amount) {
    g_city.finance.treasury = amount;
}
ANK_FUNCTION_1(__test_set_treasury);

void __test_process_events() {
    events::process();
}
ANK_FUNCTION(__test_process_events);

int __building_static_building_size(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    return std::max(1, (int)building_static_params::get((e_building_type)type).building_size);
}
ANK_FUNCTION_1(__building_static_building_size);

static int __test_building_create(int type, int x, int y) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }

    tile2i place = (x < 0 || y < 0) ? tile2i::invalid : tile2i(x, y);
    if (building *existing = building_first((e_building_type)type)) {
        return existing->id;
    }

    if (!place.valid()) {
        place.set(g_scenario.map.width / 2, g_scenario.map.height / 2);
    }

    building *b = building_create((e_building_type)type, place, 0);
    if (!b || b->id <= 0) {
        return 0;
    }

    add_building(b, 0, 0);
    b->state = BUILDING_STATE_VALID;
    return b->id;
}
ANK_FUNCTION_3(__test_building_create);

color __test_color_roundtrip(color c) {
    return c;
}
ANK_FUNCTION_1(__test_color_roundtrip);

static int __test_figure_create(int type, int x, int y) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return 0;
    }

    tile2i place = (x < 0 || y < 0) ? tile2i::invalid : tile2i(x, y);
    if (!place.valid()) {
        place.set(g_scenario.map.width / 2, g_scenario.map.height / 2);
    }

    figure *f = figure_create((e_figure_type)type, place, DIR_0_TOP_RIGHT);
    if (!f || f->id <= 0 || !f->is_alive()) {
        return 0;
    }

    return f->id;
}
ANK_FUNCTION_3(__test_figure_create);

static void __test_figure_set_action(int fid, int action) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->advance_action((short)action);
}
ANK_FUNCTION_2(__test_figure_set_action);

static void __test_figure_update_animation(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    figure_impl *impl = f->dcast();
    if (impl) {
        impl->update_animation();
    }
}
ANK_FUNCTION_1(__test_figure_update_animation);

bool __test_enemy_figure_registered(int type) {
    tile2i tile(g_scenario.map.width / 2, g_scenario.map.height / 2);
    figure *f = figure_create((e_figure_type)type, tile, 0);
    if (!f) {
        return false;
    }

    figure_impl *impl = f->dcast();
    bool is_enemy = impl && impl->dcast_enemy();
    f->poof();
    return is_enemy;
}
ANK_FUNCTION_1(__test_enemy_figure_registered);

void __test_show_tile_info(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }

    events::emit(event_show_tile_info{ b->tile, true, "test" });
}
ANK_FUNCTION_1(__test_show_tile_info);

ANK_DECLARE_JSFUNCTION_ITERATOR(register_test_js_functions);
inline void register_test_js_functions(js_State *J) {
}
