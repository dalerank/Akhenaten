#include "boilerplate_detail.h"

#include "building/building.h"
#include "building/construction/build_planner.h"
#include "building/building_storage.h"
#include "building/monuments.h"
#include "city/campaign_carry.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_recorded_paths.h"
#include "city/city_resource.h"
#include "city/coverage.h"
#include "city/map.h"
#include "content/vfs.h"
#include "core/buffer.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "empire/empire_traders.h"
#include "empire/trade_prices.h"
#include "empire/type.h"
#include "figure/enemy_army.h"
#include "figure/figure_names.h"
#include "figure/formation.h"
#include "figure/route.h"
#include "file_schemas.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/undo.h"
#include "grid/bridge_grid.h"
#include "grid/building.h"
#include "grid/canals.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/floodplain.h"
#include "grid/gardens.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/image_context.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/road_network.h"
#include "grid/soldier_strength.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/wall_material.h"
#include "io/chunk_serializer.h"
#include "io/io.h"
#include "js/js_game.h"
#include "scenario/distant_battle.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/scenario.h"
#include "game/mission.h"
#include "sound/sound_city.h"
#include "widget/widget_figure_follow.h"

#include <algorithm>
#include <cassert>

static buffer* version_probe_buf = new buffer(4);
const int GamestateLoadDetail::read_file_version(const char* filename, int offset) {
    version_probe_buf->clear();
    if (!io_read_file_part_into_buffer(filename, NOT_LOCALIZED, version_probe_buf, 4, offset + 4))
        return -1;
    return version_probe_buf->read_i32();
}

void GamestateLoadDetail::pre_load() { // do we NEED this...?
    OZZY_PROFILER_FUNCTION();
    g_scenario.campaign_scenario_id = -1;
    grid_xx::init_all_grids();

    // clear data
    g_city.victory.reset();
    g_city.migration.reset();
    g_city_planner.reset();
    g_city.init();
    g_message_manager.init();
    game.init_state();
    game.animation_timers_init();
    sound_city_init();
    building_clear_all();
    building_storage_clear_all();
    g_city.figures.init_figures();
    g_enemy_armies.clear();
    figure_name_init();
    g_formations.clear_all();
    figure_route_clear_all();
    g_recorded_paths.clear();
    map_clear_floodplain_growth();
    // Troop carry lives outside city_data; clear so old saves (no chunk) and map
    // loads cannot inherit a stale snapshot from the previous session.
    g_campaign_carry.clear();

    game.time_init(2098);
    map_monuments_clear();
    // clear grids
    map_image_clear();
    map_building_clear();
    map_terrain_clear();
    map_canal_clear();
    map_figure_clear();
    map_property_clear();
    map_sprite_clear();
    map_bridge_grids_clear();
    map_random_clear();
    g_desirability.clear_map();
    map_elevation_clear();
    map_soldier_strength_clear();
    map_road_network_clear();

    map_image_context_init();
    map_random_init();
    map_tiles_gardens_clear_all();

    events::emit(event_game_mission_pre_load{});
    events::process();

    figure_follow_stop(false);
}

void GamestateLoadDetail::post_load() {
    city_set_player_name(game_features::gameopt_player_name.to_string());
    mission_id_t missionid(g_scenario.campaign_scenario_id);

    bool is_new_mission = (game.session.last_loaded == e_session_mission);
    if (is_new_mission) {
        g_scenario.vars.clear();
    }

    g_scenario.load_metadata(missionid, is_new_mission);
    js_register_mission_vars(g_scenario.vars);

    g_empire.load_mission_metadata(missionid, /*preserve_runtime=*/!is_new_mission);
    js_register_game_handlers(missionid.value());

    // camera
    //    g_camera.refresh_camera_position();
    //    city_view_refresh_viewport();

    // problems / overlays
    g_message_manager.init_problem_areas();
    g_city.reset_overlay();
    game_undo_disable();

    g_distant_battle.determine_distant_battle_city();

    int karmy = g_empire.init_distant_battle_travel_months(EMPIRE_OBJECT_KINGDOME_ARMY);
    g_scenario.distant_battle_set_kingdome_travel_months(karmy);

    int kenemy = g_empire.init_distant_battle_travel_months(EMPIRE_OBJECT_ENEMY_ARMY);
    g_scenario.distant_battle_set_enemy_travel_months(kenemy);

    //map
    map_image_fix_icorrect_tiles();
    map_bridge_migrate_from_sprite();
    map_wall_material_migrate_from_terrain();

    // Enhanced auto-resolve: honor feature after load, drop ghost pending, reopen UI.
    g_invasion_auto_resolve.on_after_load();

    // building counts / storage
    city_resource_determine_available();
    g_city.update_allowed_foods();
    g_city.buildings.update_counters();
    g_city.on_post_load();
    g_city.resource.calculate_stocks();
    city_resource_calculate_storageyard_stocks();
    building_storage_reset_building_ids();
    g_city.avg_coverage.update();
    g_empire_traders.purge_dead();

    g_city.religion.ra_no_traders_months_left = std::clamp<int>(g_city.religion.ra_no_traders_months_left, 0, 12);
    g_city.religion.ra_harshly_reduced_trading_months_left = std::clamp<int>(g_city.religion.ra_harshly_reduced_trading_months_left, 0, 12);

    // Save/map chunks already hold prices; reset only for a fresh mission start.
    if (is_new_mission) {
        trade_prices_reset();
    }

    // city data special cases
    switch (game.session.last_loaded) {
    default:
        assert(false);
        break;

    case e_session_mission:
        game_features::gameopt_game_speed.set( 80 );
        g_city.init_campaign_mission();
        g_city.init_mission_resources(g_scenario.init_resources);
        // Pass JS player_rank from load_metadata � not campaign_scenario_id.
        g_city.kingdome.load_scenario(g_city.kingdome.player_rank, game.session.last_loaded);
        events::emit(event_building_menu_update{ "stage_normal" });
        break;

    case e_session_save:
        events::emit(event_building_menu_update{ "stage_normal" });
        break;

    case e_session_custom_map:
        g_city.init_custom_map();
        g_city.init_mission_resources(g_scenario.init_resources);
        g_city.kingdome.load_scenario(g_city.kingdome.player_rank, game.session.last_loaded);
        events::emit(event_building_menu_update{ "stage_normal" });
        break;
    }

    // city messages
    city_message_clear_scroll();

    // city sounds
    sound_city_init();
    map_tiles_gardens_update_all();

    events::emit(event_level_post_load{
        static_cast<int>(game.session.last_loaded),
        g_scenario.campaign_scenario_id});
}



bool GamestateLoadDetail::load_mission_map_raw(int scenario_id, const char *map_path) {
    if (!map_path || !map_path[0]) {
        return false;
    }

    // Map files do not store carry savings / troops / campaign rank; preserve across pre_load().
    const uint16_t saved_carry = g_city.kingdome.campaign_carry_personal_savings;
    const int32_t saved_rank = g_scenario.campaign_mission_rank;
    const campaign_carry_t saved_troops = g_campaign_carry;

    pre_load();
    vfs::path full = vfs::path(map_path).resolve();
    auto mapfile = vfs::file_open(full);
    if (!g_chunk_io.unserialize(mapfile, 0, FILE_FORMAT_MAP_FILE, read_file_version, file_schema)) {
        return false;
    }

    g_city.kingdome.campaign_carry_personal_savings = saved_carry;
    g_scenario.campaign_mission_rank = saved_rank;
    g_campaign_carry = saved_troops;

    // Campaign session so post_load() applies JS metadata as a new mission (not custom-map hacks).
    game.session.last_loaded = e_session_mission;
    game.session.last_loaded_mission = map_path;
    g_scenario.campaign_scenario_id = scenario_id;
    g_scenario.scmode = e_scenario_normal;
    return true;
}

