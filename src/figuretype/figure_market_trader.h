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

    virtual void figure_action() override;
    virtual void figure_roaming_action() override;
    virtual int provide_service() override;
};