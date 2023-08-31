#include "city_overlay_entertainment.h"

#include "building/type.h"
#include "game/state.h"
#include "city_overlay.h"

static int show_building_entertainment(const building* b) {
    return b->type == BUILDING_JUGGLER_SCHOOL || b->type == BUILDING_BOOTH || b->type == BUILDING_CONSERVATORY
           || b->type == BUILDING_BANDSTAND || b->type == BUILDING_DANCE_SCHOOL || b->type == BUILDING_PAVILLION
           || b->type == BUILDING_CHARIOT_MAKER || b->type == BUILDING_SENET_HOUSE;
}

static int show_building_bandstand(const building* b) {
    return b->type == BUILDING_CONSERVATORY || b->type == BUILDING_BANDSTAND;
}

static int show_building_colosseum(const building* b) {
    return b->type == BUILDING_CONSERVATORY || b->type == BUILDING_DANCE_SCHOOL || b->type == BUILDING_PAVILLION;
}

static int show_building_hippodrome(const building* b) {
    return b->type == BUILDING_CHARIOT_MAKER || b->type == BUILDING_SENET_HOUSE;
}

static building* get_entertainment_building(const figure* f) {
    if (f->action_state == FIGURE_ACTION_94_ENTERTAINER_ROAMING
        || f->action_state == FIGURE_ACTION_95_ENTERTAINER_RETURNING) {
        return ((figure*)f)->home();
    } else
        return ((figure*)f)->destination();
}

static int show_figure_entertainment(const figure* f) {
    return f->type == FIGURE_JUGGLER || f->type == FIGURE_MUSICIAN || f->type == FIGURE_LION_TAMER || f->type == FIGURE_CHARIOTEER;
}

static int show_figure_bandstand(const figure* f) {
    if (f->type == FIGURE_MUSICIAN) {
        return get_entertainment_building(f)->type == BUILDING_BANDSTAND;
    }

    return 0;
}

static int show_figure_colosseum(const figure* f) {
    if (f->type == FIGURE_MUSICIAN)
        return get_entertainment_building(f)->type == BUILDING_PAVILLION;
    else if (f->type == FIGURE_LION_TAMER)
        return 1;

    return 0;
}

static int show_figure_hippodrome(const figure* f) {
    return f->type == FIGURE_CHARIOTEER;
}

static int get_column_height_entertainment(const building* b) {
    return b->house_size && b->data.house.entertainment ? b->data.house.entertainment / 10 : NO_COLUMN;
}

static int get_column_height_bandstand(const building* b) {
    if (b->house_size) {
        if (b->data.house.bandstand_musician) {
            return b->data.house.bandstand_musician / 10;
        }
    }
    
    return NO_COLUMN;
}

static int get_column_height_colosseum(const building* b) {
    return b->house_size && b->data.house.colosseum_gladiator ? b->data.house.colosseum_gladiator / 10 : NO_COLUMN;
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

static int get_tooltip_bandstand(tooltip_context* c, const building* b) {
    if (b->data.house.bandstand_musician <= 0)
        return 79;
    else if (b->data.house.bandstand_musician >= 80)
        return 80;
    else if (b->data.house.bandstand_musician >= 20)
        return 81;
    else {
        return 82;
    }
}

static int get_tooltip_colosseum(tooltip_context* c, const building* b) {
    if (b->data.house.colosseum_gladiator <= 0)
        return 83;
    else if (b->data.house.colosseum_gladiator >= 80)
        return 84;
    else if (b->data.house.colosseum_gladiator >= 20)
        return 85;
    else {
        return 86;
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

const city_overlay* city_overlay_for_entertainment(void) {
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

const city_overlay* city_overlay_for_bandstand(void) {
    static city_overlay overlay = {OVERLAY_BANDSTAND,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_bandstand,
                                   show_figure_bandstand,
                                   get_column_height_bandstand,
                                   0,
                                   get_tooltip_bandstand,
                                   0,
                                   0};
    return &overlay;
}

const city_overlay* city_overlay_for_colosseum(void) {
    static city_overlay overlay = {OVERLAY_COLOSSEUM,
                                   COLUMN_TYPE_WATER_ACCESS,
                                   show_building_colosseum,
                                   show_figure_colosseum,
                                   get_column_height_colosseum,
                                   0,
                                   get_tooltip_colosseum,
                                   0,
                                   0};
    return &overlay;
}

const city_overlay* city_overlay_for_hippodrome(void) {
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
