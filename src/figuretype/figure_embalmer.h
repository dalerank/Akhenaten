#pragma once

#include "figure/figure.h"

class figure_embalmer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_EMBALMER, figure_embalmer)
    figure_embalmer(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_EMBALMER, "embalmer" }; }
    //virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_SCRIBAL_SCHOOL; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};