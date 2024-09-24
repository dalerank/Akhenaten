#include "building_bricklayers_guild.h"

#include "building/building.h"
#include "building/count.h"
#include "building/monuments.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "city/labor.h"
#include "core/random.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "game/game.h"
#include "dev/debug.h"
#include "js/js_game.h"

#include <iostream>

buildings::model_t<building_bricklayers_guild> bricklayers_guild_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_bricklayers_guild);
void config_load_building_bricklayers_guild() {
    bricklayers_guild_m.load();
}

declare_console_command(addbricks, game_cheat_add_resource<RESOURCE_BRICKS>);

void building_bricklayers_guild::window_info_background(object_info& c) {
    building* b = building_get(c.building_id);
    const auto &meta = b->dcast()->params().meta;
    window_building_play_sound(&c, b->get_sound());

    painter ctx = game.painter();

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_BRICKS), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    int pct_done = calc_percentage<int>(b->data.industry.progress, 400);
    int width = lang_text_draw(meta.text_id, 2, c.offset.x + 32, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(meta.text_id, 3, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_BRICKS), c.offset.x + 32, c.offset.y + 56);
    width = lang_text_draw(meta.text_id, 12, c.offset.x + 60, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    if (b->stored_amount() < 100) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(), c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (!c.has_road_access)
        window_building_draw_description_at(c, 86, 69, 25);
    else if (city_resource_is_mothballed(RESOURCE_BRICKS))
        window_building_draw_description_at(c, 86, meta.text_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 86, meta.text_id, 5);
    else if (!b->guild_has_resources())
        window_building_draw_description_at(c, 86, meta.text_id, 11);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 86, meta.text_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 86, meta.text_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 86, meta.text_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 86, meta.text_id, 9);
    else
        window_building_draw_description_at(c, 86, meta.text_id, 10);

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

void building_bricklayers_guild::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_bricklayers_guild::on_create(int orientation) {
    data.guild.max_workers = 1;
}

bool building_bricklayers_guild::can_spawn_bricklayer_man(int max_gatherers_per_building) {
    uint32_t total_sites = building_count_total(BUILDING_SMALL_MASTABA);
    uint32_t active_sites = building_count_active(BUILDING_SMALL_MASTABA);
    if (total_sites == active_sites) {
        return false;
    }
    
    bool has_free_man = (base.get_figures_number(FIGURE_BRICKLAYER) < data.guild.max_workers);
    if (!has_free_man) {
        return false;
    }

    return true;
}

void building_bricklayers_guild::spawn_figure() {
    base.check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    base.common_spawn_labor_seeker(100);
    int pct_workers = base.worker_percentage();
    if (pct_workers < 50) {
        return;
    }

    int spawn_delay = base.figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay < spawn_delay) {
        return;
    }

    base.figure_spawn_delay = 0;
    if (!can_spawn_bricklayer_man(data.guild.max_workers)) {
        return;
    }

    building* monument = buildings_valid_first([&] (building &b) {
        if (!b.is_monument() || !building_monument_is_unfinished(&b)) {
            return false;
        }

        return building_monument_need_bricklayers(&b);
    });

    if (!monument) {
        return;
    }

    auto f = base.create_figure_with_destination(FIGURE_BRICKLAYER, monument, FIGURE_ACTION_10_BRIRKLAYER_CREATED, BUILDING_SLOT_SERVICE);
    monument->monument_add_workers(f->id);
    f->wait_ticks = random_short() % 30; // ok
}

bool building_bricklayers_guild::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    return true;
}
