#pragma once

#include "figure/figure.h"
#include "game/game_pool.h"
#include "core/flat_map.h"

class figure_librarian : public figure_impl {
    using building_ids_set_t = flat_map<building_id, bool, 64>;
    using building_ids_set_pool_t = mission_permanent_memory_pool<building_ids_set_t, 32>;

public:
    FIGURE_METAINFO(FIGURE_LIBRARIAN, figure_librarian)
    figure_librarian(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        building_ids_set_t* serviced_houses;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void on_post_load() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LIBRARY; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    building_ids_set_pool_t &get_building_ids_set_pool();
};