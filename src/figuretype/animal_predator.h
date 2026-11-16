#pragma once

#include "core/svector.h"
#include "figure_animal.h"

struct formation;

enum e_predator_action : uint16_t {
    ACTION_8_PREDATOR_CHOOSE = 8,
    ACTION_9_PREDATOR_WALK = 9,
    ACTION_10_PREDATOR_MOVE = 10,
    ACTION_12_PREDATOR_DYING = 12,
    ACTION_13_PREDATOR_PROWL = 13,
    ACTION_18_PREDATOR_REST = 18,
    ACTION_19_PREDATOR_IDLE = 19,
    ACTION_20_PREDATOR_LOOK_FOR_PREY = 20,
    ACTION_21_PREDATOR_CHASE = 21,
    ACTION_23_PREDATOR_RETURN_TO_HERD = 23,
    ACTION_24_PREDATOR_SPAWNED = 24,

    ACTION_25_PREDATOR_RAID_LOOK_FOR_PREY = 25,
    ACTION_26_PREDATOR_RAID_CHASE = 26,
    ACTION_27_PREDATOR_RAID_ATTACK = 27,
    ACTION_28_PREDATOR_RAID_INVESTIGATE = 28,
};

enum e_predator_herd_offsets {
    PREDATOR_HERD_OFFSET_COUNT = 16,
};

struct predator_static_params : public figure_static_params {
    bool reset_frame_on_walk;
    bool death_has_directions;

    uint16_t rest_base_ticks;
    uint16_t rest_random_ticks;
    uint16_t arrival_rest_base_ticks;
    uint16_t no_tile_wait_ticks;
    uint16_t no_tile_wait_random_ticks;
    uint16_t dying_ticks;
    uint16_t chase_ticks_per_ring;
    uint16_t hunt_delay;
    uint16_t hunt_radius;
    svector<uint8_t, 4> move_cycle;
    svector<uint8_t, 4> prowl_cycle;
    svector<e_figure_type, 16> forbidden_prey;
    xstring attack_sound;
    xstring die_sound;

    uint8_t herd_spawn_delay;
    uint8_t herd_move_delay;
    uint8_t herd_roam_radius;
    bool herd_spawn_only_when_present;
    uint8_t herd_spawn_wait_range;
    uint8_t herd_spawn_wait_factor;
    uint8_t herd_new_animal_wait;
    svector<uint32_t, 16> herd_allowed_terrain;
    svector<uint32_t, 16> herd_blocked_terrain;
    svector<uint32_t, 16> herd_special_terrain;

    uint16_t raid_hunt_distance;
    uint8_t raid_chase_speed_mult;
    svector<e_figure_type, 32> raid_non_targets;

    uint32_t allowed_mask;
    uint32_t blocked_mask;
    uint32_t special_mask;
    void archive_load(archive arch);
};
ANK_CONFIG_STRUCT(predator_static_params, reset_frame_on_walk, death_has_directions, rest_base_ticks, rest_random_ticks,
  arrival_rest_base_ticks, no_tile_wait_ticks, no_tile_wait_random_ticks, dying_ticks, chase_ticks_per_ring, hunt_delay,
  hunt_radius, move_cycle, prowl_cycle, forbidden_prey, attack_sound, die_sound, herd_spawn_delay, herd_move_delay,
  herd_roam_radius, herd_spawn_only_when_present, herd_spawn_wait_range, herd_spawn_wait_factor, herd_new_animal_wait,
  herd_allowed_terrain, herd_blocked_terrain, herd_special_terrain, raid_hunt_distance, raid_chase_speed_mult,
  raid_non_targets)

class figure_predator : public figure_animal {
public:
    figure_predator(figure* f) : figure_animal(f) {}
    virtual figure_predator* dcast_predator() override { return this; }

    struct runtime_data_t {
        uint8_t hunt_ticks;
        uint8_t frame;
        uint8_t curse_raid;
        uint8_t frame_count;
        uint16_t raid_days_left;
        uint8_t move_speed_counter;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void before_poof() override;
    virtual void figure_roaming_action() override {}
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void main_image_update() override;
    virtual void update_day() override;
    virtual void acquire_attack() override;
    virtual bool play_die_sound() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

    void setup_curse_raid(int days);
    bool is_curse_raid() const;

    static void create_herd_animals(formation& herd, e_figure_type type, int count);
    static void update_herd(formation& herd);

private:
    const predator_static_params& predator_config() const;
    xstring resolve_anim(xstring anim_key) const;
    uint8_t anim_cycle(const xstring& anim_key) const;
    void set_action_cycle(int action);
    void apply_action_frames();
    void move(const svector<uint8_t, 4>& cycle);
    void set_rest_wait(uint16_t base_ticks);
    void set_no_tile_wait();
    bool walk_near(const formation* herd);
    void end_chase();
    bool find_prey_nearby();
    int find_prey_in_rings(int rings) const;
    int prey_on_tile(tile2i tile) const;

    void raid_action();
    void release_target();
    int find_raid_prey();
    bool is_raid_prey(figure* f) const;
};

void figure_predator_setup_curse_raid(figure& f, int days);
