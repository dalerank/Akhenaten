#pragma once

#include "building/building_entertainment.h"

class building_conservatory : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_CONSERVATORY, building_conservatory)

    building_conservatory(building &b) : building_entertainment(b) {}
    virtual building_conservatory *dcast_conservatory() override { return this; }

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENTERTAINMENT; }
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CONSERVATORY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};