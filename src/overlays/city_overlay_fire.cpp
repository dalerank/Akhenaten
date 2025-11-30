#include "city_overlay_fire.h"

#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "building/building_house.h"

city_overlay_fire g_city_overlay_fire;

int city_overlay_fire::get_column_height(const building *b) const {
    if (!!game_features::gameui_overlay_show_gray_buildings) {
        return COLUMN_TYPE_NONE;
    }

    if (b->prev_part_building_id || b->fire_proof) {
        return COLUMN_TYPE_NONE;
    }

    auto house = ((building*)b)->dcast_house();
    if ((house && house->house_population() <= 0) || b->type == BUILDING_GARDENS
        || b->type == BUILDING_BANDSTAND || b->type == BUILDING_BOOTH) {
        return COLUMN_TYPE_NONE;
    }

    return b->fire_risk / 100;
}

bool city_overlay_fire::show_building(const building *b) const {
    const bool need_show = std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
    if (need_show) {
        return true;
    }

    int percentage = calc_percentage<int>(b->fire_risk, 1000);
    return (percentage > 10);
}

color city_overlay_fire::color_mask_building(const building *b) const {
    const bool need_show = std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
    if (need_show) {
        return COLOR_MASK_NONE;
    }

    int percentage = calc_percentage<int>(b->fire_risk, 1000);
    return color_from_green_to_red(percentage);
}

xstring city_overlay_fire::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto main = const_cast<building*>(b)->main();
    if (main->fire_risk <= 0)
        return ui::str(66, 46);

    if (main->fire_risk <= 200)
        return ui::str(66, 47);

    if (main->fire_risk <= 400)
        return ui::str(66, 48);

    if (main->fire_risk <= 600)
        return ui::str(66, 49);

    if (main->fire_risk <= 800)
        return ui::str(66, 50);

    return ui::str(66, 51);
}
