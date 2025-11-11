#pragma once

#include "figure/figure.h"

enum e_physician_action {
    ACTION_60_PHYSICIAN_CREATED = 60,
    ACTION_61_PHYSICIAN_ENTERING_EXITING = 61,
    ACTION_62_PHYSICIAN_ROAMING = 62,
    ACTION_63_PHYSICIAN_RETURNING = 63,
};

class figure_physician : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PHYSICIAN, figure_physician)
    figure_physician(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_PHYSICIAN; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};