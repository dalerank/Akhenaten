#pragma once

#include "building/building.h"

enum e_temple_compex_attachement : uint8_t {
    etc_attachement_altar = 1 << 0,
    etc_attachement_oracle = 1 << 1,
};

class building_temple_complex : public building_impl {
public:
    building_temple_complex(building &b) : building_impl(b) {}

    virtual building_temple_complex *dcast_temple_complex() override { return this; }

    template<class T>
    struct static_params_t : public buildings::model_t<T> {
        using inherited = buildings::model_t<T>;

        using inherited::load;
        virtual void load(archive arch) override;
        virtual int planer_setup_orientation(int orientation) const override;
        virtual int planer_update_relative_orientation(build_planner &p, int global_rotation) const override;
        virtual int planer_update_building_variant(build_planner &planer) const override { return 0; }
        virtual void planer_setup_preview_graphics(build_planner &planer) const override;
    };

    virtual void on_create(int orientation) override;
    virtual void update_count() const override;
    virtual void on_post_load() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    bool has_attachement(e_temple_compex_attachement a) const { return !!(data.monuments.temple_complex_attachments & a); }
    void set_attachement(e_temple_compex_attachement a) { data.monuments.temple_complex_attachments |= a; }

    building *get_altar() const;
    building *get_oracle() const;

    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
};

class building_temple_complex_upgrade : public building_impl {
public:
    building_temple_complex_upgrade(building &b) : building_impl(b) {}

    template<typename T>
    struct static_params_t : public buildings::model_t<T> {
        virtual void planer_ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };
};

class building_temple_complex_altar : public building_temple_complex_upgrade {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR, building_temple_complex_altar)
    building_temple_complex_altar(building &b) : building_temple_complex_upgrade(b) {}

    using static_params = static_params_t<building_temple_complex_altar>;

    virtual building_temple_complex_altar *dcast_temple_complex_altar() override { return this; }
};

class building_temple_complex_oracle : public building_temple_complex_upgrade {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE, building_temple_complex_oracle)
    building_temple_complex_oracle(building &b) : building_temple_complex_upgrade(b) {}

    using static_params = static_params_t<building_temple_complex_oracle>;

    virtual building_temple_complex_oracle *dcast_temple_complex_oracle() override { return this; }
};

class building_temple_complex_osiris : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_OSIRIS, building_temple_complex_osiris)
    building_temple_complex_osiris(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_OSIRIS; }

    using static_params = static_params_t<building_temple_complex_osiris>;
};

class building_temple_complex_ra : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_RA, building_temple_complex_ra)
    building_temple_complex_ra(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_RA; }

    using static_params = static_params_t<building_temple_complex_ra>;
};
  
class building_temple_complex_ptah : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_PTAH, building_temple_complex_ptah)
    building_temple_complex_ptah(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_PTAH; }

    using static_params = static_params_t<building_temple_complex_ptah>;
};

class building_temple_complex_seth : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_SETH, building_temple_complex_seth)
    building_temple_complex_seth(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_SETH; }

    using static_params = static_params_t<building_temple_complex_seth>;
};

class building_temple_complex_bast : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_BAST, building_temple_complex_bast)
    building_temple_complex_bast(building &b) : building_temple_complex(b) {}

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_BAST; }

    using static_params = static_params_t<building_temple_complex_bast>;
};