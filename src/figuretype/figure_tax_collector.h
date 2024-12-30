#pragma once

#include "figure/figure.h"

class figure_tax_collector : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TAX_COLLECTOR, figure_tax_collector)
    figure_tax_collector(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_TAX_COLLECTOR, "taxman"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_TAX_INCOME; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
    virtual const animations_t &anim() const override;
};