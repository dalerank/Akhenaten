#pragma once

#include <cstdint>
#include <algorithm>
#include <type_traits>
#include <array>
#include <cassert>
#include <numeric>

#include "core/tokenum.h"
#include "core/archive.h"

enum e_resource : uint8_t {
    RESOURCE_NONE = 0,
    RESOURCE_GRAIN = 1, // RESOURCE_FLOUR -> RESOURCE_BREAD -> RESOURCE_PORRIDGE 
    RESOURCE_MEAT = 2, // RESOURCE_DRIED_MEAT -> RESOURCE_SALTED_MEAT 
    RESOURCE_LETTUCE = 3,
    RESOURCE_CHICKPEAS = 4, // RESOURCE_HUMMUS 
    RESOURCE_POMEGRANATES = 5, // RESOURCE_POMEGRANATE_DYE 
    RESOURCE_FIGS = 6, // RESOURCE_FIG_WINE -> RESOURCE_DATES 
    RESOURCE_FISH = 7,  // -> RESOURCE_FISH_DRIED 
    RESOURCE_GAMEMEAT = 8,
    RESOURCE_STRAW = 9, // -> RESOURCE_BASKETS -> RESOURCE_MATS 
    RESOURCE_WEAPONS = 10, // -> RESOURCE_ARROWS -> RESOURCE_SHIELDS -> RESOURCE_ARMOR_PLATES 
        // -> RESOURCE_COMPOSITE_BOWS, RESOURCE_SCALE_ARMOR, RESOURCE_HELMETS, RESOURCE_MACES, RESOURCE_KHOPESH, RESOURCE_SLINGS, RESOURCE_BATTERING_RAMS 
    RESOURCE_CLAY = 11, // RESOURCE_CLAY_TABLETS -> RESOURCE_FIGURINES 
    RESOURCE_BRICKS = 12,
    RESOURCE_POTTERY = 13, // RESOURCE_DECORATIVE_VASES 
    RESOURCE_BARLEY = 14, // RESOURCE_MALT -> RESOURCE_BEER
    RESOURCE_BEER = 15, // RESOURCE_STRONG_BEER, RESOURCE_YEAST 
    RESOURCE_FLAX = 16, // RESOURCE_ROPE, RESOURCE_FISHING_NETS
    RESOURCE_LINEN = 17, // RESOURCE_FINE_LINEN -> RESOURCE_MUMMY_WRAPPINGS -> RESOURCE_SAILS, RESOURCE_CLOTHING, RESOURCE_TAPESTRIES 
    RESOURCE_GEMS = 18, // RESOURCE_AMULETS 
    RESOURCE_LUXURY_GOODS = 19, // -> RESOURCE_BRONZE_MIRRORS, RESOURCE_JEWELRY_BOXES, RESOURCE_COSMETICS, RESOURCE_FINE_FURNITURE 
    RESOURCE_TIMBER = 20, // -> RESOURCE_CHARCOAL, RESOURCE_DICE, RESOURCE_SCAFFOLDING 
    RESOURCE_GOLD = 21, // RESOURCE_GOLD_JEWELRY , RESOURCE_GOLDEN_MASKS 
    RESOURCE_REEDS = 22, // RESOURCE_REED_BOATS, 
    RESOURCE_PAPYRUS = 23,
    RESOURCE_STONE = 24, // RESOURCE_STONE_TOOLS, RESOURCE_GRINDING_STONES, RESOURCE_MONUMENTS 
    RESOURCE_LIMESTONE = 25, // RESOURCE_LIME, RESOURCE_MORTAR, RESOURCE_STATUES 
    RESOURCE_GRANITE = 26, // RESOURCE_GRANITE_STATUES, RESOURCE_OBELISKS, RESOURCE_SARCOPHAGS, RESOURCE_POLISHED_GRANITE 
    RESOURCE_UNUSED12 = 27,
    RESOURCE_CHARIOTS = 28, // RESOURCE_CHARIOT_WHEELS, RESOURCE_CHARIOT_PARTS, RESOURCE_RACING_CHARIOTS 
    RESOURCE_COPPER = 29, // RESOURCE_BRONZE, RESOURCE_COPPER_TOOLS, RESOURCE_COPPER_VESSELS, RESOURCE_COPPER_MIRRORS 
    RESOURCE_SANDSTONE = 30, // RESOURCE_TEMPLE_STONES 
    RESOURCE_OIL = 31, // RESOURCE_LAMP_OIL, RESOURCE_EMBALMING_OILS 
    RESOURCE_HENNA = 32, // RESOURCE_HENNA_DYE 
    RESOURCE_PAINT = 33,
    RESOURCE_LAMPS = 34, // RESOURCE_OIL_LAMPS, RESOURCE_TEMPLE_LAMPS 
    RESOURCE_MARBLE = 35, // RESOURCE_MARBLE_STATUES, RESOURCE_MARBLE_COLUMNS, RESOURCE_MARBLE_TILES 

    //
    RESOURCE_DEBEN = 36,
    RESOURCE_TROOPS = 37,
    // RESOURCE_WARSHIP
    // RESOURCE_FURNITURE
    // RESOURCE_DATES 
    // RESOURCE_GRAPES 
    // RESOURCE_WINE 
    // RESOURCE_ONIONS 
    // RESOURCE_BEANS 
    // RESOURCE_CUCUMBERS 
    // RESOURCE_MELONS 
    // RESOURCE_CATTLE 
    // RESOURCE_GOATS 
    // RESOURCE_MILK 
    // RESOURCE_CHEESE 
    // RESOURCE_LEATHER 
    // RESOURCE_INCENSE 
    // RESOURCE_MYRRH 
    // RESOURCE_FRANKINCENSE 
    // RESOURCE_CINNAMON 
    // RESOURCE_PEPPER 
    // RESOURCE_SALT 
    //  -> RESOURCE_FISH_SALTED 
    // RESOURCE_ALOE -> RESOURCE_HERBS 
    // RESOURCE_KOHL 
    // RESOURCE_PERFUMES 
    // RESOURCE_NATRON 
    // RESOURCE_IVORY 
    // RESOURCE_EBONY 
    // RESOURCE_CEDAR 
    // RESOURCE_OBSIDIAN 
    // RESOURCE_TURQUOISE 
    // RESOURCE_MALACHITE 
    // RESOURCE_COTTON 
    // RESOURCE_ROPE 
    // RESOURCE_AMBER 
    // RESOURCE_PEARLS 
    // RESOURCE_SILVER 
    // RESOURCE_ELECTRUM 
    // RESOURCE_CANOPIC_JARS 
    // RESOURCE_AMULETS 
    // RESOURCE_SCROLLS 
    // RESOURCE_INK 
    // RESOURCE_MORTAR 
    // RESOURCE_RIVER_SHELLS -> RESOURCE_PEARLS_NILE 
    // RESOURCE_LEOPARD_SKINS 
    // RESOURCE_OSTRICH_FEATHERS 
    // RESOURCE_OSTRICH_EGGS 
    // RESOURCE_QUARTZITE 
    // RESOURCE_BASALT 
    // RESOURCE_TIN 
    // RESOURCE_LEAD 
    // RESOURCE_ACACIA 
    // RESOURCE_SYCAMORE 
    // RESOURCE_PALM_FRONDS -> RESOURCE_PALM_WINE -> RESOURCE_COCONUTS 
    // RESOURCE_SESAME -> RESOURCE_SESAME_OIL 
    // RESOURCE_CAMELS
    // RESOURCE_HORSES 
    // RESOURCE_SLEDGES 
    // RESOURCE_SHABTI
    // RESOURCE_SARCOPHAGI 
    // RESOURCE_MUMMY_WRAPPINGS
    // RESOURCE_SACRED_OILS, RESOURCE_SACRED_SCARABS, RESOURCE_TEMPLE_INCENSE 
    // RESOURCE_BASKETS, RESOURCE_MATS, RESOURCE_SANDALS 

    RESOURCE_COUNT
};
using e_resource_tokens_t = token_holder<e_resource, RESOURCE_NONE, RESOURCE_COUNT>;

constexpr e_resource RESOURCES_FOODS_MAX = RESOURCE_STRAW;
constexpr e_resource RESOURCES_MIN = RESOURCE_GRAIN;
constexpr e_resource RESOURCES_FOOD_MIN = RESOURCE_GRAIN;
constexpr e_resource RESOURCES_MAX = RESOURCE_DEBEN;

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

struct resource_value {
    e_resource type;
    uint16_t value;
};

struct resource_allow {
    e_resource type;
    bool allow;
};
ANK_CONFIG_STRUCT(resource_allow, type, allow)

using resource_allow_vec = svector<resource_allow, RESOURCES_MAX>;

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

    inline uint16_t &operator[](e_resource r) {
        auto it = std::find_if(begin(), end(), [r] (auto &i) { return i.type == r; });
        if (it == end()) {
            push_back({r, 0});
            return back().value;
        }
        return it->value; 
    }

    inline uint16_t operator[](e_resource r) const {
        auto it = std::find_if(begin(), end(), [r] (auto &i) { return i.type == r; });
        return it == end() ? 0 : it->value; 
    }

    inline void append(const resource_list &o) {
        for (auto &t: o) {
            (*this)[t.type] += t.value;
        }
    }

    inline bool any() const { return std::find_if(begin(), end(), [] (auto &it) { return it.value > 0; }) != end(); }
    inline uint16_t sum() const { return std::accumulate(begin(), end(), 0, [] (int r, resource_value it) { return r + it.value; }); }
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
