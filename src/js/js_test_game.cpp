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
#include "building/building_delivery_path.h"
#include "building/building_house.h"
#include "building/building_bazaar.h"
#include "building/building_granary.h"
#include "building/building_food_mill.h"
#include "building/building_static_params.h"
#include "building/building_storage.h"
#include "building/building_storage_yard.h"
#include "building/building_temple_complex.h"
#include "building/monument_mastaba.h"
#include "building/monument_pyramid.h"
#include "building/monument_royal_tomb.h"
#include "building/monuments.h"
#include "building/construction_blessing.h"
#include "city/city_recorded_paths.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "graphics/view/view.h"
#include "graphics/view/zoom.h"
#include "graphics/image.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figuretype/figure_market_buyer.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_hunter.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_tomb_artisan.h"
#include "figuretype/animal_lion.h"
#include "figuretype/animal_asp.h"
#include "figuretype/animal_scorpion.h"
#include "figuretype/figure_mummy.h"
#include "figuretype/figure_plagued_citizen.h"
#include "figuretype/figure_locust.h"
#include "figuretype/figure_frog.h"
#include "figuretype/figure_funeral_walker.h"
#include "figuretype/figure_tomb_robber.h"
#include "figuretype/figure_constable.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "figuretype/figure_enemy_elephant.h"
#include "figuretype/figure_enemy_spearman.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_soldier.h"
#include "building/building_transport_wharf.h"
#include "figure/combat.h"
#include "city/city_animals.h"
#include "graphics/color.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_industry.h"
#include "city/city_buildings.h"
#include "city/city_maintenance.h"
#include "city/city_religion_seth.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "game/autosave_module.h"
#include "core/bstring.h"
#include "game/game.h"
#include "game/file_editor.h"
#include "game/resource.h"
#include "content/vfs.h"
#include "editor/editor.h"
#include "io/gamestate/boilerplate.h"
#include "input/hotkey.h"
#include "scenario/editor.h"
#include "scenario/editor_map_meta.h"
#include "game/game_events.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario_invasion.h"
#include "scenario/types.h"
#include "window/window_info.h"
#include "city/object_info.h"
#include "scenario/request.h"
#include "scenario/distant_battle.h"
#include "figure/enemy_army.h"
#include "figure/formation.h"
#include "empire/empire.h"
#include "widget/widget_sidebar.h"

#include <SDL.h>
#include <algorithm>
#include <cstdio>
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
    events::emit(event_show_main_menu{ false });
    events::process();
}

void __test_end_city_session() {
    test_reset_session_between_tests();
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

void __test_process_scenario_events() {
    g_scenario.events.process_events();
}
ANK_FUNCTION(__test_process_scenario_events);

int __test_request_cleared_seq() {
    return scenario_request_last_cleared().seq;
}
ANK_FUNCTION(__test_request_cleared_seq);

int __test_request_cleared_tag_id() {
    return scenario_request_last_cleared().tag_id;
}
ANK_FUNCTION(__test_request_cleared_tag_id);

int __test_request_cleared_resource() {
    return scenario_request_last_cleared().resource;
}
ANK_FUNCTION(__test_request_cleared_resource);

int __test_request_cleared_fulfilled() {
    return scenario_request_last_cleared().fulfilled;
}
ANK_FUNCTION(__test_request_cleared_fulfilled);

int __test_request_cleared_was_overdue() {
    return scenario_request_last_cleared().was_overdue;
}
ANK_FUNCTION(__test_request_cleared_was_overdue);

// ED4a: editor request slots ↔ EVENT_TYPE_REQUEST (tag 8000+slot).
int __test_editor_request_roundtrip() {
    g_scenario.events.clear_for_editor();

    editor_request in{};
    in.year = 2;
    in.resource = RESOURCE_CLAY;
    in.amount = 10;
    in.deadline_years = 1;
    in.kingdom = 8;
    g_scenario.events.editor_request_save(0, &in);

    editor_request out{};
    g_scenario.events.editor_request_get(0, &out);
    if (out.year != 2 || out.resource != RESOURCE_CLAY || out.amount != 10
        || out.deadline_years != 1 || out.kingdom != 8) {
        return 0;
    }

    // Sparse slot: save 3 without filling 1/2; slot 0 must stay put.
    editor_request sparse{};
    sparse.year = 5;
    sparse.resource = RESOURCE_POTTERY;
    sparse.amount = 20;
    sparse.deadline_years = 2;
    sparse.kingdom = 4;
    g_scenario.events.editor_request_save(3, &sparse);

    editor_request slot0{};
    g_scenario.events.editor_request_get(0, &slot0);
    if (slot0.resource != RESOURCE_CLAY || slot0.amount != 10) {
        return 0;
    }
    editor_request gap{};
    g_scenario.events.editor_request_get(1, &gap);
    if (gap.resource != RESOURCE_NONE) {
        return 0;
    }
    editor_request slot3{};
    g_scenario.events.editor_request_get(3, &slot3);
    if (slot3.year != 5 || slot3.resource != RESOURCE_POTTERY || slot3.amount != 20
        || slot3.deadline_years != 2 || slot3.kingdom != 4) {
        return 0;
    }

    g_scenario.events.editor_request_delete(0);
    editor_request empty{};
    g_scenario.events.editor_request_get(0, &empty);
    if (empty.resource != RESOURCE_NONE) {
        return 0;
    }
    // Deleting slot 0 must not shift tag-stable slot 3.
    g_scenario.events.editor_request_get(3, &slot3);
    return (slot3.resource == RESOURCE_POTTERY && slot3.amount == 20) ? 1 : 0;
}
ANK_FUNCTION(__test_editor_request_roundtrip);

// ED4b/ED5: map write strips scenario_events; sidecar *.meta.js round-trips
// editor request slots + invasion/price/demand schedules.
// Returns 1 on success; on failure logs a step tag and returns 0.
int __test_editor_map_meta_roundtrip() {
    g_scenario.events.clear_for_editor();
    editor_invasions_clear();
    editor_price_changes_clear();
    editor_demand_changes_clear();

    editor_request in{};
    in.year = 3;
    in.resource = RESOURCE_CLAY;
    in.amount = 12;
    in.deadline_years = 2;
    in.kingdom = 5;
    g_scenario.events.editor_request_save(0, &in);

    editor_request sparse{};
    sparse.year = 7;
    sparse.resource = RESOURCE_POTTERY;
    sparse.amount = 4;
    sparse.deadline_years = 1;
    sparse.kingdom = 1;
    g_scenario.events.editor_request_save(3, &sparse);

    editor_invasion inv_in{};
    inv_in.year = 2;
    inv_in.type = INVASION_TYPE_ENEMY_ARMY;
    inv_in.amount = 16;
    inv_in.from = 3;
    inv_in.attack_type = FORMATION_ATTACK_TROOPS;
    scenario_editor_invasion_save(0, &inv_in);

    editor_invasion inv_sparse{};
    inv_sparse.year = 5;
    inv_sparse.type = INVASION_TYPE_LOCAL_UPRISING;
    inv_sparse.amount = 8;
    inv_sparse.from = 1;
    inv_sparse.attack_type = FORMATION_ATTACK_FOOD_CHAIN;
    scenario_editor_invasion_save(2, &inv_sparse);

    editor_price_change price_in{};
    price_in.year = 4;
    price_in.resource = RESOURCE_CLAY;
    price_in.amount = 10;
    price_in.is_rise = 1;
    scenario_editor_price_change_save(0, &price_in);

    editor_demand_change demand_in{};
    demand_in.year = 6;
    demand_in.resource = RESOURCE_POTTERY;
    demand_in.route_id = 2;
    demand_in.is_rise = 0;
    scenario_editor_demand_change_save(0, &demand_in);

    const char *map_path = "Maps/_editor_meta_rt.map";
    if (!game_file_editor_write_scenario(map_path)) {
        logs::info("[test:172] step=write_failed");
        return 0;
    }

    editor_request live0{};
    g_scenario.events.editor_request_get(0, &live0);
    if (live0.resource != RESOURCE_CLAY || live0.amount != 12) {
        logs::info("[test:172] step=live_buffer res=%d amount=%d", (int)live0.resource, live0.amount);
        return 0;
    }

    vfs::path meta = editor_map_meta_path(map_path);
    if (!vfs::file_exists(meta)) {
        logs::info("[test:172] step=meta_missing path=%s", meta.c_str());
        return 0;
    }

    editor_map_meta_remove(map_path);
    g_scenario.events.clear_for_editor();
    editor_invasions_clear();
    editor_price_changes_clear();
    editor_demand_changes_clear();
    if (!game_file_editor_load_scenario(map_path)) {
        logs::info("[test:172] step=load_map_only_failed");
        return 0;
    }
    editor_request empty{};
    g_scenario.events.editor_request_get(0, &empty);
    if (empty.resource != RESOURCE_NONE) {
        logs::info("[test:172] step=map_still_has_requests res=%d", (int)empty.resource);
        return 0;
    }
    if (g_scenario.invasions[0].type != 0) {
        logs::info("[test:172] step=map_still_has_invasions type=%d", g_scenario.invasions[0].type);
        return 0;
    }
    if (g_scenario.price_changes[0].resource != RESOURCE_NONE || g_scenario.demand_changes[0].resource != RESOURCE_NONE) {
        logs::info("[test:172] step=map_still_has_trade_schedules");
        return 0;
    }

    g_scenario.events.editor_request_save(0, &in);
    g_scenario.events.editor_request_save(3, &sparse);
    scenario_editor_invasion_save(0, &inv_in);
    scenario_editor_invasion_save(2, &inv_sparse);
    scenario_editor_price_change_save(0, &price_in);
    scenario_editor_demand_change_save(0, &demand_in);
    if (!game_file_editor_write_scenario(map_path)) {
        logs::info("[test:172] step=rewrite_failed");
        return 0;
    }
    g_scenario.events.clear_for_editor();
    editor_invasions_clear();
    editor_price_changes_clear();
    editor_demand_changes_clear();
    if (!game_file_editor_load_scenario(map_path)) {
        logs::info("[test:172] step=load_with_meta_failed");
        return 0;
    }

    editor_request out0{};
    g_scenario.events.editor_request_get(0, &out0);
    editor_request out3{};
    g_scenario.events.editor_request_get(3, &out3);
    // sort_invasions() packs filled slots by year — expect years 2 then 5 at 0/1.
    const invasion_t &out_inv0 = g_scenario.invasions[0];
    const invasion_t &out_inv1 = g_scenario.invasions[1];
    const price_change_t &out_price = g_scenario.price_changes[0];
    const demand_change_t &out_demand = g_scenario.demand_changes[0];
    const bool ok = out0.year == 3 && out0.resource == RESOURCE_CLAY && out0.amount == 12
                    && out0.deadline_years == 2 && out0.kingdom == 5
                    && out3.year == 7 && out3.resource == RESOURCE_POTTERY && out3.amount == 4
                    && out3.deadline_years == 1 && out3.kingdom == 1
                    && out_inv0.year == 2 && out_inv0.type == INVASION_TYPE_ENEMY_ARMY
                    && out_inv0.amount == 16 && out_inv0.from == 3
                    && out_inv0.attack_type == FORMATION_ATTACK_TROOPS
                    && out_inv1.year == 5 && out_inv1.type == INVASION_TYPE_LOCAL_UPRISING
                    && out_inv1.amount == 8 && out_inv1.from == 1
                    && out_inv1.attack_type == FORMATION_ATTACK_FOOD_CHAIN
                    && out_price.year == 4 && out_price.resource == RESOURCE_CLAY
                    && out_price.amount == 10 && out_price.is_rise == 1
                    && out_demand.year == 6 && out_demand.resource == RESOURCE_POTTERY
                    && out_demand.route_id == 2 && out_demand.is_rise == 0;
    if (!ok) {
        logs::info("[test:172] step=slot_mismatch s0=%d/%d/%d s3=%d/%d/%d inv0=%d/%d/%d inv1=%d/%d/%d p=%d/%d/%d d=%d/%d/%d",
                   out0.year, (int)out0.resource, out0.amount,
                   out3.year, (int)out3.resource, out3.amount,
                   out_inv0.year, out_inv0.type, out_inv0.amount,
                   out_inv1.year, out_inv1.type, out_inv1.amount,
                   out_price.year, (int)out_price.resource, out_price.amount,
                   out_demand.year, (int)out_demand.resource, out_demand.route_id);
    }

    GamestateIO::delete_map("_editor_meta_rt.map");
    return ok ? 1 : 0;
}
ANK_FUNCTION(__test_editor_map_meta_roundtrip);

// ED5: custom-map play loads sidecar invasions before g_invasions.init().
int __test_editor_invasion_meta_play() {
    g_scenario.events.clear_for_editor();
    editor_invasions_clear();

    editor_invasion inv{};
    inv.year = 1;
    inv.type = INVASION_TYPE_ENEMY_ARMY;
    inv.amount = 12;
    inv.from = 2;
    inv.attack_type = FORMATION_ATTACK_BEST_BUILDINGS;
    scenario_editor_invasion_save(0, &inv);

    const char *map_path = "Maps/_editor_inv_play.map";
    if (!game_file_editor_write_scenario(map_path)) {
        logs::info("[test:173] step=write_failed");
        return 0;
    }

    editor_invasions_clear();
    if (g_scenario.invasions[0].type != 0) {
        logs::info("[test:173] step=clear_failed");
        return 0;
    }

    // Play path: leave editor so load_map applies sidecar before g_invasions.init().
    game_exit_editor();
    if (!GamestateIO::load_map("_editor_inv_play.map", true, true)) {
        logs::info("[test:173] step=load_play_failed");
        GamestateIO::delete_map("_editor_inv_play.map");
        return 0;
    }

    const invasion_t &got = g_scenario.invasions[0];
    // Custom maps often have no empire invasion path — init may no-op month assign.
    // Success = sidecar applied on play load (schedule present for scenario_invasion_process).
    const bool ok = got.year == 1 && got.type == INVASION_TYPE_ENEMY_ARMY && got.amount == 12
                    && got.from == 2 && got.attack_type == FORMATION_ATTACK_BEST_BUILDINGS;
    if (!ok) {
        logs::info("[test:173] step=mismatch year=%d type=%d amount=%d from=%d atk=%d",
                   got.year, got.type, got.amount, got.from, (int)got.attack_type);
    }

    GamestateIO::delete_map("_editor_inv_play.map");
    return ok ? 1 : 0;
}
ANK_FUNCTION(__test_editor_invasion_meta_play);

// ED5: custom-map play loads sidecar price/demand before scenario_*_change_init().
int __test_editor_price_demand_meta_play() {
    g_scenario.events.clear_for_editor();
    editor_price_changes_clear();
    editor_demand_changes_clear();

    editor_price_change price{};
    price.year = 3;
    price.resource = RESOURCE_CLAY;
    price.amount = 7;
    price.is_rise = 1;
    scenario_editor_price_change_save(0, &price);

    editor_demand_change demand{};
    demand.year = 4;
    demand.resource = RESOURCE_POTTERY;
    demand.route_id = 1;
    demand.is_rise = 0;
    scenario_editor_demand_change_save(0, &demand);

    const char *map_path = "Maps/_editor_trade_play.map";
    if (!game_file_editor_write_scenario(map_path)) {
        logs::info("[test:174] step=write_failed");
        return 0;
    }

    editor_price_changes_clear();
    editor_demand_changes_clear();
    game_exit_editor();
    if (!GamestateIO::load_map("_editor_trade_play.map", true, true)) {
        logs::info("[test:174] step=load_play_failed");
        GamestateIO::delete_map("_editor_trade_play.map");
        return 0;
    }

    const price_change_t &got_p = g_scenario.price_changes[0];
    const demand_change_t &got_d = g_scenario.demand_changes[0];
    const bool ok = got_p.year == 3 && got_p.resource == RESOURCE_CLAY && got_p.amount == 7 && got_p.is_rise == 1
                    && got_d.year == 4 && got_d.resource == RESOURCE_POTTERY && got_d.route_id == 1
                    && got_d.is_rise == 0;
    if (!ok) {
        logs::info("[test:174] step=mismatch p=%d/%d/%d/%d d=%d/%d/%d/%d",
                   got_p.year, (int)got_p.resource, got_p.amount, got_p.is_rise,
                   got_d.year, (int)got_d.resource, got_d.route_id, got_d.is_rise);
    }

    GamestateIO::delete_map("_editor_trade_play.map");
    return ok ? 1 : 0;
}
ANK_FUNCTION(__test_editor_price_demand_meta_play);

// ED5: win_criteria round-trip via map scenario_info + *.meta.js override.
int __test_editor_win_criteria_meta() {
    scenario_editor_set_culture(35);
    if (!g_scenario.win_criteria.culture.enabled) {
        scenario_editor_toggle_culture();
    }
    scenario_editor_set_prosperity(40);
    if (!g_scenario.win_criteria.prosperity.enabled) {
        scenario_editor_toggle_prosperity();
    }
    scenario_editor_set_population(2500);
    if (!g_scenario.win_criteria.population.enabled) {
        scenario_editor_toggle_population();
    }
    scenario_editor_set_time_limit(12);
    if (!g_scenario.win_criteria.time_limit.enabled) {
        scenario_editor_toggle_time_limit();
    }
    g_scenario.win_criteria.milestone25_year = 3;
    g_scenario.win_criteria.milestone50_year = 6;
    g_scenario.win_criteria.milestone75_year = 9;
    g_scenario.is_open_play = false;

    const char *map_path = "Maps/_editor_win_rt.map";
    if (!game_file_editor_write_scenario(map_path)) {
        logs::info("[test:175] step=write_failed");
        return 0;
    }

    vfs::path meta = editor_map_meta_path(map_path);
    if (!vfs::file_exists(meta)) {
        logs::info("[test:175] step=meta_missing");
        return 0;
    }

    // Map-alone: wipe meta + mutate RAM, load must restore from scenario_info.
    editor_map_meta_remove(map_path);
    g_scenario.win_criteria.culture.goal = 1;
    g_scenario.win_criteria.prosperity.goal = 1;
    g_scenario.win_criteria.population.goal = 1;
    g_scenario.win_criteria.population.enabled = 0;
    g_scenario.win_criteria.time_limit.enabled = 0;
    g_scenario.win_criteria.time_limit.years = 0;
    if (!game_file_editor_load_scenario(map_path)) {
        logs::info("[test:175] step=load_map_only_failed");
        return 0;
    }
    if (g_scenario.win_criteria.culture.goal != 35 || g_scenario.win_criteria.prosperity.goal != 40
        || !g_scenario.win_criteria.population.enabled || g_scenario.win_criteria.population.goal != 2500
        || !g_scenario.win_criteria.time_limit.enabled || g_scenario.win_criteria.time_limit.years != 12) {
        logs::info("[test:175] step=map_mismatch c=%d p=%d pop=%d/%d tl=%d/%d",
                   g_scenario.win_criteria.culture.goal,
                   g_scenario.win_criteria.prosperity.goal,
                   g_scenario.win_criteria.population.enabled,
                   g_scenario.win_criteria.population.goal,
                   g_scenario.win_criteria.time_limit.enabled,
                   g_scenario.win_criteria.time_limit.years);
        GamestateIO::delete_map("_editor_win_rt.map");
        return 0;
    }

    // Rewrite with meta; mutate; editor load applies sidecar over map.
    scenario_editor_set_culture(35);
    scenario_editor_set_prosperity(40);
    scenario_editor_set_population(2500);
    if (!g_scenario.win_criteria.population.enabled) {
        scenario_editor_toggle_population();
    }
    scenario_editor_set_time_limit(12);
    if (!g_scenario.win_criteria.time_limit.enabled) {
        scenario_editor_toggle_time_limit();
    }
    if (!game_file_editor_write_scenario(map_path)) {
        logs::info("[test:175] step=rewrite_failed");
        return 0;
    }
    g_scenario.win_criteria.culture.goal = 99;
    g_scenario.win_criteria.population.goal = 9;
    if (!game_file_editor_load_scenario(map_path)) {
        logs::info("[test:175] step=load_with_meta_failed");
        return 0;
    }
    if (g_scenario.win_criteria.culture.goal != 35 || g_scenario.win_criteria.population.goal != 2500) {
        logs::info("[test:175] step=meta_mismatch c=%d pop=%d",
                   g_scenario.win_criteria.culture.goal, g_scenario.win_criteria.population.goal);
        GamestateIO::delete_map("_editor_win_rt.map");
        return 0;
    }

    // Play path: meta overrides after map unserialize.
    g_scenario.win_criteria.culture.goal = 2;
    game_exit_editor();
    if (!GamestateIO::load_map("_editor_win_rt.map", true, true)) {
        logs::info("[test:175] step=load_play_failed");
        GamestateIO::delete_map("_editor_win_rt.map");
        return 0;
    }
    const bool ok = g_scenario.win_criteria.culture.goal == 35 && g_scenario.win_criteria.prosperity.goal == 40
                    && g_scenario.win_criteria.population.enabled && g_scenario.win_criteria.population.goal == 2500
                    && g_scenario.win_criteria.time_limit.enabled && g_scenario.win_criteria.time_limit.years == 12
                    && g_scenario.win_criteria.milestone25_year == 3;
    if (!ok) {
        logs::info("[test:175] step=play_mismatch c=%d p=%d pop=%d tl=%d m25=%d",
                   g_scenario.win_criteria.culture.goal,
                   g_scenario.win_criteria.prosperity.goal,
                   g_scenario.win_criteria.population.goal,
                   g_scenario.win_criteria.time_limit.years,
                   g_scenario.win_criteria.milestone25_year);
    }

    GamestateIO::delete_map("_editor_win_rt.map");
    return ok ? 1 : 0;
}
ANK_FUNCTION(__test_editor_win_criteria_meta);

// Procedural editor map: generate medium landscape and require water + road tiles + entry point.
int __test_editor_map_generate() {
    game_file_editor_generate_scenario(2); // medium 80x80

    const int mw = g_scenario.map.width;
    const int mh = g_scenario.map.height;
    int water = 0;
    int road = 0;
    int meadow = 0;
    int trees = 0;
    int rocks = 0;
    for (int y = 0; y < mh; y++) {
        for (int x = 0; x < mw; x++) {
            const int t = map_terrain_get(MAP_OFFSET(x, y));
            if (t & (TERRAIN_WATER | TERRAIN_DEEPWATER))
                water++;
            if (t & TERRAIN_ROAD)
                road++;
            if (t & TERRAIN_MEADOW)
                meadow++;
            if (t & TERRAIN_TREE)
                trees++;
            if (t & TERRAIN_ROCK)
                rocks++;
        }
    }

    const bool entry_ok = g_scenario.entry_point.x() >= 0 && g_scenario.exit_point.x() >= 0;
    const bool ok = water > 0 && road > 0 && entry_ok;
    if (!ok) {
        logs::info("[test:173] step=generate_sparse water=%d road=%d meadow=%d trees=%d rocks=%d entry=%d,%d exit=%d,%d",
                   water, road, meadow, trees, rocks,
                   g_scenario.entry_point.x(), g_scenario.entry_point.y(),
                   g_scenario.exit_point.x(), g_scenario.exit_point.y());
    }
    return ok ? 1 : 0;
}
ANK_FUNCTION(__test_editor_map_generate);

static event_ph_t *__test_find_request_by_tag(int tag) {
    for (int i = 0; i < g_scenario.events.events_count(); ++i) {
        event_ph_t *e = g_scenario.events.at(i);
        if (e && e->type == EVENT_TYPE_REQUEST && e->tag_id == tag) {
            return e;
        }
    }
    return nullptr;
}

// Force overdue grace with months_left months remaining (for late-fulfill tests).
void __test_request_force_overdue(int tag, int months_left) {
    event_ph_t *e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    e->event_state = e_event_state_overdue;
    e->is_overdue = true;
    e->quest_months_left = (uint8_t)std::max(0, months_left);
}
ANK_FUNCTION_2(__test_request_force_overdue);

// Expire grace immediately → refuse path on next process_active_request.
void __test_request_force_refuse_now(int tag) {
    event_ph_t *e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    e->event_state = e_event_state_overdue;
    e->is_overdue = true;
    e->quest_months_left = 0;
    g_scenario.events.process_active_request(e->event_id);
}
ANK_FUNCTION_1(__test_request_force_refuse_now);

// Tag-targeted fulfill (visible-index dispatch is ambiguous when a mission has many requests).
void __test_request_force_fulfill(int tag, int as_late) {
    event_ph_t *e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    if (as_late) {
        e->is_overdue = true;
        e->event_state = e_event_state_finished_late;
    } else {
        e->is_overdue = false;
        e->event_state = e_event_state_finished;
    }
    g_scenario.events.process_active_request(e->event_id);
}
ANK_FUNCTION_2(__test_request_force_fulfill);

// Advisor-style dispatch (RESOURCE_TROOPS + defeat → distant battle; B8).
void __test_request_dispatch_by_tag(int tag) {
    event_ph_t *e = __test_find_request_by_tag(tag);
    if (!e || !e->is_active) {
        return;
    }
    scenario_request_dispatch_event(e->event_id);
}
ANK_FUNCTION_1(__test_request_dispatch_by_tag);

void __test_distant_battle_set_egyptian_strength(int strength) {
    if (strength <= 0) {
        g_distant_battle.battle.egyptian_strength = 0;
        g_distant_battle.battle.egyptian_months_to_travel_forth = 0;
    } else {
        g_distant_battle.battle.egyptian_strength = (uint8_t)std::min(255, strength);
        g_distant_battle.battle.egyptian_months_to_travel_forth = 1;
    }
}
ANK_FUNCTION_1(__test_distant_battle_set_egyptian_strength);

void __test_process_distant_battle_month() {
    g_distant_battle.process_distant_battle_impl();
}
ANK_FUNCTION(__test_process_distant_battle_month);

int __test_distant_battle_egyptian_strength() {
    return (int)g_distant_battle.battle.egyptian_strength;
}
ANK_FUNCTION(__test_distant_battle_egyptian_strength);

int __test_distant_battle_enemy_strength() {
    return (int)g_distant_battle.battle.enemy_strength;
}
ANK_FUNCTION(__test_distant_battle_enemy_strength);

void __test_process_invasion_binds() {
    g_invasions.process_bind_resolutions();
}
ANK_FUNCTION(__test_process_invasion_binds);

// B3: seed / inspect a single invasion_warning slot for saveload.
void __test_invasion_warning_force(int idx, int months_to_go, int warning_years, int handled) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return;
    }
    auto &w = g_invasions.warnings[idx];
    w = {};
    w.in_use = true;
    w.handled = handled != 0;
    w.months_to_go = months_to_go;
    w.warning_years = warning_years;
    w.invasion_path_id = 3;
    w.invasion_id = 5;
    w.empire_object_id = 42;
    w.image_id = 7;
    w.pos = {11, 22};
    w.year_notified = 1400;
    w.month_notified = 4;
}
ANK_FUNCTION_4(__test_invasion_warning_force);

int __test_invasion_warning_months_to_go(int idx) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return -1;
    }
    const auto &w = g_invasions.warnings[idx];
    return w.in_use ? w.months_to_go : -1;
}
ANK_FUNCTION_1(__test_invasion_warning_months_to_go);

int __test_invasion_warning_handled(int idx) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return -1;
    }
    const auto &w = g_invasions.warnings[idx];
    return w.in_use ? (w.handled ? 1 : 0) : -1;
}
ANK_FUNCTION_1(__test_invasion_warning_handled);

int __test_invasion_warning_pos_x(int idx) {
    if (idx < 0 || idx >= (int)g_invasions.warnings.size()) {
        return -999;
    }
    return g_invasions.warnings[idx].pos.x;
}
ANK_FUNCTION_1(__test_invasion_warning_pos_x);

int __test_last_message_eventmsg_phrase_id() {
    const int n = city_message_count();
    if (n <= 0) {
        return -1;
    }
    return city_message_get(n - 1).eventmsg_phrase_id;
}
ANK_FUNCTION(__test_last_message_eventmsg_phrase_id);

void __test_clear_enemy_formations() {
    for (int fi = 1; fi < MAX_FORMATIONS; ++fi) {
        formation *m = formation_get(fi);
        if (!m || !m->in_use || m->is_herd || m->own_batalion) {
            continue;
        }
        for (int fig = 0; fig < m->num_figures; ++fig) {
            if (m->figures[fig] > 0) {
                figure *f = figure_get(m->figures[fig]);
                if (f) {
                    f->poof();
                }
            }
        }
        g_formations.clear(fi);
    }
    // Also poof enemy figures that still reference a formation (pre-calculate state).
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figure *f = figure_get(i);
        if (!f || !f->is_alive() || f->formation_id <= 0) {
            continue;
        }
        formation *m = formation_get(f->formation_id);
        if (m && !m->own_batalion && !m->is_herd) {
            f->poof();
        }
    }
    g_formations.calculate_figures();
}
ANK_FUNCTION(__test_clear_enemy_formations);

static void __test_poof_kingdome_figures() {
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figure *f = figure_get(i);
        if (!f || !f->is_valid()) {
            continue;
        }
        if (figure_is_kingdome_army(f->type)) {
            f->poof();
        }
    }
}
ANK_FUNCTION(__test_poof_kingdome_figures);

// Force figures.reset()+action_perform. Needed when --integraltests pumps
// frames faster than tick_timer_ms (get_elapsed_ticks → 0).
static void __test_figures_update() {
    g_city.figures.update();
}
ANK_FUNCTION(__test_figures_update);

int __test_count_enemy_figures() {
    g_formations.calculate_figures();
    int n = 0;
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figure *f = figure_get(i);
        if (!f || !f->is_alive() || f->formation_id <= 0) {
            continue;
        }
        formation *m = formation_get(f->formation_id);
        if (m && m->in_use && !m->own_batalion && !m->is_herd) {
            ++n;
        }
    }
    return n;
}
ANK_FUNCTION(__test_count_enemy_figures);

void __test_set_scenario_enemy_id(int enemy_id) {
    g_scenario.enemy_id = (e_enemy_type)enemy_id;
}
ANK_FUNCTION_1(__test_set_scenario_enemy_id);

void __test_set_army_buildings_destroyed(int invasion_id, int count) {
    if (invasion_id <= 0 || invasion_id >= enemy_armies_t::MAX_ENEMY_ARMIES) {
        return;
    }
    enemy_army *army = enemy_army_get_editable((uint8_t)invasion_id);
    army->buildings_destroyed = (uint8_t)std::clamp(count, 0, 255);
}
ANK_FUNCTION_2(__test_set_army_buildings_destroyed);

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
    for (building *part = b->main(); part;) {
        part->state = BUILDING_STATE_VALID;
        if (!part->has_next()) {
            break;
        }
        part = part->next();
    }
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

static void __test_figure_set_home(int fid, int bid) {
    figure *f = figure_get(fid);
    building *b = building_get(bid);
    if (!f || !f->is_alive() || !b || !b->is_valid()) {
        return;
    }
    f->set_home(bid);
}
ANK_FUNCTION_2(__test_figure_set_home);

static void __test_figure_set_leading(int fid, int leader_id) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->leading_figure_id = (short)std::max(0, leader_id);
}
ANK_FUNCTION_2(__test_figure_set_leading);

static void __test_figure_set_collecting_item(int fid, int item) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->collecting_item_id = (uint8_t)std::clamp(item, 0, INVENTORY_MAX - 1);
}
ANK_FUNCTION_2(__test_figure_set_collecting_item);

static void __test_figure_set_speed(int fid, int speed) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->speed_multiplier = (uint8_t)std::clamp(speed, 0, 255);
}
ANK_FUNCTION_2(__test_figure_set_speed);

static int __test_figure_get_speed(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->speed_multiplier;
}
ANK_FUNCTION_1(__test_figure_get_speed);

static int __test_figure_apply_params_speed(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    f->apply_params_speed_multiplier();
    return f->speed_multiplier;
}
ANK_FUNCTION_1(__test_figure_apply_params_speed);

static int __test_figure_get_wait_ticks(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->wait_ticks;
}
ANK_FUNCTION_1(__test_figure_get_wait_ticks);

static int __test_cartpusher_destination_wait_threshold() {
    return figure_cartpusher::destination_wait_threshold();
}
ANK_FUNCTION(__test_cartpusher_destination_wait_threshold);

static int __test_building_create_cartpusher_wait_ticks(int bid) {
    building *b = building_get(bid);
    if (!b) {
        return -1;
    }
    figure *f = b->create_cartpusher(RESOURCE_GRAIN, 100, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL,
                                     BUILDING_SLOT_CARTPUSHER);
    return f ? f->wait_ticks : -1;
}
ANK_FUNCTION_1(__test_building_create_cartpusher_wait_ticks);

static void __test_figure_set_force_valid_animation(int fid, int enabled) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    f->set_force_valid_animation(enabled != 0);
}
ANK_FUNCTION_2(__test_figure_set_force_valid_animation);

static int __test_figure_get_damage(int fid) {
    figure *f = figure_get(fid);
    if (!f) {
        return -1;
    }
    return f->damage;
}
ANK_FUNCTION_1(__test_figure_get_damage);

static int __test_figure_is_alive(int fid) {
    figure *f = figure_get(fid);
    return (f && f->is_alive()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_is_alive);

static int __test_elephant_trample(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        return 0;
    }
    // Type check above: leaf is figure_egyptian_elephant → figure_enemy_elephant.
    auto *el = static_cast<figure_enemy_elephant *>(f->dcast());
    if (!el) {
        return 0;
    }
    el->trample_adjacent(true);
    return 1;
}
ANK_FUNCTION_1(__test_elephant_trample);

// Verify Julius-parity missile spawn args: create(shooter_id, shooter_tile, dst).
// Returns 1 if a FIGURE_SPEAR/ARROW exists with shooter_id == fid on the spearman's tile.
static int __test_spearman_fire_initial_missile(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto *sp = smart_cast<figure_enemy_spearman>(f);
    if (!sp) {
        return 0;
    }

    const e_figure_type want = sp->missile_type();
    auto target = figure_combat_get_missile_target_for_enemy(f, 10, g_city.figures.soldiers < 4);
    if (!target.fid || !target.tile.valid()) {
        return 0;
    }

    // Same create args as fixed figure_enemy_spearman::enemy_initial.
    auto *missile = figure_missile::create(fid, f->tile, target.tile, want);
    if (!missile) {
        return 0;
    }
    if (missile->runtime_data().shooter_id != fid) {
        return 0;
    }
    if (missile->base.tile != f->tile) {
        return 0;
    }
    return 1;
}
ANK_FUNCTION_1(__test_spearman_fire_initial_missile);

static int __test_count_figures(int type) {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f && f->is_alive() && f->type == (e_figure_type)type) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION_1(__test_count_figures);

static int __test_mummy_spawn_wave(int count) {
    return figure_mummy::spawn_wave(count);
}
ANK_FUNCTION_1(__test_mummy_spawn_wave);

static void __test_figure_action_perform(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    f->action_perform();
}
ANK_FUNCTION_1(__test_figure_action_perform);

static void __test_sentiment_set(int value) {
    g_city.sentiment.value = value;
}
ANK_FUNCTION_1(__test_sentiment_set);

static void __test_burial_provisions_force_dispatched(int resource, int dispatched) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return;
    }
    // Reset this resource on non-preexisting tombs, then deposit exactly `dispatched`.
    // Otherwise a prior steal leaves tomb stock > 0 and migrate skips — city/tomb desync.
    buildings_valid_do([&](building &b) {
        auto *m = b.dcast_monument();
        if (!m || !b.is_main() || m->is_preexisting()) {
            return;
        }
        auto &d = m->runtime_data();
        if (resource >= 0 && resource < RESOURCES_MAX) {
            d.burial_stock[resource] = 0;
        }
    });
    g_scenario.monuments.burial_provisions[resource].dispatched = std::max(0, dispatched);
    burial_provisions_migrate_city_pool_to_tombs();
}
ANK_FUNCTION_2(__test_burial_provisions_force_dispatched);

static int __test_tomb_robber_try_spawn(int force_gates) {
    return figure_tomb_robber::try_spawn(force_gates != 0);
}
ANK_FUNCTION_1(__test_tomb_robber_try_spawn);

static int __test_tomb_robber_spawn_wave(int count) {
    return figure_tomb_robber::spawn_wave(count);
}
ANK_FUNCTION_1(__test_tomb_robber_spawn_wave);

static int __test_tomb_robber_commit_plunder(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_TOMB_ROBER) {
        return 0;
    }
    return figure_tomb_robber(f).commit_plunder() ? 1 : 0;
}
ANK_FUNCTION_1(__test_tomb_robber_commit_plunder);

static int __test_tomb_robber_arrest(int fid, int force) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_TOMB_ROBER) {
        return 0;
    }
    return figure_tomb_robber(f).arrest(force != 0) ? 1 : 0;
}
ANK_FUNCTION_2(__test_tomb_robber_arrest);

static int __test_constable_try_arrest(int constable_id, int max_distance, int force) {
    figure *f = figure_get(constable_id);
    if (!f || !f->is_alive() || f->type != FIGURE_CONSTABLE) {
        return 0;
    }
    return figure_constable(f).try_arrest_criminal(max_distance, force != 0) ? 1 : 0;
}
ANK_FUNCTION_3(__test_constable_try_arrest);

static void __test_monument_set_preexisting(int bid, int preexisting) {
    building *b = building_get(bid);
    auto *m = b ? b->dcast_monument() : nullptr;
    if (m) {
        m->set_preexisting(preexisting != 0);
    }
}
ANK_FUNCTION_2(__test_monument_set_preexisting);

static int __test_monument_is_preexisting(int bid) {
    building *b = building_get(bid);
    auto *m = b ? b->dcast_monument() : nullptr;
    return (m && m->is_preexisting()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_monument_is_preexisting);

static int __test_kingdom_rating() {
    return g_city.kingdome.rating;
}
ANK_FUNCTION(__test_kingdom_rating);

static void __test_kingdom_set_rating(int value) {
    g_city.kingdome.rating = (uint8_t)std::clamp(value, 0, 100);
}
ANK_FUNCTION_1(__test_kingdom_set_rating);

static int __test_funeral_try_spawn(int force_ignore_road) {
    return figure_funeral_walker::try_spawn_all(force_ignore_road != 0);
}
ANK_FUNCTION_1(__test_funeral_try_spawn);

static int __test_funeral_target_tomb(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid() || f->type != FIGURE_FUNERAL_WALKER) {
        return 0;
    }
    return figure_funeral_walker(f).runtime_data().target_tomb_id;
}
ANK_FUNCTION_1(__test_funeral_target_tomb);

static int __test_funeral_dest_is_road(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid() || f->type != FIGURE_FUNERAL_WALKER) {
        return 0;
    }
    if (!f->destination_tile.valid()) {
        return 0;
    }
    return map_terrain_is(f->destination_tile, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE) ? 1 : 0;
}
ANK_FUNCTION_1(__test_funeral_dest_is_road);

static int __test_funeral_tomb_dest_is_road(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    tile2i dest = figure_funeral_walker::tomb_destination_tile(*b);
    if (!dest.valid()) {
        return 0;
    }
    return map_terrain_is(dest, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE) ? 1 : 0;
}
ANK_FUNCTION_1(__test_funeral_tomb_dest_is_road);

static int __test_monument_funeral_done(int bid) {
    building *b = building_get(bid);
    auto *m = b ? b->dcast_monument() : nullptr;
    return (m && m->has_funeral_done()) ? 1 : 0;
}
ANK_FUNCTION_1(__test_monument_funeral_done);

static void __test_monument_set_funeral_done(int bid, int done) {
    building *b = building_get(bid);
    auto *m = b ? b->dcast_monument() : nullptr;
    if (m) {
        m->set_funeral_done(done != 0);
    }
}
ANK_FUNCTION_2(__test_monument_set_funeral_done);

static int __test_locust_spawn_swarm(int count) {
    return figure_locust::spawn_swarm(count);
}
ANK_FUNCTION_1(__test_locust_spawn_swarm);

static int __test_locust_set_days(int fid, int days) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return 0;
    }
    figure_locust(f).runtime_data().days_left = (uint16_t)std::max(0, days);
    return 1;
}
ANK_FUNCTION_2(__test_locust_set_days);

static int __test_locust_get_days(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return -1;
    }
    return figure_locust(f).runtime_data().days_left;
}
ANK_FUNCTION_1(__test_locust_get_days);

static int __test_locust_cloud_variant(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return -1;
    }
    return figure_locust(f).runtime_data().cloud_variant;
}
ANK_FUNCTION_1(__test_locust_cloud_variant);

static int __test_figure_current_height(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return -1;
    }
    return f->current_height;
}
ANK_FUNCTION_1(__test_figure_current_height);

static int __test_locust_post_load(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LOCUST) {
        return 0;
    }
    // Simulate corrupt save flags then restore via on_post_load.
    f->allow_move_type = EMOVE_TERRAIN;
    f->use_cross_country = false;
    f->current_height = 0;
    figure_locust(f).runtime_data().cloud_variant = 99;
    figure_locust(f).on_post_load();
    if (f->allow_move_type != EMOVE_AMPHIBIAN || !f->use_cross_country) {
        return 0;
    }
    if (figure_locust(f).runtime_data().cloud_variant != 0) {
        return 0;
    }
    if (f->current_height <= 0) {
        return 0;
    }
    return 1;
}
ANK_FUNCTION_1(__test_locust_post_load);

static int __test_frog_spawn_swarm(int count) {
    return figure_frog::spawn_swarm(count);
}
ANK_FUNCTION_1(__test_frog_spawn_swarm);

static int __test_frog_set_days(int fid, int days) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_FROG) {
        return 0;
    }
    figure_frog(f).runtime_data().days_left = (uint16_t)std::max(0, days);
    return 1;
}
ANK_FUNCTION_2(__test_frog_set_days);

static int __test_frog_get_days(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_FROG) {
        return -1;
    }
    return figure_frog(f).runtime_data().days_left;
}
ANK_FUNCTION_1(__test_frog_get_days);

static int __test_frog_infest_house(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    figure_frog::infest_house(*b);
    auto *house = b->dcast_house();
    if (!house) {
        return 0;
    }
    return house->runtime_data().frog_infest_days > 0 ? 1 : 0;
}
ANK_FUNCTION_1(__test_frog_infest_house);

static int __test_building_curse_days(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    return b->curse_days_left;
}
ANK_FUNCTION_1(__test_building_curse_days);

static int __test_plagued_spawn_from_house(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    return figure_plagued_citizen::spawn_from_house(*b);
}
ANK_FUNCTION_1(__test_plagued_spawn_from_house);

static int __test_house_set_population(int bid, int pop) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    auto *house = b->dcast_house();
    if (!house) {
        return 0;
    }
    house->runtime_data().population = (uint16_t)std::max(0, pop);
    return house->house_population();
}
ANK_FUNCTION_2(__test_house_set_population);

static int __test_house_add_population(int bid, int num_people) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    auto *house = b->dcast_house();
    if (!house) {
        return -1;
    }
    house->add_population(num_people);
    return house->house_population();
}
ANK_FUNCTION_2(__test_house_add_population);

static int __test_house_mark_plague(int bid, int days) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building *main = b->main();
    if (!main) {
        return 0;
    }
    main->mark_plague(days);
    return main->has_plague ? 1 : 0;
}
ANK_FUNCTION_2(__test_house_mark_plague);

static int __test_building_has_plague(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    return b->main()->has_plague ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_has_plague);

static int __test_plagued_cure_nearby(int x, int y) {
    return figure_plagued_citizen::cure_nearby(tile2i(x, y), 1);
}
ANK_FUNCTION_2(__test_plagued_cure_nearby);

static int __test_figure_provide_service(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto *impl = f->dcast();
    if (!impl) {
        return 0;
    }
    return impl->provide_service();
}
ANK_FUNCTION_1(__test_figure_provide_service);

static int __test_figure_is_enemy(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return 0;
    }
    return f->is_enemy() ? 1 : 0;
}
ANK_FUNCTION_1(__test_figure_is_enemy);

static int __test_soldier_combat_target(int x, int y, int max_distance) {
    tile2i tile(x, y);
    if (!tile.valid()) {
        tile.set(g_scenario.map.width / 2, g_scenario.map.height / 2);
    }
    return figure_combat_get_target_for_soldier(tile, max_distance > 0 ? max_distance : 8);
}
ANK_FUNCTION_3(__test_soldier_combat_target);

static void __test_figure_kill(int fid) {
    figure *f = figure_get(fid);
    if (f && f->is_alive()) {
        f->wait_ticks = 0; // corpse timer must not inherit roam lifetime
        f->kill();
    }
}
ANK_FUNCTION_1(__test_figure_kill);

static int __test_city_kingdome_soldiers() {
    return g_city.figures.kingdome_soldiers;
}
ANK_FUNCTION(__test_city_kingdome_soldiers);

static int __test_kingdome_invasion_favour_only() {
    return g_city.kingdome.invasion.favour_only;
}
ANK_FUNCTION(__test_kingdome_invasion_favour_only);

static int __test_kingdome_invasion_size() {
    return g_city.kingdome.invasion.size;
}
ANK_FUNCTION(__test_kingdome_invasion_size);

static void __test_process_kingdome_invasion() {
    g_city.kingdome.process_invasion();
}
ANK_FUNCTION(__test_process_kingdome_invasion);

static void __test_kingdome_set_kills_to_size() {
    auto &inv = g_city.kingdome.invasion;
    if (inv.size > 0) {
        inv.soldiers_killed = inv.size;
    }
}
ANK_FUNCTION(__test_kingdome_set_kills_to_size);

static int __test_lion_setup_curse_raid(int fid, int days) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_LION) {
        return 0;
    }
    figure_lion_setup_curse_raid(*f, days);
    return 1;
}
ANK_FUNCTION_2(__test_lion_setup_curse_raid);

static int __test_lion_is_curse_raid(int fid) {
    figure *f = figure_get(fid);
    if (!f || f->type != FIGURE_LION) {
        return 0;
    }
    return figure_lion(f).is_curse_raid() ? 1 : 0;
}
ANK_FUNCTION_1(__test_lion_is_curse_raid);

static int __test_asp_setup_curse_raid(int fid, int days) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_ASP) {
        return 0;
    }
    figure_asp_setup_curse_raid(*f, days);
    return 1;
}
ANK_FUNCTION_2(__test_asp_setup_curse_raid);

static int __test_asp_is_curse_raid(int fid) {
    figure *f = figure_get(fid);
    if (!f || f->type != FIGURE_ASP) {
        return 0;
    }
    return figure_asp(f).is_curse_raid() ? 1 : 0;
}
ANK_FUNCTION_1(__test_asp_is_curse_raid);

static int __test_scorpion_setup_curse_raid(int fid, int days) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive() || f->type != FIGURE_SCORPION) {
        return 0;
    }
    figure_scorpion_setup_curse_raid(*f, days);
    return 1;
}
ANK_FUNCTION_2(__test_scorpion_setup_curse_raid);

static int __test_scorpion_is_curse_raid(int fid) {
    figure *f = figure_get(fid);
    if (!f || f->type != FIGURE_SCORPION) {
        return 0;
    }
    return figure_scorpion(f).is_curse_raid() ? 1 : 0;
}
ANK_FUNCTION_1(__test_scorpion_is_curse_raid);

static void __test_figure_update_day(int fid) {
    figure *f = figure_get(fid);
    auto *impl = f ? f->dcast() : nullptr;
    if (!impl) {
        return;
    }
    impl->update_day();
}
ANK_FUNCTION_1(__test_figure_update_day);

// Bypass hunt-animation callback: spawn the hunter's missile at its target.
static int __test_hunter_force_shot(int hunter_fid) {
    figure *hunter = figure_get(hunter_fid);
    if (!hunter || !hunter->is_alive()) {
        return 0;
    }

    figure_impl *impl = hunter->dcast();
    figure_hunter *h = impl ? impl->dcast_hunter() : nullptr;
    if (!h) {
        return 0;
    }

    if (!hunter->target_figure_id) {
        return 0;
    }
    figure *prey = figure_get(hunter->target_figure_id);
    if (!prey || !prey->is_alive()) {
        return 0;
    }

    const auto &params = h->hunter_params();
    auto missile = figure_missile::create(hunter->id, hunter->tile, prey->tile, h->missile_type());
    if (!missile) {
        return 0;
    }
    missile->runtime_data().missile_attack_value = params.animal_attack_value;
    return missile->id();
}
ANK_FUNCTION_1(__test_hunter_force_shot);

static int __test_get_scenario_climate() {
    return (int)g_scenario.climate;
}
ANK_FUNCTION(__test_get_scenario_climate);

static void __test_set_scenario_climate(int climate) {
    if (climate < CLIMATE_CENTRAL || climate > CLIMATE_DESERT) {
        return;
    }
    g_scenario.climate = (e_climate)climate;
}
ANK_FUNCTION_1(__test_set_scenario_climate);

static void __test_clear_scenario_prey_points() {
    g_scenario.herd_points_prey.clear();
}
ANK_FUNCTION(__test_clear_scenario_prey_points);

static void __test_set_scenario_prey_point(int index, int x, int y) {
    if (index < 0) {
        return;
    }
    if ((int)g_scenario.herd_points_prey.size() <= index) {
        g_scenario.herd_points_prey.resize(index + 1);
    }
    g_scenario.herd_points_prey[index].tile = tile2i(x, y);
}
ANK_FUNCTION_3(__test_set_scenario_prey_point);

static void __test_clear_scenario_herd_points() {
    g_scenario.herd_points_predator.clear();
}
ANK_FUNCTION(__test_clear_scenario_herd_points);

static void __test_set_scenario_herd_point(int index, int x, int y) {
    if (index < 0 || index >= MAX_PREDATOR_HERD_POINTS) {
        return;
    }
    if ((int)g_scenario.herd_points_predator.size() <= index) {
        g_scenario.herd_points_predator.resize(index + 1);
    }
    g_scenario.herd_points_predator[index].tile = tile2i(x, y);
}
ANK_FUNCTION_3(__test_set_scenario_herd_point);

static int __test_count_scenario_map_points(pcstr kind) {
    auto count_valid_herd = [](const auto &points) {
        int n = 0;
        for (const herd_point_t &hp : points) {
            n += hp.valid() ? 1 : 0;
        }
        return n;
    };
    auto count_valid_tiles = [](const auto &points) {
        int n = 0;
        for (const tile2i &t : points) {
            n += t.valid() ? 1 : 0;
        }
        return n;
    };

    if (!kind) {
        return 0;
    }
    if (!strcmp(kind, "prey")) {
        return count_valid_herd(g_scenario.herd_points_prey);
    }
    if (!strcmp(kind, "predator")) {
        return count_valid_herd(g_scenario.herd_points_predator);
    }
    if (!strcmp(kind, "fishing")) {
        return count_valid_tiles(g_scenario.fishing_points);
    }
    return 0;
}
ANK_FUNCTION_1(__test_count_scenario_map_points);

static int __test_climate_predator_type() {
    return (int)climate_predator_type();
}
ANK_FUNCTION(__test_climate_predator_type);

static void __test_create_herds() {
    g_city.animals.create_herds();
}
ANK_FUNCTION(__test_create_herds);

// Pack (x << 16) | y for a land tile where is_herd_spawn_accessible(ftype) holds; -1 if none.
static int __test_find_accessible_herd_tile(int ftype) {
    if (ftype <= FIGURE_NONE || ftype >= FIGURE_MAX) {
        return -1;
    }
    map_routing_update_land();
    const e_figure_type herd_type = (e_figure_type)ftype;
    const int w = g_scenario.map.width;
    const int h = g_scenario.map.height;
    for (int y = 8; y < h - 8; y += 2) {
        for (int x = 8; x < w - 8; x += 2) {
            tile2i tile(x, y);
            if (!tile.valid()) {
                continue;
            }
            if (g_city.animals.is_herd_spawn_accessible(tile, herd_type)) {
                return (x << 16) | (y & 0xffff);
            }
        }
    }
    return -1;
}
ANK_FUNCTION_1(__test_find_accessible_herd_tile);

static int __test_hunting_lodge_default_hunter_type() {
    return (int)hunting_lodge_default_hunter_type();
}
ANK_FUNCTION(__test_hunting_lodge_default_hunter_type);

static int __test_building_figure_spawn_delay(int bid) {
    building *b = building_get(bid);
    return b ? b->figure_spawn_delay : -1;
}
ANK_FUNCTION_1(__test_building_figure_spawn_delay);

static int __test_building_figure_spawn_timer(int bid) {
    building *b = building_get(bid);
    return b ? b->figure_spawn_timer() : -2;
}
ANK_FUNCTION_1(__test_building_figure_spawn_timer);

static void __test_building_set_figure_spawn_delay(int bid, int delay) {
    building *b = building_get(bid);
    if (!b) {
        return;
    }
    b->figure_spawn_delay = (short)delay;
}
ANK_FUNCTION_2(__test_building_set_figure_spawn_delay);

static int __test_hunting_lodge_active_hunters(building *b) {
    if (!b) {
        return -1;
    }
    return b->get_figures_number(FIGURE_OSTRICH_HUNTER)
        + b->get_figures_number(FIGURE_ANTELOPE_HUNTER)
        + b->get_figures_number(FIGURE_BIRDS_HUNTER);
}

static int __test_hunting_lodge_spawn_figure(int bid) {
    building *b = building_get(bid);
    if (!b || b->type != BUILDING_HUNTING_LODGE) {
        return -1;
    }
    building_impl *impl = b->dcast();
    if (!impl) {
        return -1;
    }
    b->has_road_access = true;
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    const int before = __test_hunting_lodge_active_hunters(b);
    impl->spawn_figure();
    return __test_hunting_lodge_active_hunters(b) - before;
}
ANK_FUNCTION_1(__test_hunting_lodge_spawn_figure);

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

namespace {

tile2i test_find_or_make_water_strip(int *out_cx, int *out_cy) {
    const int cx = g_scenario.map.width / 2;
    const int cy = g_scenario.map.height / 2;
    const int x0 = cx - 2;
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 6; dx++) {
            tile2i t(x0 + dx, cy + dy);
            map_terrain_add(t, TERRAIN_WATER);
        }
    }
    // Land strip above water for disembark.
    for (int dx = 0; dx < 6; dx++) {
        tile2i land(x0 + dx, cy - 1);
        map_terrain_remove(land, TERRAIN_WATER);
    }
    map_water_rebuild_shores();
    if (out_cx) {
        *out_cx = cx;
    }
    if (out_cy) {
        *out_cy = cy;
    }
    return tile2i(cx, cy);
}

} // namespace

// Spawn enemy transport with N soldiers loaded and sailing to a nearby shore.
// Returns transport figure id, or 0 on failure.
int __test_enemy_transport_spawn_loaded(int enemy_type, int soldier_count) {
    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    tile2i landing = tile2i(cx, cy);
    tile2i shore(cx, cy - 1);

    e_enemy_type enemy = (e_enemy_type)enemy_type;
    e_figure_type ship_type = enemy_transport_type_for(enemy);
    e_figure_type soldier_type = FIGURE_ENEMY_HITTITE_SPEARMAN;
    const enemy_properties_t &props = g_invasions.get_prop(enemy);
    if (props.figure_types[0] != FIGURE_NONE) {
        soldier_type = props.figure_types[0];
    }

    if (soldier_count < 1) {
        soldier_count = 1;
    }
    if (soldier_count > 8) {
        soldier_count = 8;
    }

    int formation_id = formation_create_enemy(soldier_type,
                                              shore,
                                              FORMATION_ENEMY_MOB,
                                              DIR_0_TOP_RIGHT,
                                              enemy,
                                              FORMATION_ATTACK_RANDOM,
                                              23,
                                              1);
    if (formation_id <= 0) {
        return 0;
    }

    for (int i = 0; i < soldier_count; i++) {
        figure *s = figure_create(soldier_type, water, DIR_0_TOP_RIGHT);
        if (!s || !s->is_valid()) {
            continue;
        }
        s->faction_id = 0;
        s->formation_id = formation_id;
        s->index_in_formation = (uint8_t)i;
        s->action_state = ACTION_152_ENEMY_WAITING;
        s->wait_ticks = 30000;
        s->formation_at_rest = 1;
        s->allow_move_type = EMOVE_AMPHIBIAN;
        s->set_flag(e_figure_flag_invisible);
    }

    auto abort_test_formation = [formation_id]() {
        for (figure *f : map_figures()) {
            if (f && f->is_alive() && f->formation_id == formation_id) {
                f->set_flag(e_figure_flag_invisible, false);
                f->kill();
            }
        }
        formation *m = formation_get(formation_id);
        if (m && m->in_use) {
            m->num_figures = 0;
            for (int fi = 0; fi < formation::max_figures_count; fi++) {
                m->figures[fi] = 0;
            }
            m->in_use = false;
        }
    };

    figure *ship = figure_create(ship_type, water, DIR_0_TOP_RIGHT);
    if (!ship || !ship->is_valid()) {
        abort_test_formation();
        return 0;
    }

    auto *transport = smart_cast<figure_enemy_transport>(ship);
    if (!transport) {
        ship->kill();
        abort_test_formation();
        return 0;
    }
    if (!transport->load_formation(formation_id)) {
        ship->kill();
        abort_test_formation();
        return 0;
    }
    if (!transport->sail_to_landing(landing)) {
        ship->kill();
        abort_test_formation();
        return 0;
    }
    return ship->id;
}
ANK_FUNCTION_2(__test_enemy_transport_spawn_loaded);

int __test_enemy_transport_has_troops(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return 0;
    }
    auto *t = smart_cast<figure_enemy_transport>(f);
    return t && t->has_troops() ? 1 : 0;
}
ANK_FUNCTION_1(__test_enemy_transport_has_troops);

static int g_test_player_transport_company_id = 0;
static int g_test_player_transport_water_x = 0;
static int g_test_player_transport_water_y = 0;

// Spawn a moored player transport + own infantry company on adjacent shore.
// Returns transport figure id (0 on failure). Company id via __test_player_transport_company_id().
int __test_player_transport_spawn_for_embark(int soldier_count) {
    g_test_player_transport_company_id = 0;

    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    g_test_player_transport_water_x = cx;
    g_test_player_transport_water_y = cy;

    if (soldier_count < 1) {
        soldier_count = 1;
    }
    if (soldier_count > 8) {
        soldier_count = 8;
    }

    // Prefer a clear shore tile on the land strip (avoid stomping map buildings).
    tile2i shore = tile2i::invalid;
    for (int dx = -2; dx <= 2; dx++) {
        tile2i cand(cx + dx, cy - 1);
        if (!cand.valid()) {
            continue;
        }
        if (map_terrain_is(cand, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            continue;
        }
        if (map_building_at(cand) > 0) {
            continue;
        }
        shore = cand;
        break;
    }
    if (!shore.valid()) {
        shore = tile2i(cx, cy - 1);
        int bid = map_building_at(shore);
        if (bid > 0) {
            building *old = building_get(bid);
            if (old && old->id) {
                old->state = BUILDING_STATE_UNUSED;
            }
            map_building_tiles_remove(bid, shore);
        }
    }

    // Minimal home wharf so figure_action can run LEAVING/ANCHORED.
    building *wharf_b = building_create(BUILDING_TRANSPORT_WHARF, shore, 0);
    if (!wharf_b || !wharf_b->id) {
        logs::info("[test:103] spawn fail: wharf create");
        return 0;
    }
    add_building(wharf_b, 0, 0);
    wharf_b->state = BUILDING_STATE_VALID;
    wharf_b->num_workers = 10;
    wharf_b->max_workers = 10;
    if (auto *wharf = wharf_b->dcast_transport_wharf()) {
        wharf->set_water_access_tiles({ water, water });
    }

    formation *m = formation_get_free(1);
    if (!m || !m->id) {
        logs::info("[test:103] spawn fail: formation");
        return 0;
    }
    g_formations.clear(m->id);
    m->faction_id = 1;
    m->in_use = 1;
    m->own_batalion = true;
    m->figure_type = FIGURE_INFANTRY;
    m->layout = FORMATION_DOUBLE_LINE_1;
    m->morale = 50;
    m->is_at_fort = 0;
    m->batalion_id = m->id;
    m->max_figures = 16;
    m->tile = shore;
    m->standard_tile = shore;
    m->home = shore;
    g_test_player_transport_company_id = m->id;

    int spawned_soldiers = 0;
    for (int i = 0; i < soldier_count; i++) {
        figure *s = figure_create(FIGURE_INFANTRY, shore, DIR_0_TOP_RIGHT);
        if (!s) {
            continue;
        }
        s->faction_id = 1;
        s->formation_id = m->id;
        s->index_in_formation = (uint8_t)formation_add_figure(m->id, s->id, 1, 0, s->max_damage());
        s->action_state = ACTION_84_SOLDIER_AT_STANDARD;
        s->formation_at_rest = 1;
        spawned_soldiers++;
    }
    if (spawned_soldiers <= 0) {
        logs::info("[test:103] spawn fail: soldiers");
        return 0;
    }

    figure *ship_f = figure_create(FIGURE_TRANSPORT_SHIP, water, DIR_0_TOP_RIGHT);
    if (!ship_f || !ship_f->is_valid()) {
        logs::info("[test:103] spawn fail: ship create");
        return 0;
    }

    auto *ship = smart_cast<figure_transport_ship>(ship_f);
    if (!ship) {
        logs::info("[test:103] spawn fail: ship cast");
        return 0;
    }

    ship_f->set_home(wharf_b->id);
    wharf_b->set_figure(BUILDING_SLOT_BOAT, ship_f);
    ship_f->source_tile = water;
    ship_f->advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
    return ship_f->id;
}
ANK_FUNCTION_1(__test_player_transport_spawn_for_embark);

int __test_player_transport_company_id() {
    return g_test_player_transport_company_id;
}
ANK_FUNCTION(__test_player_transport_company_id);

int __test_player_transport_water_x() {
    return g_test_player_transport_water_x;
}
ANK_FUNCTION(__test_player_transport_water_x);

int __test_player_transport_water_y() {
    return g_test_player_transport_water_y;
}
ANK_FUNCTION(__test_player_transport_water_y);

// Snap player transport to its sail destination and enter ANCHORED so disembark timer can run.
void __test_transport_ship_snap_to_destination(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return;
    }
    auto *ship = smart_cast<figure_transport_ship>(f);
    if (!ship) {
        return;
    }
    if (f->destination_tile.valid()) {
        f->tile = f->destination_tile;
        f->previous_tile = f->destination_tile;
    }
    ship->runtime_data().embark_ticks = 0;
    f->advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
    f->direction = DIR_FIGURE_NONE;
    f->route_remove();
}
ANK_FUNCTION_1(__test_transport_ship_snap_to_destination);

int __test_count_visible_enemy_soldiers() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (!f || !f->is_alive()) {
            continue;
        }
        if (!f->is_visible()) {
            continue;
        }
        if (f->is_boat() || f->allow_move_type == EMOVE_WATER || f->allow_move_type == EMOVE_DEEPWATER) {
            continue;
        }
        if (smart_cast<figure_enemy_transport>(f) || smart_cast<figure_enemy_warship>(f)) {
            continue;
        }
        // Prefer flag, fall back to static params (fresh spawn / flag edge cases).
        if (!f->is_enemy() && !f->params().is_enemy) {
            continue;
        }
        count++;
    }
    return count;
}
ANK_FUNCTION(__test_count_visible_enemy_soldiers);

int __test_start_sea_invasion(int enemy_type, int size) {
    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    g_scenario.invasion_points_sea.clear();
    g_scenario.invasion_points_sea.push_back(water);
    g_scenario.disembark_points.clear();
    g_scenario.disembark_points.push_back(tile2i(cx, cy - 1));

    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    opts.enemy_type = (e_enemy_type)enemy_type;
    opts.size = size > 0 ? size : 8;
    opts.via_sea = true;
    opts.invasion_id = 23;
    opts.attack_type = FORMATION_ATTACK_RANDOM;
    opts.kind = INVASION_KIND_FOREIGN;
    tile2i tile = scenario_start_invasion_impl(opts);
    return tile.valid() ? 1 : 0;
}
ANK_FUNCTION_2(__test_start_sea_invasion);

int __test_count_enemy_transports() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f && f->is_alive() && smart_cast<figure_enemy_transport>(f)) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION(__test_count_enemy_transports);

int __test_count_enemy_warships() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f && f->is_alive() && smart_cast<figure_enemy_warship>(f)) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION(__test_count_enemy_warships);

int __test_spawn_enemy_warship_on_water(int enemy_type) {
    int cx = 0;
    int cy = 0;
    tile2i water = test_find_or_make_water_strip(&cx, &cy);
    e_figure_type ftype = enemy_warship_type_for((e_enemy_type)enemy_type);
    figure *f = figure_create(ftype, water, DIR_0_TOP_RIGHT);
    return f && f->is_valid() ? f->id : 0;
}
ANK_FUNCTION_1(__test_spawn_enemy_warship_on_water);

void __test_seth_sink_all_ships() {
    god_seth.sink_all_ships();
}
ANK_FUNCTION(__test_seth_sink_all_ships);

void __test_show_tile_info(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }

    events::emit(event_show_tile_info{ b->tile, true, "test" });
}
ANK_FUNCTION_1(__test_show_tile_info);

pcstr __test_info_ui_text(pcstr element_id) {
    static bstring512 buf;
    buf = "";
    if (!element_id || !*element_id) {
        return buf.c_str();
    }
    object_info &context = common_info_window::get_object_info();
    if (!context.ui || !context.ui->contains(element_id)) {
        return buf.c_str();
    }
    buf = (*context.ui)[element_id].text().c_str();
    return buf.c_str();
}
ANK_FUNCTION_1(__test_info_ui_text);

static e_building_type test_mastaba_params_type(building *head) {
    switch (head->type) {
    case BUILDING_MEDIUM_MASTABA:
    case BUILDING_MEDIUM_MASTABA_SIDE:
    case BUILDING_MEDIUM_MASTABA_WALL:
    case BUILDING_MEDIUM_MASTABA_ENTRANCE:
    case BUILDING_MEDIUM_MASTABA_RESERVED:
        return BUILDING_MEDIUM_MASTABA;
    case BUILDING_LARGE_MASTABA:
    case BUILDING_LARGE_MASTABA_SIDE:
    case BUILDING_LARGE_MASTABA_WALL:
    case BUILDING_LARGE_MASTABA_ENTRANCE:
    case BUILDING_LARGE_MASTABA_RESERVED:
        return BUILDING_LARGE_MASTABA;
    default:
        return BUILDING_SMALL_MASTABA;
    }
}

static void test_monument_apply_phase(building *head, int phase) {
    auto mm = head->dcast_monument();
    if (!mm) {
        return;
    }
    mm->set_phase(phase);
    for (building *p = head->has_next() ? head->next() : nullptr; p; p = p->has_next() ? p->next() : nullptr) {
        if (auto pm = p->dcast_monument()) {
            pm->set_phase(phase);
        }
    }
}

// Force a monument to `phase`. When advancing forward, walks one phase at a time so
// per-phase hooks (pyramid setup_phase_6, layer type changes, …) all fire — a direct
// jump used to skip them and left the first brick ring with missing edge textures.
static void __test_monument_set_phase(int bid, int phase) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    if (!mm) {
        return;
    }

    const int cur = (int)mm->runtime_data().phase;
    if (cur >= 0 && phase > cur) {
        for (int p = cur + 1; p <= phase; ++p) {
            test_monument_apply_phase(head, p);
        }
    } else {
        test_monument_apply_phase(head, phase);
    }

    const bool is_mastaba = head->dcast_mastaba();
    const bool is_pyramid = head->dcast_pyramid();
    if (!is_mastaba && !is_pyramid) {
        return;
    }

    // Fill every part's tiles so height ornaments use the current layer (progress >= 200).
    for (building *p = head; p; p = p->has_next() ? p->next() : nullptr) {
        grid_tiles part_tiles = map_grid_get_tiles(p, 0);
        for (auto &t : part_tiles) {
            map_monuments_set_progress(t, 200);
        }
    }

    if (is_mastaba) {
        const vec2i tiles = get_mastaba_params(test_mastaba_params_type(head)).init_tiles;
        if (mm->is_finished() || mm->phase() >= 8 || phase >= 8) {
            building_mastaba::finalize(head, tiles);
        } else if (phase >= 2) {
            building_mastaba::update_images(head, phase, tiles);
        }
    }
}
ANK_FUNCTION_2(__test_monument_set_phase);

static int __test_monument_phase(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    // phase is int8_t (MONUMENT_FINISHED = -1); phase() returns uint8_t and would yield 255.
    return mm ? (int)mm->runtime_data().phase : -999;
}
ANK_FUNCTION_1(__test_monument_phase);

// Halt / unhalt monument construction (MOTHBALLED). Used by construction-blessing tests.
static void __test_monument_set_halted(int bid, int halted) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *mm = head ? head->dcast_monument() : nullptr;
    if (!mm) {
        return;
    }
    const bool want = halted != 0;
    if ((bool)mm->is_construction_halted() != want) {
        mm->toggle_construction_halted();
    }
}
ANK_FUNCTION_2(__test_monument_set_halted);

// Register a fake in-flight monument delivery (destination = main or part id).
static void __test_monument_add_delivery(int bid, int walker_id, int resource, int loads) {
    building *b = building_get(bid);
    auto *mm = b ? b->dcast_monument() : nullptr;
    if (!mm || loads <= 0) {
        return;
    }
    mm->add_delivery(walker_id, resource, loads);
}
ANK_FUNCTION_4(__test_monument_add_delivery);

static int __test_monument_resource_in_delivery(int bid, int resource) {
    building *b = building_get(bid);
    if (!b) {
        return -1;
    }
    return building_monument_resource_in_delivery(b, resource);
}
ANK_FUNCTION_2(__test_monument_resource_in_delivery);

static int __test_construction_blessing_cap(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *mm = head ? head->dcast_monument() : nullptr;
    return mm ? construction_blessing_cap_phase(*mm) : -1;
}
ANK_FUNCTION_1(__test_construction_blessing_cap);

static int __test_monument_next_part(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    if (!head || !head->has_next()) {
        return 0;
    }
    return head->next()->id;
}
ANK_FUNCTION_1(__test_monument_next_part);

// 1 if every part in the monument chain has the given building state (e.g. MOTHBALLED=7).
static int __test_monument_chain_all_state(int bid, int state) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    if (!head) {
        return 0;
    }
    for (building *part = head; part; part = part->has_next() ? part->next() : nullptr) {
        if ((int)part->state != state) {
            return 0;
        }
    }
    return 1;
}
ANK_FUNCTION_2(__test_monument_chain_all_state);

// Deliver resource loads into a monument (updates resources_pct like cart delivery).
// amount is resource units (same as deliver_resource); returns false if full / not a monument.
static bool __test_monument_add_resource(int bid, int resource, int amount) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    if (!mm || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return false;
    }
    return mm->deliver_resource(static_cast<e_resource>(resource), amount);
}
ANK_FUNCTION_3(__test_monument_add_resource);

// Current delivery progress for a resource on the monument (0..100+).
static int __test_monument_resource_pct(int bid, int resource) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto mm = head ? head->dcast_monument() : nullptr;
    if (!mm || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return -1;
    }
    return mm->runtime_data().resources_pct[resource];
}
ANK_FUNCTION_2(__test_monument_resource_pct);

static int __test_royal_tomb_lamp_stock(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *tomb = head ? head->dcast_royal_tomb() : nullptr;
    return tomb ? tomb->lamp_stock() : -1;
}
ANK_FUNCTION_1(__test_royal_tomb_lamp_stock);

static int __test_royal_tomb_lamp_stock_room(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *tomb = head ? head->dcast_royal_tomb() : nullptr;
    return tomb ? tomb->lamp_stock_room() : -1;
}
ANK_FUNCTION_1(__test_royal_tomb_lamp_stock_room);

// Attach a living guild walker to a royal tomb worker slot (bypasses pathing).
// Returns figure id, or 0 on failure.
static int __test_royal_tomb_attach_worker(int bid, int figure_type) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *tomb = head ? head->dcast_royal_tomb() : nullptr;
    if (!tomb || figure_type <= 0) {
        return 0;
    }
    if (!tomb->need_workers()) {
        return 0;
    }

    const tile2i at = tomb->access_point();
    figure *f = figure_create((e_figure_type)figure_type, at, DIR_0_TOP_RIGHT);
    if (!f || !f->id || !f->is_alive()) {
        return 0;
    }
    if (figure_type == FIGURE_STONEMASON) {
        f->action_state = FIGURE_ACTION_14_MASON_WORK_GROUND;
    } else if (figure_type == FIGURE_TOMB_ARTISAN) {
        f->action_state = ACTION_14_TOMB_ARTISAN_WORK;
        if (auto *impl = static_cast<figure_tomb_artisan *>(f->dcast())) {
            impl->runtime_data().destination_bid = head->id;
        }
    }
    f->set_destination(head);
    f->destination_tile = at;
    tomb->add_workers(f->id);
    return f->id;
}
ANK_FUNCTION_2(__test_royal_tomb_attach_worker);

// Call building_impl::update_day() (e.g. pyramid phase advance / congrats).
static void __test_building_update_day(int bid) {
    building *b = building_get(bid);
    auto *impl = b ? b->dcast() : nullptr;
    if (!impl) {
        return;
    }
    impl->update_day();
}
ANK_FUNCTION_1(__test_building_update_day);

// Minimum map_monuments progress across the monument chain (all parts).
static int __test_monument_min_progress(int bid) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    if (!head || !head->dcast_monument()) {
        return -1;
    }
    // map_grid_get_tiles(head) already walks the whole part chain — do not
    // nest another per-part walk (that re-counts the same tiles).
    grid_tiles tiles = map_grid_get_tiles(head, 0);
    if (tiles.empty()) {
        return -1;
    }
    int min_p = 200;
    for (auto &t : tiles) {
        min_p = std::min(min_p, (int)map_monuments_get_progress(t));
    }
    return min_p;
}
ANK_FUNCTION_1(__test_monument_min_progress);

// Override tile progress after set_phase (which fills 200). Mid-progress keeps
// update_day from advancing the phase across save/load day ticks.
static void __test_monument_set_all_progress(int bid, int progress) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    if (!head || !head->dcast_monument()) {
        return;
    }
    const uint32_t v = (uint32_t)std::clamp(progress, 0, 200);
    grid_tiles tiles = map_grid_get_tiles(head, 0);
    for (auto &t : tiles) {
        map_monuments_set_progress(t, v);
    }
}
ANK_FUNCTION_2(__test_monument_set_all_progress);

// Force-stock a storage yard (bypasses accepting/getting rules). Yard must already exist.
// Force-remove from a storage yard. Returns true when the resource is fully gone.
static bool __test_storage_yard_remove_resource(int bid, int resource, int amount) {
    building *b = building_get(bid);
    auto *yard = b ? b->dcast_storage_yard() : nullptr;
    if (!yard || !b->is_valid() || amount <= 0) {
        return false;
    }
    yard->remove_resource((e_resource)resource, amount);
    return yard->amount((e_resource)resource) <= 0;
}
ANK_FUNCTION_3(__test_storage_yard_remove_resource);

static bool __test_storage_yard_add_resource(int bid, int resource, int amount) {
    building *b = building_get(bid);
    auto *yard = b ? b->dcast_storage_yard() : nullptr;
    if (!yard || !b->is_valid() || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return false;
    }
    return yard->add_resource(static_cast<e_resource>(resource), amount, /*force*/true) >= 0;
}
ANK_FUNCTION_3(__test_storage_yard_add_resource);

// Returns resource id if this yard would dispatch a monument sled task, else 0.
// Used to assert stockpile blocks SY→monument delivery without waiting for spawn.
storage_worker_task building_storageyard_deliver_to_monuments(building *b);
static int __test_storageyard_monument_task_resource(int yard_bid) {
    building *b = building_get(yard_bid);
    if (!b || !b->dcast_storage_yard()) {
        return 0;
    }
    storage_worker_task task = building_storageyard_deliver_to_monuments(b);
    if (task.result != STORAGEYARD_TASK_MONUMENT || task.resource <= RESOURCE_NONE) {
        return 0;
    }
    return (int)task.resource;
}
ANK_FUNCTION_1(__test_storageyard_monument_task_resource);

static int __test_yards_stored(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_city.resource.yards_stored(static_cast<e_resource>(resource));
}
ANK_FUNCTION_1(__test_yards_stored);

static int __test_yards_stored_staffed(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_city.resource.yards_stored_staffed(static_cast<e_resource>(resource));
}
ANK_FUNCTION_1(__test_yards_stored_staffed);

static void __test_burial_provisions_clear() {
    for (int r = 0; r < RESOURCES_MAX; r++) {
        g_scenario.monuments.burial_provisions[r].required = 0;
        g_scenario.monuments.burial_provisions[r].dispatched = 0;
    }
    buildings_valid_do([](building &b) {
        auto *m = b.dcast_monument();
        if (!m || !b.is_main()) {
            return;
        }
        auto &d = m->runtime_data();
        memset(d.burial_stock, 0, sizeof(d.burial_stock));
    });
}
ANK_FUNCTION(__test_burial_provisions_clear);

static bool __test_burial_provisions_set(int resource, int required) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || required < 0) {
        return false;
    }
    g_scenario.monuments.burial_provisions[resource].required = required;
    g_scenario.monuments.burial_provisions[resource].dispatched = 0;
    return true;
}
ANK_FUNCTION_2(__test_burial_provisions_set);

static int __test_monument_burial_stock(int bid, int resource) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *m = head ? head->dcast_monument() : nullptr;
    if (!m || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return -1;
    }
    return m->burial_stock((e_resource)resource);
}
ANK_FUNCTION_2(__test_monument_burial_stock);

static int __test_monument_add_burial_stock(int bid, int resource, int amount) {
    building *b = building_get(bid);
    building *head = b ? b->main() : nullptr;
    auto *m = head ? head->dcast_monument() : nullptr;
    if (!m || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return 0;
    }
    const int added = m->add_burial_stock((e_resource)resource, amount);
    g_scenario.monuments.burial_provisions[resource].dispatched += added;
    return added;
}
ANK_FUNCTION_3(__test_monument_add_burial_stock);

static int __test_building_current_image(int bid) {
    building *b = building_get(bid);
    auto m = b ? b->dcast_monument() : nullptr;
    if (!m) {
        return 0;
    }
    const int id = m->building_image_get();
    return (id > 0 && image_get(id)) ? id : 0;
}
ANK_FUNCTION_1(__test_building_current_image);

static void __test_camera_center_building(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building *head = b->main();
    tile2i c = head->tile.shifted(head->size / 2, head->size / 2);
    int height_layers = 0;
    if (auto *pyr = head->dcast_pyramid()) {
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
    } else if (auto *m = head->dcast_monument()) {
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

    logs::info("[test-camera] tile=%d,%d cam=%d,%d zoom=%.0f layers=%d collapsed=%d vp=%d,%d",
        c.x(), c.y(),
        g_camera.camera_position.x, g_camera.camera_position.y,
        g_zoom.get_percentage(),
        height_layers,
        (int)g_camera.sidebar_collapsed,
        g_camera.size_pixels.x, g_camera.size_pixels.y);
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
// crashed in config::refresh / UI archive load (stackoverflow → fatal exit).
static bool __test_js_hotreload_handlers_stack_ok(int iterations) {
    js_State *J = js_vm_state();
    if (!J || iterations < 1) {
        return false;
    }

    const int baseline = js_gettop(J);
    for (int i = 0; i < iterations; ++i) {
        js_register_game_handlers({});
    }
    const int after = js_gettop(J);
    logs::info("[test-marker] hotreload_handlers_stack baseline=%d after=%d iterations=%d",
               baseline, after, iterations);
    if (after != baseline) {
        logs::info("[hotreload] handlers stack leak delta=%d", after - baseline);
        return false;
    }
    return true;
}
ANK_FUNCTION_1(__test_js_hotreload_handlers_stack_ok);

static bool __test_js_hotreload_file_stack_ok(pcstr path, int iterations) {
    js_State *J = js_vm_state();
    if (!J || !path || !*path || iterations < 1) {
        return false;
    }

    const int baseline = js_gettop(J);
    for (int i = 0; i < iterations; ++i) {
        js_vm_reload_file(path);
        js_vm_sync({});
    }
    const int after = js_gettop(J);
    logs::info("[test-marker] hotreload_file_stack path=%s baseline=%d after=%d iterations=%d",
               path, baseline, after, iterations);
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

#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_trader_ship.h"
#include "empire/trader_handler.h"
#include "empire/empire_traders.h"
#include "game/game_config.h"

static int __test_trader_capacity(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return -1;
    }
    if (auto *caravan = f->dcast<figure_trade_caravan>()) {
        return caravan->max_capacity();
    }
    if (auto *ship = f->dcast<figure_trade_ship>()) {
        return ship->max_capacity();
    }
    return -1;
}
ANK_FUNCTION_1(__test_trader_capacity);

static int __test_trader_static_max_capacity(int type) {
    if (type == FIGURE_TRADE_CARAVAN) {
        const auto &p = (const figure_trade_caravan::static_params &)figure_static_params::get(FIGURE_TRADE_CARAVAN);
        return p.max_capacity;
    }
    if (type == FIGURE_TRADE_SHIP) {
        const auto &p = (const figure_trade_ship::static_params &)figure_static_params::get(FIGURE_TRADE_SHIP);
        return p.max_capacity;
    }
    return -1;
}
ANK_FUNCTION_1(__test_trader_static_max_capacity);

static int __test_trader_static_capacity_random(int type) {
    if (type != FIGURE_TRADE_CARAVAN) {
        return -1;
    }
    const auto &p = (const figure_trade_caravan::static_params &)figure_static_params::get(FIGURE_TRADE_CARAVAN);
    return p.capacity_random;
}
ANK_FUNCTION_1(__test_trader_static_capacity_random);

static void __test_trader_set_bought(int fid, int amount) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    if (auto *caravan = f->dcast<figure_trade_caravan>()) {
        caravan->runtime_data().amount_bought = (uint16_t)std::max(0, amount);
        return;
    }
    if (auto *ship = f->dcast<figure_trade_ship>()) {
        ship->runtime_data().amount_bought = (uint16_t)std::max(0, amount);
    }
}
ANK_FUNCTION_2(__test_trader_set_bought);

static int __test_trader_buy_under_capacity(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return -1;
    }
    if (auto *caravan = f->dcast<figure_trade_caravan>()) {
        return caravan->total_bought() < caravan->max_capacity() ? 1 : 0;
    }
    if (auto *ship = f->dcast<figure_trade_ship>()) {
        return ship->total_bought() < ship->max_capacity() ? 1 : 0;
    }
    return -1;
}
ANK_FUNCTION_1(__test_trader_buy_under_capacity);

static int __test_empire_trader_has_traded_max(int bought, int sold, int capacity) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto &t = g_empire_traders.traders[h.handle];
    t.bought_amount = (uint16_t)std::max(0, bought);
    t.sold_amount = (uint16_t)std::max(0, sold);
    const int result = h.has_traded_max(capacity) ? 1 : 0;
    t.is_active = false;
    return result;
}
ANK_FUNCTION_3(__test_empire_trader_has_traded_max);

static int __test_empire_trader_per_good_cap() {
    return empire_trader_per_good_cap();
}
ANK_FUNCTION(__test_empire_trader_per_good_cap);

static int __test_empire_trader_ignore_total_bag() {
    return empire_trader_ignore_total_bag() ? 1 : 0;
}
ANK_FUNCTION(__test_empire_trader_ignore_total_bag);

// Sets bought_resources[resource]=amount (and totals), returns buy_full(resource) as 0/1.
static int __test_empire_trader_buy_full_at(int resource, int amount) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto &t = g_empire_traders.traders[h.handle];
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    t.bought_resources[r] = (uint16_t)std::max(0, amount);
    t.bought_amount = t.bought_resources[r];
    const int result = h.buy_full(r) ? 1 : 0;
    t.is_active = false;
    return result;
}
ANK_FUNCTION_2(__test_empire_trader_buy_full_at);

// pottery_amt / beer_amt on one trader; returns buy_full(pottery)*10 + buy_full(beer).
static int __test_empire_trader_two_goods_buy_full(int pottery_amt, int beer_amt) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto &t = g_empire_traders.traders[h.handle];
    t.bought_resources[RESOURCE_POTTERY] = (uint16_t)std::max(0, pottery_amt);
    t.bought_resources[RESOURCE_BEER] = (uint16_t)std::max(0, beer_amt);
    t.bought_amount = (uint16_t)(t.bought_resources[RESOURCE_POTTERY] + t.bought_resources[RESOURCE_BEER]);
    const int result = (h.buy_full(RESOURCE_POTTERY) ? 10 : 0) + (h.buy_full(RESOURCE_BEER) ? 1 : 0);
    t.is_active = false;
    return result;
}
ANK_FUNCTION_2(__test_empire_trader_two_goods_buy_full);

static int __test_empire_trader_buy_room_at(int resource, int amount) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto &t = g_empire_traders.traders[h.handle];
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    t.bought_resources[r] = (uint16_t)std::max(0, amount);
    const int result = h.buy_room(r);
    t.is_active = false;
    return result;
}
ANK_FUNCTION_2(__test_empire_trader_buy_room_at);

// Attach FIGURE_MARKET_BUYER to a bazaar slot and run before_action.
// Returns figure id if still alive, else 0.
static int __test_bazaar_attach_buyer(int bid, int slot, int collecting_item) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    figure *f = figure_create(FIGURE_MARKET_BUYER, bazaar->tile(), DIR_0_TOP_RIGHT);
    if (!f || !f->is_alive()) {
        return 0;
    }
    f->set_home(bid);
    f->collecting_item_id = (uint8_t)std::clamp(collecting_item, 0, INVENTORY_MAX - 1);
    f->advance_action(ACTION_145_MARKET_BUYER_GOING_TO_STORAGE);
    bazaar->base.set_figure(slot, f->id);
    if (auto *buyer = f->dcast_market_buyer()) {
        buyer->figure_before_action();
    }
    return f->is_alive() ? f->id : 0;
}
ANK_FUNCTION_3(__test_bazaar_attach_buyer);

static int __test_bazaar_max_buyers_param() {
    const auto &p = (const building_bazaar::static_params &)building_static_params::get(BUILDING_BAZAAR);
    return p.max_buyers;
}
ANK_FUNCTION(__test_bazaar_max_buyers_param);

static int __test_bazaar_food_variety_target_param() {
    const auto &p = (const building_bazaar::static_params &)building_static_params::get(BUILDING_BAZAAR);
    return p.food_variety_target;
}
ANK_FUNCTION(__test_bazaar_food_variety_target_param);

static int __test_bazaar_count_buyers(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->count_market_buyers() : -1;
}
ANK_FUNCTION_1(__test_bazaar_count_buyers);

static int __test_bazaar_on_buyer_returned(int fid) {
    figure *f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER) {
        return -1;
    }
    if (auto *buyer = f->dcast_market_buyer()) {
        buyer->apply_return_home_spawn_cooldown();
        building *h = f->home();
        return h ? h->figure_spawn_delay : -1;
    }
    return -1;
}
ANK_FUNCTION_1(__test_bazaar_on_buyer_returned);

static int __test_bazaar_pick_next_inventory(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building *dest = bazaar->pick_next_buyer_destination();
    if (!dest || !dest->id) {
        return -1;
    }
    return bazaar->runtime_data().fetch_inventory_id;
}
ANK_FUNCTION_1(__test_bazaar_pick_next_inventory);

static int __test_bazaar_get_storage_inventory(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building *dest = bazaar->get_storage_destination();
    if (!dest || !dest->id) {
        return -1;
    }
    return bazaar->runtime_data().fetch_inventory_id;
}
ANK_FUNCTION_1(__test_bazaar_get_storage_inventory);

static int __test_bazaar_get_storage_destination_type(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building *dest = bazaar->get_storage_destination();
    if (!dest || !dest->id) {
        return 0;
    }
    return dest->type;
}
ANK_FUNCTION_1(__test_bazaar_get_storage_destination_type);

static int __test_bazaar_get_storage_destination_id(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building *dest = bazaar->get_storage_destination();
    return (dest && dest->id) ? dest->id : 0;
}
ANK_FUNCTION_1(__test_bazaar_get_storage_destination_id);

static int __test_bazaar_set_desired_variety(int bid, int value) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    bazaar->set_desired_variety((uint8_t)value);
    return bazaar->desired_variety();
}
ANK_FUNCTION_2(__test_bazaar_set_desired_variety);

static int __test_bazaar_set_min_variety(int bid, int value) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    bazaar->set_min_variety((uint8_t)value);
    return bazaar->min_variety();
}
ANK_FUNCTION_2(__test_bazaar_set_min_variety);

static int __test_bazaar_desired_variety(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->desired_variety() : -1;
}
ANK_FUNCTION_1(__test_bazaar_desired_variety);

static int __test_bazaar_min_variety(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->min_variety() : -1;
}
ANK_FUNCTION_1(__test_bazaar_min_variety);

static int __test_bazaar_waiting_for_mill(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? (bazaar->waiting_for_mill_variety() ? 1 : 0) : -1;
}
ANK_FUNCTION_1(__test_bazaar_waiting_for_mill);

static int __test_market_buyer_take_food(int fid, int market_id, int storage_id) {
    figure *f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER) {
        return -1;
    }
    auto *buyer = f->dcast_market_buyer();
    building *market = building_get(market_id);
    building *storage = building_get(storage_id);
    if (!buyer || !market || !storage) {
        return -1;
    }
    return buyer->take_food_from_storage(market, storage);
}
ANK_FUNCTION_3(__test_market_buyer_take_food);

static int __test_bazaar_set_inventory(int bid, int inv, int amount) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar || inv < 0 || inv >= INVENTORY_MAX) {
        return 0;
    }
    bazaar->runtime_data().inventory[inv].value = (uint16_t)std::max(0, amount);
    return 1;
}
ANK_FUNCTION_3(__test_bazaar_set_inventory);

static int __test_bazaar_get_inventory(int bid, int inv) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar || inv < 0 || inv >= INVENTORY_MAX) {
        return -1;
    }
    return bazaar->runtime_data().inventory[inv].value;
}
ANK_FUNCTION_2(__test_bazaar_get_inventory);

static int __test_bazaar_food_types(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->food_types_in_inventory() : -1;
}
ANK_FUNCTION_1(__test_bazaar_food_types);

static void __test_bazaar_set_good_demands(int bid, int pottery, int luxury, int linen, int beer) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return;
    }
    auto &d = bazaar->runtime_data();
    d.pottery_demand = (short)pottery;
    d.luxurygoods_demand = (short)luxury;
    d.linen_demand = (short)linen;
    d.beer_demand = (short)beer;
}
ANK_FUNCTION_5(__test_bazaar_set_good_demands);

static int __test_bazaar_link_storage(int bazaar_id, int storage_id) {
    building *bazaar = building_get(bazaar_id);
    building *storage = building_get(storage_id);
    if (!bazaar || !storage || !bazaar->dcast_bazaar() || !storage->dcast_storage()) {
        return 0;
    }
    if (bazaar->road_network_id <= 0) {
        bazaar->road_network_id = 1;
    }
    if (bazaar->distance_from_entry <= 0) {
        bazaar->distance_from_entry = 1;
    }
    bazaar->has_road_access = true;
    storage->road_network_id = bazaar->road_network_id;
    storage->distance_from_entry = bazaar->distance_from_entry;
    storage->has_road_access = true;
    return 1;
}
ANK_FUNCTION_2(__test_bazaar_link_storage);

static int __test_bazaar_reclaim_slot(int bid, int slot) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    bazaar->reclaim_inactive_buyer_slot((e_building_slot)slot);
    return bazaar->base.get_figure_id(slot);
}
ANK_FUNCTION_2(__test_bazaar_reclaim_slot);

static int __test_bazaar_busy_excludes(int bid, int inv) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar || inv < 0 || inv >= INVENTORY_MAX) {
        return -1;
    }
    bool exclude[INVENTORY_MAX];
    bool has_food = false;
    bool has_good = false;
    bazaar->collect_buyer_busy_state(exclude, &has_food, &has_good);
    return exclude[inv] ? 1 : 0;
}
ANK_FUNCTION_2(__test_bazaar_busy_excludes);

static int __test_bazaar_pottery_demand(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->runtime_data().pottery_demand : -1;
}
ANK_FUNCTION_1(__test_bazaar_pottery_demand);

static int __test_bazaar_slot_figure(int bid, int slot) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    return bazaar->base.get_figure_id(slot);
}
ANK_FUNCTION_2(__test_bazaar_slot_figure);

static int __test_bazaar_force_spawn(int bid) {
    auto *bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    building &b = bazaar->base;
    b.num_workers = std::max(1, (int)b.max_workers);
    b.has_road_access = true;
    if (b.road_network_id <= 0) {
        b.road_network_id = 1;
    }
    if (b.distance_from_entry <= 0) {
        b.distance_from_entry = 1;
    }
    b.figure_spawn_delay = 0;
    bazaar->spawn_figure();
    return 1;
}
ANK_FUNCTION_1(__test_bazaar_force_spawn);

static int __test_granary_add_allowed_food(int bid, int food_index, int amount) {
    building *b = building_get(bid);
    auto *granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || food_index < 0 || food_index >= INVENTORY_MAX_FOOD || amount <= 0) {
        return 0;
    }
    e_resource res = g_city.allowed_foods(food_index);
    if (res == RESOURCE_NONE) {
        return 0;
    }
    return granary->add_resource(res, amount, /*force*/true) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_granary_add_allowed_food);

static int __test_granary_add_resource(int bid, int resource, int amount) {
    building *b = building_get(bid);
    auto *granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || amount <= 0) {
        return 0;
    }
    return granary->add_resource((e_resource)resource, amount, /*force*/true) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_granary_add_resource);

static int __test_granary_set_resource(int bid, int resource, int amount) {
    building *b = building_get(bid);
    auto *granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || amount < 0 || !resource_is_food((e_resource)resource)) {
        return 0;
    }
    auto &stored = granary->runtime_data().resource_stored;
    const e_resource res = (e_resource)resource;
    const int old_amount = stored[res];
    stored[res] = static_cast<short>(amount);
    stored[RESOURCE_NONE] = static_cast<short>(stored[RESOURCE_NONE] + old_amount - amount);
    if (stored[RESOURCE_NONE] < 0) {
        stored[RESOURCE_NONE] = 0;
    }
    return 1;
}
ANK_FUNCTION_3(__test_granary_set_resource);

static int __test_granary_clear_allowed_food(int bid, int food_index) {
    building *b = building_get(bid);
    auto *granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || food_index < 0 || food_index >= INVENTORY_MAX_FOOD) {
        return 0;
    }
    e_resource res = g_city.allowed_foods(food_index);
    if (res == RESOURCE_NONE) {
        return 0;
    }
    granary->runtime_data().resource_stored[res] = 0;
    return 1;
}
ANK_FUNCTION_2(__test_granary_clear_allowed_food);

static int __test_city_allowed_food(int food_index) {
    if (food_index < 0 || food_index >= INVENTORY_MAX_FOOD) {
        return 0;
    }
    return (int)g_city.allowed_foods(food_index);
}
ANK_FUNCTION_1(__test_city_allowed_food);

static int __test_set_allowed_food(int food_index, int resource) {
    if (food_index < 0 || food_index >= INVENTORY_MAX_FOOD) {
        return 0;
    }
    g_city.set_allowed_food(food_index, (e_resource)resource);
    // Refresh bazaar slot types so accept toggles / display match the new foods.
    buildings_valid_do([](building &b) {
        if (auto *bazaar = b.dcast_bazaar()) {
            bazaar->on_post_load();
        }
    }, BUILDING_BAZAAR);
    return 1;
}
ANK_FUNCTION_2(__test_set_allowed_food);

static int __test_city_recalc_granary_stored(int resource) {
    g_city.resource.calculate_available_food();
    return (int)g_city.resource.granary_stored((e_resource)resource);
}
ANK_FUNCTION_1(__test_city_recalc_granary_stored);

static int __test_food_mill_add_resource(int bid, int resource, int amount) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid() || amount <= 0) {
        return 0;
    }
    return mill->add_resource((e_resource)resource, amount, /*force*/true) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_food_mill_add_resource);

static int __test_food_mill_amount(int bid, int resource) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->amount((e_resource)resource);
}
ANK_FUNCTION_2(__test_food_mill_amount);

static int __test_food_mill_variety(int bid) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->food_variety();
}
ANK_FUNCTION_1(__test_food_mill_variety);

static int __test_food_mill_total_stored(int bid) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->total_stored();
}
ANK_FUNCTION_1(__test_food_mill_total_stored);

static int __test_food_mill_freespace(int bid) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->freespace();
}
ANK_FUNCTION_1(__test_food_mill_freespace);

static int __test_food_mill_set_getting(int bid, int resource) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (mill->is_getting((e_resource)resource)) {
            return 1;
        }
        building_storage_cycle_resource_state(mill->storage_id(), resource, false);
    }
    return mill->is_getting((e_resource)resource) ? 1 : 0;
}
ANK_FUNCTION_2(__test_food_mill_set_getting);

static int __test_food_mill_find_getting_source(int bid) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return 0;
    }
    g_city.resource.calculate_stocks();
    return mill->find_storage_for_getting().building_id;
}
ANK_FUNCTION_1(__test_food_mill_find_getting_source);

static int __test_food_mill_spawn_figure(int bid) {
    building *b = building_get(bid);
    auto *mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    b->has_road_access = true;
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    g_city.resource.calculate_stocks();
    const bool before = mill->has_figure_of_type(0, FIGURE_STORAGEYARD_CART);
    mill->spawn_figure();
    const bool after = mill->has_figure_of_type(0, FIGURE_STORAGEYARD_CART);
    if (before) {
        return 0;
    }
    return after ? 1 : 0;
}
ANK_FUNCTION_1(__test_food_mill_spawn_figure);

static int __test_resolve_building_road_access(int type, int x, int y, int size, int orientation) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    tile2i tile(x, y);
    if (!tile.valid()) {
        return 0;
    }
    building_road_access_result r = resolve_building_road_access(tile, (e_building_type)type, size, orientation, 0,
        road_access_resolve_mode::Preview, false);
    return r.valid ? 1 : 0;
}
ANK_FUNCTION_5(__test_resolve_building_road_access);

static int __test_building_road_access_tile(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    building *m = b->main();
    if (!m || !m->road_access.valid()) {
        return -1;
    }
    return m->road_access.grid_offset();
}
ANK_FUNCTION_1(__test_building_road_access_tile);

static void __test_building_road_access_set_stale(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building *m = b->main();
    if (!m) {
        return;
    }
    m->has_road_access = true;
    m->road_network_id = 1;
    m->distance_from_entry = 1;
    m->road_access = m->tile;
}
ANK_FUNCTION_1(__test_building_road_access_set_stale);

static int __test_building_road_access_fields_cleared(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building *m = b->main();
    if (!m) {
        return 0;
    }
    return (!m->has_road_access && m->road_network_id == 0 && m->distance_from_entry == 0
            && !m->road_access.valid())
        ? 1
        : 0;
}
ANK_FUNCTION_1(__test_building_road_access_fields_cleared);

static int __test_building_road_access_match_preview(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building *m = b->main();
    if (!m) {
        return 0;
    }
    int variant = 0;
    if (building_static_params::get(m->type).flags.is_temple_complex) {
        auto complex = m->dcast_temple_complex();
        variant = complex ? complex->runtime_data().variant : 0;
    }
    const bool assume = building_type_ghost_assume_occupied(m->type);
    building_road_ports stored = building_road_ports_stored(*m);
    building_road_ports preview = building_road_ports_preview(m->tile, m->type, m->size, m->orientation, variant, assume);
    if (!stored.valid || !preview.valid) {
        return 0;
    }
    return (stored.tile == preview.tile) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_road_access_match_preview);

static void __test_check_kingdome_access() {
    g_city.maintenance.check_kingdome_access();
}
ANK_FUNCTION(__test_check_kingdome_access);

static void __test_update_road_network() {
    g_city.map.update_road_network();
}
ANK_FUNCTION(__test_update_road_network);

static void __test_update_farms() {
    building_industry_update_farms();
}
ANK_FUNCTION(__test_update_farms);

static int __test_building_type_ghost_road_access(int type) {
    return building_type_ghost_road_access((e_building_type)type) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_type_ghost_road_access);

static int __test_building_type_ghost_assume_occupied(int type) {
    return building_type_ghost_assume_occupied((e_building_type)type) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_type_ghost_assume_occupied);

static int __test_building_type_hover_road_access(int type) {
    return building_type_hover_road_access((e_building_type)type) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_type_hover_road_access);

static void __test_link_producer_for_delivery(int producer_id, int storage_id) {
    building *producer = building_get(producer_id);
    building *storage = building_get(storage_id);
    if (!producer || !storage) {
        return;
    }

    producer->has_road_access = true;
    if (!producer->road_access.valid()) {
        producer->road_access = producer->tile;
    }
    if (producer->distance_from_entry <= 0) {
        producer->distance_from_entry = 1;
    }

    // Match map network under access tile when present (predict prefers map net).
    int net = map_road_network_get(producer->road_access);
    if (net <= 0) {
        net = producer->road_network_id > 0 ? producer->road_network_id : 1;
    }
    producer->road_network_id = net;

    for (building *part = storage->main(); part;) {
        part->road_network_id = net;
        part->distance_from_entry = producer->distance_from_entry;
        part->has_road_access = true;
        if (!part->road_access.valid()) {
            part->road_access = part->tile;
        }
        if (part->max_workers > 0) {
            part->num_workers = part->max_workers;
        } else {
            part->num_workers = std::max(1, (int)part->num_workers);
        }
        if (!part->has_next()) {
            break;
        }
        part = part->next();
    }
}
ANK_FUNCTION_2(__test_link_producer_for_delivery);

static int __test_predict_delivery(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    delivery_path_query q = building_predict_delivery(*b);
    if (!q.to) {
        return 0;
    }
    building *dest = building_get(q.to);
    return dest && dest->is_valid() ? dest->main()->id : q.to;
}
ANK_FUNCTION_1(__test_predict_delivery);

static int __test_predict_delivery_kind(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    delivery_path_query q = building_predict_delivery(*b);
    return (int)q.kind;
}
ANK_FUNCTION_1(__test_predict_delivery_kind);

static int __test_predict_delivery_reason(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    delivery_path_query q = building_predict_delivery(*b);
    return (int)q.reason;
}
ANK_FUNCTION_1(__test_predict_delivery_reason);

static void __test_building_set_workers(int bid, int workers) {
    building *b = building_get(bid);
    if (!b) {
        return;
    }
    building *m = b->main();
    if (!m) {
        return;
    }
    m->num_workers = std::max(0, workers);
    for (building *part = m; part;) {
        part->num_workers = m->num_workers;
        if (!part->has_next()) {
            break;
        }
        part = part->next();
    }
}
ANK_FUNCTION_2(__test_building_set_workers);

static void __test_storage_toggle_empty_all(int bid) {
    building *b = building_get(bid);
    if (!b) {
        return;
    }
    building *m = b->main();
    if (!m || m->storage_id <= 0) {
        return;
    }
    building_storage_toggle_empty_all(m->storage_id);
}
ANK_FUNCTION_1(__test_storage_toggle_empty_all);

static int __test_building_shows_delivery_paths(int bid) {
    building *b = building_get(bid);
    if (!b) {
        return 0;
    }
    return building_shows_delivery_paths(*b) ? 1 : 0;
}
ANK_FUNCTION_1(__test_building_shows_delivery_paths);

static int __test_recorded_path_acquire() {
    return g_recorded_paths.acquire();
}
ANK_FUNCTION(__test_recorded_path_acquire);

static void __test_recorded_path_append(int path_id, int x, int y) {
    g_recorded_paths.append(path_id, MAP_OFFSET(x, y));
}
ANK_FUNCTION_3(__test_recorded_path_append);

static void __test_building_push_recorded_path(int bid, int path_id) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building *main = b->main();
    g_recorded_paths.building_push(main ? main->id : bid, path_id);
}
ANK_FUNCTION_2(__test_building_push_recorded_path);

static int __test_building_recorded_path_at(int bid, int index) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    building *main = b->main();
    return g_recorded_paths.building_path_at(main ? main->id : bid, index);
}
ANK_FUNCTION_2(__test_building_recorded_path_at);

static int __test_recorded_path_tile_count(int path_id) {
    return (int)g_recorded_paths.tiles(path_id).size();
}
ANK_FUNCTION_1(__test_recorded_path_tile_count);

static int __test_recorded_path_used(int path_id) {
    if (path_id <= 0 || path_id >= RECORDED_PATH_POOL_SIZE) {
        return 0;
    }
    return g_recorded_paths.slots[path_id].used ? 1 : 0;
}
ANK_FUNCTION_1(__test_recorded_path_used);

ANK_DECLARE_JSFUNCTION_ITERATOR(register_test_js_functions);
inline void register_test_js_functions(js_State *J) {
}
