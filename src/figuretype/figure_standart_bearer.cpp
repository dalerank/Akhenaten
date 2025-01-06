#include "figure_standart_bearer.h"

figures::model_t<figure_standard_bearer> standard_bearer_m;

void figure_standard_bearer::figure_action() {
    const formation *m = formation_get(base.formation_id);

    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(16);
    base.map_figure_remove();
    if (m->is_at_fort) {
        base.tile = m->tile;
    } else {
        base.tile = m->standard_tile;
    }
    //    tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
    base.cc_coords.x = 15 * tilex() + 7;
    base.cc_coords.y = 15 * tiley() + 7;
    base.map_figure_add();

    base.sprite_image_id = image_id_from_group(GROUP_FIGURE_FORT_STANDARD_POLE) + 20 - m->morale / 5;
    if (m->figure_type == FIGURE_INFANTRY) {
        if (m->is_halted)
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 8;
        else {
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + base.anim.frame / 2;
        }
    } else if (m->figure_type == FIGURE_FCHARIOTEER) {
        if (m->is_halted)
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 26;
        else {
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 18 + base.anim.frame / 2;
        }
    } else {
        if (m->is_halted)
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 17;
        else {
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 9 + base.anim.frame / 2;
        }
    }
}

void figure_standard_bearer::figure_draw(painter &ctx, vec2i pixel, int hightlight, vec2i *coord_out) {
    if (formation_get(base.formation_id)->in_distant_battle) {
        return;
    }
    // base
    ImageDraw::img_generic(ctx, base.sprite_image_id, pixel);
    // flag
    int flag_height = image_get(base.cart_image_id)->height;
    ImageDraw::img_generic(ctx, base.cart_image_id, pixel.x, pixel.y - flag_height);
    // top icon
    int icon_image_id = image_id_from_group(PACK_GENERAL, 127) + formation_get(base.formation_id)->legion_id;
    ImageDraw::img_generic(ctx, icon_image_id, pixel.x, pixel.y - image_get(icon_image_id)->height - flag_height);
}
