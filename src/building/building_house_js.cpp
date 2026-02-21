#include "building_house.h"
#include "building/building.h"
#include "building/building_house_model.h"
#include "city/city.h"
#include "game/resource.h"
#include "js/js_game.h"
#include "core/bstring.h"

static building_house *house_from_bid(int bid) {
    building *b = building_get(bid);
    return b ? b->dcast_house() : nullptr;
}

std::optional<bvariant> __house_get_property(int bid, pcstr property) {
    building_house* house = house_from_bid(bid);
    if (!house) {
        return {};
    }

    auto result = archive_helper::get(house->runtime_data(), property, true);
    if (result.has_value()) {
        return result;
    }

    return archive_helper::get(house->base, property, true);
}
ANK_FUNCTION_2(__house_get_property)

int __house_level(int bid) {
    building_house* house = house_from_bid(bid);
    return house ? house->house_level() : 0;
}
ANK_FUNCTION_1(__house_level)

void __house_set_evolve_text(int bid, pcstr text) {
    building_house* house = house_from_bid(bid);
    if (house)
        house->runtime_data().evolve_text = text ? text : "";
}
ANK_FUNCTION_2(__house_set_evolve_text)

std::optional<bvariant> __house_model_property(int level, pcstr property) {
    return archive_helper::get(building_house::get_model(level), xstring(property), true);
}
ANK_FUNCTION_2(__house_model_property)

void __house_prepare_evolve_info(int bid) {
    building_house* house = house_from_bid(bid);
    if (house)
        house->determine_worst_desirability_building();
}
ANK_FUNCTION_1(__house_prepare_evolve_info)

bool __house_is_vacant_lot(int bid) {
    building_house* house = house_from_bid(bid);
    return house && house->is_vacant_lot();
}
ANK_FUNCTION_1(__house_is_vacant_lot)

int __house_population_room(int bid) {
    building_house* house = house_from_bid(bid);
    return house ? house->population_room() : 0;
}
ANK_FUNCTION_1(__house_population_room)

int __house_get_food(int bid, int index) {
    building_house* house = house_from_bid(bid);
    if (!house || index < 0 || index >= 8) return 0;
    return house->runtime_data().foods[index];
}
ANK_FUNCTION_2(__house_get_food)

int __house_get_inventory(int bid, int index) {
    building_house* house = house_from_bid(bid);
    if (!house || index < 0 || index >= 4) return 0;
    return house->runtime_data().inventory[index + INVENTORY_MIN_GOOD];
}
ANK_FUNCTION_2(__house_get_inventory)