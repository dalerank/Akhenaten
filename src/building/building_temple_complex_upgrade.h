#pragma once

#include "building/building.h"

class building_temple_complex_upgrade : public building_impl {
public:
    building_temple_complex_upgrade(building &b) : building_impl(b) {}
};

class building_temple_complex_altar : public building_temple_complex_upgrade {
public:
    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
    };


    building_temple_complex_altar(building &b) : building_temple_complex_upgrade(b) {}
    virtual building_temple_complex_altar *dcast_temple_complex_altar() override { return this; }
    virtual void update_map_orientation(int orientation) override;
};

class building_temple_complex_oracle : public building_temple_complex_upgrade {
public:
    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
    };

    building_temple_complex_oracle(building &b) : building_temple_complex_upgrade(b) {}
    virtual building_temple_complex_oracle *dcast_temple_complex_oracle() override { return this; }

    virtual void on_place_checks() override;
    virtual void update_map_orientation(int orientation) override;
};

class building_temple_complex_altar_amon : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_AMON, building_temple_complex_altar_amon, building_temple_complex_altar)
};

class building_temple_complex_oracle_thoth : public building_temple_complex_oracle {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH, building_temple_complex_oracle_thoth, building_temple_complex_oracle)
};

class building_temple_complex_altar_anubis : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, building_temple_complex_altar_anubis, building_temple_complex_altar)
};

class building_temple_complex_oracle_sekhmet : public building_temple_complex_oracle {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET, building_temple_complex_oracle_sekhmet, building_temple_complex_oracle)
};

class building_temple_complex_altar_sebek : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_SEBEK, building_temple_complex_altar_sebek, building_temple_complex_altar)
};

class building_temple_complex_oracle_min : public building_temple_complex_oracle {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE_MIN, building_temple_complex_oracle_min, building_temple_complex_oracle)
};

class building_temple_complex_altar_maat : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_MAAT, building_temple_complex_altar_maat, building_temple_complex_altar)
};

class building_temple_complex_oracle_horus : public building_temple_complex_oracle {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE_HORUS, building_temple_complex_oracle_horus, building_temple_complex_oracle)
};

class building_temple_complex_altar_isis : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_ISIS, building_temple_complex_altar_isis, building_temple_complex_altar)
};

class building_temple_complex_oracle_hathor : public building_temple_complex_oracle {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ORACLE_HATHOR, building_temple_complex_oracle_hathor, building_temple_complex_oracle)
};