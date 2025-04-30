#include "hotkeys.h"

#include "game/system.h"
#include "input/hotkey.h"
#include "content/vfs.h"
#include "core/log.h"
#include "js/js_game.h"
#include "core/svector.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_MAPPINGS HOTKEY_MAX_ITEMS * 2

static const char *CONF_HOTKEYS = "hotkeys.conf";

ANK_REGISTER_CONFIG_ITERATOR(config_load_game_hotkeys);
void config_load_game_hotkeys() {
    game_hotkeys::load();
}

namespace game_hotkeys {
    std::array<hotkey_mapping, 128> _hotkeys = { nullptr };
    std::array<hotkey_mapping, 128> _defaults = { nullptr };

    hotkey_mapping arrow_up{"arrow_up", KEY_UP, KEY_MOD_NONE, HOTKEY_ARROW_UP};
    hotkey_mapping arrow_down ("arrow_down", KEY_DOWN, KEY_MOD_NONE, HOTKEY_ARROW_DOWN);
    hotkey_mapping arrow_left ("arrow_left", KEY_LEFT, KEY_MOD_NONE, HOTKEY_ARROW_LEFT);
    hotkey_mapping arrow_right ("arrow_right", KEY_RIGHT, KEY_MOD_NONE, HOTKEY_ARROW_RIGHT);
    hotkey_mapping toggle_pause ("toggle_pause", KEY_P, KEY_MOD_NONE, HOTKEY_TOGGLE_PAUSE);
    hotkey_mapping toggle_overlay ("toggle_overlay", KEY_SPACE, KEY_MOD_NONE, HOTKEY_TOGGLE_OVERLAY);
    hotkey_mapping cycle_legion ("cycle_legion", KEY_L, KEY_MOD_NONE, HOTKEY_CYCLE_LEGION);
    hotkey_mapping increase_game_speed ("increase_game_speed", KEY_PAGEDOWN, KEY_MOD_NONE, HOTKEY_INCREASE_GAME_SPEED, KEY_RIGHTBRACKET, KEY_MOD_NONE);
    hotkey_mapping decrease_game_speed ("decrease_game_speed", KEY_PAGEUP, KEY_MOD_NONE, HOTKEY_DECREASE_GAME_SPEED, KEY_LEFTBRACKET, KEY_MOD_NONE);
    hotkey_mapping rotate_map_left ("rotate_map_left", KEY_HOME, KEY_MOD_NONE, HOTKEY_ROTATE_MAP_LEFT);
    hotkey_mapping rotate_map_right ("rotate_map_right", KEY_END, KEY_MOD_NONE, HOTKEY_ROTATE_MAP_RIGHT);
    hotkey_mapping build_vacant_house ("build_vacant_house", KEY_H, KEY_MOD_NONE, HOTKEY_BUILD_VACANT_HOUSE);
    hotkey_mapping build_clear_land ("build_clear_land", KEY_X, KEY_MOD_NONE, HOTKEY_BUILD_CLEAR_LAND);
    hotkey_mapping build_road ("build_road", KEY_B, KEY_MOD_NONE, HOTKEY_BUILD_ROAD);
    hotkey_mapping build_plaza ("build_plaza", KEY_Z, KEY_MOD_NONE, HOTKEY_BUILD_PLAZA);
    hotkey_mapping build_gardens ("build_gardens", KEY_G, KEY_MOD_NONE, HOTKEY_BUILD_GARDENS);
    hotkey_mapping build_firehouse ("build_firehouse", KEY_F, KEY_MOD_CTRL, HOTKEY_BUILD_FIREHOUSE);
    hotkey_mapping build_architect ("build_architect", KEY_A, KEY_MOD_CTRL, HOTKEY_BUILD_ARCHITECT);
    hotkey_mapping build_doctor ("build_apothecary", KEY_O, KEY_MOD_NONE, HOTKEY_BUILD_APOTHECARY);
    hotkey_mapping build_granary ("build_granary", KEY_N, KEY_MOD_NONE, HOTKEY_BUILD_GRANARY);
    hotkey_mapping build_storage_yard("build_storage_yard", KEY_U, KEY_MOD_NONE, HOTKEY_BUILD_STORAGE_YARD);
    hotkey_mapping build_bazaar ("build_bazaar", KEY_M, KEY_MOD_NONE, HOTKEY_BUILD_BAZAAR);
    hotkey_mapping build_wall ("build_wall", KEY_W, KEY_MOD_CTRL, HOTKEY_BUILD_WALL);
    hotkey_mapping build_gatehouse ("build_gatehouse", KEY_G, KEY_MOD_CTRL, HOTKEY_BUILD_GATEHOUSE);
    hotkey_mapping build_waterlift ("build_waterlift", KEY_V, KEY_MOD_CTRL, HOTKEY_BUILD_WATERLIFT);
    hotkey_mapping build_canal ("build_canal", KEY_V, KEY_MOD_NONE, HOTKEY_BUILD_CANAL);
    hotkey_mapping build_water_supply ("build_water_supply", KEY_T, KEY_MOD_NONE, HOTKEY_BUILD_WATER_SUPPLY);
    hotkey_mapping build_roadblock ("build_roadblock", KEY_L, KEY_MOD_NONE, HOTKEY_BUILD_ROADBLOCK);
    hotkey_mapping show_advisor_labor ("show_advisor_labor", KEY_KP_1, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_LABOR);
    hotkey_mapping show_advisor_labor_alt ("show_advisor_labor_alt", KEY_1, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_LABOR);
    hotkey_mapping show_advisor_military ("show_advisor_military", KEY_KP_2, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_MILITARY, KEY_2, KEY_MOD_NONE);
    hotkey_mapping show_advisor_kingdome ("show_advisor_kingdome", KEY_KP_3, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_KINGDOME, KEY_3, KEY_MOD_NONE);
    hotkey_mapping show_advisor_ratings ("show_advisor_ratings", KEY_KP_4, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_RATINGS, KEY_4);
    hotkey_mapping show_advisor_trade ("show_advisor_trade", KEY_KP_5, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_TRADE, KEY_5);
    hotkey_mapping show_advisor_population ("show_advisor_population", KEY_KP_6, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_POPULATION, KEY_6);
    hotkey_mapping show_advisor_health ("show_advisor_health", KEY_KP_7, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_HEALTH, KEY_7);
    hotkey_mapping show_advisor_education ("show_advisor_education", KEY_KP_8, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_EDUCATION, KEY_8);
    hotkey_mapping show_advisor_entertainment ("show_advisor_entertainment", KEY_KP_9, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_ENTERTAINMENT, KEY_9);
    hotkey_mapping show_advisor_religion ("show_advisor_religion", KEY_KP_0, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_RELIGION, KEY_0);
    hotkey_mapping show_advisor_financial ("show_advisor_financial", KEY_MINUS, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_FINANCIAL);
    hotkey_mapping show_advisor_chief ("show_advisor_chief", KEY_EQUALS, KEY_MOD_NONE, HOTKEY_SHOW_ADVISOR_CHIEF);
    hotkey_mapping show_advisor_housing ("show_advisor_housing");
    hotkey_mapping show_overlay_water ("show_overlay_water", KEY_W, KEY_MOD_NONE, HOTKEY_SHOW_OVERLAY_WATER);
    hotkey_mapping show_overlay_fire ("show_overlay_fire", KEY_F, KEY_MOD_NONE, HOTKEY_SHOW_OVERLAY_FIRE);
    hotkey_mapping show_overlay_damage ("show_overlay_damage", KEY_D, KEY_MOD_NONE, HOTKEY_SHOW_OVERLAY_DAMAGE);
    hotkey_mapping show_overlay_crime ("show_overlay_crime", KEY_C, KEY_MOD_NONE, HOTKEY_SHOW_OVERLAY_CRIME);
    hotkey_mapping show_overlay_problems ("show_overlay_problems", KEY_T, KEY_MOD_NONE, HOTKEY_SHOW_OVERLAY_PROBLEMS);
    hotkey_mapping editor_toggle_battle_info ("editor_toggle_battle_info", KEY_A, KEY_MOD_CTRL, HOTKEY_EDITOR_TOGGLE_BATTLE_INFO);
    hotkey_mapping load_file ("load_file", KEY_O, KEY_MOD_CTRL, HOTKEY_LOAD_FILE);
    hotkey_mapping save_file ("save_file", KEY_S, KEY_MOD_CTRL, HOTKEY_SAVE_FILE);
    hotkey_mapping rotate_building ("rotate_building", KEY_R, KEY_MOD_NONE, HOTKEY_ROTATE_BUILDING);
    hotkey_mapping change_building_variant ("change_building_variant", KEY_R, KEY_MOD_CTRL, HOTKEY_CHANGE_BUILDING_VARIANT);
    hotkey_mapping go_to_bookmark_1 ("go_to_bookmark_1", KEY_F1, KEY_MOD_NONE, HOTKEY_GO_TO_BOOKMARK_1);
    hotkey_mapping go_to_bookmark_2 ("go_to_bookmark_2", KEY_F2, KEY_MOD_NONE, HOTKEY_GO_TO_BOOKMARK_2);
    hotkey_mapping go_to_bookmark_3 ("go_to_bookmark_3", KEY_F3, KEY_MOD_NONE, HOTKEY_GO_TO_BOOKMARK_3);
    hotkey_mapping go_to_bookmark_4 ("go_to_bookmark_4", KEY_F4, KEY_MOD_NONE, HOTKEY_GO_TO_BOOKMARK_4);
    hotkey_mapping set_bookmark_1 ("set_bookmark_1", KEY_F1, KEY_MOD_ALT, HOTKEY_SET_BOOKMARK_1);
    hotkey_mapping set_bookmark_2 ("set_bookmark_2", KEY_F2, KEY_MOD_ALT, HOTKEY_SET_BOOKMARK_2);
    hotkey_mapping set_bookmark_3 ("set_bookmark_3", KEY_F3, KEY_MOD_ALT, HOTKEY_SET_BOOKMARK_3);
    hotkey_mapping set_bookmark_4 ("set_bookmark_4", KEY_F4, KEY_MOD_ALT, HOTKEY_SET_BOOKMARK_4);
    hotkey_mapping center_screen ("center_screen", KEY_F5, KEY_MOD_NONE, HOTKEY_CENTER_WINDOW);
    hotkey_mapping toggle_fullscreen ("toggle_fullscreen", KEY_ENTER, KEY_MOD_ALT, HOTKEY_TOGGLE_FULLSCREEN);
    hotkey_mapping toggle_fullscreen_alt ("toggle_fullscreen_alt", KEY_F6, KEY_MOD_NONE, HOTKEY_TOGGLE_FULLSCREEN);

    hotkey_mapping save_screenshot ("save_screenshot", KEY_F12, KEY_MOD_NONE, HOTKEY_SAVE_SCREENSHOT);
    hotkey_mapping save_city_screenshot("save_city_screenshot", KEY_F12, KEY_MOD_CTRL, HOTKEY_SAVE_CITY_SCREENSHOT);

    hotkey_mapping debug_range1_up("debug_range1_up", KEY_PAGEUP, KEY_MOD_CTRL, HOTKEY_DEBUG_1_UP);
    hotkey_mapping debug_range1_down("debug_range1_down", KEY_PAGEDOWN, KEY_MOD_CTRL, HOTKEY_DEBUG_1_DOWN);
    hotkey_mapping debug_range2_up("debug_range2_up", KEY_PAGEUP, KEY_MOD_ALT, HOTKEY_DEBUG_RENDER_UP);
    hotkey_mapping debug_range2_down("debug_range2_down", KEY_PAGEDOWN, KEY_MOD_ALT, HOTKEY_DEBUG_RENDER_DOWN);

    void set_mapping(bool alt, e_key key, e_key_mode modifiers, e_hotkey_action action);
    void set_layout_mapping(pcstr name, e_key default_key, e_key_mode modifiers, e_hotkey_action action);
}

void game_hotkeys::set_mapping(bool alt, e_key key, e_key_mode modifiers, e_hotkey_action action) {
    hotkey_mapping& mapping = _hotkeys[action];
    
    auto &state = alt ? mapping.alt : mapping.state;

    state.key = key;
    state.modifiers = modifiers;
    mapping.action = action;
}

void game_hotkeys::set_layout_mapping(pcstr name, e_key default_key, e_key_mode modifiers, e_hotkey_action action) {
    e_key key = system_keyboard_key_for_symbol(name);
    if (key == KEY_NONE) {
        logs::info("No key found on layout for: %s", name);
        key = default_key;
    }
    set_mapping(false, key, modifiers, action);
}

void game_hotkeys::init_defaults(void) {
    _hotkeys = _defaults;
}

const hotkey_mapping* game_hotkeys::hotkey_for_action(e_hotkey_action action) {
    return &_hotkeys[action];
}

void game_hotkeys::set_hotkey(const hotkey_mapping &mapping) {
    if (mapping.action < 0 || mapping.action >= HOTKEY_MAX_ITEMS) {
        return;
    }

    _hotkeys[mapping.action].state.key = mapping.state.key;
    _hotkeys[mapping.action].state.modifiers = mapping.state.modifiers;

    _hotkeys[mapping.action].alt.key = mapping.alt.key;
    _hotkeys[mapping.action].alt.modifiers = mapping.alt.modifiers;
}

const hotkey_mapping* game_hotkeys::hotkey_default(e_hotkey_action action) {
    if ((int)action < 0 || action >= HOTKEY_MAX_ITEMS) {
        return nullptr;
    }

    return &_defaults[action];
}

void game_hotkeys::load() {
    init_defaults();
    
    g_config_arch.r_objects("game_hotkeys", [&] (pcstr key, archive arch) {
        auto value = arch.to_array_str();

        if (value.empty()) {
            return;
        }

        auto it = std::find_if(_hotkeys.begin(), _hotkeys.end(), [key] (const hotkey_mapping &m) {
            return m.name == key;
        });

        if (it == _hotkeys.end()) {
            return;
        }

        e_key vkey;
        e_key_mode vmodifiers;

        hotkey_mapping_state* states[] = { &it->state, &it->alt };
        for (size_t i = 0; i < value.size(); ++i) {
            if (key_combination_from_name(value[i].c_str(), vkey, vmodifiers)) {
                states[i]->key = vkey;
                states[i]->modifiers = vmodifiers;
            }
        }        
    });

    install();
}

void game_hotkeys::install() {
    hotkeys::install(make_span(_hotkeys));
}

void game_hotkeys::save() {
    //auto &data = g_config_hotkeys_data;
    //vfs::path fs_file = vfs::content_path(INI_FILENAME);
    //
    //hotkey_install_mapping(data.mappings, data.num_mappings);
    //FILE* fp = vfs::file_open_os(fs_file, "wt");
    //if (!fp) {
    //    logs::error("Unable to write hotkey configuration file %s", INI_FILENAME);
    //    return;
    //}
    //
    //for (int i = 0; i < data.num_mappings; i++) {
    //    const char* key_name = key_combination_name(data.mappings[i].key, data.mappings[i].modifiers);
    //    fprintf(fp, "%s=%s\n", ini_keys[data.mappings[i].action], key_name);
    //}
    //vfs::file_close(fp);
}

hotkey_mapping::hotkey_mapping(pcstr n, e_key k, e_key_mode m, e_hotkey_action a, e_key k1, e_key_mode m1) : name(n), action(a) {
    state.key = k;
    state.modifiers = m;

    alt.key = k1;
    alt.modifiers = m1;

    game_hotkeys::_hotkeys[action] = *this;
    game_hotkeys::_defaults[action] = *this;
}