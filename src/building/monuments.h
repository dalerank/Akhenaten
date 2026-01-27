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
    e_resource resource;
    uint16_t count;
};

struct monument_phase {
    std::array<monument_phase_resource, 6> resources;
};

struct monument {
    e_building_type btype;
    svector<monument_phase, 10> phases;
};

class building_monument : public building_impl {
public:
    building_monument(building &b) : building_impl(b) {}

    building_monument *dcast_monument() override { return this; }

    struct runtime_data_t {
        uint8_t variant;
        uint8_t statue_offset;
        uint8_t temple_complex_upgrades;
        uint8_t resources_pct[RESOURCES_MAX];
        std::array<uint16_t, 5> workers;
        int8_t phase;
        uint8_t upgrades;
    } BUILDING_RUNTIME_DATA_T;

    virtual bool need_workers() const { return false; }
    virtual uint8_t phase() const { return runtime_data().phase; }

    virtual bool deliver_resource(e_resource resource, int amount);
    virtual int needs_resource(e_resource resource, int phase) const;
    virtual int needs_resource(e_resource resource) const;
    virtual bool needs_resources() const;
    virtual int progress();
    virtual void set_phase(int phase);
    virtual int phases() const;
    virtual grid_area get_area();
    virtual int needs_bricklayers(int ph_id) const;
    virtual void add_delivery(int figure_id, int resource_id, int num_loads);
    virtual bool requires_resource(e_resource resource) const;
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
    virtual bool is_unfinished() const;
    virtual bool is_finished() const;
};

enum module_type {
    
};

int building_monument_has_unfinished_monuments();
bool building_monument_has_delivery_for_worker(int figure_id);

int building_monument_resource_in_delivery(building *b, int resource_id);
void building_monument_remove_delivery(int figure_id);
void building_monument_remove_all_deliveries(int monument_id);
int building_monument_get_id(e_building_type type);
void building_monument_finish_monuments();


int building_monument_workers_onsite(building *b, e_figure_type figure_type);

uint32_t map_monuments_get_progress(tile2i tile);
void map_monuments_set_progress(tile2i tile, uint32_t progress);
void map_monuments_clear();

building *city_has_unfinished_monuments();