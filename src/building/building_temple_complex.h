#pragma once

#include "building/building.h"
#include "core/svector.h"
#include "grid/point.h"
#include "game/game_pool.h"

enum e_temple_compex_upgrade : uint8_t {
    etc_upgrade_altar = 1 << 0,
    etc_upgrade_oracle = 1 << 1,
};

class building_temple_complex : public building_impl {
    using decoraive_tiles_t = svector<int, 128>;
    using decoraive_tiles_pool_t = mission_permanent_memory_pool<building_temple_complex::decoraive_tiles_t, 2>;

public:
    building_temple_complex(building &b) : building_impl(b) {}

    virtual building_temple_complex *dcast_temple_complex() override { return this; }

    struct preview : building_planer_renderer {
        virtual int setup_orientation(int orientation) const override;
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int update_relative_orientation(build_planner &p, tile2i tile, int global_rotation) const override;
        virtual int update_building_variant(build_planner &planer) const override { return 0; }
    };

    // Static configuration that is populated from configs for each specific complex
    struct base_params_t {
        svector<e_building_type, 4> allowed_altar;
        svector<e_building_type, 4> allowed_oracle;
    };

    struct runtime_data_t {
        uint8_t variant;
        uint8_t temple_complex_upgrades;
        // tiles around the complex that are covered by statues, floor tiles, etc.
        decoraive_tiles_t* decorative_tiles = nullptr;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void update_count() const override;
    virtual void on_post_load() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    bool has_upgrade(e_temple_compex_upgrade a) const { return !!(runtime_data().temple_complex_upgrades & a); }
    void set_upgrade(e_temple_compex_upgrade a) { runtime_data().temple_complex_upgrades |= a; }
    void build_upgrade(e_temple_compex_upgrade a, e_building_type btype);

    building *get_altar() const;
    building *get_oracle() const;
    building *get_upgrade(e_temple_compex_upgrade type) const;

    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
    virtual void update_map_orientation(int orientation) override;

    void map_add_tiles(e_building_type type, tile2i north_tile, int orientation, building_temple_complex::decoraive_tiles_t &tiles_list);

    decoraive_tiles_pool_t &get_decorative_tiles_pool();

    static void map_tiles_add_temple_complex_parts(building *b);
    static int get_temple_complex_part_image(e_building_type type, int part, int orientation, int level);

    virtual const base_params_t &base_params() const = 0;
};

class building_temple_complex_osiris : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_OSIRIS, building_temple_complex_osiris, building_temple_complex)

    struct static_params : public base_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_OSIRIS; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(building_temple_complex_osiris::static_params, allowed_altar, allowed_oracle)

class building_temple_complex_ra : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_RA, building_temple_complex_ra, building_temple_complex)

    struct static_params : public base_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_RA; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(building_temple_complex_ra::static_params, allowed_altar, allowed_oracle)
  
class building_temple_complex_ptah : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_PTAH, building_temple_complex_ptah, building_temple_complex)

    struct static_params : public base_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_PTAH; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(building_temple_complex_ptah::static_params, allowed_altar, allowed_oracle)

class building_temple_complex_seth : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_SETH, building_temple_complex_seth, building_temple_complex)\

    struct static_params : public base_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_SETH; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(building_temple_complex_seth::static_params, allowed_altar, allowed_oracle)

class building_temple_complex_bast : public building_temple_complex {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_BAST, building_temple_complex_bast, building_temple_complex)    

    struct static_params : public base_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual e_overlay get_overlay() const override { return OVERLAY_RELIGION_BAST; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(building_temple_complex_bast::static_params, allowed_altar, allowed_oracle)