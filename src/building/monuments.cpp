#include "monuments.h"
#include "building.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"

int get_statue_image(int type, int orientation, int variant) {
    int image_id = 0;

    while (orientation < 0)
        orientation += 4;
    while (orientation > 3)
        orientation -= 4;
    while (variant < 0)
        variant += 4;
    while (variant > 3)
        variant -= 4;

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
int get_statue_image_from_value(int type, int combined, int map_orientation) {

    int orientation = combined % 4 - (map_orientation / 2);
    int variant = combined / 16;

    return get_statue_image(type, orientation - 1, variant);
}
int get_statue_variant_value(int orientation, int variant) {
    int combined = variant * 16 + orientation + 2;
    return combined;
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

int get_temple_complex_part_image(int type, int part, int orientation, int level) {
    if (level == 0) {
        switch (part) {
            case 0:
                return image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_MAIN, type) + 3 * orientation;
            case 1:
                return image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_ORACLE, type) + 3 * orientation;
            case 2:
                return image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_ALTAR, type) + 3 * orientation;
        }
    } else if (level == 1) {
        switch (part) {
            case 0:
                return image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_MAIN, type) + orientation;
            case 1:
                return image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_UPGRADES, type) + orientation;
            case 2:
                return image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_UPGRADES, type) + 2 + orientation;
        }
    }
}
building *get_temple_complex_front_facing_part(building *b) {
    int orientation = (5 - (b->data.monuments.variant / 2)) % 4;
    int orientation_rel = city_view_relative_orientation(orientation);

    switch (orientation_rel) {
        case 0:
        case 3:
            return b->main(); // the first part is the oracle
        case 1:
        case 2:
            return b->main()->next()->next(); // the last part is the oracle
    }
}