#pragma once

#include "figure/figure.h"

class figure_physician : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PHYSICIAN, figure_physician)
    figure_physician(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_PHYSICIAN, "doctor"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_PHYSICIAN; }
    virtual const animations_t &anim() const override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};