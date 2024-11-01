#include "building/building_house.h"
#include "building/destruction.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/finance.h"
#include "city/message.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/sentiment.h"
#include "city/map.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/formation_enemy.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/tutorial.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "scenario/scenario.h"

static const int CRIMINAL_OFFSETS[] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1};

void figure::protestor_action() {
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(64);
    //    cart_image_id = 0;
    //    if (action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();

    wait_ticks++;
    if (wait_ticks > 200) {
        poof();
        anim.frame = 0;
    }

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim.frame / 4] + 104;
    }
}

void figure::mugger_action() {
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(32);
    //    cart_image_id = 0;
    //    if (action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();
    switch (action_state) {
    case FIGURE_ACTION_120_MUGGER_CREATED:
    {
        // if city has palace, all mugger will go there
        wait_ticks = 0;
        int senate_id = g_city.buildings.get_palace_id();
        building* b_dst = building_get(senate_id);
        tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
        if (road_tile.valid()) {
            destination_tile = road_tile;
            set_destination(senate_id);
            advance_action(FIGURE_ACTION_121_MUGGER_MOVING);
            route_remove();
        } else {
            advance_action(FIGURE_ACTION_123_MUGGER_LEAVING);
        }
    }
    break;

    case FIGURE_ACTION_123_MUGGER_LEAVING:
    {
        wait_ticks = 0;
        tile2i exit = g_city.map.exit_point;
        if (do_goto(exit, TERRAIN_USAGE_ANY)) {
            poof();
        }
    }
    break;

    case FIGURE_ACTION_121_MUGGER_MOVING:
    {
        move_ticks(1);
        wait_ticks = 0;
        if (direction == DIR_FIGURE_NONE) {
            poof();
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            action_state = FIGURE_ACTION_120_RIOTER_CREATED;
            route_remove();
        } else if (direction == DIR_FIGURE_ATTACK) {
            if (anim.frame > 12) {
                anim.frame = 0;
            }
        }
    }
    break;

    case FIGURE_ACTION_122_MUGGER_HIDE:
        poof();
    break;

    }

    wait_ticks++;
    if (wait_ticks > 200) {
        poof();
        anim.frame = 0;
    }

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim.frame / 2] + 104;
    }
}

void figure::rioter_action() {
    g_city.figures_add_rioter(!targeted_by_figure_id);
    //    terrain_usage = TERRAIN_USAGE_ENEMY;
    //    max_roam_length = 480;
    //    cart_image_id = 0;
    //    is_ghost = false;
    switch (action_state) {
    case FIGURE_ACTION_120_RIOTER_CREATED:
        //            figure_image_increase_offset(32);
        wait_ticks++;
        if (wait_ticks >= 160) {
            advance_action(FIGURE_ACTION_121_RIOTER_MOVING);
            int x_tile, y_tile;
            int building_id = formation_rioter_get_target_building(&x_tile, &y_tile);
            if (building_id) {
                destination_tile.set(x_tile, y_tile);
                //                    destination_tile.x() = x_tile;
                //                    destination_tile.y() = y_tile;
                set_destination(building_id);
                route_remove();
            } else {
                poof();
            }
        }
        break;
    case FIGURE_ACTION_121_RIOTER_MOVING:
        //            figure_image_increase_offset(12);
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            int x_tile, y_tile;
            int building_id = formation_rioter_get_target_building(&x_tile, &y_tile);
            if (building_id) {
                destination_tile.set(x_tile, y_tile);
                //                    destination_tile.x() = x_tile;
                //                    destination_tile.y() = y_tile;
                set_destination(building_id);
                route_remove();
            } else {
                poof();
            }
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            action_state = FIGURE_ACTION_120_RIOTER_CREATED;
            route_remove();
        } else if (direction == DIR_FIGURE_ATTACK) {
            if (anim.frame > 12) {
                anim.frame = 0;
            }
        }
        break;
    }
    int dir;
    if (direction == DIR_FIGURE_ATTACK) {
        dir = attack_direction;
    } else if (direction < 8) {
        dir = direction;
    } else {
        dir = previous_tile_direction;
    }
    dir = figure_image_normalize_direction(dir);

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_DEATH) + figure_image_corpse_offset();
    } else if (direction == DIR_FIGURE_ATTACK) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_ATTACK) + CRIMINAL_OFFSETS[anim.frame % 16];
    } else if (action_state == FIGURE_ACTION_121_RIOTER_MOVING) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_WALK) + dir + 8 * anim.frame;
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_ATTACK) + CRIMINAL_OFFSETS[anim.frame / 2];
    }
}

int figure::figure_rioter_collapse_building() {
    for (int dir = 0; dir < 8; dir += 2) {
        int grid_offset = tile.grid_offset() + map_grid_direction_delta(dir);
        if (!map_building_at(grid_offset))
            continue;

        building* b = building_at(grid_offset);
        switch (b->type) {
        case BUILDING_STORAGE_ROOM:
        case BUILDING_STORAGE_YARD:
        case BUILDING_FORT_GROUND:
        case BUILDING_FORT_CHARIOTEERS:
        case BUILDING_FORT_INFANTRY:
        case BUILDING_FORT_ARCHERS:
        case BUILDING_BURNING_RUIN:
            continue;

        default:
            ; // nothing
        }

        if (b->house_size && b->subtype.house_level < HOUSE_MODEST_HOMESTEAD) {
            continue;
        }

        city_message_apply_sound_interval(MESSAGE_CAT_RIOT_COLLAPSE);
        city_message_post(false, MESSAGE_DESTROYED_BUILDING, b->type, grid_offset);
        city_message_increase_category_count(MESSAGE_CAT_RIOT_COLLAPSE);
        building_destroy_by_rioter(b);
        action_state = FIGURE_ACTION_120_RIOTER_CREATED;
        wait_ticks = 0;
        direction = dir;
        return 1;
    }
    return 0;
}
