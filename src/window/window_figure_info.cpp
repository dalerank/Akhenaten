#include "window_figure_info.h"

#include "figure/figure.h"
#include "graphics/window.h"
#include "grid/figure.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/game.h"
#include "dev/debug.h"
#include "window/message_dialog.h"
#include "window/building/figures.h"
#include "window/window_city.h"
#include "game/game.h"
#include "game/state.h"
#include "sound/sound.h"

struct building_figures_data_t {
    int figure_images[7] = {0};
    int focus_button_id;
    object_info* context_for_callback;
};

building_figures_data_t g_building_figures_data;

void draw_figure_in_city(int figure_id, vec2i* coord, painter &ctx) {
    tile2i camera_tile = city_view_get_camera_mappoint();

    int grid_offset = figure_get(figure_id)->tile.grid_offset();
    widget_city_draw_for_figure(ctx, figure_id, coord);
}

void figure_info_window::prepare_figures(object_info &c) {
    if (c.nfigure.count <= 0) {
        return;
    }

    auto &data = g_building_figures_data;

    painter ctx = game.painter();
    vec2i coord = {0, 0};
    for (int i = 0; i < c.nfigure.count; i++) {
        draw_figure_in_city(c.nfigure.figure_ids[i], &coord, ctx);
        data.figure_images[i] = graphics_save_to_texture(data.figure_images[i], coord, {48, 48});
    }
    //        if (config_get(CONFIG_UI_ZOOM))
    //            graphics_set_active_canvas(CANVAS_CITY);
    //
    //        for (int i = 0; i < c->figure.count; i++) {
    //            draw_figure_in_city(c->figure.figure_ids[i], &coord);
    //            graphics_save_to_buffer(coord.x - 25, coord.y - 45, 48, 48, data.figure_images[i]);
    //        }
    //        graphics_set_active_canvas(CANVAS_UI);
    widget_city_draw(ctx);
}

void window_building_play_figure_phrase(object_info* c) {
    int figure_id = c->nfigure.figure_ids[c->nfigure.selected_index];
    figure* f = figure_get(figure_id);
    f->figure_phrase_play();
    c->show_overlay = f->dcast()->get_overlay();
    c->nfigure.phrase_group = f->phrase_group;
    c->nfigure.phrase_id = f->phrase_id;
    c->nfigure.phrase_key = f->phrase_key;
}

figure_info_window::figure_info_window() {
    window_figure_register_handler(this);
}

inline void figure_info_window::window_info_foreground(object_info &c) {
    draw();

    int figure_id = c.nfigure.figure_ids[c.nfigure.selected_index];

    figure *f = ::figure_get(figure_id);
    g_debug_figure_id = figure_id;

    bool custom_window = f->dcast()->window_info_background(c);
    if (custom_window) {
        return;
    }

    c.nfigure.drawn = 1;
}

void figure_info_window::window_info_background(object_info &c) {
    common_info_window::window_info_background(c);

    prepare_figures(c);

    int figure_id = c.nfigure.figure_ids[c.nfigure.selected_index];
    figure *f = ::figure_get(figure_id);

    c.nfigure.draw_debug_path = 1;
    //if (!c.figure.count) {
    //    lang_text_draw_centered(70, c.terrain_type + 10, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    //}

    int image_id = f->type;
    if (f->action_state == FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE || f->action_state == FIGURE_ACTION_75_FIREMAN_AT_FIRE) {
        image_id = 18;
    }

    ui["name"] = ui::str(254, f->name);
    ui["type"] = ui::str(64, f->type);
    ui["bigimage"].image(image_id);

    for (int i = 0; i < c.nfigure.count; i++) {
        bstring64 btn_id; btn_id.printf("button_figure%d", i);
        ui[btn_id].select(i == c.nfigure.selected_index);
        ui[btn_id].onclick([index = i, &c] {
            auto &data = g_building_figures_data;
            data.context_for_callback = &c;
            data.context_for_callback->nfigure.selected_index = index;
            window_invalidate();
        });

        auto screen_opt = ui[btn_id].dcast_image_button();
        if (screen_opt) {
            screen_opt->texture_id = g_building_figures_data.figure_images[i];
        }
    }

    window_building_play_figure_phrase(&c);
    ui["phrase"] = ui::str(c.nfigure.phrase_group, c.nfigure.phrase_id);

    ui["show_path"] = (f->draw_debug_mode ? "P" : "p");
    ui["show_path"].onclick([f] {
        f->draw_debug_mode = f->draw_debug_mode ? 0 :FIGURE_DRAW_DEBUG_ROUTING;
        window_invalidate();
    });

    e_overlay foverlay = f->dcast()->get_overlay();
    ui["show_overlay"].enabled = (foverlay != OVERLAY_NONE);
    ui["show_overlay"] = (game.current_overlay != foverlay ? "v" : "V");
    ui["show_overlay"].onclick([foverlay] {
        if (game.current_overlay != foverlay) {
            game_state_set_overlay((e_overlay)foverlay);
        } else {
            game_state_reset_overlay();
        }
        window_invalidate();
    });
}

int figure_info_window::window_info_handle_mouse(const mouse *m, object_info &c) {
    return 0;
}

bool figure_info_window::check(object_info &c) {
    return false;
}

figure *figure_info_window::figure_get(object_info &c) {
    int figure_id = map_figure_id_get(c.grid_offset);
    return ::figure_get(figure_id);
}

//void window_building_draw_figure_list(object_info* c) {
//    inner_panel_draw(c->offset.x + 16, c->offset.y + 40, c->bgsize.x - 2, 13);
//    c->figure.drawn = 1;
//    if (c->figure.count <= 0) {
//        lang_text_draw_centered(70, 0, c->offset.x, c->offset.y + 120, 16 * c->bgsize.x, FONT_NORMAL_BLACK_ON_DARK);
//        return;
//    } 
//
//    for (int i = 0; i < c->figure.count; i++) {
//        button_border_draw(c->offset.x + 60 * i + 25, c->offset.y + 45, 52, 52, i == c->figure.selected_index);
//        graphics_draw_from_texture(g_building_figures_data.figure_images[i], c->offset + vec2i(27 + 60 * i, 47), {48, 48});
//    }
//    draw_figure_info(c, c->figure.figure_ids[c->figure.selected_index]);
//}