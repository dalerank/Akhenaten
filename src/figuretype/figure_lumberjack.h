#pragma once

#include "figure/figure.h"

enum e_lumberjack_action : uint16_t {
    ACTION_0_LUMBERJACK_CREATED = 0,
    ACTION_1_LUMBERJACK_RECALCULATE = 1,
    ACTION_2_LUMBERJACK_GOTO_RESOURCE = 2,
    ACTION_3_LUMBERJACK_WORK = 3,
    ACTION_4_LUMBERJACK_RETURN_HOME = 4,

    ACTION_5_LUMBERJACK_MAX
};
using e_lumberjack_action_tokens_t = token_holder<e_lumberjack_action, ACTION_0_LUMBERJACK_CREATED, ACTION_5_LUMBERJACK_MAX>;
extern const e_lumberjack_action_tokens_t e_lumberjack_action_tokens;

class figure_lumberjack : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LUMBERJACK, figure_lumberjack)
    figure_lumberjack(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int max_amount;
    } FIGURE_STATIC_DATA_T;

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
};
ANK_CONFIG_STRUCT(figure_lumberjack::static_params,
    max_amount)
