#pragma once

#include "figuretype/figure_cartpusher.h"

enum e_warehouse_cart_action {
    ACTION_9_WAREHOUSECART_DELIVERING_GOODS = 9,
    ACTION_50_WAREHOUSECART_CREATED = 50,
    ACTION_51_WAREHOUSECART_DELIVERING_RESOURCE = 51,
    ACTION_52_WAREHOUSECART_AT_DELIVERY_BUILDING = 52,
    ACTION_53_WAREHOUSECART_RETURNING_EMPTY = 53,
    ACTION_54_WAREHOUSECART_GETTING_FOOD = 54,
    ACTION_55_WAREHOUSECART_AT_GRANARY_GETTING = 55,
    ACTION_56_WAREHOUSECART_RETURNING_WITH_FOOD = 56,
    ACTION_57_WAREHOUSECART_GETTING_RESOURCE = 57,
    ACTION_58_WAREHOUSECART_AT_WAREHOUSE_GETTING_GOODS = 58,
    ACTION_59_WAREHOUSECART_RETURNING_WITH_RESOURCE = 59,
    ACTION_60_WAREHOUSECART_UNLOADING_AT_HOME = 60,
};

class figure_storageyard_cart : public figure_cartpusher {
public:
    FIGURE_METAINFO(FIGURE_STORAGEYARD_CART, figure_storageyard_cart)
    figure_storageyard_cart(figure *f) : figure_cartpusher(f) {}

    virtual figure_storageyard_cart *dcast_storageyard_cart() override { return this; }

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_NONE; }

    void do_retrieve(int action_done);
};