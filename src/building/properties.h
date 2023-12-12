#pragma once

#include "building/building_type.h"
#include "graphics/image_desc.h"
#include "graphics/image.h"

struct building_properties {
    int size;
    int fire_proof;
    int _image_collection;
    int _image_group;
    int image_offset;
    e_image_id _img = IMG_NONE;

    image_desc img() const {
        if (_img == 0) {
            return {_image_collection, _image_group};
        }

        return get_image_desc(_img);
    }

    int img_id() const {
        return image_group(img()) + image_offset;
    }
};

void building_properties_init();
const building_properties* building_properties_for_type(e_building_type type);
