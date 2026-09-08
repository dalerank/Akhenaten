#pragma once

#include "figure/figure.h"

enum e_noble_action : uint16_t {
    ACTION_0_NOBLE_ROAMING = 0,
    ACTION_1_NOBLE_RETURNING = 1,

    ACTION_2_NOBLE_MAX
};
using e_noble_action_tokens_t = token_holder<e_noble_action, ACTION_0_NOBLE_ROAMING, ACTION_2_NOBLE_MAX>;
extern const e_noble_action_tokens_t e_noble_action_tokens;

class figure_noble : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_NOBLES, figure_noble)
    figure_noble(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        int8_t applied_damage;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void before_poof() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};
