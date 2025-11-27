#pragma once

#include "figure/figure.h"
#include <unordered_set>

class figure_librarian : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LIBRARIAN, figure_librarian)
    figure_librarian(figure *f) : figure_impl(f) {}

    using building_ids_set = std::unordered_set<building_id>;
    struct runtime_data_t {
        building_ids_set* serviced_houses;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_destroy() override;
    virtual void on_post_load() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LIBRARY; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};