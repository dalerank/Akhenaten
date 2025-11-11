#pragma once

#include "figure/figure.h"

enum e_reed_gatherer_action {
    ACTION_8_REED_GATHERER_RECALCULATE = 8,
    ACTION_9_REED_GATHERER_GOTO_RESOURCE = 9,
    ACTION_10_REED_GATHERER_WORK = 10,
    ACTION_11_REED_GATHERER_RETURN_HOME = 11,
    ACTION_14_REED_GATHERER_CREATED = 14,
};

class figure_reed_gatherer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_REED_GATHERER, figure_reed_gatherer)
    figure_reed_gatherer(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int max_amount;
    } FIGURE_STATIC_DATA_T;

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};
ANK_CONFIG_STRUCT(figure_reed_gatherer::static_params, max_amount)
