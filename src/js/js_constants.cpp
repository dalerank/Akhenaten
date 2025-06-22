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
#include "scenario/events.h"
#include "graphics/font.h"
#include "figure/figure.h"
#include "city/constants.h"
#include "city/city_kingdome_relations.h"

#include "sound/sound_city.h"

js_State *js_vm_state();
#define _R(name) js_newnumber(J, name); js_setglobal(J, #name);
void js_register_game_constants(js_State *J) {
    _R(FILE_TYPE_SAVED_GAME)
    _R(FILE_DIALOG_LOAD)

    // repeated for alias id
    _R(SOUND_CHANNEL_CITY_HOUSE_SLUM)
 
    // cause it vacant lot id also
    _R(BUILDING_HOUSE_CRUDE_HUT)

    // coz it is eqaul to RESOURCE_MAX
    _R(RESOURCE_DEBEN)

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

void js_register_city_advisors(js_State *J) {
    _R(ADVISOR_LABOR)
    _R(ADVISOR_MILITARY)
    _R(ADVISOR_IMPERIAL)
    _R(ADVISOR_RATINGS)
    _R(ADVISOR_TRADE)
    _R(ADVISOR_POPULATION)
    _R(ADVISOR_HEALTH)
    _R(ADVISOR_EDUCATION)
    _R(ADVISOR_ENTERTAINMENT)
    _R(ADVISOR_RELIGION)
    _R(ADVISOR_FINANCIAL)
    _R(ADVISOR_CHIEF)
};