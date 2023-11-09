#include "resource.h"

#include "building/building_type.h"
#include "scenario/building.h"
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