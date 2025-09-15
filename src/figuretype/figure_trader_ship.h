#pragma once

#include "figuretype/figure_cartpusher.h"
#include "figure/trader.h"
#include "empire/empire_city.h"
#include "grid/point.h"

enum {
    TRADE_SHIP_NONE = 0,
    TRADE_SHIP_BUYING = 1,
    TRADE_SHIP_SELLING = 2,
};

struct empire_city;
struct event_trade_ship_arrival { int cid; int max_traders; pcstr location; };

class figure_trade_ship : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_TRADE_SHIP, figure_trade_ship)
    figure_trade_ship(figure *f) : figure_carrier(f) {}
    virtual figure_trade_ship *dcast_trade_ship() override { return this; }

    struct static_params : public figure_model {
        uint16_t max_capacity;
        virtual void archive_load(archive arch) override;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        empire_trader_handle trader;
        empire_city_handle empire_city;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual void kill() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual const animations_t &anim() const override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_TRADE_SHIP, "barge"}; }
    virtual void update_day() override;
    virtual xstring action_tip() const override;
    virtual void debug_show_properties() override;
    virtual bvariant get_property(const xstring& domain, const xstring& name) const override;
    virtual empire_city_handle empire_city() const override { return runtime_data().empire_city; } 

    empire_trader_handle empire_trader() const { return runtime_data().trader; }

    bool lost_queue();
    bool done_trading();
    int is_trading() const;

    int max_capacity() const { return current_params().max_capacity; }
};
