#pragma once

#include <cstdint>
#include <algorithm>
#include <type_traits>
#include <array>
#include <cassert>

#include "core/tokenum.h"
#include "core/svector.h"
#include "core/xstring.h"

enum e_resource : uint8_t {
    RESOURCE_NONE = 0,
    RESOURCE_MIN = 1,
    RESOURCE_FOOD_MIN = 1,
    RESOURCE_GRAIN = 1,
    RESOURCE_MEAT = 2,
    RESOURCE_LETTUCE = 3,
    RESOURCE_CHICKPEAS = 4,
    RESOURCE_POMEGRANATES = 5,
    RESOURCE_FIGS = 6,
    RESOURCE_FISH = 7,
    RESOURCE_GAMEMEAT = 8,
    RESOURCES_FOODS_MAX = 9,
    RESOURCE_STRAW = 9,
    RESOURCE_WEAPONS = 10,
    RESOURCE_CLAY = 11,
    RESOURCE_BRICKS = 12,
    RESOURCE_POTTERY = 13,
    RESOURCE_BARLEY = 14,
    RESOURCE_BEER = 15,
    RESOURCE_FLAX = 16,
    RESOURCE_LINEN = 17,
    RESOURCE_GEMS = 18,
    RESOURCE_LUXURY_GOODS = 19,
    RESOURCE_TIMBER = 20,
    RESOURCE_GOLD = 21,
    RESOURCE_REEDS = 22,
    RESOURCE_PAPYRUS = 23,
    RESOURCE_STONE = 24,
    RESOURCE_LIMESTONE = 25,
    RESOURCE_GRANITE = 26,
    RESOURCE_UNUSED12 = 27,
    RESOURCE_CHARIOTS = 28,
    RESOURCE_COPPER = 29,
    RESOURCE_SANDSTONE = 30,
    RESOURCE_OIL = 31,
    RESOURCE_HENNA = 32,
    RESOURCE_PAINT = 33,
    RESOURCE_LAMPS = 34,
    RESOURCE_MARBLE = 35,
    RESOURCES_MAX = 36,
    //
    RESOURCE_DEBEN = 36,
    RESOURCE_TROOPS = 37,
    // RESOURCE_WARSHIP
    // RESOURCE_FURNITURE

    RESOURCE_COUNT
};

struct id_resources_t {
    static const xstring none;
    static const xstring grain;
    static const xstring meat;
    static const xstring lettuce;
    static const xstring chickpeas;
    static const xstring pomegranates;
    static const xstring figs;
    static const xstring fish;
    static const xstring gamemeat;
    static const xstring straw;
    static const xstring weapons;
    static const xstring clay;
    static const xstring bricks;
    static const xstring pottery;
    static const xstring barley;
    static const xstring beer;
    static const xstring flax;
    static const xstring linen;
    static const xstring gems;
    static const xstring luxury_goods;
    static const xstring timber;
    static const xstring gold;
    static const xstring reeds;
    static const xstring papyrus;
    static const xstring stone;
    static const xstring limestone;
    static const xstring granite;
    static const xstring chariots;
    static const xstring copper;
    static const xstring sandstone;
    static const xstring oil;
    static const xstring henna;
    static const xstring paint;
    static const xstring lamps;
    static const xstring marble;
    static const xstring deben;
    static const xstring troops;
};

const id_resources_t& resources();

extern const token_holder<e_resource, RESOURCE_NONE, RESOURCE_COUNT> e_resource_tokens;

struct resource_value {
    e_resource type;
    int value;
};

struct resource_allow {
    e_resource type;
    bool allow;
};

inline e_resource& resource_next(e_resource& e) { e = e_resource(e + 1); return e; }
inline e_resource& operator++(e_resource& e) { e = e_resource(e + 1); return e; };

using resource_vec = svector<e_resource, 4>;

struct resource_list : public svector<resource_value, RESOURCES_MAX> {
    inline resource_list() {}

    inline resource_list(std::initializer_list<e_resource> r) {
        for (e_resource i: r) {
            push_back({ i, 0 });
        }
    }

    inline resource_list(e_resource b, e_resource e) {
        for (e_resource i = b; i <= e; ++i) {
            push_back({i, 0});
        }
    }

    inline int &operator[](e_resource r) {
        auto it = std::find_if(begin(), end(), [r] (auto &i) { return i.type == r; });
        if (it == end()) {
            push_back({r, 0});
            return back().value;
        }
        return it->value; 
    }

    inline int operator[](e_resource r) const {
        auto it = std::find_if(begin(), end(), [r] (auto &i) { return i.type == r; });
        return it == end() ? 0 : it->value; 
    }

    inline bool any() const { return std::find_if(begin(), end(), [] (auto &it) { return it.value > 0; }) != end(); }
    static const resource_list foods;
    static const resource_list all;
    static const resource_list values;
};


enum e_inventory_good {
    INVENTORY_FOOD1 = 0,
    INVENTORY_FOOD2 = 1,
    INVENTORY_FOOD3 = 2,
    INVENTORY_FOOD4 = 3,
    INVENTORY_GOOD1 = 4,
    INVENTORY_GOOD2 = 5,
    INVENTORY_GOOD3 = 6,
    INVENTORY_GOOD4 = 7,
    // helper constants
    INVENTORY_MIN_FOOD = 0,
    INVENTORY_MAX_FOOD = 4,
    INVENTORY_MIN_GOOD = 4,
    INVENTORY_MAX_GOOD = 8,
    INVENTORY_MAX = 8
};

enum e_resource_unit {
    RESOURCE_UNIT_PILE = 0,
    RESOURCE_UNIT_BLOCK = 1,
    RESOURCE_UNIT_WEAPON = 2,
    RESOURCE_UNIT_CHARIOT = 3
};

pcstr resource_name(e_resource resource);
e_resource resource_type(const xstring &name);
int stack_units_by_resource(int resource);
int stack_proper_quantity(int full, int resource);

const e_resource INV_RESOURCES[20] = {
  RESOURCE_POTTERY,
  RESOURCE_LUXURY_GOODS,
  RESOURCE_LINEN,
  RESOURCE_BEER,
  RESOURCE_GRAIN,
  RESOURCE_MEAT,
  RESOURCE_LETTUCE,
  RESOURCE_CHICKPEAS,
  RESOURCE_POMEGRANATES,
  RESOURCE_FIGS,
  RESOURCE_FISH,
  RESOURCE_GAMEMEAT,
};

// enum {
//     WORKSHOP_NONE = 0,
//     //
//     WORKSHOP_POTTERY,
//     WORKSHOP_BEER,
//     WORKSHOP_PAPYRUS,
//     WORKSHOP_JEWELS,
//     WORKSHOP_LINEN,
//     WORKSHOP_BRICKS,
//     WORKSHOP_CATTLE,
//     WORKSHOP_WEAPONS,
//     WORKSHOP_CHARIOTS,
//
//     WORKSHOP_LAMPS,
//     WORKSHOP_PAINT
// };

enum {
    RESOURCE_IMAGE_STORAGE = 0,
    RESOURCE_IMAGE_CART = 1,
    RESOURCE_IMAGE_FOOD_CART = 2,
    RESOURCE_IMAGE_ICON = 3,
    RESOURCE_IMAGE_ICON_WEIRD = 3
};

int resource_image_offset(int resource, int type);

template<typename ... Args>
bool resource_type_any_of(e_resource type, Args ... args) {
    int types[] = {args...};
    return (std::find(std::begin(types), std::end(types), type) != std::end(types));
}

inline bool resource_is_food(e_resource resource) {
    return resource_type_any_of
    (
        resource, 
        RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_LETTUCE,
        RESOURCE_CHICKPEAS, RESOURCE_POMEGRANATES, RESOURCE_FIGS,
        RESOURCE_FISH, RESOURCE_GAMEMEAT
    );
}

e_resource get_raw_resource(e_resource resource);
