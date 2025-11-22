#pragma once

#include "figuretype/figure_entertainer.h"

class figure_musician : public figure_entertainer {
public:
    FIGURE_METAINFO(FIGURE_MUSICIAN, figure_musician)
    figure_musician(figure *f) : figure_entertainer(f) {}
    virtual figure_musician *dcast_musician() override { return this; }

    virtual void on_create() override {}
    virtual void update_shows() override;
    virtual svector<e_building_type, 4> allow_venue_types() const override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BANDSTAND; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};