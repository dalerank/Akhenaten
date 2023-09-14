#pragma once

#include <cstdint>

enum e_god {
    GOD_OSIRIS = 0, // GOD_CERES = 0,
    GOD_RA = 1,     // GOD_NEPTUNE = 1,
    GOD_PTAH = 2,   // GOD_MERCURY = 2,
    GOD_SETH = 3,   // GOD_MARS = 3,
    GOD_BAST = 4,   // GOD_VENUS = 4
};
constexpr uint32_t MAX_GODS = 5;

template<typename ...Args>
inline int make_gods_mask(Args... args) {
    auto gods = {args...};
    int mask = 0;
    for (const auto &g : gods) { mask |= (1 << g); }
    return mask;
}

inline bool is_god_available(int mask, e_god g) { int god_mask = (1 << g); return ((mask & god_mask) == god_mask); }

enum {
    GOD_STATUS_UNKNOWN = 0,
    GOD_STATUS_KNOWN = 1,
    GOD_STATUS_PATRON = 2
};

void city_gods_reset(void);

int god_known_status(int god);

enum e_god_event {
    GOD_EVENT_MAJOR_BLESSING = 1,
    GOD_EVENT_MINOR_BLESSING = 2,
    GOD_EVENT_MAJOR_CURSE = 3,
    GOD_EVENT_MINOR_CURSE = 4
};

void city_gods_update_curses_and_blessings(int randm_god, int FORCE_EVENT = -1);

void city_gods_update(bool mood_calc_only);
bool city_gods_calculate_least_happy(void);
int city_god_happiness(int god_id);
int city_god_wrath_bolts(int god_id);
int city_god_happy_angels(int god_id);

/**
 * @return God ID or -1 if no single god is the least happy
 */
int city_god_least_happy(void);

int city_god_months_since_festival(int god_id);

int city_god_spirit_of_seth_power();
void city_god_spirit_of_seth_mark_used();

int city_god_osiris_create_shipwreck_flotsam(void);

void city_god_blessing_cheat(int god_id);
