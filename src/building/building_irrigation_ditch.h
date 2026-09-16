#pragma once

#include "building/building.h"

class building_irrigation_ditch : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_IRRIGATION_DITCH, building_irrigation_ditch, building_impl)

    struct static_params : public building_static_params {
        uint8_t canal_irrigation_value_multiplier;

        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;

    struct image_set {
        int begin;
        int end;

        static constexpr int IMAGE_FULL_OFFSET = 48;
    };
    static const image_set &images();
};
ANK_CONFIG_STRUCT(building_irrigation_ditch::static_params, canal_irrigation_value_multiplier)
