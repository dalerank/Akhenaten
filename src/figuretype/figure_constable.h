#pragma once

#include "figure/figure.h"

enum e_constable_action {
    ACTION_70_CONSTABLE_CREATED = 70,
    ACTION_71_CONSTABLE_ENTERING_EXITING = 71,
    ACTION_72_CONSTABLE_ROAMING = 72,
    ACTION_73_CONSTABLE_RETURNING = 73,
    ACTION_74_CONSTABLE_REQUESTING_WEAPONS = 74,
    ACTION_76_CONSTABLE_GOING_TO_ENEMY = 76,
    ACTION_77_CONSTABLE_AT_ENEMY = 77,
    ACTION_150_CONSTABLE_ATTACK = 150,
};

class figure_constable : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CONSTABLE, figure_constable)
    figure_constable(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        uint8_t wait_ticks_next_target;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual int provide_service() override;

    bool fight_enemy(int category, int max_distance);
    // Arrest nearby criminal (tomb robber / mugger). force skips the TEMP 75% roll.
    bool try_arrest_criminal(int max_distance, bool force = false);
};