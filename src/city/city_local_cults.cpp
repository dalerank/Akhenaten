#include "city/city_local_cults.h"

#include <algorithm>
#include <iterator>

#include "building/building.h"
#include "city/city.h"
#include "city/city_local_cults_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/simulation.h"
#include "game/game_config.h"
#include "game/simulation_time.h"
#include "io/chunk_serializer.h"

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

local_cults_state& city_local_cults_state() {
    return xvalue<local_cults_state>::ref();
}

local_cults_system city_local_cults() {
    return local_cults_system(city_local_cults_state(),
      {g_city.gods, g_simulation.simtime.month, g_simulation.simtime.year});
}

class local_cults_sim_system : public sim_system {
public:
    const char* name() const override { return "local_cults"; }
    void on_month() override { city_local_cults().advance_month(); }
    void push_save_sections(int file_version) override { g_chunk_io.push_chunk<local_cults_chunk>(64, false); }
};

void ANK_REGISTER_APPLICATION_MODULE(register_local_cults_system) {
    static local_cults_sim_system system;
    g_simulation.register_system(&system);
}

void local_cults_system::reset() {
    _state = {};
    unlock_all();
}

void local_cults_system::unlock_all() {
    _state.mission_restricts = 0;
    for (int i = LOCAL_CULT_ANUBIS; i < LOCAL_CULT_MAX; ++i) {
        _state.cults[i].unlocked = 1;
    }
}

void local_cults_system::load_mission_unlocks(const std::vector<xstring>& names) {
    if (names.empty()) {
        unlock_all();
    } else {
        _state.mission_restricts = 1;
        for (int i = 0; i < LOCAL_CULT_MAX; ++i) {
            _state.cults[i].unlocked = 0;
        }
        for (const auto &name : names) {
            const e_local_cult id = local_cult_from_name(name.c_str());
            if (id > LOCAL_CULT_NONE && id < LOCAL_CULT_MAX) {
                _state.cults[id].unlocked = 1;
            }
        }
    }
    // Mission JS overwrites unlocked after save load; rebuild active from map.
    refresh_active();
}

void local_cults_system::set_unlocked(e_local_cult id, bool unlocked) {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return;
    }
    _state.cults[id].unlocked = unlocked ? 1 : 0;
}

bool local_cults_state::is_unlocked(e_local_cult id) const {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return false;
    }
    return cults[id].unlocked != 0;
}

bool local_cults_state::is_active(e_local_cult id) const {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return false;
    }
    return cults[id].unlocked != 0 && cults[id].active != 0;
}

int local_cults_state::appeased_months(e_local_cult id) const {
    if (id <= LOCAL_CULT_NONE || id >= LOCAL_CULT_MAX) {
        return 0;
    }
    return cults[id].appeased_months;
}

void local_cults_system::refresh_active() {
    if (!game_features::gameplay_enhanced_local_cults.to_bool()) {
        for (int i = 0; i < LOCAL_CULT_MAX; ++i) {
            _state.cults[i].active = 0;
        }
        return;
    }

    for (int i = LOCAL_CULT_ANUBIS; i < LOCAL_CULT_MAX; ++i) {
        const auto &def = local_cult_static((e_local_cult)i);
        _state.cults[i].active = (_state.cults[i].unlocked && cult_building_present(def.building_type)) ? 1 : 0;
    }
}

void local_cults_system::apply_theme(e_festival_theme theme, int months) {
    if (months < 1) {
        months = 1;
    }
    // Cap so uint8 never wraps on stacked festivals.
    const int capped = std::min(months, 60);
    switch (theme) {
    case FESTIVAL_THEME_HARVEST:
        _state.farm_bonus_months = (uint8_t)std::max<int>(_state.farm_bonus_months, capped);
        break;
    case FESTIVAL_THEME_WAR:
        _state.war_bonus_months = (uint8_t)std::max<int>(_state.war_bonus_months, capped);
        break;
    case FESTIVAL_THEME_CRAFT:
        _state.craft_bonus_months = (uint8_t)std::max<int>(_state.craft_bonus_months, capped);
        break;
    default:
        break;
    }
}

void local_cults_system::apply_cult_festival(e_local_cult cult, e_festival_theme theme) {
    if (!game_features::gameplay_enhanced_local_cults.to_bool()) {
        return;
    }
    if (cult <= LOCAL_CULT_NONE || cult >= LOCAL_CULT_MAX) {
        return;
    }
    if (!_state.is_active(cult)) {
        return;
    }

    const auto &def = local_cult_static(cult);
    if (!def.festival_ok) {
        return;
    }

    _state.cults[cult].appeased_months = (uint8_t)std::max<int>(_state.cults[cult].appeased_months, 6);
    if (def.host_major_god < MAX_GODS) {
        _ctx.gods.gods[def.host_major_god].months_since_festival = 0;
        if (_ctx.gods.gods[def.host_major_god].mood < 100) {
            _ctx.gods.gods[def.host_major_god].mood
              = (uint8_t)std::min<int>(100, _ctx.gods.gods[def.host_major_god].mood + 5);
        }
    }
    apply_theme(theme, 2);
}

e_festival_theme local_cults_state::next_calendar_theme(int month) const {
    for (const auto &rite : g_calendar_rites) {
        if ((int)rite.month == month) {
            return rite.theme;
        }
    }
    return FESTIVAL_THEME_NONE;
}

pcstr local_cults_state::next_calendar_rite_id(int month) const {
    for (const auto &rite : g_calendar_rites) {
        if ((int)rite.month == month) {
            return rite.id;
        }
    }
    return "";
}

void local_cults_system::advance_month() {
    refresh_active();

    if (_state.farm_bonus_months > 0) {
        --_state.farm_bonus_months;
    }
    if (_state.war_bonus_months > 0) {
        --_state.war_bonus_months;
    }
    if (_state.craft_bonus_months > 0) {
        --_state.craft_bonus_months;
    }
    for (int i = LOCAL_CULT_ANUBIS; i < LOCAL_CULT_MAX; ++i) {
        if (_state.cults[i].appeased_months > 0) {
            --_state.cults[i].appeased_months;
        }
    }

    if (!game_features::gameplay_enhanced_festival_calendar.to_bool()) {
        return;
    }

    const int month = _ctx.month;
    const int year = _ctx.year;
    for (int ri = 0; ri < (int)std::size(g_calendar_rites); ++ri) {
        const auto &rite = g_calendar_rites[ri];
        if ((int)rite.month != month) {
            continue;
        }
        if (_state.last_rite_year == year && _state.last_rite_month == month && _state.last_rite_index == (uint8_t)ri) {
            continue;
        }

        _state.last_rite_year = (int16_t)year;
        _state.last_rite_month = (uint8_t)month;
        _state.last_rite_index = (uint8_t)ri;
        apply_theme(rite.theme, 2);
        if (rite.cult != LOCAL_CULT_NONE && _state.is_active(rite.cult)) {
            _state.cults[rite.cult].appeased_months
              = (uint8_t)std::max<int>(_state.cults[rite.cult].appeased_months, 3);
        }
        break;
    }
}
