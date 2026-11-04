#pragma once

#include "figure_animal.h"

// OG figure_birds_action (0x0049B750) herd action states (figure_action.h HERD_*).
enum e_birds_action {
    ACTION_8_BIRDS_CHOOSE = 8,
    ACTION_9_BIRDS_MOVE = 9,
    ACTION_10_BIRDS_WALK = 10,
    ACTION_12_BIRDS_HUNTED = 12,
    ACTION_14_BIRDS_ALERT = 14,
    ACTION_15_BIRDS_ALERTED_BY_MATE = 15,
    ACTION_16_BIRDS_FLEE = 16,
    ACTION_17_BIRDS_STAMPEDE = 17,
    ACTION_18_BIRDS_REST = 18,
    ACTION_19_BIRDS_GRAZE = 19,
    ACTION_24_BIRDS_SPAWNED = 24,

    // Aliases kept for existing tests / call sites.
    ACTION_8_BIRDS_RECALCULATE = ACTION_8_BIRDS_CHOOSE,
    ACTION_10_BIRDS_GOING = ACTION_10_BIRDS_WALK,
    ACTION_15_BIRDS_TERRIFIED = ACTION_15_BIRDS_ALERTED_BY_MATE,
    ACTION_16_BIRDS_FLEEING = ACTION_16_BIRDS_FLEE,
    ACTION_18_BIRDS_ROOSTING = ACTION_18_BIRDS_REST,
    ACTION_19_BIRDS_IDLE = ACTION_19_BIRDS_GRAZE,
};

class figure_birds : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_BIRDS, figure_birds)
    figure_birds(figure *f) : figure_animal(f) {}

    struct static_params : public figure_static_params {
        uint8_t scared_ticks;
        uint16_t rest_base_ticks;
        uint16_t rest_random_ticks;
        uint16_t no_tile_wait_ticks;
        uint16_t dying_ticks;

        void archive_init();
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        int8_t applied_damage;
        uint8_t scared_ticks;
        uint8_t flock_frame;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void main_image_update() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;
    virtual void apply_damage(int hit_dmg, figure_id attacker_id) override;

    virtual void herd_moved() override;
    virtual void herd_rest() override;
    virtual void herd_scare() override;
    virtual void moveto(tile2i tile) override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

private:
    void walk_near_home();
    void begin_rest();
    int move_speed() const;
};

ANK_CONFIG_STRUCT(figure_birds::static_params, scared_ticks, rest_base_ticks, rest_random_ticks, no_tile_wait_ticks,
                  dying_ticks)
