#pragma once

#include "input/keys.h"
#include "core/xstring.h"
#include "core/custom_span.hpp"

enum e_hotkey_action {
    HOTKEY_NONE = 0,
    HOTKEY_ARROW_UP,
    HOTKEY_ARROW_DOWN,
    HOTKEY_ARROW_LEFT,
    HOTKEY_ARROW_RIGHT,
    HOTKEY_TOGGLE_PAUSE,
    HOTKEY_TOGGLE_OVERLAY,
    HOTKEY_CYCLE_LEGION,
    HOTKEY_INCREASE_GAME_SPEED,
    HOTKEY_DECREASE_GAME_SPEED,
    HOTKEY_ROTATE_MAP_LEFT,
    HOTKEY_ROTATE_MAP_RIGHT,
    HOTKEY_BUILD_CLEAR_LAND,
    HOTKEY_BUILD_VACANT_HOUSE,
    HOTKEY_BUILD_ROAD,
    HOTKEY_BUILD_PLAZA,
    HOTKEY_BUILD_GARDENS,
    HOTKEY_BUILD_PREFECTURE,
    HOTKEY_BUILD_ENGINEERS_POST,
    HOTKEY_BUILD_DOCTOR,
    HOTKEY_BUILD_GRANARY,
    HOTKEY_BUILD_STORAGE_YARD,
    HOTKEY_BUILD_MARKET,
    HOTKEY_BUILD_WALL,
    HOTKEY_BUILD_GATEHOUSE,
    HOTKEY_BUILD_RESERVOIR,
    HOTKEY_BUILD_AQUEDUCT,
    HOTKEY_BUILD_FOUNTAIN,
    HOTKEY_BUILD_ROADBLOCK,
    HOTKEY_SHOW_ADVISOR_LABOR,
    HOTKEY_SHOW_ADVISOR_MILITARY,
    HOTKEY_SHOW_ADVISOR_KINGDOME,
    HOTKEY_SHOW_ADVISOR_RATINGS,
    HOTKEY_SHOW_ADVISOR_TRADE,
    HOTKEY_SHOW_ADVISOR_POPULATION,
    HOTKEY_SHOW_ADVISOR_HEALTH,
    HOTKEY_SHOW_ADVISOR_EDUCATION,
    HOTKEY_SHOW_ADVISOR_ENTERTAINMENT,
    HOTKEY_SHOW_ADVISOR_RELIGION,
    HOTKEY_SHOW_ADVISOR_FINANCIAL,
    HOTKEY_SHOW_ADVISOR_CHIEF,
    HOTKEY_SHOW_ADVISOR_HOUSING,
    HOTKEY_SHOW_OVERLAY_WATER,
    HOTKEY_SHOW_OVERLAY_FIRE,
    HOTKEY_SHOW_OVERLAY_DAMAGE,
    HOTKEY_SHOW_OVERLAY_CRIME,
    HOTKEY_SHOW_OVERLAY_PROBLEMS,
    HOTKEY_EDITOR_TOGGLE_BATTLE_INFO,
    HOTKEY_LOAD_FILE,
    HOTKEY_SAVE_FILE,
    HOTKEY_ROTATE_BUILDING,
    HOTKEY_CHANGE_BUILDING_VARIANT,
    HOTKEY_GO_TO_BOOKMARK_1,
    HOTKEY_GO_TO_BOOKMARK_2,
    HOTKEY_GO_TO_BOOKMARK_3,
    HOTKEY_GO_TO_BOOKMARK_4,
    HOTKEY_SET_BOOKMARK_1,
    HOTKEY_SET_BOOKMARK_2,
    HOTKEY_SET_BOOKMARK_3,
    HOTKEY_SET_BOOKMARK_4,
    HOTKEY_CENTER_WINDOW,
    HOTKEY_TOGGLE_FULLSCREEN,
    HOTKEY_RESERVED_1,
    HOTKEY_RESERVED_2,
    HOTKEY_RESERVED_3,
    HOTKEY_SAVE_SCREENSHOT,
    HOTKEY_SAVE_CITY_SCREENSHOT,
    //
    HOTKEY_DEBUG_1_UP,
    HOTKEY_DEBUG_1_DOWN,
    HOTKEY_DEBUG_RENDER_UP,
    HOTKEY_DEBUG_RENDER_DOWN,
    //
    HOTKEY_MAX_ITEMS
};

struct hotkey_mapping {
    xstring name;
    e_key key = KEY_NONE;
    e_key_mode modifiers = KEY_MOD_NONE;
    e_hotkey_action action = HOTKEY_NONE;

    hotkey_mapping() : name("unknown") {}
    hotkey_mapping(pcstr n, e_key k = KEY_NONE, e_key_mode m = KEY_MOD_NONE, e_hotkey_action a = HOTKEY_NONE);
};

namespace game_hotkeys {
    custom_span<hotkey_mapping *> all();
    hotkey_mapping *find(const xstring &name);

    void load();
    void save(void);
    void init_defaults();

 /**
 * Get default mapping for action
 * @param action Action
 * @return Mapping, may be an empty mapping. Only returns NULL on invalid input
 */
    const hotkey_mapping *hotkey_default(e_hotkey_action action);

    const hotkey_mapping *hotkey_for_action(e_hotkey_action action);

    void set_hotkey(const hotkey_mapping &mapping);
    void install();
}