#include "building_raw_material.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
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

#include "graphics/animation.h"

namespace model {

struct raw_building_t {
    const e_building_type type;
    const pcstr name;
    bstring64 meta_id;
    e_resource output_resource;
    e_labor_category labor_category;
    animations_t anim;
};

raw_building_t clay_pit{BUILDING_CLAY_PIT, "building_clay_pit"};
raw_building_t gold_mine{BUILDING_GOLD_MINE, "building_gold_mine"};
raw_building_t gems_mine{BUILDING_GEMSTONE_MINE, "building_gems_mine"};
raw_building_t copper_mine{BUILDING_COPPER_MINE, "building_copper_mine"};

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_raw_materials);
void config_load_building_raw_materials() {
    auto load_raw_material_model = [] (model::raw_building_t &model) {
        g_config_arch.r_section(model.name, [&model] (archive arch) {
            model.labor_category = arch.r_type<e_labor_category>("labor_category");
            model.output_resource = arch.r_type<e_resource>("output_resource");
            model.meta_id = arch.r_string("meta_id");
            model.anim.load(arch);
            city_labor_set_category(model);
        });

    };

    load_raw_material_model(model::clay_pit);
    load_raw_material_model(model::gold_mine);
    load_raw_material_model(model::gems_mine);
    load_raw_material_model(model::copper_mine);
}

static void building_raw_material_draw_info(object_info& c, const char* type, e_resource resource) {
    auto &meta = building::get_info(type);
    painter ctx = game.painter();
    c.help_id = meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

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

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
    window_building_draw_description_at(c, 16 * c.height_blocks - 136, meta.text_id, 1);
}

void building_marble_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "marble_quarry", RESOURCE_MARBLE);
}
void building_limestone_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "limestone_quarry", RESOURCE_LIMESTONE);
}

void building_timber_yard_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "timber_yard", RESOURCE_TIMBER);
}
void building_reed_gatherer_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "reed_farm", RESOURCE_REEDS);
}
void building_sandstone_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "sandstone_quarry", RESOURCE_SANDSTONE);
}
void building_granite_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "granite_quarry", RESOURCE_SANDSTONE);
}

void building_mine::on_create() {
    base.output_resource_first_id = params().output_resource;
}

void building_mine::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, params().meta_id.c_str(), params().output_resource);
}

bool building_mine::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = params().anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

int building_mine_gold::get_produce_uptick_per_day() const {
    if (config_get(CONFIG_GP_CH_GOLDMINE_TWICE_PRODUCTION)) {
        return base.num_workers / 5.f;
    } else {
        return base.num_workers / 10.f;
    }
}

const model::raw_building_t &building_mine_gold::params() const { return model::gold_mine; }
const model::raw_building_t &building_mine_copper::params() const { return model::copper_mine; }
const model::raw_building_t &building_mine_gems::params() const { return model::gems_mine; }

void building_quarry_stone::on_create() {
    base.output_resource_first_id = RESOURCE_STONE;
}

void building_quarry_stone::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, "plainstone_quarry", RESOURCE_STONE);
}

void building_clay_pit::on_create() {
    base.output_resource_first_id = model::clay_pit.output_resource;
}

void building_clay_pit::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, model::clay_pit.meta_id, model::clay_pit.output_resource);
}

int building_clay_pit::get_fire_risk(int value) const {
    if (config_get(CONFIG_GP_CH_CLAY_PIT_FIRE_RISK_REDUCED)) {
        return value / 2;
    }

    return value;
}

bool building_clay_pit::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = model::clay_pit.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}
