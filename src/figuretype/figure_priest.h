#pragma once

#include "figure/figure.h"
#include "game/gods.h"

class figure_priest : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PRIEST,figure_priest)
    figure_priest(figure *f) : figure_impl(f) {}

    struct god_params : figure_impl::static_params {
        xstring config;
        e_god god;
        svector<e_building_type, 2> temples;
        bool altar_cures_plague;
    };

    struct static_params : figure_impl::static_params {
        svector<xstring, MAX_GODS> god_configs;
        svector<god_params, MAX_GODS> gods;

        void archive_load(archive arch);
    } FIGURE_STATIC_DATA_T;

    virtual void figure_before_action() override;
    virtual int provide_service() override;
    virtual const figure_impl::static_params& params() const override;

    const god_params* god() const;
};
ANK_CONFIG_STRUCT(figure_priest::god_params, god, temples, altar_cures_plague, overlay, animations, sounds)
ANK_CONFIG_STRUCT(figure_priest::static_params, god_configs)
