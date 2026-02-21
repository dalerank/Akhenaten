#include "building_house.h"
#include "building/building.h"
#include "city/city.h"
#include "game/resource.h"
#include "graphics/elements/lang_text.h"
#include "io/gamefiles/lang.h"
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

    return archive_helper::get(house->runtime_data(), property, true);
}
ANK_FUNCTION_2(__house_get_property)

void __house_prepare_evolve_info(int bid) {
    building_house* house = house_from_bid(bid);
    if (house) {
        house->determine_worst_desirability_building();
        house->determine_evolve_text();
    }
}
ANK_FUNCTION_1(__house_prepare_evolve_info)

xstring __house_get_evolve_reason(int bid) {
    building_house* house = house_from_bid(bid);
    if (!house) return "";
    auto& housed = house->runtime_data();
    if (housed.evolve_text.empty() && housed.worst_desirability_building_id > 0) {
        building* worst = building_get(housed.worst_desirability_building_id);
        bstring512 text;
        text.printf("%s @Y%s&) %s",
            lang_text_from_key("#house_nearby_building"),
            lang_get_string(41, worst ? worst->type : 0),
            lang_text_from_key("#having_detrimental_effect"));
        return text.c_str();
    }
    return housed.evolve_text;
}
ANK_FUNCTION_1(__house_get_evolve_reason)

int __house_get_happiness_text_id(int bid) {
    building_house* house = house_from_bid(bid);
    if (!house) return 32;
    int happiness = house->runtime_data().house_happiness;
    if (happiness >= 50) return 26;
    if (happiness >= 40) return 27;
    if (happiness >= 30) return 28;
    if (happiness >= 20) return 29;
    if (happiness >= 10) return 30;
    if (happiness >= 1) return 31;
    return 32;
}
ANK_FUNCTION_1(__house_get_happiness_text_id)

xstring __house_get_additional_info(int bid) {
    building_house* house = house_from_bid(bid);
    if (!house || house->model().food_types) return "";
    return lang_get_string(127, 33);
}
ANK_FUNCTION_1(__house_get_additional_info)

bool __house_is_vacant_lot(int bid) {
    building_house* house = house_from_bid(bid);
    return house && house->is_vacant_lot();
}
ANK_FUNCTION_1(__house_is_vacant_lot)

int __house_population(int bid) {
    building_house* house = house_from_bid(bid);
    return house ? house->house_population() : 0;
}
ANK_FUNCTION_1(__house_population)

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
    if (!house || index < 0 || index >= 8) return 0;
    return house->runtime_data().inventory[index];
}
ANK_FUNCTION_2(__house_get_inventory)