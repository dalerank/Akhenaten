#include "resource.h"

#include "building/building_type.h"
#include "scenario/scenario.h"
#include "core/game_environment.h"
#include "graphics/image_groups.h"

const token_holder<e_resource, RESOURCE_NONE, RESOURCE_COUNT> e_resource_tokens;

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
