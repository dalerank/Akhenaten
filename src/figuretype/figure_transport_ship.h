#pragma once

#include "figure/figure.h"
#include "grid/water.h"

water_dest map_water_get_wharf_for_new_transport_ship(figure &boat);

enum e_transport_ship_action {
    ACTION_211_TRANSPORT_SHIP_WAITING = 211,              // OG WAITING
    ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF = 212,       // sail to home transport wharf
    ACTION_213_TRANSPORT_SHIP_DOCKED = 213,               // OG DOCKED (was MOORED)
    ACTION_214_TRANSPORT_SHIP_SAILING = 214,              // OG SAILING
    ACTION_215_TRANSPORT_SHIP_EVADING = 215,              // OG EVADING
    ACTION_216_TRANSPORT_SHIP_GOING_TO_SHIPWRIGHT = 216,  // OG GOING_TO_DOCK (repair)
    ACTION_217_TRANSPORT_SHIP_QUEUED_AT_SHIPWRIGHT = 217, // OG QUEUED_AT_DOCK
    ACTION_218_TRANSPORT_SHIP_GOING_TO_LEGION = 218,      // OG GOING_TO_LEGION
    ACTION_219_TRANSPORT_SHIP_GOING_TO_LANDING = 219,     // OG GOING_TO_LANDING
    ACTION_220_TRANSPORT_SHIP_RETURNING_TO_LANDING = 220, // OG RETURNING_TO_LANDING / from request
    ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST = 221,     // OG GOING_TO_REQUEST
    ACTION_222_TRANSPORT_SHIP_AWAY_ON_REQUEST = 222,      // OG AWAY_ON_REQUEST
    ACTION_223_TRANSPORT_SHIP_RETURNING_FROM_REQUEST = 223,

    // Compat aliases used by older call sites / tests.
    ACTION_211_TRANSPORT_SHIP_CREATED = ACTION_211_TRANSPORT_SHIP_WAITING,
    ACTION_213_TRANSPORT_SHIP_MOORED = ACTION_213_TRANSPORT_SHIP_DOCKED,
    ACTION_214_TRANSPORT_SHIP_ANCHORED = ACTION_214_TRANSPORT_SHIP_SAILING,
    ACTION_215_TRANSPORT_SHIP_LEAVING = ACTION_214_TRANSPORT_SHIP_SAILING,
};

class figure_transport_ship : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TRANSPORT_SHIP, figure_transport_ship)
    figure_transport_ship(figure *f) : figure_impl(f) {}

    virtual figure_transport_ship *dcast_transport_ship() override { return this; }

    enum e_evade_mode : int8_t {
        evade_waiting = 0,
        evade_moving = 1,
    };

    struct static_params : public figure_static_params {
        int16_t dock_wait_ticks = 50;           // OG SHIP_DOCK_WAIT_TICKS
        int16_t face_enemy_wait = 19;           // OG SHIP_FACE_ENEMY_WAIT
        int16_t face_enemy_range = 5;           // OG SHIP_FACE_ENEMY_RANGE
        int16_t legion_drowns_tick = 2;         // OG TRANSPORT_LEGION_DROWNS_TICK
        int16_t evade_ticks = 75;               // OG MILITARY_RULE_TRANSPORT_EVADE_TICKS
        int16_t evade_range = 18;               // OG MILITARY_RULE_TRANSPORT_EVADE_RANGE
        int16_t hull_auto_repair_percent = 15;  // OG MILITARY_RULE_SHIP_DAMAGED_PERCENTAGE
        // How far to probe when fleeing (OG transport_escapes used ±10 tiles).
        int16_t escape_distance = 10;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        int8_t formation_id;     // OG ship_formation_id (assigned company)
        int8_t has_troops;       // OG has_troops_on_board
        int8_t evade_mode;       // OG warship_secondary_action WAITING/MOVING
        int8_t phase;            // legacy UI: 0 empty/idle, 1 boarding, 2 loaded
        int16_t landing_x;       // OG ship_landing_x/y (order tile)
        int16_t landing_y;
        int16_t disembark_x;     // cached shore for land (optional)
        int16_t disembark_y;
        int16_t embark_ticks;    // unused by OG timing; kept for save layout
        int16_t request_event_id; // OG figure.request_event_id (−1 = none)
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual void update_animation() override;

    bool has_troops() const;
    int transported_formation() const;
    bool can_embark() const;
    bool embark_formation(int formation_id);
    void sail_to_landing(tile2i water_tile, tile2i land_order = tile2i::invalid);
    void move_to_tile(tile2i water_tile);
    void move_to_wharf(int wharf_building_id, tile2i dock_tile);
    void disembark_troops();
    void set_evade_order();
    void set_hold_order();
    void set_repair_order();
    void begin_kingdom_request();
    void return_from_kingdom_request(tile2i landing);

private:
    void clear_stale_cargo();
    void sync_embarked_troops();
    void board_legion(int formation_id);
    bool legion_ready_to_board(int formation_id) const;
    void check_auto_repair();
    void action_waiting();
    void action_going_to_wharf();
    void action_docked();
    void action_sailing();
    void action_evading();
    void action_going_to_shipwright();
    void action_queued_at_shipwright();
    void action_going_to_legion();
    void action_going_to_landing();
    void action_going_to_request();
    void action_away_on_request();
    void go_to_best_shipwright();
    bool is_docked() const;
    void update_dock();
    tile2i home_berth_tile() const;
    tile2i find_shore_tile(tile2i water_tile) const;
    tile2i pick_escape_tile(tile2i from_enemy) const;
    figure_id find_nearest_enemy_ship(int range) const;
};
ANK_CONFIG_STRUCT(figure_transport_ship::static_params,
    dock_wait_ticks, face_enemy_wait, face_enemy_range,
    legion_drowns_tick, evade_ticks, evade_range, hull_auto_repair_percent,
    escape_distance)
