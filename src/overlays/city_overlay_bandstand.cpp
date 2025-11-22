#include "city_overlay_juggler.h"

#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figuretype/figure_musician.h"
#include "building/building_house.h"
#include "city_overlay_bandstand.h"
#include "js/js_game.h"

city_overlay_bandstand g_city_overlay_bandstand;

xstring city_overlay_bandstand::get_tooltip_for_building(tooltip_context *c, const building *b) {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return {};
    }

    if (current_building_id == b->id) {
        return current_tooltip;
    }

    current_building_id = b->id;
    const tooltips_t *tooltips = nullptr;

    auto &housed = house->runtime_data();
    const int musician_value = std::max<int>(housed.bandstand_musician, housed.pavillion_musician);
    if (musician_value <= 20) tooltips = &get_tooltips("low");
    else if (musician_value <= 40) tooltips = &get_tooltips("usual");
    else if (musician_value <= 80) tooltips = &get_tooltips("medium");
    else tooltips = &get_tooltips("high");
    
    xstring tooltip = "#unknown_tooltip_bandstand";
    if (tooltips && !tooltips->values.empty()) {
        int index = rand() % tooltips->values.size();
        tooltip = tooltips->values[index];
    }

    current_tooltip = lang_xtext_from_key(tooltip);
    return current_tooltip;
}

bool city_overlay_bandstand::show_figure(const figure *f) const {
    figure_musician *musician = smart_cast<figure_musician>((figure *)f);
    return musician
             ? musician->current_destination()->type == BUILDING_BANDSTAND
             : false;
}

int city_overlay_bandstand::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    if (house->house_population()) {
        auto &housed = house->runtime_data();
        const int musician_value = std::max<int>(housed.bandstand_musician, housed.pavillion_musician);
        return musician_value / 10;
    }

    return COLUMN_TYPE_NONE;
}
