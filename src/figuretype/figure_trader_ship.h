#pragma once

#include "figuretype/figure_cartpusher.h"
#include "empire/trader_handler.h"
#include "empire/empire_city.h"
#include "grid/point.h"

enum e_trade_ship_rule {
    TRADE_SHIP_NONE = 0,
    TRADE_SHIP_BUYING = 1,
    TRADE_SHIP_SELLING = 2,
};

enum e_trade_ship_action {
    ACTION_110_TRADE_SHIP_CREATED = 110,
    ACTION_111_TRADE_SHIP_GOING_TO_DOCK = 111,
    ACTION_112_TRADE_SHIP_MOORED = 112,
    ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE = 113,
    ACTION_114_TRADE_SHIP_ANCHORED = 114,
    ACTION_115_TRADE_SHIP_LEAVING = 115,
};

struct empire_city;
struct event_trade_ship_arrival { int cid; uint8_t tid; pcstr location; };

class figure_trade_ship : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_TRADE_SHIP, figure_trade_ship)
    figure_trade_ship(figure *f) : figure_carrier(f) {}
    virtual figure_trade_ship *dcast_trade_ship() override { return this; }

    struct static_params : public figure_static_params {
        uint16_t max_capacity;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        empire_trader_handle trader;
        empire_city_handle empire_city;
        uint8_t failed_dock_attempts;
        uint16_t amount_bought;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual void kill() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual void update_day() override;
    virtual xstring action_tip() const override;
    virtual void debug_show_properties() override;
    virtual bvariant get_property(const xstring& domain, const xstring& name) const override;
    virtual empire_city_handle empire_city() const override { return runtime_data().empire_city; } 

    empire_trader_handle empire_trader() const { return runtime_data().trader; }

    bool lost_queue();
    bool done_trading();
    int is_trading() const;
    uint16_t total_bought() const { return runtime_data().amount_bought; }

    int max_capacity() const { return current_params().max_capacity; }
};
ANK_CONFIG_STRUCT(figure_trade_ship::static_params, max_capacity)
