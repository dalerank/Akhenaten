#pragma once

#include "core/svector.h"
#include "figure_animal.h"

// OG figure_crocodile_action (0x0049D0F0) / PREDATOR_* + CROCODILE_GO_TO_WATER.
enum e_crocodile_action : uint16_t {
    ACTION_8_CROCODILE_CHOOSE = 8,
    ACTION_9_CROCODILE_WALK = 9,
    ACTION_10_CROCODILE_MOVE = 10,
    ACTION_12_CROCODILE_DYING = 12,
    ACTION_13_CROCODILE_PROWL = 13,
    ACTION_18_CROCODILE_REST = 18,
    ACTION_19_CROCODILE_GO_TO_WATER = 19,
    ACTION_20_CROCODILE_LOOK_FOR_PREY = 20,
    ACTION_21_CROCODILE_CHASE = 21,
    ACTION_23_CROCODILE_RETURN_TO_HERD = 23,
    ACTION_24_CROCODILE_SPAWNED = 24,

    // Aliases kept for older remake call sites / docs.
    ACTION_8_RECALCULATE = ACTION_8_CROCODILE_CHOOSE,
    ACTION_10_CROCODILE_MOVING = ACTION_10_CROCODILE_MOVE,
    ACTION_19_CROCODILE_IDLE = ACTION_19_CROCODILE_GO_TO_WATER,
};

class figure_crocodile : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_CROCODILE, figure_crocodile)
    figure_crocodile(figure *f) : figure_animal(f) {}

    struct static_params : public figure_static_params {
        uint16_t rest_base_ticks;
        uint16_t rest_random_ticks;
        uint16_t no_tile_wait_ticks;
        uint16_t dying_ticks;
        uint16_t hunt_delay;
        uint16_t hunt_radius;
        uint16_t chase_ticks_per_ring;
        uint8_t water_chance_idle;
        uint8_t water_chance_in_water;
        uint8_t water_chance_other;
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
    bool in_deep_water() const;
    void tick_anim_frame();
    void start_action(int action);
    void choose_next_action();
    void go_to_water();
    bool walk_near(tile2i center, int random_dir);
    void end_chase();
    bool find_prey_nearby();
    int find_prey_in_radius(int radius) const;

    static void reseed_crt_rand();
    bool is_prey_candidate(const figure *f) const;
    int prey_on_tile(tile2i tile) const;
};

ANK_CONFIG_STRUCT(figure_crocodile::static_params,
    rest_base_ticks, rest_random_ticks, no_tile_wait_ticks, dying_ticks,
    hunt_delay, hunt_radius, chase_ticks_per_ring,
    water_chance_idle, water_chance_in_water, water_chance_other,
    forbidden_prey)
