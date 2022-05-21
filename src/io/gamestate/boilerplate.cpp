#include "boilerplate.h"

#include "building/construction/build_planner.h"
#include "building/granary.h"
#include "building/maintenance.h"
#include "building/menu.h"
#include "building/storage.h"
#include "city/data.h"
#include "city/emperor.h"
#include "city/map.h"
#include "city/message.h"
#include "city/military.h"
#include "city/mission.h"
#include "city/victory.h"
#include "city/resource.h"
#include "io/file.h"
#include "graphics/image.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "figure/enemy_army.h"
#include "figure/name.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "figuretype/animal.h"
#include "figuretype/water.h"
#include "graphics/animation_timers.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "game/undo.h"
#include "grid/aqueduct.h"
#include "grid/bookmark.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/image_context.h"
#include "grid/orientation.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "grid/soldier_strength.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "scenario/criteria.h"
#include "scenario/demand_change.h"
#include "scenario/distant_battle.h"
#include "scenario/earthquake.h"
#include "scenario/emperor_change.h"
#include "scenario/gladiator_revolt.h"
#include "scenario/invasion.h"
#include "scenario/price_change.h"
#include "scenario/property.h"
#include "scenario/request.h"
#include "sound/city.h"
#include "sound/music.h"
#include "game/mission.h"

#include "building/count.h"
#include "city/floods.h"
#include "window/mission_briefing.h"
#include "window/city.h"
#include "core/stopwatch.h"
#include "city/culture.h"
#include "manager.h"

void fullpath_saves(char *full, const char *filename) {
    strcpy(full, "");
    if (strncasecmp(filename, "Save/", 5) == 0 || strncasecmp(filename, "Save\\", 5) == 0) {
        strcat(full, filename);
        return;
    }
    strcat(full, "Save/");
    strcat(full, setting_player_name_utf8());
    strcat(full, "/");
    strcat(full, filename);
}
void fullpath_maps(char *full, const char *filename) {
    strcpy(full, "");
    if (strncasecmp(filename, "Maps/", 5) == 0 || strncasecmp(filename, "Maps\\", 5) == 0) {
        strcat(full, filename);
        return;
    }
    strcat(full, "Maps/");
    strcat(full, filename);
}

enum {
    LOADED_NULL = -1,
    LOADED_MISSION = 0,
    LOADED_SAVE = 1,
    LOADED_CUSTOM_MAP = 2
};

static stopwatch WATCH;

static int last_loaded = LOADED_NULL;
static void pre_load() { // do we NEED this...?
    scenario_set_campaign_scenario(-1);
    map_bookmarks_clear();

    // clear data
    city_victory_reset();
    Planner.reset();
    city_data_init();
    city_message_init_scenario();
    game_state_init();
    game_animation_init();
    sound_city_init();
    building_menu_enable_all();
    building_clear_all();
    building_storage_clear_all();
    figure_init_scenario();
    enemy_armies_clear();
    figure_name_init();
    formations_clear();
    figure_route_clear_all();

    game_time_init(2098);

    // clear grids
    map_image_clear();
    map_building_clear();
    map_terrain_clear();
    map_aqueduct_clear();
    map_figure_clear();
    map_property_clear();
    map_sprite_clear();
    map_random_clear();
    map_desirability_clear();
    map_elevation_clear();
    map_soldier_strength_clear();
    map_road_network_clear();

    map_image_context_init();
    map_random_init();
}
static void post_load() {
    // TODO: check all of these...

    WATCH.START();

    // scenario settings
    scenario_set_name(scenario_name());
    city_set_player_name(setting_player_name());
    scenario_set_campaign_rank(get_scenario_mission_rank(scenario_campaign_scenario_id()));

    // problems / overlays
    city_message_init_problem_areas();
    city_mission_tutorial_set_fire_message_shown(1);
    city_mission_tutorial_set_disease_message_shown(1);
    game_state_reset_overlay();
    game_undo_disable();

     // military
    image_set_enemy_pak(scenario_property_enemy());
    city_military_determine_distant_battle_city();
    scenario_distant_battle_set_roman_travel_months();
    scenario_distant_battle_set_enemy_travel_months();

    // building counts / storage
    // TODO: can't find cache in Pharaoh's save file format?
    building_count_update();
    building_granaries_calculate_stocks();
    city_resource_calculate_warehouse_stocks();
    city_resource_determine_available();
    for (int i = 0; i < building_get_highest_id(); i++) {
        building *b = building_get(i);
        if (b->state)
            b->update_road_access();
    }
    building_storage_reset_building_ids();
    city_culture_update_coverage();

    // traders / empire
    trade_prices_reset();
    city_emperor_init_scenario(scenario_campaign_rank());

    // city data special cases
    switch (last_loaded) {
        case LOADED_MISSION:
            city_data_init_campaign_mission();
            break;
        case LOADED_CUSTOM_MAP:
            city_data_init_custom_map();
            break;
    }

    // building menu
    building_menu_update(BUILDSET_NORMAL);

    // city messages
    city_message_clear_scroll();

    // city sounds
    sound_city_init();

    WATCH.RECORD("post-load"); //////////////////////////////////////////////////////////////////
    WATCH.LOG();
}

GamestateIO SFIO;
bool GamestateIO::write_mission(const int scenario_id) {
    // TODO?
    return false;
}
bool GamestateIO::write_savegame(const char *filename_short) {
    // concatenate string
    char full[MAX_FILE_NAME];
    fullpath_saves(full, filename_short);

    // write file
    return SFIO.write_to_file(filename_short, 0, FILE_SCHEMA_SAV, 160);
}
bool GamestateIO::write_map(const char *filename_short) {
    return false; //TODO

    // concatenate string
    char full[MAX_FILE_NAME];
    fullpath_maps(full, filename_short);

    // write file
    return SFIO.write_to_file(full, 0, FILE_SCHEMA_MAP, 160);
}

bool GamestateIO::load_mission(const int scenario_id, bool start_immediately) {
    // get mission pack file offset
    int offset = get_campaign_scenario_offset(scenario_id);
    if (offset <= 0)
        return false;

    // read file
    pre_load();
    if (!SFIO.read_from_file(MISSION_PACK_FILE, offset))
        return false;
    last_loaded = LOADED_MISSION;
    scenario_set_campaign_scenario(scenario_id);
    post_load();

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();
        // replay mission autosave file
        GamestateIO::write_savegame("autosave_replay.sav");
    }
    return true;
}
bool GamestateIO::load_savegame(const char *filename_short, bool start_immediately) {
    // concatenate string
    char full[MAX_FILE_NAME];
    fullpath_saves(full, filename_short);

    // read file
    pre_load();
    if (!SFIO.read_from_file(full, 0))
        return false;
    last_loaded = LOADED_SAVE;
    post_load();

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();
    }
    return true;
}
bool GamestateIO::load_map(const char *filename_short, bool start_immediately) {
//    return false; //TODO

    // concatenate string
    char full[MAX_FILE_NAME];
    fullpath_maps(full, filename_short);

    // read file
    pre_load();
    if (!SFIO.read_from_file(full, 0))
        return false;
    last_loaded = LOADED_CUSTOM_MAP;
    post_load();

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();
        // replay mission autosave file
        GamestateIO::write_savegame("autosave_replay.sav");
    }
    return true;
}

void GamestateIO::start_loaded_file() {

    // build the map grids when loading MAP files
    if (last_loaded != LOADED_SAVE) {
        // initialize grids
        map_tiles_update_all_elevation();
        map_tiles_river_refresh_entire();
        map_tiles_update_all_earthquake();
        map_tiles_update_all_rocks();
        map_tiles_add_entry_exit_flags();
        map_tiles_update_all_empty_land();
        map_tiles_update_all_meadow();
        map_tiles_update_all_roads();
        map_tiles_update_all_plazas();
        map_tiles_update_all_walls();
        map_tiles_update_all_aqueducts(0);

//        map_natives_init();
        figure_create_fishing_points();
        figure_create_herds();
        figure_create_flotsam();

        map_point entry = scenario_map_entry();
        map_point exit = scenario_map_exit();
        city_map_set_entry_point(entry.x(), entry.y());
        city_map_set_exit_point(exit.x(), exit.y());

        // game time
        game_time_init(scenario_property_start_year());

        // traders / empire
        empire_init_scenario();
        traders_clear();

        // set up events
        scenario_earthquake_init();
        scenario_gladiator_revolt_init();
        scenario_emperor_change_init();
        scenario_criteria_init_max_year();
        scenario_invasion_init();
        city_military_determine_distant_battle_city();
        scenario_request_init();
        scenario_demand_change_init();
        scenario_price_change_init();

        // tutorial flags
        tutorial_init();
    }

    // city view / orientation
    city_view_init();
    map_orientation_update_buildings();

    // routing
    map_routing_update_all();
    figure_route_clean();
    map_road_network_update();
    building_maintenance_check_rome_access();

    // river / garden tiles refresh
    build_terrain_caches();
    floodplains_init();
    map_tiles_river_refresh_entire();
    map_tiles_determine_gardens();
    map_tiles_update_all_vegetation_tiles();

    if (last_loaded == LOADED_MISSION)
        window_mission_briefing_show();
    else {
        game_state_unpause();
        window_city_show();
    }
    sound_music_update(true);
    last_loaded = LOADED_NULL;
}

bool GamestateIO::delete_mission(const int scenario_id) {
    // TODO?
    return false;
}
bool GamestateIO::delete_savegame(const char *filename_short) {
    // concatenate string
    char full[MAX_FILE_NAME];
    fullpath_saves(full, filename_short);

    // delete file
    return file_remove(full);
}
bool GamestateIO::delete_map(const char *filename_short) {
    // concatenate string
    char full[MAX_FILE_NAME];
    fullpath_maps(full, filename_short);

    // delete file
    return file_remove(full);
}