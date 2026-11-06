#pragma once

#include "building/building_wharf.h"

class building_transport_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_TRANSPORT_WHARF, building_transport_wharf, building_wharf)

    virtual building_transport_wharf *dcast_transport_wharf() override { return this; }

    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void on_undo() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_WHARF; }

private:
    void clear_invalid_boat();
};
