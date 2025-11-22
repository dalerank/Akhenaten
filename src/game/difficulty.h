#pragma once

#include "core/archive.h"

int difficulty_starting_kingdom(void);

int difficulty_sentiment(void);

int difficulty_adjust_enemies(int enemies);

int difficulty_adjust_wolf_attack(int attack);

int difficulty_multiply_risk(int risk_delta);

template<typename T>
struct value_dcy {
    svector<T, 5> value;

    T get() const {
        extern uint8_t game_difficulty();
        uint8_t diff = game_difficulty();
        if (value.empty()) return T(0);
        return value[std::min<int>(diff, value.size() - 1)];
    }

    inline operator T() const { return get(); }
};
using int_dcy = value_dcy<int>;
using int8_dcy = value_dcy<int8_t>;
using uint8_dcy = value_dcy<uint8_t>;
using uint16_dcy = value_dcy<uint16_t>;

template<> inline void archive::r<int8_dcy>(pcstr name, int8_dcy &v) { r(name, v.value); }
template<> inline void archive::r<uint8_dcy>(pcstr name, uint8_dcy &v) { r(name, v.value); }
template<> inline void archive::r<uint16_dcy>(pcstr name, uint16_dcy &v) { r(name, v.value); }