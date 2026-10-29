#pragma once

#include "figure/figure.h"

enum e_cartpusher_action : uint16_t {
    ACTION_0_CARTPUSHER_NONE = 0,
    // OG shared ferry states (carriers.c / walkers.c)
    ACTION_6_CARTPUSHER_ON_FERRY = 6,
    ACTION_7_CARTPUSHER_WAIT_FOR_FERRY = 7,
    // OG industry cart (carriers.c CART_*): 8 handled as ACTION_8_RECALCULATE
    ACTION_9_CARTPUSHER_DELIVERING_TO_WAREHOUSE = 9,
    ACTION_10_CARTPUSHER_DELIVERING_TO_GRANARY = 10,
    ACTION_11_CARTPUSHER_DELIVERING_TO_WORKSHOP = 11,
    ACTION_12_CARTPUSHER_AT_WAREHOUSE = 12,
    ACTION_13_CARTPUSHER_AT_GRANARY = 13,
    ACTION_14_CARTPUSHER_AT_WORKSHOP = 14,
    ACTION_15_CARTPUSHER_RETURNING = 15,
    ACTION_16_CARTPUSHER_DELIVERING_TO_RECRUITER = 16,
    ACTION_17_CARTPUSHER_AT_RECRUITER = 17,
    // Remake spawn / wait entry (kept; OG uses 8 for the same wait)
    ACTION_20_CARTPUSHER_INITIAL = 20,
    // Legacy remake duplicates (mid-flight Akhenaten saves)
    ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE_LEGACY = 21,
    ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY_LEGACY = 22,
    ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP_LEGACY = 23,
    ACTION_24_CARTPUSHER_AT_WAREHOUSE_LEGACY = 24,
    ACTION_25_CARTPUSHER_AT_GRANARY_LEGACY = 25,
    ACTION_26_CARTPUSHER_AT_WORKSHOP_LEGACY = 26,
    ACTION_27_CARTPUSHER_RETURNING_LEGACY = 27,
    // Remake: gold → palace (moved off OG 11/14)
    ACTION_28_CARTPUSHER_DELIVERING_GOLD = 28,
    ACTION_29_CARTPUSHER_UNLOADING_GOLD = 29,

    ACTION_51_CARTPUSHER_DELIVERING_RESOURCE = 51,
    ACTION_53_CARTPUSHER_RETURNING_EMPTY = 53,
    ACTION_54_CARTPUSHER_GETTING_FOOD = 54,
    ACTION_56_CARTPUSHER_RETURNING_WITH_FOOD = 56,
    ACTION_57_CARTPUSHER_GETTING_RESOURCE = 57,

    ACTION_58_CARTPUSHER_MAX
};
using figure_cartpusher_action_tokens_t = token_holder<e_cartpusher_action, ACTION_0_CARTPUSHER_NONE, ACTION_58_CARTPUSHER_MAX>;
extern const figure_cartpusher_action_tokens_t figure_cartpusher_action_tokens;

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
    figure_cartpusher(figure *f) : figure_carrier(f) {
        runtime_data().movement_check_progress = 255;
    }

    virtual figure_cartpusher *dcast_cartpusher() override { return this; }

    struct static_params : public figure_static_params {
        uint8_t wait_on_calculate_destination;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t movement_check_progress;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual bool can_move_by_water() const override;

    void do_deliver(bool storageyard_cart, int action_done, int action_fail);
    void calculate_destination(bool warehouseman);
    static int destination_wait_threshold();

    void determine_deliveryman_destination();
    void determine_granaryman_destination();
    void determine_storageyard_cart_destination();
};
ANK_CONFIG_STRUCT(figure_cartpusher::static_params,
    wait_on_calculate_destination)
