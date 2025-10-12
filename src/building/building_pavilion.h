#pragma once

#include "building/building_entertainment.h"

struct pavilion_place_offset {
    struct item {
        e_building_type type = BUILDING_NONE;
        vec2i offset;
        bool main;
    };
    svector<item, 8> items;
}; 
ANK_CONFIG_STRUCT(pavilion_place_offset::item, type, offset, main)
ANK_CONFIG_STRUCT(pavilion_place_offset, items)

struct pavilion_preview_offset {
    vec2i stand, stand_b, stand_e, booth;
    int stand_b_img = 0, stand_e_img = 0;
};
ANK_CONFIG_STRUCT(pavilion_preview_offset, stand, stand_b, stand_e, booth, stand_b_img, stand_e_img);

class building_pavilion : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_PAVILLION, building_pavilion, building_entertainment)

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
    };

    struct static_params : public building_model {
        using inherited = buildings::model_t<building_pavilion>;

        int dancer_tile = 0;
        int booth_tile = 0;
        int musician_tile_s = 0;
        int musician_tile_e = 0;

        pavilion_preview_offset preview_dir[8];
        pavilion_place_offset place_dir[8];

        virtual void planer_ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;

        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    
    virtual void on_create(int orientation) override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual building_pavilion *dcast_pavilion() override { return this; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_PAVILION; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void on_undo() override;
    virtual void update_map_orientation(int map_orientation) override;

    virtual void spawn_figure() override;
};
ANK_CONFIG_STRUCT(building_pavilion::static_params, meta)