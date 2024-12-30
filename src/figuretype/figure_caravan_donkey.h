#pragma once

#include "figure/figure.h"

struct empire_city;

class figure_caravan_donkey : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TRADE_CARAVAN_DONKEY, figure_caravan_donkey)
    figure_caravan_donkey(figure *f) : figure_impl(f) {}
    figure_caravan_donkey *dcast_caravan_donkey() override { return this; }

    const empire_city *get_empire_city() const;

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_TRADE_CARAVAN_DONKEY, "donkey"}; }
    virtual void update_animation() override;

    figure *get_head_of_caravan();
};