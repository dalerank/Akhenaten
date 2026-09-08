#pragma once

#include "figure/figure.h"

enum e_governor_action : uint16_t {
    ACTION_0_GOVERNOR_CREATED = 0,
    ACTION_1_GOVERNOR_MOVING = 1,

    ACTION_2_GOVERNOR_MAX
};
using e_governor_action_tokens_t = token_holder<e_governor_action, ACTION_0_GOVERNOR_CREATED, ACTION_2_GOVERNOR_MAX>;
extern const e_governor_action_tokens_t e_governor_action_tokens;

class figure_governor : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_GOVERNOR, figure_governor)
    figure_governor(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
};
