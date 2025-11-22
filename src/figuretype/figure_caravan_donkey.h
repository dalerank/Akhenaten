#pragma once

#include "figure/figure.h"
#include "empire/empire_city.h"

class figure_caravan_donkey : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TRADE_CARAVAN_DONKEY, figure_caravan_donkey)
    figure_caravan_donkey(figure *f) : figure_impl(f) {}
    figure_caravan_donkey *dcast_caravan_donkey() override { return this; }

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual xstring action_tip() const override;
    virtual bvariant get_property(const xstring& domain, const xstring& name) const override;
    virtual empire_city_handle empire_city() const override;
    virtual sound_key phrase_key() const override;

    figure *head_of_caravan() const;
};