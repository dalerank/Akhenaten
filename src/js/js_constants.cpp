#include "js_constants.h"

#include "js_defines.h"
#include "js_game.h"
#include "input/hotkey.h"
#include "mujs/mujs.h"
#include "window/file_dialog.h"
#include "game/game.h"
#include "game/resource.h"
#include "game/mission.h"
#include "overlays/city_overlay.h"
#include "building/building.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "graphics/font.h"
#include "graphics/screenshot.h"
#include "figure/figure.h"
#include "city/constants.h"
#include "city/city_kingdome_relations.h"
#include "sound/sound_city.h"
#include "game/gods.h"
#include "figuretype/figure_physician.h"
#include "figuretype/figure_fishing_boat.h"
#include "figuretype/figure_war_ship.h"
#include "figuretype/figure_worker.h"
#include "city/city_floods.h"
#include "grid/terrain.h"
#include "grid/water_supply.h"

e_advisor_tokens_t ANK_CONFIG_ENUM(e_advisor_tokens);
e_trade_status_tokens_t ANK_CONFIG_ENUM(e_trade_status_tokens);

js_State* js_vm_state();
#define _R(name)            \
    js_pushnumber(J, name); \
    js_setglobal(J, #name);
void js_register_game_constants(js_State* J) {
    _R(FILE_TYPE_SAVED_GAME)
    _R(FILE_TYPE_SCENARIO)
    _R(e_session_none)
    _R(e_session_mission)
    _R(e_session_save)
    _R(e_session_custom_map)
    _R(e_scenario_normal)
    _R(e_scenario_custom_map)
    _R(SCENARIO_NUBT)
    _R(GOD_UNKNOWN)

    // repeated for alias id
    _R(SOUND_CHANNEL_CITY_HOUSE_SLUM)

    // cause it vacant lot id also
    _R(BUILDING_HOUSE_VACANT_LOT)

    // coz it is eqaul to RESOURCE_MAX
    _R(RESOURCE_DEBEN)
    _R(RESOURCE_TROOPS)
    _R(RESOURCE_WATER)
    _R(LABOR_CATEGORY_NONE)
    _R(LABOR_CATEGORY_SIZE)
    _R(LABOR_CATEGORY_CULTURE)

    _R(COLOR_FONT_RED)
    _R(COLOR_FONT_BLUE)
    _R(COLOR_FONT_YELLOW)
    _R(COLOR_FONT_ORANGE)
    _R(COLOR_FONT_ORANGE_LIGHT)
    _R(COLOR_FONT_LIGHT_GRAY)
    _R(COLOR_FONT_MEDIUM_GRAY)
    _R(COLOR_FONT_DARK_RED)
    _R(COLOR_FONT_SHITTY_BROWN)
    _R(COLOR_BLACK)
    _R(COLOR_BLUE)
    _R(COLOR_LIGHT_BLUE)
    _R(COLOR_RED)
    _R(COLOR_GREEN)
    _R(COLOR_YELLOW)
    _R(COLOR_WHITE)
    _R(COLOR_MASK_BLUE)
    _R(COLOR_MASK_GREEN)
    _R(COLOR_TOOLTIP_FILL)
    _R(COLOR_TOOLTIP_BORDER)
    _R(COLOR_TOOLTIP_TEXT)

    _R(SCREENSHOT_FULL_CITY)
    _R(SCREENSHOT_DISPLAY)
    _R(SCREENSHOT_MINIMAP)

    _R(BUILDING_SLOT_SERVICE)
    _R(BUILDING_SLOT_CARTPUSHER)
    _R(BUILDING_SLOT_MARKET_BUYER)
    _R(BUILDING_SLOT_LABOR_SEEKER)
    _R(BUILDING_SLOT_JUGGLER)
    _R(BUILDING_SLOT_DRUNKARD)
    _R(BUILDING_SLOT_MUSICIAN)
    _R(BUILDING_SLOT_DANCER)
    _R(BUILDING_SLOT_PRIEST)
    _R(BUILDING_SLOT_IMMIGRANT)
    _R(BUILDING_SLOT_HOMELESS)
    _R(BUILDING_SLOT_GOVERNOR)
    _R(BUILDING_SLOT_HUNTER)
    _R(BUILDING_SLOT_BOAT)
    _R(BUILDING_SLOT_BALLISTA)
    _R(BUILDING_SLOT_CARTPUSHER_2)

    _R(ACTION_10_ROAMER_GOING)
    _R(ACTION_125_ROAMER_ROAMING)
    _R(ACTION_126_ROAMER_RETURNING)
    _R(ACTION_60_PHYSICIAN_CREATED)
    _R(ACTION_9_WORKER_CREATED)
    _R(ACTION_194_FISHING_BOAT_AT_WHARF)
    _R(ACTION_203_WARSHIP_MOORED)
    _R(ACTION_204_WARSHIP_ATTACK)

    _R(FLOOD_STATE_FARMABLE)

    _R(TERRAIN_NONE)
    _R(TERRAIN_TREE)
    _R(TERRAIN_ROCK)
    _R(TERRAIN_WATER)
    _R(TERRAIN_BUILDING)
    _R(TERRAIN_SHRUB)
    _R(TERRAIN_GARDEN)
    _R(TERRAIN_ROAD)
    _R(TERRAIN_GROUNDWATER)
    _R(TERRAIN_CANAL)
    _R(TERRAIN_ELEVATION)
    _R(TERRAIN_ACCESS_RAMP)
    _R(TERRAIN_MEADOW)
    _R(TERRAIN_RUBBLE)
    _R(TERRAIN_FOUNTAIN_RANGE)
    _R(TERRAIN_WALL)
    _R(TERRAIN_GATEHOUSE)
    _R(TERRAIN_FLOODPLAIN)
    _R(TERRAIN_FERRY_ROUTE)
    _R(TERRAIN_MARSHLAND)

    _R(TERRAIN_ROAD_BLOCKED)
    _R(TERRAIN_PLANER_FUTURE)

    _R(WELL_NECESSARY)
    _R(WELL_UNNECESSARY_FOUNTAIN)
    _R(WELL_UNNECESSARY_NO_HOUSES)

    _R(MAX_BUILDINGS)
    _R(BUILDING_MAX)

    for (config::EnumIterator* s = config::EnumIterator::tail; s; s = s->next) {
        s->func({});
    }
}

void js_register_token(int id, pcstr name) {
    if (!name || !*name) {
        return; // skip empty names
    }
    auto J = js_vm_state();
    js_pushnumber(J, id); // Use js_pushnumber instead of js_newnumber to create primitive number
    js_setglobal(J, name);
}

void js_register_menu(js_State* J) {
}
