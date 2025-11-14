#pragma once

#include "figuretype/figure_cartpusher.h"

enum e_sled_action {
    ACTION_11_SLED_RETURNING_EMPTY = 11,
    ACTION_50_SLED_CREATED = 50,
    ACTION_51_SLED_DELIVERING_RESOURCE = 51,
    ACTION_52_SLED_AT_DELIVERY_BUILDING = 52,
    ACTION_50_SLED_PULLER_CREATED = 50,
    ACTION_51_SLED_PULLER_DELIVERING_RESOURCE = 51,
    ACTION_52_SLED_PULLER_AT_DELIVERY_BUILDING = 52,
    ACTION_53_SLED_PULLER_DESTROY = 53,
    ACTION_54_SLED_PULLER_WAITING_FOR_DESTROY = 54,
};

class figure_sled : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_SLED, figure_sled)
    figure_sled(figure *f) : figure_carrier(f) {}

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual figure_sled *dcast_sled() override { return this; }

    void do_deliver(int action_done);
};

class figure_sled_puller : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SLED_PULLER, figure_sled_puller)
    figure_sled_puller(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    //virtual void update_animation() override;
};