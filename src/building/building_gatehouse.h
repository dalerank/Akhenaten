#pragma once

#include "building/building.h"

class building_gatehouse : public building_impl {
public:
    building_gatehouse(building &b) : building_impl(b) {}

    struct back_tile_orientation {
        tile2i tile;
        int orientation;
    };

    template<typename T>
    struct static_params_t : public buildings::model_t<T> {
        struct {
            svector<vec2i, 8> main_view_offset;
            svector<vec2i, 8> part_view_offset;
        } ghost;

        virtual void archive_load(archive arch) override {
            arch.r_section("ghost", [this] (archive ghost_arch) {
                ghost.main_view_offset = ghost_arch.r_array_vec2i("main");
                ghost.part_view_offset = ghost_arch.r_array_vec2i("part");
            });
        }

        virtual void planer_ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual void planer_ghost_blocked(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void update_map_orientation(int orientation) override;
        
    static back_tile_orientation second_part_tile(build_planner &planer, tile2i end, int city_orientation);
    static void update_image_set(building &maingate);
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
};

class building_brick_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_BRICK_GATEHOUSE, building_brick_gatehouse, building_gatehouse)

    struct static_params : public static_params_t<self_type> {
    } BUILDING_STATIC_DATA(static_params);;
};

class building_mud_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_MUD_GATEHOUSE, building_mud_gatehouse, building_gatehouse)

    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    struct static_params : public static_params_t<self_type> {
    } BUILDING_STATIC_DATA(static_params);;
};