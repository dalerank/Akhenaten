#include "widget_top_menu_game.h"

#include "game/game.h"

#include "graphics/elements/menu.h"
#include "graphics/elements/ui.h"
#include "graphics/elements/ui_js.h"
#include "graphics/screenshot.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "city/constants.h"
#include "city/city.h"
#include "game/game_events.h"
#include "core/profiler.h"
#include "core/core_utility.h"
#include "game/game_config.h"
#include "game/settings.h"
#include "game/cheats.h"
#include "game/state.h"
#include "game/undo.h"
#include "window/file_dialog.h"
#include "window/message_dialog.h"
#include "io/gamestate/boilerplate.h"
#include "building/construction/build_planner.h"
#include "game/system.h"
#include "window/display_options.h"
#include "window/window_city.h"
#include "window/difficulty_options.h"
#include "window/window_features.h"
#include "window/window_dynasty_menu.h"
#include "window/hotkey_config.h"
#include "window/main_menu.h"
#include "window/popup_dialog.h"
#include "window/speed_options.h"
#include "window/sound_options.h"
#include "widget/widget_sidebar.h"
#include "widget/widget_city.h"
#include "window/console.h"
#include "dev/debug.h"

#include "js/js_game.h"
#include "js/js_struct.h"

static void button_rotate_left(int param1, int param2);
static void button_rotate_reset(int param1, int param2);
static void button_rotate_right(int param1, int param2);

struct top_menu_widget_init { vec2i pos; };
struct top_menu_widget_draw { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(top_menu_widget_init, pos);
ANK_REGISTER_STRUCT_WRITER(top_menu_widget_draw, pos);

top_menu_widget_t ANK_VARIABLE(top_menu_widget);

int orientation_button_state = 0;
int orientation_button_pressed = 0;

static generic_button orientation_buttons_ph[] = {
    {12, 0, 36 - 24, 21, button_rotate_reset, button_none, 0, 0},
    {0, 0, 12, 21, button_rotate_left, button_none, 0, 0},
    {36 - 12, 0, 12, 21, button_rotate_right, button_none, 0, 0},
};

void top_menu_widget_t::on_mission_start() {
    init();
}

void top_menu_widget_t::init() {
    ui["date"].onrclick([] {
        window_message_dialog_show("message_game_control_date_display", -1, window_city_draw_all);
    });

    ui["population"].onrclick([] {
        window_message_dialog_show("message_game_control_population_display", -1, window_city_draw_all);
    });

    ui["funds"].onrclick([] {
        window_message_dialog_show("message_game_control_money_display_window", -1, window_city_draw_all);
    });

    events::subscribe([this] (event_population_changed ev) { states.population = ev.value; });
}

void top_menu_widget_t::menu_item_update(pcstr header, int item, pcstr text) {
    auto menu = headers[header].dcast_menu_header();
    if (!menu) {
        return;
    }

    menu->item(item).text = text;
}

void top_menu_widget_t::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    svector<ui::emenu_header *, 16> headers_elms;
    for (auto &header : headers.elements) {
        auto impl = header->dcast_menu_header();
        if (impl) {
            headers_elms.push_back(impl);
        }
    }

    for (auto header : headers_elms) {
        header->load_items(arch, header->id.c_str(), headers.elements);
    }
}

static void button_rotate_reset(int param1, int param2) {
    events::emit(event_rotate_map_reset{ 0 });
}

static void button_rotate_left(int param1, int param2) {
    events::emit(event_rotate_map{ HOTKEY_ROTATE_MAP_LEFT });
}

static void button_rotate_right(int param1, int param2) {
    events::emit(event_rotate_map{ HOTKEY_ROTATE_MAP_RIGHT });
}

void top_menu_widget_t::draw_elements_impl() {
    vec2i cur_offset = offset;
    const e_font hightlight_font = !!game_features::gameui_highlight_top_menu_hover ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT;
    for (auto &it : headers.elements) {
        ui::emenu_header *header = it->dcast_menu_header();

        if (!header) {
            continue;
        }

        const bool is_hovered = (it->id == focus_menu_id);

        header->impl.x_start = cur_offset.x;
        header->font(is_hovered ? hightlight_font : FONT_NORMAL_BLACK_ON_LIGHT);
        header->pos = vec2i{cur_offset.x, offset.y};
        header->draw(UiFlags_None);

        if (is_hovered) {
            ui::set_tooltip(header->tooltip());
        }

        cur_offset.x += header->text_width();
        header->impl.x_end = cur_offset.x;
        cur_offset.x += spacing;
    }
}

xstring top_menu_widget_t::get_selected_header(const mouse* m) {
    for (auto &it : headers.elements) {
        ui::emenu_header *header = it->dcast_menu_header();

        if (!header) {
            continue;
        }

        if (header->impl.x_start <= m->x && header->impl.x_end > m->x && offset.y <= m->y && offset.y + 12 > m->y) {
            return header->id;
        }
    }
    return {};
}

xstring top_menu_widget_t::bar_handle_mouse(const mouse* m) {
    focus_menu_id = get_selected_header(m);
    return get_selected_header(m);
}

void top_menu_widget_t::calculate_menu_dimensions(menu_header& menu) {
    int max_width = 0;
    int height_pixels = item_height;
    for (const auto &item: menu.items) {
        if (item.hidden) {
            continue;
        }

        int width_pixels = lang_text_get_width(item.text.c_str(), FONT_NORMAL_BLACK_ON_LIGHT);
        max_width = std::max(max_width, width_pixels);

        height_pixels += item_height;
    }
    int blocks = (max_width + 8) / 16 + 1; // 1 block padding
    menu.calculated_width_blocks = blocks < 10 ? 10 : blocks;
    menu.calculated_height_blocks = height_pixels / 16;
}

void top_menu_widget_t::sub_menu_draw_text(const xstring header, const xstring focus_item_id) {
    auto &impl = ((ui::emenu_header *)&headers[header])->impl;

    if (impl.calculated_width_blocks == 0 || impl.calculated_height_blocks == 0) {
        calculate_menu_dimensions(impl);
    }

    unbordered_panel_draw(impl.x_start, TOP_MENU_HEIGHT, impl.calculated_width_blocks, impl.calculated_height_blocks);
    int y_offset = TOP_MENU_HEIGHT + offset.y * 2;
    for (const auto &item: impl.items) {
        if (item.hidden) {
            continue;
        }
        // Set color/font on the menu item mouse hover
        pcstr text = item.text.c_str();
        if (item._textfn) {
            text = item._textfn(item.parameter);
        }

        lang_text_draw(text, vec2i{impl.x_start + 8, y_offset}, item.id == focus_item_id ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT);
        y_offset += item_height;
    }
}

xstring top_menu_widget_t::get_subitem(const mouse* m, menu_header &menu) {
    int y_offset = TOP_MENU_HEIGHT + offset.y * 2;

    for (const auto &item: menu.items) {
        if (item.hidden) {
            continue;
        }

        if (menu.x_start <= m->x && menu.x_start + 16 * menu.calculated_width_blocks > m->x && y_offset - 2 <= m->y && y_offset + 19 > m->y) {
            return item.id;
        }

        y_offset += item_height;
    }

    return {};
}

xstring top_menu_widget_t::menu_handle_mouse(const mouse* m, menu_header* menu, xstring& focus_item_id) {
    if (!menu) {
        return "";
    }

    xstring item_id = get_subitem(m, *menu);
    focus_item_id = item_id;

    if (!item_id) {
        return "";
    }

    if (m->left.went_up) {
        auto it = std::find_if(menu->items.begin(), menu->items.end(), [&item_id] (auto &it) { return it.id == item_id; });
        if (it != menu->items.end()) {
            if (it->_onclick) {
                it->_onclick(it->parameter);
            } else if (menu->_onclick) {
                menu->_onclick(*it);
            }
        }
    }

    return item_id;
}

void top_menu_widget_t::header_update_text(pcstr header, pcstr text) {
    auto &impl = ((ui::emenu_header *)&headers[header])->impl;

    headers[header].text(text);
    if (impl.calculated_width_blocks == 0) {
        return;
    }

    int item_width = lang_text_get_width(impl.text.c_str(), FONT_NORMAL_BLACK_ON_LIGHT);
    int blocks = (item_width + 8) / 16 + 1;
    if (blocks > impl.calculated_width_blocks) {
        impl.calculated_width_blocks = blocks;
    }
}

std::pair<bstring64, bstring64> split_string(pcstr input) {
    std::pair<bstring64, bstring64> result;
    pcstr pos = strstr(input, "/");
    if (pos) {
        result.first.ncat(input, (pos - input));
        result.second.cat(pos + 1);
    }

    return result;
}

void top_menu_widget_t::item_update_text(pcstr path, pcstr text) {
    auto pair = split_string(path);
    auto header = headers[pair.first].dcast_menu_header();
    auto &item = header->item(pair.second);
    item.text = text;
}

void widget_top_menu_clear_state() {
    auto& data = top_menu_widget;

    data.open_sub_menu = "";
    data.focus_menu_id = "";
    data.focus_sub_menu_id = "";
}

void top_menu_widget_t::sub_menu_init() {
    headers.event(top_menu_widget_init{ pos });
}

void top_menu_widget_t::sub_menu_draw_background(int flags) {
    window_city_draw_panels();
    window_city_draw();
    widget_sidebar_city_draw_foreground();
}

void top_menu_widget_t::sub_menu_draw_foreground(int) {
    if (!open_sub_menu) {
        return;
    }

    sub_menu_draw_text(open_sub_menu, focus_sub_menu_id);
}

void widget_sub_menu_show() {
    static window_type window = {
        WINDOW_TOP_MENU,
        [] (int flags) { top_menu_widget.sub_menu_draw_background(flags); },
        [] (int flags) { top_menu_widget.sub_menu_draw_foreground(flags); },
        widget_top_menu_handle_input
    };
    top_menu_widget.sub_menu_init();
    window_show(&window);
}

void top_menu_widget_t::draw_background_impl() {
    painter ctx = game.painter();

    int img_id = background.tid();
    const image_t *img = image_get(img_id);
    const int block_width = img->width;
    assert(block_width > 0);

    for (int x = -(screen_width() - widget_sidebar_city_offset_x()); x < screen_width(); x += (block_width - sidebar_offset)) {
        ctx.img_generic(img_id, { x, 0 });
    }

    ctx.img_generic(img_id, { widget_sidebar_city_offset_x() - block_width + sidebar_offset, 0 });
}

void top_menu_widget_t::draw_rotate_buttons() {
    // Orientation icon
    painter ctx = game.painter();
    if (orientation_button_pressed) {
        ctx.img_generic(image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state + 3, { offset_rotate, 0 });
        orientation_button_pressed--;
    } else {
        ctx.img_generic(image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state, { offset_rotate, 0 });
    }
}

void top_menu_widget_t::draw_foreground(UiFlags flags) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Topmenu");

    draw_background_impl();
    draw_elements_impl();
    draw_rotate_buttons();

    int s_width = screen_width();

    offset_rotate = s_width - offset_rotate_basic;

    // "ui" is the Debens, Population and Date texts
    ui["population"].text_var("%s %d", ui::str(6, 1), states.population);
    ui.event(top_menu_widget_draw{ pos });
    ui.begin_widget({ 0, 0 });
    ui.draw();
    ui.end_widget();
}

void widget_top_menu_draw() {
    top_menu_widget.draw_foreground(0);
}

bool top_menu_widget_t::handle_input_submenu(const mouse* m, const hotkeys* h) {
    if (m->right.went_up || h->escape_pressed) {
        widget_top_menu_clear_state();
        window_go_back();
        return true;
    }

    xstring menu_id = bar_handle_mouse(m);
    if (!!menu_id && menu_id != open_sub_menu) {
        open_sub_menu = menu_id;
    }

    auto *header = headers[open_sub_menu].dcast_menu_header();
    if (!menu_handle_mouse(m, header ? &header->impl : nullptr, focus_sub_menu_id)) {
        if (m->left.went_up) {
            widget_top_menu_clear_state();
            window_go_back();
            return true;
        }
    }
    return false;
}

int top_menu_widget_t::ui_handle_mouse(const mouse *m) {
    autoconfig_window::ui_handle_mouse(m);

    xstring menu_id = bar_handle_mouse(m);
    if (!!menu_id && m->left.went_up) {
        open_sub_menu = menu_id;
        widget_sub_menu_show();
        return 0;
    }

    return 0;
}

void widget_top_menu_handle_input(const mouse* m, const hotkeys* h) {
    if (g_screen_city.capture_input) {
        return;
    }

    int button_id = 0;
    int handled = false;

    handled = generic_buttons_handle_mouse(m, { top_menu_widget.offset_rotate, 0}, orientation_buttons_ph, 3, &button_id);
    if (button_id) {
        orientation_button_state = button_id;
        if (handled)
            orientation_button_pressed = 5;
    } else {
        orientation_button_state = 0;
    }

    if (button_id) { /**/ }
    else if (!!top_menu_widget.open_sub_menu) { top_menu_widget.handle_input_submenu(m, h); }
    else { top_menu_widget.ui_handle_mouse(m); }
}