#pragma once

#include "figure/figure.h"

enum e_tax_collector_action {
    ACTION_40_TAX_COLLECTOR_CREATED = 40,
    ACTION_41_TAX_COLLECTOR_ENTERING_EXITING = 41,
    ACTION_42_TAX_COLLECTOR_ROAMING = 42,
    ACTION_43_TAX_COLLECTOR_RETURNING = 43,
};

class figure_tax_collector : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TAX_COLLECTOR, figure_tax_collector)
    figure_tax_collector(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        short poor_taxed;
        short middle_taxed;
        short reach_taxed;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_TAX_COLLECTOR, "taxman"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_TAX_INCOME; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};