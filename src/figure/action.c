#include <cmath>
#include <map/terrain.h>
#include "action.h"

#include "city/entertainment.h"
#include "city/figures.h"
#include "figure/figure.h"
#include "figuretype/animal.h"
#include "figuretype/cartpusher.h"
#include "figuretype/crime.h"
#include "figuretype/docker.h"
#include "figuretype/editor.h"
#include "figuretype/enemy.h"
#include "figuretype/entertainer.h"
#include "figuretype/maintenance.h"
#include "figuretype/market.h"
#include "figuretype/migrant.h"
#include "figuretype/missile.h"
#include "figuretype/native.h"
#include "figuretype/service.h"
#include "figuretype/soldier.h"
#include "figuretype/trader.h"
#include "figuretype/wall.h"
#include "figuretype/water.h"
#include "core/game_environment.h"
#include "map/road_access.h"
#include "core/image_group.h"

typedef struct {
    char speed_mult;
    char terrain_usage;
    short max_roam_length;
    int base_image_group;
} figure_action_property;

static figure_action_property action_properties_lookup[] = {
        {0, 0,                     0,      0},  //FIGURE_NONE = 0,
        {1, TERRAIN_USAGE_ANIMAL,     0,      GROUP_FIGURE_MIGRANT},  //FIGURE_IMMIGRANT = 1,
        {1, TERRAIN_USAGE_ANIMAL,     0,      GROUP_FIGURE_HOMELESS},  //FIGURE_EMIGRANT = 2,
        {1, TERRAIN_USAGE_PREFER_ROADS,     0,      GROUP_FIGURE_HOMELESS},  //FIGURE_HOMELESS = 3,
        {1, TERRAIN_USAGE_ROADS,   0,      GROUP_FIGURE_CARTPUSHER},  //FIGURE_CART_PUSHER = 4,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_LABOR_SEEKER},  //FIGURE_LABOR_SEEKER = 5,
        {1, TERRAIN_USAGE_ANY,     0,      GROUP_FIGURE_EXPLOSION},  //FIGURE_EXPLOSION = 6,
        {1, TERRAIN_USAGE_ROADS,   512,    GROUP_FIGURE_TAX_COLLECTOR},  //FIGURE_TAX_COLLECTOR = 7,
        {1, TERRAIN_USAGE_ROADS,   640,    GROUP_FIGURE_ENGINEER},  //FIGURE_ENGINEER = 8,
        {1, TERRAIN_USAGE_ROADS,   0,      GROUP_FIGURE_CARTPUSHER},  //FIGURE_WAREHOUSEMAN = 9,
        {1, TERRAIN_USAGE_ROADS,   640,    GROUP_FIGURE_PREFECT},  //FIGURE_PREFECT = 10,
        {1, TERRAIN_USAGE_ANY,     0,      GROUP_FIGURE_ARCHER_PH},  //FIGURE_FORT_JAVELIN = 11,
        {1, TERRAIN_USAGE_ANY,     0,      GROUP_FIGURE_CHARIOTEER_PH},  //FIGURE_FORT_MOUNTED = 12,
        {1, TERRAIN_USAGE_ANY,     0,      GROUP_FIGURE_INFANTRY_PH},  //FIGURE_FORT_LEGIONARY = 13,
        {1, TERRAIN_USAGE_ANY,     0,      0},  //FIGURE_FORT_STANDARD = 14,
        {1, TERRAIN_USAGE_ROADS,   512,    GROUP_FIGURE_ACTOR},  //FIGURE_ACTOR = 15,
        {1, TERRAIN_USAGE_ROADS,   512,    GROUP_FIGURE_GLADIATOR},  //FIGURE_GLADIATOR = 16,
        {1, TERRAIN_USAGE_ROADS,   512,    GROUP_FIGURE_LION_TAMER},  //FIGURE_LION_TAMER = 17,
        {1, TERRAIN_USAGE_ROADS,   512,    GROUP_FIGURE_CHARIOTEER},  //FIGURE_CHARIOTEER = 18,
        {1, TERRAIN_USAGE_ROADS,   0,      GROUP_FIGURE_TRADE_CARAVAN},  //FIGURE_TRADE_CARAVAN = 19,
        {1, TERRAIN_USAGE_ANY,     0,      0},  //FIGURE_TRADE_SHIP = 20,
        {1, TERRAIN_USAGE_ROADS,   0,      GROUP_FIGURE_TRADE_CARAVAN_DONKEY},  //FIGURE_TRADE_CARAVAN_DONKEY = 21,
        {1, TERRAIN_USAGE_ROADS,   0,      GROUP_FIGURE_CRIMINAL},  //FIGURE_PROTESTER = 22,
        {1, TERRAIN_USAGE_ROADS,   0,      GROUP_FIGURE_CRIMINAL},  //FIGURE_CRIMINAL = 23,
        {1, TERRAIN_USAGE_ENEMY,   480,    GROUP_FIGURE_CRIMINAL},  //FIGURE_RIOTER = 24,
        {1, TERRAIN_USAGE_ANY,     0,      0},  //FIGURE_FISHING_BOAT = 25,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_MARKET_LADY_2},  //FIGURE_MARKET_TRADER = 26,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_PRIEST},  //FIGURE_PRIEST = 27,
        {1, TERRAIN_USAGE_ROADS,   192,    GROUP_FIGURE_SCHOOL_CHILD},   //FIGURE_SCHOOL_CHILD = 28,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_TEACHER_LIBRARIAN},  //FIGURE_TEACHER = 29,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_TEACHER_LIBRARIAN},  //FIGURE_LIBRARIAN = 30,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_BARBER},  //FIGURE_BARBER = 31,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_BATHHOUSE_WORKER},  //FIGURE_BATHHOUSE_WORKER = 32,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_DOCTOR_SURGEON},  //FIGURE_DOCTOR = 33,
        {1, TERRAIN_USAGE_ROADS,   384,    GROUP_FIGURE_MORTUARY},   //FIGURE_SURGEON = 34,
        {1, TERRAIN_USAGE_ROADS,   384,    0},   //FIGURE_WORKER = 35,
        {1, TERRAIN_USAGE_ANY,     0,      0},   //FIGURE_MAP_FLAG = 36,
        {1, TERRAIN_USAGE_ANY,     0,      0}, //FIGURE_FLOTSAM = 37,
        {1, TERRAIN_USAGE_ROADS,   0,      0},    //FIGURE_DOCKER = 38,
        {1, TERRAIN_USAGE_ROADS,   800,    0},   //FIGURE_MARKET_BUYER = 39,
        {1, TERRAIN_USAGE_ROADS,   128,    GROUP_FIGURE_PATRICIAN},   //FIGURE_PATRICIAN = 40,
        {1, TERRAIN_USAGE_ANY,     800,    0},   //FIGURE_INDIGENOUS_NATIVE = 41,
        {1, TERRAIN_USAGE_WALLS,   800,    0},   //FIGURE_TOWER_SENTRY = 42,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY43_SPEAR = 43,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY44_SWORD = 44,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY45_SWORD = 45,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY46_CAMEL = 46,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY47_ELEPHANT = 47,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY48_CHARIOT = 48,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},  //FIGURE_ENEMY49_FAST_SWORD = 49,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},  //FIGURE_ENEMY50_SWORD = 50,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},  //FIGURE_ENEMY51_SPEAR = 51,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY52_MOUNTED_ARCHER = 52,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY53_AXE = 53,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY54_GLADIATOR = 54,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY_CAESAR_JAVELIN = 55,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY_CAESAR_MOUNTED = 56,
        {1, TERRAIN_USAGE_ENEMY,     0,      0},   //FIGURE_ENEMY_CAESAR_LEGIONARY = 57,
        {1, TERRAIN_USAGE_ROADS,   0,      0},   //FIGURE_NATIVE_TRADER = 58,
        {1, TERRAIN_USAGE_ANY,     0,   0},   //FIGURE_ARROW = 59,
        {1, TERRAIN_USAGE_ANY,     0,   0},   //FIGURE_JAVELIN = 60,
        {1, TERRAIN_USAGE_ANY,     0,   0},   //FIGURE_BOLT = 61,
        {1, TERRAIN_USAGE_ANY,     0,   0},   //FIGURE_BALLISTA = 62,
        {1, TERRAIN_USAGE_ANY,     0,   0},  //FIGURE_CREATURE = 63,
        {1, TERRAIN_USAGE_ROADS,   192, GROUP_FIGURE_MISSIONARY},    //FIGURE_MISSIONARY = 64,
        {1, TERRAIN_USAGE_ANY,     0,   GROUP_FIGURE_SEAGULLS},   //FIGURE_FISH_GULLS = 65,
        {1, TERRAIN_USAGE_ROADS,   0,   GROUP_FIGURE_DELIVERY_BOY},  //FIGURE_DELIVERY_BOY = 66,
        {1, TERRAIN_USAGE_ANY,     0,   0},  //FIGURE_SHIPWRECK = 67,
        {2, TERRAIN_USAGE_ANIMAL,  0,   GROUP_FIGURE_SHEEP},  //FIGURE_SHEEP = 68,
        {2, TERRAIN_USAGE_ANIMAL,  0,   GROUP_FIGURE_OSTRICH},  //FIGURE_WOLF = 69,
        {2, TERRAIN_USAGE_ANIMAL,  0,   GROUP_FIGURE_ZEBRA},  //FIGURE_ZEBRA = 70,
        {1, TERRAIN_USAGE_ANY,     0,   0},  //FIGURE_SPEAR = 71,
        {1, TERRAIN_USAGE_ANY,     0,   0},  //FIGURE_HIPPODROME_HORSES = 72,

        // PHARAOH

        {1, TERRAIN_USAGE_ANIMAL,     0,   GROUP_FIGURE_HUNTER},  // 73
        {1, TERRAIN_USAGE_ANY,     0,   GROUP_FIGURE_HUNTER_ARROW},  // 74
        {1, TERRAIN_USAGE_ANY,     0,   0},  // 75
        {1, TERRAIN_USAGE_ANY,     0,   0},  // 76
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 77
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 78
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 79
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 80
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 81
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 82
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 83
        {1, TERRAIN_USAGE_ANIMAL,  0,      GROUP_FIGURE_HIPPO},  // 84 hippo
        {1, TERRAIN_USAGE_ANY,     0,      GROUP_FIGURE_WORKER_PH},  // 85
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 86
        {1, TERRAIN_USAGE_ROADS,   640,    GROUP_FIGURE_WATER_CARRIER},  // 87 water carrier
        {1, TERRAIN_USAGE_ROADS,   640,    GROUP_FIGURE_POLICEMAN},  // 88 policeman
        {1, TERRAIN_USAGE_ROADS,   800,    GROUP_FIGURE_MAGISTRATE},  // 89 magistrate
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 90
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 91
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 92
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 93
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 94
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 95
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 96
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 97
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 98
        {1, TERRAIN_USAGE_ANY,     0,      0},  // 99
        {1, TERRAIN_USAGE_ROADS,   0,      0},  // 100
};

#include "core/image.h"
#include "map/building.h"
#include "map/grid.h"

bool is_coords_within_range(int x, int y, int b_x, int b_y, int size, int radius) {
    int min_x = b_x - radius;
    int min_y = b_y - radius;
    int max_x = b_x + size - 1 + radius;
    int max_y = b_y + size - 1 + radius;

    if (x >= min_x && x <= max_x && y >= min_y && y <= max_y)
        return true;
    return false;
}

void figure::advance_action(short NEXT_ACTION) {
    if (NEXT_ACTION == 0)
        poof();
    else
        action_state = NEXT_ACTION;
}
bool figure::do_roam(int terrainchoice, short NEXT_ACTION) {
    terrain_usage = terrainchoice;
    if (!roam_length)
        init_roaming();
    roam_length++;
    if (roam_length >= max_roam_length) {
        destination_x = 0;
        destination_y = 0;
        destination_building_id = 0;
        roam_length = 0;
        route_remove();
        advance_action(NEXT_ACTION);
        return true;
    } else
        roam_ticks(speed_multiplier);
    return false;
}
bool figure::do_goto(int x, int y, int terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    terrain_usage = terrainchoice;
    if (use_cross_country)
        terrain_usage = TERRAIN_USAGE_ANY;

    // refresh routing if destination is different
    if (destination_x != x || destination_y != y)
        route_remove();

    // set up destination and move!!!
    if (use_cross_country) {
            set_cross_country_destination(x, y);
        if (move_ticks_cross_country(1) == 1) {
            advance_action(NEXT_ACTION);
            return true;
        }
    }
    else {
        destination_x = x;
        destination_y = y;
        move_ticks(speed_multiplier);
    }

    // check if destination is reached/figure is lost/etc.
    if (direction == DIR_FIGURE_AT_DESTINATION) {
        advance_action(NEXT_ACTION);
        direction = previous_tile_direction;
//        destination_building_id = 0;
        return true;
    }
    if (direction == DIR_FIGURE_REROUTE)
        route_remove();
    if (direction == DIR_FIGURE_LOST)
        advance_action(FAIL_ACTION);
    return false;
}
bool figure::do_gotobuilding(int destid, bool stop_at_road, int terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    int x, y;
    building *dest = building_get(destid);
    if (dest->state != BUILDING_STATE_VALID)
        advance_action(FAIL_ACTION);
    if (stop_at_road) {
        bool found_road = false;
        bool already_there = false;
//        if (!destination_x && !destination_y) {
            if (dest->type == BUILDING_WAREHOUSE || dest->type == BUILDING_WAREHOUSE_SPACE) {
                building *main = building_main(dest);
                if (terrainchoice == TERRAIN_USAGE_ROADS)
                    found_road = map_closest_reachable_road_within_radius(main->x, main->y, 3, 1, &x, &y);
                if (!found_road)
                    found_road = map_closest_road_within_radius(main->x, main->y, 3, 1, &x, &y);
                if (found_road && is_coords_within_range(tile_x, tile_y, main->x, main->y, 3, 1)) {
                    x = tile_x;
                    y = tile_y;
                }
            } else {
                if (terrainchoice == TERRAIN_USAGE_ROADS)
                    found_road = map_closest_reachable_road_within_radius(dest->x, dest->y, dest->size, 1, &x, &y);
                if (!found_road) {
                    if (building_is_house(dest->type))
                        found_road = map_closest_road_within_radius(dest->x, dest->y, dest->size, 2, &x, &y);
                    else
                        found_road = map_closest_road_within_radius(dest->x, dest->y, dest->size, 1, &x, &y);
                }
                if (found_road && is_coords_within_range(tile_x, tile_y, dest->x, dest->y, dest->size, 1)) {
                    x = tile_x;
                    y = tile_y;
                }
            }
//        } else {
//            found_road = true;
//            x = destination_x;
//            y = destination_y;
//        }
        // found any road...?
        if (found_road) {
            return do_goto(x, y, terrainchoice, NEXT_ACTION, FAIL_ACTION);
        } else {
            if (terrainchoice == TERRAIN_USAGE_ROADS && !use_cross_country)
                advance_action(FAIL_ACTION); // poof dude!!!
            else
                advance_action(NEXT_ACTION); // don't poof if it's not *requiring* roads, was just looking for one
        }
    } else
        return do_goto(dest->x, dest->y, terrainchoice, NEXT_ACTION, FAIL_ACTION); // go into building **directly**
}
bool figure::do_returnhome(int terrainchoice, short NEXT_ACTION) {
    return do_gotobuilding(building_id, true, terrainchoice, NEXT_ACTION);
}
bool figure::do_exitbuilding(bool invisible, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = 1;
    if (invisible)
        is_ghost = 1;
    return do_gotobuilding(building_id, true, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}
bool figure::do_enterbuilding(bool invisible, int buildid, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = 1;
    if (invisible)
        is_ghost = 1;
    return do_gotobuilding(buildid, false, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}

void figure::action_perform() {
//    return;
    if (state) {
        if (targeted_by_figure_id) {
            figure *attacker = figure_get(targeted_by_figure_id);
            if (attacker->state != FIGURE_STATE_ALIVE)
                targeted_by_figure_id = 0;
            if (attacker->target_figure_id != id)
                targeted_by_figure_id = 0;
        }

        //////////////

        // reset values like cart image & max roaming length
        cart_image_id = 0;
        max_roam_length = 0;
        use_cross_country = 0;
        is_ghost = 0;

        // base lookup data
        auto action_properties = action_properties_lookup[type];
        if (action_properties.terrain_usage != -1)
            terrain_usage = action_properties.terrain_usage;
        max_roam_length = action_properties.max_roam_length;
        speed_multiplier = action_properties.speed_mult;
        image_set_animation(action_properties.base_image_group);

        // check for building being alive (at the start of the action)
        building *b = building_get(building_id);
        building *b_imm = building_get(immigrant_building_id); // todo: get rid of this
        figure *leader = figure_get(leading_figure_id);
        switch (type) {
            case FIGURE_IMMIGRANT:
//                if (b_imm->state != BUILDING_STATE_VALID || b_imm->immigrant_figure_id != id || !b_imm->house_size)
//                    return poof();
                break;
            case FIGURE_ENGINEER:
            case FIGURE_PREFECT:
            case FIGURE_POLICEMAN:
            case FIGURE_MAGISTRATE:
            case FIGURE_WORKER:
            case FIGURE_MARKET_TRADER:
            case FIGURE_NATIVE_TRADER:
            case FIGURE_TAX_COLLECTOR:
            case FIGURE_TOWER_SENTRY:
            case FIGURE_MISSIONARY:
//            case FIGURE_ACTOR:
//            case FIGURE_GLADIATOR:
//            case FIGURE_LION_TAMER:
//            case FIGURE_CHARIOTEER:
            case FIGURE_BATHHOUSE_WORKER:
            case FIGURE_DOCTOR:
            case FIGURE_SURGEON:
            case FIGURE_BARBER:
            case FIGURE_WATER_CARRIER:
            case FIGURE_PRIEST:
                if (b->state != BUILDING_STATE_VALID || b->figure_id != id)
                    poof();
                break;
            case FIGURE_HUNTER:
                if (b->state != BUILDING_STATE_VALID)
                    poof();
                break;
            case FIGURE_CART_PUSHER:
                if (destination_building_id)
                    break;
                if (!building_is_floodplain_farm(b) && b->state != BUILDING_STATE_VALID || b->figure_id != id)
                    poof();
                break;
            case FIGURE_WAREHOUSEMAN:
                if (destination_building_id)
                    break;
                if (b->state != BUILDING_STATE_VALID || b->figure_id != id)
                    poof();
                break;
            case FIGURE_LABOR_SEEKER:
            case FIGURE_MARKET_BUYER:
                if (b->state != BUILDING_STATE_VALID || b->figure_id2 != id)
                    poof();
                break;
            case FIGURE_DELIVERY_BOY:
            case FIGURE_TRADE_CARAVAN_DONKEY:
                if (leading_figure_id <= 0 || leader->action_state == FIGURE_ACTION_149_CORPSE)
                    poof();
                if (leader->is_ghost)
                    is_ghost = 1;
                break;
        }

        // common action states handling
        switch (action_state) {
            case FIGURE_ACTION_150_ATTACK:
                figure_combat_handle_attack(); break;
            case FIGURE_ACTION_149_CORPSE:
                figure_combat_handle_corpse(); break;
            case FIGURE_ACTION_125_ROAMING:
            case ACTION_1_ROAMING:
                if (type == FIGURE_IMMIGRANT || type == FIGURE_EMIGRANT || type == FIGURE_HOMELESS)
                    break;
                do_roam();
                break;
            case FIGURE_ACTION_126_ROAMER_RETURNING:
            case ACTION_2_ROAMERS_RETURNING:
                if (type == FIGURE_IMMIGRANT || type == FIGURE_EMIGRANT || type == FIGURE_HOMELESS)
                    break;
                do_returnhome();
                break;
        }
        if (state == FIGURE_STATE_DYING)
           figure_combat_handle_corpse();
        if (terrain_usage == TERRAIN_USAGE_ROADS && !map_terrain_is(grid_offset_figure, TERRAIN_ROAD))
            if (action_state == ACTION_1_ROAMING || action_state == FIGURE_ACTION_125_ROAMING || destination_building_id == 0)
                poof();

        ////////////

        switch (type) {
            case 1: immigrant_action();                 break;
            case 2: emigrant_action();                  break;
            case 3: homeless_action();                  break;
            case 4: cartpusher_action();                break;
//            case 5: common_action(12, GROUP_FIGURE_LABOR_SEEKER); break;
            case 6: explosion_cloud_action();           break;
            case 7: tax_collector_action();             break;
            case 8: engineer_action();                  break;
            case 9: warehouseman_action();              break; // warehouseman_action !!!!
            case 10: prefect_action();                  break; //10
            case 11: //soldier_action();                  break;
            case 12: //soldier_action();                  break;
            case 13: soldier_action();                  break;
            case 14: military_standard_action();        break;
            case 15: //entertainer_action();              break;
            case 16: //entertainer_action();              break;
            case 17: //entertainer_action();              break;
            case 18: entertainer_action();              break;
            case 19: trade_caravan_action();            break;
            case 20: trade_ship_action();               break; //20
            case 21: trade_caravan_donkey_action();     break;
            case 22: protestor_action();                break;
            case 23: criminal_action();                 break;
            case 24: rioter_action();                   break;
            case 25: fishing_boat_action();             break;
            case 26: market_trader_action();            break;
            case 27: priest_action();                   break;
//            case 27: common_action(12, GROUP_FIGURE_PRIEST); break;
            case 28: school_child_action();             break;
//            case 29: common_action(12, GROUP_FIGURE_TEACHER_LIBRARIAN); break;
//            case 30: common_action(12, GROUP_FIGURE_TEACHER_LIBRARIAN); break; //30
//            case 31: common_action(12, GROUP_FIGURE_BARBER); break;
//            case 32: common_action(12, GROUP_FIGURE_BATHHOUSE_WORKER); break;
            case 33: //doctor_action(); break;
//            case 34: common_action(12, GROUP_FIGURE_DOCTOR_SURGEON); break;
//            case 35: worker_action();                   break;
            case 36: editor_flag_action();              break;
            case 37: flotsam_action();                  break;
            case 38: docker_action();                   break;
            case 39: market_buyer_action();             break;
//            case 40: patrician_action();                break; //40
            case 41: indigenous_native_action();        break;
            case 42: tower_sentry_action();             break;
            case 43: enemy43_spear_action();            break;
            case 44: enemy44_sword_action();            break;
            case 45: enemy45_sword_action();            break;
            case 46: enemy_camel_action();              break;
            case 47: enemy_elephant_action();           break;
            case 48: enemy_chariot_action();            break;
            case 49: enemy49_fast_sword_action();       break;
            case 50: enemy50_sword_action();            break; //50
            case 51: enemy51_spear_action();            break;
            case 52: enemy52_mounted_archer_action();   break;
            case 53: enemy53_axe_action();              break;
            case 54: enemy_gladiator_action();          break;
//                no_action();                            break;
//                no_action();                            break;
            case 57: enemy_caesar_legionary_action();   break;
            case 58: native_trader_action();            break;
            case 59: arrow_action();                    break;
            case 60: javelin_action();                  break; //60
            case 61: bolt_action();                     break;
            case 62: ballista_action();                 break;
//                no_action();                            break;
//            case 64: missionary_action();               break;
            case 65: seagulls_action();                 break;
            case 66: delivery_boy_action();             break;
            case 67: shipwreck_action();                break;
            case 68: sheep_action();                    break;
            case 69:
                if (GAME_ENV == ENGINE_ENV_C3)
                    wolf_action();
                else
                    ostrich_action();                   break;
            case 70: zebra_action();                    break; //70
            case 71: spear_action();                    break;
            case 72: hippodrome_horse_action();         break;
            // PHARAOH vvvv
            case 73: hunter_action();                   break;
            case 74: arrow_action();                    break;
            case 84: hippo_action();                    break;
            case 85: worker_action();                   break;
            case 87: water_carrier_action();            break;
            case 88: policeman_action();                break;
            case 89: magistrate_action();               break;
            default:
                break;
        }

        // poof if LOST
//        if (direction == DIR_FIGURE_LOST)
//            poof();

        // if DEAD, delete figure
        if (state == FIGURE_STATE_DEAD)
            return figure_delete_UNSAFE();

        // advance sprite offset
        figure_image_update();
    }
}

void figure_action_handle(void) {
//    return;
    city_figures_reset();
    city_entertainment_set_hippodrome_has_race(0);
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++)
        figure_get(i)->action_perform();
}
