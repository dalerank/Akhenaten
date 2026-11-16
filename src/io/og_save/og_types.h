#pragma once

// Original Pharaoh v160 savegame records, copied from the decompiled reference (tutankhamun, src/game/*_types.h).
// Plain data only: the reader fills them from the file bytes, the mapper reads them. Field names follow the reference.

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace og {

    enum dyn_queue_save_size {
        DYN_QUEUE_SAVE_SLOTS = 200,
    };

    typedef struct {
        int32_t count;
        int32_t capacity;
        int32_t head;
        int32_t tail;
        uint8_t flag;
        uint8_t reserved_1[3];
        int32_t items[DYN_QUEUE_SAVE_SLOTS];
    } dyn_queue_save;

    static_assert(sizeof(dyn_queue_save) == 0x334, "dyn_queue_save is a savegame record of 820 bytes");

    enum e_og_limits {
        MAX_BUILDINGS = 4000,
        MAX_PATH_LENGTH = 500,
        MAX_PATHS = 1000,
        MAX_FIGURES = 2000,
        MAX_FORMATIONS = 50,
        STORAGE_RECORDS = 200,
        STORAGE_RESOURCES = 36,
        FLOOD_LIST_COUNT = 30,
    };

    typedef struct {
        uint8_t size_variant;
        uint8_t stage;
        uint8_t blocks;
        uint8_t layer;
        uint8_t target_layers;
        uint8_t ramp1_height;
        uint8_t ramp2_height;
        uint8_t prep_mask;
        int16_t ramp_image_x1;
        int16_t ramp_image_y1;
        int16_t ramp_image_x2;
        int16_t ramp_image_y2;
        int16_t worker_figure_id;
        uint8_t reserved_1[2];
        uint32_t ramp_image_id;
        uint32_t ramp_link_building_id;
        int32_t ramp_link_draw_x;
        int32_t ramp_link_draw_y;
        int32_t ramp_link_x;
        int32_t ramp_link_y;
        uint8_t completion_shown;
        uint8_t reserved_2[55];
    } building_pyramid;

    typedef struct {
        int32_t city_slot;
        int32_t stage;
        int32_t worker_figure_id;
        int32_t is_main_part;
        int32_t work_flags;
        uint8_t completion_shown;
        uint8_t reserved_1[79];
    } building_monument;

    typedef struct {
        uint8_t reserved_1;
        uint8_t progress;
        uint8_t reserved_2[42];
        uint8_t completion_shown;
        uint8_t reserved_3[55];
    } building_obelisk;

    typedef struct {
        int32_t stage;
        int32_t monument_stage;
        int32_t worker_figure_id;
        uint8_t completion_shown;
        uint8_t built_parts[12];
        uint8_t reserved_1[75];
    } building_abu_simbel;

    typedef struct {
        int32_t city_slot;
        int32_t stage;
        int32_t worker_figure_id;
        int32_t is_main_part;
        int32_t work_flags;
        int32_t origin_x;
        int32_t origin_y;
        int32_t orientation;
        uint8_t completion_shown;
        uint8_t reserved_1[67];
    } building_mausoleum;

    typedef struct {
        int32_t city_slot;
        int32_t completed;
        int32_t worker_figure_id;
        int32_t stage;
        int32_t can_take_workers;
        int32_t chamber_kind;
        int32_t neighbour_offsets[6];
        int32_t remaining_work[3];
        int32_t anim_key;
        uint8_t completed_image;
        uint8_t reserved_1[3];
        int32_t stock;
        uint8_t closed_image_variant;
        uint8_t completion_shown;
        uint8_t reserved_2[26];
    } building_royal_tomb;

    typedef struct {
        int16_t inventory[12];
        uint8_t juggler;
        uint8_t musician;
        uint8_t physician;
        uint8_t dancer;
        uint8_t courthouse;
        uint8_t senet;
        uint8_t school;
        uint8_t library;
        uint8_t reserved_1;
        uint8_t dentist;
        uint8_t apothecary;
        uint8_t water_supply;
        uint8_t mortuary;
        uint8_t temple[5];
        uint8_t no_space_to_expand;
        uint8_t food_types;
        int8_t entertainment;
        int8_t education;
        int8_t health;
        int8_t num_gods;
        uint8_t devolve_delay;
        uint8_t evolve_text_id;
        uint8_t zoo;
        uint8_t is_sick;
        uint8_t tax_bonus;
        uint8_t padding_1[3];
        int32_t tax_income;
        uint8_t reserved_2[40];
    } building_house;

    typedef struct {
        int16_t reserved_1;
        int16_t inventory[12];
        uint8_t reserved_2[48];
        int16_t good_demands[4];
        uint8_t reserved_3[6];
        uint8_t fetch_inventory_id;
        uint8_t reserved_4[7];
        int16_t second_trader_id;
        int16_t second_buyer_id;
    } building_market;

    enum {
        BUILDING_DOCK_DOCKERS = 3,
    };

    typedef struct {
        int16_t reserved_1;
        int16_t resource_stored[36];
        uint8_t reserved_2[24];
        int16_t second_cart_id;
    } building_granary;

    typedef struct {
        uint8_t reserved_1[98];
        int16_t second_cart_id;
    } building_storage_yard;

    typedef struct {
        int16_t progress;
        uint8_t reserved_1[6];
        int32_t reserved_2;
        uint8_t reserved_3[4];
        int16_t fish_caught;
        uint8_t reserved_4[64];
        uint8_t worker_count;
        uint8_t labor_days_left[3];
        uint8_t orientation;
        uint8_t reserved_5[2];
        uint8_t curse_days_left;
        uint8_t reserved_6[6];
        int16_t worker_figure_id;
        int16_t second_cart_id;
    } building_industry;

    typedef struct {
        int16_t progress;
        uint8_t reserved_1[84];
        uint8_t orientation;
        uint8_t reserved_2[9];
        uint16_t boat_order;
        int16_t reserved_3;
    } building_shipyard;

    typedef struct {
        int16_t image_variant;
        uint8_t reserved_1[98];
    } building_native;

    typedef struct {
        uint8_t reserved_1[74];
        int16_t juggler_id;
        int16_t musician_id;
        int16_t dancer_id;
        int16_t reserved_2;
        uint8_t num_shows;
        uint8_t show_days_left[3];
        uint8_t reserved_3[14];
    } building_entertainment;

    typedef struct {
        int16_t unloading_docker_id;
        uint8_t reserved_1[81];
        uint8_t ship_wait_days;
        uint8_t reserved_2[2];
        uint8_t orientation;
        uint8_t reserved_3[3];
        int16_t docker_ids[BUILDING_DOCK_DOCKERS];
        int16_t ship_id;
        int16_t docked_boat_id;
    } building_dock;

    typedef struct {
        uint8_t reserved_1[85];
        uint8_t upgrades;
        uint8_t orientation;
        uint8_t reserved_2[13];
    } building_temple_complex;

    typedef struct {
        uint8_t reserved_1[86];
        uint8_t orientation;
        uint8_t reserved_2[13];
    } building_oriented;

    typedef struct {
        uint8_t reserved_1[74];
        int16_t aqueduct_links[4];
        uint8_t reserved_2[18];
    } building_water_lift;

    typedef struct {
        uint8_t state;
        uint8_t player;
        uint8_t reserved_id;
        uint8_t size;
        uint8_t house_is_merged;
        uint8_t house_size;
        int16_t x;
        int16_t y;
        uint8_t padding_2[2];
        int32_t grid_offset;
        int16_t type;
        int16_t subtype;
        uint8_t road_network_id;
        uint8_t padding_3;
        uint16_t created_sequence;
        int16_t houses_covered;
        int16_t percentage_houses_covered;
        int16_t house_population;
        int16_t house_population_room;
        int16_t distance_from_entry;
        int16_t house_highest_population;
        int16_t unreachable_ticks;
        int16_t road_access_x;
        int16_t road_access_y;
        int16_t figure_id;
        int16_t figure_id2;
        int16_t immigrant_figure_id;
        int16_t figure_id4;
        uint8_t figure_spawn_delay;
        uint8_t reserved_1;
        uint8_t figure_roam_direction;
        uint8_t has_water_access;
        uint8_t water_dependency;
        uint8_t padding_4;
        int16_t prev_part_building_id;
        int16_t next_part_building_id;
        int16_t loads_stored;
        uint8_t reserved_2;
        uint8_t has_well_access;
        int16_t num_workers;
        int8_t labor_category;
        uint8_t output_resource;
        uint8_t has_road_access;
        uint8_t padding_5;
        int16_t damage_risk;
        int16_t fire_risk;
        int16_t fire_duration;
        uint8_t fire_proof;
        uint8_t house_figure_generation_delay;
        uint8_t house_tax_coverage;
        uint8_t padding_6;
        int16_t formation_id;
        uint8_t padding_7[2];
        union {
            building_house house;
            building_pyramid pyramid;
            building_monument monument;
            building_obelisk obelisk;
            building_abu_simbel abu_simbel;
            building_mausoleum mausoleum;
            building_royal_tomb royal_tomb;
            building_market market;
            building_granary granary;
            building_storage_yard storage_yard;
            building_industry industry;
            building_shipyard shipyard;
            building_native native;
            building_entertainment entertainment;
            building_dock dock;
            building_temple_complex temple_complex;
            building_oriented oriented;
            building_water_lift water_lift;
        } data;
        int32_t tax_income_or_storage;
        uint8_t house_months_without_food;
        uint8_t ruin_has_plague;
        int8_t desirability;
        uint8_t is_deleted;
        uint8_t is_adjacent_to_water;
        uint8_t storage_id;
        union {
            int8_t house;
            uint8_t native_anger;
        } sentiment;
        uint8_t show_on_problem_overlay;
        int32_t linked_building_id;
        int16_t monument_remaining_blocks;
        uint8_t queue_index;
        uint8_t queue_slot;
        int16_t second_input_stock;
        int16_t second_input_resource;
        int32_t venue_plaza_grid_offset;
        int32_t venue_orientation;
        int32_t venue_has_plaza;
        int32_t info_orders_toggle;
        int32_t info_orders_scroll;
        int32_t crime_risk;
        int32_t house_malaria_risk;
        int32_t house_plague_distance;
        int32_t house_sick_months;
        int32_t house_water_distance;
        int32_t house_marsh_distance;
        int32_t house_plague_risk;
        int32_t problem_flags;
        int16_t incoming_carts;
        int16_t incoming_loads;
    } building;

    static_assert(sizeof(building) == 0x108, "building is a savegame record of 264 bytes");

    static_assert(
      offsetof(building, prev_part_building_id) == 0x38
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               worker_figure_id))
             == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               completion_shown))
             == 0x80
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, monument)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().monument)>,
               work_flags))
             == 0x64
        && offsetof(building, monument_remaining_blocks) == 0xC8 && offsetof(building, house_population) == 0x1C
        && offsetof(building, immigrant_figure_id) == 0x2E && offsetof(building, has_water_access) == 0x35
        && offsetof(building, tax_income_or_storage) == 0xB8,
      "building is the savegame's layout");

    static_assert(
      offsetof(building, houses_covered) == 0x18 && offsetof(building, distance_from_entry) == 0x20
        && offsetof(building, figure_id4) == 0x30 && offsetof(building, has_well_access) == 0x3F
        && offsetof(building, num_workers) == 0x40 && offsetof(building, output_resource) == 0x43
        && offsetof(building, damage_risk) == 0x46 && offsetof(building, house_tax_coverage) == 0x4E
        && offsetof(building, formation_id) == 0x50
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               juggler))
             == 0x6C
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               water_supply))
             == 0x77
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               temple))
             == 0x79
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               food_types))
             == 0x7F
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               num_gods))
             == 0x83
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               evolve_text_id))
             == 0x85
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               is_sick))
             == 0x87
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               tax_income))
             == 0x8C
        && offsetof(building, house_months_without_food) == 0xBC && offsetof(building, storage_id) == 0xC1
        && offsetof(building, linked_building_id) == 0xC4 && offsetof(building, queue_index) == 0xCA
        && offsetof(building, second_input_resource) == 0xCE && offsetof(building, crime_risk) == 0xE4
        && offsetof(building, house_plague_risk) == 0xFC && offsetof(building, is_deleted) == 0xBF
        && offsetof(building, venue_plaza_grid_offset) == 0xD0 && offsetof(building, info_orders_scroll) == 0xE0
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               courthouse))
             == 0x70
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, monument)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().monument)>,
               completion_shown))
             == 0x68
        && offsetof(building, problem_flags) == 0x100 && offsetof(building, incoming_loads) == 0x106,
      "building is the savegame's layout");

    static_assert(
      offsetof(building, player) == 0x01 && offsetof(building, x) == 0x06 && offsetof(building, grid_offset) == 0x0C
        && offsetof(building, type) == 0x10 && offsetof(building, subtype) == 0x12
        && offsetof(building, road_network_id) == 0x14 && offsetof(building, created_sequence) == 0x16
        && offsetof(building, percentage_houses_covered) == 0x1A && offsetof(building, house_population_room) == 0x1E
        && offsetof(building, house_highest_population) == 0x22 && offsetof(building, unreachable_ticks) == 0x24
        && offsetof(building, road_access_x) == 0x26 && offsetof(building, figure_id) == 0x2A
        && offsetof(building, figure_id2) == 0x2C && offsetof(building, figure_spawn_delay) == 0x32
        && offsetof(building, reserved_1) == 0x33 && offsetof(building, figure_roam_direction) == 0x34
        && offsetof(building, water_dependency) == 0x36 && offsetof(building, loads_stored) == 0x3C
        && offsetof(building, reserved_2) == 0x3E && offsetof(building, labor_category) == 0x42
        && offsetof(building, has_road_access) == 0x44 && offsetof(building, fire_risk) == 0x48
        && offsetof(building, fire_duration) == 0x4A && offsetof(building, fire_proof) == 0x4C
        && offsetof(building, house_figure_generation_delay) == 0x4D && offsetof(building, data) == 0x54
        && offsetof(building, ruin_has_plague) == 0xBD && offsetof(building, desirability) == 0xBE
        && offsetof(building, is_adjacent_to_water) == 0xC0 && offsetof(building, sentiment) == 0xC2
        && offsetof(building, show_on_problem_overlay) == 0xC3 && offsetof(building, queue_slot) == 0xCB
        && offsetof(building, second_input_stock) == 0xCC && offsetof(building, venue_orientation) == 0xD4
        && offsetof(building, venue_has_plaza) == 0xD8 && offsetof(building, info_orders_toggle) == 0xDC
        && offsetof(building, house_malaria_risk) == 0xE8 && offsetof(building, house_plague_distance) == 0xEC
        && offsetof(building, house_sick_months) == 0xF0 && offsetof(building, house_water_distance) == 0xF4
        && offsetof(building, house_marsh_distance) == 0xF8 && offsetof(building, incoming_carts) == 0x104,
      "building is the savegame's layout");

    static_assert(
      (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
        + offsetof(std::remove_reference_t<
                     decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
          inventory))
          == 0x54
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               musician))
             == 0x6D
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               physician))
             == 0x6E
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               dancer))
             == 0x6F
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               senet))
             == 0x71
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               school))
             == 0x72
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               library))
             == 0x73
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               reserved_1))
             == 0x74
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               dentist))
             == 0x75
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               apothecary))
             == 0x76
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               mortuary))
             == 0x78
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               no_space_to_expand))
             == 0x7E
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               entertainment))
             == 0x80
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               education))
             == 0x81
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               health))
             == 0x82
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               devolve_delay))
             == 0x84
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               zoo))
             == 0x86
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, house)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().house)>,
               tax_bonus))
             == 0x88
        && sizeof(building_house) == 0x64,
      "building is the savegame's layout");

    static_assert(
      (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
        + offsetof(
          std::remove_reference_t<
            decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
          stage))
          == 0x55
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               blocks))
             == 0x56
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               ramp1_height))
             == 0x59
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               prep_mask))
             == 0x5B
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               ramp_image_id))
             == 0x68
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, pyramid)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().pyramid)>,
               ramp_link_building_id))
             == 0x6C
        && sizeof(building_pyramid) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, monument)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().monument)>,
               city_slot))
             == 0x54
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, monument)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().monument)>,
               stage))
             == 0x58
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, monument)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().monument)>,
               worker_figure_id))
             == 0x5C
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, monument)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().monument)>,
               is_main_part))
             == 0x60
        && sizeof(building_monument) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, obelisk)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().obelisk)>,
               progress))
             == 0x55
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, obelisk)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().obelisk)>,
               completion_shown))
             == 0x80
        && sizeof(building_obelisk) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, abu_simbel)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().abu_simbel)>,
               stage))
             == 0x54
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, abu_simbel)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().abu_simbel)>,
               worker_figure_id))
             == 0x5C
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, abu_simbel)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().abu_simbel)>,
               completion_shown))
             == 0x60
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, abu_simbel)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().abu_simbel)>,
               built_parts))
             == 0x61
        && sizeof(building_abu_simbel) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, mausoleum)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().mausoleum)>,
               is_main_part))
             == 0x60
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, mausoleum)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().mausoleum)>,
               work_flags))
             == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, mausoleum)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().mausoleum)>,
               origin_x))
             == 0x68
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, mausoleum)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().mausoleum)>,
               origin_y))
             == 0x6C
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, mausoleum)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().mausoleum)>,
               orientation))
             == 0x70
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, mausoleum)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().mausoleum)>,
               completion_shown))
             == 0x74
        && sizeof(building_mausoleum) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               completed))
             == 0x58
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               stage))
             == 0x60
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               can_take_workers))
             == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               chamber_kind))
             == 0x68
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               neighbour_offsets))
             == 0x6C
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               remaining_work))
             == 0x84
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               anim_key))
             == 0x90
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               completed_image))
             == 0x94
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               stock))
             == 0x98
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               closed_image_variant))
             == 0x9C
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, royal_tomb)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().royal_tomb)>,
               completion_shown))
             == 0x9D
        && sizeof(building_royal_tomb) == 0x64,
      "building is the savegame's layout");

    static_assert(
      (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, market)
        + offsetof(std::remove_reference_t<
                     decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().market)>,
          inventory))
          == 0x56
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, market)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().market)>,
               good_demands))
             == 0x9E
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, market)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().market)>,
               fetch_inventory_id))
             == 0xAC
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, market)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().market)>,
               second_trader_id))
             == 0xB4
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, market)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().market)>,
               second_buyer_id))
             == 0xB6
        && sizeof(building_market) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, granary)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().granary)>,
               resource_stored))
             == 0x56
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, granary)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().granary)>,
               second_cart_id))
             == 0xB6
        && sizeof(building_granary) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, storage_yard)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .storage_yard)>,
               second_cart_id))
             == 0xB6
        && sizeof(building_storage_yard) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               progress))
             == 0x54
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               reserved_2))
             == 0x5C
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               fish_caught))
             == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               worker_count))
             == 0xA6
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               labor_days_left))
             == 0xA7
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               orientation))
             == 0xAA
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               curse_days_left))
             == 0xAD
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               worker_figure_id))
             == 0xB4
        && sizeof(building_industry) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, shipyard)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().shipyard)>,
               orientation))
             == 0xAA
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, shipyard)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().shipyard)>,
               boat_order))
             == 0xB4
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, shipyard)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().shipyard)>,
               reserved_3))
             == 0xB6
        && sizeof(building_shipyard) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, industry)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().industry)>,
               second_cart_id))
             == 0xB6
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, native)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().native)>,
               image_variant))
             == 0x54
        && sizeof(building_native) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, entertainment)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .entertainment)>,
               juggler_id))
             == 0x9E
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, entertainment)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .entertainment)>,
               musician_id))
             == 0xA0
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, entertainment)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .entertainment)>,
               dancer_id))
             == 0xA2
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, entertainment)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .entertainment)>,
               num_shows))
             == 0xA6
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, entertainment)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .entertainment)>,
               show_days_left))
             == 0xA7
        && sizeof(building_entertainment) == 0x64
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, dock)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().dock)>,
               unloading_docker_id))
             == 0x54
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, dock)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().dock)>,
               ship_wait_days))
             == 0xA7
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, dock)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().dock)>,
               orientation))
             == 0xAA
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, dock)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().dock)>,
               docker_ids))
             == 0xAE
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, dock)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().dock)>,
               ship_id))
             == 0xB4
        && (offsetof(building, data) + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, dock)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().dock)>,
               docked_boat_id))
             == 0xB6
        && sizeof(building_dock) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, temple_complex)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .temple_complex)>,
               upgrades))
             == 0xA9
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, temple_complex)
             + offsetof(std::remove_reference_t<
                          decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>()
                              .temple_complex)>,
               orientation))
             == 0xAA
        && sizeof(building_temple_complex) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, oriented)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().oriented)>,
               orientation))
             == 0xAA
        && sizeof(building_oriented) == 0x64
        && (offsetof(building, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<building>().data)>, water_lift)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<building>().data)>>().water_lift)>,
               aqueduct_links))
             == 0x9E
        && sizeof(building_water_lift) == 0x64,
      "building is the savegame's layout");

    typedef struct {
        uint8_t alternative_location_index;
        uint8_t animation_frame;
        uint8_t answers_requests;
        uint8_t flotsam_skip_tick;
        int32_t image_id;
        int16_t next_figure_id_on_same_tile;
        uint8_t type;
        union {
            uint8_t resource_id;
            uint8_t flotsam_kind;
            uint8_t editor_flag_number;
        };
        uint8_t use_cross_country;
        uint8_t is_friendly;
        uint8_t state;
        uint8_t faction_id;
        uint8_t action_state_before_attack;
        int8_t direction;
        int8_t previous_tile_direction;
        int8_t attack_direction;
        int16_t x;
        int16_t y;
        int16_t previous_tile_x;
        int16_t previous_tile_y;
        uint8_t missile_damage;
        uint8_t damage;
        uint8_t reserved_1[2];
        int32_t grid_offset;
        int16_t destination_x;
        int16_t destination_y;
        int32_t destination_grid_offset;
        int16_t source_x;
        int16_t source_y;
        union {
            int16_t formation_position_x;
            int16_t ship_landing_x;
        };
        union {
            int16_t formation_position_y;
            int16_t ship_landing_y;
        };
        uint8_t reserved_2[2];
        int16_t wait_ticks;
        uint8_t action_state;
        int8_t progress_on_tile;
        int16_t routing_path_id;
        int16_t routing_path_current_tile;
        int16_t routing_path_length;
        uint8_t in_building_wait_ticks;
        uint8_t is_on_road;
        int16_t max_roam_length;
        int16_t roam_length;
        uint8_t roam_choose_destination;
        uint8_t roam_random_counter;
        int8_t roam_turn_direction;
        int8_t roam_ticks_until_next_turn;
        union {
            struct {
                int16_t x;
                int16_t y;
                int16_t destination_x;
                int16_t destination_y;
                int16_t delta_x;
                int16_t delta_y;
                int16_t delta_xy;
            } cross_country;
            struct {
                int16_t previous_part;
                int16_t previous_height;
                int16_t part;
                int16_t height;
                int16_t progress;
                int16_t total;
            } pyramid_work;
        };
        uint8_t cc_direction;
        uint8_t speed_multiplier;
        int16_t building_id;
        union {
            int16_t immigrant_building_id;
            int16_t tomb_building_id;
        };
        union {
            int16_t destination_building_id;
            int16_t prey_figure_id;
        };
        int16_t formation_id;
        uint8_t index_in_formation;
        uint8_t formation_at_rest;
        uint8_t migrant_num_people;
        uint8_t is_ghost;
        union {
            uint8_t min_max_seen;
            uint8_t flotsam_special;
        };
        uint8_t reserved_3;
        int16_t leading_figure_id;
        uint8_t attack_image_offset;
        union {
            uint8_t wait_ticks_missile;
            uint8_t hunt_ticks;
            uint8_t cycle_ticks;
        };
        int8_t cart_offset_x;
        int8_t cart_offset_y;
        uint8_t empire_city_id;
        uint8_t trader_amount_bought;
        int16_t name_id;
        uint8_t terrain_usage;
        uint8_t reserved_4;
        union {
            int16_t resource_amount;
            int16_t extinguish_ticks;
        };
        uint8_t is_boat;
        uint8_t height_adjusted_ticks;
        uint8_t current_height;
        uint8_t target_height;
        union {
            uint8_t collecting_item_id;
            uint8_t ship_dock_index;
        };
        uint8_t ship_dock_attempts;
        uint8_t phrase_sequence_exact;
        uint8_t phrase_id;
        uint8_t phrase_sequence_city;
        uint8_t trader_id;
        union {
            uint8_t wait_ticks_next_target;
            uint8_t ship_leave_month;
        };
        uint8_t reserved_5;
        int16_t target_figure_id;
        int16_t targeted_by_figure_id;
        int16_t created_sequence;
        int16_t target_figure_created_sequence;
        uint8_t index_on_same_tile;
        uint8_t num_attackers;
        int16_t attacker_id1;
        int16_t attacker_id2;
        int16_t opponent_id;
        union {
            uint8_t ship_formation_id;
            uint8_t flee_ticks;
            uint8_t spot_wait_ticks;
            uint8_t reroute_ticks;
        };
        uint8_t buyer_storages_visited;
        uint8_t reserved_6[4];
        int32_t name_group;
        int32_t buyer_resources[4];
        int32_t buyer_storage_ids[4];
        int32_t buyer_amounts_bought[4];
        uint8_t reserved_7[80];
        int32_t ferry_path_index;
        int16_t pyramid_walk_mode;
        uint8_t reserved_8[2];
        int32_t reserved_9;
        int32_t ship_hit_points;
        int32_t ship_max_hit_points;
        uint8_t has_troops_on_board;
        uint8_t phrase_group;
        int16_t request_event_id;
        union {
            struct {
                int32_t steps;
                int32_t reserved_1;
                int32_t tile_x;
                int32_t tile_y;
            } charge;
            struct {
                int32_t reserved_1;
                int32_t hunter_building_id;
                int32_t reserved_2[2];
                int32_t frame_count;
                int32_t frame;
            } animal;
            struct {
                int32_t steps;
                int32_t moves;
                int32_t speed;
                int32_t max_straight_steps;
                int32_t model_column_m;
                int32_t model_column_n;
            } ship;
        };
        int16_t patrol_x;
        int16_t patrol_y;
        int32_t ram_damage_slow;
        union {
            uint8_t retry_count;
            uint8_t ship_move_mode;
            uint8_t lost_ticks;
        };
        uint8_t reserved_10[3];
        int32_t ram_damage_fast;
        int32_t warship_secondary_action;
        uint8_t move_speed_counter;
        uint8_t reserved_11[3];
        union {
            int32_t ram_cooldown;
            int32_t festival_trips;
        };
        uint8_t reserved_12[4];
        int32_t invasion_soldiers;
        int32_t invasion_id;
        int32_t invasion_nation;
        int32_t invasion_formation_param;
        int32_t invasion_event_id;
        int32_t cart_image_id;
    } figure;

    static_assert(sizeof(figure) == 0x184, "figure is a savegame record of 388 bytes");

    static_assert(offsetof(figure, progress_on_tile) == 0x39 && offsetof(figure, is_boat) == 0x76
                    && offsetof(figure, cc_direction) == 0x58 && offsetof(figure, move_speed_counter) == 0x160,
      "figure is the savegame's layout");

    static_assert(
      offsetof(figure, alternative_location_index) == 0x00 && offsetof(figure, animation_frame) == 0x01
        && offsetof(figure, answers_requests) == 0x02 && offsetof(figure, flotsam_skip_tick) == 0x03
        && offsetof(figure, image_id) == 0x04 && offsetof(figure, next_figure_id_on_same_tile) == 0x08
        && offsetof(figure, type) == 0x0A && offsetof(figure, resource_id) == 0x0B
        && offsetof(figure, flotsam_kind) == 0x0B && offsetof(figure, grid_offset) == 0x20
        && offsetof(figure, formation_position_x) == 0x30 && offsetof(figure, formation_position_y) == 0x32
        && offsetof(figure, ship_landing_x) == 0x30 && offsetof(figure, ship_landing_y) == 0x32
        && offsetof(figure, reserved_2) == 0x34 && offsetof(figure, wait_ticks) == 0x36
        && (offsetof(figure, cross_country)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().cross_country)>, x))
             == 0x4A
        && (offsetof(figure, cross_country)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().cross_country)>, destination_x))
             == 0x4E
        && (offsetof(figure, cross_country)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().cross_country)>, delta_xy))
             == 0x56
        && (offsetof(figure, pyramid_work)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().pyramid_work)>, previous_part))
             == 0x4A
        && (offsetof(figure, pyramid_work)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().pyramid_work)>, part))
             == 0x4E
        && (offsetof(figure, pyramid_work)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().pyramid_work)>, total))
             == 0x54
        && offsetof(figure, immigrant_building_id) == 0x5C && offsetof(figure, tomb_building_id) == 0x5C
        && offsetof(figure, destination_building_id) == 0x5E && offsetof(figure, prey_figure_id) == 0x5E
        && offsetof(figure, formation_id) == 0x60 && offsetof(figure, index_in_formation) == 0x62
        && offsetof(figure, formation_at_rest) == 0x63 && offsetof(figure, migrant_num_people) == 0x64
        && offsetof(figure, is_ghost) == 0x65 && offsetof(figure, min_max_seen) == 0x66
        && offsetof(figure, flotsam_special) == 0x66 && offsetof(figure, reserved_3) == 0x67
        && offsetof(figure, leading_figure_id) == 0x68 && offsetof(figure, attack_image_offset) == 0x6A
        && offsetof(figure, wait_ticks_missile) == 0x6B && offsetof(figure, hunt_ticks) == 0x6B
        && offsetof(figure, cycle_ticks) == 0x6B && offsetof(figure, cart_offset_x) == 0x6C
        && offsetof(figure, cart_offset_y) == 0x6D && offsetof(figure, empire_city_id) == 0x6E
        && offsetof(figure, trader_amount_bought) == 0x6F && offsetof(figure, name_id) == 0x70
        && offsetof(figure, terrain_usage) == 0x72 && offsetof(figure, reserved_4) == 0x73
        && offsetof(figure, resource_amount) == 0x74 && offsetof(figure, extinguish_ticks) == 0x74
        && offsetof(figure, target_height) == 0x79 && offsetof(figure, collecting_item_id) == 0x7A
        && offsetof(figure, ship_dock_index) == 0x7A && offsetof(figure, ship_dock_attempts) == 0x7B
        && offsetof(figure, phrase_sequence_exact) == 0x7C && offsetof(figure, phrase_id) == 0x7D
        && offsetof(figure, phrase_sequence_city) == 0x7E && offsetof(figure, trader_id) == 0x7F
        && offsetof(figure, wait_ticks_next_target) == 0x80 && offsetof(figure, ship_leave_month) == 0x80
        && offsetof(figure, reserved_5) == 0x81 && offsetof(figure, target_figure_id) == 0x82
        && offsetof(figure, targeted_by_figure_id) == 0x84 && offsetof(figure, created_sequence) == 0x86
        && offsetof(figure, target_figure_created_sequence) == 0x88 && offsetof(figure, index_on_same_tile) == 0x8A
        && offsetof(figure, num_attackers) == 0x8B && offsetof(figure, attacker_id1) == 0x8C
        && offsetof(figure, attacker_id2) == 0x8E && offsetof(figure, opponent_id) == 0x90
        && offsetof(figure, ship_formation_id) == 0x92 && offsetof(figure, flee_ticks) == 0x92
        && offsetof(figure, spot_wait_ticks) == 0x92 && offsetof(figure, reroute_ticks) == 0x92
        && offsetof(figure, buyer_storages_visited) == 0x93 && offsetof(figure, reserved_6) == 0x94
        && offsetof(figure, name_group) == 0x98 && offsetof(figure, buyer_resources) == 0x9C
        && offsetof(figure, buyer_storage_ids) == 0xAC && offsetof(figure, buyer_amounts_bought) == 0xBC
        && offsetof(figure, reserved_7) == 0xCC && offsetof(figure, ferry_path_index) == 0x11C
        && offsetof(figure, pyramid_walk_mode) == 0x120 && offsetof(figure, reserved_8) == 0x122
        && offsetof(figure, reserved_9) == 0x124 && offsetof(figure, ship_hit_points) == 0x128
        && offsetof(figure, ship_max_hit_points) == 0x12C && offsetof(figure, has_troops_on_board) == 0x130
        && offsetof(figure, phrase_group) == 0x131 && offsetof(figure, request_event_id) == 0x132
        && (offsetof(figure, charge)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().charge)>, steps))
             == 0x134
        && (offsetof(figure, charge)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().charge)>, tile_x))
             == 0x13C
        && (offsetof(figure, charge)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().charge)>, tile_y))
             == 0x140
        && (offsetof(figure, animal)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().animal)>, hunter_building_id))
             == 0x138
        && (offsetof(figure, animal)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().animal)>, frame_count))
             == 0x144
        && (offsetof(figure, animal)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().animal)>, frame))
             == 0x148
        && (offsetof(figure, ship) + offsetof(std::remove_reference_t<decltype(std::declval<figure>().ship)>, steps))
             == 0x134
        && (offsetof(figure, ship) + offsetof(std::remove_reference_t<decltype(std::declval<figure>().ship)>, moves))
             == 0x138
        && (offsetof(figure, ship) + offsetof(std::remove_reference_t<decltype(std::declval<figure>().ship)>, speed))
             == 0x13C
        && (offsetof(figure, ship)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().ship)>, max_straight_steps))
             == 0x140
        && (offsetof(figure, ship)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().ship)>, model_column_m))
             == 0x144
        && (offsetof(figure, ship)
             + offsetof(std::remove_reference_t<decltype(std::declval<figure>().ship)>, model_column_n))
             == 0x148
        && offsetof(figure, patrol_x) == 0x14C && offsetof(figure, patrol_y) == 0x14E
        && offsetof(figure, ram_damage_slow) == 0x150 && offsetof(figure, retry_count) == 0x154
        && offsetof(figure, ship_move_mode) == 0x154 && offsetof(figure, lost_ticks) == 0x154
        && offsetof(figure, reserved_10) == 0x155 && offsetof(figure, ram_damage_fast) == 0x158
        && offsetof(figure, warship_secondary_action) == 0x15C && offsetof(figure, reserved_11) == 0x161
        && offsetof(figure, ram_cooldown) == 0x164 && offsetof(figure, festival_trips) == 0x164
        && offsetof(figure, reserved_12) == 0x168 && offsetof(figure, invasion_soldiers) == 0x16C
        && offsetof(figure, invasion_id) == 0x170 && offsetof(figure, invasion_nation) == 0x174
        && offsetof(figure, invasion_formation_param) == 0x178 && offsetof(figure, invasion_event_id) == 0x17C
        && offsetof(figure, cart_image_id) == 0x180,
      "figure is the savegame's layout");

    enum formation_size {
        FORMATION_MAX_FIGURES = 16,
        FORMATION_MAX_LEGIONS = 6,
    };

    typedef struct {
        uint8_t in_use;
        uint8_t faction;
        uint8_t legion_id;
        uint8_t is_at_fort;
        int16_t figure_type;
        int16_t building_id;
        int16_t figures[FORMATION_MAX_FIGURES];
        uint8_t num_figures;
        uint8_t max_figures;
        int16_t layout;
        int16_t morale;
        int16_t x;
        int16_t y;
        int16_t order_x;
        int16_t order_y;
        int16_t home_x;
        int16_t home_y;
        int16_t destination_x;
        int16_t destination_y;
        int16_t destination_building_id;
        int16_t standard_figure_id;
        uint8_t is_legion;
        uint8_t reserved_1;
        int16_t attack_type;
        int16_t legion_recruit_type;
        int16_t has_military_training;
        int16_t total_damage;
        int16_t max_total_damage;
        union {
            int16_t ticks;
            uint8_t bytes[2];
        } wait;
        int16_t recent_fight;
        int16_t regroup_ticks;
        int16_t advance_ticks;
        int16_t halt_ticks;
        int16_t invasion_formation_index;
        int16_t is_halted;
        int16_t missile_fired;
        int16_t missile_attack_timeout;
        int16_t missile_attack_formation_id;
        int16_t prev_layout;
        int16_t cursed_by_seth;
        uint8_t months_low_morale;
        uint8_t empire_service;
        uint8_t ticks_without_target;
        uint8_t herd_kind;
        uint8_t enemy_type;
        uint8_t direction;
        int16_t prev_x;
        int16_t prev_y;
        uint8_t direction_hold_ticks;
        uint8_t orientation;
        uint8_t months_from_home;
        uint8_t months_very_low_morale;
        uint8_t herd_state;
        uint8_t herd_spawn_delay;
        uint8_t herd_direction;
        uint8_t alternate_layout;
        int16_t invasion_event_id;
        int16_t experience;
        int16_t saved_layout;
        int16_t has_move_order;
        int16_t move_order_ticks;
        int16_t request_event_id;
        int32_t ship_figure_id;
        int16_t invasion_sequence;
        uint8_t reserved_2[2];
        int32_t attack_formation_id;
    } formation;

    static_assert(sizeof(formation) == 0x90, "formation is a savegame record of 144 bytes");

    static_assert(
      offsetof(formation, legion_id) == 0x02 && offsetof(formation, figure_type) == 0x04
        && offsetof(formation, building_id) == 0x06 && offsetof(formation, figures) == 0x08
        && offsetof(formation, num_figures) == 0x28 && offsetof(formation, layout) == 0x2A
        && offsetof(formation, x) == 0x2E && offsetof(formation, order_x) == 0x32 && offsetof(formation, home_x) == 0x36
        && offsetof(formation, destination_x) == 0x3A && offsetof(formation, destination_building_id) == 0x3E
        && offsetof(formation, standard_figure_id) == 0x40 && offsetof(formation, is_legion) == 0x42
        && offsetof(formation, attack_type) == 0x44 && offsetof(formation, has_military_training) == 0x48
        && offsetof(formation, max_total_damage) == 0x4C && offsetof(formation, wait) == 0x4E
        && offsetof(formation, recent_fight) == 0x50 && offsetof(formation, advance_ticks) == 0x54
        && offsetof(formation, invasion_formation_index) == 0x58 && offsetof(formation, is_halted) == 0x5A
        && offsetof(formation, missile_attack_formation_id) == 0x60 && offsetof(formation, cursed_by_seth) == 0x64
        && offsetof(formation, months_low_morale) == 0x66 && offsetof(formation, ticks_without_target) == 0x68
        && offsetof(formation, enemy_type) == 0x6A && offsetof(formation, prev_x) == 0x6C
        && offsetof(formation, direction_hold_ticks) == 0x70 && offsetof(formation, months_very_low_morale) == 0x73
        && offsetof(formation, herd_direction) == 0x76 && offsetof(formation, alternate_layout) == 0x77
        && offsetof(formation, invasion_event_id) == 0x78 && offsetof(formation, experience) == 0x7A
        && offsetof(formation, has_move_order) == 0x7E && offsetof(formation, request_event_id) == 0x82
        && offsetof(formation, ship_figure_id) == 0x84 && offsetof(formation, invasion_sequence) == 0x88
        && offsetof(formation, attack_formation_id) == 0x8C,
      "formation is the savegame's layout");

    typedef formation formation_table[MAX_FORMATIONS];

    typedef struct enemy_army_totals_record {
        int32_t update_counter;
        int32_t legion_strength;
        int32_t legion_formations;
        int32_t enemy_strength;
        int32_t enemy_formations;
    } enemy_army_totals_record;

    static_assert(sizeof(enemy_army_totals_record) == 20, "enemy_army_totals_record is a savegame record of 20 bytes");

    static_assert(offsetof(enemy_army_totals_record, enemy_formations) == 0x10,
      "enemy_army_totals_record is the savegame's layout");

    typedef struct {
        char name[32];
    } city_player_name;

    typedef struct {
        int32_t workers_needed;
        int32_t workers_allocated;
        int32_t total_houses_covered;
        int32_t buildings;
        int32_t priority;
    } labor_category;

    static_assert(sizeof(labor_category) == 0x14, "labor_category is a savegame record of 20 bytes");

    typedef struct {
        int32_t id;
        int32_t size;
    } road_network_entry;

    enum {
        PLAYER_LARGEST_ROAD_NETWORKS = 10,
    };

    typedef struct {
        uint8_t reserved_1[2];
        uint8_t in_use;
        uint8_t enabled;
        uint8_t reserved_2;
        uint8_t building_reserved_id;
        uint8_t reserved_3[2];
        int32_t tax_percentage;
        int32_t treasury;
        int32_t sentiment;
        int32_t health_target;
        int32_t health;
        int32_t mortuary_workers;
        int32_t food_consumption_state;
        int32_t population;
        int32_t population_last_year;
        int32_t school_age;
        int32_t academy_age;
        int32_t total_capacity;
        int32_t room_in_houses;
        int32_t monthly_population[2400];
        int32_t monthly_population_next_index;
        int32_t monthly_population_count;
        int16_t population_at_age[100];
        int32_t population_per_level[20];
        int32_t yearly_births;
        int32_t yearly_deaths;
        int32_t lost_removal;
        int32_t immigration_amount_per_batch;
        int32_t emigration_amount_per_batch;
        int32_t emigration_queue_size;
        int32_t immigration_queue_size;
        int32_t lost_homeless;
        int32_t last_change;
        int32_t average_per_year;
        int32_t total_all_years;
        int32_t people_in_huts_and_shanties;
        int32_t people_in_manors_and_up;
        int32_t total_years;
        int32_t yearly_update_requested;
        int32_t last_used_house_add;
        int16_t last_used_house_remove;
        uint8_t reserved_4[2];
        int32_t immigrated_today;
        int32_t emigrated_today;
        int32_t refused_immigrants_today;
        int32_t migration_percentage;
        uint8_t reserved_5[4];
        int32_t emigration_duration;
        int32_t immigration_duration;
        int32_t migration_newcomers;
        int32_t migration_direction;
        uint8_t reserved_6[14];
        int16_t last_storage_yard_id;
        uint8_t reserved_7[36];
        int16_t entry_point_x;
        int16_t entry_point_y;
        int32_t entry_point_grid_offset;
        int16_t exit_point_x;
        int16_t exit_point_y;
        int32_t exit_point_grid_offset;
        int16_t palace_x;
        int16_t palace_y;
        int32_t palace_grid_offset;
        int32_t palace_building_id;
        uint8_t reserved_8[146];
        int16_t trade_status[36];
        int16_t trading_amount[36];
        int16_t mothballed[36];
        uint8_t reserved_9[110];
        int32_t food_stored_total;
        int32_t food_types_available;
        int32_t food_types_eaten;
        uint8_t reserved_10[4];
        int32_t request_resource;
        int32_t request_available;
        int32_t request_amount;
        int32_t sphinx_completed;
        uint8_t food_known[9];
        uint8_t resource_known[36];
        uint8_t reserved_11[207];
        int32_t stockpiled[36];
        int32_t food_supply_months;
        int32_t granaries_operating;
        int32_t percentage_plebs;
        int32_t working_age;
        int32_t workers_available;
        labor_category labor_categories[10];
        int32_t workers_employed;
        int32_t workers_unemployed;
        int32_t unemployment_percentage;
        int32_t unemployment_percentage_for_senate;
        int32_t workers_needed;
        int32_t wages;
        int32_t wages_kingdom;
        uint8_t reserved_12[4];
        int32_t wages_so_far;
        int32_t wages_this_year;
        int32_t wages_last_year;
        int32_t taxed_plebs;
        int32_t taxed_nobles;
        int32_t untaxed_plebs;
        int32_t untaxed_nobles;
        int32_t percentage_taxed_plebs;
        int32_t percentage_taxed_nobles;
        int32_t percentage_taxed_people;
        int32_t yearly_collected_plebs;
        int32_t yearly_collected_nobles;
        int32_t yearly_uncollected_plebs;
        int32_t yearly_uncollected_nobles;
        int32_t taxes_this_year;
        int32_t taxes_last_year;
        int32_t monthly_collected_plebs;
        int32_t monthly_uncollected_plebs;
        int32_t monthly_collected_nobles;
        int32_t monthly_uncollected_nobles;
        int32_t exports_this_year;
        int32_t exports_last_year;
        int32_t imports_this_year;
        int32_t imports_last_year;
        int32_t interest_so_far;
        int32_t interest_last_year;
        int32_t interest_this_year;
        int32_t stolen_last_year;
        int32_t stolen_this_year;
        int32_t construction_last_year;
        int32_t construction_this_year;
        int32_t salary_last_year;
        int32_t salary_this_year;
        int32_t salary_amount;
        int32_t salary_rank;
        int32_t salary_so_far;
        int32_t income_last_year;
        int32_t income_this_year;
        int32_t expenses_last_year;
        int32_t expenses_this_year;
        int32_t net_in_out_last_year;
        int32_t net_in_out_this_year;
        int32_t balance_last_year;
        int32_t balance_this_year;
        uint8_t reserved_13[4000];
        int32_t workshop_stored[40];
        int32_t workshop_space[40];
        uint8_t reserved_14[1280];
        int32_t houses_evolve_demand_1;
        uint8_t reserved_15[4];
        int32_t houses_evolve_demand_2;
        uint8_t reserved_16[4];
        int32_t houses_evolve_demand_3;
        uint8_t reserved_17[4];
        int32_t houses_evolve_demand_4;
        uint8_t reserved_18[4];
        int32_t caravan_import_resource;
        int32_t caravan_backup_import_resource;
        int32_t rating_culture;
        int32_t rating_prosperity;
        int32_t rating_monument;
        int32_t rating_kingdom;
        int32_t rating_peace;
        int32_t gold_delivered;
        int32_t prosperity_trend;
        uint8_t reserved_19[20];
        int32_t monument_num_criminals;
        int32_t monument_num_rioters;
        int32_t houses_missing_water_supply;
        int32_t houses_missing_well;
        int32_t houses_missing_more_entertainment;
        int32_t houses_missing_more_education;
        int32_t houses_missing_education;
        int32_t houses_requiring_school;
        int32_t houses_requiring_library;
        int32_t houses_requiring_academy;
        int32_t houses_missing_dentist;
        int32_t houses_missing_courthouse;
        int32_t houses_missing_food;
        uint8_t reserved_20[10];
        int16_t sphinx_stage;
        int32_t houses_missing_health;
        int32_t houses_missing_more_health;
        int32_t houses_requiring_dentist;
        int32_t houses_requiring_courthouse;
        int32_t houses_requiring_health;
        int32_t houses_missing_religion;
        int32_t houses_missing_second_religion;
        int32_t houses_missing_third_religion;
        int32_t houses_requiring_religion;
        int32_t juggler_shows;
        int32_t juggler_no_shows_weighted;
        int32_t musician_shows;
        int32_t musician_no_shows_weighted;
        int32_t dancer_shows;
        int32_t dancer_no_shows_weighted;
        int32_t senet_shows;
        int32_t senet_no_shows_weighted;
        int32_t venue_needing_shows;
        int32_t average_entertainment;
        int32_t houses_missing_entertainment;
        int32_t months_since_festival;
        int8_t god_target_mood[5];
        uint8_t reserved_21[5];
        int8_t god_mood[5];
        uint8_t reserved_22[5];
        int8_t god_wrath_bolts[5];
        uint8_t reserved_23[25];
        uint8_t god_extra_state_1[5];
        uint8_t reserved_24[5];
        uint8_t god_extra_state_2[5];
        uint8_t reserved_25[5];
        uint8_t god_extra_state_3[5];
        uint8_t reserved_26[5];
        int32_t god_months_since_festival[5];
        uint8_t reserved_27[20];
        int32_t least_happy_god;
        uint8_t reserved_28[4];
        int32_t no_immigration_cause;
        int32_t protesters;
        int32_t thefts;
        int32_t health_demand;
        int32_t religion_demand;
        int32_t education_demand;
        int32_t entertainment_demand;
        int32_t rioters;
        int32_t selected_rating;
        int32_t culture_explanation;
        int32_t prosperity_explanation;
        int32_t monument_explanation;
        int32_t kingdom_explanation;
        int32_t peace_explanation;
        uint8_t reserved_29[4];
        int32_t player_rank;
        int32_t personal_savings;
        int32_t donated_last_year;
        int32_t donated_this_year;
        int32_t donate_amount;
        int16_t working_dock_ids[10];
        uint8_t reserved_30[4];
        int16_t has_temple_complex;
        int16_t animals;
        int16_t num_sea_routes;
        int16_t num_land_routes;
        int16_t sea_trade_problem_duration;
        int16_t land_trade_problem_duration;
        uint8_t reserved_31[2];
        int16_t palace_placed;
        int16_t working_wharfs;
        int16_t temple_complex_upgrades;
        int16_t palace_robberies;
        int16_t palace_robberies_last_year;
        int32_t docker_import_resource;
        int32_t docker_export_resource;
        int32_t bailout_taken;
        int32_t bailout_refused_message_shown;
        int32_t cheats_used;
        int16_t recruiter_x;
        int16_t recruiter_y;
        int32_t recruiter_grid_offset;
        int32_t recruiter_building_id;
        int32_t recruiter_placed;
        uint8_t reserved_32[20];
        int32_t zoo_shows;
        int32_t zoo_no_shows_weighted;
        int32_t mission_has_won;
        int32_t mission_continue_months_left;
        int32_t mission_continue_months_chosen;
        int32_t wage_rate_paid_this_year;
        int32_t tribute_estimate;
        int32_t tribute_paid;
        int32_t tribute_not_paid_last_year;
        int32_t tribute_not_paid_total_years;
        int32_t festival_selected_god;
        int32_t festival_selected_size;
        int32_t festival_planned_size;
        int32_t festival_planned_months_to_go;
        int32_t festival_planned_god;
        int32_t festival_cost[3];
        int32_t festival_grand_beer;
        int32_t festival_not_enough_beer;
        int32_t average_religion;
        int32_t average_education;
        int32_t average_health;
        uint8_t reserved_33[4];
        int32_t first_festival_effect_months;
        int32_t second_festival_effect_months;
        uint8_t reserved_34[4];
        int32_t sentiment_unemployment;
        int32_t sentiment_previous_value;
        uint8_t reserved_35[4];
        int32_t sentiment_low_mood_cause;
        int32_t security_breach_duration;
        int32_t rating_yearly_counters[4];
        int32_t selected_gift_size;
        int32_t months_since_gift;
        int32_t gift_overdose_penalty;
        uint8_t reserved_36[4];
        int32_t gift_id[3];
        int32_t gift_cost[3];
        int32_t kingdom_salary_penalty;
        int32_t kingdom_milestone_penalty;
        int32_t kingdom_ignored_request_penalty;
        int32_t kingdom_last_year;
        int32_t kingdom_change;
        int32_t natives_hostile;
        uint8_t reserved_37[4];
        int32_t mission_post_operational;
        int32_t main_native_meeting_x;
        int32_t main_native_meeting_y;
        int32_t wage_rate_paid_last_year;
        int32_t food_needed_per_month;
        int32_t granaries_understaffed;
        int32_t granaries_not_operating;
        int32_t granaries_not_operating_with_food;
        uint8_t reserved_38[16];
        int32_t ra_exports_bonus_months;
        int32_t enemies_to_leave;
        uint8_t reserved_39[4];
        int32_t gods_angry_message_delay;
        int32_t food_consumed_last_month;
        int32_t food_produced_last_month;
        int32_t food_produced_this_month;
        uint8_t reserved_40[4];
        int32_t estimated_tax_income;
        uint8_t reserved_41[4];
        int16_t distribution_center_x;
        int16_t distribution_center_y;
        int32_t distribution_center_grid_offset;
        int32_t distribution_center_building_id;
        int32_t distribution_center_placed;
        uint8_t reserved_42[44];
        int32_t shipyard_boats_requested;
        int32_t enemies;
        int32_t sentiment_wages;
        int32_t people_in_huts;
        int32_t people_in_residences_and_up;
        int32_t kingdom_soldiers;
        uint8_t reserved_43[16];
        int32_t destroyed_buildings;
        uint8_t reserved_44[8];
        uint8_t total_transport_ships;
        uint8_t empire_service_legions_fighting;
        uint8_t empire_service_legions_not_fighting;
        uint8_t reserved_45;
        uint8_t total_warships;
        uint8_t empire_service_warships;
        uint8_t legions_fighting;
        uint8_t legions_not_fighting;
        uint8_t total_legions;
        uint8_t empire_service_legions;
        uint8_t reserved_46;
        uint8_t total_soldiers;
        uint8_t reserved_47[4];
        int32_t trade_center_building_id;
        int32_t soldiers;
        uint8_t reserved_48[3];
        int8_t sound_march_enemy;
        int8_t sound_march_horse;
        uint8_t reserved_49[10];
        uint8_t sentiment_food_toggle;
        uint8_t reserved_50[8];
        int32_t kingdom_soldiers_removed;
        int32_t chariot_legions;
        int32_t population_highest_ever;
        int32_t estimated_wages;
        int32_t luxury_goods_kinds;
        int32_t prosperity_max;
        road_network_entry largest_road_networks[PLAYER_LARGEST_ROAD_NETWORKS];
        int32_t houses_missing_second_luxury;
        int32_t flotsam_special;
        int32_t senet_house_has_plays;
        uint8_t reserved_51[12];
        int32_t fired_message_shown;
        int32_t victory_message_shown;
        int32_t mission_saved_game_state;
        int32_t tutorial_flag_seen_a;
        int32_t tutorial_flag_seen_g;
        int32_t attacking_natives;
        int32_t temple_complex_building_id;
        int32_t monument_def_id[3];
        int32_t monument_building_id[3];
        int32_t houses_requiring_more_courthouse;
        int32_t houses_missing_any_courthouse;
        int32_t plague_houses;
        int32_t requests_and_festivals_last_year;
        int32_t requests_and_festivals_this_year;
        int32_t migration_newcomers_last_month;
        int32_t crimes_this_month;
        int32_t gold_stolen_this_month;
        int32_t advisor_comment;
        int32_t hunting_lodges_working;
        int32_t game_meat_last_month;
        int32_t game_meat_this_month;
        int32_t fishing_wharfs_working;
        int32_t fish_last_month;
        int32_t fish_this_month;
        int32_t savings_lost;
        uint8_t reserved_52[24];
        int32_t festival_square_x;
        int32_t festival_square_y;
        int32_t difficulty;
        int32_t gold_last_year;
        int32_t gold_this_year;
        int32_t ra_no_traders_months;
        uint8_t reserved_53[92];
        int16_t festival_square_placed;
        int8_t god_happy_bolts[5];
        uint8_t reserved_54[5];
        int32_t monument_completion_flag;
        uint8_t reserved_55[4];
        int32_t monument_completion_months;
        int32_t months_in_debt;
        int32_t years_in_debt;
        int32_t resource_list_scroll;
        int32_t resource_settings_step;
        int32_t granary_food_stored[9];
        int32_t storage_space[36];
        int32_t storage_stored[36];
        int32_t plague_count;
        int16_t ra_trade_bonus_months;
        int16_t ra_trade_penalty_months;
        int16_t ra_trade_minor_penalty_months;
        uint8_t reserved_56[2];
        int32_t seth_minor_blessing_months;
        int32_t bast_culture_decay_skip;
        int32_t osiris_double_farm_yield;
        int32_t osiris_flood_destroys_farms;
        int32_t mansion_placed;
        int32_t enemy_warships;
        uint8_t resource_gift_received[36];
        uint8_t reserved_57[4];
        uint8_t trade_prices_mode;
        uint8_t reserved_58[3];
        int32_t military_academy_placed;
        int32_t sphinx_stage_before_delete;
    } city_player;

    static_assert(sizeof(city_player) == 0x49D8, "city_player is a savegame record of 18904 bytes");

    static_assert(
      offsetof(city_player, in_use) == 0x2 && offsetof(city_player, enabled) == 0x3
        && offsetof(city_player, building_reserved_id) == 0x5 && offsetof(city_player, tax_percentage) == 0x8
        && offsetof(city_player, treasury) == 0xC && offsetof(city_player, sentiment) == 0x10
        && offsetof(city_player, health_target) == 0x14 && offsetof(city_player, health) == 0x18
        && offsetof(city_player, mortuary_workers) == 0x1C && offsetof(city_player, food_consumption_state) == 0x20
        && offsetof(city_player, population) == 0x24 && offsetof(city_player, population_last_year) == 0x28
        && offsetof(city_player, school_age) == 0x2C && offsetof(city_player, academy_age) == 0x30
        && offsetof(city_player, total_capacity) == 0x34 && offsetof(city_player, room_in_houses) == 0x38
        && offsetof(city_player, monthly_population) == 0x3C
        && offsetof(city_player, monthly_population_next_index) == 0x25BC
        && offsetof(city_player, monthly_population_count) == 0x25C0
        && offsetof(city_player, population_at_age) == 0x25C4 && offsetof(city_player, population_per_level) == 0x268C
        && offsetof(city_player, yearly_births) == 0x26DC && offsetof(city_player, yearly_deaths) == 0x26E0
        && offsetof(city_player, lost_removal) == 0x26E4
        && offsetof(city_player, immigration_amount_per_batch) == 0x26E8
        && offsetof(city_player, emigration_amount_per_batch) == 0x26EC
        && offsetof(city_player, emigration_queue_size) == 0x26F0
        && offsetof(city_player, immigration_queue_size) == 0x26F4 && offsetof(city_player, lost_homeless) == 0x26F8
        && offsetof(city_player, last_change) == 0x26FC && offsetof(city_player, average_per_year) == 0x2700
        && offsetof(city_player, total_all_years) == 0x2704
        && offsetof(city_player, people_in_huts_and_shanties) == 0x2708
        && offsetof(city_player, people_in_manors_and_up) == 0x270C && offsetof(city_player, total_years) == 0x2710
        && offsetof(city_player, yearly_update_requested) == 0x2714
        && offsetof(city_player, last_used_house_add) == 0x2718
        && offsetof(city_player, last_used_house_remove) == 0x271C && offsetof(city_player, immigrated_today) == 0x2720
        && offsetof(city_player, emigrated_today) == 0x2724 && offsetof(city_player, refused_immigrants_today) == 0x2728
        && offsetof(city_player, migration_percentage) == 0x272C && offsetof(city_player, emigration_duration) == 0x2734
        && offsetof(city_player, immigration_duration) == 0x2738 && offsetof(city_player, migration_newcomers) == 0x273C
        && offsetof(city_player, migration_direction) == 0x2740 && offsetof(city_player, last_storage_yard_id) == 0x2752
        && offsetof(city_player, entry_point_x) == 0x2778 && offsetof(city_player, entry_point_y) == 0x277A
        && offsetof(city_player, entry_point_grid_offset) == 0x277C && offsetof(city_player, exit_point_x) == 0x2780
        && offsetof(city_player, exit_point_y) == 0x2782 && offsetof(city_player, exit_point_grid_offset) == 0x2784
        && offsetof(city_player, palace_x) == 0x2788 && offsetof(city_player, palace_y) == 0x278A
        && offsetof(city_player, palace_grid_offset) == 0x278C && offsetof(city_player, palace_building_id) == 0x2790
        && offsetof(city_player, reserved_8) == 0x2794 && offsetof(city_player, trade_status) == 0x2826
        && offsetof(city_player, trading_amount) == 0x286E && offsetof(city_player, mothballed) == 0x28B6
        && offsetof(city_player, food_stored_total) == 0x296C && offsetof(city_player, food_types_available) == 0x2970
        && offsetof(city_player, food_types_eaten) == 0x2974 && offsetof(city_player, request_resource) == 0x297C
        && offsetof(city_player, request_available) == 0x2980 && offsetof(city_player, request_amount) == 0x2984
        && offsetof(city_player, sphinx_completed) == 0x2988 && offsetof(city_player, food_known) == 0x298C
        && offsetof(city_player, resource_known) == 0x2995 && offsetof(city_player, stockpiled) == 0x2A88
        && offsetof(city_player, food_supply_months) == 0x2B18 && offsetof(city_player, granaries_operating) == 0x2B1C
        && offsetof(city_player, percentage_plebs) == 0x2B20 && offsetof(city_player, working_age) == 0x2B24
        && offsetof(city_player, workers_available) == 0x2B28 && offsetof(city_player, labor_categories) == 0x2B2C
        && offsetof(city_player, workers_employed) == 0x2BF4 && offsetof(city_player, workers_unemployed) == 0x2BF8
        && offsetof(city_player, unemployment_percentage) == 0x2BFC
        && offsetof(city_player, unemployment_percentage_for_senate) == 0x2C00
        && offsetof(city_player, workers_needed) == 0x2C04 && offsetof(city_player, wages) == 0x2C08
        && offsetof(city_player, wages_kingdom) == 0x2C0C && offsetof(city_player, wages_so_far) == 0x2C14
        && offsetof(city_player, wages_this_year) == 0x2C18 && offsetof(city_player, wages_last_year) == 0x2C1C
        && offsetof(city_player, taxed_plebs) == 0x2C20 && offsetof(city_player, taxed_nobles) == 0x2C24
        && offsetof(city_player, untaxed_plebs) == 0x2C28 && offsetof(city_player, untaxed_nobles) == 0x2C2C
        && offsetof(city_player, percentage_taxed_plebs) == 0x2C30
        && offsetof(city_player, percentage_taxed_nobles) == 0x2C34
        && offsetof(city_player, percentage_taxed_people) == 0x2C38
        && offsetof(city_player, yearly_collected_plebs) == 0x2C3C
        && offsetof(city_player, yearly_collected_nobles) == 0x2C40
        && offsetof(city_player, yearly_uncollected_plebs) == 0x2C44
        && offsetof(city_player, yearly_uncollected_nobles) == 0x2C48
        && offsetof(city_player, taxes_this_year) == 0x2C4C && offsetof(city_player, taxes_last_year) == 0x2C50
        && offsetof(city_player, monthly_collected_plebs) == 0x2C54
        && offsetof(city_player, monthly_uncollected_plebs) == 0x2C58
        && offsetof(city_player, monthly_collected_nobles) == 0x2C5C
        && offsetof(city_player, monthly_uncollected_nobles) == 0x2C60
        && offsetof(city_player, exports_this_year) == 0x2C64 && offsetof(city_player, exports_last_year) == 0x2C68
        && offsetof(city_player, imports_this_year) == 0x2C6C && offsetof(city_player, imports_last_year) == 0x2C70
        && offsetof(city_player, interest_so_far) == 0x2C74 && offsetof(city_player, interest_last_year) == 0x2C78
        && offsetof(city_player, interest_this_year) == 0x2C7C && offsetof(city_player, stolen_last_year) == 0x2C80
        && offsetof(city_player, stolen_this_year) == 0x2C84 && offsetof(city_player, construction_last_year) == 0x2C88
        && offsetof(city_player, construction_this_year) == 0x2C8C && offsetof(city_player, salary_last_year) == 0x2C90
        && offsetof(city_player, salary_this_year) == 0x2C94 && offsetof(city_player, salary_amount) == 0x2C98
        && offsetof(city_player, salary_rank) == 0x2C9C && offsetof(city_player, salary_so_far) == 0x2CA0
        && offsetof(city_player, income_last_year) == 0x2CA4 && offsetof(city_player, income_this_year) == 0x2CA8
        && offsetof(city_player, expenses_last_year) == 0x2CAC && offsetof(city_player, expenses_this_year) == 0x2CB0
        && offsetof(city_player, net_in_out_last_year) == 0x2CB4
        && offsetof(city_player, net_in_out_this_year) == 0x2CB8 && offsetof(city_player, balance_last_year) == 0x2CBC
        && offsetof(city_player, balance_this_year) == 0x2CC0 && offsetof(city_player, workshop_stored) == 0x3C64
        && offsetof(city_player, workshop_space) == 0x3D04 && offsetof(city_player, houses_evolve_demand_1) == 0x42A4
        && offsetof(city_player, houses_evolve_demand_2) == 0x42AC
        && offsetof(city_player, houses_evolve_demand_3) == 0x42B4
        && offsetof(city_player, houses_evolve_demand_4) == 0x42BC
        && offsetof(city_player, caravan_import_resource) == 0x42C4
        && offsetof(city_player, caravan_backup_import_resource) == 0x42C8
        && offsetof(city_player, rating_culture) == 0x42CC && offsetof(city_player, rating_prosperity) == 0x42D0
        && offsetof(city_player, rating_monument) == 0x42D4 && offsetof(city_player, rating_kingdom) == 0x42D8
        && offsetof(city_player, rating_peace) == 0x42DC && offsetof(city_player, gold_delivered) == 0x42E0
        && offsetof(city_player, prosperity_trend) == 0x42E4 && offsetof(city_player, monument_num_criminals) == 0x42FC
        && offsetof(city_player, monument_num_rioters) == 0x4300
        && offsetof(city_player, houses_missing_water_supply) == 0x4304
        && offsetof(city_player, houses_missing_well) == 0x4308
        && offsetof(city_player, houses_missing_more_entertainment) == 0x430C
        && offsetof(city_player, houses_missing_more_education) == 0x4310
        && offsetof(city_player, houses_missing_education) == 0x4314
        && offsetof(city_player, houses_requiring_school) == 0x4318
        && offsetof(city_player, houses_requiring_library) == 0x431C
        && offsetof(city_player, houses_requiring_academy) == 0x4320
        && offsetof(city_player, houses_missing_dentist) == 0x4324
        && offsetof(city_player, houses_missing_courthouse) == 0x4328
        && offsetof(city_player, houses_missing_food) == 0x432C && offsetof(city_player, sphinx_stage) == 0x433A
        && offsetof(city_player, houses_missing_health) == 0x433C
        && offsetof(city_player, houses_missing_more_health) == 0x4340
        && offsetof(city_player, houses_requiring_dentist) == 0x4344
        && offsetof(city_player, houses_requiring_courthouse) == 0x4348
        && offsetof(city_player, houses_requiring_health) == 0x434C
        && offsetof(city_player, houses_missing_religion) == 0x4350
        && offsetof(city_player, houses_missing_second_religion) == 0x4354
        && offsetof(city_player, houses_missing_third_religion) == 0x4358
        && offsetof(city_player, houses_requiring_religion) == 0x435C && offsetof(city_player, juggler_shows) == 0x4360
        && offsetof(city_player, juggler_no_shows_weighted) == 0x4364 && offsetof(city_player, musician_shows) == 0x4368
        && offsetof(city_player, musician_no_shows_weighted) == 0x436C && offsetof(city_player, dancer_shows) == 0x4370
        && offsetof(city_player, dancer_no_shows_weighted) == 0x4374 && offsetof(city_player, senet_shows) == 0x4378
        && offsetof(city_player, senet_no_shows_weighted) == 0x437C
        && offsetof(city_player, venue_needing_shows) == 0x4380
        && offsetof(city_player, average_entertainment) == 0x4384
        && offsetof(city_player, houses_missing_entertainment) == 0x4388
        && offsetof(city_player, months_since_festival) == 0x438C && offsetof(city_player, god_target_mood) == 0x4390
        && offsetof(city_player, god_mood) == 0x439A && offsetof(city_player, god_wrath_bolts) == 0x43A4
        && offsetof(city_player, god_extra_state_1) == 0x43C2 && offsetof(city_player, god_extra_state_2) == 0x43CC
        && offsetof(city_player, god_extra_state_3) == 0x43D6
        && offsetof(city_player, god_months_since_festival) == 0x43E0
        && offsetof(city_player, least_happy_god) == 0x4408 && offsetof(city_player, no_immigration_cause) == 0x4410
        && offsetof(city_player, protesters) == 0x4414 && offsetof(city_player, thefts) == 0x4418
        && offsetof(city_player, health_demand) == 0x441C && offsetof(city_player, religion_demand) == 0x4420
        && offsetof(city_player, education_demand) == 0x4424 && offsetof(city_player, entertainment_demand) == 0x4428
        && offsetof(city_player, rioters) == 0x442C && offsetof(city_player, selected_rating) == 0x4430
        && offsetof(city_player, culture_explanation) == 0x4434
        && offsetof(city_player, prosperity_explanation) == 0x4438
        && offsetof(city_player, monument_explanation) == 0x443C && offsetof(city_player, kingdom_explanation) == 0x4440
        && offsetof(city_player, peace_explanation) == 0x4444 && offsetof(city_player, player_rank) == 0x444C
        && offsetof(city_player, personal_savings) == 0x4450 && offsetof(city_player, donated_last_year) == 0x4454
        && offsetof(city_player, donated_this_year) == 0x4458 && offsetof(city_player, donate_amount) == 0x445C
        && offsetof(city_player, working_dock_ids) == 0x4460 && offsetof(city_player, has_temple_complex) == 0x4478
        && offsetof(city_player, animals) == 0x447A && offsetof(city_player, num_sea_routes) == 0x447C
        && offsetof(city_player, num_land_routes) == 0x447E
        && offsetof(city_player, sea_trade_problem_duration) == 0x4480
        && offsetof(city_player, land_trade_problem_duration) == 0x4482
        && offsetof(city_player, palace_placed) == 0x4486 && offsetof(city_player, working_wharfs) == 0x4488
        && offsetof(city_player, temple_complex_upgrades) == 0x448A && offsetof(city_player, palace_robberies) == 0x448C
        && offsetof(city_player, palace_robberies_last_year) == 0x448E
        && offsetof(city_player, docker_import_resource) == 0x4490
        && offsetof(city_player, docker_export_resource) == 0x4494 && offsetof(city_player, bailout_taken) == 0x4498
        && offsetof(city_player, bailout_refused_message_shown) == 0x449C
        && offsetof(city_player, cheats_used) == 0x44A0 && offsetof(city_player, recruiter_x) == 0x44A4
        && offsetof(city_player, recruiter_y) == 0x44A6 && offsetof(city_player, recruiter_grid_offset) == 0x44A8
        && offsetof(city_player, recruiter_building_id) == 0x44AC && offsetof(city_player, recruiter_placed) == 0x44B0
        && offsetof(city_player, zoo_shows) == 0x44C8 && offsetof(city_player, zoo_no_shows_weighted) == 0x44CC
        && offsetof(city_player, mission_has_won) == 0x44D0
        && offsetof(city_player, mission_continue_months_left) == 0x44D4
        && offsetof(city_player, mission_continue_months_chosen) == 0x44D8
        && offsetof(city_player, wage_rate_paid_this_year) == 0x44DC
        && offsetof(city_player, tribute_estimate) == 0x44E0 && offsetof(city_player, tribute_paid) == 0x44E4
        && offsetof(city_player, tribute_not_paid_last_year) == 0x44E8
        && offsetof(city_player, tribute_not_paid_total_years) == 0x44EC
        && offsetof(city_player, festival_selected_god) == 0x44F0
        && offsetof(city_player, festival_selected_size) == 0x44F4
        && offsetof(city_player, festival_planned_size) == 0x44F8
        && offsetof(city_player, festival_planned_months_to_go) == 0x44FC
        && offsetof(city_player, festival_planned_god) == 0x4500 && offsetof(city_player, festival_cost) == 0x4504
        && offsetof(city_player, festival_grand_beer) == 0x4510
        && offsetof(city_player, festival_not_enough_beer) == 0x4514
        && offsetof(city_player, average_religion) == 0x4518 && offsetof(city_player, average_education) == 0x451C
        && offsetof(city_player, average_health) == 0x4520
        && offsetof(city_player, first_festival_effect_months) == 0x4528
        && offsetof(city_player, second_festival_effect_months) == 0x452C
        && offsetof(city_player, sentiment_unemployment) == 0x4534
        && offsetof(city_player, sentiment_previous_value) == 0x4538
        && offsetof(city_player, sentiment_low_mood_cause) == 0x4540
        && offsetof(city_player, security_breach_duration) == 0x4544
        && offsetof(city_player, rating_yearly_counters) == 0x4548
        && offsetof(city_player, selected_gift_size) == 0x4558 && offsetof(city_player, months_since_gift) == 0x455C
        && offsetof(city_player, gift_overdose_penalty) == 0x4560 && offsetof(city_player, gift_id) == 0x4568
        && offsetof(city_player, gift_cost) == 0x4574 && offsetof(city_player, kingdom_salary_penalty) == 0x4580
        && offsetof(city_player, kingdom_milestone_penalty) == 0x4584
        && offsetof(city_player, kingdom_ignored_request_penalty) == 0x4588
        && offsetof(city_player, kingdom_last_year) == 0x458C && offsetof(city_player, kingdom_change) == 0x4590
        && offsetof(city_player, natives_hostile) == 0x4594 && offsetof(city_player, mission_post_operational) == 0x459C
        && offsetof(city_player, main_native_meeting_x) == 0x45A0
        && offsetof(city_player, main_native_meeting_y) == 0x45A4
        && offsetof(city_player, wage_rate_paid_last_year) == 0x45A8
        && offsetof(city_player, food_needed_per_month) == 0x45AC
        && offsetof(city_player, granaries_understaffed) == 0x45B0
        && offsetof(city_player, granaries_not_operating) == 0x45B4
        && offsetof(city_player, granaries_not_operating_with_food) == 0x45B8
        && offsetof(city_player, ra_exports_bonus_months) == 0x45CC && offsetof(city_player, enemies_to_leave) == 0x45D0
        && offsetof(city_player, gods_angry_message_delay) == 0x45D8
        && offsetof(city_player, food_consumed_last_month) == 0x45DC
        && offsetof(city_player, food_produced_last_month) == 0x45E0
        && offsetof(city_player, food_produced_this_month) == 0x45E4
        && offsetof(city_player, estimated_tax_income) == 0x45EC
        && offsetof(city_player, distribution_center_x) == 0x45F4
        && offsetof(city_player, distribution_center_y) == 0x45F6
        && offsetof(city_player, distribution_center_grid_offset) == 0x45F8
        && offsetof(city_player, distribution_center_building_id) == 0x45FC
        && offsetof(city_player, distribution_center_placed) == 0x4600
        && offsetof(city_player, shipyard_boats_requested) == 0x4630 && offsetof(city_player, enemies) == 0x4634
        && offsetof(city_player, sentiment_wages) == 0x4638 && offsetof(city_player, people_in_huts) == 0x463C
        && offsetof(city_player, people_in_residences_and_up) == 0x4640
        && offsetof(city_player, kingdom_soldiers) == 0x4644 && offsetof(city_player, destroyed_buildings) == 0x4658
        && offsetof(city_player, total_transport_ships) == 0x4664
        && offsetof(city_player, empire_service_legions_fighting) == 0x4665
        && offsetof(city_player, empire_service_legions_not_fighting) == 0x4666
        && offsetof(city_player, total_warships) == 0x4668 && offsetof(city_player, empire_service_warships) == 0x4669
        && offsetof(city_player, legions_fighting) == 0x466A && offsetof(city_player, legions_not_fighting) == 0x466B
        && offsetof(city_player, total_legions) == 0x466C && offsetof(city_player, empire_service_legions) == 0x466D
        && offsetof(city_player, total_soldiers) == 0x466F && offsetof(city_player, trade_center_building_id) == 0x4674
        && offsetof(city_player, soldiers) == 0x4678 && offsetof(city_player, sound_march_enemy) == 0x467F
        && offsetof(city_player, sound_march_horse) == 0x4680 && offsetof(city_player, sentiment_food_toggle) == 0x468B
        && offsetof(city_player, kingdom_soldiers_removed) == 0x4694 && offsetof(city_player, chariot_legions) == 0x4698
        && offsetof(city_player, population_highest_ever) == 0x469C && offsetof(city_player, estimated_wages) == 0x46A0
        && offsetof(city_player, luxury_goods_kinds) == 0x46A4 && offsetof(city_player, prosperity_max) == 0x46A8
        && offsetof(city_player, largest_road_networks) == 0x46AC
        && offsetof(city_player, houses_missing_second_luxury) == 0x46FC
        && offsetof(city_player, flotsam_special) == 0x4700 && offsetof(city_player, senet_house_has_plays) == 0x4704
        && offsetof(city_player, fired_message_shown) == 0x4714
        && offsetof(city_player, victory_message_shown) == 0x4718
        && offsetof(city_player, mission_saved_game_state) == 0x471C
        && offsetof(city_player, tutorial_flag_seen_a) == 0x4720
        && offsetof(city_player, tutorial_flag_seen_g) == 0x4724 && offsetof(city_player, attacking_natives) == 0x4728
        && offsetof(city_player, temple_complex_building_id) == 0x472C
        && offsetof(city_player, monument_def_id) == 0x4730 && offsetof(city_player, monument_building_id) == 0x473C
        && offsetof(city_player, houses_requiring_more_courthouse) == 0x4748
        && offsetof(city_player, houses_missing_any_courthouse) == 0x474C
        && offsetof(city_player, plague_houses) == 0x4750
        && offsetof(city_player, requests_and_festivals_last_year) == 0x4754
        && offsetof(city_player, requests_and_festivals_this_year) == 0x4758
        && offsetof(city_player, migration_newcomers_last_month) == 0x475C
        && offsetof(city_player, crimes_this_month) == 0x4760 && offsetof(city_player, gold_stolen_this_month) == 0x4764
        && offsetof(city_player, advisor_comment) == 0x4768 && offsetof(city_player, hunting_lodges_working) == 0x476C
        && offsetof(city_player, game_meat_last_month) == 0x4770
        && offsetof(city_player, game_meat_this_month) == 0x4774
        && offsetof(city_player, fishing_wharfs_working) == 0x4778 && offsetof(city_player, fish_last_month) == 0x477C
        && offsetof(city_player, fish_this_month) == 0x4780 && offsetof(city_player, savings_lost) == 0x4784
        && offsetof(city_player, festival_square_x) == 0x47A0 && offsetof(city_player, festival_square_y) == 0x47A4
        && offsetof(city_player, difficulty) == 0x47A8 && offsetof(city_player, gold_last_year) == 0x47AC
        && offsetof(city_player, gold_this_year) == 0x47B0 && offsetof(city_player, ra_no_traders_months) == 0x47B4
        && offsetof(city_player, festival_square_placed) == 0x4814 && offsetof(city_player, god_happy_bolts) == 0x4816
        && offsetof(city_player, monument_completion_flag) == 0x4820
        && offsetof(city_player, monument_completion_months) == 0x4828
        && offsetof(city_player, months_in_debt) == 0x482C && offsetof(city_player, years_in_debt) == 0x4830
        && offsetof(city_player, resource_list_scroll) == 0x4834
        && offsetof(city_player, resource_settings_step) == 0x4838
        && offsetof(city_player, granary_food_stored) == 0x483C && offsetof(city_player, storage_space) == 0x4860
        && offsetof(city_player, storage_stored) == 0x48F0 && offsetof(city_player, plague_count) == 0x4980
        && offsetof(city_player, ra_trade_bonus_months) == 0x4984
        && offsetof(city_player, ra_trade_penalty_months) == 0x4986
        && offsetof(city_player, ra_trade_minor_penalty_months) == 0x4988
        && offsetof(city_player, seth_minor_blessing_months) == 0x498C
        && offsetof(city_player, bast_culture_decay_skip) == 0x4990
        && offsetof(city_player, osiris_double_farm_yield) == 0x4994
        && offsetof(city_player, osiris_flood_destroys_farms) == 0x4998
        && offsetof(city_player, mansion_placed) == 0x499C && offsetof(city_player, enemy_warships) == 0x49A0
        && offsetof(city_player, resource_gift_received) == 0x49A4 && offsetof(city_player, trade_prices_mode) == 0x49CC
        && offsetof(city_player, military_academy_placed) == 0x49D0
        && offsetof(city_player, sphinx_stage_before_delete) == 0x49D4,
      "city_player is the savegame's layout");

    enum {
        CITY_PLAYER_RECORDS = 2,
    };

    typedef city_player city_player_records[CITY_PLAYER_RECORDS];

    enum scenario_record_sizes {
        SCENARIO_GODS = 5,
        SCENARIO_NAME_SIZE = 64,
        SCENARIO_BRIEFING_SIZE = 512,
        SCENARIO_HERD_POINTS = 4,
        SCENARIO_FISHING_POINTS = 8,
        SCENARIO_LAND_INVASION_POINTS = 8,
        SCENARIO_INVASION_POINTS = 16,
        SCENARIO_INVASION_LANDINGS = 3,
        SCENARIO_ALLOWED_BUILDINGS = 104,
        SCENARIO_MONUMENTS = 3,
        SCENARIO_BURIAL_RESOURCES = 36,
    };

    typedef union scenario_start {
        int16_t year;
        int32_t word;
    } scenario_start;

    typedef struct scenario_record {
        scenario_start start;
        int16_t climate;
        uint8_t reserved_1[4];
        int16_t god_status[SCENARIO_GODS];
        uint8_t reserved_2[12];
        int32_t initial_funds;
        int16_t enemy_type;
        int16_t enemy_type_high;
        uint8_t reserved_3[4];
        int32_t map_width;
        int32_t map_height;
        int32_t grid_start;
        int32_t grid_border_size;
        char name[SCENARIO_NAME_SIZE];
        char briefing[SCENARIO_BRIEFING_SIZE];
        uint8_t reserved_4[10];
        int16_t image;
        int16_t open_play;
        int16_t initial_rank;
        int16_t predator_herd_x[SCENARIO_HERD_POINTS];
        int16_t predator_herd_y[SCENARIO_HERD_POINTS];
        int16_t fishing_point_x[SCENARIO_FISHING_POINTS];
        int16_t fishing_point_y[SCENARIO_FISHING_POINTS];
        int16_t predator_variant;
        uint8_t reserved_5[38];
        int32_t kingdom_supplies_grain;
        int16_t invasion_point_x[SCENARIO_INVASION_POINTS];
        int16_t invasion_point_y[SCENARIO_INVASION_POINTS];
        uint8_t reserved_6[36];
        int32_t win_culture;
        int32_t win_prosperity;
        int32_t win_monument;
        int32_t win_kingdom;
        int32_t win_houses;
        int32_t win_houses_level;
        uint8_t win_culture_enabled;
        uint8_t win_prosperity_enabled;
        uint8_t win_monument_enabled;
        uint8_t win_kingdom_enabled;
        uint8_t reserved_7[8];
        int32_t time_limit;
        int32_t time_limit_years;
        int32_t survival;
        int32_t survival_years;
        int32_t win_population_enabled;
        int32_t win_population;
        int16_t earthquake_x;
        int16_t earthquake_y;
        int16_t entry_point_x;
        int16_t entry_point_y;
        int16_t exit_point_x;
        int16_t exit_point_y;
        uint8_t reserved_8[32];
        int16_t river_entry_x;
        int16_t river_entry_y;
        int16_t river_exit_x;
        int16_t river_exit_y;
        int32_t bailout_amount;
        int32_t milestone25_year;
        int32_t milestone50_year;
        int32_t milestone75_year;
        int32_t native_image_hut;
        int32_t native_image_meeting;
        int32_t native_image_crops;
        uint8_t climate_type;
        uint8_t flotsam_enabled;
        uint8_t reserved_9[2];
        int32_t empire_expanded;
        uint8_t reserved_10[4];
        uint8_t animation_set;
        uint8_t soldier_images_alt;
        uint8_t open_play_scenario_id;
        uint8_t reserved_11;
        int32_t prey_herd_x[SCENARIO_HERD_POINTS];
        int32_t prey_herd_y[SCENARIO_HERD_POINTS];
        uint16_t allowed_buildings[SCENARIO_ALLOWED_BUILDINGS];
        int16_t temple_complexes_allowed[SCENARIO_GODS];
        uint8_t reserved_12[10];
        int32_t invasion_landing_x[SCENARIO_INVASION_LANDINGS];
        int32_t invasion_landing_y[SCENARIO_INVASION_LANDINGS];
        int32_t interest_rate;
        int16_t monument_def_ids[SCENARIO_MONUMENTS];
        uint8_t reserved_13[2];
        int32_t provisions_needed[SCENARIO_BURIAL_RESOURCES];
        int32_t provisions_sent[SCENARIO_BURIAL_RESOURCES];
        int32_t pharaoh_name_id;
        int32_t player_title_id;
    } scenario_record;

    static_assert(sizeof(scenario_record) == 0x638, "scenario_record is a savegame and scenario record of 1592 bytes");

    static_assert(
      offsetof(scenario_record, god_status) == 0xA && offsetof(scenario_record, name) == 0x3C
        && offsetof(scenario_record, image) == 0x286 && offsetof(scenario_record, kingdom_supplies_grain) == 0x2E4
        && offsetof(scenario_record, win_culture) == 0x34C && offsetof(scenario_record, time_limit) == 0x370
        && offsetof(scenario_record, river_entry_x) == 0x3B4 && offsetof(scenario_record, empire_expanded) == 0x3DC
        && offsetof(scenario_record, allowed_buildings) == 0x408
        && offsetof(scenario_record, temple_complexes_allowed) == 0x4D8
        && offsetof(scenario_record, invasion_landing_x) == 0x4EC
        && offsetof(scenario_record, provisions_needed) == 0x510 && offsetof(scenario_record, pharaoh_name_id) == 0x630,
      "scenario_record is the savegame and scenario layout");

    typedef enum resource_type {
        RESOURCE_NONE = 0,
        RESOURCE_GRAIN = 1,
        RESOURCE_MEAT = 2,
        RESOURCE_LETTUCE = 3,
        RESOURCE_CHICKPEAS = 4,
        RESOURCE_POMEGRANATES = 5,
        RESOURCE_FIGS = 6,
        RESOURCE_FISH = 7,
        RESOURCE_GAMEMEAT = 8,
        RESOURCE_STRAW = 9,
        RESOURCE_WEAPONS = 10,
        RESOURCE_CLAY = 11,
        RESOURCE_BRICKS = 12,
        RESOURCE_POTTERY = 13,
        RESOURCE_BARLEY = 14,
        RESOURCE_BEER = 15,
        RESOURCE_FLAX = 16,
        RESOURCE_LINEN = 17,
        RESOURCE_GEMS = 18,
        RESOURCE_LUXURY_GOODS = 19,
        RESOURCE_TIMBER = 20,
        RESOURCE_GOLD = 21,
        RESOURCE_REEDS = 22,
        RESOURCE_PAPYRUS = 23,
        RESOURCE_STONE = 24,
        RESOURCE_LIMESTONE = 25,
        RESOURCE_GRANITE = 26,
        RESOURCE_UNUSED = 27,
        RESOURCE_CHARIOTS = 28,
        RESOURCE_COPPER = 29,
        RESOURCE_SANDSTONE = 30,
        RESOURCE_OIL = 31,
        RESOURCE_HENNA = 32,
        RESOURCE_PAINT = 33,
        RESOURCE_LAMPS = 34,
        RESOURCE_MARBLE = 35,
        RESOURCE_DEBEN = 36,
        RESOURCE_TROOPS = 37,
        RESOURCE_MIN = 1,
        RESOURCE_MAX = 36,
        RESOURCE_MIN_FOOD = 1,
        RESOURCE_MAX_FOOD = 9,
    } resource_type;

    enum empire_route_limit {
        EMPIRE_ROUTES = 50,
        EMPIRE_ROUTE_POINTS = 50,
    };

    typedef struct empire_route_point {
        int16_t x;
        int16_t y;
        uint8_t segment;
        uint8_t pad;
    } empire_route_point;

    typedef struct empire_route {
        uint8_t step;
        uint8_t reserved_1[3];
        int32_t path_slot;
        empire_route_point points[EMPIRE_ROUTE_POINTS];
        int32_t path_length;
        int32_t path_capacity;
        int16_t first_object;
        int16_t last_object;
        uint8_t kind;
        uint8_t num_points;
        uint8_t in_use;
        uint8_t reserved_2;
    } empire_route;

    static_assert(sizeof(empire_route) == 0x144, "empire_route is a savegame record of 324 bytes");

    static_assert(offsetof(empire_route, path_length) == 0x134 && offsetof(empire_route, kind) == 0x140
                    && offsetof(empire_route, in_use) == 0x142,
      "empire_route is the savegame's layout");

    enum {
        EMPIRE_CITY_COUNT = 61,
        EMPIRE_CITY_TRADER_FIGURES = 8,
        EMPIRE_OBJECT_COUNT = 200,
        EMPIRE_OBJECT_SOLD_RESOURCES = 14,
        EMPIRE_OBJECT_BOUGHT_RESOURCES = 8,
        EMPIRE_TRADE_ROUTES = 20,
        EMPIRE_CITY_NAMES = 66,
        EMPIRE_EVENT_MARKERS = 92,
        EMPIRE_MAP_HEADERS = 40,
        EMPIRE_TRADERS = 100,
    };

    typedef struct {
        uint8_t in_use;
        uint8_t reserved_1;
        uint8_t type;
        uint8_t name_id;
        uint8_t route_id;
        uint8_t is_open;
        uint8_t buys[RESOURCE_MAX];
        uint8_t sells[RESOURCE_MAX];
        int16_t cost_to_open;
        int16_t unread_default;
        int16_t trader_entry_delay;
        int16_t trader_blocked;
        int16_t map_object;
        uint8_t is_sea_trade;
        uint8_t reserved_2;
        int16_t trader_figures[EMPIRE_CITY_TRADER_FIGURES];
    } empire_city;

    static_assert(sizeof(empire_city) == 0x6A, "empire_city is a savegame record of 106 bytes");

    static_assert(offsetof(empire_city, sells) == 0x2A && offsetof(empire_city, cost_to_open) == 0x4E
                    && offsetof(empire_city, trader_entry_delay) == 0x52 && offsetof(empire_city, map_object) == 0x56
                    && offsetof(empire_city, trader_figures) == 0x5A,
      "empire_city is the savegame's layout");

    typedef struct {
        uint8_t type;
        uint8_t in_use;
        uint8_t animation_frame;
        uint8_t reserved_1;
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
        uint16_t image_id;
        int16_t image_offset;
        uint8_t reserved_2[3];
        uint8_t text_align;
        int16_t expanded_x;
        int16_t expanded_y;
        uint8_t city_type;
        uint8_t name_id;
        uint8_t route_id;
        uint8_t is_open;
        int16_t cost_to_open;
        uint8_t sells[EMPIRE_OBJECT_SOLD_RESOURCES];
        uint8_t reserved_3[7];
        uint8_t city_type_countdown;
        uint8_t buys[EMPIRE_OBJECT_BOUGHT_RESOURCES];
        uint8_t invasion_path_id;
        uint8_t invasion_years;
        uint8_t trade_amount[RESOURCE_MAX];
    } empire_object;

    static_assert(sizeof(empire_object) == 0x62, "empire_object is a savegame and scenario record of 98 bytes");

    static_assert(offsetof(empire_object, image_id) == 0x0C && offsetof(empire_object, text_align) == 0x13
                    && offsetof(empire_object, city_type) == 0x18 && offsetof(empire_object, cost_to_open) == 0x1C
                    && offsetof(empire_object, sells) == 0x1E && offsetof(empire_object, city_type_countdown) == 0x33
                    && offsetof(empire_object, buys) == 0x34 && offsetof(empire_object, invasion_path_id) == 0x3C
                    && offsetof(empire_object, trade_amount) == 0x3E,
      "empire_object is the savegame and scenario layout");

    typedef struct empire_trader {
        int32_t bought_amount;
        int32_t sold_amount;
        uint8_t bought_resources[RESOURCE_MAX];
        uint8_t sold_resources[RESOURCE_MAX];
        int32_t bought_value;
        int32_t sold_value;
    } empire_trader;

    static_assert(sizeof(empire_trader) == 0x58, "empire_trader is a savegame record of 88 bytes");

    static_assert(offsetof(empire_trader, sold_resources) == 0x2C && offsetof(empire_trader, bought_value) == 0x50,
      "empire_trader is the savegame's layout");

    typedef struct {
        int16_t scroll_x;
        int16_t scroll_y;
        int16_t editor_objects_started;
        uint8_t reserved[26];
    } empire_map_header;

    static_assert(sizeof(empire_map_header) == 0x20, "empire_map_header is a savegame and scenario record of 32 bytes");

    typedef empire_map_header empire_map_headers[EMPIRE_MAP_HEADERS];

    typedef empire_city empire_city_records[EMPIRE_CITY_COUNT];

    typedef empire_object empire_object_records[EMPIRE_OBJECT_COUNT];

    typedef int32_t trade_route_amounts[EMPIRE_TRADE_ROUTES][RESOURCE_MAX];

    enum message_list_size {
        MAX_MESSAGES = 1000,
        MESSAGE_QUEUE_SIZE = 20,
        MAX_WARNINGS = 5,
        MESSAGE_CATEGORY_COUNT = 20,
    };

    typedef struct {
        int32_t param1;
        int32_t param2;
        int16_t year;
        int16_t type;
        int16_t sequence;
        uint8_t is_read;
        uint8_t month;
        int16_t phrases[15];
        uint8_t reserved_1[2];
    } city_message;

    static_assert(sizeof(city_message) == 0x30, "city_message is a savegame record of 48 bytes");

    static_assert(offsetof(city_message, type) == 0x0A && offsetof(city_message, phrases) == 0x10,
      "city_message is the savegame's layout");

    typedef city_message city_message_table[MAX_MESSAGES];

    typedef struct {
        int32_t reserved_1;
        int16_t building_id;
        int16_t reserved_2;
        uint8_t in_use;
        uint8_t empty_all;
        uint8_t resource_state[STORAGE_RESOURCES];
        uint8_t reserved_3[6];
        int16_t accept_amount[STORAGE_RESOURCES];
        int16_t get_amount[STORAGE_RESOURCES];
    } building_storage;

    static_assert(sizeof(building_storage) == 0xC4, "building_storage is a savegame record of 196 bytes");

    static_assert(offsetof(building_storage, in_use) == 0x08 && offsetof(building_storage, accept_amount) == 0x34,
      "building_storage is the savegame's layout");

    enum ferry_queue_limit {
        FERRY_QUEUE_CAPACITY = 50,
        FERRY_QUEUES = 50,
    };

    typedef struct {
        int32_t in_use;
        int32_t head;
        int32_t tail;
        int32_t capacity;
        int32_t reserved_1;
        int32_t items[1];
    } ring_queue;

    static_assert(offsetof(ring_queue, items) == 0x14, "ring_queue is the savegame's layout");

    typedef struct ferry_queue {
        ring_queue queue;
        int32_t items_after_first[FERRY_QUEUE_CAPACITY - 1];
        int32_t building_id;
    } ferry_queue;

    static_assert(sizeof(ferry_queue) == 0xE0, "ferry_queue is a savegame record of 224 bytes");

    static_assert(offsetof(ferry_queue, building_id) == 0xDC, "ferry_queue is the savegame's layout");

    typedef ferry_queue ferry_queue_records[FERRY_QUEUES];

    enum ferry_path_record_limit {
        FERRY_PATH_RECORDS = 50,
        FERRY_PATH_PASSENGER_SLOTS = 10,
    };

    typedef struct ferry_path {
        uint8_t in_use;
        uint8_t reserved_1[3];
        int32_t passengers[FERRY_PATH_PASSENGER_SLOTS];
    } ferry_path;

    static_assert(sizeof(ferry_path) == 0x2C, "ferry_path is a savegame record of 44 bytes");

    static_assert(offsetof(ferry_path, passengers) == 4, "ferry_path is the savegame's layout");

    typedef struct {
        int32_t season_initial;
        int32_t duration_initial;
        int32_t quality_initial;
        int32_t season;
        int32_t duration;
        int32_t quality;
        int32_t reserved_1;
        int32_t quality_next;
        int32_t quality_last;
    } floodplain_settings;

    static_assert(sizeof(floodplain_settings) == 0x24, "floodplain_settings is a savegame record of 36 bytes");

    enum event_invader {
        EVENT_INVADER_ENEMY = 1,
        EVENT_INVADER_EGYPT = 2,
        EVENT_INVADER_PHARAOH = 3,
        EVENT_INVADER_BEDOUINS = 4,
        EVENT_INVADERS = 4,
    };

    enum scenario_event_limit {
        SCENARIO_MAX_EVENTS = 150,
        SCENARIO_EVENTS_LIMIT = 140,
        SCENARIO_EVENTS_ADD_ONLY_LIMIT = 120,
        SCENARIO_CHEAT_INVASION_EVENT = 140,
        SCENARIO_EARTHQUAKE_FRONTS = 4,
    };

    typedef struct {
        int16_t value;
        int16_t fixed;
        int16_t min;
        int16_t max;
    } scenario_value;

    typedef struct {
        int16_t first_formation_id;
        int16_t home_x;
        int16_t home_y;
        int16_t layout;
        int16_t destination_x;
        int16_t destination_y;
        int16_t destination_building_id;
        int16_t num_formations;
        int16_t ignore_soldiers;
        uint8_t reserved_1[4];
    } scenario_invasion_data;

    typedef struct {
        int16_t duration;
        int16_t delay;
        int16_t ticks;
        int16_t locations[2 * SCENARIO_EARTHQUAKE_FRONTS];
    } scenario_earthquake_data;

    typedef struct {
        int16_t id;
        uint8_t type;
        uint8_t month;
        scenario_value item;
        scenario_value amount;
        scenario_value year;
        scenario_value route;
        int16_t on_completed;
        int16_t on_refusal;
        uint32_t flags;
        int16_t months_initial;
        int16_t months_left;
        int16_t state;
        uint8_t is_active;
        uint8_t can_comply_shown;
        int16_t parent_id;
        uint8_t phrase_var;
        uint8_t parent_phrase_var;
        int16_t attack_target;
        union {
            scenario_earthquake_data earthquake;
            scenario_invasion_data invasion;
        } data;
        int16_t earthquake_step;
        int16_t on_too_late;
        int16_t on_defeat;
        uint8_t sender_faction;
        uint8_t invasion_warnings_shown;
        scenario_value invasion;
        uint8_t subtype;
        uint8_t months_margin;
        uint8_t coin;
        uint8_t parent_city;
        int16_t parent_phrase;
        int16_t parent_item;
        int16_t parent_amount;
        uint8_t reason[4];
        uint8_t chain_marked;
        uint8_t reserved_1[13];
    } scenario_event;

    static_assert(sizeof(scenario_event) == 0x7C, "scenario_event is a savegame and scenario record of 124 bytes");

    static_assert(offsetof(scenario_event, flags) == 0x28, "scenario_event is the savegame and scenario layout");

    static_assert(offsetof(scenario_event, reason) == 0x6A, "scenario_event is the savegame and scenario layout");

    static_assert(
      (offsetof(scenario_event, data)
        + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, earthquake)
        + offsetof(std::remove_reference_t<
                     decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                         .earthquake)>,
          duration))
          == 0x3A
        && (offsetof(scenario_event, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, earthquake)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                     .earthquake)>,
               ticks))
             == 0x3E
        && (offsetof(scenario_event, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, earthquake)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                     .earthquake)>,
               locations))
             == 0x40
        && (offsetof(scenario_event, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, invasion)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                     .invasion)>,
               layout))
             == 0x40
        && (offsetof(scenario_event, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, invasion)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                     .invasion)>,
               destination_building_id))
             == 0x46
        && (offsetof(scenario_event, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, invasion)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                     .invasion)>,
               num_formations))
             == 0x48
        && (offsetof(scenario_event, data)
             + offsetof(std::remove_reference_t<decltype(std::declval<scenario_event>().data)>, invasion)
             + offsetof(
               std::remove_reference_t<
                 decltype(std::declval<std::remove_reference_t<decltype(std::declval<scenario_event>().data)>>()
                     .invasion)>,
               ignore_soldiers))
             == 0x4A
        && offsetof(scenario_event, earthquake_step) == 0x50 && offsetof(scenario_event, invasion) == 0x58
        && offsetof(scenario_event, parent_amount) == 0x68,
      "scenario_event is the savegame and scenario layout");

    typedef struct {
        int32_t count;
        scenario_event events[SCENARIO_MAX_EVENTS];
        int32_t editor_selected_id;
        int32_t editor_scroll;
        uint8_t earthquake_active;
        uint8_t reserved_1;
        uint8_t spare_47[14];
        uint8_t invasion_search_flag;
        uint8_t spare_48;
        int16_t editor_value;
        int16_t editor_field;
        uint8_t editor_phrase;
        uint8_t spare_49;
    } scenario_events_t;

    static_assert(sizeof(scenario_events_t) == 0x48CC,
      "scenario_events_t is a savegame and scenario record of 18636 bytes");

    static_assert(offsetof(scenario_events_t, invasion_search_flag) == 0x48C4
                    && offsetof(scenario_events_t, editor_value) == 0x48C6
                    && offsetof(scenario_events_t, editor_phrase) == 0x48CA,
      "scenario_events_t is the savegame and scenario layout");

    static_assert(offsetof(scenario_events_t, events) == 0x04
                    && offsetof(scenario_events_t, editor_selected_id) == 0x48AC
                    && offsetof(scenario_events_t, editor_scroll) == 0x48B0
                    && offsetof(scenario_events_t, earthquake_active) == 0x48B4,
      "scenario_events_t is the savegame and scenario layout");

    enum city_sound_size {
        CITY_SOUND_DIRECTIONS = 5,
        CITY_SOUND_SAMPLES = 8,
        CITY_SOUND_CHANNELS = 70,
    };

    typedef struct {
        int32_t available;
        int32_t total_views;
        int32_t views_threshold;
        int32_t direction_views[CITY_SOUND_DIRECTIONS];
        int32_t current_channel;
        int32_t num_channels;
        int32_t channels[CITY_SOUND_SAMPLES];
        int32_t in_use;
        int32_t times_played;
        uint32_t last_played_time;
        uint32_t delay_millis;
        int32_t should_play;
        int32_t unused[9];
    } city_sound_channel;

    static_assert(sizeof(city_sound_channel) == 0x80, "city_sound_channel is a savegame record of 128 bytes");

    typedef struct vegetation_growth_record {
        int32_t marsh_growth_b;
        int32_t tree_growth_a;
        int32_t marsh_growth_a;
        int32_t tree_growth_b;
        uint8_t trees_reachable;
        uint8_t trees_present;
        uint8_t reeds_reachable;
        uint8_t marsh_present;
    } vegetation_growth_record;

    static_assert(sizeof(vegetation_growth_record) == 0x14,
      "vegetation_growth_record is a savegame record of 20 bytes");

    static_assert(offsetof(vegetation_growth_record, trees_reachable) == 0x10
                    && offsetof(vegetation_growth_record, marsh_present) == 0x13,
      "vegetation_growth_record is the savegame's layout");

    typedef struct {
        int32_t script;
        int32_t sequence;
        int32_t frame;
        int32_t work_remaining;
        int16_t mode;
        int16_t figure_id;
        uint8_t figure_action;
        uint8_t reverse;
        uint8_t spare_7[2];
    } monument_spot;

    static_assert(sizeof(monument_spot) == 24, "monument_spot is a savegame record of 24 bytes");


} // namespace og
