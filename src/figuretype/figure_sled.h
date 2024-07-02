#pragma once

#include "figuretype/figure_cartpusher.h"

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