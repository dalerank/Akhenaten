#pragma once

#include "grid/point.h"
#include "core/vec2i.h"
#include "building/building_type.h"
#include "building/monuments.h"
#include "building/building.h"

struct painter;

class building_mastaba : public building_impl {
public:
    building_mastaba(building &b) : building_impl(b) {}
    virtual building_mastaba *dcast_mastaba() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place_checks() override;
};

class building_small_mastaba : public building_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA, building_small_mastaba)

    building_small_mastaba(building & b) : building_mastaba(b) {}

    virtual building_small_mastaba *dcast_small_mastaba() override { return this; }

    virtual void on_place(int orientation, int variant) override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void update_count() const override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;

    std::span<uint16_t> active_workers();

    static void ghost_preview(painter &ctx, e_building_type type, vec2i pixel, tile2i start, tile2i end);
};

class building_small_mastaba_part_side : public building_small_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA_SIDE, building_small_mastaba_part_side)
    building_small_mastaba_part_side(building &b) : building_small_mastaba(b) {}
};

class building_small_mastaba_part_wall : public building_small_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA_WALL, building_small_mastaba_part_wall)
    building_small_mastaba_part_wall(building &b) : building_small_mastaba(b) {}
};

class building_small_mastaba_part_entrance : public building_small_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA_ENTRANCE, building_small_mastaba_part_entrance)
    building_small_mastaba_part_entrance(building &b) : building_small_mastaba(b) {}
};

class building_medium_mastaba : public building_mastaba {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MASTABA, building_medium_mastaba)
    building_medium_mastaba(building &b) : building_mastaba(b) {}

    virtual building_medium_mastaba *dcast_medium_mastaba() override { return nullptr; }
};

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end);
void building_small_mastabe_update_images(building *b, int curr_phase);
int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end);
tile2i building_small_mastaba_bricks_waiting_tile(building *b);
int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer);