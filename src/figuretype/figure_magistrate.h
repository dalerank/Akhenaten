#pragma once

#include "figure/figure.h"

class figure_magistrate : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MAGISTRATE, figure_magistrate)
    figure_magistrate(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_MAGISTRATE, "magistrate"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_COUTHOUSE; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};