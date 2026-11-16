#pragma once

#include "building.h"
#include "figure/figure_type.h"
#include "game/resource.h"
#include "grid/road_access.h"
#include "grid/grid.h"

#define MONUMENT_FINISHED -1
#define MONUMENT_START 1
#define MARS_OFFERING_FREQUENCY 16

#define ARCHITECTS RESOURCE_NONE

struct monument_phase_resource {
    e_resource resource = RESOURCE_NONE;
    uint16_t count = 0;
};
ANK_CONFIG_STRUCT(monument_phase_resource, resource, count)

struct monument_phase_worker {
    e_figure_type type = FIGURE_NONE;
    uint8_t count = 0;
};
ANK_CONFIG_STRUCT(monument_phase_worker, type, count)

struct monument_phase {
    uint8_t id = 0;
    std::array<monument_phase_resource, 6> resources{};
    uint16_t blocks = 0;
    std::array<monument_phase_worker, 4> workers{};
};
ANK_CONFIG_STRUCT(monument_phase, id, resources, blocks, workers)

struct monument {
    e_building_type btype = BUILDING_NONE;
    hvector<monument_phase, 16> phases;
};
ANK_CONFIG_STRUCT(monument, phases)

// OG mastaba/pyramid block-engine state (saved on the building, v191+).
enum e_pyramid_style : uint8_t {
    PYRAMID_STYLE_NONE = 0,
    PYRAMID_STYLE_MASTABA = 1,
    PYRAMID_STYLE_MUDBRICK = 2,
    PYRAMID_STYLE_TRUE = 3, // true style shares mudbrick block totals
    PYRAMID_STYLE_STEPPED = 4,
    PYRAMID_STYLE_BENT = 5,
    PYRAMID_STYLE_COUNT,
};

enum e_pyramid_part_stage : uint8_t {
    PYRAMID_STAGE_MAIN_MATERIAL = 0,
    PYRAMID_STAGE_CASING = 1,
};

struct pyramid_part_state {
    uint8_t size_variant = 0;
    uint8_t stage = 0;
    uint8_t blocks = 0;
    uint8_t layer = 0;
    uint8_t target_layers = 0;
    uint8_t subtype = 0; // layout index (pyramid_part_grid_offsets)
    uint16_t worker_figure_id = 0;
    // carpenter ramps (save v192+).
    uint8_t ramp1_height = 0;
    uint8_t ramp2_height = 0;
    uint32_t ramp_image_id = 0;
    int16_t ramp_image_x1 = 0;
    int16_t ramp_image_y1 = 0;
    int16_t ramp_image_x2 = 0;
    int16_t ramp_image_y2 = 0;
    // Frame-local: ramp-link (draw this part's ramps on a closer neighbor).
    building_id ramp_link_part_id = 0;
    int32_t ramp_link_draw_x = 0;
    int32_t ramp_link_draw_y = 0;
};

struct pyramid_main_state {
    e_pyramid_style style = PYRAMID_STYLE_NONE;
    uint8_t size_variant = 0;
    uint16_t remaining_blocks = 0;
    uint8_t block_phase_active = 0;
    // Debug: keep carpenter ramp sprites visible (finish does not clear).
    uint8_t force_show_ramps = 0;
};

// OG pyramid_entry_points / mastaba_entry hop: layout subtype + climb height.
struct pyramid_entry_point {
    int16_t part = -1;
    int16_t height = -1;
};
ANK_CONFIG_STRUCT(pyramid_entry_point, part, height)

// pyramid_part_pair_table / mastaba_part_pair_table row — subtypes worked as one block.
struct pyramid_paired_parts {
    int16_t first = -1;
    int16_t second = -1;
};
ANK_CONFIG_STRUCT(pyramid_paired_parts, first, second)

class building_monument : public building_impl {
public:
    using inherited = building_impl;

    building_monument(building &b) : building_impl(b) {}

    building_monument *dcast_monument() override { return this; }

    struct runtime_data_t {
        uint8_t variant;
        uint8_t layer;
        uint8_t resources_pct[RESOURCES_MAX];
        std::array<uint16_t, 5> workers;
        int8_t phase;
        uint8_t upgrades;
        uint16_t alt_image;
        uint8_t stair_index;
        uint8_t funeral_done;  // procession already held for this tomb (main)
        uint8_t preexisting;   // sealed carry-over tomb (no steal)
        uint8_t causeway_length; // complex only: land tiles along strip (save v182+)
        uint8_t causeway_dir;    // 0=N 1=E 2=S 3=W
        uint16_t lamp_stock;     // royal tomb lamp stock (main part); unused elsewhere
        // Burial goods loads at this tomb (BP1 ledger). Fits former bind____skip(36).
        uint8_t burial_stock[RESOURCES_MAX];
        // Ephemeral (not saved): working figure id set each tick; cleared daily.
        uint16_t carpenter_works;
        uint16_t stonemason_works;
        // OG block engine (mastaba); zero for remake tile-progress monuments.
        pyramid_main_state og_main;
        pyramid_part_state og_part;
    } BUILDING_RUNTIME_DATA_T;

    // Tall monument ornaments (tiers/cones) - skip in flat buildings view.
    virtual bool suppress_ornaments_in_flat_view() const override { return true; }

    virtual bool need_workers() const;
    bool has_free_worker_slot() const;
    virtual uint8_t phase() const { return runtime_data().phase; }

    virtual bool deliver_resource(e_resource resource, int amount);
    virtual int needs_resource(e_resource resource, int phase) const;
    virtual int needs_resource(e_resource resource) const;
    // Material still to deliver until the monument is finished (OG monuments_unplaced_resource_need, placed slot).
    int remaining_resource_need(e_resource resource) const;
    virtual bool needs_resources() const;
    virtual int progress();
    virtual void set_phase(int phase);
    virtual void on_phase_changed(int old, int current);
    virtual void sync_visuals() {}
    virtual int phases() const;
    virtual grid_area get_area() const;
    virtual int needs_bricklayers(int ph_id) const;
    int phase_blocks(int ph_id) const;
    int brick_blocks_total() const;
    int phase_worker_count(int ph_id, e_figure_type type) const;
    int phase_bricks_per_block(int ph_id) const;
    int phase_for_blocks_done(int blocks_done) const;
    virtual bool requires_resource(e_resource resource) const;
    virtual span_const<uint16_t> active_workers() const;
    int workers_assigned() const;
    int workers_slots() const;
    int workers_onsite(e_figure_type figure_type) const;
    int resource_pct(e_resource resource) const;
    int material_pct_min() const;
    virtual int building_image_get() const { return 0; }
    virtual void set_tile_progress(tile2i tile, int v);

    bool has_labour_problems() const;

    virtual bool has_required_resources_to_build() const;
    virtual tile2i center_point() const = 0;
    virtual tile2i access_point() const = 0;
    virtual const monument &config() const = 0;
    virtual int upgraded();
    virtual int working();
    virtual int module_type();
    virtual int is_construction_halted();
    virtual int toggle_construction_halted();
    virtual bool need_stonemason();
    virtual bool need_carpenter();
    virtual bool need_bricklayers();
    // OG block engines: claim a frontier part for this figure (0 = none).
    virtual int try_assign_bricklayer(figure_id /*fid*/) { return 0; }
    virtual void place_bricklayer_block(figure_id /*fid*/) {}
    virtual bool need_artisan();
    // OG artisans guild: a trip carries one load of clay (tomb plaster stage) or of paint (painting stage).
    virtual bool need_artisan_with(e_resource material);
    virtual bool is_unfinished() const;
    virtual bool is_finished() const;
    virtual xstring demolish_blocked_message() const override;

    bool has_funeral_done() const;
    void set_funeral_done(bool done = true);

    bool is_preexisting() const;
    void set_preexisting(bool preexisting = true);

    int burial_stock(e_resource r) const;
    int burial_stock_total() const;
    int add_burial_stock(e_resource r, int n);
    bool take_burial_stock(e_resource r, int n);

    // Save v196+ layout of the OG block-engine monuments (pyramids, mastabas).
    // alt_image_base: first image alt_image is chosen from (0 when the type has none).
    void bind_block_engine_state(io_buffer* iob, int alt_image_base);
};

// City required/dispatched stay UI/win SoT; tomb burial_stock is the steal ledger.
building *burial_provisions_pick_dispatch_tomb();
int burial_provisions_tomb_stock_total(e_resource r);
void burial_provisions_sync_city_dispatched();
// Old saves / test force_dispatched: city pool with empty tomb ledgers → deposit.
void burial_provisions_migrate_city_pool_to_tombs();

ANK_CONFIG_PROPERTY(building_monument::runtime_data_t, variant)

enum module_type {

};

// Is a monument of one of these types still under construction? The one-at-a-time placement
// rules all ask this, and they used to ask it through seven near-identical copies of the same
// scan. The two flags are where those copies actually differed:
//   main_parts_only    -- skip linked parts, for monuments whose parts do not share a phase
//   include_just_placed -- also see a monument placed in this very frame, still CREATED rather
//                          than VALID, so a second placement in the same frame is caught
bool building_monument_has_unfinished(std::initializer_list<e_building_type> types,
  bool main_parts_only = false, bool include_just_placed = false);

// Burial tombs (mastaba / pyramid / …) vs non-tomb monuments (sphinx / obelisk / …).
// Shared by the tomb robber and the funeral walker.
bool building_monument_is_non_tomb_type(e_building_type type);
bool building_monument_is_finished_burial_tomb(building &b);

// VALID or MOTHBALLED (halted construction). Not destroyed / deleted.
inline bool building_monument_is_alive(const building &b) {
    return b.type != BUILDING_NONE
        && (b.state == BUILDING_STATE_VALID || b.state == BUILDING_STATE_MOTHBALLED);
}

int building_monument_get_id(e_building_type type);
void building_monument_finish_monuments();


int building_monument_workers_onsite(building *b, e_figure_type figure_type);
int building_monument_find_bricklayer_task(figure_id fid);

uint32_t map_monuments_get_progress(tile2i tile);
void map_monuments_set_progress(tile2i tile, uint32_t progress);
void map_monuments_clear();

// Tile for stonemason work on mastaba/pyramid footprints (2×2 work sites).
tile2i building_monument_mason_waiting_tile(building *b);
