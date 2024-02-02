#include "building_hunting_lodge.h"

#include "building/model.h"
#include "core/direction.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"

void building_hunting_lodge::window_info_background(object_info &c) {
    painter ctx = game.painter();
    int group_id = 154;
    c.help_id = 90;
    window_building_play_sound(&c, snd::get_building_info_sound("hunting_lodge"));

    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_GAMEMEAT), c.offset.x + 32, c.offset.y + 56);
    int width = lang_text_draw(group_id, 13, c.offset.x + 60, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    if (!b->stored_amount(RESOURCE_GAMEMEAT)) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(), c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (!c.has_road_access)
        window_building_draw_description_at(c, 86, 69, 25);
    else if (city_resource_is_mothballed(RESOURCE_GAMEMEAT))
        window_building_draw_description_at(c, 86, group_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 86, group_id, 5);
    else if (b->stored_amount() <= 0)
        window_building_draw_description_at(c, 86, group_id, 11);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 86, group_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 86, group_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 86, group_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 86, group_id, 9);
    else
        window_building_draw_description_at(c, 86, group_id, 10);

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_hunting_lodge::on_create() {
    base.output_resource_first_id = RESOURCE_GAMEMEAT;
}


int building_hunting_lodge::spawn_timer() {
    int pct_workers = worker_percentage();
    if (pct_workers >= 100) {
        return 1;
    } else if (pct_workers >= 75) {
        return 5;
    } else if (pct_workers >= 50) {
        return 10;
    } else if (pct_workers >= 25) {
        return 15;
    } else if (pct_workers >= 1) {
        return 30;
    } else {
        return -1;
    }
}


bool building_hunting_lodge::can_spawn_ostrich_hunter() { // no cache because fuck the system (also I can't find the memory offset for this)
    if (has_figure_of_type(BUILDING_SLOT_HUNTER, FIGURE_OSTRICH_HUNTER)) {
        return false;
    }

    return (base.stored_full_amount < 500);
}

void building_hunting_lodge::spawn_figure() {
    check_labor_problem();

    if (!base.has_road_access) {
        return;
    }

    if (base.num_workers < model_get_building(BUILDING_HUNTING_LODGE)->laborers) {
        common_spawn_labor_seeker(100);
    }

    int spawn_delay = spawn_timer();
    if (spawn_delay == -1) { // no workers
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay < spawn_delay) {
        return;
    }

    if (can_spawn_ostrich_hunter()) {
        base.figure_spawn_delay = 10;
        figure* f = base.create_figure_generic(FIGURE_OSTRICH_HUNTER, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
        base.set_figure(BUILDING_SLOT_HUNTER, f);
    }

    if (base.common_spawn_goods_output_cartpusher()) {
        base.figure_spawn_delay = 10;
    }
}