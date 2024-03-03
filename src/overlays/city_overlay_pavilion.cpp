#include "city_overlay_pavilion.h"

#include "game/state.h"
#include "grid/property.h"
#include "city_overlay.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "figuretype/figure_musician.h"
#include "figuretype/figure_dancer.h"

static int get_column_height_senet(const building* b) {
    return (b->house_size && b->data.house.senet_player)
                ? b->data.house.senet_player / 10 
                : NO_COLUMN;
}

static int get_tooltip_senet(tooltip_context* c, const building* b) {
    if (b->data.house.senet_player <= 0) {
        return 83;
    } else if (b->data.house.senet_player >= 80) {
        return 84;
    } else if (b->data.house.senet_player >= 20) {
        return 85;
    } else {
        return 86;
    }
}

struct city_overlay_pavilion : public city_overlay {
    city_overlay_pavilion() {
        type = OVERLAY_PAVILION;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_senet;
        get_tooltip_for_building = get_tooltip_senet;
    }

    bool show_figure(const figure* f) const override {
        figure_musician *musician = ((figure*)f)->dcast_musician();
        if (musician) {
            return musician->current_destination()->type == BUILDING_PAVILLION;
        }

        figure_dancer *dancer = ((figure*)f)->dcast_dancer();
        if (dancer) {
            return true;
        }

        return false;
    }

    void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point, ctx);
        }
    }

    bool show_building(const building *b) const override {
        return (b->type == BUILDING_CONSERVATORY || b->type == BUILDING_DANCE_SCHOOL || b->type == BUILDING_PAVILLION);
    }
};

city_overlay_pavilion g_city_overlay_pavilion;

city_overlay* city_overlay_for_pavilion() {
    return &g_city_overlay_pavilion;
}