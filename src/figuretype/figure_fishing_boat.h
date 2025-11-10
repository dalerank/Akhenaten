#pragma once

#include "figure/figure.h"

enum e_fishing_boat_action : uint16_t {
    FIGURE_ACTION_190_FISHING_BOAT_CREATED = 190,
    FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH = 191,
    FIGURE_ACTION_192_FISHING_BOAT_FISHING = 192,
    FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF = 193,
    FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF = 194,
    FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH = 195,
    FIGURE_ACTION_196_FISHING_BOAT_RANDOM_FPOINT = 196,
    FIGURE_ACTION_196_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN = 197,
    FIGURE_ACTION_196_FISHING_BOAT_RETURN_TO_RANDOM_WHARF = 198,
};

class figure_fishing_boat : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FISHING_BOAT, figure_fishing_boat)
    figure_fishing_boat(figure *f) : figure_impl(f) {}
    virtual figure_fishing_boat *dcast_fishing_boat() override { return this; }

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
    virtual figure_sound_t get_sound_reaction(xstring key) const override { return {}; }
    virtual bool window_info_background(object_info &ctx) override;
    virtual void update_animation() override;
};
