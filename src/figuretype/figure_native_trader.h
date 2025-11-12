#pragma once

#include "figuretype/figure_trader.h"
#include "empire/trader_handler.h"

enum e_native_trader_action {
    ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE = 160,
    ACTION_161_NATIVE_TRADER_RETURNING = 161,
    ACTION_162_NATIVE_TRADER_CREATED = 162,
    ACTION_163_NATIVE_TRADER_AT_WAREHOUSE = 163,
};

class figure_native_trader : public figure_trader {
public:
    FIGURE_METAINFO(FIGURE_NATIVE_TRADER, figure_native_trader)
    figure_native_trader(figure *f) : figure_trader(f) {}

    struct runtime_data_t {
        uint16_t amount_bought;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_action() override;

    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual void debug_show_properties() override;

    virtual void buy(int amounts) override { runtime_data().amount_bought += amounts; }
    virtual void sell(int amounts) override { base.resource_amount_full += amounts; }
    virtual uint16_t total_bought() const override { return runtime_data().amount_bought; }
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    empire_trader_handle empire_trader();
};