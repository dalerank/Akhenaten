#pragma once

#include "building/building.h"

struct event_temple_complex_updated { building_id bid; };

enum e_temple_compex_upgrade : uint8_t {
    etc_upgrade_altar = 1 << 0,
    etc_upgrade_oracle = 1 << 1,
};

class building_temple_complex : public building_impl {
public:
    building_temple_complex(building &b) : building_impl(b) {}

    virtual building_temple_complex *dcast_temple_complex() override { return this; }

    struct preview : building_planer_renderer {
        virtual int setup_orientation(int orientation) const override;
    };

    template<class T>
    struct static_params_t : public buildings::model_t<T> {
        using inherited = buildings::model_t<T>;

        virtual int planer_update_relative_orientation(build_planner &p, tile2i tile, int global_rotation) const override;
        virtual int planer_update_building_variant(build_planner &planer) const override { return 0; }
        virtual void planer_setup_preview_graphics(build_planner &planer) const override;
    };

    struct runtime_data_t {
        uint8_t variant;
        uint8_t temple_complex_upgrades;
    };

    virtual void on_create(int orientation) override;
    virtual void update_count() const override;
    virtual void on_post_load() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    bool has_upgrade(e_temple_compex_upgrade a) const { return !!(runtime_data().temple_complex_upgrades & a); }
    bool has_upgrade(e_building_type btype) const;
    void set_upgrade(e_temple_compex_upgrade a) { runtime_data().temple_complex_upgrades |= a; }

    building *get_altar() const;
    building *get_oracle() const;
    building *get_upgrade(e_building_type type) const;

    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
    virtual void update_map_orientation(int orientation) override;

    runtime_data_t &runtime_data() { return *(runtime_data_t *)base.runtime_data; }
    const runtime_data_t &runtime_data() const { return *(runtime_data_t *)base.runtime_data; }
};

class building_temple_complex_osiris : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_OSIRIS, building_temple_complex_osiris, building_temple_complex)

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_OSIRIS; }

    using static_params = static_params_t<building_temple_complex_osiris>;
};

class building_temple_complex_ra : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_RA, building_temple_complex_ra, building_temple_complex)

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_RA; }

    using static_params = static_params_t<building_temple_complex_ra>;
};
  
class building_temple_complex_ptah : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_PTAH, building_temple_complex_ptah, building_temple_complex)

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_PTAH; }

    using static_params = static_params_t<building_temple_complex_ptah>;
};

class building_temple_complex_seth : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_SETH, building_temple_complex_seth, building_temple_complex)

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_SETH; }

    using static_params = static_params_t<building_temple_complex_seth>;
};

class building_temple_complex_bast : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_BAST, building_temple_complex_bast, building_temple_complex)    

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_BAST; }

    using static_params = static_params_t<building_temple_complex_bast>;
};