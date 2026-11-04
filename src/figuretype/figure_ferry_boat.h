#pragma once

#include "figure/figure.h"

enum e_ferry_boat_action : uint16_t {
    ACTION_0_FERRY_BOAT_CREATED = 0,
    ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION = 1, // OG 9 — cross to partner
    ACTION_2_FERRY_BOAT_AT_DESTINATION = 2,       // OG 14 — unload at partner
    ACTION_3_FERRY_BOAT_RETURNING = 3,            // OG 10 — cross home
    ACTION_4_FERRY_BOAT_WAITING = 4,              // OG 11 — wait/load at home
    ACTION_5_FERRY_BOAT_UNLOAD_HOME = 5,          // OG 12 — unload at home
    ACTION_6_FERRY_BOAT_LOAD_AWAY = 6,            // OG 13 — load at partner, then return

    ACTION_7_FERRY_BOAT_MAX
};
using e_ferry_boat_action_tokens_t = token_holder<e_ferry_boat_action, ACTION_0_FERRY_BOAT_CREATED, ACTION_7_FERRY_BOAT_MAX>;
extern const e_ferry_boat_action_tokens_t e_ferry_boat_action_tokens;

struct event_ferry_boat_goto {
    figure_id fid = 0;
    tile2i destination;
};

class building_ferry;

class figure_ferry_boat : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FERRY_BOAT, figure_ferry_boat)
    figure_ferry_boat(figure *f) : figure_impl(f) {}
    virtual figure_ferry_boat *dcast_ferry_boat() override { return this; }

    static constexpr int PASSENGER_SLOTS = 4;

    // OG boats.h: BOAT_SINKING_TICKS / BOAT_BUBBLES_FRAMES / FERRY_SLOWNESS_* / FERRY_TICK_COUNTER_LIMIT
    struct static_params : public figure_static_params {
        uint16_t sinking_ticks;
        uint16_t bubbles_frames;
        uint8_t slowness_min;
        uint8_t slowness_step;
        uint16_t tick_counter_limit;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        building_id destination_ferry_id;
        tile2i destination_tile;
        figure_id passengers[PASSENGER_SLOTS];
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual bool window_info_background(object_info &ctx) override;
    virtual void update_animation() override;
    virtual bool can_move_by_water() const override { return true; }

    bool is_idle_at_dock() const;
    bool is_crossing() const;
    void order_goto(tile2i destination);

    int passenger_count() const;
    void load_passengers(building_ferry *landing, int max);
    void unload_passengers(building_ferry *landing);

    void sink();
    // OG ferry_move — public for integral tests.
    void move_with_staff_slowness(building *home_ferry);

private:
    void kill_aboard_passengers();
};

ANK_CONFIG_STRUCT(figure_ferry_boat::static_params,
    sinking_ticks, bubbles_frames, slowness_min, slowness_step, tick_counter_limit)
