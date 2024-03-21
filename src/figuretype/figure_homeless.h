#pragma once

#include "figure/figure.h"

class figure_homeless : public figure_impl {
public:
    figure_homeless(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_HOMELESS, "homeless"}; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual bool is_common_roaming() override { return false; }
    //virtual sound_key phrase_key() const override;
};

void figure_create_homeless(tile2i tile, int num_people);