#pragma once

#include "figure/figure.h"

class figure_priest : public figure_impl {
public:
    figure_priest(figure *f) : figure_impl(f) {}

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_PRIEST, "priest"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override;
    virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};