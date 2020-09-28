#include "build_menu.h"

#include "building/construction.h"
#include "building/model.h"
#include "city/view.h"
#include "graphics/generic_button.h"
#include "graphics/image.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/property.h"
#include "widget/city.h"
#include "widget/sidebar/city.h"
#include "window/city.h"
#include "core/game_environment.h"

static void button_menu_index(int param1, int param2);
static void button_menu_item(int item);

#define BTN_W_ADD 128
#define BTN_W_MIN -BTN_W_ADD - 8
#define BTN_W_TOT 256 + BTN_W_ADD

static generic_button build_menu_buttons[] = {
        {BTN_W_MIN, 0,   256 + BTN_W_ADD, 20, button_menu_index, button_none, 1,  0},
        {BTN_W_MIN, 24,  256 + BTN_W_ADD, 20, button_menu_index, button_none, 2,  0},
        {BTN_W_MIN, 48,  256 + BTN_W_ADD, 20, button_menu_index, button_none, 3,  0},
        {BTN_W_MIN, 72,  256 + BTN_W_ADD, 20, button_menu_index, button_none, 4,  0},
        {BTN_W_MIN, 96,  256 + BTN_W_ADD, 20, button_menu_index, button_none, 5,  0},
        {BTN_W_MIN, 120, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 6,  0},
        {BTN_W_MIN, 144, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 7,  0},
        {BTN_W_MIN, 168, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 8,  0},
        {BTN_W_MIN, 192, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 9,  0},
        {BTN_W_MIN, 216, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 10, 0},
        {BTN_W_MIN, 240, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 11, 0},
        {BTN_W_MIN, 264, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 12, 0},
        {BTN_W_MIN, 288, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 13, 0},
        {BTN_W_MIN, 312, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 14, 0},
        {BTN_W_MIN, 336, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 15, 0},
        {BTN_W_MIN, 360, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 16, 0},
        {BTN_W_MIN, 384, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 17, 0},
        {BTN_W_MIN, 408, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 18, 0},
        {BTN_W_MIN, 432, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 19, 0},
        {BTN_W_MIN, 456, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 20, 0},
        {BTN_W_MIN, 480, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 21, 0},
        {BTN_W_MIN, 504, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 22, 0},
        {BTN_W_MIN, 528, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 23, 0},
        {BTN_W_MIN, 552, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 24, 0},
        {BTN_W_MIN, 576, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 25, 0},
        {BTN_W_MIN, 600, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 26, 0},
        {BTN_W_MIN, 624, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 27, 0},
        {BTN_W_MIN, 648, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 28, 0},
        {BTN_W_MIN, 672, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 29, 0},
        {BTN_W_MIN, 696, 256 + BTN_W_ADD, 20, button_menu_index, button_none, 30, 0},
};

static const int Y_MENU_OFFSETS[] = {
        0, 322, 306, 274, 258, 226, 210, 178, 162, 130, 114,
        82, 66, 34, 18, -30, -46, -62, -78, -78, -94,
        -94, -110, -110,
        0, 0, 0, 0, 0, 0
};

static struct {
    int selected_submenu;
    int num_items;
    int y_offset;

    int focus_button_id;
} data;

static int init(int submenu) {
    data.selected_submenu = submenu;
    data.num_items = building_menu_count_items(submenu);
    data.y_offset = Y_MENU_OFFSETS[data.num_items];

//    int type = building_menu_type(data.selected_submenu, item);
//    building_construction_set_type(type);

    if (submenu == BUILD_MENU_VACANT_HOUSE ||
        submenu == BUILD_MENU_CLEAR_LAND ||
        submenu == BUILD_MENU_ROAD) {
        button_menu_item(0);
        return 0;
    } else
        return 1;
}

static int get_sidebar_x_offset(void) {
    int view_x, view_y, view_width, view_height;
    city_view_get_unscaled_viewport(&view_x, &view_y, &view_width, &view_height);
    return view_x + view_width;
}
static int is_all_button(int type) {
    return (type == BUILDING_MENU_SMALL_TEMPLES && data.selected_submenu == BUILD_MENU_SMALL_TEMPLES) ||
           (type == BUILDING_MENU_LARGE_TEMPLES && data.selected_submenu == BUILD_MENU_LARGE_TEMPLES);
}
static int set_submenu_for_type(int type) {
    int current_menu = data.selected_submenu;
    switch (type) {
        case BUILDING_MENU_FARMS:
            data.selected_submenu = BUILD_MENU_FARMS;
            break;
        case BUILDING_MENU_RAW_MATERIALS:
            data.selected_submenu = BUILD_MENU_RAW_MATERIALS;
            break;
//        case BUILDING_MENU_GUILDS:
        case BUILDING_MENU_WORKSHOPS:
            data.selected_submenu = BUILD_MENU_WORKSHOPS;
            break;
        case BUILDING_MENU_SMALL_TEMPLES:
            data.selected_submenu = BUILD_MENU_SMALL_TEMPLES;
            break;
        case BUILDING_MENU_LARGE_TEMPLES:
            data.selected_submenu = BUILD_MENU_LARGE_TEMPLES;
            break;
        case BUILDING_FORT:
            data.selected_submenu = BUILD_MENU_FORTS;
            break;
        case BUILDING_MENU_MONUMENTS:
            if (GAME_ENV == ENGINE_ENV_C3)
                return 0;
            data.selected_submenu = BUILD_MENU_MONUMENTS;
            break;
        case BUILDING_MENU_WATER_CROSSINGS:
            if (GAME_ENV == ENGINE_ENV_C3)
                return 0;
            data.selected_submenu = BUILD_MENU_WATER_CROSSINGS;
            break;
        case BUILDING_MENU_BEAUTIFICATION:
            if (GAME_ENV == ENGINE_ENV_C3)
                return 0;
            data.selected_submenu = BUILD_MENU_BEAUTIFICATION;
            break;
        case BUILDING_MENU_DEFENCES:
            data.selected_submenu = BUILD_MENU_DEFENCES;
            break;
        case BUILDING_MENU_SHRINES:
            data.selected_submenu = BUILD_MENU_SHRINES;
            break;
        default:
            return 0;
    }
    return current_menu != data.selected_submenu;
}

#include "window/city.h"

static void draw_background(void) {
    window_city_draw_panels();
}
static void draw_menu_buttons(void) {
    int x_offset = get_sidebar_x_offset();
    int label_width = (BTN_W_TOT) / 16;
    int label_margin = BTN_W_TOT + 10;
    int label_offset = 0;
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        label_offset = 20;

    font_t font = FONT_NORMAL_GREEN;
    int item_index = -1;
    for (int i = 0; i < data.num_items; i++) {
        if (GAME_ENV == ENGINE_ENV_PHARAOH)
            font = FONT_NORMAL_BLACK;
        if (data.focus_button_id == i + 1)
            font = FONT_NORMAL_GREEN;
        item_index = building_menu_next_index(data.selected_submenu, item_index);
        label_draw(x_offset - label_margin, data.y_offset + 110 + 24 * i, label_width,
                   data.focus_button_id == i + 1 ? 1 : 2);
        int type = building_menu_type(data.selected_submenu, item_index);
        if (is_all_button(type))
            lang_text_draw_centered(52, 19, x_offset - label_margin + label_offset, data.y_offset + 113 + 24 * i, 176,
                                    font);
        else
            lang_text_draw_centered(28, type, x_offset - label_margin + label_offset, data.y_offset + 113 + 24 * i, 176,
                                    font);
        if (type == BUILDING_DRAGGABLE_RESERVOIR)
            type = BUILDING_RESERVOIR;
        int cost = model_get_building(type)->cost;
        if (type == BUILDING_FORT)
            cost = 0;
        if (type == BUILDING_MENU_SMALL_TEMPLES && data.selected_submenu == BUILD_MENU_SMALL_TEMPLES)
            cost = model_get_building(BUILDING_SMALL_TEMPLE_CERES)->cost;
        if (type == BUILDING_MENU_LARGE_TEMPLES && data.selected_submenu == BUILD_MENU_LARGE_TEMPLES)
            cost = model_get_building(BUILDING_LARGE_TEMPLE_CERES)->cost;
        if (cost)
            text_draw_money(cost, x_offset - 82 - label_offset, data.y_offset + 114 + 24 * i, font);
    }
}
static void draw_foreground(void) {
    window_city_draw();
    draw_menu_buttons();
}

static int handle_build_submenu(const mouse *m) {
    return generic_buttons_handle_mouse(m, get_sidebar_x_offset() - 258, data.y_offset + 110, build_menu_buttons,
                                        data.num_items, &data.focus_button_id);
}
static void handle_input(const mouse *m, const hotkeys *h) {
    if (handle_build_submenu(m) ||
        widget_sidebar_city_handle_mouse_build_menu(m))
        return;
    if (input_go_back_requested(m, h)) {
        window_city_show();
        return;
    }
}
static int button_index_to_submenu_item(int index) {
    int item = -1;
    for (int i = 0; i <= index; i++) {
        item = building_menu_next_index(data.selected_submenu, item);
    }
    return item;
}
static void button_menu_index(int param1, int param2) {
    button_menu_item(button_index_to_submenu_item(param1 - 1));
}
static void button_menu_item(int item) {
    widget_city_clear_current_tile();

    int type = building_menu_type(data.selected_submenu, item);
    building_construction_set_type(type);

    if (set_submenu_for_type(type)) {
        data.num_items = building_menu_count_items(data.selected_submenu);
        data.y_offset = Y_MENU_OFFSETS[data.num_items];
        building_construction_clear_type();
        window_invalidate();
    } else {
        window_city_show();
    }
}

int window_build_menu_image(void) {
    int image_base = image_id_from_group(GROUP_PANEL_WINDOWS);
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            if (building_construction_type() == BUILDING_NONE)
                return image_base + 12;
            switch (data.selected_submenu) {
                default:
                case BUILD_MENU_VACANT_HOUSE:
                    return image_base;
                case BUILD_MENU_CLEAR_LAND:
                    if (scenario_property_climate() == CLIMATE_DESERT)
                        return image_id_from_group(GROUP_PANEL_WINDOWS_DESERT);
                    else {
                        return image_base + 11;
                    }
                case BUILD_MENU_ROAD:
                    if (scenario_property_climate() == CLIMATE_DESERT)
                        return image_id_from_group(GROUP_PANEL_WINDOWS_DESERT) + 1;
                    else {
                        return image_base + 10;
                    }
                case BUILD_MENU_WATER:
                    if (scenario_property_climate() == CLIMATE_DESERT)
                        return image_id_from_group(GROUP_PANEL_WINDOWS_DESERT) + 2;
                    else {
                        return image_base + 3;
                    }
                case BUILD_MENU_HEALTH:
                    return image_base + 5;
                case BUILD_MENU_RELIGION:
                    return image_base + 1;
                case BUILD_MENU_EDUCATION:
                    return image_base + 6;
                case BUILD_MENU_ENTERTAINMENT:
                    return image_base + 4;
                case BUILD_MENU_ADMINISTRATION:
                    return image_base + 2;
                case BUILD_MENU_ENGINEERING:
                    return image_base + 7;
                case BUILD_MENU_SECURITY:
                    if (scenario_property_climate() == CLIMATE_DESERT)
                        return image_id_from_group(GROUP_PANEL_WINDOWS_DESERT) + 3;
                    else {
                        return image_base + 8;
                    }
                case BUILD_MENU_INDUSTRY:
                    return image_base + 9;
            }
            break;
        case ENGINE_ENV_PHARAOH:
            image_base = image_id_from_group(GROUP_PANEL_WINDOWS_PH);
//            if (building_construction_type() == BUILDING_NONE)
//                return image_base;
            switch (data.selected_submenu) {
                default:
                case BUILD_MENU_VACANT_HOUSE:
                    return image_base + 1;
                case BUILD_MENU_ROAD:
                    return image_base + 5;
                case BUILD_MENU_CLEAR_LAND:
                    return image_base + 9;
                case BUILD_MENU_FARMS:
                case BUILD_MENU_FOOD:
                    return image_base + 10;
                case BUILD_MENU_GUILDS:
                case BUILD_MENU_RAW_MATERIALS:
                case BUILD_MENU_INDUSTRY:
                    return image_base + 6;
                case BUILD_MENU_DISTRIBUTION:
                    return image_base + 2;
                case BUILD_MENU_ENTERTAINMENT:
                    return image_base + 3;
                case BUILD_MENU_SHRINES:
                case BUILD_MENU_TEMPLES:
                case BUILD_MENU_LARGE_TEMPLES:
                case BUILD_MENU_MONUMENTS:
                case BUILD_MENU_RELIGION:
                    return image_base + 7;
                case BUILD_MENU_EDUCATION:
                    return image_base + 11;
                case BUILD_MENU_HEALTH:
                    return image_base + 4;
                case BUILD_MENU_WATER_CROSSINGS:
                case BUILD_MENU_BEAUTIFICATION:
                case BUILD_MENU_ADMINISTRATION:
                    return image_base + 8;
                case BUILD_MENU_DEFENCES:
                case BUILD_MENU_FORTS:
                case BUILD_MENU_SECURITY:
                    return image_base + 12;
            }
            break;
    }

}
void window_build_menu_show(int submenu) {
    if (init(submenu)) {
        window_type window = {
                WINDOW_BUILD_MENU,
                draw_background,
                draw_foreground,
                handle_input,
                0
        };
        window_show(&window);
    }
}
