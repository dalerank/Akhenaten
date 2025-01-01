#pragma once

#include "building/building_wharf.h"

class building_transport_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_TRANSPORT_WHARF, building_transport_wharf)
    building_transport_wharf(building &b) : building_wharf(b) {}

    virtual building_transport_wharf *dcast_transport_wharf() override { return this; }

    struct static_params : public buildings::model_t<building_transport_wharf> {
        virtual void load(archive arch) override;
    };

    virtual void update_month() override;
    virtual void update_count() const override;
    virtual void spawn_figure() override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};