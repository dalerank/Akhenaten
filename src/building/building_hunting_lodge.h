#pragma once

#include "building/building_industry.h"

class building_hunting_lodge : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_HUNTING_LODGE, building_hunting_lodge, building_impl)

    struct static_params : public building_static_params {
        uint8_dcy max_hunters;
    } BUILDING_STATIC_DATA_T;

    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_HUNTER_LOUDGE; }
};
ANK_CONFIG_STRUCT(building_hunting_lodge::static_params, max_hunters)
