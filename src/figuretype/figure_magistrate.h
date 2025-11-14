#pragma once

#include "figure/figure.h"

enum e_magistrate_action {
    ACTION_10_MAGISTRATE_GOING = 10,
    ACTION_70_MAGISTRATE_CREATED = 70,
    ACTION_71_MAGISTRATE_ENTERING_EXITING = 71,
    ACTION_72_MAGISTRATE_ROAMING = 72,
    ACTION_73_MAGISTRATE_RETURNING = 73,
    ACTION_76_MAGISTRATE_GOING_TO_ENEMY = 76,
    ACTION_77_MAGISTRATE_AT_ENEMY = 77,
    ACTION_125_MAGISTRATE_ROAMING = 125,
};

class figure_magistrate : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MAGISTRATE, figure_magistrate)
    figure_magistrate(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_COUTHOUSE; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};