#pragma once

#include "figure/figure.h"

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
