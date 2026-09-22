#pragma once

#include "figure/figure.h"

enum e_tax_collector_action {
    ACTION_0_TAX_COLLECTOR_CREATED = 0,
    ACTION_1_TAX_COLLECTOR_ENTERING_EXITING = 1,
    ACTION_2_TAX_COLLECTOR_ROAMING = 2,
    ACTION_3_TAX_COLLECTOR_RETURNING = 3,

    ACTION_4_TAX_COLLECTOR_MAX
};
using e_tax_collector_action_tokens_t = token_holder<e_tax_collector_action, ACTION_0_TAX_COLLECTOR_CREATED, ACTION_4_TAX_COLLECTOR_MAX>;
extern const e_tax_collector_action_tokens_t e_tax_collector_action_tokens;

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
    virtual int provide_service() override;
};
