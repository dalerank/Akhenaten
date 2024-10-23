#pragma once

#include "building/building.h"

class building_wharf : public building_impl {
public:
    building_wharf(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_tick(bool refresh_only) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    virtual bool ship_moored() const { return false; }
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

