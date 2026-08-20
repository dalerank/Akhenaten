#pragma once

#include "building.h"
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

struct monument_phase {
    uint8_t id = 0;
    // Default-init zeros unused slots; archive only overwrites the first N from JS.
    std::array<monument_phase_resource, 6> resources{};
};
ANK_CONFIG_STRUCT(monument_phase, id, resources)

struct monument {
    e_building_type btype = BUILDING_NONE;
    hvector<monument_phase, 16> phases;
};
ANK_CONFIG_STRUCT(monument, phases)

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
        uint16_t lamp_stock;     // royal tomb working stock (≤700); unused elsewhere
        // Burial goods loads at this tomb (BP1 ledger). Fits former bind____skip(36).
        uint8_t burial_stock[RESOURCES_MAX];
    } BUILDING_RUNTIME_DATA_T;

    // Tall monument ornaments (tiers/cones) - skip in flat buildings view.
    virtual bool suppress_ornaments_in_flat_view() const override { return true; }

    virtual bool need_workers() const { return false; }
    virtual uint8_t phase() const { return runtime_data().phase; }

    virtual bool deliver_resource(e_resource resource, int amount);
    virtual int needs_resource(e_resource resource, int phase) const;
    virtual int needs_resource(e_resource resource) const;
    virtual bool needs_resources() const;
    virtual int progress();
    virtual void set_phase(int phase);
    virtual void on_phase_changed(int old, int current);
    virtual int phases() const;
    virtual grid_area get_area() const;
    virtual int needs_bricklayers(int ph_id) const;
    virtual void add_delivery(int figure_id, int resource_id, int num_loads);
    virtual bool requires_resource(e_resource resource) const;
    virtual span_const<uint16_t> active_workers() const;
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
    virtual bool need_workers();
    virtual int is_construction_halted();
    virtual int toggle_construction_halted();
    virtual bool need_stonemason();
    virtual bool need_carpenter();
    virtual bool need_bricklayers();
    virtual bool need_artisan();
    virtual bool is_unfinished() const;
    virtual bool is_finished() const;

    bool has_funeral_done() const;
    void set_funeral_done(bool done = true);

    bool is_preexisting() const;
    void set_preexisting(bool preexisting = true);

    int burial_stock(e_resource r) const;
    int burial_stock_total() const;
    int add_burial_stock(e_resource r, int n);
    bool take_burial_stock(e_resource r, int n);
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

int building_monument_has_unfinished_monuments();
bool building_monument_has_delivery_for_worker(int figure_id);

// Burial tombs (mastaba / pyramid / …) vs non-tomb monuments (sphinx / obelisk / …).
// Shared by the tomb robber and the funeral walker.
bool building_monument_is_non_tomb_type(e_building_type type);
bool building_monument_is_finished_burial_tomb(building &b);

// VALID or MOTHBALLED (halted construction). Not destroyed / deleted.
inline bool building_monument_is_alive(const building &b) {
    return b.type != BUILDING_NONE
        && (b.state == BUILDING_STATE_VALID || b.state == BUILDING_STATE_MOTHBALLED);
}

int building_monument_resource_in_delivery(building *b, int resource_id);
void building_monument_remove_delivery(int figure_id);
void building_monument_remove_all_deliveries(int monument_id);
int building_monument_get_id(e_building_type type);
void building_monument_finish_monuments();


int building_monument_workers_onsite(building *b, e_figure_type figure_type);

uint32_t map_monuments_get_progress(tile2i tile);
void map_monuments_set_progress(tile2i tile, uint32_t progress);
void map_monuments_clear();

// Tile for stonemason work on mastaba/pyramid footprints (2×2 work sites).
tile2i building_monument_mason_waiting_tile(building *b);

building *city_has_unfinished_monuments();