
#include "building_palace.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/ratings.h"
#include "city/city.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/animkeys.h"
#include "grid/desirability.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "game/game.h"

buildings::model_t<building_village_palace> village_building_palace_m;
buildings::model_t<building_town_palace> town_building_palace_m;
buildings::model_t<building_city_palace> city_building_palace_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_palace_model);
void config_load_building_palace_model() {
    village_building_palace_m.load();
    town_building_palace_m.load();
    city_building_palace_m.load();
}

void building_palace::on_create(int orientation) {
    base.labor_category = village_building_palace_m.labor_category;
}

void building_palace::on_post_load() {
    g_city.buildings.add_palace(&base);
}

void building_palace::on_destroy() {
    g_city.buildings.remove_palace(&base);
}

void building_palace::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    //if (g_desirability.get(tile()) <= 30) {
    //    map_building_tiles_add(id(), tile(), size(), image_id_from_group(GROUP_BUILDING_PALACE), TERRAIN_BUILDING);
    //} else {
    //    map_building_tiles_add(id(), tile(), size(), image_id_from_group(GROUP_BUILDING_PALACE_FANCY), TERRAIN_BUILDING);
    //}
}

void building_palace::window_info_background(object_info &c) {
    building* b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    painter ctx = game.painter();
    c.go_to_advisor.left_a = ADVISOR_FINANCIAL;

    window_building_play_sound(&c, snd::get_building_info_sound(b->type));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(105, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), c.offset.x + 16, c.offset.y + 36);

    int width = lang_text_draw(105, 2, c.offset.x + 44, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_amount(8, 0, b->tax_income_or_storage, c.offset.x + 44 + width, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 72, group_id, 10);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 72, group_id, 5);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 72, group_id, 6);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 72, group_id, 7);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 72, group_id, 8);
    else {
        window_building_draw_description_at(c, 72, group_id, 9);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);

    lang_text_draw(105, 3, c.offset.x + 60, c.offset.y + 220, FONT_NORMAL_BLACK_ON_LIGHT);
}

bool building_palace::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (worker_percentage() > 50) {
        draw_normal_anim(ctx, point, tile, color_mask);
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
