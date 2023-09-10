#include "city_overlay_health.h"

#include "city_overlay.h"
#include "grid/property.h"
#include "grid/building.h"

static int get_column_height_health(const building* b) {
    if (!b->house_size) {
        return NO_COLUMN;
    }
    
    if (b->disease_days > 0) {
        return 10;
    }

    return (100 - b->common_health) / 10;
}

static int get_tooltip_health(tooltip_context* c, const building* b) {
    if (b->disease_days > 0) {
        return 131;
    }

    if (b->common_health < 25) {
        return 130;
    } else if (b->common_health < 50) {
        return 129;
    } else if (b->common_health < 75) {
        return 128;
    } else {
        return 127;
    }
}

struct city_overlay_health : public city_overlay {
    city_overlay_health() {
        type = OVERLAY_HEALTH;
        column_type = COLUMN_TYPE_RISK;

        get_column_height = get_column_height_health;
        get_tooltip_for_building = get_tooltip_health;
    }

    bool show_figure(const figure* f) const override {
        return (f->type == FIGURE_MORTUARY_WORKER || f->type == FIGURE_APOTHECARY || f->type == FIGURE_PHYSICIAN || f->type == FIGURE_DENTIST);
    }

    void draw_custom_top(vec2i pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        int x = pixel.x;
        int y = pixel.y;
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building *b) const override {
        return (b->type == BUILDING_MORTUARY || b->type == BUILDING_APOTHECARY || b->type == BUILDING_PHYSICIAN || b->type == BUILDING_DENTIST);
    }
};

city_overlay_health g_city_overlay_health;

const city_overlay* city_overlay_for_health(void) {
    return &g_city_overlay_health;
}