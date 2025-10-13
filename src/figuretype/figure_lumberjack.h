#pragma once

#include "figure/figure.h"

enum e_lumberjack_action {
    ACTION_8_LUMBERJACK_RECALCULATE = 8,
    ACTION_9_LUMBERJACK_GOTO_RESOURCE = 9,
    ACTION_10_LUMBERJACK_WORK = 10,
    ACTION_11_LUMBERJACK_RETURN_HOME = 11,
    ACTION_14_LUMBERJACK_CREATED = 14,
};

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
    virtual figure_phrase_t phrase() const override { return {FIGURE_LUMBERJACK, "woodcutter"}; }
    virtual void update_animation() override;
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};
ANK_CONFIG_STRUCT(figure_lumberjack::static_params,
    max_amount)