#pragma once

#include "figure/figure.h"

enum e_figure_ostrich_hunber : uint16_t {
    ACTION_9_OSTRICH_HUNTER_CHASE_PREY = 9,
    ACTION_11_OSTRICH_HUNTER_WALK = 11,
    ACTION_12_OSTRICH_HUNTER_MOVE_PACKED = 12,
    ACTION_14_OSTRICH_HUNTER_UNLOADING = 14,
    ACTION_15_OSTRICH_HUNTER_HUNT = 15,
    ACTION_16_OSTRICH_HUNTER_INVESTIGATE = 16,
    ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED = 17,
    ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED = 18,
};

class figure_ostrich_hunter : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_OSTRICH_HUNTER, figure_ostrich_hunter)
    figure_ostrich_hunter(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t max_hunting_distance;
        int8_t missile_delay;

        void archive_init();
    } FIGURE_STATIC_DATA_T;

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    //virtual void poof() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_OSTRICH_HUNTER, "oshunter"}; }
    virtual sound_key phrase_key() const override;
    virtual figure_sound_t get_sound_reaction(pcstr key) const;
    virtual void update_animation() override;
};
ANK_CONFIG_STRUCT(figure_ostrich_hunter::static_params,
    max_hunting_distance, missile_delay)