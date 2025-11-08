#include "figure_standart_bearer.h"

figures::model_t<figure_standard_bearer> standard_bearer_m;

void figure_standard_bearer::on_create() {
    figure_impl::on_create();
}

void figure_standard_bearer::figure_action() {
    const formation *m = formation_get(base.formation_id);

    base.wait_ticks = 0;
    base.map_figure_remove();
    if (m->is_at_fort) {
        base.tile = m->tile;
    } else {
        base.tile = m->standard_tile;
    }

    base.cc_coords.x = 15 * tilex() + 7;
    base.cc_coords.y = 15 * tiley() + 7;
    base.map_figure_add();
}

void figure_standard_bearer::on_post_load() {
    figure_impl::on_post_load();
    setup_flag_animation();
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

void figure_standard_bearer::figure_draw(painter &ctx, vec2i pixel, int hightlight) {
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
    const image_t *flag = image_get(base.animctx.start_frame());
    const vec2i flag_offset = vec2i(0, -flag->height);
    //if (m->is_halted) 
    {
        ctx.img_generic(base.main_image_id, pixel + pole_offset + flag_offset);
    }

    // top icon
    int icon_image_id = anim("sign").first_img() + formation_get(base.formation_id)->batalion_id;
    const vec2i icon_offset = vec2i(0, -image_get(icon_image_id)->height);
    ctx.img_generic(icon_image_id, pixel + flag_offset + pole_offset + icon_offset);
}

void figure_standard_bearer::before_poof() {
    setup_flag_animation();
}

void figure_standard_bearer::main_image_update() {
    base.main_image_id = base.animctx.start_frame() + base.animctx.current_frame();
}
