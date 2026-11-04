#pragma once

#include "figure/figure.h"

enum e_warship_action {
    ACTION_203_WARSHIP_MOORED = 203,
    ACTION_204_WARSHIP_ATTACK = 204,
    ACTION_205_WARSHIP_CREATED = 205,
    ACTION_206_WARSHIP_GOING_TO_PATROL = 206,
    ACTION_207_WARSHIP_GOING_TO_WHARF = 207,
    ACTION_208_WARSHIP_GOING_TO_RANDOM = 208,
    ACTION_209_WARSHIP_ON_PATROL = 209,
    ACTION_210_WARSHIP_GOING_TO_TILE = 210,
    ACTION_211_WARSHIP_IDLE_AT_TILE = 211,
    // OG FIGURE_ACTION_WARSHIP_GOING_TO_DOCK / QUEUED_AT_DOCK (shipwright repair).
    ACTION_212_WARSHIP_GOING_TO_SHIPWRIGHT = 212,
    ACTION_213_WARSHIP_QUEUED_AT_SHIPWRIGHT = 213,
    // OG kingdom troop-request cycle (ships_player / military.c warship).
    ACTION_221_WARSHIP_GOING_TO_REQUEST = 221,
    ACTION_222_WARSHIP_AWAY_ON_REQUEST = 222,
    ACTION_223_WARSHIP_RETURNING_FROM_REQUEST = 223,
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
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        short active_order;
        short target_id;
        short last_order;
        int8_t crew_fatigue;   // 0–100; UI bands Rested/Tired/Exhausted
        uint8_t fatigue_tick;  // sub-counter for growth/decay intervals
        uint8_t answers_requests; // OG figure.answers_requests (fleet advisor)
        int16_t request_event_id; // OG figure.request_event_id (−1 = none)
    } FIGURE_RUNTIME_DATA_T;

    void begin_kingdom_request(int event_id);
    void return_from_kingdom_request();

    int8_t missile_attack_value() const { return current_params().missile_attack_value; }
    int16_t missile_delay() const { return current_params().missile_delay; }

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual void update_animation() override;

    void figure_action_goto_wharf();
    void figure_action_common();
    void figure_action_combat();
    void figure_action_repair();
    void figure_action_move_to_tile();

    figure_id find_combat_target(int max_distance);
    void combat_tick_vs_target(figure *target, int max_pursue_distance);
    void launch_missile_at(figure *target);
    void ram_target(figure *target);
    void check_sink();

    void move_to_tile(tile2i dest);
    void move_to_wharf(int wharf_building_id, tile2i dock_tile);
};
ANK_CONFIG_STRUCT(figure_warship::order_t, id, text)
ANK_CONFIG_STRUCT(figure_warship::static_params, orders_info, missile_attack_value, missile_delay)