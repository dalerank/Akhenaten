#pragma once

#include "figure_animal.h"
#include "core/tokenum.h"

// OG figure_ostrich_action (0x0049BD40). Primary names keep JS test tokens stable.
enum e_ostrich_action {
    ACTION_0_OSTRICH_NONE = 0,
    ACTION_8_OSTRICH_RECALCULATE = 8, // OG HERD_CHOOSE
    ACTION_9_OSTRICH_MOVE = 9,
    ACTION_10_OSTRICH_GOING = 10, // OG HERD_WALK
    ACTION_12_OSTRICH_HUNTED = 12,
    ACTION_14_OSTRICH_ALERT = 14,
    ACTION_15_OSTRICH_TERRIFIED = 15, // OG HERD_ALERTED_BY_MATE
    ACTION_16_OSTRICH_FLEEING = 16,   // OG HERD_FLEE
    ACTION_17_OSTRICH_STAMPEDE = 17,
    ACTION_18_OSTRICH_ROOSTING = 18, // OG HERD_REST
    ACTION_19_OSTRICH_IDLE = 19,     // OG HERD_GRAZE
    ACTION_24_OSTRICH_SPAWNED = 24,
    ACTION_196_OSTRICH_AT_REST = 196,

    ACTION_8_OSTRICH_CHOOSE = ACTION_8_OSTRICH_RECALCULATE,
    ACTION_10_OSTRICH_WALK = ACTION_10_OSTRICH_GOING,
    ACTION_15_OSTRICH_ALERTED_BY_MATE = ACTION_15_OSTRICH_TERRIFIED,
    ACTION_16_OSTRICH_FLEE = ACTION_16_OSTRICH_FLEEING,
    ACTION_18_OSTRICH_REST = ACTION_18_OSTRICH_ROOSTING,
    ACTION_19_OSTRICH_GRAZE = ACTION_19_OSTRICH_IDLE,

    ACTION_197_OSTRICH_MAX
};
using e_ostrich_action_tokens_t = token_holder<e_ostrich_action, ACTION_0_OSTRICH_NONE, ACTION_197_OSTRICH_MAX>;
extern const e_ostrich_action_tokens_t e_ostrich_action_tokens;

class figure_ostrich : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_OSTRICH, figure_ostrich)
    figure_ostrich(figure *f) : figure_animal(f) {}
    virtual figure_ostrich *dcast_ostrich() override { return this; }

    struct static_params : public figure_static_params {
        uint8_t scared_ticks;
        uint16_t rest_base_ticks;
        uint16_t rest_random_ticks;
        uint16_t no_tile_wait_ticks;
        uint16_t dying_ticks;
        uint16_t alert_ticks;

        void archive_init();
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        int8_t applied_damage;
        uint8_t scared_ticks;
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
    void begin_choose();
    void begin_rest_or_graze();
    void walk_near_destination();
    void start_flee();
    int move_speed() const;
};

ANK_CONFIG_STRUCT(figure_ostrich::static_params, scared_ticks, rest_base_ticks, rest_random_ticks, no_tile_wait_ticks,
                  dying_ticks, alert_ticks)
