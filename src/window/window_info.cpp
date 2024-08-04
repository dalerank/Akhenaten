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
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "dev/debug.h"

#include <functional>
#include <utility>
#include <mutex>

object_info g_object_info;
svector<common_info_window *, 10> *g_window_info_handlers = nullptr;

struct empty_info_window : public common_info_window {
    using widget::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual void draw_background(object_info &c) override {
        //outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
        lang_text_draw_centered(70, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    }

    virtual int handle_mouse(const mouse *m, object_info &c) override {
        return 0;
    }

    virtual void draw_foreground(object_info &c) override {
        draw();
    }

    virtual bool check(object_info &c) override {
        return false;
    }
};

empty_info_window g_empty_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_info_window);
void config_load_info_window() {
    g_empty_info_window.load("empty_info_window");
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

    context.handler = nullptr;
    for (auto &handler : *g_window_info_handlers) {
        if (handler->check(context)) {
            context.handler = handler;
            break;
        }
    }

    if (!context.handler) {
        context.handler = &g_empty_info_window;
    }

    // dialog size
    int bgsizey[] = {16, 16, 18, 19, 14, 23, 16};
    context.bgsize = {29, bgsizey[context.handler->get_height_id(context)]};

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
    context.handler->draw_background(context);
}

static void buiding_info_draw_foreground() {
    ui::begin_widget(g_object_info.offset);
    auto &context = g_object_info;

    context.handler->draw_foreground(context);

    // general buttons
    int y_offset = (context.storage_show_special_orders) ? context.subwnd_y_offset : 0;
    int height_blocks = (context.storage_show_special_orders) ? context.height_blocks_submenu : context.bgsize.y;

    ui::img_button(GROUP_CONTEXT_ICONS, vec2i(14, y_offset + 16 * height_blocks - 40), {28, 28}, {0})
               .onclick([&context] (int, int) {
                    if (context.help_id > 0) {
                        window_message_dialog_show(context.help_id, -1, window_city_draw_all);
                    } else {
                        window_message_dialog_show(MESSAGE_DIALOG_HELP, -1, window_city_draw_all);
                    }
                    window_invalidate();
               });

    ui::img_button(GROUP_CONTEXT_ICONS, vec2i(16 * context.bgsize.x - 40, y_offset + 16 * height_blocks - 40), {28, 28}, {4})
               .onclick([&context] (int, int) {
                    if (context.storage_show_special_orders) {
                        context.storage_show_special_orders = 0;
                        storage_settings_backup_reset();
                        window_invalidate();
                    } else {
                        window_city_show();
                    }
               });

    if (!context.storage_show_special_orders && context.go_to_advisor.first && is_advisor_available(context.go_to_advisor.first)) {
        int img_offset = (context.go_to_advisor.left_a - 1) * 3;
        ui::img_button(GROUP_MESSAGE_ADVISOR_BUTTONS, vec2i(40, 16 * context.bgsize.y - 40), {28, 28}, {img_offset})
               .onclick([&context] (int, int) {
                   window_advisors_show_advisor(context.go_to_advisor.first);
               });
    }

    if (!context.storage_show_special_orders && context.go_to_advisor.left_a && is_advisor_available(context.go_to_advisor.left_a)) {
        int img_offset = (context.go_to_advisor.left_a - 1) * 3;
        ui::img_button(GROUP_MESSAGE_ADVISOR_BUTTONS, vec2i(40, 16 * context.bgsize.y - 40), {28, 28}, {img_offset})
               .onclick([&context] (int, int) {
                   window_advisors_show_advisor(context.go_to_advisor.left_a);
               });
    }

    if (!context.storage_show_special_orders && context.go_to_advisor.left_b && is_advisor_available(context.go_to_advisor.left_b)) {
        int img_offset = (context.go_to_advisor.left_b - 1) * 3;
        ui::img_button(GROUP_MESSAGE_ADVISOR_BUTTONS, vec2i(65, 16 * context.bgsize.y - 40), {28, 28}, {img_offset})
               .onclick([&context] (int, int) {
                   window_advisors_show_advisor(context.go_to_advisor.left_b);
               });
    }

    if (!context.storage_show_special_orders && context.figure.draw_debug_path) {
        figure* f = figure_get(context.figure.figure_ids[0]);
        pcstr label = (f->draw_debug_mode ? "P" : "p");
        ui::button(label, {400, 3 + 16 * context.bgsize.y - 40}, {20, 20})
              .onclick([&context, f] (int, int) {
                  f->draw_debug_mode = f->draw_debug_mode ? 0 :FIGURE_DRAW_DEBUG_ROUTING;
                  window_invalidate();
              });
    }

    if (!context.storage_show_special_orders && context.show_overlay != OVERLAY_NONE) {
        pcstr label = (game.current_overlay != context.show_overlay ? "v" : "V");
        ui::button(label, {375, 3 + 16 * context.bgsize.y - 40}, {20, 20})
             .onclick([&context] (int, int) {
                if (game.current_overlay != context.show_overlay) {
                    game_state_set_overlay((e_overlay)context.show_overlay);
                } else {
                    game_state_reset_overlay();
                }
                window_invalidate();
             });
    }
}

static void buiding_info_handle_input(const mouse* m, const hotkeys* h) {
    auto &context = g_object_info;

    bool button_id = ui::handle_mouse(m);
  
    if (!button_id) {
        int btn_id = context.handler->handle_mouse(m, context);
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
        if (!context.handler) {
            return;
        }

        context.handler->draw_tooltip(c);
    };

    auto draw_refresh = [] () {
        auto &context = g_object_info;
        if (!context.handler) {
            return;
        }

        context.handler->draw_background(context);
    };

    static window_type window = {
        WINDOW_BUILDING_INFO,
        buiding_info_draw_background,
        buiding_info_draw_foreground,
        buiding_info_handle_input,
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

common_info_window::common_info_window() {
    if (!g_window_info_handlers) {
        g_window_info_handlers = new svector<common_info_window *, 10>();
    }

    auto it = std::find(g_window_info_handlers->begin(), g_window_info_handlers->end(), this);
    if (it == g_window_info_handlers->end()) {
        g_window_info_handlers->push_back(this);
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
