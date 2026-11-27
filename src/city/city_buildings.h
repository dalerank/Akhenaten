#pragma once

#include "building/building.h"
#include "core/custom_span.hpp"
#include "core/svector.h"
#include "core/hvector.h"
#include "city/building_index.h"

#include <array>
#include <functional>
#include <vector>

class city_building_registry_t {
public:
    building* get(building_id id) {
        verify_no_crash(id < MAX_BUILDINGS);
        if (id >= MAX_BUILDINGS) {
            return &_records[0];
        }
        return &_records[id];
    }

    building* begin() { return _records.data(); }
    building* end() { return _records.data() + MAX_BUILDINGS; }

    building* at(int grid_offset);
    building* at(int x, int y);
    building* at(tile2i tile);

    building* exists_at(int grid_offset);
    building* exists_at(tile2i tile);

    building* create(e_building_type type, tile2i tile, int orientation);
    building* first(e_building_type type);
    building* next(building_id id, e_building_type type);

    building_id id_first(e_building_type type);
    building_id id_closest(e_building_type type, tile2i center, int8_t radius);

    hvector<building_id, 16> find_farms_in_radius(tile2i center, int radius);
    hvector<building_id, 16> find_monuments_in_radius(tile2i center, int radius);
    hvector<building_id, 64> find_manageable_industry_in_radius(tile2i tile, int size, int radius);

    building_id closest_route(
      building& home, std::function<bool(building&)> pred,
      std::function<int(building&)> fweight = [](auto&) { return 0; });

    void clear_all();
    void update_state();

    // Integral tests only: record 0 of buildings and figures is the shared fallback for invalid ids and is
    // saved, so nothing may write to it except the OG scratch use (see stub_records_guard_check).
    void stub_records_guard_reset();
    void stub_records_guard_check(pcstr phase);

private:
    void delete_UNSAFE(building* b);

    struct stub_records_guard_t {
        bool armed = false;
        std::vector<uint8_t> building0;
        std::vector<uint8_t> figure0;
    };

    std::array<building, MAX_BUILDINGS> _records;
    stub_records_guard_t _stub_guard;
};

city_building_registry_t& city_buildings();

inline building* building_begin() {
    return building_get(1);
}
inline building* building_end() {
    return city_buildings().end();
}

bool building_is_manageable_industry(const building& b);

template<typename T>
T* building_at_ex(tile2i tile) {
    building* b = city_buildings().at(tile);
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

template <typename Types, typename F>
void buildings_of_types_do(const Types& types, F func) {
    building_id id = 0;
    while ((id = building_index().next_after(types, id)) != 0) {
        building& b = *building_get(id);
        if (building_type_any_of(b.type, types)) {
            func(b);
        }
    }
}

template<typename T>
void buildings_valid_do(T func, const std::initializer_list<e_building_type>& types) {
    buildings_of_types_do(types, [&](building& b) {
        if (b.is_valid()) {
            func(b);
        }
    });
}

template<typename T>
void buildings_valid_do(T func, e_building_type type) {
    const std::array<e_building_type, 1> types = {type};
    buildings_of_types_do(types, [&](building& b) {
        if (b.is_valid()) {
            func(b);
        }
    });
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

inline building* building_first_of_type(e_building_type type) {
    return city_buildings().next(1, type);
}

template <typename T>
inline building *building_first_of_type(const T& types) {
    building_id id = 0;
    while ((id = building_index().next_after(types, id)) != 0) {
        building* b = building_get(id);
        if (b->is_valid() && building_type_any_of(b->type, types)) {
            return b;
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
        if (b.is_valid() && b.is_farm()) {
            func(b);
        }
    }
}

template<typename T>
void buildings_workshop_do(T func) {
    for (auto &b : city_buildings()) {
        if (b.is_valid() && b.is_workshop()) {
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
