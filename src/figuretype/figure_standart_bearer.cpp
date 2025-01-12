#include "figure_standart_bearer.h"

figures::model_t<figure_standard_bearer> standard_bearer_m;

void figure_standard_bearer::on_create() {

}

void figure_standard_bearer::figure_action() {
    const formation *m = formation_get(base.formation_id);
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(16);
    base.wait_ticks = 0;
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
}

void figure_standard_bearer::update_animation() {
    //
}

void figure_standard_bearer::on_config_reload() {
    image_set_animation(animkeys().none);
    setup_flag_animation();
}

void figure_standard_bearer::on_update_home() {
    setup_flag_animation();
}

void figure_standard_bearer::setup_flag_animation() {
    const formation *m = formation_get(base.formation_id);
    if (m->figure_type == FIGURE_INFANTRY) {
        image_set_animation("flag_infantry");
    } else if (m->figure_type == FIGURE_FCHARIOTEER) {
        image_set_animation("flag_chariots");
    } else {
        image_set_animation("flag_archers");
    }
}

void figure_standard_bearer::figure_draw(painter &ctx, vec2i pixel, int hightlight, vec2i *coord_out) {
    if (formation_get(base.formation_id)->in_distant_battle) {
        return;
    }

    const formation *m = formation_get(base.formation_id);
    // base
    const animation_t &pole = anim("pole");
    const int morale = (pole.max_frames * (21.f - m->morale / 5) / 21.f);
    const image_t *img = image_get(pole.first_img() + morale);
    const vec2i pole_offset = vec2i(0, -img->height);
    ImageDraw::img_generic(ctx, img, pixel + pole_offset);

    // flag
    const image_t *flag = image_get(base.anim.start());
    const vec2i flag_offset = vec2i(0, -flag->height);
    //if (m->is_halted) 
    {
        ImageDraw::img_generic(ctx, base.sprite_image_id, pixel + pole_offset + flag_offset);
    }

    // top icon
    int icon_image_id = anim("sign").first_img() + formation_get(base.formation_id)->legion_id;
    const vec2i icon_offset = vec2i(0, -image_get(icon_image_id)->height);
    ImageDraw::img_generic(ctx, icon_image_id, pixel + flag_offset + pole_offset + icon_offset);
}

void figure_standard_bearer::before_poof() {
    setup_flag_animation();
}

void figure_standard_bearer::main_update_image() {
    base.sprite_image_id = base.anim.start() + base.anim.current_frame();
}
