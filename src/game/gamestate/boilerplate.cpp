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
#include "city/view.h"
#include "city/resource.h"
#include "core/encoding.h"
#include "core/file.h"
#include "core/image.h"
#include "core/io.h"
#include "core/lang.h"
#include "core/string.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "figure/enemy_army.h"
#include "figure/formation.h"
#include "figure/name.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "figuretype/animal.h"
#include "figuretype/water.h"
#include "game/animation.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "game/undo.h"
#include "map/aqueduct.h"
#include "map/bookmark.h"
#include "map/building.h"
#include "map/desirability.h"
#include "map/elevation.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/image.h"
#include "map/image_context.h"
#include "map/natives.h"
#include "map/orientation.h"
#include "map/property.h"
#include "map/random.h"
#include "map/road_network.h"
#include "map/routing_terrain.h"
#include "map/soldier_strength.h"
#include "map/sprite.h"
#include "map/terrain.h"
#include "map/tiles.h"
#include "scenario/criteria.h"
#include "scenario/demand_change.h"
#include "scenario/distant_battle.h"
#include "scenario/earthquake.h"
#include "scenario/emperor_change.h"
#include "scenario/empire.h"
#include "scenario/gladiator_revolt.h"
#include "scenario/invasion.h"
#include "scenario/map.h"
#include "scenario/price_change.h"
#include "scenario/property.h"
#include "scenario/request.h"
#include "scenario/scenario.h"
#include "sound/city.h"
#include "sound/music.h"
#include "game/undo.h"
#include "game/player_data.h"
#include "game/mission.h"

#include <string.h>
#include <building/count.h>
#include <city/floods.h>
#include <window/mission_briefing.h>
#include <window/city.h>
#include <game/gamestate/manager.h>

//static const char MISSION_PACK_FILE[] = "mission1.pak";

static const char MISSION_SAVED_GAMES[][32] = {
        "Citizen.sav",
        "Clerk.sav",
        "Engineer.sav",
        "Architect.sav",
        "Quaestor.sav",
        "Procurator.sav",
        "Aedile.sav",
        "Praetor.sav",
        "Consul.sav",
        "Proconsul.sav",
        "Caesar.sav",
        "Caesar2.sav"
};

void path_build_saves(char *full, const char *filename) {
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
void path_build_maps(char *full, const char *filename) {
    strcpy(full, "");
    if (strncasecmp(filename, "Maps/", 5) == 0 || strncasecmp(filename, "Maps\\", 5) == 0) {
        strcat(full, filename);
        return;
    }
    strcat(full, "Maps/");
    strcat(full, filename);
}

static void clear_scenario_data(void) {
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
static void initialize_scenario_data(const uint8_t *scenario_name) {
    scenario_set_name(scenario_name);
    scenario_map_init();

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

    map_natives_init();

    city_view_init();

    figure_create_fishing_points();
    figure_create_herds();
    figure_create_flotsam();

    map_routing_update_all();

    scenario_map_init_entry_exit();

    map_point entry = scenario_map_entry();
    map_point exit = scenario_map_exit();

    city_map_set_entry_point(entry.x, entry.y);
    city_map_set_exit_point(exit.x, exit.y);

    game_time_init(scenario_property_start_year());

    // set up events
    scenario_earthquake_init();
    scenario_gladiator_revolt_init();
    scenario_emperor_change_init();
    scenario_criteria_init_max_year();

    empire_init_scenario();
    traders_clear();
    scenario_invasion_init();
    city_military_determine_distant_battle_city();
    scenario_request_init();
    scenario_demand_change_init();
    scenario_price_change_init();
    building_menu_update(BUILDSET_NORMAL);
    image_load_main_paks(scenario_property_climate(), 0, 0);
    image_set_enemy_pak(scenario_property_enemy());

    city_data_init_scenario();
    game_state_unpause();
}
static void load_empire_data(int is_custom_scenario, int empire_id) {
//    if (GAME_ENV == ENGINE_ENV_C3) // only for external file
//        empire_load_external_c3(is_custom_scenario, empire_id);
    scenario_distant_battle_set_roman_travel_months();
    scenario_distant_battle_set_enemy_travel_months();
}
static void pre_load() { // do we NEED this...?
    scenario_set_campaign_scenario(-1);
    map_bookmarks_clear();
}
static void post_load() {
    trade_prices_reset();
    load_empire_data(scenario_is_custom(), scenario_empire_id());
    if (scenario_is_custom())
        initialize_scenario_data(scenario_name());
    city_set_player_name(setting_player_name());

    scenario_map_init();

    city_view_init();

    map_routing_update_all();
    floodplains_init();

    map_orientation_update_buildings();
    figure_route_clean();
    map_road_network_update();
    building_maintenance_check_rome_access();
    building_granaries_calculate_stocks();
    building_menu_update(BUILDSET_NORMAL);
    city_message_init_problem_areas();

    sound_city_init();

    game_undo_disable();
    game_state_reset_overlay();

    city_mission_tutorial_set_fire_message_shown(1);
    city_mission_tutorial_set_disease_message_shown(1);

    if (GAME_ENV == ENGINE_ENV_C3) // TODO?
        image_load_main_paks(scenario_property_climate(), 0, 0);

    image_set_enemy_pak(scenario_property_enemy());
    city_military_determine_distant_battle_city();
    map_tiles_determine_gardens();

    city_message_clear_scroll();
    map_tiles_river_refresh_entire();

    // TODO: temp?
    // can't find cache in Pharaoh's save file format?
    building_count_update();
    city_resource_calculate_warehouse_stocks();
    city_resource_determine_available();
    for (int i = 0; i < building_get_highest_id(); i++) {
        building *b = building_get(i);
        if (b->state)
            b->update_road_access();
    }

    building_storage_reset_building_ids();

    // post load
    if (scenario_is_mission_rank(1))
        setting_set_personal_savings_for_mission(0, 0);

    scenario_settings_init_mission();
    city_emperor_init_scenario(scenario_campaign_rank());

    tutorial_init();
    building_menu_update(BUILDSET_NORMAL);
    city_message_init_scenario();

    scenario_set_campaign_rank(get_scenario_mission_rank(scenario_campaign_scenario_id()));
    city_data_init_campaign_mission();

//    game_state_unpause();
}

GamestateIO SFIO;
bool GamestateIO::write_mission(const int scenario_id) {
    // TODO?
    return false;
}
bool GamestateIO::write_savegame(const char *filename_short) {
    // concatenate string
    char full[MAX_FILE_NAME];
    path_build_saves(full, filename_short);

    // write file
    return SFIO.write_to_file(filename_short, 0, FILE_SCHEMA_SAV, {160, 181});
}
bool GamestateIO::write_map(const char *filename_short) {
    return false; //TODO

    // concatenate string
    char full[MAX_FILE_NAME];
    path_build_maps(full, filename_short);

    // write file
    return SFIO.write_to_file(full, 0, FILE_SCHEMA_MAP, {160, 181});
}

enum {
    LOADED_NULL = -1,
    LOADED_MISSION = 0,
    LOADED_SAVE = 1,
    LOADED_MAP = 2
};

static int last_loaded = LOADED_NULL;
bool GamestateIO::load_mission(const int scenario_id, bool start_immediately) {
    // get mission pack file offset
    int offset = get_campaign_scenario_offset(scenario_id);
    if (offset <= 0)
        return false;

    // read file
    pre_load();
    if (!SFIO.read_from_file(MISSION_PACK_FILE, offset))
        return false;
    post_load();
    scenario_set_campaign_scenario(scenario_id);
    last_loaded = LOADED_MISSION;

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
    path_build_saves(full, filename_short);

    // read file
    pre_load();
    if (!SFIO.read_from_file(full, 0))
        return false;
    post_load();
    last_loaded = LOADED_SAVE;

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();
    }
    return true;
}
bool GamestateIO::load_map(const char *filename_short, bool start_immediately) {
    return false; //TODO

    // concatenate string
    char full[MAX_FILE_NAME];
    path_build_maps(full, filename_short);

    // read file
    pre_load();
    if (!SFIO.read_from_file(full, 0))
        return false;
    post_load();
    last_loaded = LOADED_MAP;

    // finish loading and start
    if (start_immediately) {
        start_loaded_file();
        // replay mission autosave file
        GamestateIO::write_savegame("autosave_replay.sav");
    }
    return true;
}

void GamestateIO::start_loaded_file() {
    game_state_unpause();
    if (last_loaded == LOADED_MISSION)
        window_mission_briefing_show();
    else
        window_city_show();
    sound_music_update(1);
    last_loaded = LOADED_NULL;
}

bool GamestateIO::delete_mission(const int scenario_id) {
    // TODO?
    return false;
}
bool GamestateIO::delete_savegame(const char *filename_short) {
    // concatenate string
    char full[MAX_FILE_NAME];
    path_build_saves(full, filename_short);

    // delete file
    return file_remove(full);
}
bool GamestateIO::delete_map(const char *filename_short) {
    // concatenate string
    char full[MAX_FILE_NAME];
    path_build_maps(full, filename_short);

    // delete file
    return file_remove(full);
}