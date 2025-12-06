#pragma once

#include <cstdint>

#include "game/gods.h"
#include "building/building_type.h"
#include "core/svector.h"
#include "core/tokenum.h"
#include "core/archive.h"

using e_god_tokens_t = const token_holder<e_god, GOD_OSIRIS, MAX_GODS>;
extern e_god_tokens_t e_god_tokens;

enum e_god_status : uint8_t {
    GOD_STATUS_UNKNOWN = 0,
    GOD_STATUS_KNOWN = 1,
    GOD_STATUS_PATRON = 2
};

struct event_religion_update {};
struct event_religion_god_status_update { e_god god; e_god_status status; };


struct god_state {
    struct static_params_t {
        e_god type;
        e_building_type shrine_type;
        e_building_type temple_type;
        e_building_type complex_type;
    };

    e_god type;
    uint8_t mood;
    uint8_t target_mood;
    uint8_t wrath_bolts;
    uint8_t happy_ankhs;
    bool blessing_done;
    bool curse_done;
    uint8_t months_since_festival;
    int8_t unused1;
    int8_t unused2;
    int8_t unused3;
    e_god_status is_known;

    const static_params_t &static_params() const;
};

template<>
struct stable_array_max_elements<god_state::static_params_t> {
    enum { max_elements = MAX_GODS };
};

template<>
struct std::hash<god_state::static_params_t> {
    [[nodiscard]] size_t operator()(const god_state::static_params_t &g) const noexcept {
        return g.type;
    }
};

ANK_CONFIG_STRUCT(god_state::static_params_t, type, shrine_type, temple_type, complex_type)

enum e_god_mood {
    GOD_MOOD_WRATHFUL = -3,
    GOD_MOOD_VERY_ANGRY = -2,
    GOD_MOOD_ANGRY = -1,
    GOD_MOOD_INDIFIRENT = 0,
    GOD_MOOD_FINE = 1,
    GOD_MOOD_PLEASURE = 2,
    GOD_MOOD_EXALTED = 3
};

enum e_god_event {
    GED_EVENT_UNKNOWN = -1,
    GOD_EVENT_MAJOR_BLESSING = 1,
    GOD_EVENT_MINOR_BLESSING = 2,
    GOD_EVENT_MAJOR_CURSE = 3,
    GOD_EVENT_MINOR_CURSE = 4
};

struct city_religion_t {
    god_state gods[MAX_GODS];
    e_god least_happy_god;
    int32_t angry_message_delay;
    bool bast_curse_active;
    uint8_t ra_150_export_profits_months_left;
    uint8_t ra_harshly_reduced_trading_months_left;
    uint8_t ra_no_traders_months_left;
    uint8_t ra_slightly_reduced_trading_months_left;
    uint8_t ra_slightly_increased_trading_months_left;
    int8_t osiris_sank_ships;
    int32_t seth_crush_enemy_troops;
    uint8_t seth_protect_player_troops_months;
    uint8_t osiris_double_farm_yield_days;
    bool osiris_flood_will_destroy_active;

    uint8_t coverage[MAX_GODS];
    uint8_t coverage_common;

    bool is_god_available(int mask, e_god g) { int god_mask = (1 << g); return ((mask & god_mask) == god_mask); };
    void reset();
    int coverage_avg(e_god god);
    void calc_coverage();
    int god_coverage_total(e_god god, e_building_type temple, e_building_type shrine, e_building_type complex);
    void calculate_gods_mood_targets();
    void update();
    void update_mood(e_god randm_god);
    void update_monthly_data(e_god randm_god);
    e_god_status is_god_known(e_god god);
    void set_god_known(e_god god, e_god_status v);
    bool calculate_least_happy_god();
    e_god_mood least_mood();
    int god_happiness(e_god god_id);
    int god_wrath_bolts(e_god god_id);
    int god_happy_angels(e_god god_id);

    bool PTAH_industry_restock();
    bool PTAH_warehouse_destruction();
    bool PTAH_warehouse_restock();
    bool PTAH_industry_destruction();
    bool BAST_houses_destruction();
    int spirit_of_seth_power();
    void spirit_of_seth_mark_used();
    bool osiris_create_shipwreck_flotsam();

    void perform_minor_blessing(e_god god);
    void perform_minor_curse(e_god god);
    void perform_major_blessing(e_god god);
    void perform_major_curse(e_god god);
    void update_curses_and_blessings(e_god randm_god, e_god_event force);
    int months_since_last_festival();
    int months_since_festival(e_god god_id);
    e_god get_least_happy_god();

    using god_states = svector<god_state *, MAX_GODS>;
    god_states known_gods();
};

template<typename ...Args>
inline int make_gods_mask(Args... args) {
    auto gods = {args...};
    int mask = 0;
    for (const auto &g : gods) { mask |= (1 << g); }
    return mask;
}

inline e_god& god_next(e_god& god) { god = e_god(god + 1); return god; }
inline e_god& operator++(e_god& god) { god = e_god(god + 1); return god; };
