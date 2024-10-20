#pragma once

#include "building/building.h"

class building_wharf : public building_impl {
public:
    building_wharf(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
};

class building_transport_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_TRANSPORT_WHARF, building_transport_wharf)
    building_transport_wharf(building &b) : building_wharf(b) {}

    struct static_params : public buildings::model_t<building_transport_wharf> {
        virtual void load(archive arch) override;
    };

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};

