#pragma once

#include "figuretype/figure_entertainer.h"

class figure_senet_player : public figure_entertainer {
public:
    FIGURE_METAINFO(FIGURE_SENET_PLAYER, figure_senet_player)
    figure_senet_player(figure *f) : figure_entertainer(f) {}

    virtual void on_create() override {}
    virtual void update_shows() override;
    virtual svector<e_building_type, 4> allow_venue_types() const override { return {BUILDING_SENET_HOUSE}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_SENET_HOUSE; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};