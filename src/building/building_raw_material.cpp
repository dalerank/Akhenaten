#include "building_raw_material.h"

#include "building/building.h"
#include "city/object_info.h"
#include "building/count.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/random.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "graphics/text.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "city/labor.h"
#include "widget/city/ornaments.h"
#include "grid/random.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "figure/figure.h"

#include "graphics/animation.h"

buildings::model_t<building_clay_pit> clay_pit_m;
buildings::model_t<building_mine_gold> gold_mine_m;
buildings::model_t<building_mine_gems> gems_mine_m;
buildings::model_t<building_mine_copper> copper_mine_m;
buildings::model_t<building_reed_gatherer> gatherer_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_raw_materials);
void config_load_building_raw_materials() {
    clay_pit_m.load();
    gold_mine_m.load();
    gems_mine_m.load();
    copper_mine_m.load();
    gatherer_m.load();
}

void building_raw_material_draw_info(object_info& c, const char* type, e_resource resource) {
    const auto &meta = building_get(c.building_id)->dcast()->get_info();
    painter ctx = game.painter();
    c.help_id = meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    int pct_done = calc_percentage<int>(b->data.industry.progress, 200);
    int width = lang_text_draw(meta.text_id, 2, c.offset.x + 32, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(meta.text_id, 3, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access) {
        window_building_draw_description_at(c, 70, 69, 25);
    } else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, 70, meta.text_id, 4);
    else if (b->data.industry.curse_days_left > 4)
        window_building_draw_description_at(c, 70, meta.text_id, 11);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 70, meta.text_id, 5);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 70, meta.text_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 70, meta.text_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 70, meta.text_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 70, meta.text_id, 9);
    else
        window_building_draw_description_at(c, 70, meta.text_id, 10);

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
    window_building_draw_description_at(c, 16 * c.bgsize.y - 136, meta.text_id, 1);
}

void building_marble_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "marble_quarry", RESOURCE_MARBLE);
}

void building_mine::on_create(int orientation) {
    base.output_resource_first_id = params().output_resource;
}

void building_mine::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, params().meta_id.c_str(), params().output_resource);
}

bool building_mine::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point, &base, tile, anim("work"), color_mask);
    return true;
}

int building_mine_gold::get_produce_uptick_per_day() const {
    if (config_get(CONFIG_GP_CH_GOLDMINE_TWICE_PRODUCTION)) {
        return base.num_workers / 5.f;
    } else {
        return base.num_workers / 10.f;
    }
}

void building_mine_gold::update_count() const {
    building_increase_industry_count(RESOURCE_GOLD, num_workers() > 0);
}

const building_impl::static_params &building_mine_gold::params() const { return gold_mine_m; }
const animation_t &building_mine_gold::anim(pcstr key) const { return gold_mine_m.anim[key]; }

const building_impl::static_params &building_mine_copper::params() const { return copper_mine_m; }
const animation_t &building_mine_copper::anim(pcstr key) const { return copper_mine_m.anim[key]; }

void building_mine_copper::update_count() const {
    building_increase_industry_count(RESOURCE_COPPER, num_workers() > 0);
}

const building_impl::static_params &building_mine_gems::params() const { return gems_mine_m; }
const animation_t &building_mine_gems::anim(pcstr key) const { return gems_mine_m.anim[key]; }

void building_mine_gems::update_count() const {
    building_increase_industry_count(RESOURCE_GEMS, num_workers() > 0);
}

void building_quarry_stone::on_create(int orientation) {
    base.output_resource_first_id = RESOURCE_STONE;
}

void building_quarry_stone::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, "plainstone_quarry", RESOURCE_STONE);
}

void building_clay_pit::on_create(int orientation) {
    base.output_resource_first_id = clay_pit_m.output_resource;
}

void building_clay_pit::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, clay_pit_m.meta_id, clay_pit_m.output_resource);
}

int building_clay_pit::get_fire_risk(int value) const {
    if (config_get(CONFIG_GP_CH_CLAY_PIT_FIRE_RISK_REDUCED)) {
        return value / 2;
    }

    return value;
}

bool building_clay_pit::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = clay_pit_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

void building_clay_pit::update_count() const {
    building_increase_industry_count(RESOURCE_CLAY, num_workers() > 0);
}

void building_reed_gatherer::on_create(int orientation) {
    base.output_resource_first_id = RESOURCE_REEDS;
    data.industry.max_gatheres = 1;
}

void building_reed_gatherer::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, "reed_farm", RESOURCE_REEDS);
}

bool building_reed_gatherer::can_spawn_gatherer(int max_gatherers_per_building, int carry_per_person) {
    bool resource_reachable = false;
    resource_reachable = map_routing_citizen_found_terrain(base.road_access, nullptr, TERRAIN_MARSHLAND);

    if (!resource_reachable) {
        return false;
    }

    int gatherers_this_yard = base.get_figures_number(FIGURE_REED_GATHERER);

    // can only spawn if there's space for more reed in the building
    int max_loads = 500 / carry_per_person;
    if (gatherers_this_yard < max_gatherers_per_building
        && gatherers_this_yard + (base.stored_amount() / carry_per_person) < (max_loads - gatherers_this_yard)) {
        return true;
    }

    return false;
}

bool building_reed_gatherer::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = gatherer_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

void building_reed_gatherer::update_count() const {
    building_increase_industry_count(RESOURCE_REEDS, num_workers() > 0);
}

void building_reed_gatherer::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(100);
    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;

        if (can_spawn_gatherer(data.industry.max_gatheres, 50)) {
            auto f = create_figure_generic(FIGURE_REED_GATHERER, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
            random_generate_next();
            f->wait_ticks = random_short() % 30; // ok
            return;
        }
    }

    base.common_spawn_goods_output_cartpusher();
}
