#pragma once

#include "building/building.h"
#include "window/window_building_info.h"

class building_fort : public building_impl {
public:
    building_fort(building &b) : building_impl(b) {}
    virtual building_fort *dcast_fort() override { return this; }

    template<typename T>
    struct static_params_t : buildings::model_t<T> {
        struct {
            svector<vec2i, 4> main_view_offset;
            svector<vec2i, 4> ground_view_offset;
            svector<vec2i, 32> ground_check_offset;
        } ghost;

        virtual void load(archive arch) override {
            arch.r_section("ghost", [this] (archive ghost_arch) {
                ghost.main_view_offset = ghost_arch.r_array_vec2i("main");
                ghost.ground_view_offset = ghost_arch.r_array_vec2i("ground");
                ghost.ground_check_offset = ghost_arch.r_array_vec2i("ground_check");
            });
        }

        virtual void planer_ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual void planer_ghost_blocked(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t verrsion) override;
    virtual void highlight_waypoints() override;
};

class building_fort_ground : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FORT_GROUND, building_fort_ground)
    building_fort_ground(building &b) : building_impl(b) {}
    virtual building_fort_ground *dcast_fort_ground() { return this; }
};

class building_fort_charioteers : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_CHARIOTEERS, building_fort_charioteers)
    building_fort_charioteers(building &b) : building_fort(b) {}

    using static_params = static_params_t<building_fort_charioteers>;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};

class building_fort_archers : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_ARCHERS, building_fort_archers)
    building_fort_archers(building &b) : building_fort(b) {}

    using static_params = static_params_t<building_fort_archers>;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};

class building_fort_infantry : public building_fort {
public:
    BUILDING_METAINFO(BUILDING_FORT_INFANTRY, building_fort_infantry)
    building_fort_infantry(building &b) : building_fort(b) {}

    using static_params = static_params_t<building_fort_infantry>;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};