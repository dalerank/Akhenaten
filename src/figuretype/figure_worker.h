#pragma once

#include "building/monument_pyramid_figure.h"
#include "figure/figure.h"

// OG figure_action.h FIGURE_ACTION_LABORER_* (laborer.c).
enum e_laborer_action : uint16_t {
    ACTION_8_LABORER_IDLE = 8,
    ACTION_9_LABORER_GOING_OUT = 9,
    ACTION_10_LABORER_TO_FARM = 10,
    ACTION_12_LABORER_ROAMING = 12,
    ACTION_13_LABORER_RETURNING = 13,
    ACTION_15_LABORER_TO_STORAGE_YARD = 15,
    ACTION_16_LABORER_AT_STORAGE_YARD = 16,
    ACTION_17_LABORER_TO_PYRAMID = 17,
    ACTION_18_LABORER_CLIMB_RAMP = 18,
    ACTION_19_LABORER_TO_MASON = 19,
    ACTION_20_LABORER_WALK_TO_MASON = 20,
    ACTION_21_LABORER_TO_LEVEL_TILE = 21,
    ACTION_22_LABORER_LEVEL_WORK = 22,
    ACTION_23_LABORER_SLED_TO_SUN_TEMPLE = 23,
    ACTION_24_LABORER_TO_SUN_TEMPLE = 24,
    ACTION_25_LABORER_SUN_TEMPLE_WORK = 25,
    ACTION_26_LABORER_SLED_TO_MAUSOLEUM = 26,
    ACTION_27_LABORER_TO_MAUSOLEUM = 27,
    ACTION_28_LABORER_MAUSOLEUM_WORK = 28,
    ACTION_29_LABORER_DELIVERED = 29,
    ACTION_30_LABORER_SLED_AT_RAMP = 30,
    ACTION_31_LABORER_SLED_TO_LIBRARY = 31,
    ACTION_32_LABORER_TO_LIBRARY = 32,
    ACTION_33_LABORER_LIBRARY_WORK = 33,
    ACTION_34_LABORER_SLED_TO_CAESAREUM = 34,
    ACTION_35_LABORER_SLED_TO_LIGHTHOUSE = 35,
    ACTION_36_LABORER_SLED_TO_TOMB = 36,
    // Remake (gameplay_change_mastaba_clay_delivery): clay pulled to a mastaba on a sled train.
    ACTION_37_LABORER_SLED_TO_MASTABA = 37,

    // Non-OG sentinel: do_gotobuilding / do_goto route-lost → poof (removed in later commits).
    ACTION_14_LABORER_ROUTE_LOST = 14,

    // Transitional aliases (pre-OG names used by older call sites / JS).
    ACTION_9_WORKER_CREATED = ACTION_9_LABORER_GOING_OUT,
    ACTION_10_WORKER_GOING = ACTION_10_LABORER_TO_FARM,
    ACTION_11_WORKER_GOING_TO_PLACE = ACTION_21_LABORER_TO_LEVEL_TILE,
    ACTION_12_WORKER_LEVELING_GROUND = ACTION_22_LABORER_LEVEL_WORK,
    ACTION_13_WORKER_BACK_FROM_WORKS = ACTION_13_LABORER_RETURNING,
    ACTION_14_WORKER_CHECK_DESTINATION = ACTION_14_LABORER_ROUTE_LOST,
    ACTION_16_WORKER_TO_YARD = ACTION_15_LABORER_TO_STORAGE_YARD,
    ACTION_17_WORKER_TO_MASON = ACTION_17_LABORER_TO_PYRAMID,
    ACTION_18_WORKER_DELIVER_BLOCK = ACTION_29_LABORER_DELIVERED,
    ACTION_19_WORKER_CLIMB_RAMP = ACTION_18_LABORER_CLIMB_RAMP,
    ACTION_20_WORKER_TO_MASON_ON_LAYER = ACTION_19_LABORER_TO_MASON,
    ACTION_21_WORKER_WALK_TO_MASON = ACTION_20_LABORER_WALK_TO_MASON,
};

class figure_worker : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LABORER, figure_worker)

    figure_worker(figure *f) : figure_impl(f) {}
    virtual figure_worker *dcast_worker() override { return this; }

    static bool farm_work_waiting();

    // OG laborer_rules[] (laborer.h / laborer.c defaults).
    struct static_params : public figure_static_params {
        uint16_t load;
        uint16_t yard_wait_ticks;
        uint16_t ramp_route_retry_ticks;
        uint16_t ramp_route_give_up_ticks;
        uint16_t delivered_wait_ticks;
        uint16_t ferry_wait_ticks;
        uint16_t max_roam_ticks;
        uint16_t farm_walk_ticks;
        uint8_t home_road_radius;
        uint8_t max_out;
        uint8_t labor_seeker_houses;
        uint8_t spawn_delay_full;
        uint8_t spawn_delay_75_percent;
        uint8_t spawn_delay_50_percent;
        uint8_t spawn_delay_25_percent;
        uint8_t spawn_delay_low;
        uint8_t farm_search_distance;
        uint8_t farm_busy_labor_days;
        uint8_t farm_labor_days;
        uint8_t camp_labor_days;
        uint8_t level_tiles_in_a_row;
        uint8_t monument_work_searches;

        void archive_init();
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        figure_id mason_fid;
        uint8_t delivering_block;
        uint8_t walk_mode;
        uint8_t level_tiles_done;
        uint8_t site_state;
        uint8_t monument_searches;
        building_id yard_bid;
        building_id tomb_bid;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual pcstr info_type_name() const override;

    tile2i monumen_tile4work(building *b);
    // OG assign_pyramid block haul: style material → yard → mason.
    bool assign_block_delivery(building *monument, figure_id mason_fid);
    void assign_brick_delivery(building *monument, figure_id mason_fid) {
        assign_block_delivery(monument, mason_fid);
    }
    void find_work();
    e_resource block_material_for(building *monument, figure_id mason_fid) const;
    // Its sled was left behind: free the mason for another laborer and go back idle.
    void drop_load();

private:
    bool uses_ramp_climb(building *monument) const;
    tile2i ramp_entry_tile(building *monument) const;
    bool assign_farm_task(building *farm);
    bool assign_monument_task(building *monument, figure_id mason_fid);
    void monument_site_work_tick(building *monument);
    void sled_to_monument_tick(building *monument);
    bool assign_lamp_delivery(building *tomb);
    void at_storage_yard_lamps();
    bool assign_clay_delivery(building* mastaba);
    void at_storage_yard_clay();
    bool hauls_to_site() const;
    void sled_to_tomb_tick(building *tomb);
    void enter_idle_pool();
    void finish_block_delivery();
};

ANK_CONFIG_STRUCT(figure_worker::static_params,
    load, yard_wait_ticks, ramp_route_retry_ticks, ramp_route_give_up_ticks,
    delivered_wait_ticks, ferry_wait_ticks, max_roam_ticks, farm_walk_ticks,
    home_road_radius, max_out, labor_seeker_houses,
    spawn_delay_full, spawn_delay_75_percent, spawn_delay_50_percent,
    spawn_delay_25_percent, spawn_delay_low,
    farm_search_distance, farm_busy_labor_days, farm_labor_days, camp_labor_days,
    level_tiles_in_a_row, monument_work_searches)
