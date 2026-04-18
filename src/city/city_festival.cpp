#include "city_festival.h"

#include <algorithm>

#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "buildings.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/city_message.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "figuretype/festival_guy.h"
#include "graphics/image_groups.h"
#include "core/tokenum.h"

using e_festival_type_tokens = token_holder<e_festival_type, FESTIVAL_NONE, FESTIVAL_MAX>;
e_festival_type_tokens ANK_CONFIG_ENUM(festival_type_tokens);

void city_festival_t::execute_festival() {
    tile2i square_pos = city_building_get_festival_square_position();
    building *square = building_at(square_pos);
    if (!square->is_valid()) {
        return;
    }

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
        case BUILDING_DANCE_SCHOOL: {
                figure* f = b->create_figure_generic(FIGURE_FESTIVAL_GUY, (e_figure_action)ACTION_10_FESTIVAL_GUY_CREATED, BUILDING_SLOT_PRIEST, DIR_4_BOTTOM_LEFT);

                tile2i tile_on_square = square_pos.shifted(rand() % square->size, rand() % square->size);
                f->tile = b->road_access;
                f->set_home(b);
                f->set_destination(square);
                f->destination_tile = tile_on_square;
                f->wait_ticks = rand() % 10;

                auto fguy = f->dcast_festival_guy();
                fguy->runtime_data().festival_remaining_dances = rand() % 10;
            }
            break;
        }
    }

    if (first_festival_effect_months <= 0) {
        first_festival_effect_months = 12;
        switch (planned_size) {
        case FESTIVAL_SMALL:
            g_city.change_happiness(7);
            break;
        case FESTIVAL_LARGE:
            g_city.change_happiness(9);
            break;
        case FESTIVAL_GRAND:
            g_city.change_happiness(12);
            break;
        }
    } else if (second_festival_effect_months <= 0) {
        second_festival_effect_months = 12;
        switch (planned_size) {
        case FESTIVAL_SMALL:
            g_city.change_happiness(2);
            break;
        case FESTIVAL_LARGE:
            g_city.change_happiness(3);
            break;
        case FESTIVAL_GRAND:
            g_city.change_happiness(5);
            break;
        }
    } else {
        switch (planned_size) {
        case FESTIVAL_SMALL:
            g_city.change_happiness(1);
            break;

        case FESTIVAL_LARGE:
            g_city.change_happiness(2);
            break;

        case FESTIVAL_GRAND:
            g_city.change_happiness(3);
            break;
        }
    }

    months_since_festival = 1;

    g_city.religion.gods[planned_god].months_since_festival = 0;
    switch (planned_size) {
    case FESTIVAL_SMALL:
        messages::popup("message_common_festival", 0, 0);
        break;

    case FESTIVAL_LARGE:
        messages::popup("message_lavish_festival", 0, 0);
        break;

    case FESTIVAL_GRAND:
        messages::popup("message_grand_festival", 0, 0);

        if (!!game_features::gameplay_change_grandfestival) {
            g_city.religion.gods[planned_god].blessing_done = 0;
        }

        break;
    }

    planned_size = FESTIVAL_NONE;
    months_till_next= 0;
}

void city_festival_t::advance_month() {
    months_since_festival = std::min<uint8_t>(months_since_festival+1, 60);

    if (first_festival_effect_months > 0) {
        --first_festival_effect_months;
    }

    if (second_festival_effect_months > 0) {
        --second_festival_effect_months;
    }

    if (planned_size == FESTIVAL_NONE) {
        return;
    }

    months_till_next--;
    if (months_till_next <= 0) {
        months_till_next = 0;
        execute_festival();
    }
}
