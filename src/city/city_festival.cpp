#include "city_festival.h"

#include <algorithm>

#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "buildings.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/city_finance.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "figuretype/festival_guy.h"
#include "graphics/image_groups.h"

bool city_festival_t::is_planned() {
    return planned.size != FESTIVAL_NONE;
}

int city_festival_t::months_till_next() {
    return planned.months_to_go;
}

xstring city_festival_t::selected_god_name() {
    auto key = (e_god_short)g_city.festival.selected_god;
    return bstring16("#god_", e_god_short_tokens.name(key)).c_str();
}

void city_festival_t::select_god(e_god god_id) {
    selected_god = god_id;
}

void city_festival_t::select_size(e_festival_type size) {
    selected_size = size;
}

void city_festival_t::schedule(e_god god, e_festival_type festival_size, int months_until_festival, int festival_cost, int beer_to_remove) {
    planned.god = god;
    planned.size = festival_size;
    planned.months_to_go = static_cast<int8_t>(std::clamp(months_until_festival, -128, 127));

    events::emit(event_finance_request{ efinance_request_festival, festival_cost });
    events::emit(event_festival_hold{ planned.god, planned.size });

    if (festival_size == FESTIVAL_GRAND && beer_to_remove > 0) {
        const uint16_t amount = static_cast<uint16_t>(std::clamp(beer_to_remove, 0, 65535));
        events::emit(event_storageyards_remove_resource{ RESOURCE_BEER, amount });
    }
}

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
        switch (planned.size) {
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
        switch (planned.size) {
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
        switch (planned.size) {
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

    g_city.religion.gods[planned.god].months_since_festival = 0;
    switch (planned.size) {
    case FESTIVAL_SMALL:
        messages::popup("message_common_festival", 0, 0);
        break;

    case FESTIVAL_LARGE:
        messages::popup("message_lavish_festival", 0, 0);
        break;

    case FESTIVAL_GRAND:
        messages::popup("message_grand_festival", 0, 0);

        if (!!game_features::gameplay_change_grandfestival) {
            g_city.religion.gods[planned.god].blessing_done = 0;
        }

        break;
    }

    planned.size = FESTIVAL_NONE;
    planned.months_to_go = 0;
}

void city_festival_t::update() {
    months_since_festival = std::min<uint8_t>(months_since_festival+1, 60);

    if (first_festival_effect_months > 0) {
        --first_festival_effect_months;
    }

    if (second_festival_effect_months > 0) {
        --second_festival_effect_months;
    }

    if (!is_planned()) {
        return;
    }

    planned.months_to_go--;
    if (planned.months_to_go <= 0) {
        planned.months_to_go = 0;
        execute_festival();
    }
}
