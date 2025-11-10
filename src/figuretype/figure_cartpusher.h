#pragma once

#include "figure/figure.h"

enum e_cartpusher_action {
    ACTION_9_CARTPUSHER_DELIVERING_GOODS = 9,
    ACTION_10_CARTPUSHER_DELIVERING_FOOD = 10,
    ACTION_11_CARTPUSHER_DELIVERING_GOLD = 11,
    ACTION_20_CARTPUSHER_INITIAL = 20,
    ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE = 21,
    ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY = 22,
    ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP = 23,
    ACTION_24_CARTPUSHER_AT_WAREHOUSE = 24,
    ACTION_25_CARTPUSHER_AT_GRANARY = 25,
    ACTION_26_CARTPUSHER_AT_WORKSHOP = 26,
    ACTION_27_CARTPUSHER_RETURNING = 27,
};

class figure_carrier : public figure_impl {
public:
    figure_carrier(figure *f) : figure_impl(f) {}

    void load_resource(e_resource resource, int amount);
    void append_resource(e_resource resource, int amount);
    int dump_resource(int amount);
};

class figure_cartpusher : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_CART_PUSHER, figure_cartpusher)
    figure_cartpusher(figure *f) : figure_carrier(f) {}

    virtual figure_cartpusher *dcast_cartpusher() override { return this; }

    struct static_params : public figure_static_params {
        uint8_t wait_on_calculate_destination;
    } FIGURE_STATIC_DATA_T;

    virtual void figure_before_action() override;
    virtual void before_poof() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_CART_PUSHER, "cartpusher"}; }
    virtual e_overlay get_overlay() const override { return OVERLAY_NONE; }
    virtual sound_key phrase_key() const override;
    virtual bool can_move_by_water() const override;

    void do_deliver(bool storageyard_cart, int action_done, int action_fail);
    void calculate_destination(bool warehouseman);

    void determine_deliveryman_destination();
    void determine_granaryman_destination();
    void determine_storageyard_cart_destination();
};
ANK_CONFIG_STRUCT(figure_cartpusher::static_params,
    wait_on_calculate_destination)