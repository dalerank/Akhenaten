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
#include "game/game.h"

#include "js/js_game.h"

struct building_scribal_school_t {
    vec2i papyrus;
    vec2i icon_res;
    vec2i text_res;
} building_scribal_school;

ANK_REGISTER_CONFIG_ITERATOR(config_load_scribal_school);
void config_load_scribal_school(archive arch) {
    arch.load_global_section("building_scribal_school", [] (archive arch) {
        building_scribal_school.papyrus.x = arch.read_integer("papyrus_x");
        building_scribal_school.papyrus.y = arch.read_integer("papyrus_y");

        arch.read_object_section("info", [] (archive arch) {
            building_scribal_school.icon_res.x = arch.read_integer("icon_res_x");
            building_scribal_school.icon_res.y = arch.read_integer("icon_res_y");
            building_scribal_school.text_res.x = arch.read_integer("text_res_x");
            building_scribal_school.text_res.y = arch.read_integer("text_res_y");
        });
    });
}

static void building_education_draw_info(object_info& c, const char* type, e_figure_type ftype, e_resource resource) {
    auto &meta = building::get_info(type);

    c.help_id = meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));
    outer_panel_draw(c.offset.x, c.offset.y, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building *b = building_get(c.building_id);
    painter ctx = game.painter();

    if (resource != RESOURCE_NONE) {
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset + building_scribal_school.icon_res);
        int width = lang_text_draw(23, 77, c.offset + building_scribal_school.text_res, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_amount(8, 10, b->stored_amount(), c.offset + building_scribal_school.text_res + vec2i{width, 0}, FONT_NORMAL_BLACK_ON_LIGHT);
    }

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
    building_education_draw_info(c, "school_scribe", FIGURE_TEACHER, RESOURCE_PAPYRUS);
}
void building_academy_draw_info(object_info& c) {
    building_education_draw_info(c, "academy", FIGURE_SCRIBER, RESOURCE_NONE);
}
void building_library_draw_info(object_info& c) {
    building_education_draw_info(c, "library", FIGURE_LIBRARIAN, RESOURCE_NONE);
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

void building_education_draw_raw_material_storage(painter &ctx, const building *b, vec2i pos, color color_mask) {
    int amount = 0;
    int amount2 = 0;
    switch (b->type) {
    case BUILDING_SCRIBAL_SCHOOL:
        amount = ceil((float)b->stored_amount() / 100.0) - 1;
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(IMG_RESOURCE_PAPYRUS) + amount, pos + building_scribal_school.papyrus, color_mask);
        }
        break;
    }
}