#include "config.h"

#include "building/building_menu.h"
#include "core/game_environment.h"
#include "core/string.h"
#include "core/log.h"
#include "city/city.h"
#include "game/settings.h"
#include "game/game.h"
#include "game/system.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "game/game_config.h"
#include "content/dir.h"
#include "io/gamefiles/lang.h"
#include "translation/translation.h"
#include "window/hotkey_config.h"
#include "window/plain_message_dialog.h"
#include "scenario/scenario.h"
#include "window/select_list.h"
#include "empire/empire_city.h"

#include <string.h>
#include <numeric>

#define MAX_LANGUAGE_DIRS 20

#define FIRST_BUTTON_Y 72
#define BUTTON_SPACING 24
#define TEXT_Y_OFFSET 4

#define CHECKBOX_CHECK_SIZE 20
#define CHECKBOX_HEIGHT 20
#define CHECKBOX_WIDTH 560

#define NUM_VISIBLE_ITEMS 15

#define ITEM_Y_OFFSET 60
#define ITEM_HEIGHT 24

constexpr int CONFIG_STRING_VALUE_MAX = 64;
struct window_config_ext_data_t {
    int focus_button;
    int language_focus_button;
    int bottom_focus_button;
    int page_focus_button;
    int page;
    int starting_option;
    void (*close_callback)(void);

    struct {
        int original_value;
        int new_value;
        std::function<int(int key)> change_action;
        std::function<int()> get_value;
    } config_values[CONFIG_MAX_ENTRIES];

    struct {
        xstring original_value;
        xstring new_value;
        int (*change_action)(int key);
    } config_string_values[CONFIG_STRING_MAX_ENTRIES];

    svector<xstring, MAX_LANGUAGE_DIRS> language_options;
    svector<bstring64, MAX_LANGUAGE_DIRS> language_options_utf8;
    int selected_language_option;
};

window_config_ext_data_t g_window_config_ext_data;

static void toggle_switch(int id, int param2);
static void toggle_god_disabled(int id, int param2);
static void toggle_city_option(int id, int param2);
static void button_language_select(int param1, int param2);
static void button_reset_defaults(int param1, int param2);
static void button_hotkeys(int param1, int param2);
static void button_close(int save, int param2);
static void button_page(int param1, int param2);
static void toggle_building(int id, int param2);
static void toggle_resource(int id, int param2);
// static int config_change_zoom(int key);
static int config_change_basic(int key);
static int config_change_string_basic(int key);
static int config_change_string_language(int key);


static void toggle_switch_t(int key, int param2) {
    auto &data = g_window_config_ext_data;
    int option = key & 0xff;
    data.config_values[option].new_value = !data.config_values[option].new_value;
}

static generic_button checkbox_buttons[] = {
    {20, 72, 20, 20, toggle_switch_t, button_none, 0x1000, TR_CONFIG_FIX_IMMIGRATION_BUG},
    {20, 96, 20, 20, toggle_switch_t, button_none, 0x1001, TR_CONFIG_FIX_100_YEAR_GHOSTS},
    {20, 120, 20, 20, toggle_switch_t, button_none, 0x1002, TR_CONFIG_FIX_EDITOR_EVENTS},
    {20, 144, 20, 20, toggle_switch_t, button_none, 0x1003, TR_CONFIG_SIDEBAR_INFO},
    {20, 168, 20, 20, toggle_switch_t, button_none, 0x1004, TR_CONFIG_SHOW_INTRO_VIDEO},
    {20, 192, 20, 20, toggle_switch_t, button_none, 0x1005, TR_CONFIG_SMOOTH_SCROLLING},
    {20, 216, 20, 20, toggle_switch_t, button_none, 0x1006, TR_CONFIG_DRAW_WALKER_WAYPOINTS},
    {20, 240, 20, 20, toggle_switch_t, button_none, 0x1007, TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE},
    {20, 264, 20, 20, toggle_switch_t, button_none, 0x1008, TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE},
    {20, 288, 20, 20, toggle_switch_t, button_none, 0x1009, TR_CONFIG_SHOW_CONSTRUCTION_SIZE},
    {20, 312, 20, 20, toggle_switch_t, button_none, 0x100A, TR_CONFIG_ZOOM_STEPPED},
    {20, 336, 20, 20, toggle_switch_t, button_none, 0x100B, TR_CONFIG_COMPLETE_RATING_COLUMNS},
    {20, 360, 20, 20, toggle_switch_t, button_none, 0x100C, TR_CONFIG_HIGHLIGHT_LEGIONS},
    {20, 384, 20, 20, toggle_switch_t, button_none, 0x100D, TR_CONFIG_ROTATE_MANUALLY},

    //
    {20, 72, 20, 20, toggle_switch, button_none, CONFIG_UI_HIGHLIGHT_TOP_MENU_HOVER, TR_CONFIG_HIGHLIGHT_TOP_MENU_HOVER},
    {20, 96, 20, 20, toggle_switch, button_none, CONFIG_UI_EMPIRE_CITY_OLD_NAMES, TR_CONFIG_EMPIRE_CITY_OLD_NAMES},
    {20, 120, 20, 20, toggle_switch, button_none, CONFIG_UI_DRAW_FPS, TR_CONFIG_DRAW_FPS},

    //
    {20, 72, 20, 20, toggle_switch, button_none, CONFIG_UI_HIDE_NEW_GAME_TOP_MENU, TR_CONFIG_HIDE_NEW_GAME_TOP_MENU},
    {20, 96, 20, 20, toggle_switch, button_none, CONFIG_UI_DRAW_CLOUD_SHADOWS, TR_CONFIG_DRAW_CLOUD_SHADOWS},
    {20, 122, 20, 20, toggle_switch, button_none, CONFIG_GP_CHANGE_SAVE_YEAR_KINGDOME_RATING, TR_CONFIG_SAVE_YEAR_KINGDOME_RATING},

    // 
    {20, 120, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_GRANDFESTIVAL, TR_CONFIG_GRANDFESTIVAL},
    {20, 144, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_JEALOUS_GODS, TR_CONFIG_JEALOUS_GODS},
    {20, 168, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_GLOBAL_LABOUR, TR_CONFIG_GLOBAL_LABOUR},
    {20, 192, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_SCHOOL_WALKERS, TR_CONFIG_SCHOOL_WALKERS},
    {20, 216, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_RETIRE_AT_60, TR_CONFIG_RETIRE_AT_60},
    {20, 240, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_FIXED_WORKERS, TR_CONFIG_FIXED_WORKERS},
    {20, 264, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_EXTRA_FORTS, TR_CONFIG_EXTRA_FORTS},
    {20, 288, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_WOLVES_BLOCK, TR_CONFIG_WOLVES_BLOCK},
    {20, 312, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_DYNAMIC_GRANARIES, TR_CONFIG_DYNAMIC_GRANARIES},
    {20, 336, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_MORE_STOCKPILE, TR_CONFIG_MORE_STOCKPILE},
    {20, 360, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_NO_BUYER_DISTRIBUTION, TR_CONFIG_NO_BUYER_DISTRIBUTION},
    //
    {20, 72, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_IMMEDIATELY_DELETE_BUILDINGS, TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS},
    {20, 96, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD, TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD},
    {20, 120, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_GRANARIES_GET_DOUBLE, TR_CONFIG_GRANARIES_GET_DOUBLE},
    {20, 144, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_TOWER_SENTRIES_GO_OFFROAD, TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD},
    {20, 168, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_FARMS_DELIVER_CLOSE, TR_CONFIG_FARMS_DELIVER_CLOSE},
    {20, 192, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_DELIVER_ONLY_TO_ACCEPTING_GRANARIES, TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES},
    {20, 216, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_ALL_HOUSES_MERGE, TR_CONFIG_ALL_HOUSES_MERGE},
    {20, 240, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_WINE_COUNTS_IF_OPEN_TRADE_ROUTE, TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE},
    {20, 264, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_RANDOM_COLLAPSES_TAKE_MONEY, TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY},
    {20, 288, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_MULTIPLE_BARRACKS, TR_CONFIG_MULTIPLE_BARRACKS},
    {20, 312, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_WAREHOUSES_DONT_ACCEPT, TR_CONFIG_NOT_ACCEPTING_WAREHOUSES},
    {20, 336, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_HOUSES_DONT_EXPAND_INTO_GARDENS, TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS},
    {20, 360, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_FIREMAN_RETUNING, TR_CONFIG_FIREMAN_RETURNING},
    {20, 384, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_CART_SPEED_QUANTITY, TR_CONFIG_CART_SPEED_DEPENDS_QUANTITY},
    //
    {20, 72, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_CITIZEN_ROAD_OFFSET, TR_CONFIG_CH_CITIZEN_ROAD_OFFSET},
    {20, 96, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_WORK_CAMP_ONE_WORKER_PER_MONTH, TR_CONFIG_CH_WORK_CAMP_ONE_WORKER_PER_MONTH},
    {20, 120, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_CLAY_PIT_FIRE_RISK_REDUCED, TR_CONFIG_CH_CLAY_PIT_FIRE_RISK_REDUCED},
    {20, 144, 20, 20, toggle_city_option, button_none, CONFIG_GP_CH_CITY_HAS_ANIMALS, TR_CONFIG_CITY_HAS_ANIMALS},
    {20, 168, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_GOLDMINE_TWICE_PRODUCTION, TR_CONFIG_GOLDMINE_TWICE_PRODUCTION},
    {20, 192, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM, TR_CONFIG_NEW_TAX_COLLECTION_SYSTEM},
    {20, 216, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_SMALL_HUT_NIT_CREATE_EMIGRANT, TR_CONFIG_SMALL_HUT_NOT_CREATE_EMIGRANT},
    {20, 240, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_DELIVERY_BOY_GOES_TO_MARKET_ALONE, TR_CONFIG_DELIVERY_BOY_GOES_TO_MARKET_ALONE},
    {20, 264, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_RELIGION_COVERAGE_INFLUENCE_SENTIMENT, TR_CONFIG_RELIGION_COVERAGE_INFLUENCE_SENTIMENT},
    {20, 288, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_MONUMENTS_INFLUENCE_SENTIMENT, TR_CONFIG_MONUMENTS_INFLUENCE_SENTIMENT},
    {20, 312, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_WELL_RADIUS_DEPENDS_MOISTURE, TR_CONFIG_WELL_RADIUS_DEPENDS_MOISTURE},
    {20, 336, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_ENTER_POINT_ON_NEAREST_TILE, TR_CONFIG_ENTER_POINT_ON_NEAREST_TILE},
    {20, 360, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_FISHING_WHARF_SPAWN_BOATS, TR_CONFIG_FISHING_WHARF_SPAWN_BOATS},
    {20, 384, 20, 20, toggle_city_option, button_none, CONFIG_GP_CH_FLOTSAM_ENABLED, TR_CONFIG_CITY_FLOTSAM_ENABLED},

    //
    {20, 72, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_COPPER_NEAR_MOUNTAINS, TR_CONFIG_COPPER_NEAR_MOUNTAINS},
    {20, 96, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_RECRUITER_NOT_NEED_FORTS, TR_CONFIG_RECRUITER_NOT_NEED_FORTS},
    {20, 120, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_BUILDING_CLOSEST_ROAD, TR_CONFIG_BUILDING_CLOSEST_ROAD},
    {20, 144, 20, 20, toggle_switch, button_none, CONFIG_GP_CH_FLOODPLAIN_RANDOM_GROW, TR_CONFIG_FLOODPLAIN_RANDOM_GROW},
    
    // GODS
    {20, 72, 20, 20,  toggle_god_disabled, button_none, CONFIG_GP_CH_GOD_OSIRIS_DISABLED, TR_CONFIG_GOD_OSIRIS_DISABLED},
    {20, 96, 20, 20,  toggle_god_disabled, button_none, CONFIG_GP_CH_GOD_RA_DISABLED, TR_CONFIG_GOD_RA_DISABLED},
    {20, 120, 20, 20, toggle_god_disabled, button_none, CONFIG_GP_CH_GOD_PTAH_DISABLED, TR_CONFIG_GOD_PTAH_DISABLED},
    {20, 144, 20, 20, toggle_god_disabled, button_none, CONFIG_GP_CH_GOD_SETH_DISABLED, TR_CONFIG_GOD_SETH_DISABLED},
    {20, 168, 20, 20, toggle_god_disabled, button_none, CONFIG_GP_CH_GOD_BAST_DISABLED, TR_CONFIG_GOD_BAST_DISABLED},

    //
    {20, 72, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_WOOD_CUTTER, TR_CONFIG_BUILDING_WOOD_CUTTER},
    {20, 96, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_COPPER_MINE, TR_CONFIG_BUILDING_COPPE_MINE},
    {20, 120, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_REED_GATHERER, TR_CONFIG_BUILDING_REED_GATHERER},
    {20, 144, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_PAPYRUS_MAKER, TR_CONFIG_BUILDING_PAPYRUS_MAKER},
    {20, 168, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_SCRIBAL_SCHOOL, TR_CONFIG_BUILDING_SCRIBAL_SCHOOL},
    {20, 192, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_SHIPYARD, TR_CONFIG_BUILDING_SHIPYARD},
    {20, 216, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_FISHING_WHARF, TR_CONFIG_BUILDING_FISHING_WHARF},
    {20, 240, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_CHICKPEAS_FARM, TR_CONFIG_BUILDING_CHICKPEAS_FARM},
    {20, 264, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_LETTUCE_FARM, TR_CONFIG_BUILDING_LETTUCE_FARM},
    {20, 288, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_POMEGRANATES_FARM, TR_CONFIG_BUILDING_POMEGRANATES_FARM},
    {20, 312, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_FIGS_FARM, TR_CONFIG_BUILDING_FIGS_FARM},
    {20, 336, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_GRAIN_FARM, TR_CONFIG_BUILDING_GRAIN_FARM},
    {20, 360, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_CATTLE_RANCH, TR_CONFIG_BUILDING_CATTLE_RANCH},
    {20, 384, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_BRICKS_WORKSHOP, TR_CONFIG_BUILDING_BRICKS_WORKSHOP},
    //
    {20, 72, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_WORK_CAMP, TR_CONFIG_BUILDING_WORK_CAMP},
    {20, 96, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_GOLD_MINE, TR_CONFIG_BUILDING_GOLD_MINE},
    {20, 120, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_QUARRY_SANDSTONE, TR_CONFIG_BUILDING_QUARRY_SANDSTONE},
    {20, 144, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_QUARRY_GRANITE, TR_CONFIG_BUILDING_QUARRY_GRANITE},
    {20, 168, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_QUARRY_STONE, TR_CONFIG_BUILDING_QUARRY_STONE},
    {20, 192, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_QUARRY_LIMESTONE, TR_CONFIG_BUILDING_QUARRY_LIMESTONE},
    {20, 216, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_CLAY_PIT, TR_CONFIG_BUILDING_CLAY_PIT},
    {20, 240, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_WEAPONSMITH, TR_CONFIG_BUILDING_WEAPONSMITH},
    {20, 264, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_RECRUTER, TR_CONFIG_BUILDING_RECRUTER},
    {20, 288, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_SMALL_MASTABA, TR_CONFIG_BUILDING_SMALL_MASTABA},
    {20, 312, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_BRICKLAYERS, TR_CONFIG_BUILDING_BRICKLAYERS},
    {20, 336, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_BOOTH, TR_CONFIG_BUILDING_BOOTH},
    {20, 360, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_BANDSTAND, TR_CONFIG_BUILDING_BANDSTAND},
    {20, 384, 20, 20, toggle_building, button_none, CONFIG_GP_CH_BUILDING_MEDIUM_MASTABA, TR_CONFIG_BUILDING_MEDIUM_MASTABA },
    //

    //
    {20, 72, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_TIMBER, TR_CONFIG_RESOURCE_TIMBER},
    {20, 96, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_COPPER, TR_CONFIG_RESOURCE_COPPER},
    {20, 120, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_REED, TR_CONFIG_RESOURCE_REED},
    {20, 144, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_PAPYRUS, TR_CONFIG_RESOURCE_PAPYRUS},
    {20, 168, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_FISH, TR_CONFIG_RESOURCE_FISH},
    {20, 192, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_CHICKPEAS, TR_CONFIG_RESOURCE_CHICKPEAS},
    {20, 216, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_POMEGRANADES, TR_CONFIG_RESOURCE_POMEGRANADES},
    {20, 240, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_LETTUCE, TR_CONFIG_RESOURCE_LETTUCE},
    {20, 264, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_FIGS, TR_CONFIG_RESOURCE_FIGS},
    {20, 288, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_GRAIN, TR_CONFIG_RESOURCE_GRAIN},
    {20, 312, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_MEAT, TR_CONFIG_RESOURCE_MEAT},
    {20, 336, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_BRICKS, TR_CONFIG_RESOURCE_BRICKS},
    {20, 360, 20, 20, toggle_resource, button_none, CONFIG_GP_CH_RESOURCE_CLAY, TR_CONFIG_RESOURCE_CLAY},
};

static int options_per_page[] = {13, 4, 3, 14, 14, 14, 4, 5, 14, 14, 13};

static generic_button language_button = {120, 50, 200, 24, button_language_select, button_none, 0, TR_CONFIG_LANGUAGE_LABEL};

static generic_button bottom_buttons[]= {
    {250, 436, 150, 30, button_reset_defaults, button_none, 0, TR_BUTTON_RESET_DEFAULTS},
    {410, 436, 100, 30, button_close, button_none, 0, TR_BUTTON_CANCEL},
    {520, 436, 100, 30, button_close, button_none, 1, TR_BUTTON_OK},
    {20, 436, 180, 30, button_hotkeys, button_none, 0, TR_BUTTON_CONFIGURE_HOTKEYS}
};

static generic_button page_buttons[] = {
    {20, 16, 25, 25, button_page, button_none, 0, TR_BUTTON_PREV},
    {50, 16, 25, 25, button_page, button_none, 1, TR_BUTTON_NEXT}
};

static int page_names[] = {
    TR_CONFIG_HEADER_GAMEPLAY_CHANGES,
    TR_CONFIG_HEADER_UI_CHANGES, // 14
    TR_CONFIG_HEADER_UI_CHANGES, // 3
    TR_CONFIG_HEADER_GAMEPLAY_CHANGES, // 14
    TR_CONFIG_HEADER_GAMEPLAY_CHANGES, // 14
    TR_CONFIG_HEADER_GAMEPLAY_CHANGES,  // 14
    TR_CONFIG_HEADER_BUILDING_CHANGES, // 4
    TR_CONFIG_HEADER_GODS_CHANGES,  // 5
    TR_CONFIG_HEADER_BUILDING_CHANGES, // 14
    TR_CONFIG_HEADER_BUILDING_CHANGES, // 13
    TR_CONFIG_HEADER_RESOURCE_CHANGES, // 13
};

static void set_language(int index) {
    auto& data = g_window_config_ext_data;
    const char* dir = (index == 0 ? "" : data.language_options_utf8[index]);
    data.config_string_values[CONFIG_STRING_UI_LANGUAGE_DIR].new_value = dir;

    data.selected_language_option = index;
}

static void cancel_values(void) {
    auto& data = g_window_config_ext_data;
    for (int i = 0; i < CONFIG_MAX_ENTRIES; i++) {
        data.config_values[i].new_value = data.config_values[i].original_value;
    }

    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
        data.config_string_values[i].new_value = data.config_string_values[i].original_value; // memcpy required to fix warning on Switch build
    }
}

static int config_changed(e_config_key key) {
    auto& data = g_window_config_ext_data;
    return data.config_values[key].original_value != data.config_values[key].new_value;
}

static int config_string_changed(int key) {
    auto& data = g_window_config_ext_data;
    return data.config_string_values[key].original_value != data.config_string_values[key].new_value;
}

static int config_change_basic(int key) {
    auto& data = g_window_config_ext_data;
    g_ankh_config.set((e_config_key)key, data.config_values[key].new_value);
    data.config_values[key].original_value = data.config_values[key].new_value;
    return 1;
}

template<typename T>
static int config_change_basic_t(int key, const T& t) {
    auto &data = g_window_config_ext_data;
    g_ankh_config.settings.set_bool(t.name, data.config_values[key].new_value);
    data.config_values[key].original_value = data.config_values[key].new_value;
    return 1;
}

static int config_change_string_basic(int key) {
    auto& data = g_window_config_ext_data;
    g_ankh_config.set((e_config_str)key, data.config_string_values[key].new_value);
    data.config_string_values[key].original_value = data.config_string_values[key].new_value;

    return 1;
}

static int config_change_string_language(int key) {
    auto& data = g_window_config_ext_data;
    g_ankh_config.set(CONFIG_STRING_UI_LANGUAGE_DIR, data.config_string_values[key].new_value);
    if (!game_reload_language()) {
        // Notify user that language dir is invalid and revert to previously selected
        window_plain_message_dialog_show(TR_INVALID_LANGUAGE_TITLE, TR_INVALID_LANGUAGE_MESSAGE);
        g_ankh_config.set(CONFIG_STRING_UI_LANGUAGE_DIR, data.config_string_values[key].original_value);
        game_reload_language();
        return 0;
    }
    data.config_string_values[key].original_value = data.config_string_values[key].new_value;
    return 1;
}

static bool apply_changed_configs() {
    auto& data = g_window_config_ext_data;
    for (int i = 0; i < CONFIG_MAX_ENTRIES; ++i) {
        if (config_changed((e_config_key)i)) {
            if (!data.config_values[i].change_action)
                logs::error("Change action is not available for index: %d", i);
            else if (!data.config_values[i].change_action(i))
                return false;
        }
    }
    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; ++i) {
        if (config_string_changed(i)) {
            if (!data.config_string_values[i].change_action(i))
                return false;
        }
    }
    return true;
}

static void button_hotkeys_goback() {
}

static void button_hotkeys(int param1, int param2) {
    window_hotkey_config_show(button_hotkeys_goback);
}

static void button_language_select(int param1, int param2) {
    auto& data = g_window_config_ext_data;
    window_select_list_show_text(screen_dialog_offset_x() + language_button.x + language_button.width - 10,
                                 screen_dialog_offset_y() + 45,
                                 make_span(data.language_options.data(), data.language_options.size()),
                                 set_language);
}

static void button_reset_defaults(int param1, int param2) {
    auto& data = g_window_config_ext_data;

    for (int i = 0; i < CONFIG_MAX_ENTRIES; ++i) {
        data.config_values[i].new_value = config_get_default_value((e_config_key)i);
    }
    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; ++i) {
        data.config_string_values[i].new_value = config_get_default_string_value((e_config_key)i);
    }
    set_language(0);
}
static void button_close(int save, int param2) {
    if (!save) {
        cancel_values();
        window_go_back();
        return;
    }

    if (apply_changed_configs()) {
        window_go_back();
    }
}
static void button_page(int param1, int param2) {
    auto& data = g_window_config_ext_data;
    if (param1) {
        data.page++;
        if (data.page >= std::size(options_per_page))
            data.page = 0;

    } else {
        data.page--;
        if (data.page < 0) {
            data.page = (int)std::size(options_per_page) - 1;
        }
    }

    data.starting_option = 0;
    for (int i = 0; i < data.page; i++) {
        data.starting_option += options_per_page[i];
    }
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_window_config_ext_data;
    const mouse* m_dialog = mouse_in_dialog(m);
    bool mouse_button = false;

    mouse_button |= !!generic_buttons_min_handle_mouse(m_dialog, {0, 0}, checkbox_buttons, data.starting_option + options_per_page[data.page], &data.focus_button, data.starting_option);
    mouse_button |= !!generic_buttons_handle_mouse(m_dialog, {0, 0}, bottom_buttons, (int)std::size(bottom_buttons), &data.bottom_focus_button);
    mouse_button |= !!generic_buttons_handle_mouse(m_dialog, {0, 0}, page_buttons, (int)std::size(page_buttons), &data.page_focus_button);
    mouse_button |= !!generic_buttons_handle_mouse(m_dialog, {0, 0}, &language_button, 1, &data.language_focus_button);

    if (!mouse_button && (m->right.went_up || h->escape_pressed)) {
        if (data.close_callback) {
            data.close_callback();
        }
        window_go_back();
    }
}

static void toggle_god_disabled(int key, int param2) {
    auto& data = g_window_config_ext_data;
    data.config_values[key].new_value = 1 - data.config_values[key].new_value;

    e_god god = (e_god)(key - CONFIG_GP_CH_GOD_OSIRIS_DISABLED);
    bool known = !data.config_values[key].new_value;
    building_menu_update_gods_available(god, known);
    g_city.religion.set_god_known(god, known ? GOD_STATUS_KNOWN : GOD_STATUS_UNKNOWN);
}

static void toggle_city_option(int key, int param2) {
    switch (key) {
    case CONFIG_GP_CH_CITY_HAS_ANIMALS: g_scenario.env.has_animals = !g_scenario.env.has_animals; break;
    case CONFIG_GP_CH_FLOTSAM_ENABLED: g_scenario.env.flotsam_enabled = !g_scenario.env.flotsam_enabled; break;
    }
}

static void toggle_building(int id, int param2) {
    e_building_type type = BUILDING_NONE;
    switch (id) {
    case CONFIG_GP_CH_BUILDING_WOOD_CUTTER: type = BUILDING_WOOD_CUTTERS; break;
    case CONFIG_GP_CH_BUILDING_COPPER_MINE: type = BUILDING_COPPER_MINE; break;
    case CONFIG_GP_CH_BUILDING_REED_GATHERER: type = BUILDING_REED_GATHERER; break;
    case CONFIG_GP_CH_BUILDING_PAPYRUS_MAKER: type = BUILDING_PAPYRUS_WORKSHOP; break;
    case CONFIG_GP_CH_BUILDING_SCRIBAL_SCHOOL: type = BUILDING_SCRIBAL_SCHOOL; break;
    case CONFIG_GP_CH_BUILDING_SHIPYARD: type = BUILDING_SHIPWRIGHT; break;
    case CONFIG_GP_CH_BUILDING_FISHING_WHARF: type = BUILDING_FISHING_WHARF; break;
    case CONFIG_GP_CH_BUILDING_CHICKPEAS_FARM: type = BUILDING_CHICKPEAS_FARM; break;
    case CONFIG_GP_CH_BUILDING_LETTUCE_FARM: type = BUILDING_LETTUCE_FARM; break;
    case CONFIG_GP_CH_BUILDING_POMEGRANATES_FARM: type = BUILDING_POMEGRANATES_FARM; break;
    case CONFIG_GP_CH_BUILDING_FIGS_FARM: type = BUILDING_FIGS_FARM; break;
    case CONFIG_GP_CH_BUILDING_GRAIN_FARM: type = BUILDING_GRAIN_FARM; break;
    case CONFIG_GP_CH_BUILDING_CATTLE_RANCH: type = BUILDING_CATTLE_RANCH; break;
    case CONFIG_GP_CH_BUILDING_BRICKS_WORKSHOP: type = BUILDING_BRICKS_WORKSHOP; break;
    case CONFIG_GP_CH_BUILDING_WORK_CAMP: type = BUILDING_WORK_CAMP; break;
    case CONFIG_GP_CH_BUILDING_GOLD_MINE: type = BUILDING_GOLD_MINE; break;
    case CONFIG_GP_CH_BUILDING_QUARRY_SANDSTONE: type = BUILDING_SANDSTONE_QUARRY; break;
    case CONFIG_GP_CH_BUILDING_QUARRY_GRANITE: type = BUILDING_GRANITE_QUARRY; break;
    case CONFIG_GP_CH_BUILDING_QUARRY_STONE: type = BUILDING_STONE_QUARRY; break;
    case CONFIG_GP_CH_BUILDING_QUARRY_LIMESTONE: type = BUILDING_LIMESTONE_QUARRY; break;
    case CONFIG_GP_CH_BUILDING_CLAY_PIT: type = BUILDING_CLAY_PIT; break;
    case CONFIG_GP_CH_BUILDING_BOOTH: type = BUILDING_BOOTH; break;
    case CONFIG_GP_CH_BUILDING_BANDSTAND: type = BUILDING_BANDSTAND; break;
    case CONFIG_GP_CH_BUILDING_WEAPONSMITH: type = BUILDING_WEAPONSMITH; break;
    case CONFIG_GP_CH_BUILDING_RECRUTER: type = BUILDING_RECRUITER; break;
    case CONFIG_GP_CH_BUILDING_SMALL_MASTABA: type = BUILDING_SMALL_MASTABA; break;
    case CONFIG_GP_CH_BUILDING_BRICKLAYERS: type = BUILDING_BRICKLAYERS_GUILD; break;
    default:
        return;
    }

    bool can_build = building_menu_is_building_enabled(type);
    building_menu_toggle_building(type, !can_build);
    building_menu_invalidate();
}

static void toggle_resource(int id, int param2) {
    e_resource resource = RESOURCE_NONE;
    switch (id) {
    case CONFIG_GP_CH_RESOURCE_TIMBER: resource = RESOURCE_TIMBER; break;
    case CONFIG_GP_CH_RESOURCE_COPPER: resource = RESOURCE_COPPER; break;
    case CONFIG_GP_CH_RESOURCE_REED: resource = RESOURCE_REEDS; break;
    case CONFIG_GP_CH_RESOURCE_PAPYRUS: resource = RESOURCE_PAPYRUS; break;
    case CONFIG_GP_CH_RESOURCE_FISH: resource = RESOURCE_FISH; break;
    case CONFIG_GP_CH_RESOURCE_CHICKPEAS: resource = RESOURCE_CHICKPEAS; break;
    case CONFIG_GP_CH_RESOURCE_LETTUCE: resource = RESOURCE_LETTUCE; break;
    case CONFIG_GP_CH_RESOURCE_POMEGRANADES: resource = RESOURCE_POMEGRANATES; break;
    case CONFIG_GP_CH_RESOURCE_FIGS: resource = RESOURCE_FIGS; break;
    case CONFIG_GP_CH_RESOURCE_GRAIN: resource = RESOURCE_GRAIN; break;
    case CONFIG_GP_CH_RESOURCE_MEAT: resource = RESOURCE_MEAT; break;
    case CONFIG_GP_CH_RESOURCE_BRICKS: resource = RESOURCE_BRICKS; break;
    case CONFIG_GP_CH_RESOURCE_CLAY: resource = RESOURCE_CLAY; break;
    default:
        return;
    }

    bool can_produce = !g_city.can_produce_resource(resource);
    g_city.set_produce_resource(resource, can_produce);

    if (resource == RESOURCE_FISH) {
        if (can_produce) {
            g_city.fishing_points.reset();
        } else {
            g_city.fishing_points.clear();
        }
    }
}

static void toggle_switch(int key, int param2) {
    auto& data = g_window_config_ext_data;
    data.config_values[key].new_value = !data.config_values[key].new_value;

    switch (key) {
    case CONFIG_UI_EMPIRE_CITY_OLD_NAMES: 
        g_settings.city_names_style = data.config_values[key].new_value;
        break;
    }
}

static void init(void (*close_callback)()) {
    auto& data = g_window_config_ext_data;
    data.page = 0;
    data.starting_option = 0;
    data.close_callback = close_callback;

    auto features = game_features::features();
    for (int i = 0; i < features.size(); ++i) {
        data.config_values[i].get_value = [i] () -> int { return game_features::features()[i]->to_bool(); };
    }

    for (int i = 0; i < std::size(checkbox_buttons); i++) {
        int parameter1 = checkbox_buttons[i].parameter1;
        int index = parameter1 < 0xff ? parameter1 : i;
        e_config_key key = (e_config_key)parameter1;
        const bool value = (parameter1 < 0xff) ? g_ankh_config.get(key) : data.config_values[index].get_value();
        data.config_values[index].original_value = value;
        data.config_values[index].new_value = value;
        data.config_values[index].change_action = config_change_basic;
    }

    for (int i = 0; i < features.size(); ++i) {
        data.config_values[i].change_action = [i] (int key) -> int { return config_change_basic_t(key, *game_features::features()[i]); };
    }

    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
        const xstring value = g_ankh_config.get((e_config_str)i);
        data.config_string_values[i].original_value = value;
        data.config_string_values[i].new_value = value;
    }
    //    data.config_values[CONFIG_UI_ZOOM].change_action = config_change_zoom;
    data.config_string_values[0].change_action = config_change_string_language;

    data.language_options.clear();
    data.language_options_utf8.clear();

    data.language_options.push_back( (pcstr)translation_for(TR_CONFIG_LANGUAGE_DEFAULT)) ;
    data.language_options_utf8.push_back("");

    const dir_listing* subdirs = vfs::dir_find_all_subdirectories(nullptr);
    for (int i = 0; i < subdirs->num_files; i++) {
        if (!data.language_options.full() && lang_dir_is_valid(subdirs->files[i])) {
            data.language_options_utf8.push_back(subdirs->files[i]);

            bstring256 buffer;
            encoding_from_utf8(subdirs->files[i], (uint8_t*)buffer.data(), CONFIG_STRING_VALUE_MAX);
            data.language_options.push_back( buffer.c_str() );
            if (data.config_string_values[CONFIG_STRING_UI_LANGUAGE_DIR].original_value == subdirs->files[i]) {
                data.selected_language_option = i;
            }
        }
    }
}

static bool is_config_option_enabled(int option) {
    auto& data = g_window_config_ext_data;
    switch (option) {
    case CONFIG_GP_CH_CITY_HAS_ANIMALS: return g_scenario.env.has_animals;
    case CONFIG_GP_CH_FLOTSAM_ENABLED: return g_scenario.env.flotsam_enabled;
    case CONFIG_GP_CH_RESOURCE_TIMBER: return g_city.can_produce_resource(RESOURCE_TIMBER);
    case CONFIG_GP_CH_RESOURCE_COPPER: return g_city.can_produce_resource(RESOURCE_COPPER);
    case CONFIG_GP_CH_RESOURCE_REED: return g_city.can_produce_resource(RESOURCE_REEDS);
    case CONFIG_GP_CH_RESOURCE_FISH: return g_city.can_produce_resource(RESOURCE_FISH);
    case CONFIG_GP_CH_RESOURCE_CHICKPEAS: return g_city.can_produce_resource(RESOURCE_CHICKPEAS);
    case CONFIG_GP_CH_RESOURCE_POMEGRANADES: return g_city.can_produce_resource(RESOURCE_POMEGRANATES);
    case CONFIG_GP_CH_RESOURCE_LETTUCE: return g_city.can_produce_resource(RESOURCE_LETTUCE);
    case CONFIG_GP_CH_RESOURCE_FIGS: return g_city.can_produce_resource(RESOURCE_FIGS);
    case CONFIG_GP_CH_RESOURCE_GRAIN: return g_city.can_produce_resource(RESOURCE_GRAIN);
    case CONFIG_GP_CH_RESOURCE_MEAT: return g_city.can_produce_resource(RESOURCE_MEAT);
    case CONFIG_GP_CH_RESOURCE_PAPYRUS: return g_city.can_produce_resource(RESOURCE_PAPYRUS);
    case CONFIG_GP_CH_RESOURCE_BRICKS: return g_city.can_produce_resource(RESOURCE_BRICKS);

    case CONFIG_GP_CH_BUILDING_WOOD_CUTTER: return building_menu_is_building_enabled(BUILDING_WOOD_CUTTERS);
    case CONFIG_GP_CH_BUILDING_COPPER_MINE: return building_menu_is_building_enabled(BUILDING_COPPER_MINE);
    case CONFIG_GP_CH_BUILDING_REED_GATHERER: return building_menu_is_building_enabled(BUILDING_REED_GATHERER);
    case CONFIG_GP_CH_BUILDING_PAPYRUS_MAKER: return building_menu_is_building_enabled(BUILDING_PAPYRUS_WORKSHOP);
    case CONFIG_GP_CH_BUILDING_SCRIBAL_SCHOOL: return building_menu_is_building_enabled(BUILDING_SCRIBAL_SCHOOL);
    case CONFIG_GP_CH_BUILDING_SHIPYARD: return building_menu_is_building_enabled(BUILDING_SHIPWRIGHT);
    case CONFIG_GP_CH_BUILDING_FISHING_WHARF: return building_menu_is_building_enabled(BUILDING_FISHING_WHARF);
    case CONFIG_GP_CH_BUILDING_POMEGRANATES_FARM: return building_menu_is_building_enabled(BUILDING_POMEGRANATES_FARM);
    case CONFIG_GP_CH_BUILDING_CHICKPEAS_FARM: return building_menu_is_building_enabled(BUILDING_CHICKPEAS_FARM);
    case CONFIG_GP_CH_BUILDING_LETTUCE_FARM: return building_menu_is_building_enabled(BUILDING_LETTUCE_FARM);
    case CONFIG_GP_CH_BUILDING_FIGS_FARM: return building_menu_is_building_enabled(BUILDING_FIGS_FARM);
    case CONFIG_GP_CH_BUILDING_GRAIN_FARM: return building_menu_is_building_enabled(BUILDING_GRAIN_FARM);
    case CONFIG_GP_CH_BUILDING_CATTLE_RANCH: return building_menu_is_building_enabled(BUILDING_CATTLE_RANCH);
    case CONFIG_GP_CH_BUILDING_BRICKS_WORKSHOP: return building_menu_is_building_enabled(BUILDING_BRICKS_WORKSHOP);
    case CONFIG_GP_CH_BUILDING_WORK_CAMP: return building_menu_is_building_enabled(BUILDING_WORK_CAMP);
    case CONFIG_GP_CH_BUILDING_GOLD_MINE: return building_menu_is_building_enabled(BUILDING_GOLD_MINE);
    case CONFIG_GP_CH_BUILDING_QUARRY_SANDSTONE: return building_menu_is_building_enabled(BUILDING_SANDSTONE_QUARRY);
    case CONFIG_GP_CH_BUILDING_QUARRY_GRANITE: return building_menu_is_building_enabled(BUILDING_GRANITE_QUARRY);
    case CONFIG_GP_CH_BUILDING_QUARRY_STONE: return building_menu_is_building_enabled(BUILDING_STONE_QUARRY);
    case CONFIG_GP_CH_BUILDING_QUARRY_LIMESTONE: return building_menu_is_building_enabled(BUILDING_LIMESTONE_QUARRY);
    case CONFIG_GP_CH_BUILDING_CLAY_PIT: return building_menu_is_building_enabled(BUILDING_CLAY_PIT);
    case CONFIG_GP_CH_BUILDING_BOOTH: return building_menu_is_building_enabled(BUILDING_BOOTH);
    case CONFIG_GP_CH_BUILDING_BANDSTAND: return building_menu_is_building_enabled(BUILDING_BANDSTAND);
    case CONFIG_GP_CH_BUILDING_WEAPONSMITH: return building_menu_is_building_enabled(BUILDING_WEAPONSMITH);
    case CONFIG_GP_CH_BUILDING_RECRUTER: return building_menu_is_building_enabled(BUILDING_RECRUITER);
    case CONFIG_GP_CH_BUILDING_SMALL_MASTABA: return building_menu_is_building_enabled(BUILDING_SMALL_MASTABA);
    case CONFIG_GP_CH_BUILDING_MEDIUM_MASTABA: return building_menu_is_building_enabled(BUILDING_MEDIUM_MASTABA);
    case CONFIG_GP_CH_BUILDING_BRICKLAYERS: return building_menu_is_building_enabled(BUILDING_BRICKLAYERS_GUILD);
    }

    return data.config_values[option].new_value;
}

static void draw_background(int) {
    auto& data = g_window_config_ext_data;
    painter ctx = game.painter();
    graphics_clear_screen();

    ImageDraw::img_background(ctx, image_id_from_group(GROUP_CONFIG_BACKGROUND));
    graphics_set_to_dialog();
    outer_panel_draw(vec2i{0, 0}, 40, 30);

    text_draw_centered(translation_for(page_names[data.page]), 16, 16, 608, FONT_LARGE_BLACK_ON_LIGHT, 0);

    text_draw(translation_for(TR_CONFIG_LANGUAGE_LABEL), 20, 56, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    text_draw_centered((uint8_t*)data.language_options[data.selected_language_option].c_str(), language_button.x, language_button.y + 6, language_button.width, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    for (int i = 0; i < options_per_page[data.page]; i++) {
        text_draw(translation_for(checkbox_buttons[data.starting_option + i].parameter2), 44, FIRST_BUTTON_Y + BUTTON_SPACING * i + TEXT_Y_OFFSET, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    }

    for (int i = 0; i < options_per_page[data.page]; i++) {
        int value = i + data.starting_option;
        generic_button &btn = checkbox_buttons[value];
        if (is_config_option_enabled(btn.parameter1 & 0xff)) {
            text_draw(string_from_ascii("x"), btn.x + 6, btn.y + 3, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        }
    }

    for (int i = 0; i < std::size(bottom_buttons); i++) {
        text_draw_centered(translation_for(bottom_buttons[i].parameter2), bottom_buttons[i].x, bottom_buttons[i].y + 9, bottom_buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    }
    
    for (int i = 0; i < std::size(page_buttons); i++) {
        text_draw_centered(translation_for(page_buttons[i].parameter2), page_buttons[i].x, page_buttons[i].y + 6, page_buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    }

    //if (GAME_ENV == ENGINE_ENV_C3) { // TODO: temporary fix to mitigate translation exception
    //    text_draw_label_and_number_centered((const char*)translation_for(TR_CONFIG_PAGE_LABEL), data.page + 1, "", 60, 416, 85, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    //}

    // text_draw_centered(translation_for(TR_CONFIG_PAGE_LABEL), 80, 415, 30, FONT_NORMAL_BLACK, 0);
    // text_draw_number(data.page + 1, '@', " ", 120, 415, FONT_NORMAL_BLACK);

    graphics_reset_dialog();
}

static void draw_foreground(int) {
    auto& data = g_window_config_ext_data;
    graphics_set_to_dialog();

    for (int i = 0; i < options_per_page[data.page]; i++) {
        int value = data.starting_option + i;
        generic_button* btn = &checkbox_buttons[value];
        button_border_draw(btn->x, btn->y, btn->width, btn->height, data.focus_button == value + 1);
    }

    for (int i = 0; i < std::size(bottom_buttons); i++) {
        button_border_draw(bottom_buttons[i].x,
                           bottom_buttons[i].y,
                           bottom_buttons[i].width,
                           bottom_buttons[i].height,
                           data.bottom_focus_button == i + 1);
    }

    for (int i = 0; i < std::size(page_buttons); i++) {
        button_border_draw(page_buttons[i].x,
                           page_buttons[i].y,
                           page_buttons[i].width,
                           page_buttons[i].height,
                           data.page_focus_button == i + 1);
    }

    button_border_draw(language_button.x,
                       language_button.y,
                       language_button.width,
                       language_button.height,
                       data.language_focus_button == 1);

    graphics_reset_dialog();
}
void window_config_show(void (*close_callback)(void)) {
    window_type window = {
        WINDOW_CONFIG,
        draw_background,
        draw_foreground,
        handle_input
    };
    init(close_callback);
    window_show(&window);
}