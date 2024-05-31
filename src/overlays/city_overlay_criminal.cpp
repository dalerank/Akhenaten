#include "city_overlay_criminal.h"

#include "building/model.h"
#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "game/state.h"


city_overlay_crime g_city_overlay_crime;

city_overlay* city_overlay_for_crime() {
    return &g_city_overlay_crime;
}

city_overlay_crime::city_overlay_crime() {
    type = OVERLAY_CRIME;
    column_type = COLUMN_TYPE_RISK;
}

int city_overlay_crime::get_column_height(const building* b) const {
    if (b->house_size && b->house_population > 0) {
        int crime = b->house_criminal_active;
        return crime / 10;
    }
    return NO_COLUMN;
}

int city_overlay_crime::get_tooltip_for_building(tooltip_context* c, const building* b) const {
    if (b->house_population <= 0) {
        return 63;
    }

    if (b->house_criminal_active >= 80)
        return 63;
    else if (b->house_criminal_active >= 60)
        return 62;
    else if (b->house_criminal_active >= 40)
        return 61;
    else if (b->house_criminal_active >= 30)
        return 60;
    else if (b->house_criminal_active >= 20)
        return 59;
    else {
        return 58;
    }
}

bool city_overlay_crime::show_figure(const figure *f) const {
    return f->type == FIGURE_CONSTABLE || f->type == FIGURE_PROTESTER || f->type == FIGURE_CRIMINAL
        || f->type == FIGURE_TOMB_ROBER;
}

void city_overlay_crime::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    if (!map_property_is_draw_tile(point)) {
        return;
    }

    if (map_building_at(point)) {
        city_overlay::draw_building_top(pixel, point, ctx);
    }
}

bool city_overlay_crime::show_building(const building *b) const {
    return b->type == BUILDING_POLICE_STATION || b->type == BUILDING_FESTIVAL_SQUARE;
}
