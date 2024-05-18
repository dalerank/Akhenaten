#include "building_academy.h"

#include "building/building_education.h"
#include "building/count.h"
#include "city/labor.h"
#include "js/js_game.h"

buildings::model_t<building_academy> academy_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_academy);
void config_load_building_academy() {
    academy_m.load();
}

void building_academy::window_info_background(object_info &c) {
    building_education_draw_info(c, "academy", FIGURE_SCRIBER, RESOURCE_NONE, vec2i{0, 0}, vec2i{0, 0});
}

void building_academy::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
}
