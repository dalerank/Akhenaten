#pragma once

#include "figure/figure.h"

class figure_fishing_boat : public figure_impl {
public:
    figure_fishing_boat(figure *f) : figure_impl(f) {}
    virtual figure_fishing_boat *dcast_fishing_boat() override { return this; }

    virtual void on_create() override {}
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_FISHING_BOAT, "fishing"}; }
    //virtual e_overlay get_overlay() const override { return OVERLAY_APOTHECARY; }
    virtual sound_key phrase_key() const override { return {}; }
    virtual figure_sound_t get_sound_reaction(pcstr key) const override { return {}; }
    virtual bool window_info_background(object_info &ctx) override;
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;
};
