#pragma once

#include "building/building.h"

class building_dentist : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DENTIST, building_dentist, building_impl)

    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DENTIST; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
    virtual void spawn_figure() override;
    virtual void update_month() override;
    
    building_id find_noble_house_with_max_bad_teeth();
};