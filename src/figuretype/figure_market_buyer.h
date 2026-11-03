#pragma once

#include "figure/figure.h"

enum e_market_buyer_action {
    ACTION_144_MARKET_BUYER_CREATE = 144,
    ACTION_145_MARKET_BUYER_GOING_TO_STORAGE = 145,
    ACTION_146_MARKET_BUYER_RETURNING = 146,
    ACTION_147_MARKET_BUYER_REROUTING = 147,
    ACTION_150_MARKET_BUYER_ATTACKED = 150,
};

class figure_market_buyer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MARKET_BUYER, figure_market_buyer)
    figure_market_buyer(figure *f) : figure_impl(f) {}
    virtual figure_market_buyer *dcast_market_buyer() override { return this; }

    // OG trip state (Pharaoh FIG_BUYER): shopping list + up to 3 storage visits.
    // Unused when gameplay_change_bazaar_multi_buyers is ON (enhanced single-item trips).
    struct runtime_data_t {
        int8_t resources[4];          // inventory slots, -1 = empty
        uint16_t amounts_bought[4];   // units already taken this trip
        uint8_t storages_visited;
        uint8_t is_food_trip;         // 1 = food list, 0 = goods list
        uint16_t visited_storage_ids[3];
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual int provide_service() override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;
    virtual xstring action_tip() const override;
    virtual void acquire_attack() override;

    bool take_resource_from_storageyard(building *warehouse);
    int take_food_from_storage(building *market, building *granary);
    int create_delivery_boy(int leader_id, int inventory_slot = -1);
    void apply_return_home_spawn_cooldown();

    static bool use_og_trip();
    void init_og_trip(const int8_t items[4], bool food);
    bool og_has_bought() const;
    void og_at_storage();
    void og_return_or_die();
    void og_go_to_storage(int storage_id);
    int og_buy_food_slot(int index, building *storage);
    int og_buy_goods_slot(int index, building *storage);
    void og_next_storage();
};

int provide_market_goods(building *market, tile2i tile);
