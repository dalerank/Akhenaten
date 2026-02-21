#include "building_house.h"
#include "building/building.h"
#include "city/city.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/elements/lang_text.h"
#include "grid/road_access.h"
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

bool __house_has_road_nearby(int bid) {
    building_house* house = house_from_bid(bid);
    if (!house) return false;
    tile2i road_tile = map_closest_road_within_radius(house->tile(), 1, 2);
    return road_tile.valid();
}
ANK_FUNCTION_1(__house_has_road_nearby)

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

xstring __house_get_people_text(int bid) {
    building_house* house = house_from_bid(bid);
    if (!house) return "";
    bstring256 people_text, adv_people_text;
    int house_population_room = house->population_room();
    people_text.printf("%u %s", house->house_population(), lang_get_string(127, 20));
    if (house_population_room < 0) {
        adv_people_text.printf("%u %s", -house_population_room, lang_get_string(127, 21));
    } else if (house_population_room > 0) {
        adv_people_text.printf("%s %u", lang_get_string(127, 22), house_population_room);
    } else {
        adv_people_text = "no rooms";
    }
    bstring256 result;
    result.printf("%s ( %s )", people_text.c_str(), adv_people_text.c_str());
    return result;
}
ANK_FUNCTION_1(__house_get_people_text)

xstring __house_get_tax_info(int bid) {
    building_house* house = house_from_bid(bid);
    if (!house) return "";
    auto& housed = house->runtime_data();
    bstring256 tax_info_text;
    if (housed.tax_coverage) {
        int pct = calc_adjust_with_percentage<int>(housed.tax_income_or_storage / 2, g_city.finance.tax_percentage);
        tax_info_text.printf("%s %u %s", lang_get_string(127, 24), pct, lang_get_string(127, 25));
    } else {
        tax_info_text = lang_get_string(127, 23);
    }
    return tax_info_text;
}
ANK_FUNCTION_1(__house_get_tax_info)

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
