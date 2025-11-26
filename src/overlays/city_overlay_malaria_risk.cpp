#include "city_overlay_malaria_risk.h"

#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"
#include "building/building_house.h"
#include "dev/debug.h"
#include "city/city_buildings.h"
#include "grid/malaria_risk.h"

city_overlay_malaria_risk g_city_overlay_malaria_risk;

int city_overlay_malaria_risk::get_column_height(const building *b) const {
    if (b->prev_part_building_id) {
        return COLUMN_TYPE_NONE;
    }

    // Показываем колонку только если есть риск малярии
    if (b->malaria_risk <= 0) {
        return COLUMN_TYPE_NONE;
    }

    // Высота колонки пропорциональна риску (0-100 -> 0-10)
    return b->malaria_risk / 10;
}

void city_overlay_malaria_risk::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    city_overlay::draw_custom_top(pixel, tile, ctx);

    // В дебажном режиме показываем числовые значения
    if (debug_render_mode() == e_debug_render_overlay_add) {
        building *b = building_at(tile);
        if (b && b->id) {
            bstring32 text;
            // Показываем риск из grid и риск здания
            int grid_risk = g_malaria_risk.get(tile);
            if (grid_risk > 0 || b->malaria_risk > 0) {
                if (grid_risk > 0 && b->malaria_risk > 0) {
                    text.printf("g:%d b:%d", grid_risk, b->malaria_risk);
                } else if (grid_risk > 0) {
                    text.printf("g:%d", grid_risk);
                } else {
                    text.printf("b:%d", b->malaria_risk);
                }
                // Цвет зависит от уровня риска
                color risk_color = (b->malaria_risk < 30) ? COLOR_LIGHT_GREEN : 
                                   (b->malaria_risk < 60) ? COLOR_YELLOW : COLOR_LIGHT_RED;
                debug_text_a(ctx, text, pixel.x + 15, pixel.y + 15, 0, text, risk_color);
            }
        }
    }
}

xstring city_overlay_malaria_risk::get_tooltip_for_building(tooltip_context *c, const building *b) {
    if (b->malaria_risk <= 0) {
        return ui::str(66, 137); // "This building is a negligible malaria risk."
    } else if (b->malaria_risk <= 20) {
        return ui::str(66, 138); // "This building has some risk of malaria."
    } else if (b->malaria_risk <= 40) {
        return ui::str(66, 139); // "This building has a risk of malaria"
    } else if (b->malaria_risk <= 60) {
        return ui::str(66, 140); // "This building will have malaria soon."
    } else {
        return ui::str(66, 147); // "Risk of malaria"
    }
}

