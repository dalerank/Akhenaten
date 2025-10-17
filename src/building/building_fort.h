#pragma once

#include "building/building.h"
#include "window/window_building_info.h"

struct building_fort_ghost {
    svector<vec2i, 4> main_view_offset;
    svector<vec2i, 4> ground_view_offset;
    svector<vec2i, 32> ground_check_offset;
};
ANK_CONFIG_STRUCT(building_fort_ghost,
    main_view_offset, ground_view_offset, ground_check_offset)

class building_fort : public building_impl {
public:
    building_fort(building &b) : building_impl(b) {}
    virtual building_fort *dcast_fort() override { return this; }

    struct base_params {
        building_fort_ghost ghost;
    };

    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual void ghost_blocked(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const override;
    };

    struct runtime_data_t {
        building_id ground;
        e_formation_id formation_id;
        e_figure_type figure_type;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t verrsion) override;
    virtual void highlight_waypoints() override;

    building_fort_ground* ground() const { return building_get(runtime_data().ground)->dcast_fort_ground(); }
    e_formation_id create_batalion();
};

class building_fort_ground : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FORT_GROUND, building_fort_ground, building_impl)
    virtual building_fort_ground *dcast_fort_ground() override { return this; }
};

class building_fort_charioteers : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_CHARIOTEERS, building_fort_charioteers, building_fort)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_fort_charioteers::static_params, ghost)

class building_fort_archers : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_ARCHERS, building_fort_archers, building_fort)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_fort_archers::static_params, ghost)

class building_fort_infantry : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_INFANTRY, building_fort_infantry, building_fort)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_fort_infantry::static_params, ghost)