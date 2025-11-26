#pragma once

#include "building.h"
#include "game/resource.h"
#include "grid/road_access.h"
#include "grid/grid.h"

#define MONUMENT_FINISHED -1
#define MONUMENT_START 1
#define MARS_OFFERING_FREQUENCY 16

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
};

enum module_type {
    
};

tile2i building_monument_access_point(building *b);
tile2i building_monument_center_point(building *b);
grid_area building_monument_get_area(building *b);
int building_monument_add_module(building *b, int module_type);
bool building_monument_deliver_resource(building *b, e_resource resource, int amount);
int building_monument_has_unfinished_monuments();
void building_monument_set_phase(building *b, int phase);
bool building_monument_is_monument(const building *b);
bool building_monument_type_is_monument(e_building_type type);
bool building_monument_type_is_mini_monument(e_building_type type);
bool building_monument_is_temple_complex(e_building_type type);
bool building_monument_needs_resources(building *b);
int building_monument_progress(building *b);
bool building_monument_has_labour_problems(building *b);
int building_monument_working(e_building_type type);
bool building_monument_requires_resource(e_building_type type, e_resource resource);
bool building_monument_has_required_resources_to_build(e_building_type type);
int building_monument_needs_resource(building *b, e_resource resource);
int building_monument_needs_resources(e_building_type type, e_resource resource, int phase);
int building_monument_needs_bricklayers(e_building_type type, int phase);
bool building_monument_need_bricklayers(const building *b);
bool building_monument_need_stonemason(const building *b);
bool building_monument_need_carpenter(const building *b);
int building_monument_resource_in_delivery(building *b, int resource_id);
void building_monument_remove_delivery(int figure_id);
void building_monument_add_delivery(int monument_id, int figure_id, int resource_id, int num_loads);
bool building_monument_has_delivery_for_worker(int figure_id);
void building_monument_remove_all_deliveries(int monument_id);
int building_monument_get_id(e_building_type type);
int building_monument_upgraded(e_building_type type);
int building_monument_module_type(e_building_type type);
int building_monument_phases(e_building_type building_type);
void building_monument_finish_monuments();
void building_monument_initialize_deliveries();

bool building_monument_need_workers(building *b);
int building_monument_is_construction_halted(building *b);
int building_monument_toggle_construction_halted(building *b);
bool building_monument_is_unfinished(const building *b);
bool building_monument_is_finished(const building *b);

int building_monument_workers_onsite(building *b, e_figure_type figure_type);

int get_monument_part_image(int part, int orientation, int level);
int get_temple_complex_part_image(e_building_type type, int part, int orientation, int level);

uint32_t map_monuments_get_progress(tile2i tile);
void map_monuments_set_progress(tile2i tile, uint32_t progress);
void map_monuments_clear();

building *city_has_unfinished_monuments();