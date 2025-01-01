#pragma once

#include "building/building_wharf.h"

class building_warship_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_WARSHIP_WHARF, building_warship_wharf)
    building_warship_wharf(building &b) : building_wharf(b) {}

    virtual building_warship_wharf *dcast_warship_wharf() override { return this; }

    struct static_params : public buildings::model_t<building_warship_wharf> {
        virtual void load(archive arch) override;
    };

    virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual bool ship_moored() const override;
    virtual void update_month() override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};