#pragma once

#include "building/building.h"
#include "building/monuments.h"
#include "core/archive.h"
#include "core/hvector.h"
#include "core/svector.h"
#include "core/vec2i.h"
#include "figure/figure.h"
#include "grid/point.h"

#include <array>
#include <cstdint>

enum e_pyramid_limits {
    PYRAMID_PARTS_CAPACITY = 144,
    PYRAMID_SIZE_COUNT = 5,
    PYRAMID_VIEW_COUNT = 4,
    PYRAMID_RING_COUNT = 6,
    PYRAMID_RAMP_KIND_COUNT = 8,
    PYRAMID_RAMP_OFFSET_ROWS = 6,
    PYRAMID_RAMP_BLOCKS_PER_LAYER = 6,
};

// OG pyramid_part_ring — subtype ranges walked by next_on_ring (casing perimeter).
struct pyramid_part_ring {
    int16_t down_first = 0;
    int16_t down_last = 0;
    int16_t up_first = 0;
    int16_t up_last = 0;
};
ANK_CONFIG_STRUCT(pyramid_part_ring, down_first, down_last, up_first, up_last)

enum e_pyramid_part_kind : int {
    PYRAMID_PART_CORNER_TOP = 0,
    PYRAMID_PART_CORNER_LEFT = 1,
    PYRAMID_PART_CORNER_BOTTOM = 2,
    PYRAMID_PART_CORNER_RIGHT = 3,
    PYRAMID_PART_EDGE_TOP_LEFT = 4,
    PYRAMID_PART_EDGE_BOTTOM_LEFT = 5,
    PYRAMID_PART_EDGE_BOTTOM_RIGHT = 6,
    PYRAMID_PART_EDGE_TOP_RIGHT = 7,
    PYRAMID_PART_INNER = 8,
    PYRAMID_PART_KIND_MAX,
};

struct pyramid_ramp_offsets_t {
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_CORNER_TOP{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_CORNER_LEFT{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_CORNER_BOTTOM{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_CORNER_RIGHT{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_EDGE_TOP_LEFT{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_EDGE_BOTTOM_LEFT{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_EDGE_BOTTOM_RIGHT{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_EDGE_TOP_RIGHT{};
    std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> PYRAMID_PART_INNER{};

    const std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> &operator[](int kind) const {
        const std::array<vec2i, PYRAMID_RAMP_OFFSET_ROWS> *rows[PYRAMID_PART_KIND_MAX] = {
            &PYRAMID_PART_CORNER_TOP,
            &PYRAMID_PART_CORNER_LEFT,
            &PYRAMID_PART_CORNER_BOTTOM,
            &PYRAMID_PART_CORNER_RIGHT,
            &PYRAMID_PART_EDGE_TOP_LEFT,
            &PYRAMID_PART_EDGE_BOTTOM_LEFT,
            &PYRAMID_PART_EDGE_BOTTOM_RIGHT,
            &PYRAMID_PART_EDGE_TOP_RIGHT,
            &PYRAMID_PART_INNER,
        };
        if (kind < 0) {
            kind = 0;
        }
        if (kind >= PYRAMID_PART_KIND_MAX) {
            kind = PYRAMID_PART_KIND_MAX - 1;
        }
        return *rows[kind];
    }
};
ANK_CONFIG_STRUCT(pyramid_ramp_offsets_t,
    PYRAMID_PART_CORNER_TOP, PYRAMID_PART_CORNER_LEFT, PYRAMID_PART_CORNER_BOTTOM, PYRAMID_PART_CORNER_RIGHT,
    PYRAMID_PART_EDGE_TOP_LEFT, PYRAMID_PART_EDGE_BOTTOM_LEFT, PYRAMID_PART_EDGE_BOTTOM_RIGHT, PYRAMID_PART_EDGE_TOP_RIGHT,
    PYRAMID_PART_INNER)

struct pyramid_engine_config_t {
    int blocks_per_layer = 6;
    int block_ticks_a = 41;
    int block_ticks_b = 69;
    int casing_ticks = 50;
    // pyramid_part_grid_offsets — grid deltas from main (GRID_LENGTH=228).
    std::array<int32_t, PYRAMID_PARTS_CAPACITY> part_grid_offsets{};

    std::array<int, PYRAMID_SIZE_COUNT * PYRAMID_PARTS_CAPACITY> part_kinds{};

    // OG pyramid_neighbour_offsets[view][3] — flat view*3+slot; ramp-link uses slot 0/1.
    std::array<int32_t, 12> neighbour_offsets{};

    // pyramid_ramp_base — pixel base shift per part kind before ramp_offsets row.
    std::array<vec2i, PYRAMID_RAMP_KIND_COUNT> ramp_base{};
    // pyramid_ramp_offsets[kind][row] — pixel step by height within a layer.
    pyramid_ramp_offsets_t ramp_offsets{};
    // OG pyramid_part_rings[6] — shared across all pyramid sizes.
    hvector<pyramid_part_ring, PYRAMID_RING_COUNT> part_rings;
    // stepped_ramp_offsets[kind*6+row] — sprite xy (x_with_ramp unused until walk).
    pyramid_ramp_offsets_t stepped_ramp_offsets{};
    // stepped_ramp_shift[18] — draw shift by (ramp_image - ramps_base).
    std::array<vec2i, 18> stepped_ramp_shift{};
};
ANK_CONFIG_STRUCT(pyramid_engine_config_t,
    blocks_per_layer, block_ticks_a, block_ticks_b, casing_ticks, part_grid_offsets, part_kinds,
    neighbour_offsets, ramp_base, ramp_offsets, part_rings, stepped_ramp_offsets, stepped_ramp_shift)

extern pyramid_engine_config_t pyramid_engine_config;

// pyramid_ramp_table row — carpenter ramp schedule for one 2×2 part.
struct pyramid_ramp_spec_t {
    uint8_t part = 0;
    uint8_t ramp1_height = 0;
    uint8_t ramp2_height = 0;
    uint8_t ramp1_linked_part = 0;
    uint8_t ramp2_linked_part = 0;
};
ANK_CONFIG_STRUCT(pyramid_ramp_spec_t, part, ramp1_height, ramp2_height, ramp1_linked_part, ramp2_linked_part)

class monument_pyramid_engine {
public:
    building *chain_head(building *any_part) const;
    void collect_parts(building *any_part, svector<building *, PYRAMID_PARTS_CAPACITY> &out) const;
    int size_variant(building *main) const;
    int part_count(building *main) const;
    int block_total(building *main) const;
    bool is_mudbrick(building *b) const;
    bool uses_block_engine(building *b) const;
    e_pyramid_style style_of(building *b) const;
    bool block_phase_active(building *main) const;

    const std::array<int32_t, PYRAMID_PARTS_CAPACITY> &part_grid_offsets() const;
    const vec2i &ramp_offset_at(int kind, int row) const;
    const hvector<pyramid_ramp_spec_t, 48> &ramp_specs_for(building *head) const;

    void offset_to_xy(int off, int &dx, int &dy) const;
    void size_norm_origin(int part_count, int &min_dx, int &min_dy) const;
    int part_height(const pyramid_part_state &p) const;
    int rotated_kind(int kind, int view) const;
    int geometric_kind(tile2i nw, vec2i footprint, tile2i part_tile) const;
    // OG layout kind for subtype (inner-ring edges stay EDGE_*, not INNER).
    int layout_kind(building *head, int subtype) const;
    int ramp_base_image(building &part, int kind, e_pyramid_style style) const;
    void set_ramp_offsets(pyramid_part_state &ps, int kind, e_pyramid_style style) const;

    void find_frontier(building *main, svector<building_id, PYRAMID_PARTS_CAPACITY> &frontier);
    void place_block(building_id part_id, figure_id fid);
    int boost_blocks(building *main, int max_count);
    bool needs_main_material(const pyramid_part_state &p) const;

private:
    bool is_mudbrick_type(e_building_type t) const;
    bool uses_block_engine_type(e_building_type t) const;
    int layer_capacity() const;
    void add_block(pyramid_part_state &p) const;
    int frontier_order(const pyramid_part_state &part, const pyramid_part_state &best) const;
    void apply_block_placed(building *head, pyramid_main_state &ms, pyramid_part_state &ps);
};

extern monument_pyramid_engine g_monument_pyramid_engine;

void pyramid_engine_clear_all();
void pyramid_engine_init(building *main);

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

int pyramid_engine_part_needs_ramp(building_id part_id);

tile2i pyramid_engine_entry_tile(building *main);
