#pragma once

#include "figure/figure.h"

enum e_ferry_boat_action : uint16_t {
    ACTION_200_FERRY_BOAT_CREATED = 200,
    ACTION_201_FERRY_BOAT_GOING_TO_DESTINATION = 201,
    ACTION_202_FERRY_BOAT_AT_DESTINATION = 202,
    ACTION_203_FERRY_BOAT_RETURNING = 203,
    ACTION_204_FERRY_BOAT_WAITING = 204,
};

class figure_ferry_boat : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FERRY_BOAT, figure_ferry_boat)
    figure_ferry_boat(figure *f) : figure_impl(f) {}
    virtual figure_ferry_boat *dcast_ferry_boat() override { return this; }

    struct runtime_data_t {
        building_id destination_ferry_id;
        tile2i destination_tile;     
        int wait_ticks_at_destination;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual sound_key phrase_key() const override;
    virtual bool window_info_background(object_info &ctx) override;
    virtual void update_animation() override;
    virtual bool can_move_by_water() const override { return true; }

private:
    building* find_destination_ferry();
    void update_destination();
};

