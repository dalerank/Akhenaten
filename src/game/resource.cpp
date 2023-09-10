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
#include "core/game_environment.h"
#include "graphics/boilerplate.h"

int resource_get_icon(int resource, int quantity) {
    return resource + image_id_from_group(GROUP_RESOURCE_ICONS);
}

int resource_is_food(int resource) {
    return resource == RESOURCE_GRAIN || resource == RESOURCE_MEAT || resource == RESOURCE_LETTUCE
           || resource == RESOURCE_CHICKPEAS || resource == RESOURCE_POMEGRANATES || resource == RESOURCE_FIGS
           || resource == RESOURCE_FISH || resource == RESOURCE_GAMEMEAT;
}

#include <building/building.h>
bool resource_required_by_workshop(building* b, int resource) {
    switch (resource) {
    case RESOURCE_CLAY:
        return (b->type == BUILDING_POTTERY_WORKSHOP || b->type == BUILDING_BRICKS_WORKSHOP);
    case RESOURCE_STRAW:
        return (b->type == BUILDING_BRICKS_WORKSHOP || b->type == BUILDING_CATTLE_RANCH);
    case RESOURCE_BARLEY:
        return b->type == BUILDING_BEER_WORKSHOP;
    case RESOURCE_REEDS:
        return b->type == BUILDING_PAPYRUS_WORKSHOP;
    case RESOURCE_FLAX:
        return b->type == BUILDING_LINEN_WORKSHOP;
    case RESOURCE_GEMS:
        return b->type == BUILDING_JEWELS_WORKSHOP;
    case RESOURCE_COPPER:
        return b->type == BUILDING_WEAPONS_WORKSHOP;
    case RESOURCE_TIMBER:
        return b->type == BUILDING_CHARIOTS_WORKSHOP;
    case RESOURCE_HENNA:
        return b->type == BUILDING_PAINT_WORKSHOP;
    case RESOURCE_OIL:
        return b->type == BUILDING_LAMP_WORKSHOP;
    default:
        return false;
    }
}
