#include "city_overlay_entertainment.h"

#include "game/state.h"
#include "figure/figure.h"
#include "city_overlay.h"

static int show_building_entertainment(const building* b) {
    return b->type == BUILDING_JUGGLER_SCHOOL || b->type == BUILDING_BOOTH || b->type == BUILDING_CONSERVATORY
           || b->type == BUILDING_BANDSTAND || b->type == BUILDING_DANCE_SCHOOL || b->type == BUILDING_PAVILLION
           || b->type == BUILDING_CHARIOT_MAKER || b->type == BUILDING_SENET_HOUSE;
}

static int show_building_hippodrome(const building* b) {
    return b->type == BUILDING_CHARIOT_MAKER || b->type == BUILDING_SENET_HOUSE;
}

static int show_figure_entertainment(const figure* f) {
    return f->type == FIGURE_JUGGLER || f->type == FIGURE_MUSICIAN || f->type == FIGURE_DANCER || f->type == FIGURE_CHARIOTEER;
}

static int show_figure_hippodrome(const figure* f) {
    return f->type == FIGURE_CHARIOTEER;
}

static int get_column_height_entertainment(const building* b) {
    return b->house_size && b->data.house.entertainment ? b->data.house.entertainment / 10 : NO_COLUMN;
}

static int get_column_height_hippodrome(const building* b) {
    return b->house_size && b->data.house.hippodrome ? b->data.house.hippodrome / 10 : NO_COLUMN;
}

static int get_tooltip_entertainment(tooltip_context* c, const building* b) {
    if (b->data.house.entertainment <= 0)
        return 64;
    else if (b->data.house.entertainment < 10)
        return 65;
    else if (b->data.house.entertainment < 20)
        return 66;
    else if (b->data.house.entertainment < 30)
        return 67;
    else if (b->data.house.entertainment < 40)
        return 68;
    else if (b->data.house.entertainment < 50)
        return 69;
    else if (b->data.house.entertainment < 60)
        return 70;
    else if (b->data.house.entertainment < 70)
        return 71;
    else if (b->data.house.entertainment < 80)
        return 72;
    else if (b->data.house.entertainment < 90)
        return 73;
    else {
        return 74;
    }
}

static int get_tooltip_hippodrome(tooltip_context* c, const building* b) {
    if (b->data.house.hippodrome <= 0)
        return 87;
    else if (b->data.house.hippodrome >= 80)
        return 88;
    else if (b->data.house.hippodrome >= 20)
        return 89;
    else {
        return 90;
    }
}

city_overlay* city_overlay_for_entertainment() {
    static city_overlay overlay = {OVERLAY_ENTERTAINMENT,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_entertainment,
                                   show_figure_entertainment,
                                   get_column_height_entertainment,
                                   0,
                                   get_tooltip_entertainment,
                                   0,
                                   0};
    return &overlay;
}

city_overlay* city_overlay_for_hippodrome() {
    static city_overlay overlay = {OVERLAY_HIPPODROME,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_hippodrome,
                                   show_figure_hippodrome,
                                   get_column_height_hippodrome,
                                   0,
                                   get_tooltip_hippodrome,
                                   0,
                                   0};
    return &overlay;
}
