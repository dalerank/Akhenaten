#pragma once

#include "game/resource.h"
#include "building/building.h"

class building_bazaar : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BAZAAR, building_bazaar, building_impl)
    virtual building_bazaar *dcast_bazaar() override { return this; }

    struct static_params : public building_static_params {
        uint8_t max_search_distance;
        uint8_t fancy_treshold_desirability;
        uint8_t minimal_pick_food_amount;
        std::array<uint16_t, 4> pick_food_below;
        std::array<uint16_t, 4> pick_good_below;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        resource_value inventory[8];
        short pottery_demand;
        short luxurygoods_demand;
        short linen_demand;
        short beer_demand;
        short fetch_inventory_id;
        sbitarray16 market_goods;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MARKET; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    building *get_storage_destination();
    uint16_t get_idx_amount(uint8_t index) const { return runtime_data().inventory[index].value; }
    uint16_t get_resource_amount(e_resource res) const;
    int max_food_stock();
    int max_goods_stock();
    bool idx_accepted(uint8_t index);
    bool res_accepted(e_resource res);
    void toggle_res_accepted(e_resource index);
    void toggle_idx_accepted(uint8_t index);
    void unaccept_all_goods();
    inline int allow_food_types() const { return 4; }
    inline int allow_good_types() const { return 4; }
};
ANK_CONFIG_STRUCT(building_bazaar::static_params, 
                    max_search_distance, fancy_treshold_desirability, minimal_pick_food_amount,
                    pick_food_below, pick_good_below)

