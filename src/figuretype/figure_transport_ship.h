#pragma once

#include "figure/figure.h"

enum e_transport_ship_action {
    ACTION_210_TRANSPORT_SHIP_RESERVED = 210,
    ACTION_211_TRANSPORT_SHIP_CREATED = 211,
    ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF = 212,
    ACTION_213_TRANSPORT_SHIP_MOORED = 213,
    ACTION_214_TRANSPORT_SHIP_ANCHORED = 214,
    ACTION_215_TRANSPORT_SHIP_LEAVING = 215,
};

class figure_transport_ship : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TRANSPORT_SHIP, figure_transport_ship)
    figure_transport_ship(figure *f) : figure_impl(f) {}

    virtual figure_transport_ship *dcast_transport_ship() override { return this; }
    
    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void before_poof() override;
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void kill() override;
    virtual sound_key phrase_key() const override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override { return {}; }
    virtual void update_animation() override;
};
