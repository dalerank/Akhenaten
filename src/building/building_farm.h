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

    struct preview : building_planer_renderer {
        int is_blocked(tile2i tile, int size, blocked_tile_vec &blocked_tiles) const;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    struct runtime_data_t : public no_copy_assignment {
        uint8_t worker_frame;
        uint16_t progress;
        uint16_t progress_max;
        uint16_t ready_production;
        figure_id worker_id;
        uint8_t labor_days_left;
        e_labor_state labor_state;
        building_id work_camp_id;
        uint8_t produce_multiplier;
    } BUILDING_RUNTIME_DATA(runtime_data_t);

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
    virtual void start_production() override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;

    short progress() const { return runtime_data().progress; }
    short progress_max() const { return runtime_data().progress_max; }

    void map_building_tiles_add_farm(e_building_type type, int building_id, tile2i tile, int crop_image_offset, int progress);
    void add_tiles();
    static int get_crops_image(e_building_type type, int growth);
    static int get_farm_image(e_building_type type, tile2i tile);
    static void draw_crops(painter &ctx, e_building_type type, int progress, tile2i tile, vec2i point, color color_mask);

    void deplete_soil();
    void update_tiles_image();
    bool is_currently_flooded() const;
    void spawn_figure_harvests();
    inline bool is_floodplain_farm() const { return building_is_floodplain_farm(base); }

    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;

    void draw_farm_worker(painter &ctx, int direction, int action, vec2i coords, color color_mask = COLOR_MASK_NONE);
    void draw_workers(painter &ctx, building *b, tile2i tile, vec2i pos);
    int expected_produce();
};

struct building_farm_grain : public building_farm {
    BUILDING_METAINFO(BUILDING_GRAIN_FARM, building_farm_grain, building_farm);
};

struct building_farm_lettuce : public building_farm {
    BUILDING_METAINFO(BUILDING_LETTUCE_FARM, building_farm_lettuce, building_farm);
};

struct building_farm_chickpeas : public building_farm {
    BUILDING_METAINFO(BUILDING_CHICKPEAS_FARM, building_farm_chickpeas, building_farm);
};

struct building_farm_pomegranates : public building_farm {
    BUILDING_METAINFO(BUILDING_POMEGRANATES_FARM, building_farm_pomegranates, building_farm);
};

struct building_farm_barley : public building_farm {
    BUILDING_METAINFO(BUILDING_BARLEY_FARM, building_farm_barley, building_farm);
};

struct building_farm_flax : public building_farm {
    BUILDING_METAINFO(BUILDING_FLAX_FARM, building_farm_flax, building_farm);
};

struct building_farm_henna : public building_farm {
    BUILDING_METAINFO(BUILDING_HENNA_FARM, building_farm_henna, building_farm);
};

struct building_farm_figs : public building_farm {
    BUILDING_METAINFO(BUILDING_FIGS_FARM, building_farm_figs, building_farm);
};

bool building_farm_time_to_deliver(bool floodplains, int resource_id = 0);
