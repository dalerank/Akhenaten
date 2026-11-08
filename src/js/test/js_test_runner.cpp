#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "building/monument_pyramid.h"
#include "building/monuments.h"
#include "city/object_info.h"
#include "core/app.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/xstring.h"
#include "editor/editor.h"
#include "empire/empire.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figuretype/figure_plagued_citizen.h"
#include "game/autosave_module.h"
#include "game/game.h"
#include "game/game_events.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/view/zoom.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "input/hotkey.h"
#include "io/gamestate/boilerplate.h"
#include "platform/integral_tests.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "widget/debug_console.h"
#include "window/window_info.h"

#include <SDL.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>

// SDL_main.h does `#define main SDL_main`; undo it here so building::main() etc.
// are not macro-mangled (this TU is not the program entry point).
#ifdef main
#undef main
#endif

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

        if (strip_bom && chunk.size() >= 3 && (unsigned char)chunk[0] == 0xEF && (unsigned char)chunk[1] == 0xBB
            && (unsigned char)chunk[2] == 0xBF) {
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
        game.tick_timer_ms = 0;
        g_app.pump_one_frame();
    }
}

void __test_pump_frames(int n) {
    n = std::clamp(n, 0, 240); // safety bound: ~4s at 60fps
    test_pump(n);
}
ANK_FUNCTION_1(__test_pump_frames);

// Wall-clock pause while still drawing (for visual layer-step tests).
static void __test_sleep_ms(int ms) {
    ms = std::clamp(ms, 0, 60000);
    const Uint32 deadline = SDL_GetTicks() + (Uint32)ms;
    while (!g_app.quit && !SDL_TICKS_PASSED(SDL_GetTicks(), deadline)) {
        g_app.pump_one_frame();
        SDL_Delay(16);
    }
}
ANK_FUNCTION_1(__test_sleep_ms);

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

static void do_synthetic_click(Uint8 sdl_button, int logical_x, int logical_y) {
    // No window id, so SDL does not remap these. Real events arrive already logical.
    push_mouse_motion(logical_x, logical_y);
    push_mouse_button(SDL_MOUSEBUTTONDOWN, sdl_button, logical_x, logical_y);
    test_pump(2);
    push_mouse_button(SDL_MOUSEBUTTONUP, sdl_button, logical_x, logical_y);
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

    // load_map only clears scenario events when a *.meta.js sidecar exists.
    g_scenario.events.clear_for_editor();

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

void test_reset_session_between_tests() {
    if (editor_is_active()) {
        editor_set_active(0);
    }
    game.session.active = false;
    g_scenario.events.clear_for_editor();
    events::emit(event_show_main_menu{false});
    events::process();
}

void __test_end_city_session() {
    test_reset_session_between_tests();
}
ANK_FUNCTION(__test_end_city_session);

pcstr __test_music_current_track() {
    return g_sound.music_current_track().c_str();
}
ANK_FUNCTION(__test_music_current_track);

void __test_music_next_track() {
    g_sound.music_next_track();
}
ANK_FUNCTION(__test_music_next_track);

int __test_music_load_playlist(pcstr text) {
    return g_sound.music_load_playlist_text(text ? text : "");
}
ANK_FUNCTION_1(__test_music_load_playlist);

void __test_set_campaign_scenario_id(int id) {
    g_scenario.campaign_scenario_id = id;
    g_scenario.scmode = e_scenario_normal;
}
ANK_FUNCTION_1(__test_set_campaign_scenario_id);

void __test_process_events() {
    events::process();
}
ANK_FUNCTION(__test_process_events);

void __test_process_scenario_events() {
    g_scenario.events.process_events();
}
ANK_FUNCTION(__test_process_scenario_events);

color __test_color_roundtrip(color c) {
    return c;
}
ANK_FUNCTION_1(__test_color_roundtrip);

void __test_show_tile_info(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }

    events::emit(event_show_tile_info{b->tile, true, "test"});
}
ANK_FUNCTION_1(__test_show_tile_info);

pcstr __test_info_ui_text(pcstr element_id) {
    static bstring512 buf;
    buf = "";
    if (!element_id || !*element_id) {
        return buf.c_str();
    }
    object_info& context = common_info_window::get_object_info();
    if (!context.ui || !context.ui->contains(element_id)) {
        return buf.c_str();
    }
    buf = (*context.ui)[element_id].text().c_str();
    return buf.c_str();
}
ANK_FUNCTION_1(__test_info_ui_text);

int __test_info_ui_image(pcstr element_id) {
    auto& context = common_info_window::get_object_info();
    if (!context.ui) {
        return -1;
    }
    return (*context.ui)[element_id].image().tid();
}
ANK_FUNCTION_1(__test_info_ui_image);

int __test_info_ui_enabled(pcstr element_id) {
    if (!element_id || !*element_id) {
        return -1;
    }
    object_info& context = common_info_window::get_object_info();
    if (!context.ui || !context.ui->contains(element_id)) {
        return -1;
    }
    return (*context.ui)[element_id].enabled ? 1 : 0;
}
ANK_FUNCTION_1(__test_info_ui_enabled);

static void __test_camera_center_building(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building* head = b->main();
    tile2i c = head->tile.shifted(head->size / 2, head->size / 2);
    int height_layers = 0;
    if (auto* pyr = head->dcast_pyramid()) {
        const vec2i foot = pyr->pyramid_params().init_tiles;
        c = head->tile.shifted(foot.x / 2, foot.y / 2);
        // Aim by *built* height, not max monument size — otherwise a 2-tier shot
        // is framed as a 5-tier stack and looks like a tight close-up.
        const int max_layers = std::max(1, foot.x / 4);
        const int phase = pyr->phase();
        int built = 1;
        if (phase >= 6) {
            built = 1 + (phase - 6) / 6;
        }
        height_layers = std::clamp(built, 1, max_layers);
    } else if (auto* m = head->dcast_monument()) {
        c = m->center_point();
    }
    if (!c.valid()) {
        return;
    }

    // Instant collapse — animated widget_sidebar_expanded_collapse() leaves the
    // expanded chrome on screen until the slide finishes (and screenshots skip that).
    g_camera.toggle_sidebar(1);

    // Zoom OUT = higher percentage (zoom_min=25 is close-up, zoom_max=250 is far).
    // 180 fits a 20×20 two-tier stepped pyramid in a ~1200×770 collapsed viewport.
    g_zoom.set_scale(180.f);
    g_camera.set_extra_scroll_margin(120);

    // Tall brick courses draw upward from the footprint. Aim slightly NW of the
    // geometric centre so the on-screen mass (not the SE tip) lands mid-viewport.
    // Do not use lookup_tile_to_pixel: that cache is only filled during a city draw.
    if (height_layers > 1) {
        const int aim = height_layers - 1;
        c = c.shifted(-aim, -aim);
    }
    g_camera.go_to_mappoint(c);

    logs::info("[test-camera] tile=%d,%d cam=%d,%d zoom=%.0f layers=%d collapsed=%d vp=%d,%d", c.x(), c.y(),
      g_camera.camera_position.x, g_camera.camera_position.y, g_zoom.get_percentage(), height_layers,
      (int)g_camera.sidebar_collapsed, g_camera.size_pixels.x, g_camera.size_pixels.y);
}
ANK_FUNCTION_1(__test_camera_center_building);

static void __camera_scroll(int dx, int dy) {
    // Unclamped nudge for screenshot framing.
    g_camera.camera_position.x += dx;
    g_camera.camera_position.y += dy;
    g_camera.tile_internal.x = g_camera.camera_position.x / TILE_WIDTH_PIXELS;
    g_camera.tile_internal.y = g_camera.camera_position.y / HALF_TILE_HEIGHT_PIXELS;
    g_camera.tile_internal.y &= ~1;
    g_camera.update_derived_camera_state();
}
ANK_FUNCTION_2(__camera_scroll);

static void __camera_sidebar_collapsed(int collapsed) {
    g_camera.toggle_sidebar(collapsed ? 1 : 0);
}
ANK_FUNCTION_1(__camera_sidebar_collapsed);

// Hot-reload stack regression: each js_vm_sync used to leave ~1 stack slot per
// [console_command=…] handler (~30). JS_STACKSIZE is 256, so ~10 reloads then
// crashed in config::refresh / UI archive load (stackoverflow ? fatal exit).
static bool __test_js_hotreload_handlers_stack_ok(int iterations) {
    js_State* J = js_vm_state();
    if (!J || iterations < 1) {
        return false;
    }

    const int baseline = J->gettop();
    for (int i = 0; i < iterations; ++i) {
        js_register_game_handlers({});
    }
    const int after = J->gettop();
    logs::info("[test-marker] hotreload_handlers_stack baseline=%d after=%d iterations=%d", baseline, after,
      iterations);
    if (after != baseline) {
        logs::info("[hotreload] handlers stack leak delta=%d", after - baseline);
        return false;
    }
    return true;
}
ANK_FUNCTION_1(__test_js_hotreload_handlers_stack_ok);

static bool __test_js_hotreload_file_stack_ok(pcstr path, int iterations) {
    js_State* J = js_vm_state();
    if (!J || !path || !*path || iterations < 1) {
        return false;
    }

    const int baseline = J->gettop();
    for (int i = 0; i < iterations; ++i) {
        js_vm_reload_file(path);
        js_vm_sync({});
    }
    const int after = J->gettop();
    logs::info("[test-marker] hotreload_file_stack path=%s baseline=%d after=%d iterations=%d", path, baseline, after,
      iterations);
    if (after != baseline) {
        logs::info("[hotreload] file reload stack leak delta=%d", after - baseline);
        return false;
    }
    return true;
}
ANK_FUNCTION_2(__test_js_hotreload_file_stack_ok);

static pcstr __test_autosave_format(int slots, int slot) {
    static bstring256 buf;
    buf = autosave_module_t::format_monthly_filename(slots, slot, "svx");
    return buf.c_str();
}
ANK_FUNCTION_2(__test_autosave_format);

static int __test_autosave_pick(int slots, int exists_mask, int m0, int m1, int m2) {
    bool exists[10] = {};
    uint64_t mtime[10] = {};
    if (slots < 1) {
        slots = 1;
    }
    if (slots > 10) {
        slots = 10;
    }
    const int mtimes_in[] = {m0, m1, m2};
    for (int i = 0; i < slots; ++i) {
        exists[i] = (exists_mask & (1 << i)) != 0;
        mtime[i] = exists[i] ? (uint64_t)(i < 3 ? mtimes_in[i] : (100 + i)) : UINT64_MAX;
    }
    return autosave_module_t::pick_slot(slots, exists, mtime);
}
ANK_FUNCTION_5(__test_autosave_pick);

static bool __test_ironwill_exempt(pcstr filename_short) {
    return autosave_module_t::is_ironwill_exempt_save(filename_short);
}
ANK_FUNCTION_1(__test_ironwill_exempt);
