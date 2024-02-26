#pragma once

#include "figuretype/figure_cartpusher.h"

class figure_sled : public figure_carrier {
public:
    figure_sled(figure *f) : figure_carrier(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual figure_sled *dcast_sled() override { return this; }

    void do_deliver(int action_done);
};