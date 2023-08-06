#include "city_overlay_religion.h"

#include "widget/overlays/city_overlay.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "city/constants.h"

#include <algorithm>

static void add_god(tooltip_context* c, int god_id) {
    int index = c->num_extra_values;
    c->extra_value_text_groups[index] = 59;
    c->extra_value_text_ids[index] = 11 + god_id;
    c->num_extra_values++;
}

static int get_column_height_religion(const building* b) {
    return b->house_size && b->data.house.num_gods ? b->data.house.num_gods * 17 / 10 : NO_COLUMN;
}

static int get_tooltip_religion(tooltip_context* c, const building* b) {
    if (b->data.house.num_gods < 5) {
        if (b->data.house.temple_osiris)
            add_god(c, GOD_OSIRIS);

        if (b->data.house.temple_ra)
            add_god(c, GOD_RA);

        if (b->data.house.temple_ptah)
            add_god(c, GOD_PTAH);

        if (b->data.house.temple_seth)
            add_god(c, GOD_SETH);

        if (b->data.house.temple_bast)
            add_god(c, GOD_BAST);
    }

    if (b->data.house.num_gods <= 0) {
        return 12;
    } else if (b->data.house.num_gods == 1) {
        return 13;
    } else if (b->data.house.num_gods == 2) {
        return 14;
    } else if (b->data.house.num_gods == 3) {
        return 15;
    } else if (b->data.house.num_gods == 4) {
        return 16;
    } else if (b->data.house.num_gods == 5) {
        return 17;
    } else {
        return 18; // >5 gods, shouldn't happen...
    }
}

struct city_overlay_religion : public city_overlay {
    city_overlay_religion() {
        type = OVERLAY_RELIGION;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_religion;
        get_tooltip_for_building = get_tooltip_religion;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_PRIEST;
    }

    void draw_custom_top(pixel_coordinate pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building* b) const override {
        return building_is_religion(b->type);
    }
};

city_overlay_religion g_city_overlay_religion;
const city_overlay* city_overlay_for_religion(void) {
    return &g_city_overlay_religion;
}

struct city_overlay_religion_bast : public city_overlay {
    city_overlay_religion_bast() {
        type = OVERLAY_RELIGION_BAST;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_religion;
        get_tooltip_for_building = get_tooltip_religion;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_PRIEST;
    }

    void draw_custom_top(pixel_coordinate pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building* b) const override {
        e_building_type bast_types[] = {BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST};
        return std::find(std::begin(bast_types), std::end(bast_types), b->type) != std::end(bast_types);
    }
};

city_overlay_religion_bast g_city_overlay_religion_bast;
const city_overlay* city_overlay_for_religion_bast(void) {
    return &g_city_overlay_religion_bast;
}