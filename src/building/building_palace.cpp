
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
#include "window/window_building_info.h"
#include "widget/city/ornaments.h"
#include "window/advisors.h"
#include "sound/sound_building.h"
#include "game/game.h"

struct palace_info_window : public building_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return building_get(c.building_id)->dcast_palace();
    }
};

buildings::model_t<building_village_palace> village_building_palace_m;
buildings::model_t<building_town_palace> town_building_palace_m;
buildings::model_t<building_city_palace> city_building_palace_m;
palace_info_window palace_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_palace_model);
void config_load_building_palace_model() {
    village_building_palace_m.load();
    town_building_palace_m.load();
    city_building_palace_m.load();
    palace_infow.load("info_window_palace");
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

bool building_palace::can_play_animation() const {
    return worker_percentage() > 50;
}

void building_palace::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();

    //if (g_desirability.get(tile()) <= 30) {
    //    map_building_tiles_add(id(), tile(), size(), image_id_from_group(GROUP_BUILDING_PALACE), TERRAIN_BUILDING);
    //} else {
    //    map_building_tiles_add(id(), tile(), size(), image_id_from_group(GROUP_BUILDING_PALACE_FANCY), TERRAIN_BUILDING);
    //}
}

bool building_palace::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

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

void palace_info_window::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    building *b = building_get(c.building_id);
    ui["resource_img"].image(RESOURCE_DEBEN);
    ui["title"] = ui::str(28, b->type);
    ui["vaults_hold"].text_var("%s %d Db", ui::str(c.group_id, 2), b->tax_income_or_storage);

    std::pair<int, int> reason = { c.group_id, 0 };
    if (!c.has_road_access) reason = { 69, 25 };
    else if (b->num_workers <= 0) reason.second = 10;
    else reason.second = approximate_value(c.worker_percentage / 100.f, make_array(9, 8, 7, 6, 5));

    draw_employment_details(c);
    ui["workers_desc"] = ui::str(reason.first, reason.second);

    ui["visit_advisor"].onclick([] {
        window_advisors_show_advisor(ADVISOR_RATINGS);
    });
}

