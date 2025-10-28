#include "earthquake.h"

#include "building/building.h"
#include "building/destruction.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/game.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/property.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "scenario/scenario.h"
#include "sound/effect.h"

struct eathquake_data_t {
    int game_year;
    int month;
    int state;
    int duration;
    int max_duration;
    int delay;
    int max_delay;
    struct {
        int x;
        int y;
    } expand[4];
};

eathquake_data_t g_eathquake_data;

void scenario_earthquake_init(void) {
    auto &data = g_eathquake_data;
    data.game_year = g_scenario.start_year + g_scenario.earthquake.year;
    data.month = 2 + (random_byte() & 7);
    switch (g_scenario.earthquake.severity) {
    default:
        data.max_duration = 0;
        data.max_delay = 0;
        break;
    case EARTHQUAKE_SMALL:
        data.max_duration = 25 + (random_byte() & 0x1f);
        data.max_delay = 10;
        break;
    case EARTHQUAKE_MEDIUM:
        data.max_duration = 100 + (random_byte() & 0x3f);
        data.max_delay = 8;
        break;
    case EARTHQUAKE_LARGE:
        data.max_duration = 250 + random_byte();
        data.max_delay = 6;
        break;
    }
    data.state = e_event_state_initial;
    for (int i = 0; i < 4; i++) {
        data.expand[i].x = g_scenario.earthquake_point.x();
        data.expand[i].y = g_scenario.earthquake_point.y();
    }
}

static int can_advance_earthquake_to_tile(int x, int y) {
    if (map_terrain_is(MAP_OFFSET(x, y), TERRAIN_ELEVATION | TERRAIN_ROCK | TERRAIN_WATER))
        return 0;
    else {
        return 1;
    }
}

static void advance_earthquake_to_tile(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int building_id = map_building_at(grid_offset);
    if (building_id) {
        building_get(building_id)->destroy_by_fire();
        int ruin_id = map_building_at(grid_offset);
        if (ruin_id) {
            building_get(ruin_id)->state = BUILDING_STATE_DELETED_BY_GAME;
            map_building_set(grid_offset, 0);
        }
    }
    map_terrain_set(grid_offset, 0);
    map_tiles_set_earthquake(x, y);
    map_tiles_gardens_update_all();
    map_tiles_update_all_roads();
    map_tiles_update_all_plazas();

    map_routing_update_land();
    map_routing_update_walls();

    figure_create_explosion_cloud(tile2i(x, y), 1);
}

void scenario_earthquake_process() {
    auto &data = g_eathquake_data;
    if (g_scenario.earthquake.severity == EARTHQUAKE_NONE || g_scenario.earthquake_point.x() == -1
        || g_scenario.earthquake_point.y() == -1)
        return;
    if (data.state == e_event_state_initial) {
        if (game.simtime.year == data.game_year && game.simtime.month == data.month) {
            data.state = e_event_state_in_progress;
            data.duration = 0;
            data.delay = 0;
            advance_earthquake_to_tile(data.expand[0].x, data.expand[0].y);
            messages::popup("message_earthquake", 0, MAP_OFFSET(data.expand[0].x, data.expand[0].y));
        }
    } else if (data.state == e_event_state_in_progress) {
        data.delay++;
        if (data.delay >= data.max_delay) {
            data.delay = 0;
            data.duration++;
            if (data.duration >= data.max_duration)
                data.state = e_event_state_finished;

            int dx, dy, index;
            switch (random_byte() & 0xf) {
            case 0:
                index = 0;
                dx = 0;
                dy = -1;
                break;
            case 1:
                index = 1;
                dx = 1;
                dy = 0;
                break;
            case 2:
                index = 2;
                dx = 0;
                dy = 1;
                break;
            case 3:
                index = 3;
                dx = -1;
                dy = 0;
                break;
            case 4:
                index = 0;
                dx = 0;
                dy = -1;
                break;
            case 5:
                index = 0;
                dx = -1;
                dy = 0;
                break;
            case 6:
                index = 0;
                dx = 1;
                dy = 0;
                break;
            case 7:
                index = 1;
                dx = 1;
                dy = 0;
                break;
            case 8:
                index = 1;
                dx = 0;
                dy = -1;
                break;
            case 9:
                index = 1;
                dx = 0;
                dy = 1;
                break;
            case 10:
                index = 2;
                dx = 0;
                dy = 1;
                break;
            case 11:
                index = 2;
                dx = -1;
                dy = 0;
                break;
            case 12:
                index = 2;
                dx = 1;
                dy = 0;
                break;
            case 13:
                index = 3;
                dx = -1;
                dy = 0;
                break;
            case 14:
                index = 3;
                dx = 0;
                dy = -1;
                break;
            case 15:
                index = 3;
                dx = 0;
                dy = 1;
                break;
            default:
                return;
            }
            int x = calc_bound(data.expand[index].x + dx, 0, g_scenario.map.width - 1);
            int y = calc_bound(data.expand[index].y + dy, 0, g_scenario.map.height - 1);
            if (can_advance_earthquake_to_tile(x, y)) {
                data.expand[index].x = x;
                data.expand[index].y = y;
                advance_earthquake_to_tile(x, y);
            }
        }
    }
}

int scenario_earthquake_is_in_progress(void) {
    auto &data = g_eathquake_data;
    return data.state == e_event_state_in_progress;
}

void scenario_earthquake_save_state(buffer* buf) {
    auto &data = g_eathquake_data;
    buf->write_i32(data.game_year);
    buf->write_i32(data.month);
    buf->write_i32(data.state);
    buf->write_i32(data.duration);
    buf->write_i32(data.max_duration);
    buf->write_i32(data.max_delay);
    buf->write_i32(data.delay);
    for (int i = 0; i < 4; i++) {
        buf->write_i32(data.expand[i].x);
        buf->write_i32(data.expand[i].y);
    }
}

void scenario_earthquake_load_state(buffer* buf) {
    auto &data = g_eathquake_data;
    data.game_year = buf->read_i32();
    data.month = buf->read_i32();
    data.state = buf->read_i32();
    data.duration = buf->read_i32();
    data.max_duration = buf->read_i32();
    data.max_delay = buf->read_i32();
    data.delay = buf->read_i32();
    for (int i = 0; i < 4; i++) {
        data.expand[i].x = buf->read_i32();
        data.expand[i].y = buf->read_i32();
    }
}

static void set_earthquake_image(int grid_offset) {
    tile2i tile(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(tile)) {
        const terrain_image img = map_image_context_get_earthquake(grid_offset);
        if (img.is_valid) {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_EARTHQUAKE) + img.group_offset + img.item_offset);
        } else {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_EARTHQUAKE));
        }
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

void update_earthquake_tile(int grid_offset) {
    tile2i tile(grid_offset);

    if (map_terrain_is(grid_offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(tile)) {
        map_terrain_add(grid_offset, TERRAIN_ROCK);
        map_property_mark_plaza_or_earthquake(grid_offset);
        map_tiles_foreach_region_tile(tile.shifted(-1, -1), tile.shifted(1, 1), set_earthquake_image);
    }
}

void map_tiles_update_all_earthquake(void) {
    map_tiles_foreach_map_tile(update_earthquake_tile);
}

void map_tiles_set_earthquake(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    // earthquake: terrain = rock && bitfields = plaza
    map_terrain_add(grid_offset, TERRAIN_ROCK);
    map_property_mark_plaza_or_earthquake(grid_offset);

    map_tiles_foreach_region_tile(tile2i(x - 1, y - 1), tile2i(x + 1, y + 1), set_earthquake_image);
}


