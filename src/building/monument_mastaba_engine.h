#pragma once

#include "building/building.h"
#include "building/monuments.h"
#include "core/archive.h"
#include "core/svector.h"
#include "figure/figure.h"
#include "grid/point.h"

enum e_pyramid_walk_mode : uint8_t {
    PYRAMID_WALK_NONE = 0,
    PYRAMID_WALK_ACTIVE = 1,
};

// Compile-time part-list capacity (must cover largest mastaba / future pyramid).
constexpr int MASTABA_PARTS_CAPACITY = 36;

struct monument_engine_config_t {
    int mastaba_max_parts = 36;
    int blocks_per_layer = 6;
    int block_ticks_a = 41;
    int block_ticks_b = 69;
    int casing_ticks = 50;
    int default_bricks_per_block = 100;
};
ANK_CONFIG_STRUCT(monument_engine_config_t,
    mastaba_max_parts, blocks_per_layer,
    block_ticks_a, block_ticks_b, casing_ticks, default_bricks_per_block)

extern monument_engine_config_t monument_engine_config;

// Helpers over building-stored construction state (size geometry lives on mastaba params).
class monument_mastaba_engine {
public:
    pyramid_main_state *main_state(building_id main_id);
    pyramid_part_state *part_state(building_id part_id);
    pyramid_main_state &ensure_main(building_id main_id);
    pyramid_part_state &ensure_part(building_id part_id);

    void clear_building(building_id id);
    void clear_all();

    void find_frontier(building *main, svector<building_id, MASTABA_PARTS_CAPACITY> &frontier);
    void place_block(building_id part_id, figure_id fid);
    // Dev cheat / monument_up: place up to max_count blocks (0 = all remaining).
    int boost_blocks(building *main, int max_count);

private:
    int part_height(const pyramid_part_state &p) const;
    int layer_capacity(const pyramid_part_state &p, bool is_main) const;
    void add_block(pyramid_part_state &p, bool is_main) const;
    int frontier_order(const pyramid_part_state &part, const pyramid_part_state &best) const;
    bool needs_main_material(const pyramid_part_state &p) const;
    void apply_block_placed(building *head, pyramid_main_state &ms, pyramid_part_state &ps);
};

extern monument_mastaba_engine g_monument_mastaba_engine;

building *mastaba_chain_head(building *any_part);
void mastaba_collect_parts(building *any_part, svector<building *, MASTABA_PARTS_CAPACITY> &out);

pyramid_main_state *pyramid_main_state_get(building_id main_id);
pyramid_part_state *pyramid_part_state_get(building_id part_id);
void mastaba_engine_clear_building(building_id id);
void mastaba_engine_clear_all();

bool mastaba_engine_is(building *b);
bool mastaba_engine_block_phase_active(building *main);

void mastaba_engine_init(building *main);
void mastaba_engine_start_block_phase(building *main);
bool mastaba_engine_blocks_finished(building *main);

int mastaba_engine_try_assign_bricklayer(building *main, figure_id fid);
bool mastaba_engine_part_has_active_worker(building_id part_id);
void mastaba_engine_place_block(building_id part_id, figure_id fid);
int mastaba_engine_boost_blocks(building *main, int max_count);
void mastaba_engine_find_frontier(building *main, svector<building_id, MASTABA_PARTS_CAPACITY> &frontier);

building_id mastaba_engine_find_mason_waiting_for_block(building *main);
void mastaba_engine_laborer_deliver_block(figure_id mason_fid);

tile2i mastaba_engine_entry_tile(building *main);
