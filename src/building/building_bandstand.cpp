#include "building_bandstand.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "construction/build_planner.h"
#include "city/labor.h"
#include "game/resource.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "sound/sound_building.h"

struct bandstand_model : public buildings::model_t<building_bandstand>{
    int stand_sn_n = 0;
    int stand_sn_s = 0;
    int stand_we_w = 0;
    int stand_we_e = 0;
    int booth = 0;
} bandstand_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_bandstand_config);
void config_load_building_bandstand_config() {
    bandstand_m.load();
    bandstand_m.stand_sn_n = bandstand_m.anim["stand_sn_n"].first_img();
    bandstand_m.stand_sn_s = bandstand_m.anim["stand_sn_s"].first_img();
    bandstand_m.stand_we_w = bandstand_m.anim["stand_we_w"].first_img();
    bandstand_m.stand_we_e = bandstand_m.anim["stand_we_e"].first_img();
    bandstand_m.booth = bandstand_m.anim["booth"].first_img();
}

void building_bandstand::on_create(int orientation) {
    base.fire_proof = 1;
}

void building_bandstand::update_day() {
    int shows = 0;
    auto update_shows = [&] (auto &days) { if (days > 0) { --days; ++shows; } };
    update_shows(data.entertainment.days1);
    update_shows(data.entertainment.days2);

    data.entertainment.num_shows = shows;
}

void building_bandstand::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    data.entertainment.booth_corner_grid_offset = tile().grid_offset();
    data.entertainment.orientation = orientation;

    int size = params().building_size;
    int image_id = params().anim["square"].first_img();

    // add underlying plaza first
    map_add_venue_plaza_tiles(id(), size, tile(), image_id, false);
    int absolute_orientation = (abs(orientation * 2 + (8 - city_view_orientation())) % 8) / 2;
    // add additional building parts, update graphics accordingly
    switch (absolute_orientation) {
    case 0:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 2, 1, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 2, 0, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 0, 0, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 1, 0, false);
        break;

    case 1:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 1, 2, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 2, 2, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 1, 0, 1, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 2, 0, 1, false);
        break;

    case 2:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 2, 1, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 2, 2, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 1, 2, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 2, 2, false);
        break;

    case 3:
        build_planner_latch_on_venue(BUILDING_GARDENS, &base, 1, 2, 0);
        build_planner_latch_on_venue(BUILDING_BOOTH, &base, 0, 2, 0);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 1, 0, 3, true);
        build_planner_latch_on_venue(BUILDING_BANDSTAND, &base, 0, 0, 3, false);
        break;
    }
}

void building_bandstand::spawn_figure() {
    if (!is_main())
        return;

    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0) {
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
        }

        if (data.entertainment.days2 > 0) {
            create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
        }
    }
}

bool building_bandstand::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    int imgs[] = {bandstand_m.booth, bandstand_m.stand_sn_n, bandstand_m.stand_sn_s, bandstand_m.stand_we_e, bandstand_m.stand_we_w};
    int image_id = map_image_at(tile);
    const auto it = std::find(std::begin(imgs), std::end(imgs), image_id);
    return (it == std::end(imgs));
}

bool building_bandstand::force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    int imgs[] = {bandstand_m.booth, bandstand_m.stand_sn_n, bandstand_m.stand_sn_s, bandstand_m.stand_we_e, bandstand_m.stand_we_w};
    int image_id = map_image_at(tile);
    const auto it = std::find(std::begin(imgs), std::end(imgs), image_id);
    if (it != std::end(imgs)) {
       ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, mask);
       ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, mask);
    }
    return false;
}

void building_bandstand::window_info_background(object_info &c) {
    c.help_id = 72;

    window_building_play_sound(&c, snd::get_building_info_sound("bandstand"));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(71, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
        window_building_draw_description(c, 71, 6);
    } else if (!b->data.entertainment.num_shows) {
        window_building_draw_description(c, 71, 2);
    } else if (b->data.entertainment.num_shows == 2) {
        window_building_draw_description(c, 71, 3);
    } else if (b->data.entertainment.days1) {
        window_building_draw_description(c, 71, 4);
    } else if (b->data.entertainment.days2) {
        window_building_draw_description(c, 71, 5);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 7);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(71, 8, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(71, 7, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }

    if (b->data.entertainment.days2 > 0) {
        int width = lang_text_draw(71, 10, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days2, c.offset.x + width + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(72, 7 + b->data.entertainment.days3_or_play, c.offset.x + 32, c.offset.y + 222, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(71, 9, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void building_bandstand::draw_shows_musicians(painter &ctx, vec2i pixel, int direction, color color_mask) {
    building* main = base.main();
    if (main->data.entertainment.days2) {
        building* next_tile = base.next();
        switch (direction) {
        case 0:
        {
            const animation_t &anim = bandstand_m.anim["musician_sn"];
            building_draw_normal_anim(ctx, pixel, &base, tile(), anim, color_mask);
        }
        break;

        case 1:
        {
            const animation_t &anim = bandstand_m.anim["musician_we"];
            building_draw_normal_anim(ctx, pixel, &base, tile(), anim, color_mask);
        }
        break;
        }
    }
}

void building_bandstand::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
    building_increase_type_count(BUILDING_BOOTH, num_workers() > 0);
}

bool building_bandstand::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int color_mask = 0;
    if (drawing_building_as_deleted(&base) || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    int grid_offset = tile.grid_offset();
    if (map_image_at(grid_offset) == bandstand_m.stand_sn_n) {
        draw_shows_musicians(ctx, point, 1, color_mask);
    } else if (map_image_at(grid_offset) == bandstand_m.stand_we_w) {
        draw_shows_musicians(ctx, point, 0, color_mask);
    }

    if (map_image_at(grid_offset) == bandstand_m.booth) {
        const animation_t &anim = bandstand_m.anim["juggler"];
        building* main = base.main();
        if (main->data.entertainment.days1) {
            building_draw_normal_anim(ctx, point, &base, tile, anim, mask);
        }
    }

    return false;
}

void building_bandstand::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int size = bandstand_m.building_size;
    int square_id = bandstand_m.anim["square"].first_img();
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, COLOR_MASK_GREEN);
    }

    switch (orientation / 2) {
    case 0:
        draw_building_ghost(ctx, bandstand_m.stand_sn_n, pixel, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_sn_s, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{60, 30}, COLOR_MASK_GREEN);
        break;
    case 1:
        draw_building_ghost(ctx, bandstand_m.stand_we_w, pixel + vec2i{30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_we_e, pixel + vec2i{60, 30}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{0, 60}, COLOR_MASK_GREEN);
        break;
    case 2:
        draw_building_ghost(ctx, bandstand_m.stand_sn_n, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_sn_s, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{0, 60}, COLOR_MASK_GREEN);
        break;
    case 3:
        draw_building_ghost(ctx, bandstand_m.stand_we_w, pixel, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.stand_we_e, pixel + vec2i{30, 15}, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, bandstand_m.booth, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
        break;
    }
}
