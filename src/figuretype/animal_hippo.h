#pragma once

#include "core/svector.h"
#include "figure_animal.h"

// OG figure_hippo_action (animals.c) / PREDATOR_* + HIPPO_GO_TO_WATER/CHARGE/ANIMATE.
enum e_hippo_action : uint16_t {
    ACTION_8_HIPPO_CHOOSE = 8,
    ACTION_9_HIPPO_WALK = 9,
    ACTION_10_HIPPO_MOVE = 10,
    ACTION_12_HIPPO_DYING = 12,
    ACTION_13_HIPPO_PROWL = 13,
    ACTION_18_HIPPO_REST = 18,
    ACTION_19_HIPPO_GO_TO_WATER = 19,
    ACTION_20_HIPPO_LOOK_FOR_PREY = 20,
    ACTION_21_HIPPO_CHASE = 21,
    ACTION_23_HIPPO_RETURN_TO_HERD = 23,
    ACTION_24_HIPPO_SPAWNED = 24,
    ACTION_25_HIPPO_CHARGE = 25,
    ACTION_26_HIPPO_ANIMATE = 26,

    // Aliases for older call sites / tests.
    ACTION_8_HIPPO_RECALCULATE = ACTION_8_HIPPO_CHOOSE,
    ACTION_10_HIPPO_GOING = ACTION_10_HIPPO_MOVE,
    ACTION_19_HIPPO_IDLE = ACTION_19_HIPPO_GO_TO_WATER,
    ACTION_18_HIPPO_ROOSTING = ACTION_18_HIPPO_REST,
};

class figure_hippo : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_HIPPO, figure_hippo)
    figure_hippo(figure *f) : figure_animal(f) {}
    virtual figure_hippo *dcast_hippo() override { return this; }

    struct static_params : public figure_static_params {
        uint16_t rest_base_ticks;
        uint16_t rest_random_ticks;
        uint16_t no_tile_wait_ticks;
        uint16_t dying_ticks;
        uint16_t hunt_delay;
        uint16_t hunt_radius;
        uint16_t chase_ticks_per_ring;
        uint16_t animate_ticks;
        uint16_t after_hunt_ticks;
        svector<uint8_t, 4> choice_idle;
        svector<uint8_t, 4> choice_in_water;
        svector<uint8_t, 4> choice_animating;
        svector<uint8_t, 4> choice_other;
        svector<e_figure_type, 16> forbidden_prey;

        void archive_init();
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t hunt_ticks;
        uint8_t anim_tick;
        uint8_t frame_count;
        uint8_t frame_advanced;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void main_image_update() override;
    virtual void acquire_attack() override;
    virtual bool play_die_sound() override;

    virtual void herd_moved() override;
    virtual void herd_rest() override;
    virtual void moveto(tile2i tile) override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

private:
    int move_speed() const;
    int charge_speed() const;
    bool in_deep_water() const;
    void tick_anim_frame();
    void start_action(int action);
    void choose_next_action();
    void hunt_or_choose_action();
    void go_to_water();
    bool walk_near(tile2i center, int random_dir);
    void end_chase();
    bool find_prey_nearby();
    int find_prey_in_radius(int radius) const;
    int weighted_choice(const svector<uint8_t, 4> &weights) const;

    static void reseed_crt_rand();
    bool is_prey_candidate(const figure *f) const;
    int prey_on_tile(tile2i tile) const;
};

ANK_CONFIG_STRUCT(figure_hippo::static_params,
    rest_base_ticks, rest_random_ticks, no_tile_wait_ticks, dying_ticks,
    hunt_delay, hunt_radius, chase_ticks_per_ring, animate_ticks, after_hunt_ticks,
    choice_idle, choice_in_water, choice_animating, choice_other,
    forbidden_prey)
