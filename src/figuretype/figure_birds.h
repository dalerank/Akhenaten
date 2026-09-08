#pragma once

#include "figure_animal.h"

enum e_birds_action {
    ACTION_8_BIRDS_RECALCULATE = 8,
    ACTION_10_BIRDS_GOING = 10,
    ACTION_16_BIRDS_FLEEING = 16,
    ACTION_15_BIRDS_TERRIFIED = 15,
    ACTION_18_BIRDS_ROOSTING = 18,
    ACTION_19_BIRDS_IDLE = 19,
    ACTION_24_BIRDS_SPAWNED = 24,
    ACTION_196_BIRDS_AT_REST = 196,
};

class figure_birds : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_BIRDS, figure_birds)
    figure_birds(figure *f) : figure_animal(f) {}

    struct static_params : public figure_static_params {
        uint8_t scared_ticks;

        void archive_init();
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        int8_t applied_damage;
        uint8_t scared_ticks;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;
    virtual void apply_damage(int hit_dmg, figure_id attacker_id) override;

    virtual void herd_moved() override;
    virtual void herd_rest() override;
    virtual void herd_scare() override;
    virtual void moveto(tile2i tile) override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};
ANK_CONFIG_STRUCT(figure_birds::static_params, scared_ticks)
