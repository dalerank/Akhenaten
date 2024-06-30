#pragma once

#include "figure/figure.h"

class figure_missile : public figure_impl {
public:
    figure_missile(figure *f) : figure_impl(f) {}

    virtual void figure_before_action() override;
    virtual void figure_action() override;

    int get_non_citizen_on_tile();
    int get_citizen_on_tile();
    void missile_hit_target(int target_id, int legionary_type);

    static void create(int building_id, tile2i tile, tile2i dst, e_figure_type type);
};

class figure_hunter_arrow : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_HUNTER_ARROW, figure_hunter_arrow)
    figure_hunter_arrow(figure *f) : figure_missile(f) {}
};

class figure_arrow : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_ARROW, figure_arrow)
    figure_arrow(figure *f) : figure_missile(f) {}
};

class figure_spear : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_SPEAR, figure_spear)
    figure_spear(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
};

class figure_javelin : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_JAVELIN, figure_javelin)
    figure_javelin(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
};

class figure_bolt : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_BOLT, figure_bolt)
    figure_bolt(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
};