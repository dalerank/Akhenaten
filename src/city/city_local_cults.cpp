#include "city/city_local_cults.h"

#include <algorithm>
#include <iterator>

#include "building/building.h"
#include "city/city.h"
#include "game/simulation.h"
#include "game/game_config.h"
#include "game/simulation_time.h"

namespace {

const festival_calendar_rite_t g_calendar_rites[] = {
    {"flood_thanksgiving", MONTH_JULY, FESTIVAL_THEME_HARVEST, LOCAL_CULT_NONE},
    {"opet_procession", MONTH_OCTOBER, FESTIVAL_THEME_CRAFT, LOCAL_CULT_THOTH},
};

bool cult_building_present(e_building_type type) {
    // Prefer VALID scan: buildings[].total can lag or include non-VALID entries.
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building *b = building_get(i);
        if (b && b->state == BUILDING_STATE_VALID && b->type == type) {
            return true;
        }
    }
    return false;
}

} // namespace

void city_local_cults_t::reset() {
    for (int i = 0; i < LOCAL_CULT_MAX; ++i) {
        cults[i] = {};
    }
    mission_restricts = 0;
    farm_bonus_months = 0;
    war_bonus_months = 0;
    craft_bonus_months = 0;
    planned_theme = FESTIVAL_THEME_NONE;
    planned_cult = LOCAL_CULT_NONE;
    last_rite_month = 255;
    last_rite_year = -1;
    last_rite_index = 255;
    unlock_all();
}

void city_local_cults_t::unlock_all() {
    mission_restricts = 0;
    for (int i = LOCAL_CULT_ANUBIS; i < LOCAL_CULT_MAX; ++i) {
        cults[i].unlocked = 1;
    }
}

void city_local_cults_t::load_mission_unlocks(const std::vector<xstring> &names) {
    if (names.empty()) {
        unlock_all();
    } else {
        mission_restricts = 1;
        for (int i = 0; i < LOCAL_CULT_MAX; ++i) {
            cults[i].unlocked = 0;
        }
        for (const auto &name : names) {
            const e_local_cult id = local_cult_from_name(name.c_str());
            if (id > LOCAL_CULT_NONE && id < LOCAL_CULT_MAX) {
                cults[id].unlocked = 1;
            }
        }
    }
    // Mission JS overwrites unlocked after save load; rebuild active from map.
    refresh_active();
}

void city_local_cults_t::set_unlocked(e_local_cult id, bool unlocked) {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return;
    }
    cults[id].unlocked = unlocked ? 1 : 0;
}

bool city_local_cults_t::is_unlocked(e_local_cult id) const {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return false;
    }
    return cults[id].unlocked != 0;
}

bool city_local_cults_t::is_active(e_local_cult id) const {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return false;
    }
    return cults[id].unlocked != 0 && cults[id].active != 0;
}

int city_local_cults_t::appeased_months(e_local_cult id) const {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return 0;
    }
    return cults[id].appeased_months;
}

void city_local_cults_t::refresh_active() {
    if (!game_features::gameplay_enhanced_local_cults.to_bool()) {
        for (int i = 0; i < LOCAL_CULT_MAX; ++i) {
            cults[i].active = 0;
        }
        return;
    }

    for (int i = LOCAL_CULT_ANUBIS; i < LOCAL_CULT_MAX; ++i) {
        const auto &def = local_cult_static((e_local_cult)i);
        cults[i].active = (cults[i].unlocked && cult_building_present(def.building_type)) ? 1 : 0;
    }
}

void city_local_cults_t::apply_theme(e_festival_theme theme, int months) {
    if (months < 1) {
        months = 1;
    }
    // Cap so uint8 never wraps on stacked festivals.
    const int capped = std::min(months, 60);
    switch (theme) {
    case FESTIVAL_THEME_HARVEST:
        farm_bonus_months = (uint8_t)std::max<int>(farm_bonus_months, capped);
        break;
    case FESTIVAL_THEME_WAR:
        war_bonus_months = (uint8_t)std::max<int>(war_bonus_months, capped);
        break;
    case FESTIVAL_THEME_CRAFT:
        craft_bonus_months = (uint8_t)std::max<int>(craft_bonus_months, capped);
        break;
    default:
        break;
    }
}

void city_local_cults_t::apply_cult_festival(e_local_cult cult, e_festival_theme theme) {
    if (!game_features::gameplay_enhanced_local_cults.to_bool()) {
        return;
    }
    if (cult <= LOCAL_CULT_NONE || cult >= LOCAL_CULT_MAX) {
        return;
    }
    if (!is_active(cult)) {
        return;
    }

    const auto &def = local_cult_static(cult);
    if (!def.festival_ok) {
        return;
    }

    cults[cult].appeased_months = (uint8_t)std::max<int>(cults[cult].appeased_months, 6);
    if (def.host_major_god < MAX_GODS) {
        g_city.religion.gods[def.host_major_god].months_since_festival = 0;
        if (g_city.religion.gods[def.host_major_god].mood < 100) {
            g_city.religion.gods[def.host_major_god].mood
                = (uint8_t)std::min<int>(100, g_city.religion.gods[def.host_major_god].mood + 5);
        }
    }
    apply_theme(theme, 2);
}

e_festival_theme city_local_cults_t::next_calendar_theme(int month) const {
    for (const auto &rite : g_calendar_rites) {
        if ((int)rite.month == month) {
            return rite.theme;
        }
    }
    return FESTIVAL_THEME_NONE;
}

pcstr city_local_cults_t::next_calendar_rite_id(int month) const {
    for (const auto &rite : g_calendar_rites) {
        if ((int)rite.month == month) {
            return rite.id;
        }
    }
    return "";
}

void city_local_cults_t::advance_month() {
    refresh_active();

    if (farm_bonus_months > 0) {
        --farm_bonus_months;
    }
    if (war_bonus_months > 0) {
        --war_bonus_months;
    }
    if (craft_bonus_months > 0) {
        --craft_bonus_months;
    }
    for (int i = LOCAL_CULT_ANUBIS; i < LOCAL_CULT_MAX; ++i) {
        if (cults[i].appeased_months > 0) {
            --cults[i].appeased_months;
        }
    }

    if (!game_features::gameplay_enhanced_festival_calendar.to_bool()) {
        return;
    }

    const int month = g_simulation.simtime.month;
    const int year = g_simulation.simtime.year;
    for (int ri = 0; ri < (int)std::size(g_calendar_rites); ++ri) {
        const auto &rite = g_calendar_rites[ri];
        if ((int)rite.month != month) {
            continue;
        }
        if (last_rite_year == year && last_rite_month == month && last_rite_index == (uint8_t)ri) {
            continue;
        }

        last_rite_year = (int16_t)year;
        last_rite_month = (uint8_t)month;
        last_rite_index = (uint8_t)ri;
        apply_theme(rite.theme, 2);
        if (rite.cult != LOCAL_CULT_NONE && is_active(rite.cult)) {
            cults[rite.cult].appeased_months
                = (uint8_t)std::max<int>(cults[rite.cult].appeased_months, 3);
        }
        break;
    }
}
