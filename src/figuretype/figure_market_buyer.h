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
    virtual figure_market_buyer* dcast_market_buyer() override { return this; }

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BAZAAR_ACCESS; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;
    virtual xstring action_tip() const override;
    virtual void acquire_attack() override;

    bool take_resource_from_storageyard(building *warehouse);
    int take_food_from_storage(building *market, building *granary);
    int create_delivery_boy(int leader_id);
};

int provide_market_goods(building *market, tile2i tile);
