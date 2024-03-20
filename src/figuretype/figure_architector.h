#pragma once

#include "figure/figure.h"

class figure_architector : public figure_impl {
public:
    figure_architector(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_ARCHITECT, "engineer"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_DAMAGE; }
    virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};