#include "city_overlay_health.h"

#include "building/type.h"
#include "city_overlay.h"

static int show_building_mortuary(const building* b) {
    return b->type == BUILDING_MORTUARY;
}

static int show_figure_mortuary(const figure* f) {
    return f->type == FIGURE_MORTUARY_WORKER;
}

static int get_column_height_mortuary(const building* b) {
    return b->house_size && b->data.house.mortuary ? b->data.house.mortuary / 10 : NO_COLUMN;
}

static int get_tooltip_mortuary(tooltip_context* c, const building* b) {
    if (b->data.house.mortuary <= 0)
        return 39;
    else if (b->data.house.mortuary >= 80)
        return 40;
    else if (b->data.house.mortuary >= 20)
        return 41;
    else {
        return 42;
    }
}

const city_overlay* city_overlay_for_mortuary(void) {
    static city_overlay overlay = {OVERLAY_MORTUARY,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_mortuary,
                                   show_figure_mortuary,
                                   get_column_height_mortuary,
                                   0,
                                   get_tooltip_mortuary,
                                   0,
                                   0};
    return &overlay;
}
