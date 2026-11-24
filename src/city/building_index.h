#pragma once

#include "building/building_type.h"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <limits>
#include <vector>

class building;

class building_type_index {
public:
    void clear();
    void rebuild();
    void note(const building& b);
    bool verify(const char* phase) const;

    building_id next_after(e_building_type type, building_id after) const {
        if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
            return 0;
        }
        const auto& ids = _by_type[type];
        auto it = std::upper_bound(ids.begin(), ids.end(), after);
        return it == ids.end() ? 0 : *it;
    }

    template <typename Types>
    building_id next_after(const Types& types, building_id after) const {
        building_id best = 0;
        for (e_building_type type : types) {
            const building_id id = next_after(type, after);
            if (id && (!best || id < best)) {
                best = id;
            }
        }
        return best;
    }

private:
    std::array<std::vector<building_id>, BUILDING_MAX> _by_type;
};

building_type_index& building_index();
