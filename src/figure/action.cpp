
#include "action.h"

#include "grid/terrain.h"

#include "city/entertainment.h"
#include "city/city.h"
#include "city/city.h"
#include "core/profiler.h"
#include "figure/figure.h"
#include "graphics/animkeys.h"
#include "graphics/image_desc.h"
#include "grid/road_access.h"

#include <algorithm>

/*
static figure_action_property action_properties_lookup[] = {
  {FIGURE_FCHARIOTEER, 1, 0, GROUP_FIGURE_CHARIOTEER_PH},
  {FIGURE_SENET_PLAYER, 1, 0, GROUP_FIGURE_CHARIOTEER},
  {FIGURE_PROTESTER, 1, 0, GROUP_FIGURE_THIEF_WALK},
  {FIGURE_CRIMINAL, 1, 0, GROUP_FIGURE_THIEF_WALK},
  {FIGURE_TOMB_ROBER, 1, TERRAIN_USAGE_ENEMY, 480, GROUP_FIGURE_RIOTER_WALK},
  {FIGURE_MARKET_TRADER, 1, 0, 0, 0, IMG_NONE},
  {FIGURE_PRIEST, 1, 0, 0, 0, IMG_PRIEST_OSIRIS},
  {FIGURE_TEACHER, 1, 0, 0, 0, IMG_NONE},
  {FIGURE_SCRIBER, 1, 0, 0, 0, IMG_NONE},
  {FIGURE_LIBRARIAN, 1, 384, GROUP_FIGURE_LIBRARIAN},
  {FIGURE_DENTIST, 1, 0, 0, 0},
  {FIGURE_PHYSICIAN, 1, 0, 0, 0, IMG_NONE},
  {FIGURE_HERBALIST, 1, 0, 0, 0, IMG_NONE},
  {FIGURE_EMBALMER, 1, 384, GROUP_FIGURE_EMBALMER},
  {FIGURE_MAP_FLAG, 1, 0, 0, 0},
  {FIGURE_DOCKER, 1, 0, 0, 0, ANIM_DOCKER_WALK},
  {FIGURE_NOBLES, 1, 128, GROUP_FIGURE_NOBLE},
  {FIGURE_INDIGENOUS_NATIVE, 1, 800, 0, 0},
  {FIGURE_TOWER_SENTRY, 1, TERRAIN_USAGE_WALLS, 800, 0, 0},
  {FIGURE_ENEMY43_SPEAR, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY44_SWORD, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY45_SWORD, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY46_CAMEL, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY47_ELEPHANT, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY48_CHARIOT, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY49_FAST_SWORD, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY50_SWORD, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY51_SPEAR, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY52_MOUNTED_ARCHER, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY53_AXE, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY54_GLADIATOR, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY_CAESAR_JAVELIN, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY_CAESAR_MOUNTED, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_ENEMY_CAESAR_LEGIONARY, 1, TERRAIN_USAGE_ENEMY, 0, 0, 0},
  {FIGURE_NATIVE_TRADER, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_ARROW, 1, 0, 0, 0},
  {FIGURE_JAVELIN, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_BOLT, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_BALLISTA, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_CREATURE, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_MISSIONARY, 1, TERRAIN_USAGE_ROADS, 192, GROUP_FIGURE_MISSIONARY},
  {FIGURE_DELIVERY_BOY, 1, 0, 0, 0, ANIM_DELIVERY_BOY_WALK},
  {FIGURE_BIRDS, 2, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_SHEEP},
  {FIGURE_ANTELOPE, 2, 0, GROUP_FIGURE_CROCODILE},
  {FIGURE_CHARIOR_RACER, 1, 0, 0, 0},

  {FIGURE_PHARAOH, 1, TERRAIN_USAGE_ANY, 0, GROUP_FIGURE_PHARAOH_WALK},
  {FIGURE_GOVERNOR, 1, TERRAIN_USAGE_ROADS, 0, GROUP_FIGURE_GOVERNOR},
  {FIGURE_WARSHIP, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_CARPENTER, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_BRICKLAYER, 1, 0, 0, 0, IMG_BRICKLAYER_WALK},
  {FIGURE_STONEMASON, 1, 0, 0, 0},
  {FIGURE_CROCODILE, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_HYENA, 1, TERRAIN_USAGE_ANIMAL, 0, GROUP_FIGURE_HYENA_WALK},
  {FIGURE_LABORER, 1, TERRAIN_USAGE_ANY, 0, 0, 0, IMG_NONE},
  {FIGURE_SLED, 1, TERRAIN_USAGE_ANY, 0, 0, 0, IMG_NONE},
  {FIGURE_CONSTABLE, 1, TERRAIN_USAGE_ROADS, 640, GROUP_FIGURE_POLICEMAN},
  {FIGURE_MAGISTRATE, 1, 0, 0, 0, IMG_NONE},
  {FIGURE_FESTIVAL_PRIEST, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_ENEMY_TRANSPORT, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_ENEMY_WARSHIP, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_FUNERAL_WALKER, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_SHOWMAN, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_PLAGUED_CITIZEN, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_BEDOUIN_INFANTRY, 1, TERRAIN_USAGE_ANY, 0, 0, 0},
  {FIGURE_EGYPTIAN_WARSHIP, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_EGYPTIAN_TRANSPORT, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
  {FIGURE_ASP, 1, TERRAIN_USAGE_ROADS, 0, 0, 0},
}; */

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

void figure::advance_action(short next_action) {
    if (state == FIGURE_STATE_DYING && next_action != FIGURE_ACTION_149_CORPSE) {
        return;
    }
    action_state = next_action;
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

bool figure::do_goto(tile2i dest, int terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
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
        set_cross_country_destination(dest);
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

bool figure::do_gotobuilding(building* dest, bool stop_at_road, e_terrain_usage terrainchoice, short NEXT_ACTION, short FAIL_ACTION) {
    tile2i finish_tile;
    set_destination(dest);
    if (dest->state != BUILDING_STATE_VALID) {
        advance_action(FAIL_ACTION);
    }

    if (stop_at_road) {
        bool found_road = false;
        bool already_there = false;

        // correct road lookup for warehouse tiles range
        if (dest->type == BUILDING_STORAGE_YARD || dest->type == BUILDING_STORAGE_ROOM) {
            building* main = dest->main();
            if (terrainchoice == TERRAIN_USAGE_ROADS) {
                found_road = map_closest_reachable_road_within_radius(main->tile, 3, 1, finish_tile);
            }

            if (!found_road) {
                finish_tile = map_closest_road_within_radius(main->tile, 3, 1);
                found_road = finish_tile.valid();
            }

            if (found_road && is_coords_within_range(tile.x(), tile.y(), main->tile.x(), main->tile.y(), 3, 1)) {
                finish_tile = tile;
            }
        } else if (building_is_temple_complex(dest->type)) { // TODO: proper return home for temple complexes
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
                    found_road = map_closest_reachable_road_within_radius(dest->tile, dest->size, 1, finish_tile);
                }

                if (!found_road) {
                    if (building_is_house(dest->type) || dest->type == BUILDING_BURNING_RUIN) {
                        finish_tile = map_closest_road_within_radius(dest->tile, dest->size, 2);
                        found_road = finish_tile.valid();
                    } else {
                        finish_tile = map_closest_road_within_radius(dest->tile, dest->size, 1);
                        found_road = finish_tile.valid();
                    }
                }

                if (found_road && is_coords_within_range(tile.x(), tile.y(), dest->tile.x(), dest->tile.y(), dest->size, 1)) {
                    finish_tile = tile;
                }
            }
        }
        // found any road...?
        if (found_road) {
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

bool figure::do_returnhome(e_terrain_usage terrainchoice, short NEXT_ACTION) {
    return do_gotobuilding(home(), true, terrainchoice, NEXT_ACTION);
}

bool figure::do_exitbuilding(bool invisible, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = true;
    // "go to" home, but stop at road = go to entrance
    return do_gotobuilding(home(), true, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}

bool figure::do_enterbuilding(bool invisible, building* b, short NEXT_ACTION, short FAIL_ACTION) {
    use_cross_country = true;
    return do_gotobuilding(b, false, TERRAIN_USAGE_ANY, NEXT_ACTION, FAIL_ACTION);
}

void figure::action_perform() {
    if (action_state < 0) {
        set_state(FIGURE_STATE_DEAD);
    }

    if (state) {
        if (targeted_by_figure_id) {
            figure* attacker = figure_get(targeted_by_figure_id);
            if (attacker && attacker->state != FIGURE_STATE_ALIVE) {
                targeted_by_figure_id = 0;
            }

            if (attacker && attacker->target_figure_id != id) {
                targeted_by_figure_id = 0;
            }
        }

        //////////////

        // reset values like cart image & max roaming length
        cart_image_id = 0;
        max_roam_length = 0;
        use_cross_country = false;

        // base lookup data
        const auto &params = figure_impl::params(type);
        if (params.terrain_usage != -1 && terrain_usage == 0xff) {
            terrain_usage = params.terrain_usage;
        }
        max_roam_length = params.max_roam_length;
        speed_multiplier = params.speed_mult;
        if (!this->anim.id) {
            const animation_t &def_anim = params.anim[animkeys().walk];
            image_set_animation(def_anim);
        }

        // check for building being alive (at the start of the action)
        building* b = home();
        figure* leader = figure_get(leading_figure_id);
        switch (type) {
        case FIGURE_NATIVE_TRADER:
        case FIGURE_TOWER_SENTRY:
        case FIGURE_MISSIONARY:
        case FIGURE_EMBALMER:
            if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id)) {
                poof();
            }
            break;

        case FIGURE_NOBLES:
            if (b->state != BUILDING_STATE_VALID) {
                poof();
            }
            break;

        default:
            dcast()->figure_before_action();
            break;
        }

        // common action states handling
        dcast()->figure_roaming_action();

        if (state == FIGURE_STATE_DYING) { // update corpses / dying animation
            figure_combat_handle_corpse();
        }

        if (map_terrain_is(tile, TERRAIN_ROAD|TERRAIN_FERRY_ROUTE)) { // update road flag
            outside_road_ticks = 0;
            if (map_terrain_is(tile.grid_offset(), TERRAIN_WATER)) { // bridge
                set_target_height_bridge();
            }
        } else {
            if (outside_road_ticks < 255) {
                outside_road_ticks++;
            }

            if (map_terrain_is(tile.grid_offset(), TERRAIN_BUILDING)) { // bridge
                set_target_height_building();
            }

            const bool tile_is_water = map_terrain_is(tile.grid_offset(), TERRAIN_WATER);
            if (!can_move_by_water() && tile_is_water) {
                kill();
            }

            if (!can_move_by_terrain() && !tile_is_water) {
                kill();
            }

            if (terrain_usage == TERRAIN_USAGE_ROADS) { // walkers outside of roads for too long?
                                                        // dudes with destination have a bit of lee way
                if (destination_tile.x() && destination_tile.y() && outside_road_ticks > 100) {
                    poof();
                }

                if (!destination_tile.x() && !destination_tile.y() && state == FIGURE_STATE_ALIVE && outside_road_ticks > 0) {
                    poof();
                }
            }
        }

        switch (type) {
        case FIGURE_PROTESTER: protestor_action(); break;
        case FIGURE_CRIMINAL: mugger_action(); break;
        case FIGURE_TOMB_ROBER: rioter_action(); break;
            //            case 30: common_action(12, GROUP_FIGURE_TEACHER_LIBRARIAN); break; //30
            //            case 32: common_action(12, GROUP_FIGURE_BATHHOUSE_WORKER); break;
        case 36: editor_flag_action(); break;
        case FIGURE_NOBLES: noble_action(); break; 
        case 41: indigenous_native_action(); break;
        case 42: tower_sentry_action(); break;
        case 43: enemy43_spear_action(); break;
        case 44: enemy44_sword_action(); break;
        case 45: enemy45_sword_action(); break;
        case 46: enemy_camel_action(); break;
        case 47: enemy_elephant_action(); break;
        case 48: enemy_chariot_action(); break;
        case 49: enemy49_fast_sword_action(); break;
        case 50: enemy50_sword_action(); break; // 50
        case 51: enemy51_spear_action(); break;
        case 52: enemy52_mounted_archer_action(); break;
        case 53: enemy53_axe_action(); break;
        case 54: enemy_gladiator_action(); break;
        case 57: enemy_kingdome_soldier_action(); break;
        case FIGURE_BALLISTA: ballista_action(); break;
        case FIGURE_ANTELOPE: zebra_action(); break; // 70
        case FIGURE_CHARIOR_RACER: hippodrome_horse_action(); break;

        default:
            {
                auto *impl = dcast();
                impl->figure_action();
                impl->update_animation();
            }
            break;
        }

        // if DEAD, delete figure -- this is UNSAFE, and should only be done here.
        if (state == FIGURE_STATE_DEAD) {
            return figure_delete_UNSAFE();
        }

        // poof if LOST
        //if (direction == DIR_FIGURE_CAN_NOT_REACH) {
        //    if (figure_type_none_of(*this, FIGURE_ARROW, FIGURE_HUNTER_ARROW, FIGURE_BOLT)) {
        //        dcast()->poof();
        //    }
        //}

        // advance sprite offset
        figure_image_update(false);
    }
}
