#include "resource.h"

#include "building/type.h"
#include "scenario/building.h"
#include "core/game_environment.h"

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
#include "graphics/image.h"

int resource_get_icon(int resource, int quantity) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        return resource + image_id_from_group(GROUP_EMPIRE_RESOURCES) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        // assume we are dealing with NORMAL icons....

        return resource + image_id_from_group(GROUP_RESOURCE_ICONS);
    }
}

int resource_is_food(int resource) {
    return resource == RESOURCE_GRAIN || resource == RESOURCE_MEAT ||
           resource == RESOURCE_LETTUCE || resource == RESOURCE_CHICKPEAS ||
           resource == RESOURCE_POMEGRANATES || resource == RESOURCE_FIGS ||
           resource == RESOURCE_FISH || resource == RESOURCE_GAMEMEAT;
}

#include <building/building.h>
bool resource_required_by_workshop(building *b, int resource) {
    switch (resource) {
        case RESOURCE_CLAY:
            return (b->subtype.workshop_type == WORKSHOP_POTTERY
                 || b->subtype.workshop_type == WORKSHOP_BRICKS);
        case RESOURCE_STRAW:
            return (b->subtype.workshop_type == WORKSHOP_BRICKS
                 || b->subtype.workshop_type == WORKSHOP_CATTLE);
        case RESOURCE_BARLEY:
            return b->subtype.workshop_type == WORKSHOP_BEER;
        case RESOURCE_REEDS:
            return b->subtype.workshop_type == WORKSHOP_PAPYRUS;
        case RESOURCE_FLAX:
            return b->subtype.workshop_type == WORKSHOP_LINEN;
        case RESOURCE_GEMS:
            return b->subtype.workshop_type == WORKSHOP_JEWELS;
        case RESOURCE_COPPER:
            return b->subtype.workshop_type == WORKSHOP_WEAPONS;
        case RESOURCE_TIMBER:
            return b->subtype.workshop_type == WORKSHOP_CHARIOTS;
        case RESOURCE_HENNA:
            return b->subtype.workshop_type == WORKSHOP_PAINT;
        case RESOURCE_OIL:
            return b->subtype.workshop_type == WORKSHOP_LAMPS;
        default:
            return false;
    }
}
