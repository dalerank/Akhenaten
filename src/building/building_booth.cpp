#include "building_booth.h"

#include "building/building.h"
#include "construction/build_planner.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/warnings.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "grid/building_tiles.h"
#include "grid/property.h"
#include "grid/building.h"
#include "grid/image.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "sound/sound_building.h"
#include "city/labor.h"

struct booth_model : public buildings::model_t<building_booth> {
    int booth = 0;
} booth_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_booth);
void config_load_building_booth() {
    booth_m.load();
    booth_m.booth = booth_m.anim["booth"].first_img();
}

void building_booth::update_day() {
    building_impl::update_day();

    int shows = 0;
    if (data.entertainment.days1 > 0) {
        --data.entertainment.days1;
        ++shows;
    }

    data.entertainment.num_shows = shows;
}

void building_booth::on_place(int orientation, int variant) {
    data.entertainment.booth_corner_grid_offset = tile().grid_offset();
    data.entertainment.orientation = orientation;

    building_impl::on_place(orientation, variant);
}

void building_booth::on_place_update_tiles(int orientation, int variant) {
    int image_id = anim(animkeys().square).first_img();

    // add underlying plaza first
    map_add_venue_plaza_tiles(id(), params().building_size, tile(), image_id, false);
    int absolute_orientation = (abs(orientation * 2 + (8 - city_view_orientation())) % 8) / 2;

    // add additional building parts, update graphics accordingly
    switch (absolute_orientation) {
    case 0: build_planner_latch_on_venue(BUILDING_BOOTH, &base, 0, 0, orientation, true); break;
    case 1: build_planner_latch_on_venue(BUILDING_BOOTH, &base, 1, 0, orientation, true); break;
    case 2: build_planner_latch_on_venue(BUILDING_BOOTH, &base, 1, 1, orientation, true); break;
    case 3: build_planner_latch_on_venue(BUILDING_BOOTH, &base, 0, 1, orientation, true); break;
    }
}

void building_booth::on_place_checks() {
    if (building_count_active(BUILDING_JUGGLER_SCHOOL) <= 0) {
        building_construction_warning_show(WARNING_BUILD_ACTOR_COLONY);
    }
}

void building_booth::window_info_background(object_info &c) {
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, b->get_sound());
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
        window_building_draw_description(c, group_id, 4);
    } else if (!b->data.entertainment.num_shows) {
        window_building_draw_description(c, group_id, 2);
    } else if (b->data.entertainment.days1) {
        window_building_draw_description(c, group_id, 3);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 6);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(group_id, 6, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(group_id, 7 + b->data.entertainment.days3_or_play, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(group_id, 5, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void building_booth::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0) {
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
        }
    }
}

bool building_booth::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int color_mask = 0;
    if (drawing_building_as_deleted(&base) || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    int grid_offset = tile.grid_offset();
    if (data.entertainment.days1 && map_image_at(grid_offset) == booth_m.booth) {
        const animation_t &anim = this->anim(animkeys().juggler);
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }
    return true;
}

bool building_booth::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    int image_id = map_image_at(tile);
    return (booth_m.booth != image_id);
}

bool building_booth::force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    int image_id = map_image_at(tile);
    if (booth_m.booth == image_id) {
        ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, mask);
        ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, mask);
    }

    return false;
}

void building_booth::update_map_orientation(int map_orientation) {
    int plaza_image_id = anim(animkeys().square).first_img();
    tile2i btile(data.entertainment.booth_corner_grid_offset);
    map_add_venue_plaza_tiles(id(), base.size, btile, plaza_image_id, true);
}

void building_booth::on_undo() {
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            if (map_building_at(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0) {
                map_building_set(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
            }
        }
    }
}

void building_booth::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int size = booth_m.building_size;
    int square_id = booth_m.anim[animkeys().square].first_img();
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, COLOR_MASK_GREEN);
    }

    switch (orientation / 2) {
    case 0: draw_building_ghost(ctx, booth_m.booth, pixel, COLOR_MASK_GREEN); break;
    case 1: draw_building_ghost(ctx, booth_m.booth, pixel + vec2i{30, 15}, COLOR_MASK_GREEN); break;
    case 2: draw_building_ghost(ctx, booth_m.booth, pixel + vec2i{0, 30}, COLOR_MASK_GREEN); break;
    case 3: draw_building_ghost(ctx, booth_m.booth, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN); break;
    }
}