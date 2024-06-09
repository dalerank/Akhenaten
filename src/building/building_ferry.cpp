#include "building/building_ferry.h"

#include "city/labor.h"
#include "grid/water.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/routing/routing.h"
#include "graphics/elements/ui.h"

#include "io/gamefiles/lang.h"

#include "js/js_game.h"

buildings::model_t<building_ferry> ferry_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_ferry);
void config_load_building_ferry() {
    ferry_m.load();
}

void building_ferry::on_create(int orientation) {
    data.industry.orientation = orientation;
}

void building_ferry::on_place_update_tiles(int orientation, int variant) {
    int img_id = ferry_m.anim["base"].first_img() + orientation;
    map_water_add_building(id(), tile(), ferry_m.building_size, img_id);
    map_building_tiles_add(id(), tile(), ferry_m.building_size, img_id, TERRAIN_BUILDING|TERRAIN_ROAD|TERRAIN_FERRY_ROUTE);
}

void building_ferry::window_info_background(object_info &c) {
    c.help_id = 85;
    window_building_play_sound(&c, "wavs/gatehouse.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(e_text_ferry_landing, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building *ferry = building_get(c.building_id);
    if (!map_routing_ferry_has_routes(ferry)) {
        window_building_draw_description_at(c, 16 * c.bgsize.y - 158, e_text_ferry_landing, e_text_ferry_landing_no_routes);
    } else if (!ferry->has_road_access) {
        window_building_draw_description_at(c, 16 * c.bgsize.y - 158, e_text_ferry_landing, e_text_ferry_landing_no_roads);
    } else if (ferry->num_workers <= 0) {
        window_building_draw_description_at(c, 16 * c.bgsize.y - 158, e_text_ferry_landing, e_text_ferry_landing_no_workers);
    }
}

void building_ferry::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    int image_id = ferry_m.anim["base"].first_img() + image_offset;
    map_water_add_building(id(), tile(), ferry_m.building_size, image_id);
}

void building_ferry::highlight_waypoints() {
    building_impl::highlight_waypoints();

    ferry_tiles fpoints = map_water_docking_points(base);
    map_highlight_set(fpoints.point_a, 3);
    map_highlight_set(fpoints.point_b, 3);
}
