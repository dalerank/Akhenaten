#include "building_tower.h"

#include "js/js_game.h"
#include "grid/terrain.h"
#include "grid/road_access.h"
#include "grid/building_tiles.h"
#include "grid/tiles.h"
#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "io/gamefiles/lang.h"
#include "core/direction.h"
#include "city/labor.h"
#include "figure/figure.h"
#include "building/building_barracks.h"

buildings::model_t<building_brick_tower> brick_tower_m;
buildings::model_t<building_mud_tower> mud_tower_m;

void building_tower::on_create(int orientation) {
    map_terrain_remove_with_radius(tilex(), tiley(), 2, 0, TERRAIN_WALL);
    map_building_tiles_add(id(), tile(), params().building_size, params().anim["base"].first_img(), TERRAIN_BUILDING | TERRAIN_GATEHOUSE);
    map_tiles_update_area_walls(tile(), 5);
}

void building_tower::window_info_background(object_info &c) {
    c.help_id = 85;
    window_building_play_sound(&c, "Wavs/tower.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(e_text_tower, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 91, 2);
    else if (b->has_figure(0))
        window_building_draw_description(c, 91, 3);
    else {
        window_building_draw_description(c, 91, 4);
    }
    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

void building_tower::spawn_figure() {
    check_labor_problem();
    tile2i road = map_get_road_access_tile(tile(), base.size);
    if (!road.valid()) {
        return;
    }

    common_spawn_labor_seeker(50);
    if (num_workers() <= 0) {
        return;
    }

    if (base.has_figure(0) && !base.has_figure(3)) { // has sentry but no ballista -> create
        create_figure_generic(FIGURE_BALLISTA, FIGURE_ACTION_180_BALLISTA_CREATED, BUILDING_SLOT_BALLISTA, DIR_0_TOP_RIGHT);
    }

    if (!base.has_figure(0)) {
        building_barracks_request_tower_sentry();
    }
}
