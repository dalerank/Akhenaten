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
    e_figure_sound attack;
    e_figure_sound click;
};
ANK_CONFIG_STRUCT(figure_sound_kind_t, types, hit, die, attack, click)

struct figure_hunter_shot_sounds_t {
    e_figure_sound central;
    e_figure_sound northern;
    e_figure_sound desert;
};
ANK_CONFIG_STRUCT(figure_hunter_shot_sounds_t, central, northern, desert)

class figure_sound_kinds_t {
public:
    e_figure_sound default_die;
    figure_hunter_shot_sounds_t hunter_shot;
    svector<figure_sound_kind_t, 32> figures;

    void archive_unload();
    void archive_init();
    const figure_sound_kind_t& of(e_figure_type type) const;

private:
    std::array<uint8_t, FIGURE_MAX> kind_of_type;
};

figure_sound_kinds_t& figure_sound_kinds();
