#include "monuments.h"
#include "building.h"
#include "core/image.h"

int get_statue_image(int type, int orientation, int variant) {
    int image_id = 0;

    if (orientation > 3)
        orientation = 0;
    if (variant > 3)
        orientation = 0;

    if (variant < 2) {
        switch (type) {
            case BUILDING_SMALL_STATUE:
                image_id = image_id_from_group(GROUP_BUILDING_STATUE_SMALL_1);
                break;
            case BUILDING_MEDIUM_STATUE:
                image_id = image_id_from_group(GROUP_BUILDING_STATUE_MEDIUM_1);
                break;
            case BUILDING_LARGE_STATUE:
                image_id = image_id_from_group(GROUP_BUILDING_STATUE_LARGE_1);
                break;
        }
        image_id += variant * 4 + orientation;
    } else {
        switch (type) {
            case BUILDING_SMALL_STATUE:
                image_id = image_id_from_group(GROUP_BUILDING_STATUE_SMALL_2);
                break;
            case BUILDING_MEDIUM_STATUE:
                image_id = image_id_from_group(GROUP_BUILDING_STATUE_MEDIUM_2);
                break;
            case BUILDING_LARGE_STATUE:
                image_id = image_id_from_group(GROUP_BUILDING_STATUE_LARGE_2);
                break;
        }
        variant -= 2;
        image_id += variant * 4 + orientation;
    }
    return image_id;
}

int get_monument_part_image(int part, int orientation, int level) {
    if (level < 0)
        level = 0;
    if (level > 11)
        level = 11;

    int base_image_id = image_id_from_group(GROUP_MONUMENT_BLOCKS);

    switch (part) {
        case MONUMENT_PART_CORNERS:
            return base_image_id + orientation + level * 8;
        case MONUMENT_PART_SIDES:
            return base_image_id + orientation + level * 8 + 4;
        case MONUMENT_PART_CENTER:
            if (level > 5)
                level = 5;
            return base_image_id + 96 + level + orientation * 6;
        case MONUMENT_PART_EXTRA: // ramps, mastaba entrance, etc.
            return base_image_id + 108 + orientation;
        case MONUMENT_PART_EXTERIORS: // TODO
            return image_id_from_group(GROUP_MONUMENT_EXTERIORS_END_DRY);
            break;
        case MONUMENT_PART_CORNERS_2: // for bent pyramids
            if (level > 5)
                level = 5;
            return image_id_from_group(GROUP_MONUMENT_EXTRA_BLOCKS) + orientation + level * 8;
        case MONUMENT_PART_SIDES_2: // for bent pyramids
            if (level > 5)
                level = 5;
            return image_id_from_group(GROUP_MONUMENT_EXTRA_BLOCKS) + orientation + level * 8 + 4;
    }
}