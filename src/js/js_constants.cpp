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
