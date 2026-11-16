#pragma once

#include "figure/figure.h"

enum e_law_walker_action {
    ACTION_70_LAW_WALKER_CREATED = 70,
    ACTION_71_LAW_WALKER_ENTERING_EXITING = 71,
    ACTION_72_LAW_WALKER_ROAMING = 72,
    ACTION_73_LAW_WALKER_RETURNING = 73,
    ACTION_76_LAW_WALKER_CHASE = 76,
};

enum e_law_walker_limits {
    LAW_WALKER_ANIMATION_FRAMES = 12,
};

// OG walkers.c law_walker_action: the constable and the magistrate share one state machine; only the constable
// looks for enemies, chases them and plays an attack sound.
class figure_law_walker : public figure_impl {
public:
    figure_law_walker(figure* f) : figure_impl(f) {}

    struct runtime_data_t {
        uint8_t wait_ticks_next_target;
        uint8_t walk_frame;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override { law_walker_action(); }
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual void acquire_attack() override;

protected:
    virtual int home_road_radius() const = 0;
    virtual void on_walk_cycle(bool wrapped) {}
    virtual void on_attack_tick() {}

    void law_walker_action();
    void law_walker_chase();
    void return_home();
    tile2i home_road() const;
};
