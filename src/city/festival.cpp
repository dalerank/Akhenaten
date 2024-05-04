#include "festival.h"

#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "building/count.h"
#include "buildings.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/finance.h"
#include "city/message.h"
#include "city/sentiment.h"
#include "core/random.h"
#include "figure/figure.h"
#include "config/config.h"
#include "graphics/image_groups.h"

static auto &city_data = g_city;
bool city_festival_is_planned(void) {
    return city_data.festival.planned.size != FESTIVAL_NONE;
}
int city_festival_months_since_last(void) {
    return city_data.festival.months_since_festival;
}
int city_festival_months_till_next(void) {
    return city_data.festival.planned.months_to_go;
}

int city_festival_small_cost(void) {
    return city_data.festival.small_cost;
}
int city_festival_large_cost(void) {
    return city_data.festival.large_cost;
}
int city_festival_grand_cost(void) {
    return city_data.festival.grand_cost;
}
int city_festival_grand_alcohol(void) {
    return city_data.festival.grand_alcohol;
}
int city_festival_out_of_alcohol(void) {
    return city_data.festival.not_enough_alcohol;
}

int city_festival_selected_god(void) {
    return city_data.festival.selected.god;
}
void city_festival_select_god(int god_id) {
    city_data.festival.selected.god = god_id;
}

int city_festival_selected_size(void) {
    return city_data.festival.selected.size;
}
int city_festival_select_size(int size) {
    if (size == FESTIVAL_GRAND && city_data.festival.not_enough_alcohol)
        return 0;

    city_data.festival.selected.size = size;
    return 1;
}

void city_festival_schedule(void) {
    city_data.festival.planned.god = city_data.festival.selected.god;
    city_data.festival.planned.size = city_data.festival.selected.size;
    int cost;
    if (city_data.festival.selected.size == FESTIVAL_SMALL) {
        city_data.festival.planned.months_to_go = 2;
        cost = city_data.festival.small_cost;
    } else if (city_data.festival.selected.size == FESTIVAL_LARGE) {
        city_data.festival.planned.months_to_go = 3;
        cost = city_data.festival.large_cost;
    } else {
        city_data.festival.planned.months_to_go = 4;
        cost = city_data.festival.grand_cost;
    }

    city_finance_process_requests_and_festivals(cost);

    if (city_data.festival.selected.size == FESTIVAL_GRAND) {
        building_storageyards_remove_resource(RESOURCE_BEER, city_data.festival.grand_alcohol);
    }
}

static void throw_party(void) {
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        switch (b->type) {
        case BUILDING_TEMPLE_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_RA:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_PTAH:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_SETH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_BAST:
        case BUILDING_TEMPLE_COMPLEX_BAST:
        case BUILDING_JUGGLER_SCHOOL:
        case BUILDING_CONSERVATORY:
        case BUILDING_DANCE_SCHOOL: { // this actually doesn't happen in Pharaoh?
                                      //                    if (b->has_figure(0))
                                      //                        b->remove_figure(0);
                figure* f = b->create_figure_generic(FIGURE_FESTIVAL_PRIEST, FIGURE_ACTION_10_FESTIVAL_PRIEST_CREATED, BUILDING_SLOT_PRIEST, DIR_4_BOTTOM_LEFT);
                f->festival_remaining_dances = 10;

                // choose a random tile on the festival square
                tile2i festival = city_building_get_festival_square_position();
                festival.shift(2, 2);
                f->do_goto(festival, TERRAIN_USAGE_ROADS, 10);

                break;
            }
        }
    }

    if (city_data.festival.first_festival_effect_months <= 0) {
        city_data.festival.first_festival_effect_months = 12;
        switch (city_data.festival.planned.size) {
        case FESTIVAL_SMALL:
            city_sentiment_change_happiness(7);
            break;
        case FESTIVAL_LARGE:
            city_sentiment_change_happiness(9);
            break;
        case FESTIVAL_GRAND:
            city_sentiment_change_happiness(12);
            break;
        }
    } else if (city_data.festival.second_festival_effect_months <= 0) {
        city_data.festival.second_festival_effect_months = 12;
        switch (city_data.festival.planned.size) {
        case FESTIVAL_SMALL:
            city_sentiment_change_happiness(2);
            break;
        case FESTIVAL_LARGE:
            city_sentiment_change_happiness(3);
            break;
        case FESTIVAL_GRAND:
            city_sentiment_change_happiness(5);
            break;
        }
    }
    city_data.festival.months_since_festival = 1;
    city_data.religion.gods[city_data.festival.planned.god].months_since_festival = 0;
    switch (city_data.festival.planned.size) {
    case FESTIVAL_SMALL:
        city_message_post(true, MESSAGE_SMALL_FESTIVAL, 0, 0);
        break;
    case FESTIVAL_LARGE:
        city_message_post(true, MESSAGE_LARGE_FESTIVAL, 0, 0);
        break;
    case FESTIVAL_GRAND:
        city_message_post(true, MESSAGE_GRAND_FESTIVAL, 0, 0);
        if (config_get(CONFIG_GP_CH_GRANDFESTIVAL))
            city_data.religion.gods[city_data.festival.planned.god].blessing_done = 0;

        break;
    }
    city_data.festival.planned.size = FESTIVAL_NONE;
    city_data.festival.planned.months_to_go = 0;
}
void city_festival_update(void) {
    city_data.festival.months_since_festival++;
    if (city_data.festival.first_festival_effect_months)
        --city_data.festival.first_festival_effect_months;

    if (city_data.festival.second_festival_effect_months)
        --city_data.festival.second_festival_effect_months;

    if (city_festival_is_planned()) {
        city_data.festival.planned.months_to_go--;
        if (city_data.festival.planned.months_to_go <= 0)
            throw_party();
    }
}
void city_festival_calculate_costs(void) {
    city_data.festival.small_cost = city_data.population.population / 20 + 10;
    city_data.festival.large_cost = city_data.population.population / 10 + 20;
    city_data.festival.grand_cost = city_data.population.population / 5 + 40;
    city_data.festival.grand_alcohol = city_data.population.population / 500 + 1;
    city_data.festival.not_enough_alcohol = 0;

    int32_t alcohol_resource = RESOURCE_BEER;

    if (city_data.resource.stored_in_warehouses[alcohol_resource] < city_data.festival.grand_alcohol) {
        city_data.festival.not_enough_alcohol = 1;
        if (city_data.festival.selected.size == FESTIVAL_GRAND) {
            city_data.festival.selected.size = FESTIVAL_LARGE;
        }
    }
}

void figure::festival_guy_action() {
    building* b = home();
    switch (b->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        image_set_animation(IMG_PRIEST_OSIRIS);
        break;
    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        image_set_animation(IMG_PRIEST_RA);
        break;
    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        image_set_animation(IMG_PRIEST_PTAH);
        break;
    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        image_set_animation(IMG_PRIEST_SETH);
        break;
    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        image_set_animation(IMG_PRIEST_BAST);
        break;
    case BUILDING_JUGGLER_SCHOOL:
        image_set_animation(ANIM_JUGGLER_WALK);
        break;
    case BUILDING_CONSERVATORY:
        image_set_animation(ANIM_MUSICIAN_WALK);
        break;
    case BUILDING_DANCE_SCHOOL:
        image_set_animation(ANIM_DANCER_WALK);
        break;
    }
    switch (action_state) {
    case 9: // is "dancing" on tile
        festival_remaining_dances--;
        advance_action(10);
        break;
    case 10: // goes to random spot on the square

        // still going to the square center, first
        if (terrain_usage == TERRAIN_USAGE_ROADS) {
            if (do_goto(destination_tile, TERRAIN_USAGE_ROADS, 10))
                terrain_usage = TERRAIN_USAGE_ANY;
        } else {
            //                use_cross_country = true; // todo?
            if (routing_path_id) {
                do_goto(destination_tile, TERRAIN_USAGE_ANY, 11);
            } else {
                bool has_square = building_count_total(BUILDING_FESTIVAL_SQUARE);
                if (festival_remaining_dances == 0 || !has_square) {
                    return poof();
                }

                // choose a random tile on the festival square
                tile2i festival = city_building_get_festival_square_position();
                int rand_x, rand_y;
                int rand_seed = random_short();
                do {
                    int random_tile = rand_seed % 25;
                    rand_x = festival.x() + random_tile % 5;
                    rand_y = festival.y() + random_tile / 5;
                    rand_seed++;
                } while (rand_x == tile.x() && rand_y == tile.y());

                do_goto(map_point(rand_x, rand_y), TERRAIN_USAGE_ANY, 11);
            }
        }
        break;
    case 11: // reached a random spot on the square, now what?
        advance_action(9);
        break;
    }
}