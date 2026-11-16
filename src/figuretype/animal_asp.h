#pragma once

#include "core/svector.h"
#include "figure_animal.h"

struct formation;

// OG figure_asp_action (animals.c) on the FIGURE_ACTION_PREDATOR_* states.
enum e_asp_action : uint16_t {
    ACTION_8_ASP_CHOOSE = 8,
    ACTION_9_ASP_WALK = 9,
    ACTION_10_ASP_MOVE = 10,
    ACTION_12_ASP_DYING = 12,
    ACTION_13_ASP_PROWL = 13,
    ACTION_18_ASP_REST = 18,
    ACTION_19_ASP_IDLE = 19,
    ACTION_20_ASP_LOOK_FOR_PREY = 20,
    ACTION_21_ASP_CHASE = 21,
    ACTION_23_ASP_RETURN_TO_HERD = 23,
    ACTION_24_ASP_SPAWNED = 24,

    // Seth curse raid (gameplay_seth_asp_raid), not in OG.
    ACTION_25_ASP_RAID_LOOK_FOR_PREY = 25,
    ACTION_26_ASP_RAID_CHASE = 26,
    ACTION_27_ASP_RAID_ATTACK = 27,
    ACTION_28_ASP_RAID_INVESTIGATE = 28,
};

enum e_asp_herd_offsets {
    ASP_HERD_OFFSET_COUNT = 16,
};

class figure_asp : public figure_animal {
public:
    FIGURE_METAINFO(FIGURE_ASP, figure_asp)
    figure_asp(figure *f) : figure_animal(f) {}

    struct static_params : public figure_static_params {
        uint16_t rest_base_ticks;
        uint16_t rest_random_ticks;
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
        void archive_init();
    } FIGURE_STATIC_DATA_T;

    // Byte 2 / bytes 4-5 keep curse_raid / raid_days_left where older saves stored them.
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
    // figure::action_perform already ticks the corpse once; OG keeps it 127 ticks.
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

    static void create_herd_animals(formation& herd, int count);
    static void update_herd(formation& herd);

private:
    void move(const svector<uint8_t, 4>& cycle);
    void set_rest_or_idle();
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

ANK_CONFIG_STRUCT(figure_asp::static_params, rest_base_ticks, rest_random_ticks, dying_ticks, chase_ticks_per_ring,
  hunt_delay, hunt_radius, move_cycle, prowl_cycle, forbidden_prey, attack_sound, die_sound, herd_spawn_delay,
  herd_move_delay, herd_roam_radius, herd_spawn_only_when_present, herd_spawn_wait_range, herd_spawn_wait_factor,
  herd_new_animal_wait, herd_allowed_terrain, herd_blocked_terrain, herd_special_terrain, raid_hunt_distance,
  raid_chase_speed_mult, raid_non_targets)

void figure_asp_setup_curse_raid(figure &f, int days);
