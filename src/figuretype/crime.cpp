#include "crime.h"

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

static void generate_rioter(building* b) {
    tile2i road_tile;
    if (!map_closest_road_within_radius(b->tile, b->size, 4, road_tile)) {
        return;
    }

    city_sentiment_add_criminal();
    int people_in_mob;
    int population = city_population();
    if (population <= 150)
        people_in_mob = 1;
    else if (population <= 300)
        people_in_mob = 2;
    else if (population <= 800)
        people_in_mob = 3;
    else if (population <= 1200)
        people_in_mob = 4;
    else if (population <= 2000)
        people_in_mob = 5;
    else {
        people_in_mob = 6;
    }
    int x_target, y_target;
    int target_building_id = formation_rioter_get_target_building(&x_target, &y_target);
    for (int i = 0; i < people_in_mob; i++) {
        // TODO: to add correct rioter image
        figure* f = figure_create(FIGURE_TOMB_ROBER, road_tile, DIR_4_BOTTOM_LEFT);
        f->advance_action(FIGURE_ACTION_120_RIOTER_CREATED);
        f->roam_length = 0;
        f->wait_ticks = 10 + 4 * i;
        if (target_building_id) {
            f->destination_tile.set(x_target, y_target);
            //            f->destination_tile.x() = x_target;
            //            f->destination_tile.y() = y_target;
            f->set_destination(target_building_id);
        } else {
            f->poof();
        }
    }
    building_destroy_by_rioter(b);
    g_city.ratings.monument_record_rioter();
    city_sentiment_change_happiness(20);
    tutorial_on_crime();
    city_message_apply_sound_interval(MESSAGE_CAT_RIOT);
    city_message_post_with_popup_delay(MESSAGE_CAT_RIOT, MESSAGE_RIOT, b->type, road_tile.grid_offset());
}

static void generate_mugger(building* b) {
    city_sentiment_add_criminal();
    if (b->house_criminal_active > 60 && city_can_create_mugger()) {
        b->house_criminal_active -= 60;
        tile2i road_tile;
        if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
            figure* f = figure_create(FIGURE_CRIMINAL, road_tile, DIR_4_BOTTOM_LEFT);
            f->advance_action(FIGURE_ACTION_120_MUGGER_CREATED);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);

            g_city.ratings.monument_record_criminal();
            int taxes_this_year = city_finance_overview_this_year()->income.taxes;
            if (taxes_this_year > 20) {
                int money_stolen = taxes_this_year / 4;
                if (money_stolen > 400) {
                    money_stolen = 400 - random_byte() / 2;
                }

                city_show_message_criminal(MESSAGE_TUTORIAL_CRIME, money_stolen, f->tile.grid_offset());
                city_finance_process_stolen(money_stolen);              
            } else {
                int treasury = city_finance_treasury();
                int money_stolen = 0;
                if (treasury > 0) {
                    money_stolen = (random_byte() / 2) % 100;
                }

                if (money_stolen > 0) {
                    city_show_message_criminal(MESSAGE_TUTORIAL_CRIME, money_stolen, f->tile.grid_offset());
                    city_finance_process_stolen(money_stolen);
                }
            }
        }
    }
}

static void generate_protestor(building* b) {
    city_sentiment_add_protester();
    if (b->house_criminal_active > 30 && city_can_create_protestor()) {
        b->house_criminal_active -= 30;
        tile2i road_tile;
        if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
            figure* f = figure_create(FIGURE_PROTESTER, road_tile, DIR_4_BOTTOM_LEFT);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);
            g_city.ratings.monument_record_criminal();
        }
    }
}

void figure_generate_criminals(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Generate Criminals");
    building* min_building = nullptr;
    int min_happiness = 50;
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size) {
            if (b->sentiment.house_happiness >= 50) {
                b->house_criminal_active = 0;
            } else if (b->sentiment.house_happiness < min_happiness) {
                min_happiness = b->sentiment.house_happiness;
                min_building = b;
            }
        }
    }

    if (min_building) {
        int sentiment = city_sentiment();

        if (sentiment < 30) {
            if (random_byte() >= sentiment + 50) {
                if (min_happiness <= 10) {
                    // if (GAME_ENV == ENGINE_ENV_C3) { // Temporary disable rioters in Egypt
                    //     generate_rioter(min_building);
                    // } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                    generate_mugger(min_building);
                } else if (min_happiness < 30) {
                    generate_mugger(min_building);
                } else if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        } else if (sentiment < 60) {
            if (random_byte() >= sentiment + 40) {
                if (min_happiness < 30) {
                    generate_mugger(min_building);
                } else if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        } else {
            if (random_byte() >= sentiment + 20) {
                if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        }
    }
}

void figure::protestor_action() {
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(64);
    //    cart_image_id = 0;
    //    if (action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();

    wait_ticks++;
    if (wait_ticks > 200) {
        poof();
        anim_frame = 0;
    }

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim_frame / 4] + 104;
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
        int senate_id = city_buildings_get_palace_id();
        building* b_dst = building_get(senate_id);
        tile2i road_tile;
        if (map_closest_road_within_radius(b_dst->tile, b_dst->size, 2, road_tile)) {
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
            if (anim_frame > 12) {
                anim_frame = 0;
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
        anim_frame = 0;
    }

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim_frame / 2] + 104;
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
            if (anim_frame > 12) {
                anim_frame = 0;
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
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_ATTACK) + CRIMINAL_OFFSETS[anim_frame % 16];
    } else if (action_state == FIGURE_ACTION_121_RIOTER_MOVING) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_WALK) + dir + 8 * anim_frame;
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_RIOTER_ATTACK) + CRIMINAL_OFFSETS[anim_frame / 2];
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
