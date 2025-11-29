#include "file_editor.h"

#include "building/construction/build_planner.h"
#include "building/building_storage.h"
#include "building/building_wall.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/victory.h"
#include "city/city_building_menu_ctrl.h"
#include "empire/empire_map.h"
#include "empire/empire_object.h"
#include "figure/enemy_army.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_names.h"
#include "figure/route.h"
#include "empire/trader_handler.h"
#include "empire/empire.h"
#include "figuretype/editor.h"
#include "game/state.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/image_context.h"
#include "grid/natives.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/canals.h"
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "grid/soldier_strength.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "scenario/distant_battle.h"
#include "scenario/earthquake.h"
#include "scenario/editor.h"
#include "scenario/empire.h"
#include "scenario/scenario_invasion.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/music.h"
#include "game/game.h"
#include "empire/empire_traders.h"

void game_file_editor_clear_data(void) {
    g_city.victory_state.reset();
    g_city.migration.reset();
    g_city_planner.reset();
    g_city.init();
    g_city.init_custom_map();
    g_message_manager.init();
    game_state_init();
    game.animation_timers_init();
    sound_city_init();
    g_building_menu_ctrl.set_all(true);
    building_clear_all();
    building_storage_clear_all();
    g_city.figures.init_figures();
    g_enemy_armies.clear();
    figure_name_init();
    g_formations.clear_all();
    figure_route_clear_all();
    g_empire_traders.init();
    game.simtime.init(2098);
    g_invasions.clear();
}

static void clear_map_data(void) {
    map_image_clear();
    map_building_clear();
    map_terrain_clear();
    map_canal_clear();
    map_figure_clear();
    map_property_clear();
    map_sprite_clear();
    map_random_clear();
    g_desirability.clear_map();
    map_elevation_clear();
    map_soldier_strength_clear();
    map_road_network_clear();

    map_image_context_init();
    map_terrain_init_outside_map();
    map_random_init();
    map_property_init_alternate_terrain();
}

static void create_blank_map(int size) {
    scenario_editor_create(size);
    clear_map_data();
    map_image_init_edges();
    camera_go_to_corner_tile(screen_tile(76, 152), true);
    city_view_reset_orientation();
}

static void prepare_map_for_editing(void) {
    //    image_load_main_paks(scenario_property_climate(), 1, 0);

    //    empire_load_external_c3(1, scenario_empire_id());
    g_empire.init_cities();

    g_city.figures.init_figures();
    figure_create_editor_flags();

    map_tiles_update_all_elevation();
    map_tiles_river_refresh_entire();
    map_tiles_update_all_earthquake();
    map_tiles_update_all_rocks();
    map_tiles_update_all_empty_land();
    map_tiles_update_all_meadow();
    map_tiles_update_all_roads();
    map_tiles_update_all_plazas();
    building_mud_wall::update_all_walls();
    map_canal_update_all_tiles(0);
    map_natives_init_editor();
    map_routing_update_all();

    city_view_init();
    game.paused = false;
}

void game_file_editor_create_scenario(int size) {
    create_blank_map(size);
    prepare_map_for_editing();
}

int game_file_editor_load_scenario(const char* scenario_file) {
    clear_map_data();
    //    if (!game_file_io_read_scenario(scenario_file)) TODO
    //        return 0;

    prepare_map_for_editing();
    return 1;
}

int game_file_editor_write_scenario(const char* scenario_file) {
    scenario_editor_set_native_images(image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE),
                                      image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE) + 2,
                                      image_id_from_group(GROUP_EDITOR_BUILDING_CROPS));

    int karmy = g_empire.init_distant_battle_travel_months(EMPIRE_OBJECT_KINGDOME_ARMY);
    g_scenario.distant_battle_set_kingdome_travel_months(karmy);

    int kenemy = g_empire.init_distant_battle_travel_months(EMPIRE_OBJECT_ENEMY_ARMY);
    g_scenario.distant_battle_set_enemy_travel_months(kenemy);

    //    return game_file_io_write_scenario(scenario_file); TODO
    return 0;
}
