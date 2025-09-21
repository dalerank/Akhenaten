#pragma once

#include "figure_trader.h"
#include "empire/empire_city.h"
#include "figure/trader.h"

struct event_trade_caravan_arrival { int cid; int max_traders; pcstr location; };

enum e_trade_carava_action {
    ACTION_100_TRADE_CARAVAN_CREATED = 100,
    ACTION_101_TRADE_CARAVAN_ARRIVING = 101,
    ACTION_102_TRADE_CARAVAN_TRADING = 102,
    ACTION_103_TRADE_CARAVAN_LEAVING = 103,
    ACTION_104_TRADE_CARAVAN_RECALC_LEAVING = 104,
};

class figure_trade_caravan : public figure_trader {
public:
    FIGURE_METAINFO(FIGURE_TRADE_CARAVAN, figure_trade_caravan);
    figure_trade_caravan(figure *f) : figure_trader(f) {}

    virtual figure_trade_caravan *dcast_trade_caravan() override { return this; }

    struct runtime_data_t {
        empire_trader_handle trader;
        empire_city_handle empire_city;
    } FIGURE_RUNTIME_DATA_T;

    struct static_params : figure_model {
        int wait_ticks_after_create;
        uint16_t max_capacity;

        virtual void archive_load(archive arch) override;
    } FIGURE_STATIC_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void before_poof() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_TRADE_CARAVAN, "caravan"}; }
    virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual void update_animation() override;
    virtual xstring action_tip() const override;
    virtual void debug_show_properties() override;
    virtual bvariant get_property(const xstring& domain, const xstring& name) const override;

    empire_trader_handle empire_trader() const { return runtime_data().trader; }
    empire_city_handle empire_city() const { return runtime_data().empire_city; }

    void go_to_next_storageyard(tile2i src_tile, int distance_to_entry);
};