#include "window_info.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "overlays/city_overlay.h"
#include "core/calc.h"
#include "figure/figure.h"
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
#include "window/window_advisors.h"
#include "window/autoconfig_window.h"
#include "graphics/elements/ui_js.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "window/window_building_info.h"
#include "window/window_figure_info.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"
#include "io/gamefiles/lang.h"
#include "core/log.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include "graphics/elements/tooltip.h"
#include "input/mouse.h"

#include <functional>
#include <utility>
#include <mutex>

object_info ANK_VARIABLE(def_object_info)
std::vector<common_info_window *> *g_window_building_handlers = nullptr;
std::vector<common_info_window *> *g_window_batalion_handlers = nullptr;
std::vector<common_info_window *> *g_window_figure_handlers = nullptr;
std::vector<common_info_window *> *g_window_terrain_handlers = nullptr;

struct empty_info_window : public common_info_window {
    virtual void window_info_background(object_info &c) override {
        //outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
        lang_text_draw_centered(70, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    }
};

figure_info_window figure_common_window;
building_info_window g_building_common_window;
empty_info_window g_empty_info_window;

void window_info_show(const tile2i& point, bool avoid_mouse);

void ANK_REGISTER_CONFIG_ITERATOR(config_load_info_window) {
    g_building_common_window.load("building_info_window");
    g_empty_info_window.load("empty_info_window");
    figure_common_window.load("figure_info_window");

    auto load_configs = [] (auto &handlers) {
        if (!handlers) {
            return;
        }
        for (auto &handler : *handlers) {
            const xstring section = handler->section();
            if (!section.empty()) {
                handler->load(section);
            }
        }
    };

    load_configs(g_window_building_handlers);
    load_configs(g_window_batalion_handlers);
    load_configs(g_window_figure_handlers);
    load_configs(g_window_terrain_handlers);

    if (def_object_info.ui) {
        window_info_show(tile2i(def_object_info.grid_offset), true);
    }
}

void object_info::reset(tile2i tile) {
    grid_offset = tile.grid_offset();
    can_play_sound = true;
    go_to_advisor_first = ADVISOR_NONE;
    go_to_advisor_left_a = ADVISOR_NONE;
    go_to_advisor_left_b = ADVISOR_NONE;
    bid = map_building_at(tile);
    terrain_type = terrain_info_none;
    figure_drawn = 0;
    help_id = 0;
    help_link = {};
}

figure *object_info::figure_get() {
    int figure_id = figure_ids[figure_selected_index];
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

    if (!context.figure_ids.empty()) {
        verify_no_crash(g_window_batalion_handlers);
        find_handler(*g_window_batalion_handlers, context);
    }

    if (!context.ui && !context.figure_ids.empty()) {
        find_handler(*g_window_figure_handlers, context);
        if (!context.ui) {
            context.ui = &figure_common_window;
        }
    }
    verify_no_crash(g_window_building_handlers);
    find_handler(*g_window_building_handlers, context);

    int building_id = map_building_at(context.grid_offset);
    if (!context.ui && building_id) {
        context.ui = &g_building_common_window;
        context.bid = building_id;
    }

    verify_no_crash(g_window_terrain_handlers);
    if (!context.ui) {
        find_handler(*g_window_terrain_handlers, context);
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
    js_call_event_handlers("top_menu_draw", {});
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
        window_city_show();
    }
}

void window_info_show(const tile2i& point, bool avoid_mouse) {
    auto get_tooltip = [] (tooltip_context* c) {
        if (def_object_info.ui) {
            def_object_info.ui->draw_tooltip(c);
        }
    };

    auto draw_refresh = [] () {
        if (def_object_info.ui) {
            def_object_info.ui->window_info_background(def_object_info);
        }
    };

    static window_type window = {
        "window_building_info",
        window_info_draw_background,
        window_info_draw_foreground,
        window_info_handle_input,
        get_tooltip,
        draw_refresh,
    };

    window_info_init(point, avoid_mouse);
    window_show(&window);
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

void window_batalion_register_handler(common_info_window *handler) {
    window_info_register_handler_t(g_window_batalion_handlers, handler);
}

void window_figure_register_handler(common_info_window *handler) {
    window_info_register_handler_t(g_window_figure_handlers, handler);
}

void window_terrain_register_handler(common_info_window *handler) {
    window_info_register_handler_t(g_window_terrain_handlers, handler);
}

vec2i common_info_window::bgsize() const {
    vec2i bgsize = ui["background"].pxsize() / 16;
    return bgsize;
}

void common_info_window::window_info_background(object_info &c) {
    bvariant_map::scoped js_j;
    js_helper::writer(*js_j, window_info{c.offset});
    ui::dispatch_autoconfig_es_event(this, __func__, *js_j);
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

object_info &common_info_window::get_object_info() {
    return def_object_info;
}

void common_info_window::archive_load(archive arch) {
    widget::archive_load(arch);
    arch.r_array_str("open_sounds", open_sounds);
}

void common_info_window::init(object_info &c) {
}

void common_info_window::draw_tooltip(tooltip_context *c) {
    textid tx = get_tooltip(def_object_info);
    pcstr tooltip = tx.valid() ? (pcstr)lang_get_string(tx) : nullptr;
    int button_id = ui::button_hover(&mouse::get());
    if (button_id > 0 && !(tooltip && *tooltip)) {
        tooltip = ui::button_tooltip(button_id - 1);
    }
    if (tooltip && *tooltip) {
        c->text = tooltip;
        return;
    }
    // Element tooltips (e.g. workers_img) set via ui::set_tooltip during draw.
    const tooltip_context& uitooltip = ui::get_tooltip();
    if (!!uitooltip.text) {
        c->text = uitooltip.text;
    }
}
