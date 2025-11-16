#include "city_overlay_health.h"

#include "grid/property.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "building/building_house.h"
#include "city/city_buildings.h"
#include "dev/debug.h"

city_overlay_health g_city_overlay_health;

int city_overlay_health::get_column_height(const building *b) const {
    if (b->disease_days > 0) {
        return 10;
    }

    auto house = ((building *)b)->dcast_house();
    if (!house || house->house_population() <= 0) {
        return COLUMN_TYPE_NONE;
    }

    const auto& housed = house->runtime_data();
    return house->base.common_health / 10;
}

e_column_color city_overlay_health::get_column_color(const building *b) const {
    if (b->disease_days > 0) {
        return COLUMN_COLOR_RED;
    }

    auto house = ((building *)b)->dcast_house();
    if (!house || house->house_population() <= 0) {
        return COLUMN_COLOR_NONE;
    }

    return COLUMN_COLOR_NONE;
}

void city_overlay_health::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    city_overlay::draw_custom_top(pixel, tile, ctx);

    if (debug_render_mode() == e_debug_render_overlay_add) {
        building *b = building_at(tile);
        if (b->id) {
            auto house = b->dcast_house();
            bstring32 text;
            if (house) {
                text.printf("%d/%d", b->common_health, house->runtime_data().health);
            } else {
                text.printf("%d", b->common_health);
            }
            debug_text_a(ctx, text, pixel.x + 15, pixel.y + 15, 0, text, COLOR_LIGHT_BLUE);
        }
    }
}

xstring city_overlay_health::get_tooltip_for_building(tooltip_context *c, const building *b) {
    if (b->disease_days > 0) {
        return ui::str(66, 131);
    }

    if (b->common_health < 25) {
        return ui::str(66, 130);
    } else if (b->common_health < 50) {
        return ui::str(66, 129);
    } else if (b->common_health < 75) {
        return ui::str(66, 128);
    } else {
        return ui::str(66, 127);
    }
}
