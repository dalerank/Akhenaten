#include "building/building_pavilion.h"

#include "building/count.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/labor.h"
#include "grid/image.h"
#include "js/js_game.h"

struct pavilion_model : public buildings::model_t<building_pavilion> {
    int base = 0;
    struct preview_offset {
        vec2i stand, stand_b, stand_e, booth;
    };

    preview_offset dir_0;
} pavilion_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_pavilion);
void config_load_building_pavilion() {
    pavilion_m.load([] (archive arch) {
        arch.r_section("preview_dir_0", [] (archive d_arch) {
            pavilion_m.dir_0.stand = d_arch.r_vec2i("stand");
            pavilion_m.dir_0.stand_b = d_arch.r_vec2i("stand_b");
            pavilion_m.dir_0.stand_e = d_arch.r_vec2i("stand_e");
            pavilion_m.dir_0.booth = d_arch.r_vec2i("booth");
        });
    });
    pavilion_m.base = pavilion_m.anim["base"].first_img();
}

void building_pavilion::on_create(int orientation) {

}

bool building_pavilion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (map_image_at(tile) == pavilion_m.base) {
        building* main = base.main();
        if (main->data.entertainment.days3_or_play) {
            int base_id = building_impl::params(BUILDING_PAVILLION).anim["base"].first_img();
            building_draw_normal_anim(ctx, point + vec2i{64, 0}, &base, tile, image_id_from_group(GROUP_DANCERS_SHOW) - 1, color_mask, base_id);
        }
    }

    return true;
}

void building_pavilion::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
    building_increase_type_count(BUILDING_BANDSTAND, num_workers() > 0);
    building_increase_type_count(BUILDING_BOOTH, num_workers() > 0);
}

void building_pavilion::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0)
            base.create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days2 > 0)
            base.create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days3_or_play > 0)
            base.create_roaming_figure(FIGURE_DANCER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }
}

void building_pavilion::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int size = pavilion_m.building_size;
    int square_id = building_impl::params(BUILDING_PAVILLION).anim["square"].first_img();
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, COLOR_MASK_GREEN);
    }
    int stand_sn_n = pavilion_m.anim["stand_sn_n"].first_img();
    int stand_sn_s = pavilion_m.anim["stand_sn_s"].first_img();
    int booth = pavilion_m.anim["booth"].first_img();
    int stand = pavilion_m.anim["base"].first_img();
    switch (orientation) {
    case 0:
        draw_building_ghost(ctx, stand, pixel + pavilion_m.dir_0.stand, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, stand_sn_n, pixel + pavilion_m.dir_0.stand_b, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, stand_sn_s, pixel + pavilion_m.dir_0.stand_e, COLOR_MASK_GREEN);
        draw_building_ghost(ctx, booth, pixel + pavilion_m.dir_0.booth, COLOR_MASK_GREEN);
        break;
    //case 1:
    //    draw_building_ghost(ctx, stand, pixel + vec2i{60, 30}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
    //    break;
    //case 2:
    //    draw_building_ghost(ctx, stand, pixel + vec2i{30, 15}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel + vec2i{90, 45}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{60, 60}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel + vec2i{0, 90}, COLOR_MASK_GREEN);
    //    break;
    //case 3:
    //    draw_building_ghost(ctx, stand, pixel + vec2i{-30, 45}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel + vec2i{30, 75}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{0, 90}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel + vec2i{90, 45}, COLOR_MASK_GREEN);
    //    break;
    //case 4:
    //    draw_building_ghost(ctx, stand, pixel + vec2i{30, 45}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel + vec2i{-90, 45}, COLOR_MASK_GREEN);
    //    break;
    //case 5:
    //    draw_building_ghost(ctx, stand, pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel + vec2i{60, 60}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{30, 75}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel + vec2i{-90, 45}, COLOR_MASK_GREEN);
    //    break;
    //case 6:
    //    draw_building_ghost(ctx, stand, pixel + vec2i{-60, 30}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel + vec2i{0, 60}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{-30, 75}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel, COLOR_MASK_GREEN);
    //    break;
    //case 7:
    //    draw_building_ghost(ctx, stand, pixel, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_n, pixel + vec2i{60, 30}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, stand_sn_s, pixel + vec2i{30, 45}, COLOR_MASK_GREEN);
    //    draw_building_ghost(ctx, booth, pixel + vec2i{-90, 45}, COLOR_MASK_GREEN);
    //    break;
    }
}

void building_pavilion::window_info_background(object_info &c) {
    c.help_id = 73;
    window_building_play_sound(&c, "wavs/colloseum.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(74, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 74, 6);
    else if (!b->data.entertainment.num_shows)
        window_building_draw_description(c, 74, 2);
    else if (b->data.entertainment.num_shows == 2)
        window_building_draw_description(c, 74, 3);
    else if (b->data.entertainment.days1)
        window_building_draw_description(c, 74, 5);
    else if (b->data.entertainment.days2)
        window_building_draw_description(c, 74, 4);

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 6);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(74, 8, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 7, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
    if (b->data.entertainment.days2 > 0) {
        int width = lang_text_draw(74, 10, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days2, c.offset.x + width + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 9, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}
