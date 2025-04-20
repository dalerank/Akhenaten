#include "js_constants.h"

#include "js_defines.h"

#include "input/hotkey.h"
#include "mujs/mujs.h"
#include "window/file_dialog.h"
#include "overlays/city_overlay.h"
#include "building/building.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "scenario/events.h"
#include "graphics/font.h"
#include "city/constants.h"

#include "sound/sound_city.h"

template<typename T>
void js_register_tokens(js_State *J, const T &tokens) {
    for (const auto &btype : tokens.values) {
        if (!btype.name || !*btype.name) {
            continue;
        }
        js_newnumber(J, btype.id);
        js_setglobal(J, btype.name);
    }
}

#define _R(name) js_newnumber(J, name); js_setglobal(J, #name);
void js_register_game_constants(js_State *J) {
   _R(FILE_TYPE_SAVED_GAME)
   _R(FILE_DIALOG_LOAD)
}

void js_register_collection_images(js_State *J) {
    js_register_tokens(J, e_pack_type_tokens);
}

void js_register_city_walkers(js_State *J) {
    js_register_tokens(J, e_figure_type_tokens);
}

void js_register_city_sound_constants(js_State *J) {
    js_register_tokens(J, e_sound_channel_city_tokens);
    // repeated for alias id
    _R(SOUND_CHANNEL_CITY_HOUSE_SLUM)
}

void js_register_city_buildings(js_State *J) {
    js_register_tokens(J, e_building_type_tokens);
    // cause it vacant lot id also
    _R(BUILDING_HOUSE_CRUDE_HUT)
}

void js_register_ui_fonts(js_State *J) {
    js_register_tokens(J, e_tont_type_tokens);
}

void js_register_city_labor_category(js_State *J) {
    js_register_tokens(J, e_labor_category_tokens);
}

void js_register_city_overlays(js_State *J) {
    js_register_tokens(J, e_overlay_tokens);
    js_register_tokens(J, e_column_type_tokens);
}

void js_registere_event_type(js_State *J) {
    js_register_tokens(J, e_event_type_tokens);
}

void js_register_terrain(js_State *J) {
   _R(TERRAIN_USAGE_ANY)
   _R(TERRAIN_USAGE_ROADS)
   _R(TERRAIN_USAGE_ENEMY)
   _R(TERRAIN_USAGE_PREFER_ROADS)
   _R(TERRAIN_USAGE_WALLS)
   _R(TERRAIN_USAGE_ANIMAL)
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

void js_register_city_resources(js_State *J) {
   _R(RESOURCE_NONE)
   _R(RESOURCE_MIN)
   _R(RESOURCE_FOOD_MIN)
   _R(RESOURCE_GRAIN)
   _R(RESOURCE_MEAT)
   _R(RESOURCE_LETTUCE)
   _R(RESOURCE_CHICKPEAS)
   _R(RESOURCE_POMEGRANATES)
   _R(RESOURCE_FIGS)
   _R(RESOURCE_FISH)
   _R(RESOURCE_GAMEMEAT)
   _R(RESOURCES_FOODS_MAX)
   _R(RESOURCE_STRAW)
   _R(RESOURCE_WEAPONS)
   _R(RESOURCE_CLAY)
   _R(RESOURCE_BRICKS)
   _R(RESOURCE_POTTERY)
   _R(RESOURCE_BARLEY)
   _R(RESOURCE_BEER)
   _R(RESOURCE_FLAX)
   _R(RESOURCE_LINEN)
   _R(RESOURCE_GEMS)
   _R(RESOURCE_LUXURY_GOODS)
   _R(RESOURCE_TIMBER)
   _R(RESOURCE_GOLD)
   _R(RESOURCE_REEDS)
   _R(RESOURCE_PAPYRUS)
   _R(RESOURCE_STONE)
   _R(RESOURCE_LIMESTONE)
   _R(RESOURCE_GRANITE)
   _R(RESOURCE_UNUSED12)
   _R(RESOURCE_CHARIOTS)
   _R(RESOURCE_COPPER)
   _R(RESOURCE_SANDSTONE)
   _R(RESOURCE_OIL)
   _R(RESOURCE_HENNA)
   _R(RESOURCE_PAINT)
   _R(RESOURCE_LAMPS)
   _R(RESOURCE_MARBLE)
   _R(RESOURCES_MAX)
   _R(RESOURCE_DEBEN)
   _R(RESOURCE_TROOPS)
}