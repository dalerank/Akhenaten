#pragma once

#include "figure/figure.h"

class figure_librarian : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LIBRARIAN, figure_librarian)
    figure_librarian(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LIBRARY; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};