#pragma once

#include "figure/figure.h"

enum e_fishing_boat_action : uint16_t {
    ACTION_190_FISHING_BOAT_CREATED = 190,
    ACTION_191_FISHING_BOAT_GOING_TO_FISH = 191,
    ACTION_192_FISHING_BOAT_FISHING = 192,
    ACTION_193_FISHING_BOAT_GOING_TO_WHARF = 193,
    ACTION_194_FISHING_BOAT_AT_WHARF = 194,
    ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH = 195,
    ACTION_196_FISHING_BOAT_RANDOM_FPOINT = 196,
    ACTION_196_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN = 197,
    ACTION_196_FISHING_BOAT_RETURN_TO_RANDOM_WHARF = 198,
};

class figure_fishing_boat : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FISHING_BOAT, figure_fishing_boat)
    figure_fishing_boat(figure *f) : figure_impl(f) {}
    virtual figure_fishing_boat *dcast_fishing_boat() override { return this; }

    struct static_params : public figure_static_params {
        uint16_t fish_per_trip;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        bool had_home;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    //virtual e_overlay get_overlay() const override { return OVERLAY_APOTHECARY; }
    virtual sound_key phrase_key() const override;
    virtual bool window_info_background(object_info &ctx) override;
    virtual void update_animation() override;
};
ANK_CONFIG_STRUCT(figure_fishing_boat::static_params, fish_per_trip)
