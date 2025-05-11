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

struct hotkey_definition {
    int* action = nullptr;
    int value;
    int key;
    int modifiers;
    int repeatable;
    std::function<void()> callback;
};

struct arrow_definition {
    void (*action)(int is_down);
    int key;
};

struct global_hotkeys {
    int save_screenshot;
    int save_city_screenshot;
};

struct hotkey_data_t {
    global_hotkeys global_hotkey_state;
    hotkeys hotkey_state;

    svector<hotkey_definition, 128> definitions;
    svector<arrow_definition, 16> arrows;
};

hotkey_data_t g_hotkey_data;

static void add_definition(const hotkey_mapping& mapping, bool alt) {
    auto& data = g_hotkey_data;
   
    e_key key = alt ? mapping.alt.key : mapping.state.key;
    e_key_mode modifiers = alt ? mapping.alt.modifiers : mapping.state.modifiers;
    
    if (key == KEY_NONE) {
        return;
    }

    hotkey_definition *def = &data.definitions.emplace_back();
    def->key = key;
    def->modifiers = modifiers;

    def->value = 1;
    def->repeatable = 0;
    switch (mapping.action) {
    case HOTKEY_TOGGLE_PAUSE:
        def->callback = [action = mapping.action] { events::emit(event_toggle_pause{ action }); };
        break;

    case HOTKEY_TOGGLE_OVERLAY:      
        def->callback = [action = mapping.action] { events::emit(event_toggle_overlay{ action }); };
        break;

    case HOTKEY_CYCLE_LEGION:
        def->callback = [action = mapping.action] { events::emit(event_toggle_legion{ action }); };
        break;

    case HOTKEY_INCREASE_GAME_SPEED:
    case HOTKEY_DECREASE_GAME_SPEED:
        def->callback = [action = mapping.action] { events::emit(event_change_gamespeed{ action }); };
        def->repeatable = 1;
        break;

    case HOTKEY_ROTATE_MAP_LEFT:
    case HOTKEY_ROTATE_MAP_RIGHT:
        def->callback = [action = mapping.action] { events::emit(event_rotate_map{ action }); };
        break;

    case HOTKEY_SHOW_ADVISOR_LABOR:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_LABOR }); };
        break;
    case HOTKEY_SHOW_ADVISOR_MILITARY:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_MILITARY }); };
        break;
    case HOTKEY_SHOW_ADVISOR_KINGDOME:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_IMPERIAL }); };
        break;
    case HOTKEY_SHOW_ADVISOR_RATINGS:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_RATINGS }); };
        break;
    case HOTKEY_SHOW_ADVISOR_TRADE:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_RATINGS }); };
        break;
    case HOTKEY_SHOW_ADVISOR_POPULATION:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_POPULATION }); };
        break;
    case HOTKEY_SHOW_ADVISOR_HEALTH:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_HEALTH }); };
        break;
    case HOTKEY_SHOW_ADVISOR_EDUCATION:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_EDUCATION }); };
        break;
    case HOTKEY_SHOW_ADVISOR_ENTERTAINMENT:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_ENTERTAINMENT }); };
        break;
    case HOTKEY_SHOW_ADVISOR_RELIGION:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_RELIGION }); };
        break;
    case HOTKEY_SHOW_ADVISOR_FINANCIAL:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_FINANCIAL }); };
        break;
    case HOTKEY_SHOW_ADVISOR_CHIEF:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_CHIEF }); };
        break;
    case HOTKEY_SHOW_ADVISOR_HOUSING:
        def->callback = [] { events::emit(event_show_advisor{ ADVISOR_HOUSING }); };
        break;

    case HOTKEY_SHOW_OVERLAY_WATER:
    case HOTKEY_SHOW_OVERLAY_FIRE:
    case HOTKEY_SHOW_OVERLAY_DAMAGE:
    case HOTKEY_SHOW_OVERLAY_CRIME:
    case HOTKEY_SHOW_OVERLAY_PROBLEMS:
        def->callback = [action = mapping.action] { events::emit(event_hotkey_overlay{ action }); };
        break;

    case HOTKEY_EDITOR_TOGGLE_BATTLE_INFO:
        def->callback = [action = mapping.action] { events::emit(event_editor_toggle_battle_info{ action }); };
        break;
    case HOTKEY_LOAD_FILE:
        def->callback = [action = mapping.action] { events::emit(event_load_city{ action }); };
        break;

    case HOTKEY_SAVE_FILE:
        def->callback = [action = mapping.action] { events::emit(event_save_city{ action }); };
        break;
    case HOTKEY_ROTATE_BUILDING:
        def->callback = [action = mapping.action] { events::emit(event_rotate_building{ action }); };
        break;
    case HOTKEY_CHANGE_BUILDING_VARIANT:
        def->callback = [action = mapping.action] { events::emit(event_change_building_variant{ action }); };
        break;
    case HOTKEY_GO_TO_BOOKMARK_1:
    case HOTKEY_GO_TO_BOOKMARK_2:
    case HOTKEY_GO_TO_BOOKMARK_3:
    case HOTKEY_GO_TO_BOOKMARK_4:
        def->callback = [action = mapping.action] { events::emit(event_goto_bookmark{ action - HOTKEY_GO_TO_BOOKMARK_1 }); };
        break;
    case HOTKEY_SET_BOOKMARK_1:
    case HOTKEY_SET_BOOKMARK_2:
    case HOTKEY_SET_BOOKMARK_3:
    case HOTKEY_SET_BOOKMARK_4:
        def->callback = [action = mapping.action] { events::emit(event_set_bookmark{ action - HOTKEY_SET_BOOKMARK_1 }); };
        break;
    case HOTKEY_CENTER_WINDOW:
        def->callback = [action = mapping.action] { events::emit(event_app_center_screen{ action }); };
        break;
    case HOTKEY_TOGGLE_FULLSCREEN:
        def->callback = [action = mapping.action] { events::emit(event_app_toggle_fullscreen{ action }); };
        break;
    case HOTKEY_SAVE_SCREENSHOT:
        def->action = &data.global_hotkey_state.save_screenshot;
        break;
    case HOTKEY_SAVE_CITY_SCREENSHOT:
        def->action = &data.global_hotkey_state.save_city_screenshot;
        break;

    case HOTKEY_BUILD_VACANT_HOUSE:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_HOUSE_VACANT_LOT }); };
        break;

    case HOTKEY_BUILD_CLEAR_LAND:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_CLEAR_LAND }); };
        break;

    case HOTKEY_BUILD_ROAD:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_ROAD }); };
        break;

    case HOTKEY_BUILD_ARCHITECT:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_ARCHITECT_POST }); };
        break;

    case HOTKEY_BUILD_WALL:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_MUD_WALL }); };
        break;

    case HOTKEY_BUILD_GATEHOUSE:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_MUD_GATEHOUSE }); };
        break;

    case HOTKEY_BUILD_FIREHOUSE:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_FIREHOUSE }); };
        break;

    case HOTKEY_BUILD_GRANARY:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_GRANARY }); };
        break;

    case BUILDING_STORAGE_YARD:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_STORAGE_YARD }); };
        break;

    case HOTKEY_BUILD_BAZAAR:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_BAZAAR }); };
        break;

    case HOTKEY_BUILD_PLAZA:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_PLAZA }); };
        break;

    case HOTKEY_BUILD_GARDENS:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_GARDENS }); };
        break;

    case HOTKEY_BUILD_WATERLIFT:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_WATER_LIFT }); };
        break;

    case HOTKEY_BUILD_CANAL:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_IRRIGATION_DITCH }); };
        break;

    case HOTKEY_BUILD_WATER_SUPPLY:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_WATER_SUPPLY }); };
        break;

    case HOTKEY_BUILD_APOTHECARY:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_APOTHECARY }); };
        break;

    case HOTKEY_BUILD_ROADBLOCK:
        def->callback = [] { events::emit(event_building_mode{ BUILDING_ROADBLOCK }); };
        break;

    case HOTKEY_DEBUG_1_UP:
        def->callback = [action = mapping.action] { events::emit(event_debug_tile_change{ +1 }); };
        def->repeatable = 1;
        break;

    case HOTKEY_DEBUG_1_DOWN:
        def->callback = [action = mapping.action] { events::emit(event_debug_tile_change{ -1 }); };
        def->repeatable = 1;
        break;

    case HOTKEY_DEBUG_RENDER_UP:
        def->callback = [action = mapping.action] { events::emit(event_debug_render_change{ 1 }); };
        def->repeatable = 1;
        break;

    case HOTKEY_DEBUG_RENDER_DOWN:
        def->callback = [action = mapping.action] { events::emit(event_debug_render_change{ -1 }); };
        def->repeatable = 1;
        break;
    default:
        def->action = 0;
    }
}

static void add_arrow(const hotkey_mapping& mapping, bool alt) {
    auto& data = g_hotkey_data;
    e_key key = alt ? mapping.alt.key : mapping.state.key;
    
    if (key == KEY_NONE) {
        return;
    }

    arrow_definition* arrow = &data.arrows.emplace_back();
    arrow->key = key;

    switch (mapping.action) {
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
}

void hotkeys::install(const custom_span<hotkey_mapping> &mappings) {
    auto& data = g_hotkey_data;
    
    data.definitions.clear();
    data.arrows.clear();
    
    // Fixed keys: Escape and Enter
    hotkey_definition &escape_def = data.definitions.emplace_back();

    escape_def.action = &data.hotkey_state.enter_pressed;
    escape_def.key = KEY_ENTER;
    escape_def.modifiers = 0;
    escape_def.repeatable = 0;
    escape_def.value = 1;

    hotkey_definition &enter_def = data.definitions.emplace_back();
    enter_def.action = &data.hotkey_state.escape_pressed;
    enter_def.key = KEY_ESCAPE;
    enter_def.modifiers = 0;
    enter_def.repeatable = 0;
    enter_def.value = 1;

    std::array<e_hotkey_action, 4> arrow_actions = {
        HOTKEY_ARROW_UP,
        HOTKEY_ARROW_DOWN,
        HOTKEY_ARROW_LEFT,
        HOTKEY_ARROW_RIGHT
    };

    for (int i = 0; i < mappings.size(); i++) {
        int action = mappings[i].action;
        const bool is_arrow_action = std::find(arrow_actions.begin(), arrow_actions.end(), action) != arrow_actions.end();
        if (is_arrow_action) {
            add_arrow(mappings[i], false);
            add_arrow(mappings[i], true);
        } else {
            add_definition(mappings[i], false);
            add_definition(mappings[i], true);
        }
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

    if (key == KEY_NONE) {
        return;
    }

    for (auto &arrow: data.arrows) {
        if (arrow.key == key)
            arrow.action(1);
    }

    for (auto &def: data.definitions) {
        if (def.key == key && def.modifiers == modifiers && (!repeat || def.repeatable)) {
            if (def.action) {
                *(def.action) = def.value;
            }

            if (def.callback) {
                def.callback();
            }
        }
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

    for (auto &arrow : data.arrows) {
        if (arrow.key == key)
            arrow.action(0);
    }
}

void hotkey_handle_escape(void) {
    video_stop();
    popup_dialog::show_yesno("#popup_dialog_quit", [] (bool accepted) {
        if (accepted) {
            widget_top_menu_clear_state();
            main_menu_screen::show(/*restart_music*/true);
        } else {
            window_city_show();
        }
    });
}

void hotkey_handle_global_keys() {
    auto& data = g_hotkey_data;

    if (data.global_hotkey_state.save_screenshot) {
        graphics_save_screenshot(SCREENSHOT_DISPLAY);
    } else if (data.global_hotkey_state.save_city_screenshot) {
        graphics_save_screenshot(SCREENSHOT_FULL_CITY);
    }
}
