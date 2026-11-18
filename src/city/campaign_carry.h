#pragma once

#include <cstdint>

#include "core/bstring.h"

#include "building/building_type.h"
#include "figure/figure_type.h"

enum e_troop_carry_slot : uint8_t {
    TROOP_CARRY_INFANTRY = 0,
    TROOP_CARRY_ARCHER = 1,
    TROOP_CARRY_CHARIOT = 2,
    TROOP_CARRY_MAX = 3
};

enum e_troop_carry_mask : uint8_t {
    TROOP_CARRY_MASK_INFANTRY = 1 << TROOP_CARRY_INFANTRY,
    TROOP_CARRY_MASK_ARCHER = 1 << TROOP_CARRY_ARCHER,
    TROOP_CARRY_MASK_CHARIOT = 1 << TROOP_CARRY_CHARIOT,
};

enum {
    CAMPAIGN_CARRY_MONUMENT_MAX = 8
};

struct campaign_troop_slot_t {
    uint8_t has_data; // snapshot from previous win
    uint8_t pending;  // available to place this mission
    uint8_t num_figures;
    uint8_t has_military_training;
    int16_t morale;
    uint16_t experience;
};

struct campaign_monument_slot_t {
    uint8_t has_data;
    uint8_t orientation;
    uint8_t variant;
    uint8_t pad;
    uint16_t type; // e_building_type
    int16_t tile_x;
    int16_t tile_y;
};

struct campaign_carry_t {
    campaign_troop_slot_t troops[TROOP_CARRY_MAX];
    uint8_t notice_posted;
    uint8_t pad_troops[3];
    campaign_troop_slot_t troop_refund[TROOP_CARRY_MAX]; // undo / demolish restore
    campaign_monument_slot_t monuments[CAMPAIGN_CARRY_MONUMENT_MAX];

    void clear();
    void clear_troops();
    void clear_monuments();

    void snapshot_from_formations();
    void activate_for_mission(uint8_t mask);
    bool try_apply_to_fort(e_building_type fort_type, int formation_id);
    void expire_pending_troops();
    void refund_fort_if_applied(e_building_type fort_type);
    int pending_mask() const;
    void post_notice_if_needed();

    void snapshot_monuments_from_city();
    void apply_monuments();
};

extern campaign_carry_t g_campaign_carry;

e_troop_carry_slot troop_carry_slot_for_building(e_building_type type);
e_troop_carry_slot troop_carry_slot_for_figure(e_figure_type type);
e_figure_type troop_carry_figure_type(e_troop_carry_slot slot);
uint8_t troop_carry_mask_parse_name(pcstr name);
bool campaign_carry_is_monument_type(e_building_type type);
bool campaign_carry_is_fort_building(e_building_type type);
