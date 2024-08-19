#include "window_figure_info.h"

#include "figure/figure.h"
#include "graphics/window.h"
#include "grid/figure.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/game.h"
#include "dev/debug.h"
#include "window/message_dialog.h"
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
figure_info_window g_figure_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_window_info);
void config_load_figure_window_info() {
    g_figure_info_window.load("figure_info_window");
}

void draw_figure_in_city(int figure_id, vec2i* coord, painter &ctx) {
    map_point camera_tile = city_view_get_camera_mappoint();

    int grid_offset = figure_get(figure_id)->tile.grid_offset();
    widget_city_draw_for_figure(ctx, figure_id, coord);
}

void window_figure_info_prepare_figures(object_info &c) {
    auto &data = g_building_figures_data;
    painter ctx = game.painter();

    if (c.figure.count > 0) {
        vec2i coord = {0, 0};
        for (int i = 0; i < c.figure.count; i++) {
            draw_figure_in_city(c.figure.figure_ids[i], &coord, ctx);
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
}

void window_building_play_figure_phrase(object_info* c) {
    int figure_id = c->figure.figure_ids[c->figure.selected_index];
    figure* f = figure_get(figure_id);
    f->figure_phrase_play();
    c->show_overlay = f->dcast()->get_overlay();
    c->figure.phrase_group = f->phrase_group;
    c->figure.phrase_id = f->phrase_id;
    c->figure.phrase_key = f->phrase_key;
}

figure_info_window::figure_info_window() {
    window_figure_register_handler(this);
}

inline void figure_info_window::window_info_foreground(object_info &c) {
    draw();

    draw_figure_info(&c, c.figure.figure_ids[c.figure.selected_index]);
    c.figure.drawn = 1;
}

void figure_info_window::window_info_background(object_info &c) {
    common_info_window::window_info_background(c);

    //ui.begin_widget(c.offset);

    window_figure_info_prepare_figures(c);

    c.figure.draw_debug_path = 1;
    //if (!c.figure.count) {
    //    lang_text_draw_centered(70, c.terrain_type + 10, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    //}

    for (int i = 0; i < c.figure.count; i++) {
        bstring64 btn_id; btn_id.printf("button_figure%d", i);
        ui[btn_id].select(i == c.figure.selected_index);
        ui[btn_id].onclick([index = i, &c] {
            auto &data = g_building_figures_data;
            data.context_for_callback = &c;
            data.context_for_callback->figure.selected_index = index;
            window_building_play_figure_phrase(data.context_for_callback);
            window_invalidate();
        });

        auto screen_opt = ui[btn_id].dcast_image_button();
        if (screen_opt) {
            screen_opt->texture_id = g_building_figures_data.figure_images[i];
        }
    }

    figure* f = figure_get(c.figure.figure_ids[0]);
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
    c.figure.selected_index = 0;
    c.figure.count = 0;
    for (int i = 0; i < 7; i++) {
        c.figure.figure_ids[i] = 0;
    }

    int figure_id = map_figure_id_get(c.grid_offset);
    while (figure_id > 0 && c.figure.count < 7) {
        figure *f = figure_get(figure_id);
        if (f->state != FIGURE_STATE_DEAD && f->action_state != FIGURE_ACTION_149_CORPSE) {
            switch (f->type) {
            case FIGURE_NONE:
            case FIGURE_EXPLOSION:
            case FIGURE_MAP_FLAG:
            case FIGURE_ARROW:
            case FIGURE_JAVELIN:
            case FIGURE_BOLT:
            case FIGURE_BALLISTA:
            case FIGURE_CREATURE:
            case FIGURE_FISHING_POINT:
            case FIGURE_FISHING_SPOT:
            case FIGURE_SPEAR:
            case FIGURE_CHARIOR_RACER:
            break;

            default:
            c.figure.figure_ids[c.figure.count++] = figure_id;
            //                        f->igure_phrase_determine();
            break;
            }
        }
        figure_id = (figure_id != f->next_figure) ? f->next_figure : 0;
    }

    return (c.figure.count > 0);
}

void draw_figure_info(object_info* c, int figure_id) {
    button_border_draw(c->offset.x + 24, c->offset.y + 102, 16 * (c->bgsize.x - 3), 138, 0);

    figure* f = figure_get(figure_id);
    g_debug_figure_id = figure_id;

    int type = f->type;
    bool custom_window = f->dcast()->window_info_background(*c);
    if (custom_window) {
        return;
    }

    if (type >= FIGURE_ENEMY43_SPEAR && type <= FIGURE_ENEMY53_AXE) {
        f->draw_enemy(c);
    } else if (f->is_herd()) {
        f->draw_animal(c);
    } else {
        f->draw_normal_figure(c);
    }
}

void window_building_draw_figure_list(object_info* c) {
    inner_panel_draw(c->offset.x + 16, c->offset.y + 40, c->bgsize.x - 2, 13);
    c->figure.drawn = 1;
    if (c->figure.count <= 0) {
        lang_text_draw_centered(70, 0, c->offset.x, c->offset.y + 120, 16 * c->bgsize.x, FONT_NORMAL_BLACK_ON_DARK);
        return;
    } 

    for (int i = 0; i < c->figure.count; i++) {
        button_border_draw(c->offset.x + 60 * i + 25, c->offset.y + 45, 52, 52, i == c->figure.selected_index);
        graphics_draw_from_texture(g_building_figures_data.figure_images[i], c->offset + vec2i(27 + 60 * i, 47), {48, 48});
    }
    draw_figure_info(c, c->figure.figure_ids[c->figure.selected_index]);
}