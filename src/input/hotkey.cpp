#include "hotkey.h"

#include "city/constants.h"
#include "core/app.h"
#include "overlays/city_overlay.h"
#include "game/state.h"
#include "game/system.h"
#include "game/settings.h"
#include "graphics/screenshot.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "input/scroll.h"
#include "widget/widget_top_menu_game.h"
#include "window/window_city.h"
#include "window/hotkey_editor.h"
#include "window/main_menu.h"
#include "window/popup_dialog.h"
#include "game/game.h"

#include <stdlib.h>
#include <string.h>

struct hotkey_definition {
    int* action;
    int value;
    int key;
    int modifiers;
    int repeatable;
};

struct arrow_definition {
    void (*action)(int is_down);
    int key;
};

struct global_hotkeys {
    int center_screen;
    int toggle_fullscreen;
    int save_screenshot;
    int save_city_screenshot;
};

struct hotkey_data_t {
    global_hotkeys global_hotkey_state;
    hotkeys hotkey_state;

    hotkey_definition* definitions;
    int num_definitions;
    arrow_definition* arrows;
    int num_arrows;
};

hotkey_data_t g_hotkey_data;

static void add_definition(const hotkey_mapping* mapping) {
    auto& data = g_hotkey_data;
    hotkey_definition* def = &data.definitions[data.num_definitions];
    def->key = mapping->key;
    def->modifiers = mapping->modifiers;
    def->value = 1;
    def->repeatable = 0;
    switch (mapping->action) {
    case HOTKEY_TOGGLE_PAUSE:
        def->action = &data.hotkey_state.toggle_pause;
        break;
    case HOTKEY_TOGGLE_OVERLAY:
        def->action = &data.hotkey_state.toggle_overlay;
        break;
    case HOTKEY_CYCLE_LEGION:
        def->action = &data.hotkey_state.cycle_legion;
        break;
    case HOTKEY_INCREASE_GAME_SPEED:
        def->action = &data.hotkey_state.increase_game_speed;
        def->repeatable = 1;
        break;
    case HOTKEY_DECREASE_GAME_SPEED:
        def->action = &data.hotkey_state.decrease_game_speed;
        def->repeatable = 1;
        break;
    case HOTKEY_ROTATE_MAP_LEFT:
        def->action = &data.hotkey_state.rotate_map_left;
        break;
    case HOTKEY_ROTATE_MAP_RIGHT:
        def->action = &data.hotkey_state.rotate_map_right;
        break;
    case HOTKEY_SHOW_ADVISOR_LABOR:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_LABOR;
        break;
    case HOTKEY_SHOW_ADVISOR_MILITARY:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_MILITARY;
        break;
    case HOTKEY_SHOW_ADVISOR_IMPERIAL:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_IMPERIAL;
        break;
    case HOTKEY_SHOW_ADVISOR_RATINGS:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_RATINGS;
        break;
    case HOTKEY_SHOW_ADVISOR_TRADE:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_TRADE;
        break;
    case HOTKEY_SHOW_ADVISOR_POPULATION:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_POPULATION;
        break;
    case HOTKEY_SHOW_ADVISOR_HEALTH:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_HEALTH;
        break;
    case HOTKEY_SHOW_ADVISOR_EDUCATION:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_EDUCATION;
        break;
    case HOTKEY_SHOW_ADVISOR_ENTERTAINMENT:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_ENTERTAINMENT;
        break;
    case HOTKEY_SHOW_ADVISOR_RELIGION:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_RELIGION;
        break;
    case HOTKEY_SHOW_ADVISOR_FINANCIAL:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_FINANCIAL;
        break;
    case HOTKEY_SHOW_ADVISOR_CHIEF:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_CHIEF;
        break;
    case HOTKEY_SHOW_ADVISOR_HOUSING:
        def->action = &data.hotkey_state.show_advisor;
        def->value = ADVISOR_HOUSING;
        break;
    case HOTKEY_SHOW_OVERLAY_WATER:
        def->action = &data.hotkey_state.show_overlay;
        def->value = OVERLAY_WATER;
        break;
    case HOTKEY_SHOW_OVERLAY_FIRE:
        def->action = &data.hotkey_state.show_overlay;
        def->value = OVERLAY_FIRE;
        break;
    case HOTKEY_SHOW_OVERLAY_DAMAGE:
        def->action = &data.hotkey_state.show_overlay;
        def->value = OVERLAY_DAMAGE;
        break;
    case HOTKEY_SHOW_OVERLAY_CRIME:
        def->action = &data.hotkey_state.show_overlay;
        def->value = OVERLAY_CRIME;
        break;
    case HOTKEY_SHOW_OVERLAY_PROBLEMS:
        def->action = &data.hotkey_state.show_overlay;
        def->value = OVERLAY_PROBLEMS;
        break;
    case HOTKEY_EDITOR_TOGGLE_BATTLE_INFO:
        def->action = &data.hotkey_state.toggle_editor_battle_info;
        break;
    case HOTKEY_LOAD_FILE:
        def->action = &data.hotkey_state.load_file;
        break;
    case HOTKEY_SAVE_FILE:
        def->action = &data.hotkey_state.save_file;
        break;
    case HOTKEY_ROTATE_BUILDING:
        def->action = &data.hotkey_state.rotate_building;
        break;
    case HOTKEY_CHANGE_BUILDING_VARIANT:
        def->action = &data.hotkey_state.change_building_variant;
        break;
    case HOTKEY_GO_TO_BOOKMARK_1:
        def->action = &data.hotkey_state.go_to_bookmark;
        def->value = 1;
        break;
    case HOTKEY_GO_TO_BOOKMARK_2:
        def->action = &data.hotkey_state.go_to_bookmark;
        def->value = 2;
        break;
    case HOTKEY_GO_TO_BOOKMARK_3:
        def->action = &data.hotkey_state.go_to_bookmark;
        def->value = 3;
        break;
    case HOTKEY_GO_TO_BOOKMARK_4:
        def->action = &data.hotkey_state.go_to_bookmark;
        def->value = 4;
        break;
    case HOTKEY_SET_BOOKMARK_1:
        def->action = &data.hotkey_state.set_bookmark;
        def->value = 1;
        break;
    case HOTKEY_SET_BOOKMARK_2:
        def->action = &data.hotkey_state.set_bookmark;
        def->value = 2;
        break;
    case HOTKEY_SET_BOOKMARK_3:
        def->action = &data.hotkey_state.set_bookmark;
        def->value = 3;
        break;
    case HOTKEY_SET_BOOKMARK_4:
        def->action = &data.hotkey_state.set_bookmark;
        def->value = 4;
        break;
    case HOTKEY_CENTER_WINDOW:
        def->action = &data.global_hotkey_state.center_screen;
        break;
    case HOTKEY_TOGGLE_FULLSCREEN:
        def->action = &data.global_hotkey_state.toggle_fullscreen;
        break;
    case HOTKEY_SAVE_SCREENSHOT:
        def->action = &data.global_hotkey_state.save_screenshot;
        break;
    case HOTKEY_SAVE_CITY_SCREENSHOT:
        def->action = &data.global_hotkey_state.save_city_screenshot;
        break;
    case HOTKEY_BUILD_VACANT_HOUSE:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_HOUSE_VACANT_LOT;
        break;
    case HOTKEY_BUILD_CLEAR_LAND:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_CLEAR_LAND;
        break;
    case HOTKEY_BUILD_ROAD:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_ROAD;
        break;
    case HOTKEY_BUILD_ENGINEERS_POST:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_ARCHITECT_POST;
        break;
    case HOTKEY_BUILD_WALL:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_MUD_WALL;
        break;
    case HOTKEY_BUILD_GATEHOUSE:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_MUD_GATEHOUSE;
        break;
    case HOTKEY_BUILD_PREFECTURE:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_POLICE_STATION;
        break;
    case HOTKEY_BUILD_GRANARY:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_GRANARY;
        break;
    case BUILDING_STORAGE_YARD:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_STORAGE_YARD;
        break;
    case HOTKEY_BUILD_MARKET:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_BAZAAR;
        break;
    case HOTKEY_BUILD_PLAZA:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_PLAZA;
        break;
    case HOTKEY_BUILD_GARDENS:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_GARDENS;
        break;
    case HOTKEY_BUILD_RESERVOIR:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_WATER_LIFT;
        break;
    case HOTKEY_BUILD_AQUEDUCT:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_IRRIGATION_DITCH;
        break;
    case HOTKEY_BUILD_FOUNTAIN:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_MENU_BEAUTIFICATION;
        break;
    case HOTKEY_BUILD_DOCTOR:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_APOTHECARY;
        break;
    case HOTKEY_BUILD_ROADBLOCK:
        def->action = &data.hotkey_state.building;
        def->value = BUILDING_ROADBLOCK;
        break;
    case HOTKEY_DEBUG_1_UP:
        def->action = &data.hotkey_state.debug_tile_up;
        def->repeatable = 1;
        break;
    case HOTKEY_DEBUG_1_DOWN:
        def->action = &data.hotkey_state.debug_tile_down;
        def->repeatable = 1;
        break;
    case HOTKEY_DEBUG_RENDER_UP:
        def->action = &data.hotkey_state.debug_render_up;
        def->repeatable = 1;
        break;
    case HOTKEY_DEBUG_RENDER_DOWN:
        def->action = &data.hotkey_state.debug_render_down;
        def->repeatable = 1;
        break;
    default:
        def->action = 0;
    }
    if (def->action)
        data.num_definitions++;
}

static void add_arrow(const hotkey_mapping* mapping) {
    auto& data = g_hotkey_data;
    arrow_definition* arrow = &data.arrows[data.num_arrows];
    arrow->key = mapping->key;
    switch (mapping->action) {
    case HOTKEY_ARROW_UP:
        arrow->action = scroll_arrow_up;
        break;
    case HOTKEY_ARROW_DOWN:
        arrow->action = scroll_arrow_down;
        break;
    case HOTKEY_ARROW_LEFT:
        arrow->action = scroll_arrow_left;
        break;
    case HOTKEY_ARROW_RIGHT:
        arrow->action = scroll_arrow_right;
        break;
    default:
        arrow->action = 0;
        break;
    }
    if (arrow->action)
        data.num_arrows++;
}

static int allocate_mapping_memory(int total_definitions, int total_arrows) {
    auto& data = g_hotkey_data;
    free(data.definitions);
    free(data.arrows);
    data.num_definitions = 0;
    data.num_arrows = 0;
    data.definitions = (hotkey_definition*)malloc(sizeof(hotkey_definition) * total_definitions);
    data.arrows = (arrow_definition*)malloc(sizeof(arrow_definition) * total_arrows);
    if (!data.definitions || !data.arrows) {
        free(data.definitions);
        free(data.arrows);
        return 0;
    }
    return 1;
}

void hotkey_install_mapping(hotkey_mapping* mappings, int num_mappings) {
    auto& data = g_hotkey_data;
    int total_definitions = 2; // Enter and ESC are fixed hotkeys
    int total_arrows = 0;
    for (int i = 0; i < num_mappings; i++) {
        int action = mappings[i].action;
        if (action == HOTKEY_ARROW_UP || action == HOTKEY_ARROW_DOWN || action == HOTKEY_ARROW_LEFT
            || action == HOTKEY_ARROW_RIGHT) {
            total_arrows++;
        } else
            total_definitions++;
    }
    if (!allocate_mapping_memory(total_definitions, total_arrows))
        return;

    // Fixed keys: Escape and Enter
    data.definitions[0].action = &data.hotkey_state.enter_pressed;
    data.definitions[0].key = KEY_ENTER;
    data.definitions[0].modifiers = 0;
    data.definitions[0].repeatable = 0;
    data.definitions[0].value = 1;

    data.definitions[1].action = &data.hotkey_state.escape_pressed;
    data.definitions[1].key = KEY_ESCAPE;
    data.definitions[1].modifiers = 0;
    data.definitions[1].repeatable = 0;
    data.definitions[1].value = 1;

    data.num_definitions = 2;

    for (int i = 0; i < num_mappings; i++) {
        int action = mappings[i].action;
        if (action == HOTKEY_ARROW_UP || action == HOTKEY_ARROW_DOWN || action == HOTKEY_ARROW_LEFT
            || action == HOTKEY_ARROW_RIGHT) {
            add_arrow(&mappings[i]);
        } else
            add_definition(&mappings[i]);
    }
}

const hotkeys* hotkey_state(void) {
    return &g_hotkey_data.hotkey_state;
}

void hotkey_reset_state(void) {
    auto& data = g_hotkey_data;
    memset(&data.hotkey_state, 0, sizeof(data.hotkey_state));
    memset(&data.global_hotkey_state, 0, sizeof(data.global_hotkey_state));
}

void hotkey_key_pressed(int key, int modifiers, int repeat) {
    auto& data = g_hotkey_data;
    if (window_is(WINDOW_HOTKEY_EDITOR)) {
        window_hotkey_editor_key_pressed(key, modifiers);
        return;
    }
    if (key == KEY_NONE)
        return;
    for (int i = 0; i < data.num_arrows; i++) {
        arrow_definition* arrow = &data.arrows[i];
        if (arrow->key == key)
            arrow->action(1);
    }
    for (int i = 0; i < data.num_definitions; i++) {
        hotkey_definition* def = &data.definitions[i];
        if (def->key == key && def->modifiers == modifiers && (!repeat || def->repeatable))
            *(def->action) = def->value;
    }
}

void hotkey_key_released(int key, int modifiers) {
    auto& data = g_hotkey_data;
    if (window_is(WINDOW_HOTKEY_EDITOR)) {
        window_hotkey_editor_key_released(key, modifiers);
        return;
    }
    if (key == KEY_NONE) {
        return;
    }
    for (int i = 0; i < data.num_arrows; i++) {
        arrow_definition* arrow = &data.arrows[i];
        if (arrow->key == key)
            arrow->action(0);
    }
}

void hotkey_handle_escape(void) {
    video_stop();
    popup_dialog::show_yesno("#popup_dialog_quit", [] (bool accepted) {
        if (accepted) {
            widget_top_menu_clear_state();
            window_main_menu_show(true);
        } else {
            window_city_show();
        }
    });
}

void hotkey_handle_global_keys() {
    auto& data = g_hotkey_data;
    if (data.global_hotkey_state.center_screen) {
        system_center();
    }

    if (data.global_hotkey_state.toggle_fullscreen) {
        app_fullscreen(!g_settings.is_fullscreen());
    }

    if (data.global_hotkey_state.save_screenshot) {
        graphics_save_screenshot(SCREENSHOT_DISPLAY);
    } else if (data.global_hotkey_state.save_city_screenshot) {
        graphics_save_screenshot(SCREENSHOT_FULL_CITY);
    }
}
