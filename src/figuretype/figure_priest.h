#pragma once

#include "figure/figure.h"

class figure_priest : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PRIEST,figure_priest)
    figure_priest(figure *f) : figure_impl(f) {}

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override;
    virtual void update_animation() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};