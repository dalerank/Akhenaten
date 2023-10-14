#include "city_overlay_religion.h"

#include "city/constants.h"
#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "overlays/city_overlay.h"
#include "city/gods.h"
#include "figure/figure.h"

#include <algorithm>
#include <array>

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

    void draw_custom_top(vec2i pixel, map_point point) const override {
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
city_overlay* city_overlay_for_religion() {
    return &g_city_overlay_religion;
}

struct city_overlay_religion_god : public city_overlay {
    city_overlay_religion_god() {
        type = OVERLAY_RELIGION_BAST;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_religion;
        get_tooltip_for_building = get_tooltip_religion;
    }

    bool show_figure(const figure* f) const override {
        return walkers.size() > 0
                ? std::find(walkers.begin(), walkers.end(), f->type) != walkers.end()
                : f->type == FIGURE_PRIEST;
    }

    void draw_custom_top(vec2i pixel, map_point point) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point);
        }
    }

    bool show_building(const building* b) const override {
        return std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
    }
};

struct city_overlay_religion_osiris : public city_overlay_religion_god {
    city_overlay_religion_osiris() {
        type = OVERLAY_RELIGION_OSIRIS;
    }
};

struct city_overlay_religion_ra : public city_overlay_religion_god {
    city_overlay_religion_ra() {
        type = OVERLAY_RELIGION_RA;
        buildings = {BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA};
    }
};

struct city_overlay_religion_ptah : public city_overlay_religion_god {
    city_overlay_religion_ptah() {
        type = OVERLAY_RELIGION_PTAH;
        buildings = {BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_SHRINE_PTAH};
    }
};

struct city_overlay_religion_seth : public city_overlay_religion_god {
    city_overlay_religion_seth() {
        type = OVERLAY_RELIGION_SETH;
        buildings = {BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_SHRINE_SETH};
    }
};

struct city_overlay_religion_bast : public city_overlay_religion_god {
    city_overlay_religion_bast() {
        type = OVERLAY_RELIGION_BAST;
        buildings = {BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST};
    }
};

city_overlay_religion_osiris g_city_overlay_religion_osiris;
city_overlay_religion_ra g_city_overlay_religion_ra;
city_overlay_religion_ptah g_city_overlay_religion_ptah;
city_overlay_religion_seth g_city_overlay_religion_seth;
city_overlay_religion_bast g_city_overlay_religion_bast;

city_overlay* city_overlay_for_religion_osiris() {
    return &g_city_overlay_religion_osiris;
}

city_overlay* city_overlay_for_religion_ra() {
    return &g_city_overlay_religion_ra;
}

city_overlay* city_overlay_for_religion_ptah() {
    return &g_city_overlay_religion_ptah;
}

city_overlay* city_overlay_for_religion_seth() {
    return &g_city_overlay_religion_seth;
}

city_overlay* city_overlay_for_religion_bast() {
    return &g_city_overlay_religion_bast;
}