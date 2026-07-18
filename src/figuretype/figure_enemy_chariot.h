#pragma once

#include "figuretype/figure_enemy_fast_sword.h"

// Enemy chariots are fast melee raiders. Behaviourally they reuse the shared
// fast-sword enemy logic (marching, formation handling, melee fighting); this
// dedicated type keeps them grouped and gives future chariot-specific tuning
// (speed, the second attack animation) a home. Only Assyrian and Hyksos armies
// field chariots today (enemies.js type3 = 10%); the rest are registered too so
// every FIGURE_ENEMY_*_CHARIOT resolves to a class instead of asserting when a
// mission or the console spawns it. Attack cadence against buildings falls back
// to figure_enemy_fast_sword::interval_attack_delay() (the chariot configs carry
// no interval field), so the leaves do not override it.
class figure_enemy_chariot : public figure_enemy_fast_sword {
public:
    figure_enemy_chariot(figure* f) : figure_enemy_fast_sword(f) {}
};

class figure_assyrian_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_ASSYRIAN_CHARIOT, figure_assyrian_chariot)
    figure_assyrian_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_assyrian_chariot::static_params, interval_attack_delay)

class figure_hyksos_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HYKSOS_CHARIOT, figure_hyksos_chariot)
    figure_hyksos_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_hyksos_chariot::static_params, interval_attack_delay)

class figure_egyptian_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_EGYPTIAN_CHARIOT, figure_egyptian_chariot)
    figure_egyptian_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_egyptian_chariot::static_params, interval_attack_delay)

class figure_canaanite_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_CANAANITE_CHARIOT, figure_canaanite_chariot)
    figure_canaanite_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_canaanite_chariot::static_params, interval_attack_delay)

class figure_kushite_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_KUSHITE_CHARIOT, figure_kushite_chariot)
    figure_kushite_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_kushite_chariot::static_params, interval_attack_delay)

class figure_hittite_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HITTITE_CHARIOT, figure_hittite_chariot)
    figure_hittite_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_hittite_chariot::static_params, interval_attack_delay)

class figure_persian_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_PERSIAN_CHARIOT, figure_persian_chariot)
    figure_persian_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_persian_chariot::static_params, interval_attack_delay)

class figure_libian_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_LIBIAN_CHARIOT, figure_libian_chariot)
    figure_libian_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_libian_chariot::static_params, interval_attack_delay)

class figure_nubian_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_NUBIAN_CHARIOT, figure_nubian_chariot)
    figure_nubian_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_nubian_chariot::static_params, interval_attack_delay)

class figure_phoenician_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_PHOENICIAN_CHARIOT, figure_phoenician_chariot)
    figure_phoenician_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_phoenician_chariot::static_params, interval_attack_delay)

class figure_roman_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_ROMAN_CHARIOT, figure_roman_chariot)
    figure_roman_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_roman_chariot::static_params, interval_attack_delay)

class figure_seapeople_chariot : public figure_enemy_chariot {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_SEAPEOPLE_CHARIOT, figure_seapeople_chariot)
    figure_seapeople_chariot(figure* f) : figure_enemy_chariot(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(figure_seapeople_chariot::static_params, interval_attack_delay)
