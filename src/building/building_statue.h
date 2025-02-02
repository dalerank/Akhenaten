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
        
        using inherited::load;
        virtual void load(archive arch) override;
        virtual void planer_setup_preview_graphics(build_planner &planer) const override;
        virtual int planer_setup_building_variant(e_building_type type, tile2i tile, int variant) const override;
        virtual int planer_next_building_variant(e_building_type type, tile2i tile, int variant) const override;
        virtual int planer_setup_orientation(int orientation) const override { return 1; }
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void update_map_orientation(int map_orientation) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual const statue_params_t &statue_params() = 0;
};

class building_small_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_SMALL_STATUE, building_small_statue)
    building_small_statue(building &b) : building_statue(b) {}

    virtual const statue_params_t &statue_params() { return current_params(); }

    using static_params = static_params_t<building_small_statue>;
    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};

class building_medium_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STATUE, building_medium_statue)
    building_medium_statue(building &b) : building_statue(b) {}

    virtual const statue_params_t &statue_params() { return current_params(); }

    using static_params = static_params_t<building_medium_statue>;
    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};

class building_large_statue : public building_statue {
public:
    BUILDING_METAINFO(BUILDING_LARGE_STATUE, building_large_statue)
    building_large_statue(building &b) : building_statue(b) {}

    virtual const statue_params_t &statue_params() { return current_params(); }

    using static_params = static_params_t<building_large_statue>;
    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};
