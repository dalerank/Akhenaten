#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

/**
 * @file
 * Type definitions for resources
 */

/**
 * Resource types
 */

#define RESOURCES_MAX 36
#define RESOURCES_FOODS_MAX 9

enum e_resource {
    RESOURCE_NONE = 0,
    RESOURCE_GRAIN = 1,        // RESOURCE_WHEAT = 1,
    RESOURCE_MEAT = 2,         // RESOURCE_VEGETABLES = 2,
    RESOURCE_LETTUCE = 3,      // RESOURCE_FRUIT = 3,
    RESOURCE_CHICKPEAS = 4,    // RESOURCE_OLIVES = 4,
    RESOURCE_POMEGRANATES = 5, // RESOURCE_VINES = 5,
    RESOURCE_FIGS = 6,         // RESOURCE_MEAT_C3 = 6,
    RESOURCE_FISH = 7,         // RESOURCE_WINE = 7,
    RESOURCE_GAMEMEAT = 8,     // RESOURCE_OIL_C3 = 8,
    RESOURCE_STRAW = 9,        // RESOURCE_IRON = 9,
    RESOURCE_WEAPONS = 10,     // RESOURCE_TIMBER_C3 = 10,
    RESOURCE_CLAY = 11,
    RESOURCE_BRICKS = 12,  // RESOURCE_MARBLE_C3 = 12,
    RESOURCE_POTTERY = 13, // RESOURCE_WEAPONS_C3 = 13,
    RESOURCE_BARLEY = 14,  // RESOURCE_FURNITURE = 14,
    RESOURCE_BEER = 15,    // RESOURCE_POTTERY_C3 = 15,
    RESOURCE_FLAX = 16,    // RESOURCE_DENARII = 16,
    RESOURCE_LINEN = 17,   // RESOURCE_TROOPS_C3 = 17,
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
    //
    RESOURCE_DEBEN = 36,
    RESOURCE_TROOPS = 37,
    // helper constants
    RESOURCE_MIN = 1,
    RESOURCE_MIN_FOOD = 1,
};

enum {
    //    INVENTORY_FOOD1 = 0,
    //    INVENTORY_FOOD2 = 1,
    //    INVENTORY_FOOD3 = 2,
    //    INVENTORY_FOOD4 = 3,
    INVENTORY_GOOD1 = 5,
    INVENTORY_GOOD2 = 7,
    INVENTORY_GOOD3 = 6,
    INVENTORY_GOOD4 = 4,
    // helper constants
    INVENTORY_MIN_FOOD = 0,
    INVENTORY_MAX_FOOD = 4,
    INVENTORY_MIN_GOOD = 4,
    INVENTORY_MAX_GOOD = 8,
    INVENTORY_MAX = 8
};

enum { RESOURCE_UNIT_PILE = 0, RESOURCE_UNIT_BLOCK = 1, RESOURCE_UNIT_WEAPON = 2, RESOURCE_UNIT_CHARIOT = 3 };

int ALLOWED_FOODS(int i);
bool is_food_allowed(int resource);
void set_allowed_food(int i, int resource);
int stack_units_by_resource(int resource);
int stack_proper_quantity(int full, int resource);

const int INV_RESOURCES[20] = {
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

int resource_get_icon(int resource, int quantity = 1);

int resource_is_food(int resource);

class building;

bool resource_required_by_workshop(building* b, int resource);

#endif // GAME_RESOURCE_H
