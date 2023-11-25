#include "building_education.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

static void building_education_draw_info(object_info& c, const char* type, e_figure_type ftype) {
    auto &meta = building::get_info(type);
    c.help_id = meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));
    outer_panel_draw(c.offset.x, c.offset.y, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building *b = building_get(c.building_id);

    if (ftype != FIGURE_NONE && b->has_figure_of_type(BUILDING_SLOT_SERVICE, ftype)) {
        window_building_draw_description(c, meta.text_id, e_text_figure_on_patrol);
    } else if (!c.has_road_access) {
        window_building_draw_description(c, e_text_building, e_text_building_no_roads);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, meta.text_id, e_text_no_workers);
    } else {
        window_building_draw_description(c, meta.text_id, e_text_works_fine);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_scribal_school_draw_info(object_info& c) {
    building_education_draw_info(c, "school_scribe", FIGURE_TEACHER);
}
void building_academy_draw_info(object_info& c) {
    building_education_draw_info(c, "academy", FIGURE_SCRIBER);
}
void building_library_draw_info(object_info& c) {
    building_education_draw_info(c, "library", FIGURE_LIBRARIAN);
}

void building::spawn_figure_school() {
    check_labor_problem();
    if (has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_TEACHER)) {
        return;
    }

    tile2i road;
    if (map_get_road_access_tile(tile, size, road)) {
        common_spawn_labor_seeker(50);
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            return;
        }

        figure_spawn_delay++;
        if (figure_spawn_delay > spawn_delay) {
            figure_spawn_delay = 0;

            figure* f = figure_create(FIGURE_TEACHER, road, DIR_0_TOP_RIGHT);
            f->action_state = FIGURE_ACTION_125_ROAMING;
            f->set_home(id);
            set_figure(BUILDING_SLOT_SERVICE, f->id);
            f->init_roaming_from_building(0);
        }
    }
}