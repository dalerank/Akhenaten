#include "building_academy.h"

#include "building/building_education.h"
#include "building/count.h"
#include "city/labor.h"

buildings::model_t<building_academy> academy_m;

void building_academy::window_info_background(object_info &c) {
    building_education_draw_info(c, FIGURE_SCRIBER, RESOURCE_NONE, vec2i{0, 0}, vec2i{0, 0});
}
