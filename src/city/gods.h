#pragma once

#include <cstdint>
#include "core/svector.h"

enum e_god {
    GOD_OSIRIS = 0, // GOD_CERES = 0,
    GOD_RA = 1,     // GOD_NEPTUNE = 1,
    GOD_PTAH = 2,   // GOD_MERCURY = 2,
    GOD_SETH = 3,   // GOD_MARS = 3,
    GOD_BAST = 4,   // GOD_VENUS = 4
    MAX_GODS,
    GOD_UNKNOWN = MAX_GODS
};

enum e_god_status {
    GOD_STATUS_UNKNOWN = 0,
    GOD_STATUS_KNOWN = 1,
    GOD_STATUS_PATRON = 2
};

struct god_state {
    e_god type;
    uint8_t mood;
    uint8_t target_mood;
    uint8_t wrath_bolts;
    uint8_t happy_ankhs;
    bool blessing_done;
    bool curse_done;
    uint32_t months_since_festival;
    int8_t unused1;
    int8_t unused2;
    int8_t unused3;
    e_god_status is_known;
};


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
    GOD_EVENT_MAJOR_BLESSING = 1,
    GOD_EVENT_MINOR_BLESSING = 2,
    GOD_EVENT_MAJOR_CURSE = 3,
    GOD_EVENT_MINOR_CURSE = 4
};

template<typename ...Args>
inline int make_gods_mask(Args... args) {
    auto gods = {args...};
    int mask = 0;
    for (const auto &g : gods) { mask |= (1 << g); }
    return mask;
}

svector<god_state *, MAX_GODS> city_gods_knowns();

inline bool city_gods_is_available(int mask, e_god g) { int god_mask = (1 << g); return ((mask & god_mask) == god_mask); }

void city_gods_reset();

e_god_status city_gods_is_known(e_god god);
void city_god_set_known(e_god god, e_god_status v);

void city_gods_update_curses_and_blessings(int randm_god, int FORCE_EVENT = -1);

void city_gods_update(bool mood_calc_only);
bool city_gods_calculate_least_happy();
int city_god_happiness(int god_id);
int city_god_wrath_bolts(int god_id);
int city_god_happy_angels(int god_id);
int city_months_since_last_festival();

e_god_mood city_gods_least_mood();
e_god city_god_least_happy();

int city_god_months_since_festival(int god_id);

int city_god_spirit_of_seth_power();
void city_god_spirit_of_seth_mark_used();

bool city_god_osiris_create_shipwreck_flotsam();

void city_god_blessing_cheat(e_god god_id);
void city_god_upset_cheat(e_god god_id);
