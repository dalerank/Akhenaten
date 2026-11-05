#pragma once

#include "building/building.h"
#include "building/monuments.h"
#include "core/archive.h"
#include "core/svector.h"
#include "figure/figure.h"
#include "grid/point.h"

constexpr int PYRAMID_PARTS_CAPACITY = 144;
constexpr int PYRAMID_SIZE_COUNT = 5;

struct pyramid_engine_config_t {
    int blocks_per_layer = 6;
    int block_ticks_a = 41;
    int block_ticks_b = 69;
    int casing_ticks = 50;
};
ANK_CONFIG_STRUCT(pyramid_engine_config_t,
    blocks_per_layer, block_ticks_a, block_ticks_b, casing_ticks)

// OG pyramid_block_total @ 0x005F5C40 / pyramid_part_count @ 0x0056F7D8
inline constexpr int k_pyramid_block_totals[PYRAMID_SIZE_COUNT] = {216, 552, 1104, 1920, 3048};
inline constexpr int k_pyramid_part_counts[PYRAMID_SIZE_COUNT] = {16, 36, 64, 100, 144};

extern pyramid_engine_config_t pyramid_engine_config;

class monument_pyramid_engine {
public:
    building *chain_head(building *any_part) const;
    void collect_parts(building *any_part, svector<building *, PYRAMID_PARTS_CAPACITY> &out) const;
    int size_variant(building *main) const;
    int block_total(int size_variant) const;
    bool is_mudbrick(building *b) const;
    bool block_phase_active(building *main) const;

    void find_frontier(building *main, svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier);
    void place_block(building_id part_id, figure_id fid);
    int boost_blocks(building *main, int max_count);
    bool needs_main_material(const pyramid_part_state &p) const;

private:
    bool is_mudbrick_type(e_building_type t) const;
    int part_height(const pyramid_part_state &p) const;
    int layer_capacity() const;
    void add_block(pyramid_part_state &p) const;
    int frontier_order(const pyramid_part_state &part, const pyramid_part_state &best) const;
    void apply_block_placed(building *head, pyramid_main_state &ms, pyramid_part_state &ps);
};

extern monument_pyramid_engine g_monument_pyramid_engine;

void pyramid_engine_init_mudbrick(building *main);
void pyramid_engine_start_block_phase(building *main);
bool pyramid_engine_blocks_finished(building *main);

int pyramid_engine_try_assign_bricklayer(building *main, figure_id fid);
bool pyramid_engine_part_has_active_worker(building_id part_id);
void pyramid_engine_place_block(building_id part_id, figure_id fid);
int pyramid_engine_boost_blocks(building *main, int max_count);
void pyramid_engine_find_frontier(building *main, svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier);

building_id pyramid_engine_find_mason_waiting_for_block(building *main);
void pyramid_engine_laborer_deliver_block(figure_id mason_fid);

// Ramp gate stub: always 0 until carpenter thresholds are ported.
int pyramid_engine_part_needs_ramp(building_id part_id);

tile2i pyramid_engine_entry_tile(building *main);
