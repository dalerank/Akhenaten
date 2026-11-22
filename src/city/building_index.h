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

extern building_type_index g_building_index;

inline constexpr std::array<e_building_type, 20> k_house_building_types = {BUILDING_HOUSE_CRUDE_HUT,
  BUILDING_HOUSE_STURDY_HUT, BUILDING_HOUSE_MEAGER_SHANTY, BUILDING_HOUSE_COMMON_SHANTY, BUILDING_HOUSE_ROUGH_COTTAGE,
  BUILDING_HOUSE_ORDINARY_COTTAGE, BUILDING_HOUSE_MODEST_HOMESTEAD, BUILDING_HOUSE_SPACIOUS_HOMESTEAD,
  BUILDING_HOUSE_MODEST_APARTMENT, BUILDING_HOUSE_SPACIOUS_APARTMENT, BUILDING_HOUSE_COMMON_RESIDENCE,
  BUILDING_HOUSE_SPACIOUS_RESIDENCE, BUILDING_HOUSE_ELEGANT_RESIDENCE, BUILDING_HOUSE_FANCY_RESIDENCE,
  BUILDING_HOUSE_COMMON_MANOR, BUILDING_HOUSE_SPACIOUS_MANOR, BUILDING_HOUSE_ELEGANT_MANOR,
  BUILDING_HOUSE_STATELY_MANOR, BUILDING_HOUSE_MODEST_ESTATE, BUILDING_HOUSE_PALATIAL_ESTATE};
