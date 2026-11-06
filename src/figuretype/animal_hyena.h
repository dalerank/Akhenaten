#pragma once

#include "core/svector.h"
#include "figure_animal.h"

// OG figure_hyena_action → wild_predator_action(WILD_HYENA) in animals_wild.c.
enum e_hyena_action : uint16_t {
    ACTION_8_HYENA_CHOOSE = 8,
    ACTION_9_HYENA_WALK = 9,
    ACTION_10_HYENA_MOVE = 10,
    ACTION_12_HYENA_DYING = 12,
    ACTION_13_HYENA_PROWL = 13,
    ACTION_18_HYENA_REST = 18,
    ACTION_19_HYENA_IDLE = 19,
    ACTION_20_HYENA_LOOK_FOR_PREY = 20,
    ACTION_21_HYENA_CHASE = 21,
    ACTION_23_HYENA_RETURN_TO_HERD = 23,
    ACTION_24_HYENA_SPAWNED = 24,

    // Aliases for older remake call sites.
    ACTION_8_HYENA_RECALCULATE = ACTION_8_HYENA_CHOOSE,
    ACTION_10_HYENA_MOVING = ACTION_10_HYENA_MOVE,
    ACTION_24_HYENA_CREATED = ACTION_24_HYENA_SPAWNED,
};

class figure_hyena : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_HYENA, figure_hyena)
    figure_hyena(figure *f) : figure_animal(f) {}

    struct static_params : public figure_static_params {
        uint16_t rest_base_ticks;
        uint16_t rest_random_ticks;
        uint16_t no_tile_wait_ticks;
        uint16_t dying_ticks;
        uint16_t hunt_delay;
        uint16_t hunt_radius;
        uint16_t chase_ticks_per_ring;
        uint8_t prowl_speed_factor;
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
    void tick_anim_frame();
    void set_rest_wait();
    void start_rest_or_idle();
    void choose_next_action();
    bool walk_near_herd(int random_dir);
    void end_chase();
    bool find_prey_nearby();
    int find_prey_in_radius(int radius) const;

    static void reseed_crt_rand();
    bool is_prey_candidate(const figure *f) const;
    int prey_on_tile(tile2i tile) const;
};

ANK_CONFIG_STRUCT(figure_hyena::static_params,
    rest_base_ticks, rest_random_ticks, no_tile_wait_ticks, dying_ticks,
    hunt_delay, hunt_radius, chase_ticks_per_ring, prowl_speed_factor,
    forbidden_prey)

int figure_combat_get_target_for_hyena(tile2i tile, int max_distance);
