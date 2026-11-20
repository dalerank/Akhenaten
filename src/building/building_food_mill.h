#pragma once

#include "building/building_storage.h"
#include "building/building_granary.h"
#include "grid/point.h"

// Enhanced Food Mill (PC2): food-only intermediate store with variety count.
class building_food_mill : public building_storage {
public:
    BUILDING_METAINFO(BUILDING_FOOD_MILL, building_food_mill, building_storage)

    virtual building_food_mill *dcast_food_mill() override { return this; }

    struct static_params : public building_static_params {
        uint16_t max_capacity_stored = 1600;
        uint16_t max_per_type = 800;
        uint8_t max_search_distance = 40;
        uint8_t min_workers_percent_for_tasks = 50;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        // [RESOURCE_NONE] = free capacity; food slots hold stock (∥ granary).
        short resource_stored[16];
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_graphic() override;
    virtual void update_day() override;
    virtual void spawn_figure() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void draw_postrender_effects(painter& ctx, vec2i point, tile2i tile, color color_mask) override;

    virtual int amount(e_resource resource) const override;
    virtual bool is_getting(e_resource resource) override;
    virtual int remove_resource(e_resource resource, int amount) override;
    virtual int add_resource(e_resource resource, int amount, bool force) override;
    virtual int freespace() const override;
    virtual int total_stored() const override;

    // Distinct food types with stock > 0 → 0..4 (FM2).
    int food_variety() const;
    bool is_accepting(e_resource resource) const;
    bool is_not_accepting(e_resource resource) const;

    granary_task_status determine_worker_task();
    // Sources: granary / storage yard only (not farms, not other mills).
    granary_getting_result find_storage_for_getting();

private:
    void draw_placeholder(painter &ctx, color color_mask) const;
    int better_getting_source();
};

ANK_CONFIG_STRUCT(building_food_mill::static_params, max_capacity_stored, max_per_type,
                  max_search_distance, min_workers_percent_for_tasks)
