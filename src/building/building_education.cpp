#include "building_education.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

static void building_education_draw_info(object_info& c, int help_id, const char* type, int group_id, e_figure_type ftype) {
    c.help_id = help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));
    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(group_id, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building *b = building_get(c.building_id);

    if (ftype != FIGURE_NONE && b->has_figure_of_type(BUILDING_SLOT_SERVICE, ftype)) {
        window_building_draw_description(c, group_id, e_text_figure_on_patrol);
    } else if (!c.has_road_access) {
        window_building_draw_description(c, e_text_building, e_text_building_no_roads);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, group_id, e_text_no_workers);
    } else {
        window_building_draw_description(c, group_id, e_text_works_fine);
    }

    inner_panel_draw(c.x_offset + 16, c.y_offset + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_scribal_school_draw_info(object_info& c) {
    building_education_draw_info(c, 68, "school_scribe", 85, FIGURE_TEACHER);
}
void building_academy_draw_info(object_info& c) {
    building_education_draw_info(c, 69, "academy", 86, FIGURE_SCRIBER);
}
void building_library_draw_info(object_info& c) {
    building_education_draw_info(c, 70, "library", 87, FIGURE_LIBRARIAN);
}
