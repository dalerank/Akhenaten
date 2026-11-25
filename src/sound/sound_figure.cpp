#include "sound/sound_figure.h"

#include "core/calc.h"
#include "core/log.h"
#include "city/city_figures.h"
#include "core/xvalue.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "graphics/view/view.h"
#include "graphics/view/zoom.h"
#include "sound/sound.h"

#include <algorithm>

enum e_sound_figure_pan {
    SOUND_FIGURE_PAN_RANGE = 128,
    SOUND_FIGURE_PAN_CENTRE = 64,
    SOUND_FIGURE_QUIET_DIVISOR = 4,
};

ANK_CONFIG_STRUCT(sound_figure_t, out_of_view_figures, runs, groups)

sound_figure_t& sound_figure() {
    return xvalue<sound_figure_t>::ref();
}

ANK_DECLARE_CONFIG_ITERATOR(config_load_sound_figure);
void config_load_sound_figure() {
    call_unload_if_exists(sound_figure());
    const bool ok = g_config_arch.r("figure_sounds", sound_figure());
    call_init_if_exists(sound_figure());
    verify_no_crash_var(ok, "Variable not exist in config: %s", "figure_sounds");
}

void ANK_PERMANENT_CALLBACK(event_sound_figure, ev) {
    if (sound_manager().log_event_sources()) {
        logs::info("[event] figure=%d group=%d variant=%d sent from %s:%d", ev.figure_id, ev.group, ev.variant,
          ev.source_file, ev.source_line);
    }
    sound_figure().play(ev);
}

void sound_figure_t::archive_unload() {
    out_of_view_figures.clear();
    runs.clear();
    groups.clear();
    samples = {};
}

void sound_figure_t::archive_init() {
    for (const auto& g : groups) {
        if (g.group <= FIGURE_SOUND_NONE || g.group >= FIGURE_SOUND_COUNT) {
            continue;
        }
        auto& variants = samples[g.group];
        variants[FIGURE_SOUND_VARIANT_IDLE].file = g.idle;
        variants[FIGURE_SOUND_VARIANT_ROAM].file = g.roam;
        variants[FIGURE_SOUND_VARIANT_ATTACK].file = g.attack;
        variants[FIGURE_SOUND_VARIANT_DIE].file = g.die;
        variants[FIGURE_SOUND_VARIANT_RUN].file = g.run;
    }
}

e_figure_sound sound_figure_t::pick_from_run(e_figure_sound group) {
    for (const auto& r : runs) {
        if (r.first == group && r.count > 0) {
            return (e_figure_sound)(group + rng() % r.count);
        }
    }
    return group;
}

bool sound_figure_t::heard_out_of_view(e_figure_type type) const {
    return std::find(out_of_view_figures.begin(), out_of_view_figures.end(), type) != out_of_view_figures.end();
}

const vfs::path& sound_figure_t::sample_path(sample_t& sample) {
    if (!sample.probed) {
        sample.probed = true;
        sample.resolved = sound_manager().audio_file_path(sample.file);
    }
    return sample.resolved;
}

void sound_figure_t::play(const event_sound_figure& ev) {
    if (!game_features::gameopt_sound_effects_enabled.to_bool()) {
        return;
    }
    if (ev.group <= FIGURE_SOUND_NONE || ev.group >= FIGURE_SOUND_COUNT || ev.variant < 0
        || ev.variant >= FIGURE_SOUND_VARIANT_COUNT) {
        return;
    }

    figure* f = figure_get(ev.figure_id);
    if (!f || !f->is_valid()) {
        return;
    }

    const bool log = sound_manager().log_events();
    const e_figure_sound group = pick_from_run((e_figure_sound)ev.group);
    pcstr group_name = e_figure_sound_tokens.name(group);
    pcstr variant_name = e_figure_sound_variant_tokens.name((e_figure_sound_variant)ev.variant);

    const vec2i tile_pixel = g_camera.tile_to_pixel(f->tile) - g_camera.offset;
    const int zoom = (int)g_zoom.get_percentage();
    const vec2i pixel{tile_pixel.x * 100 / zoom + g_camera.offset.x, tile_pixel.y * 100 / zoom + g_camera.offset.y};
    const int width = g_camera.size_pixels.x;
    const int height = g_camera.screen_size.y;
    bool quiet = false;
    if (pixel.x < 0 || pixel.y < 0 || pixel.x > width || pixel.y > height) {
        if (!heard_out_of_view(f->type)) {
            if (log) {
                logs::info("[sound] figure %d %s %s -> out of view", ev.figure_id, group_name, variant_name);
            }
            return;
        }
        quiet = true;
    }

    sample_t& sample = samples[group][ev.variant];
    if (sample.file.empty()) {
        if (log) {
            logs::info("[sound] figure %d %s %s -> silent", ev.figure_id, group_name, variant_name);
        }
        return;
    }

    const vfs::path& path = sample_path(sample);
    const int channel = sound_manager().free_effect_channel(path);
    if (log) {
        logs::info("[sound] figure %d %s %s -> %s channel %d%s", ev.figure_id, group_name, variant_name,
          sample.file.c_str(), channel, quiet ? " quiet" : "");
    }
    if (path.empty() || channel < 0) {
        return;
    }

    const int pan = width > 0 ? pixel.x * SOUND_FIGURE_PAN_RANGE / width : SOUND_FIGURE_PAN_CENTRE;
    const int left = calc_bound((SOUND_FIGURE_PAN_RANGE - pan) * 100 / SOUND_FIGURE_PAN_CENTRE, 0, 100);
    const int right = calc_bound(pan * 100 / SOUND_FIGURE_PAN_CENTRE, 0, 100);
    int volume = calc_bound(game_features::gameopt_sound_effects_volume.to_int(), 0, 100);
    if (quiet) {
        volume /= SOUND_FIGURE_QUIET_DIVISOR;
    }
    sound_manager().play_effect_panned(channel, path, volume, left, right);
}
