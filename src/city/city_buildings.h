#pragma once

#include "building/building.h"
#include "core/custom_span.hpp"

inline building *building_begin() { return building_get(1); }
inline building *building_end() { return building_get(MAX_BUILDINGS); }

custom_span<building> &city_buildings();

building *building_next(building_id id, e_building_type type);

building_id building_id_first(e_building_type type);
building_id building_id_random(e_building_type type);
building_id building_id_closest(e_building_type type, tile2i center, int8_t radius);

building *building_first(e_building_type type);

building *building_create(e_building_type type, tile2i tile, int orientation);

building *building_at(int grid_offset);
building *building_at(int x, int y);
building *building_at(tile2i tile);

bool building_exists_at(int grid_offset, building *b);
bool building_exists_at(tile2i point, building *b);

void building_clear_all();
void building_update_state();
building_id building_closest_route(building &home, std::function<bool(building &)> pred, std::function<int (building &)> fweight = [] (auto &) { return 0; });

template<typename T>
T* building_at_ex(tile2i tile) {
    building *b = building_at(tile);
    return smart_cast<T>(b);
}

template<typename T>
T *building_get_ex(building_id bid) {
    building *b = building_get(bid);
    return smart_cast<T>(b);
}

template<typename T>
void buildings_valid_do(T func) {
    for (auto &b : city_buildings()) {
        if (b.is_valid()) {
            func(b);
        }
    }
}

template<typename T>
void buildings_valid_do(T func, const std::initializer_list<e_building_type>& types) {
    for (auto &b : city_buildings()) {
        if (b.is_valid() && building_type_any_of(b, types)) {
            func(b);
        }
    }
}

template<typename T>
void buildings_valid_do(T func, e_building_type type) {
    for (auto &b : city_buildings()) {
        if (b.is_valid() && (b.type == type)) {
            func(b);
        }
    }
}

template <typename T>
inline building *building_first(T pred) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->is_valid() && pred(*it)) {
            return it;
        }
    }
    return nullptr;
}

template <typename B, typename T>
inline B *building_first_ex(T pred) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        B *b = smart_cast<B>(it);

        if (b && b->is_valid() && pred(b)) {
            return b;
        }
    }
    return nullptr;
}

template <typename T>
inline building *building_first_of_type(const T& types) {
    for (auto &b : city_buildings()) {
        if (b.is_valid() && building_type_any_of(b, types)) {
            return &b;
        }
    }
    return nullptr;
}

template<typename T>
inline building *buildings_valid_first(T func) {
    for (auto &b : city_buildings()) {
        if (b.is_valid()) {
            if (func(b)) {
                return &b;
            }
        }
    }
    return nullptr;
}

template<typename T, typename F>
void buildings_valid_do(F func) {
    for (auto &b : city_buildings()) {
        if (!b.is_valid()) {
            continue;
        }

        T *ptr = smart_cast<T *>(b.dcast());
        if (ptr) {
            func(ptr);
        }
    }
}

template<typename T>
void buildings_valid_farms_do(T func) {
    for (auto &b : city_buildings()) {
        if (b.is_valid() && building_is_farm(b)) {
            func(b);
        }
    }
}

template<typename T>
void buildings_workshop_do(T func) {
    for (auto &b : city_buildings()) {
        if (b.is_valid() && building_is_workshop(b.type)) {
            func(b);
        }
    }
}

template<typename Array, typename ... Args>
void buildings_get(Array &arr, Args ... args) {
    int types[] = { args... };
    for (const auto &type : types) {
        for (building *it = building_begin(), *e = building_end(); it != e; ++it) {
            if (it->type == type) {
                arr.push_back(it);
            }
        }
    }
}
