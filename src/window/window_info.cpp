#include "window_info.h"

#include "building/building.h"
#include "building/building_storage.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "overlays/city_overlay.h"
#include "core/calc.h"
#include "game/state.h"
#include "figure/figure.h"
#include "figure/formation_batalion.h"
#include "figure/figure_phrase.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/property.h"
#include "grid/road_access.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "game/game.h"
#include "input/input.h"
#include "window/advisors.h"
#include "window/building/common.h"
#include "window/building/culture.h"
#include "window/building/distribution.h"
#include "window/building/figures.h"
#include "window/building/government.h"
#include "window/building/terrain.h"
#include "window/building/utility.h"
#include "window/window_building_info.h"
#include "window/window_terrain_info.h"
#include "window/window_figure_info.h"
#include "window/window_ruin_info.h"
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "widget/widget_sidebar.h"
#include "io/gamefiles/lang.h"
#include "dev/debug.h"
#include "js/js_game.h"

#include <functional>
#include <utility>
#include <mutex>

object_info ANK_VARIABLE(def_object_info)
std::vector<common_info_window *> *g_window_building_handlers = nullptr;
std::vector<common_info_window *> *g_window_figure_handlers = nullptr;

struct empty_info_window : public common_info_window {
    virtual void window_info_background(object_info &c) override {
        //outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
        lang_text_draw_centered(70, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    }
};

terrain_info_window g_terrain_info_window;
figure_info_window figure_common_window;
building_info_window g_building_common_window;
empty_info_window g_empty_info_window;
ruin_info_window g_ruin_info_window;

void window_info_show(const tile2i& point, bool avoid_mouse);

void ANK_REGISTER_CONFIG_ITERATOR(config_load_info_window) {
    g_building_common_window.load("building_info_window");
    g_empty_info_window.load("empty_info_window");
    figure_common_window.load("figure_info_window");
    g_terrain_info_window.load("terrain_info_window");
    g_ruin_info_window.load("ruin_info_window");

    auto load_configs = [] (auto &handlers) {
        for (auto &handler : *handlers) {
            pcstr section = handler->section();
            if (section && *section) {
                handler->load(section);
            }
        }
    };

    load_configs(g_window_building_handlers);
    load_configs(g_window_figure_handlers);

    if (def_object_info.ui) {
        window_info_show(tile2i(def_object_info.grid_offset), true);
    }
}

static int center_in_city(int element_width_pixels) {
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);
    int margin = (view_size.x - element_width_pixels) / 2;
    return view_pos.x + margin;
}

void object_info::reset(tile2i tile) {
    grid_offset = tile.grid_offset();
    can_play_sound = true;
    storage_show_special_orders = 0;
    go_to_advisor = {ADVISOR_NONE, ADVISOR_NONE, ADVISOR_NONE};
    bid = map_building_at(tile);
    terrain_type = TERRAIN_INFO_EMPTY;
    nfigure.drawn = 0;
}

figure *object_info::figure_get() {
    int figure_id = nfigure.ids[nfigure.selected_index];
    return ::figure_get(figure_id);
}

building *object_info::building_get() {
    return ::building_get(bid);
}

void window_info_update(bool avoid_mouse) {
    auto &context = def_object_info;

    context.ui = nullptr;
    auto find_handler = [] (auto &handlers, auto &context) {
        if (context.ui) {
            return;
        }

        for (auto &handler : handlers) {
            if (handler->check(context)) {
                context.ui = handler;
                break;
            }
        }
    };

    if (!context.nfigure.ids.empty()) {
        find_handler(*g_window_figure_handlers, context);
        if (!context.ui) {
            context.ui = &figure_common_window;
        }
    }
    find_handler(*g_window_building_handlers, context);

    int building_id = map_building_at(context.grid_offset);
    if (!context.ui && building_id) {
        context.ui = &g_building_common_window;
        context.bid = building_id;
    }

    if (!context.ui && map_terrain_is(context.grid_offset, TERRAIN_RUBBLE)) {
        context.terrain_type = TERRAIN_INFO_RUBBLE;
        context.ui = &g_ruin_info_window;
    }

    if (!context.ui && g_terrain_info_window.check(context)) {
        context.ui = &g_terrain_info_window;
    }

    if (!context.ui) {
        context.ui = &g_empty_info_window;
    }

    context.ui->init(context);
    context.ui->update(context);

    // dialog size
    context.bgsize = context.ui->bgsize();

    if (avoid_mouse) {
        return;
    }

    // dialog placement
    context.offset = window_building_set_possible_position(mouse::get().pos(), context.bgsize);
}

void window_info_init(tile2i tile, bool avoid_mouse) {
    auto &context = def_object_info;
    context.reset(tile);
    context.fill_figures_info(tile);

    city_resource_determine_available();

    window_info_update(avoid_mouse);
}

static void window_info_draw_background(int) {
    auto &context = def_object_info;

    game.animation = false;
    window_city_draw_panels();
    window_city_draw();
    widget_sidebar_city_draw_foreground();
    context.ui->window_info_background(context);
}

static void window_info_draw_foreground(int) {
    auto &ui = *def_object_info.ui;

    ui.begin_widget(def_object_info.offset);
    ui.window_info_foreground(def_object_info);
    ui.end_widget();
}

static void window_info_handle_input(const mouse* m, const hotkeys* h) {
    auto &context = def_object_info;
    auto &ui = *def_object_info.ui;
  
    bool button_id = context.ui->window_info_handle_mouse(m, context);

    if (!button_id) {
        ui.begin_widget(def_object_info.offset);
        button_id = ui::handle_mouse(m);
        ui.end_widget();
    }

    if (!button_id && input_go_back_requested(m, h)) {
        context.reset(tile2i::invalid);
        if (context.storage_show_special_orders) {
            storage_settings_backup_check();
        } else {
            window_city_show();
        }
    }
}

void window_info_show(const tile2i& point, bool avoid_mouse) {
    auto get_tooltip = [] (tooltip_context* c) {
        auto &context = def_object_info;
        if (!context.ui) {
            return;
        }

        context.ui->draw_tooltip(c);
    };

    auto draw_refresh = [] () {
        auto &context = def_object_info;
        if (!context.ui) {
            return;
        }

        context.ui->window_info_background(context);
    };

    static window_type window = {
        WINDOW_BUILDING_INFO,
        window_info_draw_background,
        window_info_draw_foreground,
        window_info_handle_input,
        get_tooltip,
        draw_refresh,
    };

    window_info_init(point, avoid_mouse);
    window_show(&window);
}

int window_building_info_get_type() {
    auto &context = def_object_info;
    return building_get(context.bid)->type;
}

void window_building_info_show_storage_orders() {
    auto &context = def_object_info;
    context.storage_show_special_orders = 1;
}

template<typename T>
void window_info_register_handler_t(T &ptr, common_info_window *handler) {
    if (!ptr) {
        using PtrT = std::remove_reference_t<T>;
        using RawT = std::remove_pointer_t<T>;
        ptr = new RawT();
    }

    auto it = std::find(ptr->begin(), ptr->end(), handler);
    if (it == ptr->end()) {
        ptr->push_back(handler);
    }
}

void window_building_register_handler(common_info_window *handler) {
    window_info_register_handler_t(g_window_building_handlers, handler);
}

void window_figure_register_handler(common_info_window *handler) {
    window_info_register_handler_t(g_window_figure_handlers, handler);
}

vec2i common_info_window::bgsize() const {
    vec2i bgsize = ui["background"].pxsize() / 16; 
    return bgsize;
}

void common_info_window::window_info_foreground(object_info &c) {
    ui.draw(); 
}

void common_info_window::register_handlers() {
    events::subscribe([] (event_show_tile_info ev) {
        window_info_show(ev.tile, ev.avoid_mouse);
    });

    events::subscribe([] (event_update_tile_info ev) {
        window_info_update(true);
    });
}

void common_info_window::update_buttons(object_info &c) {
    vec2i bgsize = ui["background"].pxsize();
    ui["button_help"].onclick([&c] {
        if (c.help_id > 0) {
            const xstring help_id = lang_get_message_id(c.help_id);
            window_message_dialog_show(help_id, -1, window_city_draw_all);
        } else {
            window_message_dialog_show("message_dialog_help", -1, window_city_draw_all);
        }
    });

    ui["button_close"].onclick([&c] {
        if (c.storage_show_special_orders) {
            c.storage_show_special_orders = 0;
            storage_settings_backup_reset();
        } else {
            window_city_show();
        }
    });

    if (!ui.contains("first_advisor")) {
        return;
    }

    auto first_advisor = ui["first_advisor"].dcast_image_button();
    if (first_advisor) {
        first_advisor->enabled = c.go_to_advisor.first && g_city.is_advisor_available(c.go_to_advisor.first);
        first_advisor->img_desc.offset = (c.go_to_advisor.left_a - 1) * 3;
        first_advisor->pos.y = bgsize.y - 40;
        first_advisor->onclick([&c] {
            window_advisors_show_advisor(c.go_to_advisor.first);
        });
    }

    if (!ui.contains("second_advisor")) {
        return;
    }

    auto second_advisor = ui["second_advisor"].dcast_image_button();
    if (second_advisor) {
        second_advisor->enabled = c.go_to_advisor.left_a && g_city.is_advisor_available(c.go_to_advisor.left_a);
        second_advisor->img_desc.offset = (c.go_to_advisor.left_a - 1) * 3;
        second_advisor->pos.y = bgsize.y - 40;
        second_advisor->onclick([&c] {
            window_advisors_show_advisor(c.go_to_advisor.left_a);
        });
    }

    if (!ui.contains("third_advisor")) {
        return;
    }

    auto third_advisor = ui["third_advisor"].dcast_image_button();
    if (third_advisor) {
        third_advisor->enabled = c.go_to_advisor.left_b && g_city.is_advisor_available(c.go_to_advisor.left_b);
        third_advisor->img_desc.offset = (c.go_to_advisor.left_b - 1) * 3;
        third_advisor->pos.y = bgsize.y - 40;
        third_advisor->onclick([&c] {
            window_advisors_show_advisor(c.go_to_advisor.left_b);
        });
    }
}

void common_info_window::archive_load(archive arch) {
    widget::archive_load(arch);

    if (check(def_object_info)) {
        init(def_object_info);
    }

    arch.r_array_str("open_sounds", open_sounds);
}

void common_info_window::init(object_info &c) {
}

void common_info_window::draw_tooltip(tooltip_context *c) {
    textid tx = get_tooltip(def_object_info);
    pcstr tooltip = (pcstr)lang_get_string(tx);
    int button_id = ui::button_hover(&mouse::get());
    if (button_id > 0 && !(tooltip && *tooltip)) {
        tooltip = ui::button_tooltip(button_id - 1);
    }
}
