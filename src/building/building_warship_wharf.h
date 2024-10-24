#pragma once

#include "building/building_wharf.h"

class building_warship_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_WARSHIP_WHARF, building_warship_wharf)
    building_warship_wharf(building &b) : building_wharf(b) {}

    struct static_params : public buildings::model_t<building_warship_wharf> {
        virtual void load(archive arch) override;
    };

    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_map_orientation(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual bool ship_moored() const override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};