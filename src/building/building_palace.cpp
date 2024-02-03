
#include "building_palace.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/ratings.h"
#include "city/labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/property.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "game/game.h"

struct village_palace_model_t {
    static constexpr e_building_type type = BUILDING_VILLAGE_PALACE;
    e_labor_category labor_category;
    animations_t anim;
};
village_palace_model_t village_palace_model;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_palace_model);
void config_load_building_palace_model() {
    g_config_arch.r_section("building_village_palace", [] (archive arch) {
        village_palace_model.labor_category = arch.r_type<e_labor_category>("labor_category");
        village_palace_model.anim.load(arch);
    });
    
    city_labor_set_category(village_palace_model);
}

void building_palace::on_create() {
    base.labor_category = village_palace_model.labor_category;
}

void building_palace::window_info_background(object_info &c) {
    painter ctx = game.painter();
    c.go_to_advisor.left_a = ADVISOR_FINANCIAL;
    c.help_id = e_text_building_palace;

    window_building_play_sound(&c, snd::get_building_info_sound("palace"));
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(105, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), c.offset.x + 16, c.offset.y + 36);

    building* b = building_get(c.building_id);
    int width = lang_text_draw(105, 2, c.offset.x + 44, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_amount(8, 0, b->tax_income_or_storage, c.offset.x + 44 + width, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 72, 106, 10);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 72, 106, 5);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 72, 106, 6);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 72, 106, 7);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 72, 106, 8);
    else {
        window_building_draw_description_at(c, 72, 106, 9);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);

    lang_text_draw(105, 3, c.offset.x + 60, c.offset.y + 220, FONT_NORMAL_BLACK_ON_LIGHT);
}

bool building_palace::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    switch (type()) {
    case BUILDING_VILLAGE_PALACE:
        if (worker_percentage() > 50) {
            const animation_t &anim = village_palace_model.anim["work"];
            building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
        }
        break;
    }

    //int image_id = image_id_from_group(GROUP_BUILDING_PALACE);
    //ImageDraw::img_generic(ctx, image_id + 1, point.x + 138, point.y + 44 - city_rating_culture() / 2, color_mask);
    //ImageDraw::img_generic(ctx, image_id + 2, point.x + 168, point.y + 36 - city_rating_prosperity() / 2, color_mask);
    //ImageDraw::img_generic(ctx, image_id + 3, point.x + 198, point.y + 27 - city_rating_monument() / 2, color_mask);
    //ImageDraw::img_generic(ctx, image_id + 4, point.x + 228, point.y + 19 - city_rating_kingdom() / 2, color_mask);
    //// unemployed
    //image_id = image_group(IMG_HOMELESS);
    //int unemployment_pct = city_labor_unemployment_percentage_for_senate();
    //if (unemployment_pct > 0)  ImageDraw::img_generic(ctx, image_id + 108, point.x + 80,  point.y, color_mask);
    //if (unemployment_pct > 5)  ImageDraw::img_generic(ctx, image_id + 104, point.x + 230, point.y - 30, color_mask);
    //if (unemployment_pct > 10) ImageDraw::img_generic(ctx, image_id + 107, point.x + 100, point.y + 20, color_mask);
    //if (unemployment_pct > 15) ImageDraw::img_generic(ctx, image_id + 106, point.x + 235, point.y - 10, color_mask);
    //if (unemployment_pct > 20) ImageDraw::img_generic(ctx, image_id + 106, point.x + 66,  point.y + 20, color_mask);

    return true;
}