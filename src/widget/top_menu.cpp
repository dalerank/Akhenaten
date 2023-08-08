#include "top_menu.h"

#include "building/construction/build_planner.h"
#include "city/finance.h"
#include "city/population.h"
#include "dev/debug.h"
#include "game/cheats.h"
#include "game/mission.h"
#include "game/orientation.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/system.h"
#include "game/time.h"
#include "game/undo.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/menu.h"
#include "graphics/elements/panel.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "io/gamestate/boilerplate.h"
#include "io/manager.h"
#include "scenario/property.h"
#include "widget/city.h"
#include "window/advisors.h"
#include "window/city.h"
#include "window/difficulty_options.h"
#include "window/display_options.h"
#include "window/file_dialog.h"
#include "window/game_menu.h"
#include "window/main_menu.h"
#include "window/message_dialog.h"
#include "window/popup_dialog.h"
#include "window/sound_options.h"
#include "window/speed_options.h"
#include "window/hotkey_config.h"
#include "window/config.h"

#include "core/core_utility.h"
#include "core/span.hpp"

enum E_INFO { INFO_NONE = 0, INFO_FUNDS = 1, INFO_POPULATION = 2, INFO_DATE = 3 };

enum e_menu_index { INDEX_OPTIONS = 1, INDEX_HELP = 2, INDEX_ADVISORS = 3, INDEX_DEBUG = 4 };

static void menu_file_new_game(int param);
static void menu_file_replay_map(int param);
static void menu_file_load_game(int param);
static void menu_file_save_game(int param);
static void menu_file_delete_game(int param);
static void menu_file_exit_city(int param);

static void menu_options_display(int param);
static void menu_options_sound(int param);
static void menu_options_speed(int param);
static void menu_options_difficulty(int param);
static void menu_options_autosave(int param);
static void menu_options_hotkeys(int param);
static void menu_options_change_enh(int param);

static void menu_help_help(int param);
static void menu_help_mouse_help(int param);
static void menu_help_warnings(int param);
static void menu_help_about(int param);

static void menu_advisors_go_to(int advisor);
static void menu_debug_change_opt(int opt);
static void menu_debug_show_console(int param);
static void menu_update_text(menu_bar_item& menu, int index, int text_number);
static void menu_update_text(menu_bar_item& menu, int index, const char* text);

static menu_item menu_file[] = {
  {1, 1, menu_file_new_game, 0},
  {1, 2, menu_file_replay_map, 0},
  {1, 3, menu_file_load_game, 0},
  {1, 4, menu_file_save_game, 0},
  {1, 6, menu_file_delete_game, 0},
  {1, 5, menu_file_exit_city, 0},
};

static menu_item menu_options[] = {
  {2, 1, menu_options_display, 0},
  {2, 2, menu_options_sound, 0},
  {2, 3, menu_options_speed, 0},
  {2, 6, menu_options_difficulty, 0},
  {19, 51, menu_options_autosave, 0},
  {2, 1, menu_options_hotkeys, 0, false, "Hotkeys options"},
  {2, 1, menu_options_change_enh, 0, false, "Enhanced options"},
};

static menu_item menu_help[] = {
  {3, 1, menu_help_help, 0},
  {3, 2, menu_help_mouse_help, 0},
  {3, 5, menu_help_warnings, 0},
  {3, 7, menu_help_about, 0},
};

static menu_item menu_advisors[] = {
  {4, 1, menu_advisors_go_to, ADVISOR_LABOR},
  {4, 2, menu_advisors_go_to, ADVISOR_MILITARY},
  {4, 3, menu_advisors_go_to, ADVISOR_IMPERIAL},
  {4, 4, menu_advisors_go_to, ADVISOR_RATINGS},
  {4, 5, menu_advisors_go_to, ADVISOR_TRADE},
  {4, 6, menu_advisors_go_to, ADVISOR_POPULATION},
  {4, 7, menu_advisors_go_to, ADVISOR_HEALTH},
  {4, 8, menu_advisors_go_to, ADVISOR_EDUCATION},
  {4, 9, menu_advisors_go_to, ADVISOR_ENTERTAINMENT},
  {4, 10, menu_advisors_go_to, ADVISOR_RELIGION},
  {4, 11, menu_advisors_go_to, ADVISOR_FINANCIAL},
  {4, 12, menu_advisors_go_to, ADVISOR_CHIEF},
};

static menu_item menu_debug[] = {
  {5, 1, menu_debug_change_opt, e_debug_show_pages},
  {5, 2, menu_debug_change_opt, e_debug_show_game_time},
  {5, 3, menu_debug_change_opt, e_debug_show_build_planner},
  {5, 4, menu_debug_change_opt, e_debug_show_religion},
  {5, 5, menu_debug_change_opt, e_debug_show_tutorial},
  {5, 6, menu_debug_change_opt, e_debug_show_floods},
  {5, 7, menu_debug_change_opt, e_debug_show_camera},
  {5, 8, menu_debug_change_opt, e_debug_show_tile_cache},
  {5, 9, menu_debug_show_console, 0, false, "show console"},
};

menu_bar_item g_top_menu[] = {
  {1, menu_file, std::size(menu_file)},
  {2, menu_options, std::size(menu_options)},
  {3, menu_help, std::size(menu_help)},
  {4, menu_advisors, std::size(menu_advisors)},
  {5, menu_debug, std::size(menu_debug), "Debug"},
};

static void menu_debug_opt_text(int opt, bool v) {
    static const char* debug_text[][2] = {
      {"show_pages ON", "show_pages OFF"},
      {"show_game_time ON", "show_game_time OFF"},
      {"show_build_planner ON", "show_build_planner OFF"},
      {"show_religion ON", "show_religion OFF"},
      {"show_tutorial ON", "show_tutorial OFF"},
      {"show_floods ON", "show_floods OFF"},
      {"show_camera ON", "show_camera OFF"},
      {"show_tile_cache ON", "show_tile_cache OFF"},
    };
    menu_update_text(g_top_menu[INDEX_DEBUG], opt, debug_text[opt][v ? 0 : 1]);
}

static void menu_debug_change_opt(int opt) {
    g_debug_show_opts[opt] = !g_debug_show_opts[opt];
    menu_debug_opt_text(opt, g_debug_show_opts[opt]);
}

static void button_rotate_reset(int param1, int param2) {
    game_orientation_rotate_north();
    window_invalidate();
}
static void button_rotate_left(int param1, int param2) {
    game_orientation_rotate_left();
    window_invalidate();
}
static void button_rotate_right(int param1, int param2) {
    game_orientation_rotate_right();
    window_invalidate();
}

static image_button orientation_button[] = {
  {0, 0, 36, 21, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 72, button_rotate_left, button_none, 0, 0, 1},
};

static generic_button orientation_buttons_ph[] = {
  {12, 0, 36 - 24, 21, button_rotate_reset, button_none, 0, 0},
  {0, 0, 12, 21, button_rotate_left, button_none, 0, 0},
  {36 - 12, 0, 12, 21, button_rotate_right, button_none, 0, 0},
};

struct top_menu_data_t {
    int offset_funds;
    int offset_population;
    int offset_date;
    int offset_rotate;

    int open_sub_menu;
    int focus_menu_id;
    int focus_sub_menu_id;
};

top_menu_data_t g_top_menu_data;

#define TOP_MENU_BASE_X_OFFSET 10
#define MENU_BASE_TEXT_Y_OFFSET 6
#define MENU_ITEM_HEIGHT 20

void menu_bar_draw(const std::span<menu_bar_item>& items) {
    short x_offset = TOP_MENU_BASE_X_OFFSET;
    for (auto& item : items) {
        item.x_start = x_offset;
        int text_length
          = item.text_raw
              ? lang_text_draw(item.text_raw, x_offset, MENU_BASE_TEXT_Y_OFFSET, FONT_NORMAL_BLACK_ON_LIGHT)
              : lang_text_draw(item.text_group, 0, x_offset, MENU_BASE_TEXT_Y_OFFSET, FONT_NORMAL_BLACK_ON_LIGHT);
        x_offset += text_length;
        item.x_end = x_offset;
        x_offset += 32; // spacing
    }
}

static int get_menu_bar_item(const mouse* m, const std::span<menu_bar_item>& items) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i].x_start <= m->x && items[i].x_end > m->x && MENU_BASE_TEXT_Y_OFFSET <= m->y
            && MENU_BASE_TEXT_Y_OFFSET + 12 > m->y) {
            return i + 1;
        }
    }
    return 0;
}

static int menu_bar_handle_mouse(const mouse* m, const std::span<menu_bar_item>& items, int* focus_menu_id) {
    int menu_id = get_menu_bar_item(m, items);
    if (focus_menu_id)
        *focus_menu_id = menu_id;

    return menu_id;
}

static void menu_debug_show_console(int param) {
    game_cheat_console(true);
}

static void calculate_menu_dimensions(menu_bar_item& menu) {
    int max_width = 0;
    int height_pixels = MENU_ITEM_HEIGHT;
    for (int i = 0; i < menu.num_items; i++) {
        menu_item* sub = &menu.items[i];
        if (sub->hidden)
            continue;

        int width_pixels = sub->text_raw
                             ? lang_text_get_width(sub->text_raw, FONT_NORMAL_BLACK_ON_LIGHT)
                             : lang_text_get_width(sub->text_group, sub->text_number, FONT_NORMAL_BLACK_ON_LIGHT);

        if (width_pixels > max_width)
            max_width = width_pixels;

        height_pixels += MENU_ITEM_HEIGHT;
    }
    int blocks = (max_width + 8) / 16 + 1; // 1 block padding
    menu.calculated_width_blocks = blocks < 10 ? 10 : blocks;
    menu.calculated_height_blocks = height_pixels / 16;
}
void menu_draw(menu_bar_item& menu, int focus_item_id) {
    if (menu.calculated_width_blocks == 0 || menu.calculated_height_blocks == 0)
        calculate_menu_dimensions(menu);

    unbordered_panel_draw(menu.x_start, TOP_MENU_HEIGHT, menu.calculated_width_blocks, menu.calculated_height_blocks);
    int y_offset = TOP_MENU_HEIGHT + MENU_BASE_TEXT_Y_OFFSET * 2;
    for (int i = 0; i < menu.num_items; i++) {
        menu_item* sub = &menu.items[i];
        if (sub->hidden)
            continue;

        // Set color/font on the menu item mouse hover
        if (i == focus_item_id - 1) {
            if (GAME_ENV == ENGINE_ENV_C3) {
                graphics_fill_rect(menu.x_start, y_offset - 4, 16 * menu.calculated_width_blocks, 20, COLOR_BLACK);
                lang_text_draw_colored(
                  sub->text_group, sub->text_number, menu.x_start + 8, y_offset, FONT_SMALL_PLAIN, COLOR_FONT_ORANGE);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                sub->text_raw
                  ? lang_text_draw(sub->text_raw, menu.x_start + 8, y_offset, FONT_NORMAL_YELLOW)
                  : lang_text_draw(sub->text_group, sub->text_number, menu.x_start + 8, y_offset, FONT_NORMAL_YELLOW);
            }
        } else {
            sub->text_raw ? lang_text_draw(sub->text_raw, menu.x_start + 8, y_offset, FONT_NORMAL_BLACK_ON_LIGHT)
                          : lang_text_draw(
                            sub->text_group, sub->text_number, menu.x_start + 8, y_offset, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        y_offset += MENU_ITEM_HEIGHT;
    }
}
static int get_menu_item(const mouse* m, menu_bar_item* menu) {
    int y_offset = TOP_MENU_HEIGHT + MENU_BASE_TEXT_Y_OFFSET * 2;
    for (int i = 0; i < menu->num_items; i++) {
        if (menu->items[i].hidden)
            continue;

        if (menu->x_start <= m->x && menu->x_start + 16 * menu->calculated_width_blocks > m->x && y_offset - 2 <= m->y
            && y_offset + 19 > m->y) {
            return i + 1;
        }
        y_offset += MENU_ITEM_HEIGHT;
    }
    return 0;
}
int menu_handle_mouse(const mouse* m, menu_bar_item* menu, int* focus_item_id) {
    int item_id = get_menu_item(m, menu);
    if (focus_item_id)
        *focus_item_id = item_id;

    if (!item_id)
        return 0;

    if (m->left.went_up) {
        menu_item* item = &menu->items[item_id - 1];
        item->left_click_handler(item->parameter);
    }
    return item_id;
}

void menu_update_text(menu_bar_item& menu, int index, const char* text) {
    menu.items[index].text_number = 0;
    menu.items[index].text_group = 0;
    menu.items[index].text_raw = text;
    if (menu.calculated_width_blocks == 0)
        return;

    int item_width = lang_text_get_width(menu.items[index].text_raw, FONT_NORMAL_BLACK_ON_LIGHT);
    int blocks = (item_width + 8) / 16 + 1;
    if (blocks > menu.calculated_width_blocks) {
        menu.calculated_width_blocks = blocks;
    }
}

void menu_update_text(menu_bar_item& menu, int index, int text_number) {
    menu.items[index].text_number = text_number;
    if (menu.calculated_width_blocks == 0)
        return;

    int item_width = lang_text_get_width(menu.items[index].text_group, text_number, FONT_NORMAL_BLACK_ON_LIGHT);
    int blocks = (item_width + 8) / 16 + 1;
    if (blocks > menu.calculated_width_blocks) {
        menu.calculated_width_blocks = blocks;
    }
}

struct top_menu_drawn_t {
    int population;
    int treasury;
    int month;
};

top_menu_drawn_t g_top_menu_drawn;

void clear_state(void) {
    auto& data = g_top_menu_data;

    data.open_sub_menu = 0;
    data.focus_menu_id = 0;
    data.focus_sub_menu_id = 0;
}

void widget_top_menu_clear_state() {
    clear_state();
}

static void set_text_for_autosave(void) {
    menu_update_text(g_top_menu[INDEX_OPTIONS], 4, setting_monthly_autosave() ? 51 : 52);
}
static void set_text_for_tooltips(void) {
    int new_text;
    switch (setting_tooltips()) {
    case TOOLTIPS_NONE:
        new_text = 2;
        break;
    case TOOLTIPS_SOME:
        new_text = 3;
        break;
    case TOOLTIPS_FULL:
        new_text = 4;
        break;
    default:
        return;
    }
    menu_update_text(g_top_menu[INDEX_HELP], 1, new_text);
}
static void set_text_for_warnings(void) {
    menu_update_text(g_top_menu[INDEX_HELP], 2, setting_warnings() ? 6 : 5);
}
static void set_text_for_debug() {
    for (int i = 0; i < e_debug_opt_size; ++i) {
        menu_debug_opt_text(i, g_debug_show_opts[i]);
    }
}

static void init(void) {
    g_top_menu[INDEX_OPTIONS].items[0].hidden = system_is_fullscreen_only();

    set_text_for_autosave();
    set_text_for_tooltips();
    set_text_for_warnings();
    set_text_for_debug();
}

static void draw_background(void) {
    window_city_draw_panels();
    window_city_draw();
}
static void draw_foreground(void) {
    auto& data = g_top_menu_data;
    if (!data.open_sub_menu)
        return;

    menu_draw(g_top_menu[data.open_sub_menu - 1], data.focus_sub_menu_id);
}

static void handle_input(const mouse* m, const hotkeys* h) {
    widget_top_menu_handle_input(m, h);
}

static void top_menu_window_show(void) {
    window_type window = {WINDOW_TOP_MENU, draw_background, draw_foreground, handle_input};
    init();
    window_show(&window);
}

int orientation_button_state = 0;
int orientation_button_pressed = 0;

static void refresh_background(void) {
    int block_width = 24;
    int image_base = image_id_from_group(GROUP_TOP_MENU_SIDEBAR);
    int s_width = screen_width();

    if (GAME_ENV == ENGINE_ENV_C3) {
        for (int i = 0; i * block_width < s_width; i++)
            ImageDraw::img_generic(image_base + i % 8, i * block_width, 0);

        // black panels for funds/pop/time
        if (s_width < 800)
            ImageDraw::img_generic(image_base + 14, 336, 0);
        else if (s_width < 1024) {
            ImageDraw::img_generic(image_base + 14, 336, 0);
            ImageDraw::img_generic(image_base + 14, 456, 0);
            ImageDraw::img_generic(image_base + 14, 648, 0);
        } else {
            ImageDraw::img_generic(image_base + 14, 480, 0);
            ImageDraw::img_generic(image_base + 14, 624, 0);
            ImageDraw::img_generic(image_base + 14, 840, 0);
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        block_width = 96;
        int s_end = s_width - 1000 - 24 + city_view_is_sidebar_collapsed() * (162 - 18);
        int s_start = s_end - ceil((float)s_end / (float)block_width) * block_width;

        for (int i = 0; s_start + i * block_width < s_end; i++) {
            ImageDraw::img_generic(image_id_from_group(GROUP_SIDE_PANEL) + 8, s_start + (i * block_width), 0);
        }

        ImageDraw::img_generic(image_id_from_group(GROUP_SIDE_PANEL) + 8, s_end, 0);
    }
}

void widget_top_menu_draw(int force) {
    auto& data = g_top_menu_data;
    if (!force && g_top_menu_drawn.treasury == city_finance_treasury()
        && g_top_menu_drawn.population == city_population() && g_top_menu_drawn.month == game_time_month()) {
        return;
    }

    refresh_background();
    menu_bar_draw(make_span(g_top_menu));

    color_t treasure_color = COLOR_WHITE;
    int treasury = city_finance_treasury();

    if (treasury < 0) {
        treasure_color = COLOR_FONT_RED;
    }

    font_t treasure_font = (treasury >= 0 ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW);
    int s_width = screen_width();

    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        data.offset_funds = s_width - 540;
        data.offset_population = s_width - 400;
        data.offset_date = s_width - 150; // 135
        data.offset_rotate = data.offset_date - 50;

        lang_text_draw_month_year_max_width(
          game_time_month(), game_time_year(), data.offset_date - 2, 5, 110, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        // Orientation icon
        if (orientation_button_pressed) {
            ImageDraw::img_generic(image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state + 3,
                                   data.offset_rotate,
                                   0);
            orientation_button_pressed--;
        } else
            ImageDraw::img_generic(image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state,
                                   data.offset_rotate,
                                   0);
    }

    if (s_width < 800) {
        if (GAME_ENV == ENGINE_ENV_C3) {
            data.offset_funds = 338;      // +2
            data.offset_population = 453; // +5
            data.offset_date = 547;
            data.offset_rotate = data.offset_date - 50;

            int width = lang_text_draw_colored(6, 0, 341, 5, FONT_SMALL_PLAIN, treasure_color);
            text_draw_number_colored(treasury, '@', " ", 346 + width, 5, FONT_SMALL_PLAIN, treasure_color);

            width = lang_text_draw(6, 1, 458, 5, FONT_NORMAL_BLACK_ON_LIGHT);
            text_draw_number(city_population(), '@', " ", 450 + width, 5, FONT_NORMAL_BLACK_ON_LIGHT);

            lang_text_draw_month_year_max_width(
              game_time_month(), game_time_year(), 540, 5, 100, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            // TODO: draw for 800x600 resolution
        }
    } else if (s_width < 1024) {
        int width = lang_text_draw_colored(6, 0, data.offset_funds + 2 + 100, 5, treasure_font, 0);
        text_draw_number_colored(treasury, '@', " ", data.offset_funds + 7 + width + 100, 5, treasure_font, 0);

        width = lang_text_draw(6, 1, data.offset_population + 2 + 100, 5, FONT_NORMAL_BLACK_ON_LIGHT);
        text_draw_number(
          city_population(), '@', " ", data.offset_population + 7 + width + 100, 5, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        int width = lang_text_draw_colored(6, 0, data.offset_funds + 2, 5, treasure_font, 0);
        text_draw_number_colored(treasury, '@', " ", data.offset_funds + 7 + width, 5, treasure_font, 0);

        width = lang_text_draw(6, 1, data.offset_population + 2, 5, FONT_NORMAL_BLACK_ON_LIGHT);
        text_draw_number(
          city_population(), '@', " ", data.offset_population + 7 + width, 5, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    g_top_menu_drawn.treasury = treasury;
    g_top_menu_drawn.population = city_population();
    g_top_menu_drawn.month = game_time_month();
}

static int get_info_id(int mouse_x, int mouse_y) {
    auto& data = g_top_menu_data;
    if (mouse_y < 4 || mouse_y >= 18)
        return INFO_NONE;

    if (mouse_x > data.offset_funds && mouse_x < data.offset_funds + 128)
        return INFO_FUNDS;

    if (mouse_x > data.offset_population && mouse_x < data.offset_population + 128)
        return INFO_POPULATION;

    if (mouse_x > data.offset_date && mouse_x < data.offset_date + 128)
        return INFO_DATE;

    if (mouse_x > data.offset_rotate && mouse_x < data.offset_rotate + 36) {
        if (mouse_x <= data.offset_rotate + 12)
            return -15;
        else if (mouse_x <= data.offset_rotate + 24)
            return -16;
        else
            return -14;
    }
    return INFO_NONE;
}

static bool handle_input_submenu(const mouse* m, const hotkeys* h) {
    auto& data = g_top_menu_data;
    if (m->right.went_up || h->escape_pressed) {
        clear_state();
        window_go_back();
        return true;
    }
    int menu_id = menu_bar_handle_mouse(m, make_span(g_top_menu), &data.focus_menu_id);
    if (menu_id && menu_id != data.open_sub_menu) {
        window_invalidate();
        data.open_sub_menu = menu_id;
    }
    if (!menu_handle_mouse(m, &g_top_menu[data.open_sub_menu - 1], &data.focus_sub_menu_id)) {
        if (m->left.went_up) {
            clear_state();
            window_go_back();
            return true;
        }
    }
    return false;
}
static bool handle_right_click(int type) {
    if (type == INFO_NONE)
        return false;

    if (type == INFO_FUNDS)
        window_message_dialog_show(MESSAGE_DIALOG_TOP_FUNDS, -1, window_city_draw_all);
    else if (type == INFO_POPULATION)
        window_message_dialog_show(MESSAGE_DIALOG_TOP_POPULATION, -1, window_city_draw_all);
    else if (type == INFO_DATE)
        window_message_dialog_show(MESSAGE_DIALOG_TOP_DATE, -1, window_city_draw_all);

    return true;
}
static bool handle_mouse_menu(const mouse* m) {
    auto& data = g_top_menu_data;
    int menu_id = menu_bar_handle_mouse(m, make_span(g_top_menu), &data.focus_menu_id);
    if (menu_id && m->left.went_up) {
        data.open_sub_menu = menu_id;
        top_menu_window_show();
        return true;
    }
    if (m->right.went_up)
        return handle_right_click(get_info_id(m->x, m->y));

    return false;
}

bool widget_top_menu_handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_top_menu_data;
    int result = 0;
    if (!widget_city_has_input()) {
        int button_id = 0;
        int handled = false;
        if (GAME_ENV == ENGINE_ENV_C3)
            handled = image_buttons_handle_mouse(m, data.offset_rotate, 0, orientation_button, 3, &button_id);
        else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            handled = generic_buttons_handle_mouse(m, data.offset_rotate, 0, orientation_buttons_ph, 3, &button_id);
            if (button_id) {
                orientation_button_state = button_id;
                if (handled)
                    orientation_button_pressed = 5;
            } else
                orientation_button_state = 0;
        }

        if (button_id)
            result = handled;
        else if (data.open_sub_menu)
            result = handle_input_submenu(m, h);
        else
            result = handle_mouse_menu(m);
    }

    return result;
}
int widget_top_menu_get_tooltip_text(tooltip_context* c) {
    auto& data = g_top_menu_data;
    if (data.focus_menu_id)
        return 50 + data.focus_menu_id;

    int button_id = get_info_id(c->mouse_x, c->mouse_y);
    if (button_id && GAME_ENV == ENGINE_ENV_PHARAOH)
        button_id += 1;
    if (button_id)
        return 59 + button_id;

    return 0;
}

static void replay_map_handle(bool confirmed) {
    if (!confirmed) {
        window_city_show();
        return;
    }

    Planner.reset();
    if (scenario_is_custom()) {
        GamestateIO::load_savegame("autosave_replay.sav");
        window_city_show();
    } else {
        int scenario_id = scenario_campaign_scenario_id();
        clear_state();
        GamestateIO::load_mission(scenario_id, true);
    }
}

static void menu_file_new_game_handle(bool confirmed) {
    if (!confirmed) {
        window_city_show();
        return;
    }

    Planner.reset();
    game_undo_disable();
    game_state_reset_overlay();
    window_game_menu_show();
}

static void menu_file_new_game(int param) {
    clear_state();
    window_popup_dialog_show(POPUP_DIALOG_QUIT, menu_file_new_game_handle, e_popup_btns_yesno);
}

static void menu_file_replay_map(int param) {
    clear_state();
    window_popup_dialog_show_confirmation(1, 2, replay_map_handle);
}
static void menu_file_load_game(int param) {
    clear_state();
    Planner.reset();
    window_city_show();
    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
}
static void menu_file_save_game(int param) {
    clear_state();
    window_city_show();
    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_SAVE);
}
static void menu_file_delete_game(int param) {
    clear_state();
    window_city_show();
    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_DELETE);
}
static void menu_file_confirm_exit(bool accepted) {
    if (accepted) {
        clear_state();
        window_main_menu_show(true);
    } else {
        window_city_show();
    }
}
static void menu_file_exit_city(int param) {
    clear_state();
    window_popup_dialog_show(POPUP_DIALOG_QUIT, menu_file_confirm_exit, e_popup_btns_yesno);
}

static void menu_options_display(int param) {
    clear_state();
    window_display_options_ext_show(window_city_show);
}
static void menu_options_sound(int param) {
    clear_state();
    window_sound_options_show(window_city_show);
}
static void menu_options_speed(int param) {
    clear_state();
    window_speed_options_show(window_city_show);
}
static void menu_options_difficulty(int param) {
    clear_state();
    window_difficulty_options_show(window_city_show);
}
static void menu_options_autosave(int param) {
    setting_toggle_monthly_autosave();
    set_text_for_autosave();
}

static void menu_options_change_enh_back() {

}

static void menu_options_change_enh(int param) {
    window_config_show(menu_options_change_enh_back);
}

static void menu_options_hotkeys(int param) {
    window_hotkey_config_show(menu_options_change_enh_back);
}

static void menu_help_help(int param) {
    clear_state();
    window_go_back();
    window_message_dialog_show(MESSAGE_DIALOG_HELP, -1, window_city_draw_all);
}
static void menu_help_mouse_help(int param) {
    setting_cycle_tooltips();
    set_text_for_tooltips();
}
static void menu_help_warnings(int param) {
    setting_toggle_warnings();
    set_text_for_warnings();
}
static void menu_help_about(int param) {
    clear_state();
    window_go_back();
    window_message_dialog_show(MESSAGE_DIALOG_ABOUT, -1, window_city_draw_all);
}

static void menu_advisors_go_to(int advisor) {
    clear_state();
    window_go_back();
    window_advisors_show_advisor(advisor);
}
