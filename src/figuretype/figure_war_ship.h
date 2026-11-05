#pragma once

#include "figure/figure.h"

enum e_warship_action {
    ACTION_8_WARSHIP_WAITING = 8,
    ACTION_9_WARSHIP_STRAIGHT = 9,
    ACTION_10_WARSHIP_HUNTING = 10,
    ACTION_11_WARSHIP_SAILING = 11,
    ACTION_12_WARSHIP_EVADING = 12,
    ACTION_13_WARSHIP_GOING_TO_DOCK = 13,
    ACTION_15_WARSHIP_QUEUED_AT_DOCK = 15,
    ACTION_17_WARSHIP_GOING_TO_REQUEST = 17,
    ACTION_18_WARSHIP_AWAY_ON_REQUEST = 18,
    ACTION_19_WARSHIP_RETURNING_FROM_REQUEST = 19,
    ACTION_20_WARSHIP_DOCKED = 20,
    ACTION_23_WARSHIP_PATROLLING = 23,
    ACTION_24_WARSHIP_ATTACKING_SHIP = 24,
};

enum e_warship_secondary_action {
    WARSHIP_SECONDARY_MOVING = 9,
    WARSHIP_SECONDARY_FOLLOW_TARGET = 9,
    WARSHIP_SECONDARY_SAILING = 11,
    WARSHIP_SECONDARY_WAITING = 16,
    WARSHIP_SECONDARY_PATROL_ATTACK = 21,
    WARSHIP_SECONDARY_PATROLLING = 22,
    WARSHIP_SECONDARY_PATROL = 22,
};

enum e_warship_move_mode {
    WARSHIP_MOVE_FULL_SPEED = 0,
    WARSHIP_MOVE_SLOW = 1,
    WARSHIP_MOVE_RESTING = 2,
};

class figure_warship : public figure_impl {
public:
    enum e_order {
        e_order_none = 0,
        e_order_goto_wharf,
        e_order_engage_nearby,
        e_order_hold_position,
        e_order_seek_and_destroy,
        e_order_repair,
        e_order_move_to_tile,
        e_order_max,
    };

    struct order_t {
        xstring key;
        int8_t id;
        int8_t text;
    };

    FIGURE_METAINFO(FIGURE_WARSHIP, figure_warship)
    figure_warship(figure *f) : figure_impl(f) {}
    virtual figure_warship *dcast_warship() override { return this; }

    struct static_params : public figure_static_params {
        std::unordered_map<xstring, order_t> orders_info;
        int8_t missile_attack_value = 6;
        int16_t missile_delay = 200;
        int16_t hunt_range = 228;
        int16_t missile_range = 10;
        int16_t patrol_extra_range = 10;
        int16_t patrol_radius = 10;
        int16_t damaged_percent = 15;
        int16_t dock_wait_ticks = 50;
        int16_t face_enemy_wait = 19;
        int16_t face_enemy_range = 5;
        int16_t ram_cooldown = 15;
        int16_t evade_ticks = 75;
        int16_t evade_range = 18;
        int16_t shoot_ticks = 100;
        int16_t target_check_ticks = 10;
        int16_t full_moves = 80;
        int16_t full_steps = 8;
        int16_t fatigue_ticks = 200;
        int16_t ram_fast_percent = 120;
        int8_t score_loaded_transport = 25;
        int8_t score_land_enemy = 17;
        int8_t score_warship = 15;
        int8_t score_transport = 10;
        int16_t escape_distance = 10;
        int16_t fatigue_rest_interval = 40;
        int16_t fatigue_grow_interval = 80;
        int16_t fatigue_combat_interval = 20;
        int8_t fatigue_rest_amount = 2;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        short active_order;
        short target_id;
        short action_before_attack;
        int16_t patrol_x;
        int16_t patrol_y;
        int16_t request_event_id = -1;
        uint16_t move_count;
        uint16_t move_steps;
        uint8_t secondary_action;
        uint8_t ship_move_mode;
        uint8_t ram_cooldown;
        uint8_t answers_requests = 1;
        int8_t crew_fatigue = 0;
        uint8_t fatigue_tick = 0;
    } FIGURE_RUNTIME_DATA_T;

    int8_t missile_attack_value() const { return current_params().missile_attack_value; }
    int16_t missile_delay() const { return current_params().missile_delay; }

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual void update_animation() override;

    void set_order(int order);
    void attack_target(figure_id target_id);
    void move_to_tile(tile2i dest);
    void move_to_wharf(int wharf_building_id, tile2i dock_tile);

    int target_score(figure *f, int distance) const;
    figure_id find_enemy_at(tile2i origin, int range);
    figure_id find_closest_enemy_ship(int range);
    figure_id find_ram_target();
    void fire_missile(figure_id target_id);
    void shoot();
    void ram();
    void ship_move(bool cautious);
    void move_attack();
    void sail_to_destination();
    void patrol();
    void evade();
    void attack_ship();
    void wait_at_shipyard();
    void go_to_best_dock();
    void sail_to_dock();
    void docked();
    void request_action();
    void check_sink();
    void update_crew_fatigue();

    void send_to_request(int event_id);
    void return_from_request();
    // legion_requests.cpp entry points (OG city/legion_requests).
    void begin_kingdom_request(int event_id) { send_to_request(event_id); }
    void return_from_kingdom_request() { return_from_request(); }
};
ANK_CONFIG_STRUCT(figure_warship::order_t, id, text)
ANK_CONFIG_STRUCT(figure_warship::static_params,
    orders_info, missile_attack_value, missile_delay, hunt_range, missile_range, patrol_extra_range,
    patrol_radius, damaged_percent, dock_wait_ticks, face_enemy_wait, face_enemy_range, ram_cooldown,
    evade_ticks, evade_range, shoot_ticks, target_check_ticks, full_moves, full_steps, fatigue_ticks,
    ram_fast_percent, score_loaded_transport, score_land_enemy, score_warship, score_transport,
    escape_distance, fatigue_rest_interval, fatigue_grow_interval, fatigue_combat_interval,
    fatigue_rest_amount)