#pragma once

#include "figure/figure.h"

enum e_festival_priest_action {
    ACTION_10_FESTIVAL_PRIEST_CREATED = 10,
    ACTION_11_FESTIVAL_PRIEST_GOTO_SQUARE = 11,
    ACTION_12_FESTIVAL_PRIEST_DANCE = 12,
    ACTION_13_FESTIVAL_PRIEST_GOTO_HOME = 13,
};

class figure_festival_priest : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FESTIVAL_PRIEST, figure_festival_priest)
    figure_festival_priest(figure* f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int8_t trips; // OG walkers.c walker_rules[WALKER_RULE_FESTIVAL_TRIPS]
    } FIGURE_STATIC_DATA_T;
    virtual figure_festival_priest* dcast_festival_priest() override { return this; }

    struct runtime_data_t {
        int8_t festival_remaining_dances;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void before_poof() override;
    virtual void update_animation() override;
};
ANK_CONFIG_STRUCT(figure_festival_priest::static_params, trips)
