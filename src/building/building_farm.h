#pragma once

#include "building/building.h"

enum e_farm_worker_state {
    FARM_WORKER_TILING,
    FARM_WORKER_SEEDING,
    FARM_WORKER_HARVESTING
};

class building_farm : public building_impl {
public:
    building_farm(building &b) : building_impl(b) {}
    virtual building_farm *dcast_farm() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientration, int variant) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void draw_normal_anim(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual e_sound_channel_city sound_channel() const override;
    virtual void update_count() const override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual void on_undo() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    void deplete_soil();
    void update_tiles_image();
    void spawn_figure_harvests();
    inline bool is_floodplain_farm() const { return building_is_floodplain_farm(base); }

    static void ghost_preview(painter &ctx, e_building_type type, vec2i point, tile2i tile);
    static int get_farm_image(e_building_type type, tile2i tile);
    static void draw_crops(painter &ctx, e_building_type type, int progress, tile2i tile, vec2i point, color color_mask);
    void draw_farm_worker(painter &ctx, int direction, int action, vec2i coords, color color_mask = COLOR_MASK_NONE);
    void draw_workers(painter &ctx, building *b, tile2i tile, vec2i pos);
};

struct building_farm_grain : public building_farm {
    building_farm_grain(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_GRAIN_FARM, building_farm_grain);
};
struct building_farm_lettuce : public building_farm {
    building_farm_lettuce(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_LETTUCE_FARM, building_farm_lettuce);
};
struct building_farm_chickpeas : public building_farm {
    building_farm_chickpeas(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_CHICKPEAS_FARM, building_farm_chickpeas);
};
struct building_farm_pomegranates : public building_farm {
    building_farm_pomegranates(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_POMEGRANATES_FARM, building_farm_pomegranates);
};
struct building_farm_barley : public building_farm {
    building_farm_barley(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_BARLEY_FARM, building_farm_barley);
};
struct building_farm_flax : public building_farm {
    building_farm_flax(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_FLAX_FARM, building_farm_flax);
};
struct building_farm_henna : public building_farm {
    building_farm_henna(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_HENNA_FARM, building_farm_henna);
};
struct building_farm_figs : public building_farm {
    building_farm_figs(building &b) : building_farm(b) {}
    BUILDING_METAINFO(BUILDING_FIGS_FARM, building_farm_figs);
};

bool building_farm_time_to_deliver(bool floodplains, int resource_id = 0);
