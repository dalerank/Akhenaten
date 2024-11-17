#include "destruction.h"

#include "building/building_house.h"
#include "city/message.h"
#include "city/population.h"
#include "city/city.h"
#include "figuretype/wall.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/random.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "sound/sound.h"

#include <core/random.h>
#include <string.h>

const vec2i destroy_on_fire_tiles[] = {         {0, 0},
                                        {1, 0}, {1, 1}, {0, 1}, 
                                {2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, 
                        {3, 0}, {3, 1}, {3, 2}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, 
                {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, 
        {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}};

static void destroy_on_fire(building* b, bool plagued) {
    game_undo_disable();
    b->fire_risk = 0;
    b->damage_risk = 0;
    if (b->house_size && b->house_population > 0) {
        city_population_remove_home_removed(b->house_population);
    }

    int was_tent = b->house_size && b->subtype.house_level <= HOUSE_STURDY_HUT;
    b->house_population = 0;
    b->house_size = 0;
    b->output_resource_first_id = RESOURCE_NONE;
    b->output_resource_second_id = RESOURCE_NONE;
    b->distance_from_entry = 0;
    b->clear_related_data();

    int waterside_building = 0;
    if (b->type == BUILDING_DOCK || b->type == BUILDING_FISHING_WHARF || b->type == BUILDING_SHIPWRIGHT) {
        waterside_building = 1;
    }

    int num_tiles;
    if (b->size >= 2 && b->size <= 5) {
        num_tiles = b->size * b->size;
    } else {
        if (b->house_size > 1) {
            num_tiles = b->house_size * b->house_size;
        } else {
            num_tiles = 0;
        }
    }

    map_building_tiles_remove(b->id, b->tile);
    unsigned int rand_int = random_short();
    if (map_terrain_is(b->tile, TERRAIN_WATER)) {
        b->state = BUILDING_STATE_DELETED_BY_GAME;
    } else {
        b->type = BUILDING_BURNING_RUIN;
        b->remove_figure(3);
        b->tax_income_or_storage = 0;
        b->fire_duration = (b->map_random_7bit & 7) + 1;
        b->fire_proof = 1;
        b->size = 1;
        b->has_plague = plagued;
        memset(&b->data, 0, sizeof(building::data));

        // FIXME: possible can't render image & fire animation
        unsigned char random = rand_int % 4;
        rand_int *= rand_int;
        int image_id = image_id_from_group(GROUP_TERRAIN_RUBBLE_GENERAL) + 9 * random;
        map_building_tiles_add(b->id, b->tile, 1, image_id, TERRAIN_BUILDING);
    }

    for (int tile = 1; tile < num_tiles; tile++) {
        tile2i shifted = b->tile.shifted(destroy_on_fire_tiles[tile].x, destroy_on_fire_tiles[tile].y);
        if (map_terrain_is(shifted, TERRAIN_WATER)) {
            continue;
        }

        // FIXME: possible can't render image & fire animation
        building* ruin = building_create(BUILDING_BURNING_RUIN, shifted, 0);
        unsigned char random = rand_int % 4;
        rand_int *= rand_int;
        int image_id = image_id_from_group(GROUP_TERRAIN_RUBBLE_GENERAL) + 9 * random;
        map_building_tiles_add(ruin->id, ruin->tile, 1, image_id, TERRAIN_BUILDING);
        ruin->fire_duration = (ruin->map_random_7bit & 7) + 1;
        b->remove_figure(3);
        ruin->fire_proof = 1;
        ruin->has_plague = plagued;
    }

    if (waterside_building) {
        map_routing_update_water();
    }
}

static void destroy_linked_parts(building* b, bool on_fire) {
    building* part = b;
    for (int i = 0; i < 99; i++) {
        if (part->prev_part_building_id <= 0) {
            break;
        }

        int part_id = part->prev_part_building_id;
        part = building_get(part_id);
        if (on_fire) {
            destroy_on_fire(part, false);
        } else {
            map_building_tiles_set_rubble(part_id, part->tile, part->size);
            part->state = BUILDING_STATE_RUBBLE;
        }
    }

    part = b;
    for (int i = 0; i < 99; i++) {
        part = part->next();
        if (part->id <= 0) {
            break;
        }

        if (on_fire) {
            destroy_on_fire(part, false);
        } else {
            map_building_tiles_set_rubble(part->id, part->tile, part->size);
            part->state = BUILDING_STATE_RUBBLE;
        }
    }
}

void building_destroy_by_collapse(building* b) {
    b = b->main();
    b->state = BUILDING_STATE_RUBBLE;
    map_building_tiles_set_rubble(b->id, b->tile, b->size);
    figure_create_explosion_cloud(b->tile, b->size);
    destroy_linked_parts(b, false);
    g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
}

void building_destroy_by_poof(building* b, bool clouds) {
    b = b->main();
    if (clouds) {
        figure_create_explosion_cloud(b->tile, b->size);
        g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
    }

    do {
        b->state = BUILDING_STATE_UNUSED;
        map_tiles_update_region_empty_land(true, b->tile, b->tile.shifted(b->size - 1, b->size - 1));
        if (b->next_part_building_id < 1) {
            return;
        }

        b = b->next();
    } while (true);
}

void building_destroy_by_fire(building* b) {
    b = b->main();
    destroy_on_fire(b, false);
    destroy_linked_parts(b, true);
    g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
}

void building_mark_plague(building* b) {
    b = b->main();
    b->disease_days = 30;
    b->has_plague = true;
    //destroy_on_fire(b, true);
}

void building_destroy_by_rioter(building* b) {
    b = b->main();
    destroy_on_fire(b, false);
}

int building_destroy_first_of_type(e_building_type type) {
    int i = building_id_first(type);
    if (i < MAX_BUILDINGS) {
        building* b = building_get(i);
        int grid_offset = b->tile.grid_offset();
        game_undo_disable();
        b->state = BUILDING_STATE_RUBBLE;
        map_building_tiles_set_rubble(i, b->tile, b->size);
        g_sound.play_effect(SOUND_EFFECT_EXPLOSION);
        map_routing_update_land();
        return grid_offset;
    }
    return 0;
}

void building_destroy_last_placed(void) {
    int highest_sequence = 0;
    building* last_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_CREATED || b->state == BUILDING_STATE_VALID) {
            if (b->creation_sequence_index > highest_sequence) {
                highest_sequence = b->creation_sequence_index;
                last_building = b;
            }
        }
    }
    if (last_building) {
        city_message_post(true, MESSAGE_ROAD_TO_ROME_BLOCKED, 0, last_building->tile.grid_offset());
        game_undo_disable();
        building_destroy_by_collapse(last_building);
        map_routing_update_land();
    }
}

void building_destroy_increase_enemy_damage(int grid_offset, int max_damage) {
    if (map_building_damage_increase(grid_offset) > max_damage) {
        building_destroy_by_enemy(tile2i(grid_offset));
    }
}

void building_destroy_by_enemy(tile2i tile) {
    int grid_offset = tile.grid_offset();
    int x = tile.x();
    int y = tile.y();
    int building_id = map_building_at(grid_offset);
    if (building_id > 0) {
        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID) {
            g_city.ratings.monument_building_destroyed(b->type);
            building_destroy_by_collapse(b);
        }
    } else {
        if (map_terrain_is(grid_offset, TERRAIN_WALL)) {
            figure_kill_tower_sentries_at(tile);
        }

        map_building_tiles_set_rubble(0, tile, 1);
    }
    figure_tower_sentry_reroute();
    map_tiles_update_area_walls(tile, 3);
    map_tiles_update_region_canals(x - 3, y - 3, x + 3, y + 3);
    map_routing_update_land();
    map_routing_update_walls();
}
