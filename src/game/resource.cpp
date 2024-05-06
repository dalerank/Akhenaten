#include "resource.h"

#include "building/building_type.h"
#include "scenario/scenario.h"
#include "core/game_environment.h"
#include "graphics/image_groups.h"

int resource_image_offset(int resource, int type) {
    switch (type) {
    case RESOURCE_IMAGE_STORAGE:
        return 0;
    case RESOURCE_IMAGE_CART:
        return 648;
    case RESOURCE_IMAGE_FOOD_CART:
        return 8;
    case RESOURCE_IMAGE_ICON:
        return 0;
    default:
        return 0;
    }
}

int resource_is_food(int resource) {
    return resource == RESOURCE_GRAIN || resource == RESOURCE_MEAT || resource == RESOURCE_LETTUCE
           || resource == RESOURCE_CHICKPEAS || resource == RESOURCE_POMEGRANATES || resource == RESOURCE_FIGS
           || resource == RESOURCE_FISH || resource == RESOURCE_GAMEMEAT;
}

e_resource get_raw_resource(e_resource resource) {
    switch (resource) {
    case RESOURCE_STRAW:
    return RESOURCE_GRAIN;
    case RESOURCE_POTTERY:
    return RESOURCE_CLAY;
    case RESOURCE_LUXURY_GOODS:
    return RESOURCE_GEMS;
    case RESOURCE_LINEN:
    return RESOURCE_FLAX;
    case RESOURCE_BEER:
    return RESOURCE_BARLEY;
    case RESOURCE_WEAPONS:
    return RESOURCE_COPPER;
    case RESOURCE_PAPYRUS:
    return RESOURCE_REEDS;
    case RESOURCE_CHARIOTS:
    return RESOURCE_TIMBER;
    case RESOURCE_PAINT:
    return RESOURCE_HENNA;
    case RESOURCE_LAMPS:
    return RESOURCE_OIL;
    default:
    return resource;
    }
}
