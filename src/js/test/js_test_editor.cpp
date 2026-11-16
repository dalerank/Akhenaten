#include "js/test/js_test_common.h"

#include "widget/widget_city.h"
#include "grid/image.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"

#include "building/building_delivery_path.h"
#include "content/vfs.h"
#include "core/log.h"
#include "figure/formation.h"
#include "game/file_editor.h"
#include "game/game.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/editor.h"
#include "scenario/editor_map_meta.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/types.h"

// ED4a: editor request slots ? EVENT_TYPE_REQUEST (tag 8000+slot).
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
    if (out.year != 2 || out.resource != RESOURCE_CLAY || out.amount != 10 || out.deadline_years != 1
        || out.kingdom != 8) {
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
    if (slot3.year != 5 || slot3.resource != RESOURCE_POTTERY || slot3.amount != 20 || slot3.deadline_years != 2
        || slot3.kingdom != 4) {
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

    const char* map_path = "Maps/_editor_meta_rt.map";
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
    if (
      g_scenario.price_changes[0].resource != RESOURCE_NONE || g_scenario.demand_changes[0].resource != RESOURCE_NONE) {
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
    const invasion_t& out_inv0 = g_scenario.invasions[0];
    const invasion_t& out_inv1 = g_scenario.invasions[1];
    const price_change_t& out_price = g_scenario.price_changes[0];
    const demand_change_t& out_demand = g_scenario.demand_changes[0];
    const bool ok = out0.year == 3 && out0.resource == RESOURCE_CLAY && out0.amount == 12 && out0.deadline_years == 2
                    && out0.kingdom == 5 && out3.year == 7 && out3.resource == RESOURCE_POTTERY && out3.amount == 4
                    && out3.deadline_years == 1 && out3.kingdom == 1 && out_inv0.year == 2
                    && out_inv0.type == INVASION_TYPE_ENEMY_ARMY && out_inv0.amount == 16 && out_inv0.from == 3
                    && out_inv0.attack_type == FORMATION_ATTACK_TROOPS && out_inv1.year == 5
                    && out_inv1.type == INVASION_TYPE_LOCAL_UPRISING && out_inv1.amount == 8 && out_inv1.from == 1
                    && out_inv1.attack_type == FORMATION_ATTACK_FOOD_CHAIN && out_price.year == 4
                    && out_price.resource == RESOURCE_CLAY && out_price.amount == 10 && out_price.is_rise == 1
                    && out_demand.year == 6 && out_demand.resource == RESOURCE_POTTERY && out_demand.route_id == 2
                    && out_demand.is_rise == 0;
    if (!ok) {
        logs::info(
          "[test:172] step=slot_mismatch s0=%d/%d/%d s3=%d/%d/%d inv0=%d/%d/%d inv1=%d/%d/%d p=%d/%d/%d d=%d/%d/%d",
          out0.year, (int)out0.resource, out0.amount, out3.year, (int)out3.resource, out3.amount, out_inv0.year,
          out_inv0.type, out_inv0.amount, out_inv1.year, out_inv1.type, out_inv1.amount, out_price.year,
          (int)out_price.resource, out_price.amount, out_demand.year, (int)out_demand.resource, out_demand.route_id);
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

    const char* map_path = "Maps/_editor_inv_play.map";
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

    const invasion_t& got = g_scenario.invasions[0];
    // Custom maps often have no empire invasion path — init may no-op month assign.
    // Success = sidecar applied on play load (schedule present for scenario_invasion_process).
    const bool ok = got.year == 1 && got.type == INVASION_TYPE_ENEMY_ARMY && got.amount == 12 && got.from == 2
                    && got.attack_type == FORMATION_ATTACK_BEST_BUILDINGS;
    if (!ok) {
        logs::info("[test:173] step=mismatch year=%d type=%d amount=%d from=%d atk=%d", got.year, got.type, got.amount,
          got.from, (int)got.attack_type);
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

    const char* map_path = "Maps/_editor_trade_play.map";
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

    const price_change_t& got_p = g_scenario.price_changes[0];
    const demand_change_t& got_d = g_scenario.demand_changes[0];
    const bool ok = got_p.year == 3 && got_p.resource == RESOURCE_CLAY && got_p.amount == 7 && got_p.is_rise == 1
                    && got_d.year == 4 && got_d.resource == RESOURCE_POTTERY && got_d.route_id == 1
                    && got_d.is_rise == 0;
    if (!ok) {
        logs::info("[test:174] step=mismatch p=%d/%d/%d/%d d=%d/%d/%d/%d", got_p.year, (int)got_p.resource,
          got_p.amount, got_p.is_rise, got_d.year, (int)got_d.resource, got_d.route_id, got_d.is_rise);
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

    const char* map_path = "Maps/_editor_win_rt.map";
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
        logs::info("[test:175] step=map_mismatch c=%d p=%d pop=%d/%d tl=%d/%d", g_scenario.win_criteria.culture.goal,
          g_scenario.win_criteria.prosperity.goal, g_scenario.win_criteria.population.enabled,
          g_scenario.win_criteria.population.goal, g_scenario.win_criteria.time_limit.enabled,
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
        logs::info("[test:175] step=meta_mismatch c=%d pop=%d", g_scenario.win_criteria.culture.goal,
          g_scenario.win_criteria.population.goal);
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
        logs::info("[test:175] step=play_mismatch c=%d p=%d pop=%d tl=%d m25=%d", g_scenario.win_criteria.culture.goal,
          g_scenario.win_criteria.prosperity.goal, g_scenario.win_criteria.population.goal,
          g_scenario.win_criteria.time_limit.years, g_scenario.win_criteria.milestone25_year);
    }

    GamestateIO::delete_map("_editor_win_rt.map");
    return ok ? 1 : 0;
}
ANK_FUNCTION(__test_editor_win_criteria_meta);

// Procedural editor map from a fixed seed: medium landscape with water, a road and entry/exit points.
static bool editor_generated_map_valid(uint32_t seed, bool log_failure) {
    game_file_editor_generate_scenario_seeded(2, seed); // medium 80x80

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
    if (!ok && log_failure) {
        logs::info("[test:173] seed=%u water=%d road=%d meadow=%d trees=%d rocks=%d entry=%d,%d exit=%d,%d", seed,
          water, road, meadow, trees, rocks, g_scenario.entry_point.x(), g_scenario.entry_point.y(),
          g_scenario.exit_point.x(), g_scenario.exit_point.y());
    }
    return ok;
}

// Terrain hash of the current map, to check that a seed always gives the same map.
static int editor_map_terrain_hash() {
    uint32_t h = 2166136261u;
    for (int y = 0; y < g_scenario.map.height; y++) {
        for (int x = 0; x < g_scenario.map.width; x++) {
            h = (h ^ (uint32_t)map_terrain_get(MAP_OFFSET(x, y))) * 16777619u;
        }
    }
    return (int)(h & 0x7FFFFFFF);
}

int __test_editor_map_generate(int seed) {
    return editor_generated_map_valid((uint32_t)seed, true) ? editor_map_terrain_hash() : 0;
}
ANK_FUNCTION_1(__test_editor_map_generate);

// Number of seeds in [first, first + count) that give a map without water, road or entry/exit.
int __test_editor_map_generate_invalid_count(int first, int count) {
    int invalid = 0;
    for (int i = 0; i < count; i++) {
        invalid += editor_generated_map_valid((uint32_t)(first + i), true) ? 0 : 1;
    }
    return invalid;
}
ANK_FUNCTION_2(__test_editor_map_generate_invalid_count);

static int __test_pending_water_frames() {
    return g_screen_city.pending_water_frames();
}
ANK_FUNCTION(__test_pending_water_frames);

// Gives a tile the first water frame; returns its image id, or 0 without Pharaoh art.
static int __test_set_water_image(int x, int y) {
    const int image_id = image_id_from_group(GROUP_TERRAIN_WATER);
    if (image_id <= 0) {
        return 0;
    }
    map_image_set(tile2i(x, y), image_id);
    return image_id;
}
ANK_FUNCTION_2(__test_set_water_image);

static int __test_map_image_at(int x, int y) {
    return map_image_at(tile2i(x, y));
}
ANK_FUNCTION_2(__test_map_image_at);
