#include "top_menu_editor.h"

#include "game/file_editor.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/menu.h"
#include "graphics/elements/panel.h"
#include "graphics/font.h"
#include "graphics/screen.h"
#include "graphics/window.h"
#include "scenario/editor_map.h"
#include "scenario/scenario.h"
#include "window/editor/empire.h"
#include "window/editor/window_editor.h"
#include "window/message_dialog.h"
#include "window/popup_dialog.h"
#include "window/select_list.h"
#include "window/autoconfig_window.h"

#include <algorithm>

static void menu_file_new_map(int param);
static void menu_file_load_map(int param);
static void menu_file_save_map(int param);
static void menu_file_exit_editor(int param);

static void menu_options_sound(int param);
static void menu_options_speed(int param);

static void menu_help_help(int param);
static void menu_help_about(int param);

static void menu_resets_herds(int param);
static void menu_resets_fish(int param);
static void menu_resets_invasions(int param);

static void menu_empire_choose(int param);

static menu_item menu_file[] = {
  {7, 1, menu_file_new_map, 0},
  {7, 2, menu_file_load_map, 0},
  {7, 3, menu_file_save_map, 0},
  {7, 4, menu_file_exit_editor, 0},
};

static menu_item menu_options[] = {
  {2, 2, menu_options_sound, 0},
  {2, 3, menu_options_speed, 0},
};

static menu_item menu_help[] = {
  {3, 1, menu_help_help, 0},
  {3, 7, menu_help_about, 0},
};

static menu_item menu_resets[] = {
  {10, 1, menu_resets_herds, 0},
  {10, 2, menu_resets_fish, 0},
  {10, 3, menu_resets_invasions, 0},
};

static menu_item menu_empire[] = {
  {149, 1, menu_empire_choose, 0},
};

struct editor_menu_bar {
    int text_group;
    menu_item *items;
    int num_items;
    int x_start = 0;
    int x_end = 0;
    int calculated_width_blocks = 0;
    int calculated_height_blocks = 0;
};

static editor_menu_bar menu[] = {
  {7, menu_file, 4},
  {2, menu_options, 2},
  {3, menu_help, 2},
  {10, menu_resets, 3},
  {149, menu_empire, 1},
};

static constexpr int MENU_BAR_COUNT = 5;
static constexpr int ITEM_HEIGHT = 20;

static struct {
    int open_sub_menu;
    int focus_menu_id;
    int focus_sub_menu_id;
} data;

static void clear_state(void) {
    data.open_sub_menu = 0;
    data.focus_menu_id = 0;
    data.focus_sub_menu_id = 0;
}

static void calculate_menu_dimensions(editor_menu_bar &bar) {
    int max_width = 0;
    int height_pixels = ITEM_HEIGHT;
    for (int i = 0; i < bar.num_items; i++) {
        if (bar.items[i].hidden) {
            continue;
        }
        int width_pixels = lang_text_get_width(bar.items[i].text_group, bar.items[i].text_number, FONT_NORMAL_BLACK_ON_LIGHT);
        max_width = std::max(max_width, width_pixels);
        height_pixels += ITEM_HEIGHT;
    }
    int blocks = (max_width + 8) / 16 + 1;
    bar.calculated_width_blocks = blocks < 10 ? 10 : blocks;
    bar.calculated_height_blocks = height_pixels / 16;
}

static void draw_submenu(void) {
    if (!data.open_sub_menu) {
        return;
    }

    editor_menu_bar &bar = menu[data.open_sub_menu - 1];
    if (bar.calculated_width_blocks == 0 || bar.calculated_height_blocks == 0) {
        calculate_menu_dimensions(bar);
    }

    unbordered_panel_draw(bar.x_start, TOP_MENU_HEIGHT, bar.calculated_width_blocks, bar.calculated_height_blocks);
    int y_offset = TOP_MENU_HEIGHT + 2;
    for (int i = 0; i < bar.num_items; i++) {
        if (bar.items[i].hidden) {
            continue;
        }
        e_font font = (i + 1 == data.focus_sub_menu_id) ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT;
        lang_text_draw(bar.items[i].text_group, bar.items[i].text_number, bar.x_start + 8, y_offset, font);
        y_offset += ITEM_HEIGHT;
    }
}

static void draw_foreground(int) {
    if (!data.open_sub_menu) {
        return;
    }
    window_editor_map_draw_all();
    draw_submenu();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    widget_top_menu_editor_handle_input(m, h);
}

static void top_menu_window_show(void) {
    window_type window = {"window_editor_top_menu", [](int) {}, draw_foreground, handle_input};
    window_show(&window);
}

void widget_top_menu_editor_draw(void) {
    int block_width = 24;
    int image_base = image_id_from_group(GROUP_TOP_MENU_SIDEBAR);
    int s_width = screen_width();
    painter ctx = game.painter();
    for (int i = 0; i * block_width < s_width; i++) {
        ctx.img_generic(image_base + i % 8, {i * block_width, 0});
    }

    int x_offset = 10;
    for (int i = 0; i < MENU_BAR_COUNT; i++) {
        menu[i].x_start = x_offset;
        e_font font = (i + 1 == data.focus_menu_id) ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT;
        x_offset += lang_text_draw(menu[i].text_group, 0, x_offset, 6, font);
        menu[i].x_end = x_offset;
        x_offset += 16;
    }
}

static int get_bar_menu_id(const mouse *m) {
    if (m->y < 0 || m->y >= TOP_MENU_HEIGHT) {
        return 0;
    }
    for (int i = 0; i < MENU_BAR_COUNT; i++) {
        if (menu[i].x_start <= m->x && menu[i].x_end > m->x) {
            return i + 1;
        }
    }
    return 0;
}

static int get_submenu_item(const mouse *m, editor_menu_bar &bar) {
    int y_offset = TOP_MENU_HEIGHT + 2;
    for (int i = 0; i < bar.num_items; i++) {
        if (bar.items[i].hidden) {
            continue;
        }
        if (bar.x_start <= m->x && bar.x_start + 16 * bar.calculated_width_blocks > m->x
            && y_offset - 2 <= m->y && y_offset + 19 > m->y) {
            return i + 1;
        }
        y_offset += ITEM_HEIGHT;
    }
    return 0;
}

static bool handle_input_submenu(const mouse* m, const hotkeys* h) {
    if (m->right.went_up || h->escape_pressed) {
        clear_state();
        window_go_back();
        return true;
    }

    int menu_id = get_bar_menu_id(m);
    if (menu_id && menu_id != data.open_sub_menu) {
        data.open_sub_menu = menu_id;
        data.focus_sub_menu_id = 0;
        menu[menu_id - 1].calculated_width_blocks = 0;
        return true;
    }

    editor_menu_bar &bar = menu[data.open_sub_menu - 1];
    if (bar.calculated_width_blocks == 0) {
        calculate_menu_dimensions(bar);
    }

    int item_id = get_submenu_item(m, bar);
    data.focus_sub_menu_id = item_id;
    if (item_id && m->left.went_up) {
        menu_item &item = bar.items[item_id - 1];
        if (item._onclick) {
            item._onclick(item.parameter);
        }
        return true;
    }

    if (m->left.went_up) {
        clear_state();
        window_go_back();
        return true;
    }
    return true;
}

static bool handle_mouse_menu(const mouse* m) {
    data.focus_menu_id = get_bar_menu_id(m);
    if (data.focus_menu_id && m->left.went_up) {
        data.open_sub_menu = data.focus_menu_id;
        data.focus_sub_menu_id = 0;
        menu[data.open_sub_menu - 1].calculated_width_blocks = 0;
        top_menu_window_show();
        return true;
    }
    return false;
}

int widget_top_menu_editor_handle_input(const mouse* m, const hotkeys* h) {
    if (data.open_sub_menu)
        return handle_input_submenu(m, h);
    else {
        return handle_mouse_menu(m);
    }
}

static void map_size_selected(int size) {
    clear_state();
    if (size >= 0 && size <= 5) {
        game_file_editor_create_scenario(size);
        window_editor_map_show();
    } else {
        window_go_back();
    }
}

static void menu_file_new_map(int param) {
    window_select_list_show(50, 50, 33, 7, map_size_selected);
}

static void menu_file_load_map(int param) {
    clear_state();
    window_editor_map_show();
    autoconfig_window::show("file_dialog_load_scenario");
}

static void menu_file_save_map(int param) {
    clear_state();
    window_editor_map_show();
    autoconfig_window::show("file_dialog_save_scenario");
}

static void menu_file_exit_editor(int param) {
    clear_state();
    window_editor_map_show();

    if (g_scenario.is_saved) {
        game_exit_editor();
        return;
    }

    popup_dialog::show_yesno("#popup_dialog_quit_without_saving", [](bool accepted) {
        if (accepted)
            game_exit_editor();
        else {
            window_editor_map_show();
        }
    });
}

static void menu_options_sound(int param) {
    clear_state();
    window_editor_map_show();
    autoconfig_window::show("sound_options_window");
}

static void menu_options_speed(int param) {
    clear_state();
    window_editor_map_show();
    autoconfig_window::show("speed_options_window");
}

static void menu_help_help(int param) {
    clear_state();
    window_go_back();
    window_message_dialog_show("message_dialog_editor_help", -1, window_editor_map_draw_all);
}

static void menu_help_about(int param) {
    clear_state();
    window_go_back();
    window_message_dialog_show("message_dialog_editor_about", -1, window_editor_map_draw_all);
}

static void menu_resets_herds(int param) {
    scenario_editor_clear_predator_herd_points();
    clear_state();
    window_go_back();
}

static void menu_resets_fish(int param) {
    scenario_editor_clear_fishing_points();
    clear_state();
    window_go_back();
}

static void menu_resets_invasions(int param) {
    scenario_editor_clear_invasion_points();
    clear_state();
    window_go_back();
}

static void menu_empire_choose(int param) {
    clear_state();
    window_go_back();
    window_editor_empire_show();
}
