#include "action.h"

#include "grid/terrain.h"

#include "city/entertainment.h"
#include "city/figures.h"
#include "core/profiler.h"
#include "figure/figure.h"
#include "graphics/image_groups.h"
#include "grid/road_access.h"

#include <algorithm>

struct figure_action_property {
    char speed_mult;
    char terrain_usage;
    short max_roam_length;
    int base_image_collection;
    int base_image_group;
};

static figure_action_property action_properties_lookup[] = {
  {0, 0, 0, 0, 0},                                                       // FIGURE_NONE = 0,
  {1, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_IMMIGRANT},                  // FIGURE_IMMIGRANT = 1,
  {1, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_VAGRANT},                    // FIGURE_EMIGRANT = 2,
  {1, TERRAIN_USAGE_PREFER_ROADS, 0, GROUP_FIGURE_VAGRANT},              // FIGURE_HOMELESS = 3,
  {1, TERRAIN_USAGE_ROADS, 0, GROUP_FIGURE_CARTPUSHER},                  // FIGURE_CART_PUSHER = 4,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_LABOR_SEEKER},              // FIGURE_LABOR_SEEKER = 5,
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_EXPLOSION},                     // FIGURE_EXPLOSION = 6,
  {1, TERRAIN_USAGE_ROADS, 512, GROUP_FIGURE_TAX_COLLECTOR},             // FIGURE_TAX_COLLECTOR = 7,
  {1, TERRAIN_USAGE_ROADS, 640, GROUP_FIGURE_ENGINEER},                  // FIGURE_ENGINEER = 8,
  {1, TERRAIN_USAGE_ROADS, 0, GROUP_FIGURE_CARTPUSHER},                  // FIGURE_WAREHOUSEMAN = 9,
  {1, TERRAIN_USAGE_ROADS, 640, GROUP_FIGURE_FIREMAN},                   // FIGURE_PREFECT = 10,
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_ARCHER_PH},                     // FIGURE_FORT_JAVELIN = 11,
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_CHARIOTEER_PH},                 // FIGURE_FORT_MOUNTED = 12,
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_INFANTRY_PH},                   // FIGURE_FORT_LEGIONARY = 13,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_FORT_STANDARD = 14,
  {1, TERRAIN_USAGE_ROADS, 512, GROUP_FIGURE_JUGGLER},                   // FIGURE_JUGGLER = 15,
  {1, TERRAIN_USAGE_ROADS, 512, GROUP_FIGURE_MUSICIAN},                  // FIGURE_MUSICIAN = 16,
  {1, TERRAIN_USAGE_ROADS, 512, GROUP_FIGURE_DANCER},                    // FIGURE_DANCER = 17,
  {1, TERRAIN_USAGE_ROADS, 512, GROUP_FIGURE_CHARIOTEER},                // FIGURE_CHARIOTEER = 18,
  {1, TERRAIN_USAGE_PREFER_ROADS, 0, GROUP_FIGURE_TRADE_CARAVAN},        // FIGURE_TRADE_CARAVAN = 19,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_TRADE_SHIP = 20,
  {1, TERRAIN_USAGE_PREFER_ROADS, 0, GROUP_FIGURE_TRADE_CARAVAN_DONKEY}, // FIGURE_TRADE_CARAVAN_DONKEY = 21,
  {1, TERRAIN_USAGE_ROADS, 0, GROUP_FIGURE_THIEF_WALK},                  // FIGURE_PROTESTER = 22,
  {1, TERRAIN_USAGE_ROADS, 0, GROUP_FIGURE_THIEF_WALK},                    // FIGURE_CRIMINAL = 23,
  {1, TERRAIN_USAGE_ENEMY, 480, GROUP_FIGURE_RIOTER_WALK},                  // FIGURE_RIOTER = 24,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_FISHING_BOAT = 25,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_MARKET_LADY_2},             // FIGURE_MARKET_TRADER = 26,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_PRIEST},                    // FIGURE_PRIEST = 27,
  {1, TERRAIN_USAGE_ROADS, 192, GROUP_FIGURE_SCHOOL_CHILD},              // FIGURE_SCHOOL_CHILD = 28,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_TEACHER_LIBRARIAN},         // FIGURE_TEACHER = 29,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_TEACHER_LIBRARIAN},         // FIGURE_LIBRARIAN = 30,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_BARBER},                    // FIGURE_BARBER = 31,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_BATHHOUSE_WORKER},          // FIGURE_BATHHOUSE_WORKER = 32,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_DOCTOR_SURGEON},            // FIGURE_DOCTOR = 33,
  {1, TERRAIN_USAGE_ROADS, 384, GROUP_FIGURE_MORTUARY},                  // FIGURE_SURGEON = 34,
  {1, TERRAIN_USAGE_ROADS, 384, 0, 0},                                   // FIGURE_WORKER = 35,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_MAP_FLAG = 36,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_FLOTSAM = 37,
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                                     // FIGURE_DOCKER = 38,
  {1, TERRAIN_USAGE_ROADS, 800, 0, 0},                                   // FIGURE_MARKET_BUYER = 39,
  {1, TERRAIN_USAGE_ROADS, 128, GROUP_FIGURE_PATRICIAN},                 // FIGURE_PATRICIAN = 40,
  {1, TERRAIN_USAGE_ANY, 800, 0, 0},                                     // FIGURE_INDIGENOUS_NATIVE = 41,
  {1, TERRAIN_USAGE_WALLS, 800, 0, 0},                                   // FIGURE_TOWER_SENTRY = 42,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY43_SPEAR = 43,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY44_SWORD = 44,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY45_SWORD = 45,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY46_CAMEL = 46,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY47_ELEPHANT = 47,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY48_CHARIOT = 48,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY49_FAST_SWORD = 49,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY50_SWORD = 50,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY51_SPEAR = 51,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY52_MOUNTED_ARCHER = 52,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY53_AXE = 53,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY54_GLADIATOR = 54,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY_CAESAR_JAVELIN = 55,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY_CAESAR_MOUNTED = 56,
  {1, TERRAIN_USAGE_ENEMY, 0, 0, 0},                                     // FIGURE_ENEMY_CAESAR_LEGIONARY = 57,
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                                     // FIGURE_NATIVE_TRADER = 58,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_ARROW = 59,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_JAVELIN = 60,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_BOLT = 61,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_BALLISTA = 62,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_CREATURE = 63,
  {1, TERRAIN_USAGE_ROADS, 192, GROUP_FIGURE_MISSIONARY},                // FIGURE_MISSIONARY = 64,
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_SEAGULLS},                      // FIGURE_FISH_GULLS = 65,
  {1, TERRAIN_USAGE_ROADS, 0, GROUP_FIGURE_GRANARY_BOY},                 // FIGURE_DELIVERY_BOY = 66,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_SHIPWRECK = 67,
  {2, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_SHEEP},                      // FIGURE_SHEEP = 68,
  {2, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_OSTRICH_WALK},               // FIGURE_OSTRICH = 69,
  {2, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_CROCODILE},                  // FIGURE_ZEBRA = 70,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_SPEAR = 71,
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                       // FIGURE_HIPPODROME_HORSES = 72,

  // PHARAOH

  {1, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_HUNTER_OSTRICH_MOVE}, // 73
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_HUNTER_ARROW},           // 74
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 75
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 76
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 77
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 78
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 79
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 80
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 81
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 82
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 83
  {1, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_HIPPO_WALK},          // 84 hippo
  {1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_WORKER_PH},              // 85
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 86
  {1, TERRAIN_USAGE_ROADS, 640, GROUP_FIGURE_WATER_CARRIER},      // 87 water carrier
  {1, TERRAIN_USAGE_ROADS, 640, GROUP_FIGURE_POLICEMAN},          // 88 policeman
  {1, TERRAIN_USAGE_ROADS, 800, GROUP_FIGURE_MAGISTRATE},         // 89 magistrate
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 90
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 91
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 92
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 93
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 94
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 95
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 96
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 97
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 98
  {1, TERRAIN_USAGE_ANY, 0, 0, 0},                                // 99
  {1, TERRAIN_USAGE_ROADS, 0, 0, 0},                              // 100
};

bool is_coords_within_range(int x, int y, int b_x, int b_y, int size, int radius) {
    int min_x = b_x - radius;
    int min_y = b_y - radius;
    int max_x = b_x + size - 1 + radius;
    int max_y = b_y + size - 1 + radius;

    if (x >= min_x && x <= max_x && y >= min_y && y <= max_y) {
        return true;
    }

    return false;
}

void figure::advance_action(short NEXT_ACTION) {
    //    if (NEXT_ACTION == 0)
    //        poof();
    //    else
    action_state = NEXT_ACTION;
}
bool figure::do_roam(int terrainchoice, short NEXT_ACTION) {
    terrain_usage = terrainchoice;
    roam_length++;
    if (roam_length >= max_roam_length) { // roam over, return home
        destination_tile.set(0);
        roam_length = 0;
        set_destination(0);
        route_remove();
        advance_action(NEXT_ACTION);
        return true;
    } else {
        roam_ticks(speed_multiplier);
    }
    return false;
}

bool figure::do_goto(map_point dest, int terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    OZZY_PROFILER_SECTION("Figure/Goto");
    terrain_usage = terrainchoice;
    if (use_cross_country) {
        terrain_usage = TERRAIN_USAGE_ANY;
    }

    // refresh routing if destination is different
    if (destination_tile != dest) {
        OZZY_PROFILER_SECTION("Figure/Goto/Route remove (no dest)");
        route_remove();
    }

    // set up destination and move!!!
    if (use_cross_country) {
        OZZY_PROFILER_SECTION("Figure/Goto/CrossCountry");
        set_cross_country_destination(dest.x(), dest.y());
        if (move_ticks_cross_country(1) == 1) {
            advance_action(NEXT_ACTION);
            return true;
        }
    } else {
        OZZY_PROFILER_SECTION("Figure/Goto/MoveTicks");
        destination_tile = dest;
        move_ticks(speed_multiplier);
    }

    // check if destination is reached/figure is lost/etc.
    if (direction == DIR_FIGURE_NONE) {
        advance_action(NEXT_ACTION);
        direction = previous_tile_direction;
        return true;
    }

    if (direction == DIR_FIGURE_REROUTE) {
        OZZY_PROFILER_SECTION("Figure/Goto/Route Remove (reroute)");
        route_remove();
    }

    if (direction == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(FAIL_ACTION);
    }

    return false;
}
bool figure::do_gotobuilding(building* dest, bool stop_at_road, int terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    map_point finish_tile;
    set_destination(dest);
    if (dest->state != BUILDING_STATE_VALID) {
        advance_action(FAIL_ACTION);
    }

    if (stop_at_road) {
        bool found_road = false;
        bool already_there = false;

        // correct road lookup for warehouse tiles range
        if (dest->type == BUILDING_STORAGE_YARD || dest->type == BUILDING_STORAGE_YARD_SPACE) {
            building* main = dest->main();
            if (terrainchoice == TERRAIN_USAGE_ROADS) {
                found_road = map_closest_reachable_road_within_radius(main->tile.x(), main->tile.y(), 3, 1, finish_tile);
            }

            if (!found_road) {
                found_road = map_closest_road_within_radius(main->tile, 3, 1, finish_tile);
            }

            if (found_road && is_coords_within_range(tile.x(), tile.y(), main->tile.x(), main->tile.y(), 3, 1)) {
                finish_tile = tile;
            }
        } else if (building_is_large_temple(dest->type)) { // TODO: proper return home for temple complexes
            building* main = dest->main();
            if (main->has_road_access) {
                found_road = true;
                finish_tile = main->road_access;
            }
        } else {
            building* main = dest->main();
            if (main->has_road_access) {
                found_road = true;
                finish_tile = main->road_access;
            } else {
                if (terrainchoice == TERRAIN_USAGE_ROADS) {
                    found_road = map_closest_reachable_road_within_radius(dest->tile.x(), dest->tile.y(), dest->size, 1, finish_tile);
                }

                if (!found_road) {
                    if (building_is_house(dest->type) || dest->type == BUILDING_BURNING_RUIN) {
                        found_road = map_closest_road_within_radius(dest->tile, dest->size, 2, finish_tile);
                    } else {
                        found_road = map_closest_road_within_radius(dest->tile, dest->size, 1, finish_tile);
                    }
                }

                if (found_road && is_coords_within_range(tile.x(), tile.y(), dest->tile.x(), dest->tile.y(), dest->size, 1)) {
                    finish_tile = tile;
                }
            }
        }
        // found any road...?
        if (found_road) {
            //            destination_tile.set(x, y);
            return do_goto(finish_tile, terrainchoice, NEXT_ACTION, FAIL_ACTION);
        } else {
            if (terrainchoice == TERRAIN_USAGE_ROADS && !use_cross_country) {
                advance_action(FAIL_ACTION); // poof dude!!!
            } else {
                advance_action(NEXT_ACTION); // don't poof if it's not *requiring* roads, was just looking for one
            }
        }
    } else {
        return do_goto(dest->tile, terrainchoice, NEXT_ACTION, FAIL_ACTION); // go into building **directly**
    }

    return false;
}
bool figure::do_returnhome(int terrainchoice, short NEXT_ACTION) {
    return do_gotobuilding(home(), true, terrainchoice, NEXT_ACTION);
}
bool figure::do_exitbuilding(bool invisible, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = true;
    if (invisible)
        is_ghost = true;
    // "go to" home, but stop at road = go to entrance
    return do_gotobuilding(home(), true, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}
bool figure::do_enterbuilding(bool invisible, building* b, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = true;
    if (invisible)
        is_ghost = true;
    return do_gotobuilding(b, false, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}

void figure::action_perform() {
    //    return;
    if (action_state < 0) {
        set_state(FIGURE_STATE_DEAD);
    }

    if (state) {
        if (targeted_by_figure_id) {
            figure* attacker = figure_get(targeted_by_figure_id);
            if (attacker->state != FIGURE_STATE_ALIVE)
                targeted_by_figure_id = 0;
            if (attacker->target_figure_id != id)
                targeted_by_figure_id = 0;
        }

        //////////////

        // reset values like cart image & max roaming length
        cart_image_id = 0;
        max_roam_length = 0;
        use_cross_country = false;
        is_ghost = false;

        // base lookup data
        figure_action_property action_properties = action_properties_lookup[type];
        if (action_properties.terrain_usage != -1 && terrain_usage == -1)
            terrain_usage = action_properties.terrain_usage;
        max_roam_length = action_properties.max_roam_length;
        speed_multiplier = action_properties.speed_mult;
        image_set_animation(action_properties.base_image_collection, action_properties.base_image_group);

        // check for building being alive (at the start of the action)
        building* b = home();
        building* b_imm = immigrant_home();
        figure* leader = figure_get(leading_figure_id);
        switch (type) {
        case FIGURE_IMMIGRANT:
            //                if (b_imm->state != BUILDING_STATE_VALID)
            //                    poof();
            //                if (!b_imm->house_size)
            //                    poof();
            //                if (!b_imm->has_figure(2, id))
            //                    poof();
            if (b_imm->type == BUILDING_BURNING_RUIN) {
                poof();
            }
            if (terrain_type == TERRAIN_WATER) {
                image_set_animation(GROUP_FIGURE_FERRY_BOAT, 0, 4, 4);
            }
            break;

        case FIGURE_ENGINEER:
        case FIGURE_FIREMAN:
        case FIGURE_POLICEMAN:
        case FIGURE_MAGISTRATE:
        case FIGURE_WORKER:
        case FIGURE_MARKET_TRADER:
        case FIGURE_NATIVE_TRADER:
        case FIGURE_TAX_COLLECTOR:
        case FIGURE_TOWER_SENTRY:
        case FIGURE_MISSIONARY:
        case FIGURE_WATER_CARRIER:
        case FIGURE_APOTHECARY:
        case FIGURE_DENTIST:
        case FIGURE_MORTUARY_WORKER:
        case FIGURE_PHYSICIAN:
        case FIGURE_PRIEST:
            if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id)) {
                poof();
            }
            break;

        case FIGURE_OSTRICH_HUNTER:
            if (b->state != BUILDING_STATE_VALID) {
                poof();
            }
            break;

        case FIGURE_REED_GATHERER:
        case FIGURE_LUMBERJACK:
            if (b->state != BUILDING_STATE_VALID) {
                poof();
            }
            break;

        case FIGURE_CART_PUSHER:
            if (has_destination())
                break;

            if (!building_is_floodplain_farm(b)
                && (b->state != BUILDING_STATE_VALID || (!b->has_figure(0, id) && !b->has_figure(1, id)))) {
                poof();
            }
            break;

        case FIGURE_STORAGE_YARD_DELIVERCART:
            if (has_destination())
                break;
            if (b->state != BUILDING_STATE_VALID || (!b->has_figure(0, id) && !b->has_figure(1, id)))
                poof();
            break;

        case FIGURE_LABOR_SEEKER:
            //            case FIGURE_MARKET_BUYER:
            if (b->state != BUILDING_STATE_VALID) //  || !b->has_figure(1, id)
                poof();
            break;

        case FIGURE_DELIVERY_BOY:
        case FIGURE_TRADE_CARAVAN_DONKEY:
            if (leading_figure_id <= 0) {
                //poof();
            }

            if (leader->action_state == FIGURE_ACTION_149_CORPSE) {  
                poof(); // TODO make runaway from this tile
            }

            if (leader->is_ghost) {
                is_ghost = true;
            }
            break;
        }

        // common action states handling
        switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
            break;

        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;

        case FIGURE_ACTION_125_ROAMING:
        case ACTION_1_ROAMING:
            if (type == FIGURE_IMMIGRANT || type == FIGURE_EMIGRANT || type == FIGURE_HOMELESS) {
                break;
            }
            do_roam();
            break;

        case FIGURE_ACTION_126_ROAMER_RETURNING:
        case ACTION_2_ROAMERS_RETURNING:
            if (type == FIGURE_IMMIGRANT || type == FIGURE_EMIGRANT || type == FIGURE_HOMELESS) {
                break;
            }
            do_returnhome();
            break;
        }
        if (state == FIGURE_STATE_DYING) // update corpses / dying animation
            figure_combat_handle_corpse();
        if (map_terrain_is(tile.grid_offset(), TERRAIN_ROAD)) { // update road flag
            outside_road_ticks = 0;
            if (map_terrain_is(tile.grid_offset(), TERRAIN_WATER)) // bridge
                set_target_height_bridge();
        } else {
            if (outside_road_ticks < 255)
                outside_road_ticks++;

            const bool tile_is_water = map_terrain_is(tile.grid_offset(), TERRAIN_WATER);
            if (!can_move_by_water() && tile_is_water) {
                kill();
            }

            if (!can_move_by_terrain() && !tile_is_water) {
                kill();
            }

            if (terrain_usage == TERRAIN_USAGE_ROADS) { // walkers outside of roads for too long?
                if (destination_tile.x() && destination_tile.y()
                    && outside_road_ticks > 100) // dudes with destination have a bit of lee way
                    poof();
                if (!destination_tile.x() && !destination_tile.y() && state == FIGURE_STATE_ALIVE
                    && outside_road_ticks > 0)
                    poof();
            }
        }

        ////////////

        switch (type) {
        case FIGURE_IMMIGRANT:
            immigrant_action();
            break;
        case FIGURE_EMIGRANT:
            emigrant_action();
            break;
        case 3:
            homeless_action();
            break;
        case 4:
            cartpusher_action();
            break;
            //            case 5: common_action(12, GROUP_FIGURE_LABOR_SEEKER); break;
        case 6:
            explosion_cloud_action();
            break;
        case 7:
            tax_collector_action();
            break;
        case 8:
            engineer_action();
            break;
        case 9:
            storageyard_cart_action();
            break; // warehouseman_action !!!!

        case FIGURE_FIREMAN:
            fireman_action();
            break; // 10

        case 11:   // soldier_action();                  break;
        case 12:   // soldier_action();                  break;
        case 13:
            soldier_action();
            break;
        case 14:
            military_standard_action();
            break;
        case 15: // entertainer_action();              break;
        case 16: // entertainer_action();              break;
        case 17: // entertainer_action();              break;
        case 18:
            entertainer_action();
            break;
        case 19:
            trade_caravan_action();
            break;
        case 20:
            trade_ship_action();
            break; // 20
        case 21:
            trade_caravan_donkey_action();
            break;
        case 22:
            protestor_action();
            break;
        case 23:
            mugger_action();
            break;
        case 24:
            rioter_action();
            break;
        case 25:
            fishing_boat_action();
            break;
        case FIGURE_MARKET_TRADER:
            market_trader_action();
            break;
        case 27:
            priest_action();
            break;
            //            case 27: common_action(12, GROUP_FIGURE_PRIEST); break;
        case 28:
            school_child_action();
            break;
            //            case 29: common_action(12, GROUP_FIGURE_TEACHER_LIBRARIAN); break;
            //            case 30: common_action(12, GROUP_FIGURE_TEACHER_LIBRARIAN); break; //30
            //            case 31: common_action(12, GROUP_FIGURE_BARBER); break;
            //            case 32: common_action(12, GROUP_FIGURE_BATHHOUSE_WORKER); break;
        case 33: // doctor_action(); break;
                 //            case 34: common_action(12, GROUP_FIGURE_DOCTOR_SURGEON); break;
                 //            case 35: worker_action();                   break;
        case 36:
            editor_flag_action();
            break;
        case 37:
            flotsam_action();
            break;
        case 38:
            docker_action();
            break;
        case FIGURE_MARKET_BUYER:
            market_buyer_action();
            break;
            //            case 40: patrician_action();                break; //40
        case 41:
            indigenous_native_action();
            break;
        case 42:
            tower_sentry_action();
            break;
        case 43:
            enemy43_spear_action();
            break;
        case 44:
            enemy44_sword_action();
            break;
        case 45:
            enemy45_sword_action();
            break;
        case 46:
            enemy_camel_action();
            break;
        case 47:
            enemy_elephant_action();
            break;
        case 48:
            enemy_chariot_action();
            break;
        case 49:
            enemy49_fast_sword_action();
            break;
        case 50:
            enemy50_sword_action();
            break; // 50
        case 51:
            enemy51_spear_action();
            break;
        case 52:
            enemy52_mounted_archer_action();
            break;
        case 53:
            enemy53_axe_action();
            break;
        case 54:
            enemy_gladiator_action();
            break;
            //                no_action();                            break;
            //                no_action();                            break;
        case 57:
            enemy_caesar_legionary_action();
            break;
        case 58:
            native_trader_action();
            break;
        case 59:
            arrow_action();
            break;
        case 60:
            javelin_action();
            break; // 60
        case 61:
            bolt_action();
            break;
        case 62:
            ballista_action();
            break;
            //                no_action();                            break;
            //            case 64: missionary_action();               break;
        case 65:
            seagulls_action();
            break;

        case FIGURE_DELIVERY_BOY:
            delivery_boy_action();
            break;

        case 67:
            shipwreck_action();
            break;
        case 68:
            sheep_action();
            break;
        case FIGURE_OSTRICH:
            ostrich_action();
            break;
        case 70:
            zebra_action();
            break; // 70
        case 71:
            spear_action();
            break;
        case 72:
            hippodrome_horse_action();
            break;
        case FIGURE_OSTRICH_HUNTER:
            ostrich_hunter_action();
            break;
        case 74:
            arrow_action();
            break;
        case 75:
            gatherer_action();
            break; // wood cutters
        case FIGURE_HIPPO:
            hippo_action();
            break;
        case FIGURE_WORKER_PH:
            worker_action();
            break;
        case 87:
            water_carrier_action();
            break;
        case FIGURE_POLICEMAN:
            policeman_action();
            break;
        case 89:
            magistrate_action();
            break;
        case 90:
            gatherer_action();
            break; // reed gatherers
        case 91:
            festival_guy_action();
            break;
        case FIGURE_HYENA:
            hyena_action();
            break;
        default:
            break;
        }

        // if DEAD, delete figure -- this is UNSAFE, and should only be done here.
        if (state == FIGURE_STATE_DEAD)
            return figure_delete_UNSAFE();

        // poof if LOST
        if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            if (figure_type_none_of(*this, FIGURE_ARROW, FIGURE_HUNTER_ARROW, FIGURE_BOLT)) {
                poof();
            }
        }

        // advance sprite offset
        figure_image_update(false);
    }
}

void figure_action_handle() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure Action");
    city_figures_reset();
    city_entertainment_set_hippodrome_has_race(0);

    for (auto &figure: figures()) {
        figure->action_perform();
    }
}
