#pragma once

#include "building/building.h"

class building_statue : public building_impl {
public:
    building_statue(building &b) : building_impl(b) {}
    virtual building_statue *dcast_statue() override { return this; }

    struct statue_params_t {
        std::vector<image_desc> var;
        int get_image(e_building_type type, int orientation, int variant) const;
    };

    template<class T>
    struct static_params_t : public statue_params_t, public buildings::model_t<T> {
        using inherited = buildings::model_t<T>;
        
        using inherited::archive_load;
        virtual void archive_load(archive arch) override;
        virtual void planer_setup_preview_graphics(build_planner &planer) const override;
        virtual int planer_setup_building_variant(e_building_type type, tile2i tile, int variant) const override;
        virtual int planer_next_building_variant(e_building_type type, tile2i tile, int variant) const override;
        virtual int planer_update_relative_orientation(build_planner &p, tile2i tile, int global_orientation) const override;
        virtual int planer_setup_orientation(int orientation) const override { return 1; }
        virtual int planer_update_building_variant(build_planner &planer) const override;
    };

    struct runtime_data_t {
        uint8_t variant;
        uint8_t statue_offset;
        uint8_t temple_complex_upgrades;
        uint8_t resources_pct[RESOURCES_MAX];
        uint8_t service;
        uint8_t upgrades;
    } BUILDING_RUNTIME_DATA(runtime_data_t);

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void update_map_orientation(int map_orientation) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void add_workers(figure_id fid) override;
    virtual void update_day() override;

    virtual const statue_params_t &statue_params() = 0;

    uint8_t service() const { return runtime_data().service; }
    void set_service(uint8_t v) { runtime_data().service = v; }
};

class building_small_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_SMALL_STATUE, building_small_statue, building_statue)

    virtual const statue_params_t &statue_params() { return current_params(); }

    using static_params = static_params_t<building_small_statue>;
    BUILDING_STATIC_DATA(static_params);
};

class building_medium_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STATUE, building_medium_statue, building_statue)

    virtual const statue_params_t &statue_params() { return current_params(); }

    using static_params = static_params_t<building_medium_statue>;
    BUILDING_STATIC_DATA(static_params);
};

class building_large_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_LARGE_STATUE, building_large_statue, building_statue)

    virtual const statue_params_t &statue_params() { return current_params(); }

    using static_params = static_params_t<building_large_statue>;
    BUILDING_STATIC_DATA(static_params);
};
