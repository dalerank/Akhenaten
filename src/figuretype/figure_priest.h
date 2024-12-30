#pragma once

#include "figure/figure.h"

class figure_priest : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PRIEST,figure_priest)
    figure_priest(figure *f) : figure_impl(f) {}

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_PRIEST, "priest"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override;
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};

class figure_festival_priest : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FESTIVAL_PRIEST, figure_festival_priest)
    figure_festival_priest(figure *f) : figure_impl(f) {}

    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void before_poof() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_FESTIVAL_PRIEST, "festival"}; }
    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION; }
    virtual const animations_t &anim() const override;
};