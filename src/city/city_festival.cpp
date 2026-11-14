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
#include "figuretype/figure_festival_priest.h"
#include "graphics/image_groups.h"
#include "core/tokenum.h"
#include "game/local_cults.h"

using e_festival_type_tokens = token_holder<e_festival_type, FESTIVAL_NONE, FESTIVAL_MAX>;
e_festival_type_tokens ANK_CONFIG_ENUM(festival_type_tokens);

void city_festival_t::execute_festival() {
    tile2i square_pos = city_building_get_festival_square_position();
    building *square = building_at(square_pos);
    if (!square->is_valid()) {
        return;
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

    if (game_features::gameplay_enhanced_local_cults.to_bool()) {
        g_city.local_cults.refresh_active();
    }
    const bool cult_festival = g_city.local_cults.planned_cult != LOCAL_CULT_NONE
        && game_features::gameplay_enhanced_local_cults.to_bool()
        && g_city.local_cults.is_active((e_local_cult)g_city.local_cults.planned_cult);
    if (cult_festival) {
        g_city.local_cults.apply_cult_festival(
            (e_local_cult)g_city.local_cults.planned_cult,
            (e_festival_theme)g_city.local_cults.planned_theme);
    } else if (planned_god < MAX_GODS) {
        g_city.religion.gods[planned_god].months_since_festival = 0;
        if (game_features::gameplay_enhanced_festival_calendar.to_bool()
            || game_features::gameplay_enhanced_local_cults.to_bool()) {
            g_city.local_cults.apply_theme((e_festival_theme)g_city.local_cults.planned_theme, 2);
        }
    }
    switch (planned_size) {
    case FESTIVAL_SMALL:
        messages::popup("message_common_festival", 0, 0);
        break;

    case FESTIVAL_LARGE:
        messages::popup("message_lavish_festival", 0, 0);
        break;

    case FESTIVAL_GRAND:
        messages::popup("message_grand_festival", 0, 0);

        if (!!game_features::gameplay_change_grandfestival
            && planned_god < MAX_GODS
            && !cult_festival) {
            g_city.religion.gods[planned_god].blessing_done = 0;
        }

        break;
    }

    figure_festival_priest::spawn_celebrants(
      planned_size * figure_festival_priest::current_params().celebrants_per_size);

    planned_size = FESTIVAL_NONE;
    months_till_next = 0;
    g_city.local_cults.planned_theme = FESTIVAL_THEME_NONE;
    g_city.local_cults.planned_cult = LOCAL_CULT_NONE;
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
