#pragma once

#include "figure_animal.h"

// OG figure_antelope_action (0x0049C750). Primary names keep JS test tokens stable.
enum e_antelope_action {
    ACTION_8_ANTELOPE_RECALCULATE = 8, // OG HERD_CHOOSE
    ACTION_9_ANTELOPE_MOVE = 9,
    ACTION_10_ANTELOPE_GOING = 10, // OG HERD_WALK
    ACTION_12_ANTELOPE_HUNTED = 12,
    ACTION_14_ANTELOPE_ALERT = 14,
    ACTION_15_ANTELOPE_TERRIFIED = 15, // OG HERD_ALERTED_BY_MATE
    ACTION_16_ANTELOPE_FLEEING = 16,   // OG HERD_FLEE
    ACTION_17_ANTELOPE_STAMPEDE = 17,
    ACTION_18_ANTELOPE_ROOSTING = 18, // OG HERD_REST
    ACTION_19_ANTELOPE_IDLE = 19,     // OG HERD_GRAZE
    ACTION_24_ANTELOPE_SPAWNED = 24,
    ACTION_196_ANTELOPE_AT_REST = 196,

    ACTION_8_ANTELOPE_CHOOSE = ACTION_8_ANTELOPE_RECALCULATE,
    ACTION_10_ANTELOPE_WALK = ACTION_10_ANTELOPE_GOING,
    ACTION_15_ANTELOPE_ALERTED_BY_MATE = ACTION_15_ANTELOPE_TERRIFIED,
    ACTION_16_ANTELOPE_FLEE = ACTION_16_ANTELOPE_FLEEING,
    ACTION_18_ANTELOPE_REST = ACTION_18_ANTELOPE_ROOSTING,
    ACTION_19_ANTELOPE_GRAZE = ACTION_19_ANTELOPE_IDLE,
};

class figure_antelope : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_ANTELOPE, figure_antelope)
    figure_antelope(figure *f) : figure_animal(f) {}
    virtual figure_antelope *dcast_antelope() override { return this; }

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

ANK_CONFIG_STRUCT(figure_antelope::static_params, scared_ticks, rest_base_ticks, rest_random_ticks, no_tile_wait_ticks,
                  dying_ticks, alert_ticks)
