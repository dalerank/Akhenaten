#include "js_constants.h"

#include "js_defines.h"
#include "js_game.h"
#include "input/hotkey.h"
#include "mujs/mujs.h"
#include "window/file_dialog.h"
#include "overlays/city_overlay.h"
#include "building/building.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "scenario/scenario_event_manager.h"
#include "graphics/font.h"
#include "figure/figure.h"
#include "city/constants.h"
#include "city/city_kingdome_relations.h"
#include "sound/sound_city.h"

using e_advisor_tokens_t = token_holder<e_advisor, ADVISOR_NONE, ADVISOR_MAX>;
e_advisor_tokens_t ANK_CONFIG_ENUM(e_advisor_tokens);

js_State *js_vm_state();
#define _R(name) js_newnumber(J, name); js_setglobal(J, #name);
void js_register_game_constants(js_State *J) {
    _R(FILE_TYPE_SAVED_GAME)

    // repeated for alias id
    _R(SOUND_CHANNEL_CITY_HOUSE_SLUM)
 
    // cause it vacant lot id also
    _R(BUILDING_HOUSE_VACANT_LOT)

    // coz it is eqaul to RESOURCE_MAX
    _R(RESOURCE_DEBEN)
    _R(LABOR_CATEGORY_NONE)

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
    _R(COLOR_RED)
    _R(COLOR_GREEN)
    _R(COLOR_YELLOW)
    _R(COLOR_WHITE)

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

    for (config::EnumIterator *s = config::EnumIterator::tail; s; s = s->next) {
        s->func({});
    }
}

void js_register_token(int id, pcstr name) {
    if (!name || !*name) {
        return; // skip empty names
    }
    auto J = js_vm_state();
    js_newnumber(J, id);
    js_setglobal(J, name);
}

void js_register_menu(js_State *J) {
}
