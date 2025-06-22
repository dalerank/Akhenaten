#pragma once

#include "figure/figure.h"

enum e_stonemason_action : uint16_t {
    FIGURE_ACTION_10_MASON_CREATED = 10,
    FIGURE_ACTION_11_MASON_GOING = 11,
    FIGURE_ACTION_14_MASON_WORK_GROUND = 14,
    FIGURE_ACTION_14_MASON_WORK_WALL = 15,
    FIGURE_ACTION_16_MASON_RETURN_HOME = 16,
    FIGURE_ACTION_20_MASON_DESTROY = 20,
};

class figure_stonemason : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_STONEMASON, figure_stonemason)
    figure_stonemason(figure *f) : figure_impl(f) {}

    struct static_params : public figure_model {
    };

    virtual void on_create() override {}
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_STONEMASON, "mason" }; }
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    //virtual bool is_common_roaming() override { return false; }
    //virtual sound_key phrase_key() const override;
};