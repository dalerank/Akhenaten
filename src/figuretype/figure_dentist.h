#pragma once

#include "figure/figure.h"

class figure_dentist : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_DENTIST, figure_dentist)
    figure_dentist(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_DENTIST, "dentist"}; }
    //virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_DENTIST; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};