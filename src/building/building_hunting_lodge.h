#pragma once

#include "building/building_industry.h"
#include "figure/figure_type.h"

class building_hunting_lodge : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_HUNTING_LODGE, building_hunting_lodge, building_impl)

    struct static_params : public building_static_params {
        uint8_dcy spawn_delay_100_percent;
        uint8_dcy spawn_delay_75_percent;
        uint8_dcy spawn_delay_50_percent;
        uint8_dcy spawn_delay_25_percent;
        uint8_dcy spawn_delay_default;     // default delay for 1-24% workers
        uint8_dcy max_hunters;             // simultaneous hunters from this lodge
        e_figure_type hunter_type = FIGURE_NONE; // FIGURE_NONE = climate resolve
    } BUILDING_STATIC_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_HUNTER_LOUDGE; }

    int spawn_timer();
    e_figure_type resolve_hunter_type() const;
    int active_hunters_count() const;
    bool can_spawn_hunter();
};
ANK_CONFIG_STRUCT(building_hunting_lodge::static_params,
    spawn_delay_100_percent, spawn_delay_75_percent, spawn_delay_50_percent,
    spawn_delay_25_percent, spawn_delay_default, max_hunters, hunter_type)
