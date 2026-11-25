#pragma once

#include "core/archive.h"
#include "core/svector.h"
#include "figure/figure_type.h"
#include "game/sound_effect.h"

#include <array>

struct figure_sound_kind_t {
    svector<e_figure_type, 16> types;
    e_figure_sound hit;
    e_figure_sound die;
};
ANK_CONFIG_STRUCT(figure_sound_kind_t, types, hit, die)

class figure_sound_kinds_t {
public:
    e_figure_sound default_die;
    svector<figure_sound_kind_t, 32> figures;

    void archive_unload();
    void archive_init();
    const figure_sound_kind_t& of(e_figure_type type) const;

private:
    std::array<uint8_t, FIGURE_MAX> kind_of_type;
};

figure_sound_kinds_t& figure_sound_kinds();
