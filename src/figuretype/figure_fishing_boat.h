#pragma once

#include "figure/figure.h"

enum e_fishing_boat_action : uint16_t {
    ACTION_0_FISHING_BOAT_CREATED = 0,
    ACTION_1_FISHING_BOAT_GOING_TO_FISH = 1,
    ACTION_2_FISHING_BOAT_FISHING = 2,
    ACTION_3_FISHING_BOAT_GOING_TO_WHARF = 3,
    ACTION_4_FISHING_BOAT_AT_WHARF = 4,
    ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH = 5,
    ACTION_6_FISHING_BOAT_RANDOM_FPOINT = 6,
    ACTION_7_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN = 7,
    ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF = 8,

    ACTION_9_FISHING_BOAT_MAX
};
using e_fishing_boat_action_tokens_t = token_holder<e_fishing_boat_action, ACTION_0_FISHING_BOAT_CREATED, ACTION_9_FISHING_BOAT_MAX>;
extern const e_fishing_boat_action_tokens_t e_fishing_boat_action_tokens;

class figure_fishing_boat : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FISHING_BOAT, figure_fishing_boat)
    figure_fishing_boat(figure *f) : figure_impl(f) {}
    virtual figure_fishing_boat *dcast_fishing_boat() override { return this; }

    struct static_params : public figure_static_params {
        uint16_t fish_per_trip;
        uint16_t fishing_time_base;        
        uint8_t fishing_time_multiplier;  
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        bool had_home;
        uint8_t fishing_point_check_attempts;
        tile2i preferred_fishing_tile;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    //virtual e_overlay get_overlay() const override { return OVERLAY_APOTHECARY; }
    virtual bool window_info_background(object_info &ctx) override;
    virtual void update_animation() override;
};
ANK_CONFIG_STRUCT(figure_fishing_boat::static_params, fish_per_trip, fishing_time_base, fishing_time_multiplier)
