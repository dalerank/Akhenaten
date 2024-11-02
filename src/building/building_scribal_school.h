#pragma once

#include "building/building.h"

class building_scribal_school : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_SCRIBAL_SCHOOL, building_scribal_school);
    building_scribal_school(building &b) : building_impl(b) {}

    struct static_params : public buildings::model_t<building_scribal_school> {
        using inherited = model_t<building_scribal_school>;

        vec2i papyrus;
        vec2i icon_res;
        vec2i text_res;

        using inherited::load;
        virtual void load(archive arch) override;
    };

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_SCRIBAL_SCHOOL; }
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void update_month() override;
    virtual void on_place_checks() override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};