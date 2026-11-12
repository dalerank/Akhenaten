#pragma once

#include "game/resource.h"
#include "building/building.h"

enum e_bazaar_fetch_group {
    e_bazaar_fetch_all = 0,
    e_bazaar_fetch_foods = 1,
    e_bazaar_fetch_goods = 2,
};

class building_bazaar : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BAZAAR, building_bazaar, building_impl)
    virtual building_bazaar *dcast_bazaar() override { return this; }

    struct static_params : public building_static_params {
        uint8_t max_search_distance;
        uint8_t fancy_treshold_desirability;
        uint8_t minimal_pick_food_amount;
        uint8_t max_buyers;
        uint8_t food_variety_target; // Slice B: prefer foods until this many food slots stocked
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
        // FM3: per-bazaar variety orders (flag ON). Seeded from food_variety_target.
        uint8_t desired_variety;
        uint8_t min_variety;
        // OG: second roaming trader while desirability > fancy threshold (not a figure slot).
        int16_t second_trader_id;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void update_month() override;
    void sync_inventory_types();
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MARKET; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_sprite_anims() override;
    const animation_t& work_anim() const;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    void maintain_fancy_second_trader();
    void update_good_demands_from_houses(int radius = 10);
    int16_t second_trader_id() const { return runtime_data().second_trader_id; }

    building *get_storage_destination(e_bazaar_fetch_group group = e_bazaar_fetch_all,
                                      const bool *exclude = nullptr,
                                      bool tick_demand = true);

    building *get_og_food_destination(int8_t items[4]);
    building *get_og_goods_destination(int8_t items[4]);
    // Refresh nearest storage ids for an in-progress OG buyer (demand countdown like OG).
    void update_og_buyer_storages(int nearest_out[INVENTORY_MAX]);
    int effective_max_buyers() const;
    int count_market_buyers() const;
    e_building_slot free_market_buyer_slot() const;
    void collect_buyer_busy_state(bool *exclude, bool *has_food_buyer, bool *has_good_buyer) const;
    building *pick_next_buyer_destination();
    void reclaim_inactive_buyer_slot(e_building_slot slot);
    void force_clear_buyer_slot(e_building_slot slot);
    void tick_good_demands();
    static bool is_active_market_buyer(figure *f);

    uint16_t get_idx_amount(uint8_t index) const { return runtime_data().inventory[index].value; }
    uint16_t get_resource_amount(e_resource res) const;
    int max_food_stock();
    int max_goods_stock();
    int food_types_in_inventory() const;
    bool needs_food_variety() const;
    bool waiting_for_mill_variety() const;
    uint8_t desired_variety() const;
    uint8_t min_variety() const;
    void set_desired_variety(uint8_t value);
    void set_min_variety(uint8_t value);
    bool idx_accepted(uint8_t index) const;
    bool res_accepted(e_resource res) const;
    void toggle_res_accepted(e_resource index);
    void toggle_idx_accepted(uint8_t index);
    void unaccept_all_goods();
    inline int allow_food_types() const { return 4; }
    inline int allow_good_types() const { return 4; }
};
ANK_CONFIG_PROPERTY(building_bazaar::runtime_data_t, pottery_demand)
ANK_CONFIG_STRUCT(building_bazaar::static_params,
                    max_search_distance, fancy_treshold_desirability, minimal_pick_food_amount,
                    max_buyers, food_variety_target, pick_food_below, pick_good_below)
