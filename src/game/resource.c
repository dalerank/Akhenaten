#include "resource.h"

#include "building/type.h"
#include "scenario/building.h"
#include "core/game_environment.h"

int resource_image_offset(int resource, int type) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (resource == RESOURCE_MEAT_C3 && scenario_building_allowed(BUILDING_WHARF)) {
            switch (type) {
                case RESOURCE_IMAGE_STORAGE:
                    return 40;
                case RESOURCE_IMAGE_CART:
                    return 648;
                case RESOURCE_IMAGE_FOOD_CART:
                    return 8;
                case RESOURCE_IMAGE_ICON:
                    return 0;
                default:
                    return 0;
            }
        } else {
            return 0;
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
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
    } else
        return 0;
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
    if (GAME_ENV == ENGINE_ENV_C3)
        return resource == RESOURCE_WHEAT || resource == RESOURCE_VEGETABLES ||
               resource == RESOURCE_FRUIT || resource == RESOURCE_MEAT_C3;
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        return resource == RESOURCE_GRAIN || resource == RESOURCE_MEAT_PH ||
               resource == RESOURCE_LETTUCE || resource == RESOURCE_CHICKPEAS ||
               resource == RESOURCE_POMEGRANATES || resource == RESOURCE_FIGS ||
               resource == RESOURCE_FISH || resource == RESOURCE_GAMEMEAT;
}

int resource_to_workshop_type(int resource) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        switch (resource) {
            case RESOURCE_OLIVES:
                return WORKSHOP_OLIVES_TO_OIL;
            case RESOURCE_VINES:
                return WORKSHOP_VINES_TO_WINE;
            case RESOURCE_IRON:
                return WORKSHOP_IRON_TO_WEAPONS;
            case RESOURCE_TIMBER_C3:
                return WORKSHOP_TIMBER_TO_FURNITURE;
            case RESOURCE_CLAY:
                return WORKSHOP_CLAY_TO_POTTERY;
            default:
                return WORKSHOP_NONE;
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        switch (resource) {
            case RESOURCE_CLAY:
                return WORKSHOP_CLAY_TO_POTTERY;
// TODO: How to use clay both for pottery and bricks workshop?
//            case RESOURCE_CLAY_PH:
//                return WORKSHOP_CLAY_TO_BRICKS;
            case RESOURCE_TIMBER_PH:
                return WORKSHOP_TIMBER_TO_FURNITURE;
            case RESOURCE_BARLEY:
                return WORKSHOP_BARLEY_TO_BEER;
            case RESOURCE_FLAX:
                return WORKSHOP_FLAX_TO_LINEN;
            case RESOURCE_REEDS:
                return WORKSHOP_REEDS_TO_PAPYRUS;
            case RESOURCE_COPPER:
                return WORKSHOP_COPPER_TO_WEAPONS;
            default:
                return WORKSHOP_NONE;
        }
    }
}

int resource_get_gold() {
    if (GAME_ENV == ENGINE_ENV_C3) {
        return RESOURCE_DENARII;
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        return RESOURCE_GOLD;
    }
}
