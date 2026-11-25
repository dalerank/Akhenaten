#pragma once

#include "core/vfs/vfs.h"
#include "core/archive.h"
#include "core/svector.h"
#include "core/xstring.h"
#include "figure/figure_type.h"
#include "game/game_events.h"
#include "game/sound_effect.h"

#include <array>
#include <random>

struct sound_figure_group_t {
    e_figure_sound group;
    xstring idle;
    xstring roam;
    xstring attack;
    xstring die;
    xstring run;
};
ANK_CONFIG_STRUCT(sound_figure_group_t, group, idle, roam, attack, die, run)

struct sound_figure_run_t {
    e_figure_sound first;
    uint8_t count;
};
ANK_CONFIG_STRUCT(sound_figure_run_t, first, count)

class sound_figure_t {
public:
    svector<e_figure_type, 96> out_of_view_figures;
    svector<sound_figure_run_t, 4> runs;
    svector<sound_figure_group_t, FIGURE_SOUND_COUNT> groups;

    void archive_unload();
    void archive_init();
    void play(const event_sound_figure& ev);

private:
    struct sample_t {
        xstring file;
        vfs::path resolved;
        bool probed = false;
    };

    e_figure_sound pick_from_run(e_figure_sound group);
    bool heard_out_of_view(e_figure_type type) const;
    const vfs::path& sample_path(sample_t& sample);

    std::array<std::array<sample_t, FIGURE_SOUND_VARIANT_COUNT>, FIGURE_SOUND_COUNT> samples;
    std::minstd_rand rng;
};

sound_figure_t& sound_figure();
