#include "building/building_house.h"

#include "building/model.h"
#include "window/building/common.h"
#include "city/city.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "grid/road_access.h"
#include "window/building/figures.h"
#include "window/window_building_info.h"
#include "window/window_figure_info.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

struct info_window_house : public building_info_window_t<info_window_house> {
    virtual void archive_load(archive arch) override {
        building_info_window::archive_load(arch);
    }

    virtual void init(object_info& c) override;
    virtual bool check(object_info &c) override {
        building_house *h = c.building_get()->dcast_house();
        if (!h) {
            return false;
        }

        return !h->is_vacant_lot();
    }
};

struct info_window_vacant_lot : building_info_window_t<info_window_vacant_lot> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building_house *h = c.building_get()->dcast_house();
        if (!h) {
            return false;
        }

        return h->is_vacant_lot();
    }
};

info_window_house house_infow;
info_window_vacant_lot vacant_lot_infow;

void info_window_vacant_lot::init(object_info &c) {
    building_info_window::init(c);

    auto house = c.building_get()->dcast_house();
    if (!house) {
        return;
    }

    tile2i road_tile = map_closest_road_within_radius(house->tile(), 1, 2);
    int text_id = road_tile.valid() ? 1 : 2;

    ui["describe"] = ui::str(128, text_id);
}

void info_window_house::init(object_info &c) {
    building_info_window::init(c);

    auto house = c.building_get()->dcast_house();

    if (!house || !house->house_population()) {
        return;
    }

    house->determine_worst_desirability_building();
    house->determine_evolve_text();

    auto &housed = house->runtime_data();
    if (housed.evolve_text.empty() && housed.worst_desirability_building_id > 0) { // is about to devolve
        bstring512 text;
        text.printf("%s @Y%s&) %s",
            lang_text_from_key("#house_nearby_building"),
            ui::str(41, ::building_get(housed.worst_desirability_building_id)->type),
            lang_text_from_key("#having_detrimental_effect"));
        ui["evolve_reason"] = text;
    } else { // needs something to evolve 
        ui["evolve_reason"] = housed.evolve_text;
    }

    auto food_icon = [] (int i) { bstring32 id_icon; id_icon.printf("food%u_icon", i); return id_icon; };
    auto food_text = [] (int i) { bstring32 id_text; id_text.printf("food%u_text", i); return id_text; };

    int food_index = 0;
    for (int i = 0; i < 4; ++i) {
        e_resource resource = g_city.allowed_foods(i);
        if (resource != RESOURCE_NONE) {
            int stored = housed.foods[i];
            ui[food_icon(food_index)].image(resource);
            ui[food_text(food_index)].text_var(resource ? "%u" : "", stored);
            ++food_index;
        }
    }

    auto good_icon = [] (int i) { bstring32 id_icon; id_icon.printf("good%u_icon", i); return id_icon; };
    auto good_text = [] (int i) { bstring32 id_text; id_text.printf("good%u_text", i); return id_text; };

    // goods inventory
    e_resource house_goods[] = { RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS, RESOURCE_LINEN, RESOURCE_BEER };
    for (int i = 0; i < 4; ++i) {
        e_resource resource = house_goods[i];
        int stored = housed.inventory[INVENTORY_GOOD1 + i];
        ui[good_icon(i)].image(resource);
        ui[good_text(i)].text_var("%u", stored);
    }

    bstring256 people_text, adv_people_text;
    const int house_population_room = house->population_room();
    people_text.printf("%u %s", house->house_population(), ui::str(127, 20));
    if (house_population_room < 0) {
        adv_people_text.printf("%u %s", -house_population_room, ui::str(127, 21));
    } else if (house->population_room() > 0) {
        adv_people_text.printf("%s %u", ui::str(127, 22), house_population_room);
    } else {
        adv_people_text = "no rooms";
    }
    ui["people_text"].text_var("%s ( %s )", people_text.c_str(), adv_people_text.c_str());

    bstring256 tax_info_text;
    if (housed.tax_coverage) {
        int pct = calc_adjust_with_percentage<int>(housed.tax_income_or_storage / 2, g_city.finance.tax_percentage);
        tax_info_text.printf("%s %u %s", ui::str(127, 24), pct, ui::str(127, 25));
    } else {
        tax_info_text = ui::str(127, 23);
    }
    ui["tax_info"] = tax_info_text;

    int happiness = housed.house_happiness;
    int happiness_text_id;
    if (happiness >= 50) { happiness_text_id = 26; } 
    else if (happiness >= 40) { happiness_text_id = 27; } 
    else if (happiness >= 30) { happiness_text_id = 28; } 
    else if (happiness >= 20) { happiness_text_id = 29; } 
    else if (happiness >= 10) { happiness_text_id = 30; } 
    else if (happiness >= 1) { happiness_text_id = 31; } 
    else { happiness_text_id = 32; }

    ui["happiness_info"] = ui::str(127, happiness_text_id);

    if (!house->model().food_types) { // no foods
        ui["additional_info"] = ui::str(127, 33);
    }
}