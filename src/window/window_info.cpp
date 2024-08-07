#include "window_info.h"

#include "building/building.h"
#include "building/model.h"
#include "building/building_storage.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "overlays/city_overlay.h"
#include "core/calc.h"
#include "game/state.h"
#include "figure/figure.h"
#include "figure/formation_legion.h"
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
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "dev/debug.h"

#include <functional>
#include <utility>
#include <mutex>

object_info g_object_info;
svector<common_info_window *, 10> *g_window_info_handlers = nullptr;

struct empty_info_window : public common_info_window {
    virtual void window_info_background(object_info &c) override {
        //outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
        lang_text_draw_centered(70, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    }
};

terrain_info_window g_terrain_info_window;
building_info_window g_building_info_window;
empty_info_window g_empty_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_info_window);
void config_load_info_window() {
    g_building_info_window.load("building_info_window");
    g_empty_info_window.load("empty_info_window");
    g_terrain_info_window.load("terrain_info_window");
}

static int center_in_city(int element_width_pixels) {
    vec2i view_pos, view_size;
    const view_data_t &viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);
    int margin = (view_size.x - element_width_pixels) / 2;
    return view_pos.x + margin;
}

void object_info::reset(tile2i tile) {
    grid_offset = tile.grid_offset();
    can_play_sound = true;
    storage_show_special_orders = 0;
    go_to_advisor = {ADVISOR_NONE, ADVISOR_NONE, ADVISOR_NONE};
    building_id = map_building_at(tile);
    rubble_building_type = map_rubble_building_type(grid_offset);
    has_reservoir_pipes = map_terrain_is(tile, TERRAIN_GROUNDWATER);
    aqueduct_has_water = !!map_canal_at(grid_offset) && ((map_image_at(tile) - image_id_from_group(GROUP_BUILDING_AQUEDUCT)) < 15);
    terrain_type = TERRAIN_INFO_EMPTY;
    figure.drawn = 0;
    figure.draw_debug_path = 0;
    show_overlay = OVERLAY_NONE;
}

void buiding_info_init(tile2i tile) {
    auto &context = g_object_info;
    context.reset(tile);

    city_resource_determine_available();

    context.ui = nullptr;
    for (auto &handler : *g_window_info_handlers) {
        if (handler->check(context)) {
            context.ui = handler;
            break;
        }
    }

    int building_id = map_building_at(context.grid_offset);
    if (!context.ui && building_id) {
        context.ui = &g_building_info_window;
        context.building_id = building_id;
    }

    if (!context.ui && g_terrain_info_window.check(context)) {
        context.ui = &g_terrain_info_window;
    }

    if (!context.ui) {
        context.ui = &g_empty_info_window;
    }

    // dialog size
    int bgsizey[] = {16, 16, 18, 19, 14, 23, 16};
    context.bgsize = {29, bgsizey[context.ui->get_height_id(context)]};

    // dialog placement
    int s_width = screen_width();
    int s_height = screen_height();
    context.offset.x = center_in_city(16 * context.bgsize.x);
    if (s_width >= 1024 && s_height >= 768) {
        context.offset = *mouse_get();
        context.offset = window_building_set_possible_position(context.offset, context.bgsize);
    } else if (s_height >= 600 && mouse_get()->y <= (s_height - 24) / 2 + 24) {
        context.offset.y = s_height - 16 * context.bgsize.y - MARGIN_POSITION;
    } else {
        context.offset.y = MIN_Y_POSITION;
    }
}

static void buiding_info_draw_background() {
    auto &context = g_object_info;

    game.animation = false;
    window_city_draw_panels();
    window_city_draw();
    context.ui->window_info_background(context);
}

static void buiding_info_draw_foreground() {
    auto &ui = *g_object_info.ui;
    ui.begin_widget(g_object_info.offset);
    ui.window_info_foreground(g_object_info);
}

static void building_info_handle_input(const mouse* m, const hotkeys* h) {
    auto &context = g_object_info;

    bool button_id = ui::handle_mouse(m);
  
    if (!button_id) {
        int btn_id = context.ui->window_info_handle_mouse(m, context);
        button_id |= !!btn_id;
    }

    if (!button_id && input_go_back_requested(m, h)) {
        if (context.storage_show_special_orders) {
            storage_settings_backup_check();
        } else {
            window_city_show();
        }
    }
}

void window_building_info_show(const tile2i& point) {
    auto get_tooltip = [] (tooltip_context* c) {
        auto &context = g_object_info;
        if (!context.ui) {
            return;
        }

        context.ui->draw_tooltip(c);
    };

    auto draw_refresh = [] () {
        auto &context = g_object_info;
        if (!context.ui) {
            return;
        }

        context.ui->window_info_background(context);
    };

    static window_type window = {
        WINDOW_BUILDING_INFO,
        buiding_info_draw_background,
        buiding_info_draw_foreground,
        building_info_handle_input,
        get_tooltip,
        draw_refresh,
    };

    buiding_info_init(point);
    window_show(&window);
}

int window_building_info_get_type() {
    auto &context = g_object_info;
    return building_get(context.building_id)->type;
}

void window_building_info_show_storage_orders() {
    auto &context = g_object_info;
    context.storage_show_special_orders = 1;
    window_invalidate();
}

void window_info_register_handler(common_info_window *handler) {
    if (!g_window_info_handlers) {
        g_window_info_handlers = new svector<common_info_window *, 10>();
    }

    auto it = std::find(g_window_info_handlers->begin(), g_window_info_handlers->end(), handler);
    if (it == g_window_info_handlers->end()) {
        g_window_info_handlers->push_back(handler);
    }
}

common_info_window::common_info_window() {
}

void common_info_window::window_info_background(object_info &c) {
    ; // nothing

    update_buttons(c);
}

void common_info_window::update_buttons(object_info &c) {
    auto &ui = *c.ui;

    vec2i bgsize = ui["background"].pxsize();
    ui["button_help"].pos.y = bgsize.y - 40;
    ui["button_help"].onclick([&c] {
        if (c.help_id > 0) {
            window_message_dialog_show(c.help_id, -1, window_city_draw_all);
        } else {
            window_message_dialog_show(MESSAGE_DIALOG_HELP, -1, window_city_draw_all);
        }
        window_invalidate();
    });

    ui["button_close"].pos.y = bgsize.y - 40;
    ui["button_close"].onclick([&c] {
        if (c.storage_show_special_orders) {
            c.storage_show_special_orders = 0;
            storage_settings_backup_reset();
            window_invalidate();
        } else {
            window_city_show();
        }
    });

    auto first_advisor = ui["first_advisor"].dcast_image_button();
    if (first_advisor) {
        first_advisor->enabled = c.go_to_advisor.first &&is_advisor_available(c.go_to_advisor.first);
        first_advisor->img_desc.offset = (c.go_to_advisor.left_a - 1) * 3;
        first_advisor->pos.y = bgsize.y - 40;
        first_advisor->onclick([&c] {
            window_advisors_show_advisor(c.go_to_advisor.first);
        });
    }

    auto second_advisor = ui["second_advisor"].dcast_image_button();
    if (second_advisor) {
        second_advisor->enabled = c.go_to_advisor.left_a && is_advisor_available(c.go_to_advisor.left_a);
        second_advisor->img_desc.offset = (c.go_to_advisor.left_a - 1) * 3;
        second_advisor->pos.y = bgsize.y - 40;
        second_advisor->onclick([&c] {
            window_advisors_show_advisor(c.go_to_advisor.left_a);
        });
    }

    auto third_advisor = ui["third_advisor"].dcast_image_button();
    if (third_advisor) {
        third_advisor->enabled = c.go_to_advisor.left_b && is_advisor_available(c.go_to_advisor.left_b);
        third_advisor->img_desc.offset = (c.go_to_advisor.left_b - 1) * 3;
        third_advisor->pos.y = bgsize.y - 40;
        third_advisor->onclick([&c] {
            window_advisors_show_advisor(c.go_to_advisor.left_b);
        });
    }
}

void common_info_window::draw_tooltip(tooltip_context *c) {
    std::pair<int, int> tooltip = get_tooltip(g_object_info);
    int button_id = ui::button_hover(mouse_get());
    if (button_id > 0 && tooltip.first < 0) {
        tooltip = ui::button(button_id - 1)._tooltip;
    }

    if (tooltip.first > 0 || tooltip.second > 0) {
        c->type = TOOLTIP_BUTTON;
        c->text_id = tooltip.second;
        if (tooltip.first) {
            c->text_group = tooltip.first;
        }
        window_invalidate();
    }
}
