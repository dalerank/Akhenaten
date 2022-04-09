#include "file.h"

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
#include "game/gamestate/file_io.h"
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
#include "undo.h"
#include "player_data.h"
#include "mission.h"

#include <string.h>
#include <building/count.h>
#include <city/floods.h>
#include <window/mission_briefing.h>
#include <window/city.h>

static const char MISSION_PACK_FILE[] = "mission1.pak";

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
    if (GAME_ENV == ENGINE_ENV_C3) // only for external file
        empire_load_external_c3(is_custom_scenario, empire_id);
    scenario_distant_battle_set_roman_travel_months();
    scenario_distant_battle_set_enemy_travel_months();
}

static void initialize_saved_game(void) {
    load_empire_data(scenario_is_custom(), scenario_empire_id());

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

    game_state_unpause();
}
static buffer *offset_buf = new buffer(4);
static int get_campaign_scenario_offset(int scenario_id) {
    // init 4-byte buffer and read from file header corresponding to scenario index (i.e. mission 20 = offset 20*4 = 80)
    offset_buf->clear();
    if (!io_read_file_part_into_buffer(MISSION_PACK_FILE, NOT_LOCALIZED, offset_buf, 4, 4 * scenario_id))
        return 0;
    return offset_buf->read_i32();
}
static bool game_load_scenario_savegame(const char *filename) {}
static bool game_load_scenario_pak_mission(int scenario_id) {

    int offset = get_campaign_scenario_offset(scenario_id);
    if (offset <= 0)
        return false;
    if (!game_file_io_read_saved_game(MISSION_PACK_FILE, offset))
        return false;

    if (scenario_id == SCENARIO_NUBT)
        scenario_set_player_name(setting_player_name());
    else
        scenario_restore_campaign_player_name();
    initialize_saved_game();
    scenario_fix_patch_trade(scenario_id);

    scenario_set_campaign_scenario(scenario_id);
    scenario_set_campaign_rank(get_scenario_mission_rank(scenario_id));

    city_data_init_campaign_mission();

    return true;
}
static bool game_load_scenario_custom_map(const char *filename) {
    if (!file_exists(filename, NOT_LOCALIZED))
        return false;

    clear_scenario_data();
//    if (!game_file_io_read_scenario(filename)) // TODO
//        return false;
    if (!game_file_io_read_saved_game(filename, 0)) // TODO
        return false;

    // post-load
    trade_prices_reset();
    load_empire_data(1, scenario_empire_id());
    initialize_scenario_data(scenario_name());
    scenario_set_player_name(setting_player_name());
    return true;
}

static bool pre_load() {
    scenario_set_campaign_scenario(-1);
    map_bookmarks_clear();
    return true;
}
static bool post_load() {
    if (scenario_is_mission_rank(1))
        setting_set_personal_savings_for_mission(0, 0);

    scenario_settings_init_mission();
    city_emperor_init_scenario(scenario_campaign_rank());

    tutorial_init();
    building_menu_update(BUILDSET_NORMAL);
    city_message_init_scenario();
    return true;
}
bool game_start_loaded_scenario() {
    if (!post_load()) return false;
    if (scenario_is_custom())
        window_city_show();
    else
        window_mission_briefing_show();
    sound_music_update(1);
    return true;
}
bool game_load_scenario(const char *filename, bool start_immediately) {
    if (!pre_load()) return false;

    // file loading
    if (file_has_extension(filename, "map"))
        if (!game_load_scenario_custom_map(filename)) return false;
    else if (file_has_extension(filename, "sav"))
        if (!game_load_scenario_savegame(filename)) return false;
    else return false;

    if (start_immediately)
        return game_start_loaded_scenario();
    return true;
}
bool game_load_scenario(const uint8_t *scenario_name, bool start_immediately) {
    if (!pre_load()) return false;

    return false; // TODO

    if (!start_immediately)
        return true;
}
bool game_load_scenario(int scenario_id, bool start_immediately) {

    if (!pre_load()) return false;

    // pak loading
    if (!game_load_scenario_pak_mission(scenario_id))
        return false;

    if (start_immediately)
       return game_start_loaded_scenario();
    return true;
}

bool game_file_load_saved_game(const char *filename) {
    if (!game_file_io_read_saved_game(filename, 0))
        return false;

    initialize_saved_game();
    building_storage_reset_building_ids();

    sound_music_update(1);
    return true;
}
bool game_file_write_saved_game(const char *filename) {
    return game_file_io_write_saved_game(filename);
}
bool game_file_delete_saved_game(const char *filename) {
    return game_file_io_delete_saved_game(filename);
}
void game_file_write_mission_saved_game(void) {
    return; // temp
    int rank = scenario_campaign_rank();
    if (rank < 0)
        rank = 0;
    else if (rank > 11)
        rank = 11;

    return; // temp
    const char *filename = MISSION_SAVED_GAMES[rank];
    if (locale_translate_rank_autosaves()) {
        char localized_filename[MAX_FILE_NAME];
        encoding_to_utf8(lang_get_string(32, rank), localized_filename, MAX_FILE_NAME,
                         encoding_system_uses_decomposed());
        strcat(localized_filename, ".svx");
        filename = localized_filename;
    }
    if (city_mission_should_save_start() && !file_exists(filename, NOT_LOCALIZED))
        game_file_io_write_saved_game(filename);
}
