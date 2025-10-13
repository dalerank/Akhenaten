#include "figuretype/figure_rioter.h"

#include "figure/service.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "building/building_house.h"
#include "grid/road_access.h"
#include "js/js_game.h"

static const int CRIMINAL_OFFSETS[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1 };

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_rioter);

void figure_rioter::figure_action() {
    g_city.figures_add_rioter(!base.targeted_by_figure_id);
    //    terrain_usage = TERRAIN_USAGE_ENEMY;
    //    max_roam_length = 480;
    //    cart_image_id = 0;
    //    is_ghost = false;
    switch (action_state()) {
    case FIGURE_ACTION_120_RIOTER_CREATED:
        //            figure_image_increase_offset(32);
        base.wait_ticks++;
        if (base.wait_ticks >= 160) {
            advance_action(FIGURE_ACTION_121_RIOTER_MOVING);
            int x_tile, y_tile;
            int building_id = formation_rioter_get_target_building(&x_tile, &y_tile);
            if (building_id) {
                base.destination_tile = { x_tile, y_tile };
                set_destination(building_id);
                route_remove();
            } else {
                poof();
            }
        }
        break;
    case FIGURE_ACTION_121_RIOTER_MOVING:
        //            figure_image_increase_offset(12);
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            int x_tile, y_tile;
            int building_id = formation_rioter_get_target_building(&x_tile, &y_tile);
            if (building_id) {
                base.destination_tile = { x_tile, y_tile };
                set_destination(building_id);
                route_remove();
            } else {
                poof();
            }
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action( FIGURE_ACTION_120_RIOTER_CREATED );
            route_remove();
        } else if (direction() == DIR_FIGURE_ATTACK) {
            if (base.animctx.frame > 12) {
                base.animctx.frame = 0;
            }
        }
        break;
    }

    int dir;
    if (direction() == DIR_FIGURE_ATTACK) {
        dir = base.attack_direction;
    } else if (direction() < 8) {
        dir = direction();
    } else {
        dir = base.previous_tile_direction;
    }
    dir = base.figure_image_normalize_direction(dir);
}

int figure_rioter::collapse_building() {
    for (int dir = 0; dir < 8; dir += 2) {
        int grid_offset = tile().grid_offset() + map_grid_direction_delta(dir);
        if (!map_building_at(grid_offset))
            continue;

        building *b = building_at(grid_offset);
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

        auto house = b->dcast_house();
        if (house && house->house_level() > 0) {
            if (house->house_level() < HOUSE_MODEST_HOMESTEAD) {
                continue;
            }
        }

        city_message_apply_sound_interval(MESSAGE_CAT_RIOT_COLLAPSE);
        messages::popup(MESSAGE_DESTROYED_BUILDING, b->type, grid_offset);
        city_message_increase_category_count(MESSAGE_CAT_RIOT_COLLAPSE);

        auto bmain = b->main();
        bmain->destroy_by_fire();
        
        advance_action( FIGURE_ACTION_120_RIOTER_CREATED );
        base.wait_ticks = 0;
        base.direction = dir;
        return 1;
    }
    return 0;
}

void figure_rioter::update_animation() {
    xstring animkey = animkeys().walk;

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:  animkey = animkeys().death; break;
    case ACTION_122_RIOTER_ATTACK: animkey = animkeys().attack; break;
    }

    image_set_animation(animkey);
}