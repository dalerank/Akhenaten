#include "boilerplate.h"
#include "boilerplate_detail.h"

#include "building/construction/build_planner.h"
#include "building/building_granary.h"
#include "building/building_storage.h"
#include "building/building_wall.h"
#include "building/monuments.h"
#include "game/game_config.h"
#include "game/autosave_module.h"
#include "city/city.h"
#include "city/map.h"
#include "city/city_message.h"
#include "city/city_hotkeys_handler.h"
#include "city/campaign_carry.h"
#include "city/military.h"
#include "city/city_resource.h"
#include "core/bstring.h"
#include "content/vfs.h"
#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/type.h"
#include "empire/trade_prices.h"
#include "figure/enemy_army.h"
#include "figure/figure_names.h"
#include "figure/route.h"
#include "empire/trader_handler.h"
#include "game/mission.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "grid/canals.h"
#include "grid/trees.h"
#include "grid/bookmark.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/image_context.h"
#include "grid/orientation.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "grid/soldier_strength.h"
#include "grid/sprite.h"
#include "grid/bridge_grid.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/wall_material.h"
#include "grid/moisture.h"
#include "grid/floodplain.h"
#include "grid/basin.h"
#include "grid/water.h"
#include "grid/sandstone.h"
#include "grid/stone.h"
#include "grid/limestone.h"
#include "grid/granite.h"
#include "grid/golden.h"
#include "grid/copper.h"
#include "grid/clay.h"
#include "grid/gems.h"
#include "game/game.h"
#include "editor/editor.h"
#include "scenario/criteria.h"
#include "scenario/demand_change.h"
#include "scenario/distant_battle.h"
#include "scenario/earthquake.h"
#include "scenario/editor_map_meta.h"
#include "scenario/farao_change.h"
#include "scenario/scenario_revolt.h"
#include "scenario/scenario_invasion.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/price_change.h"
#include "scenario/request.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "js/js_game.h"
#include "widget/widget_figure_follow.h"
#include "window/window_city.h"
#include "window/file_dialog_common.h"
#include "game/game_events.h"
#include "empire/empire.h"
#include "city/city_warnings.h"
#include "city/city_recorded_paths.h"
#include "empire/empire_traders.h"

#include "chunks.h"
#include "file_schemas.h"
#include "city/coverage.h"
#include "city/city_floods.h"
#include "core/log.h"
#include "core/profiler.h"
#include "io/io.h"
#include "io/chunk_serializer.h"
#include "js/js_game.h"
#include "dev/debug.h"
#include "window/popup_dialog.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <vector>
#include <cstdio>

#ifdef _MSC_VER
// not #if defined(_WIN32) || defined(_WIN64) because we have strncasecmp in mingw
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#include <direct.h>
#else
#include <sys/stat.h>
#endif

uint32_t save_data_version() {
    return latest_save_version;
}

uint32_t svx_container_version() {
    return svx::CONTAINER_REV;
}

vfs::path fullpath_saves(vfs::path filename) {
    if (strncasecmp(filename, "Save/", 5) == 0 || strncasecmp(filename, "Save\\", 5) == 0) {
        return vfs::path(filename);
    }

    return vfs::path(vfs::SAVE_FOLDER, "/", game_features::gameopt_player_name.to_string().c_str(), "/", filename);
}

vfs::path fullpath_maps(vfs::path filename) {
    if (strncasecmp(filename, "Maps/", 5) == 0 || strncasecmp(filename, "Maps\\", 5) == 0) {
        return filename;
    }
    return vfs::path(vfs::MAPS_FOLDER, "/", filename.c_str());
}

bool GamestateIO::write_family_marker(pcstr filename_short) {
    vfs::path full = fullpath_saves(filename_short);
    vfs::path folders = vfs::content_path(fullpath_saves("").c_str());

    logs::info("Save player data: writing %s (dir %s)", full.c_str(), folders.c_str());
    vfs::create_folders(folders);

    // FILE_FORMAT_SAVE_FILE (.sav) stub — not a city save, so no Ironwill / last_save update.
    const bool save_ok = g_chunk_io.serialize(full, 0, FILE_FORMAT_SAVE_FILE, save_data_version(),
                                              file_schema_family_marker);
    if (save_ok) {
        logs::info("Save player data: OK %s", full.c_str());
    } else {
        logs::error("Save player data: FAILED %s", full.c_str());
    }
    return save_ok;
}

bool GamestateIO::write_savegame(pcstr filename_short) {
    // Gate by flag + whitelist only (session.active is not cleared on main menu — E4/R6).
    if (game_features::gameopt_ironwill.to_bool()
        && !autosave_module_t::is_ironwill_exempt_save(filename_short)) {
        logs::info("Save game: blocked by Ironwill (%s)", filename_short ? filename_short : "");
        return false;
    }

    vfs::path full = fullpath_saves(filename_short);

    logs::info("Save game: writing %s", full.c_str());

    e_file_format format = get_format_from_file(filename_short);
    assert(format == FILE_FORMAT_SAVE_FILE_EXT);
    bool save_ok = g_chunk_io.serialize(full, 0, format, save_data_version(), file_schema);
    if (save_ok) {
        if (!autosave_module_t::is_monthly_filename(filename_short)) {
            game_features::gameopt_last_save_filename = full.c_str();
            game_features::gameopt_last_player = game_features::gameopt_player_name.to_string();
            game_features::save();
        }
        logs::info("Save game: OK %s", full.c_str());
    } else {
        logs::error("Save game: FAILED %s", full.c_str());
    }

    return save_ok;
}

bool GamestateIO::write_map(pcstr path, bool relative) {
    if (!path || !path[0]) {
        return false;
    }
    if (relative) {
        return g_chunk_io.serialize(fullpath_maps(path), 0, FILE_FORMAT_MAP_FILE, 160, file_schema);
    }
    return g_chunk_io.serialize(path, 0, FILE_FORMAT_MAP_FILE, 160, file_schema);
}

bool GamestateIO::load_mission(const int scenario_id, bool start_immediately) {
    xstring map_file;
    g_config_arch.r_section(mission_id_t(scenario_id), [&](archive arch) {
        map_file = arch.r_string("map_file");
    });

    if (map_file.empty()) {
        logs::error("Mission %d: no map_file in mission script", scenario_id);
        return false;
    }

    const vfs::path map_full = vfs::path(map_file.c_str()).resolve();
    if (!vfs::file_exists(map_full)) {
        logs::error("Mission %d: map file missing: %s", scenario_id, map_file.c_str());
        bstring512 body;
        body.printf("Map file not found:\n%s", map_file.c_str());
        popup_dialog::show_ok(lang_text_from_key("#popup_dialog_map_file_missing"), body.c_str());
        return false;
    }

    if (!GamestateLoadDetail::load_mission_map_raw(scenario_id, map_file.c_str())) {
        logs::error("Mission %d: map_file '%s' failed to load", scenario_id, map_file.c_str());
        return false;
    }

    // Scenario selection loads with start_immediately=false, so start_loaded_file()
    // (which also calls init_cities) never runs. post_load() needs EMPIRE_CITY_OURS via
    // update_allowed_foods() — rebuild cities from empire objects first.
    g_empire.init_cities();

    GamestateLoadDetail::post_load();

    g_empire.fix_trade_routes();

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();

        // replay mission autosave file
        bstring256 filename("autosave_replay.", saved_game_data_expanded.extension);
        GamestateIO::write_savegame(filename);
    }

    return true;
}

bool GamestateIO::load_savegame(pcstr filename_short, bool start_immediately) {
    // concatenate string
    bstring256 full = fullpath_saves(filename_short).resolve();

    if (!vfs::file_exists(full.c_str())) {
        logs::error("Load game: file not found %s", full.c_str());
        return false;
    }

    // read file
    GamestateLoadDetail::pre_load();
    e_file_format file_format = get_format_from_file(filename_short);
    auto savegame = vfs::file_open(full);
    if (!g_chunk_io.unserialize(savegame, 0, file_format, GamestateLoadDetail::read_file_version, file_schema)) {
        return false;
    }

    game.session.last_loaded = e_session_save;
    game.session.last_loaded_mission = filename_short;
    GamestateLoadDetail::post_load();

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();
    }

    return true;
}

bool GamestateIO::load_map(pcstr filename, bool relative, bool start_immediately) {
    OZZY_PROFILER_FUNCTION();
    vfs::path fullpath;
    if (relative) {
        fullpath = fullpath_maps(filename).resolve();
    } else {
        fullpath = vfs::path(filename).resolve();
    }

    // read file
    GamestateLoadDetail::pre_load();
    auto mapfile = vfs::file_open(fullpath);
    if (!g_chunk_io.unserialize(mapfile, 0, FILE_FORMAT_MAP_FILE, GamestateLoadDetail::read_file_version, file_schema)) {
        return false;
    }

    game.session.last_loaded = e_session_custom_map;
    game.session.last_loaded_mission = filename;
    g_scenario.campaign_scenario_id = get_custom_mission_id(filename);
    // temp hack, custom map missions have no cities
    auto cities = g_empire.get_cities();
    cities[0].type = EMPIRE_CITY_OURS;
    cities[0].in_use = true;
    // temp hack

    // ED5: custom-map play loads *.meta.js (requests/invasions/price/demand)
    // before start_loaded_file inits. Editor load applies meta itself after strip.
    if (!editor_is_active()) {
        editor_invasions_clear();
        editor_price_changes_clear();
        editor_demand_changes_clear();
        if (vfs::file_exists(editor_map_meta_path(fullpath.c_str()))) {
            g_scenario.events.clear_for_editor();
            editor_map_meta_load(fullpath.c_str());
        }
    }

    GamestateLoadDetail::post_load();

    if (start_immediately) {
        start_loaded_file();
        bstring256 filename("autosave_replay.", saved_game_data_expanded.extension);
        GamestateIO::write_savegame(filename);
    }

    return true;
}

void GamestateIO::start_loaded_file() {
    // build the map grids when loading MAP files
    if (game.session.last_loaded != e_session_save) {
        // initialize grids
        map_tiles_update_all_elevation();
        map_tiles_river_refresh_entire();
        map_tiles_update_all_earthquake();
        map_tiles_update_all_rocks();
        map_sandstone_init();
        map_stone_init();
        map_limestone_init();
        map_granite_init();
        map_golden_init();
        map_copper_init();
        map_gems_init();
        map_clay_init();
        map_tiles_add_entry_exit_flags();
        map_tiles_update_all_cleared_land();
        map_tiles_update_all_empty_land();
        map_tiles_update_all_meadow();
        map_tiles_update_all_roads();
        map_tiles_update_all_plazas();
        map_canal_update_all_tiles(0);

        //        map_natives_init();
        g_city.fishing_points.create();
        g_city.animals.create_herds();

        g_city.map.entry_point = scenario_map_entry();
        g_city.map.exit_point = scenario_map_exit();

        game.time_init(g_scenario.start_year);

        // traders / empire
        g_empire_map.init_scenario();
        g_empire.init_cities();
        g_empire_traders.init();

        // set up events
        scenario_earthquake_init();
        scenario_revolt_init();
        scenario_kingdome_change_init();
        scenario_criteria_init_max_year();
        g_invasions.init();
        g_distant_battle.determine_distant_battle_city();
        scenario_request_init();
        scenario_demand_change_init();
        scenario_price_change_init();
    }

    map_moisture_recompute_profile();

    g_camera.init();
    map_orientation_update_buildings();
    map_terrain_init_outside_map();
    map_normalize_outside_diamond_all();

    // river / garden tiles refresh
    build_terrain_caches();
    map_basin_rebuild();
    canals_reset_decay_phase();

    // routing
    map_routing_update_all();
    figure_route_clean();
    g_city.map.update_road_network();
    map_routing_update_ferry_routes();
    g_city.maintenance.check_kingdome_access();

    // tiles
    g_floods.init();
    map_water_rebuild_shores();
    map_tiles_update_floodplain_images();
    map_tiles_river_refresh_entire();
    map_tiles_gardens_determine();
    map_tiles_upadte_all_marshland_tiles();
    map_tree_update_all_tiles();
    map_building_update_all_tiles();

    autoconfig_window::before_mission_start();
    events::emit(event_mission_start{ g_scenario.campaign_scenario_id });

    if (game.session.last_loaded == e_session_mission) {
        g_campaign_carry.activate_for_mission(g_scenario.carry_troops_mask);
        g_campaign_carry.post_notice_if_needed();
        // Monument store survives missions without carry_monuments (e.g. Maritis 50).
        if (g_scenario.carry_monuments) {
            g_campaign_carry.apply_monuments();
        }
    }

    g_city.before_start_simulation();
    game.before_start_simulation();
    game.session.active = true;

    const bool show_briefing = (game.session.last_loaded == e_session_mission);
    if (show_briefing) {
        events::emit(event_mission_briefing_show_after_load{ g_scenario.campaign_scenario_id });
        events::process();
    } else {
        game.paused = false;
        window_city_show();
        g_sound.music_update(true);
    }
    game.session.last_loaded = e_session_none;
}

bool GamestateIO::delete_savegame(vfs::path filename_short) {
    vfs::path full = fullpath_saves(filename_short);
    return vfs::file_remove(full);
}

bool GamestateIO::delete_map(const char* filename_short) {
    vfs::path full = fullpath_maps(filename_short);
    // ED4b sidecar next to map (Maps/foo.map ? Maps/foo.meta.js).
    vfs::path meta = full;
    char *dot = std::strrchr(meta.data(), '.');
    if (dot) {
        std::snprintf(dot, (size_t)(vfs::path::capacity - (dot - meta.data())), ".meta.js");
        if (vfs::file_exists(meta)) {
            vfs::file_remove(meta.c_str());
        }
    }
    return vfs::file_remove(full);
}

declare_console_command_p(save_map) {
    std::string filename;

    // Read filename from input stream
    if (!(is >> filename)) {
        os << "Error: Please provide a filename.\n";
        os << "Usage: save_map <filename>\n";
        os << "Example: save_map my_custom_map\n";
        return;
    }

    // Check if we're in a valid game state
    if (!game.session.active) {
        os << "Error: No active game session. Please load a map or start a mission first.\n";
        return;
    }

    bool success = GamestateIO::write_map(filename.c_str());

    os << (success
           ? "Map saved successfully!\n"
           : "Error: Failed to save map.\n");
}