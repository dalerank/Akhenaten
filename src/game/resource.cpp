#include "resource.h"

#include "building/building_type.h"
#include "scenario/scenario.h"
#include "core/game_environment.h"
#include "graphics/image_groups.h"

const token_holder<e_resource, RESOURCE_NONE, RESOURCE_COUNT> e_resource_tokens;

static id_resources_t g_tags;
const id_resources_t &resources() {
    return g_tags;
}

const xstring id_resources_t::none = "none";
const xstring id_resources_t::grain = "grain";
const xstring id_resources_t::meat = "meat";
const xstring id_resources_t::lettuce = "lettuce";
const xstring id_resources_t::chickpeas = "chickpeas";
const xstring id_resources_t::pomegranates = "pomegranates";
const xstring id_resources_t::figs = "figs";
const xstring id_resources_t::fish = "fish";
const xstring id_resources_t::gamemeat = "gamemeat";
const xstring id_resources_t::straw = "straw";
const xstring id_resources_t::weapons = "weapons";
const xstring id_resources_t::clay = "clay";
const xstring id_resources_t::bricks = "bricks";
const xstring id_resources_t::pottery = "pottery";
const xstring id_resources_t::barley = "barley";
const xstring id_resources_t::beer = "beer";
const xstring id_resources_t::flax = "flax";
const xstring id_resources_t::linen = "linen";
const xstring id_resources_t::gems = "gems";
const xstring id_resources_t::luxury_goods = "luxury_goods";
const xstring id_resources_t::timber = "timber";
const xstring id_resources_t::gold = "gold";
const xstring id_resources_t::reeds = "reeds";
const xstring id_resources_t::papyrus = "papyrus";
const xstring id_resources_t::stone = "stone";
const xstring id_resources_t::limestone = "limestone";
const xstring id_resources_t::granite = "granite";
const xstring id_resources_t::chariots = "chariots";
const xstring id_resources_t::copper = "copper";
const xstring id_resources_t::sandstone = "sandstone";
const xstring id_resources_t::oil = "oil";
const xstring id_resources_t::henna = "henna";
const xstring id_resources_t::paint = "paint";
const xstring id_resources_t::lamps = "lamps";
const xstring id_resources_t::marble = "marble";
const xstring id_resources_t::deben = "deben";
const xstring id_resources_t::troops = "troops";

e_resource resource_type(const xstring &name) {
    if (name == resources().none) return RESOURCE_NONE;
    if (name == resources().grain) return RESOURCE_GRAIN;
    if (name == resources().meat) return RESOURCE_MEAT;
    if (name == resources().lettuce) return RESOURCE_LETTUCE;
    if (name == resources().chickpeas) return RESOURCE_CHICKPEAS;
    if (name == resources().pomegranates) return RESOURCE_POMEGRANATES;
    if (name == resources().figs) return RESOURCE_FIGS;
    if (name == resources().fish) return RESOURCE_FISH;
    if (name == resources().gamemeat) return RESOURCE_GAMEMEAT;
    if (name == resources().straw) return RESOURCE_STRAW;
    if (name == resources().weapons) return RESOURCE_WEAPONS;
    if (name == resources().clay) return RESOURCE_CLAY;
    if (name == resources().bricks) return RESOURCE_BRICKS;
    if (name == resources().pottery) return RESOURCE_POTTERY;
    if (name == resources().barley) return RESOURCE_BARLEY;
    if (name == resources().beer) return RESOURCE_BEER;
    if (name == resources().flax) return RESOURCE_FLAX;
    if (name == resources().linen) return RESOURCE_LINEN;
    if (name == resources().gems) return RESOURCE_GEMS;
    if (name == resources().luxury_goods) return RESOURCE_LUXURY_GOODS;
    if (name == resources().timber) return RESOURCE_TIMBER;
    if (name == resources().gold) return RESOURCE_GOLD;
    if (name == resources().reeds) return RESOURCE_REEDS;
    if (name == resources().papyrus) return RESOURCE_PAPYRUS;
    if (name == resources().stone) return RESOURCE_STONE;
    if (name == resources().limestone) return RESOURCE_LIMESTONE;
    if (name == resources().granite) return RESOURCE_GRANITE;
    if (name == resources().chariots) return RESOURCE_CHARIOTS;
    if (name == resources().copper) return RESOURCE_COPPER;
    if (name == resources().sandstone) return RESOURCE_SANDSTONE;
    if (name == resources().oil) return RESOURCE_OIL;
    if (name == resources().henna) return RESOURCE_HENNA;
    if (name == resources().paint) return RESOURCE_PAINT;
    if (name == resources().lamps) return RESOURCE_LAMPS;
    if (name == resources().marble) return RESOURCE_MARBLE;
    if (name == resources().deben) return RESOURCE_DEBEN;
    if (name == resources().troops) return RESOURCE_TROOPS;

    assert(false);
    return RESOURCE_NONE;
}

pcstr resource_name(e_resource resource) {
    switch (resource) {
    case RESOURCE_NONE: return "none";
    case RESOURCE_GRAIN: return "grain";
    case RESOURCE_MEAT: return "meat";
    case RESOURCE_LETTUCE: return "lettuce";
    case RESOURCE_CHICKPEAS: return "chickpeas";
    case RESOURCE_POMEGRANATES: return "pomegranates";
    case RESOURCE_FIGS: return "figs";
    case RESOURCE_FISH: return "fish";
    case RESOURCE_GAMEMEAT: return "gamemeat";
    case RESOURCE_STRAW: return "straw";
    case RESOURCE_WEAPONS: return "weapons";
    case RESOURCE_CLAY: return "clay";
    case RESOURCE_BRICKS: return "bricks";
    case RESOURCE_POTTERY: return "pottery";
    case RESOURCE_BARLEY: return "barley";
    case RESOURCE_BEER: return "beer";
    case RESOURCE_FLAX: return "flax";
    case RESOURCE_LINEN: return "linen";
    case RESOURCE_GEMS: return "gems";
    case RESOURCE_LUXURY_GOODS: return "luxury_goods";
    case RESOURCE_TIMBER: return "timber";
    case RESOURCE_GOLD: return "gold";
    case RESOURCE_REEDS: return "reeds";
    case RESOURCE_PAPYRUS: return "papyrus";
    case RESOURCE_STONE: return "stone";
    case RESOURCE_LIMESTONE: return "limestone";
    case RESOURCE_GRANITE: return "granite";
    case RESOURCE_UNUSED12: return "unused";
    case RESOURCE_CHARIOTS: return "chariots";
    case RESOURCE_COPPER: return "copper";
    case RESOURCE_SANDSTONE: return "sandstone";
    case RESOURCE_OIL: return "oil";
    case RESOURCE_HENNA: return "henna";
    case RESOURCE_PAINT: return "paint";
    case RESOURCE_LAMPS: return "lamps";
    case RESOURCE_MARBLE: return "marble";
    case RESOURCE_DEBEN: return "deben";
    case RESOURCE_TROOPS: return "troops";

    default:
        assert(false);
    }
    return "unknown";
}

int resource_image_offset(int resource, int type) {
    switch (type) {
    case RESOURCE_IMAGE_STORAGE: return 0;
    case RESOURCE_IMAGE_CART: return 648;
    case RESOURCE_IMAGE_FOOD_CART: return 8;
    case RESOURCE_IMAGE_ICON: return 0;
    default:
        return 0;
    }
}

const resource_list resource_list::foods = resource_list(RESOURCE_GRAIN, RESOURCE_GAMEMEAT);
const resource_list resource_list::all = resource_list(RESOURCE_GRAIN, RESOURCE_MARBLE);
const resource_list resource_list::values = resource_list(RESOURCE_NONE, RESOURCE_MARBLE);

e_resource get_raw_resource(e_resource resource) {
    switch (resource) {
    case RESOURCE_STRAW: return RESOURCE_GRAIN;
    case RESOURCE_POTTERY: return RESOURCE_CLAY;
    case RESOURCE_LUXURY_GOODS: return RESOURCE_GEMS;
    case RESOURCE_LINEN: return RESOURCE_FLAX;
    case RESOURCE_BEER: return RESOURCE_BARLEY;
    case RESOURCE_WEAPONS: return RESOURCE_COPPER;
    case RESOURCE_PAPYRUS: return RESOURCE_REEDS;
    case RESOURCE_CHARIOTS: return RESOURCE_TIMBER;
    case RESOURCE_PAINT: return RESOURCE_HENNA;
    case RESOURCE_LAMPS: return RESOURCE_OIL;
    default:
    return resource;
    }
}
