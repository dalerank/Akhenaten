#pragma once

#include "building/building.h"

class building_tax_collector : public building_impl {
public:
    building_tax_collector(building &b) : building_impl(b) {}
    virtual bool is_workshop() const override { return true; }
    virtual void window_info_background(object_info &c) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_TAX_INCOME; }
    virtual void update_month() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_TAX_COLLECTOR; }
};