#pragma once

#include "figure/figure.h"

enum e_market_trader_action {
    ACTION_125_MARKET_TRADER_ROAMING = 125,
    ACTION_126_MARKET_TRADER_RETURNING = 126
};

class figure_market_trader : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MARKET_TRADER, figure_market_trader)
    figure_market_trader(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_roaming_action() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BAZAAR_ACCESS; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
};