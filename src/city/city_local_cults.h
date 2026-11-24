#pragma once

#include <cstdint>
#include <vector>

#include "core/xstring.h"
#include "game/local_cults.h"

struct local_cult_runtime_t {
    uint8_t unlocked = 0;
    uint8_t active = 0;
    uint8_t appeased_months = 0;
    uint8_t reserved = 0;
};

struct festival_calendar_rite_t {
    pcstr id;
    uint8_t month;
    e_festival_theme theme;
    e_local_cult cult;
};

struct local_cults_state {
    local_cult_runtime_t cults[LOCAL_CULT_MAX] = {};
    uint8_t mission_restricts = 0;
    uint8_t farm_bonus_months = 0;
    uint8_t war_bonus_months = 0;
    uint8_t craft_bonus_months = 0;
    uint8_t planned_theme = FESTIVAL_THEME_NONE;
    uint8_t planned_cult = LOCAL_CULT_NONE;
    uint8_t last_rite_month = 255;
    int16_t last_rite_year = -1;
    uint8_t last_rite_index = 255;
    uint8_t reserved_pad[3] = {};

    bool is_unlocked(e_local_cult id) const;
    bool is_active(e_local_cult id) const;
    int appeased_months(e_local_cult id) const;
    e_festival_theme next_calendar_theme(int month) const;
    pcstr next_calendar_rite_id(int month) const;
};

struct gods_state;

struct local_cults_context {
    gods_state& gods;
    int month;
    int year;
};

class local_cults_system {
public:
    local_cults_system(local_cults_state& state, const local_cults_context& ctx) : _state(state), _ctx(ctx) {}

    void reset();
    void load_mission_unlocks(const std::vector<xstring> &names);
    void unlock_all();
    void set_unlocked(e_local_cult id, bool unlocked);
    void refresh_active();
    void advance_month();
    void apply_theme(e_festival_theme theme, int months = 2);
    void apply_cult_festival(e_local_cult cult, e_festival_theme theme);

private:
    local_cults_state& _state;
    local_cults_context _ctx;
};

local_cults_state& city_local_cults_state();
local_cults_system city_local_cults();
