#include "file_editor.h"

#include "building/construction/build_planner.h"
#include "building/building_storage.h"
#include "building/building_wall.h"
#include "city/city.h"
#include "city/city_message.h"
#include "game/game_events.h"
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
#include "grid/road_network.h"
#include "grid/routing/routing_terrain.h"
#include "grid/soldier_strength.h"
#include "grid/sprite.h"
#include "grid/bridge_grid.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/distant_battle.h"
#include "scenario/earthquake.h"
#include "scenario/editor.h"
#include "scenario/editor_map_gen.h"
#include "scenario/editor_map_meta.h"
#include "scenario/empire.h"
#include "scenario/scenario_invasion.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/sound_city.h"
#include "sound/music.h"
#include "game/game.h"
#include "empire/empire_traders.h"

#include <cstring>

#if defined(_MSC_VER)
#define strncasecmp _strnicmp
#endif


void game_file_editor_clear_data(void) {
    grid_xx::init_all_grids();

    g_city.victory.reset();
    g_city.migration.reset();
    g_city_planner.reset();
    g_city.init();
    g_city.init_custom_map();
    g_message_manager.init();
    game.init_state();
    game.animation_timers_init();
    sound_city_init();
    events::emit(event_building_menu_update{ "enable_all" });
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
    map_bridge_grids_clear();
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
    g_camera.go_to_corner_tile(screen_tile(76, 152), true);
    g_camera.reset_orientation();
}

static void prepare_map_for_editing(void) {
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

    g_camera.init();
    game.paused = false;
}

void game_file_editor_create_scenario(int size) {
    create_blank_map(size);
    prepare_map_for_editing();
}

void game_file_editor_generate_scenario(int size) {
    game_file_editor_clear_data();
    create_blank_map(size);
    editor_map_generate();
    prepare_map_for_editing();
    g_scenario.is_saved = 0;
}

static bool path_looks_absolute(const char *path) {
    if (!path || !path[0]) {
        return false;
    }
    if (path[0] == '/' || path[0] == '\\') {
        return true;
    }
    return path[1] == ':' && ((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z'));
}

int game_file_editor_load_scenario(const char* scenario_file) {
    if (!scenario_file || !scenario_file[0]) {
        return 0;
    }

    const bool relative = !path_looks_absolute(scenario_file);
    if (!GamestateIO::load_map(scenario_file, relative, false)) {
        return 0;
    }

    // ED4b: .map is terrain-only SoT — drop embedded scenario_events, then apply sidecar.
    g_scenario.events.clear_for_editor();
    editor_map_meta_load(scenario_file);

    prepare_map_for_editing();
    g_scenario.is_saved = true;
    return 1;
}

int game_file_editor_write_scenario(const char* scenario_file) {
    if (!scenario_file || !scenario_file[0]) {
        return 0;
    }

    scenario_editor_set_native_images(image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE),
                                      image_id_from_group(GROUP_EDITOR_BUILDING_NATIVE) + 2,
                                      image_id_from_group(GROUP_EDITOR_BUILDING_CROPS));

    int karmy = g_empire.init_distant_battle_travel_months(EMPIRE_OBJECT_KINGDOME_ARMY);
    g_scenario.distant_battle_set_kingdome_travel_months(karmy);

    int kenemy = g_empire.init_distant_battle_travel_months(EMPIRE_OBJECT_ENEMY_ARMY);
    g_scenario.distant_battle_set_enemy_travel_months(kenemy);

    // ED4b: strip request events from the map blob; persist them in *.meta.js instead.
    editor_requests_preserve_begin();

    bool ok = false;
    const bool relative = !(path_looks_absolute(scenario_file)
        || strncasecmp(scenario_file, "Maps/", 5) == 0
        || strncasecmp(scenario_file, "Maps\\", 5) == 0);
    ok = GamestateIO::write_map(scenario_file, relative);

    editor_requests_preserve_end();

    if (ok) {
        editor_map_meta_write(scenario_file);
        g_scenario.is_saved = true;
    }
    return ok ? 1 : 0;
}
