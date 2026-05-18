#include "city_overlay_enemies.h"

#include "figure/figure.h"

city_overlay_enemies g_city_overlay_enemies;

bool city_overlay_enemies::show_figure(const figure *f) const {
    return ((figure *)f)->dcast()->get_overlay() == OVERLAY_ENEMIES;
}

int city_overlay_enemies::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

bool city_overlay_enemies::show_building(const building *b) const {
    return false;
}
