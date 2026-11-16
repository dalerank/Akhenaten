#pragma once

#include "building/building.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid_engine.h"
#include "building/monuments.h"
#include "figure/figure.h"

// OG pyramid_figure.c — walk up entry-point tables without normal routes
// (PYRAMID_STEPS_PER_TILE ticks per hop), then along the layer to a work part.

enum e_pyramid_figure_limits {
    PYRAMID_STEPS_PER_TILE = 15,
    PYRAMID_MOVEMENT_TILE_CHANGE_STEP = 8,
    PYRAMID_LABORER_NEAR_TILES = 7,
    PYRAMID_NO_FRONTIER_INDEX = 999,
    LABORER_TRAIN_CATCH_UP_TICKS = 8,
    LABORER_SLED_PULLERS = 5,
    LABORER_TRAIN_MAX_LINKS = 8,
    LABORER_SLED_SPACING = 12,
    LABORER_PULLER_SPACING = 7,
};

struct pyramid_figure_work_t {
    building_id previous_part = 0;
    building_id part = 0;
    int16_t previous_height = 0;
    int16_t height = 0;
    int16_t progress = 0;
    int16_t total = 0;
};

class monument_pyramid_figure {
public:
    void start_climb(figure_id fid);
    void set_walk_target(figure_id fid, building_id part_id, int height, bool set_walk_mode);
    int climb_step(figure_id fid, int step);
    void snap_to_part(figure_id fid);
    void walk_on_ramp(figure_id fid, int mode, int fail_action, int next_action);
    void find_next_part(figure_id fid, int set_height, int fail_action, int done_action, int next_action);

    void stonemason_arrive_part(figure_id fid);
    int laborer_can_enter_ramp(figure_id fid) const;
    void laborer_pair_with_mason(figure_id fid);
    void follow_closely(figure_id fid, figure_id leader_id, int climb_step_n, int distance);
    figure_id find_train_leader(figure_id fid, int *position) const;
    void train_follow(figure_id fid, int is_sled);
    void spawn_sled_train(figure_id laborer_fid);
    void spawn_single_sled(figure_id laborer_fid);
    figure* create_sled(figure* laborer, figure_id front_id);
    void drop_train(figure_id member_fid);

    building_id find_mason_waiting_for_block(building *head, int clear_partner);
    void sort_frontier(building_id* parts, int count) const;
    void wake_pair_mason(figure_id mason_fid);
    building_id next_on_ring(building_id part_id) const;

    pyramid_figure_work_t *work_data(figure *f) const;
    uint8_t &walk_mode(figure *f) const;
    building_id work_part_bid(figure *f) const;
    void set_work_part_bid(figure *f, building_id part_id) const;

private:
    enum e_ramp_step : int {
        RAMP_FAIL = 0,
        RAMP_ON_LAYER = 1,
        RAMP_WALK_TO_ENTRY = 2,
        RAMP_HANDLED = 3,
    };

    building *chain_head_for(building *any) const;
    int part_height_of(building_id part_id) const;
    building_id part_id_by_subtype(building *head, int subtype) const;
    const pyramid_entry_point *entry_points_for(building *head, int &count) const;
    int rotated_tile_kind(building *part) const;
    void neighbour_part_tile(int grid_offset, int rotation, building *head, int *x, int *y) const;
    const pyramid_paired_parts *pair_table_for(building *head, int &count) const;
    building_id part_pair(building* head, building_id part_id) const;
    building_id frontier_pair_part(building_id part_id, const svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier,
        uint8_t *is_first) const;
    int pair_waiting_mason(building_id part_id, const svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier) const;
    int claim_next_part(figure_id fid, int set_height, int done_action, int next_action);
    int part_mason_is_working(building_id part_id) const;
    int mason_waits_for_block(const figure *mason) const;
    int laborer_brings_block_to(figure_id laborer_id, figure_id mason_id) const;
    void follow_on_ground(figure_id fid, figure *f, const figure *leader, int distance) const;
    int follow_step_reaches_leader(figure_id fid, figure *f, const figure *leader, int climb_step_n, int distance);
    void take_leader_walk(figure_id fid, figure *f, const figure *leader, int distance);

    void stop_walk(figure *f, int fail_action) const;
    void begin_on_layer(figure *f, int next_action) const;
    int worker_has_ramp_part(figure_id fid, building *head, const pyramid_entry_point *entries, int count) const;
    int first_frontier_height(building *head) const;
    int ramp_next_step(figure_id fid, building_id part_id, int mode, const pyramid_entry_point *entries, int count, int *index);
    void walk_to_entry(figure_id fid, building_id part_id, int mode, const pyramid_entry_point &entry);
};

extern monument_pyramid_figure g_monument_pyramid_figure;

inline void pyramid_figure_start_climb(figure_id fid) {
    g_monument_pyramid_figure.start_climb(fid);
}
inline void pyramid_figure_set_walk_target(figure_id fid, building_id part_id, int height, bool set_walk_mode) {
    g_monument_pyramid_figure.set_walk_target(fid, part_id, height, set_walk_mode);
}
inline int pyramid_figure_climb_step(figure_id fid, int step) {
    return g_monument_pyramid_figure.climb_step(fid, step);
}
inline void pyramid_figure_snap_to_part(figure_id fid) {
    g_monument_pyramid_figure.snap_to_part(fid);
}
inline void pyramid_figure_walk_on_ramp(figure_id fid, int mode, int fail_action, int next_action) {
    g_monument_pyramid_figure.walk_on_ramp(fid, mode, fail_action, next_action);
}
inline void pyramid_figure_find_next_part(figure_id fid, int set_height, int fail_action, int done_action, int next_action) {
    g_monument_pyramid_figure.find_next_part(fid, set_height, fail_action, done_action, next_action);
}
inline void pyramid_stonemason_arrive_part(figure_id fid) {
    g_monument_pyramid_figure.stonemason_arrive_part(fid);
}
inline int pyramid_laborer_can_enter_ramp(figure_id fid) {
    return g_monument_pyramid_figure.laborer_can_enter_ramp(fid);
}
inline void pyramid_laborer_pair_with_mason(figure_id fid) {
    g_monument_pyramid_figure.laborer_pair_with_mason(fid);
}
inline void pyramid_figure_follow_closely(figure_id fid, figure_id leader_id, int climb_step_n, int distance) {
    g_monument_pyramid_figure.follow_closely(fid, leader_id, climb_step_n, distance);
}
inline figure_id pyramid_figure_find_train_leader(figure_id fid, int *position) {
    return g_monument_pyramid_figure.find_train_leader(fid, position);
}
inline void pyramid_figure_train_follow(figure_id fid, int is_sled) {
    g_monument_pyramid_figure.train_follow(fid, is_sled);
}
inline void pyramid_figure_spawn_sled_train(figure_id laborer_fid) {
    g_monument_pyramid_figure.spawn_sled_train(laborer_fid);
}
inline void pyramid_figure_spawn_single_sled(figure_id laborer_fid) {
    g_monument_pyramid_figure.spawn_single_sled(laborer_fid);
}
inline pyramid_figure_work_t *pyramid_figure_work_data(figure *f) {
    return g_monument_pyramid_figure.work_data(f);
}
inline uint8_t &pyramid_figure_walk_mode(figure *f) {
    return g_monument_pyramid_figure.walk_mode(f);
}
inline building_id pyramid_figure_work_part_bid(figure *f) {
    return g_monument_pyramid_figure.work_part_bid(f);
}
