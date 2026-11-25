#include "sound_city.h"
#include "city/city_figures.h"
#include "city/city_population.h"
#include "core/svector.h"
#include "core/main_thread.h"
#include "core/xvalue.h"

#include "game/game_config.h"

#include "building/building_house.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/log.h"
#include "core/profiler.h"
#include "graphics/view/view.h"
#include "grid/terrain.h"
#include "sound/channel.h"
#include "game/game_events.h"
#include "scenario/scenario.h"
#include "building/building_static_params.h"
#include "sound/sound.h"
#include "js/js_register.h"

#include <assert.h>
#include <string.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <string>
#include <vector>

// OG savegame city_sounds chunk holds 70 channels (8960 bytes); later channels are runtime-only.
#define MAX_CHANNELS                ((int)std::tuple_size<decltype(city_sounds_t::channels)>::value)

sound_city_t& sound_city() {
    return xvalue<sound_city_t>::ref();
}

void sound_city_t::clear_names() {
    sounds.names.fill(xstring());
    sounds.building_channels.fill(-1);
}

void sound_city_t::set_name(int channel, xstring id) {
    const int index = channel - SOUND_CHANNEL_CITY_MIN;
    if (index < 0 || index >= MAX_CHANNELS) {
        return;
    }
    sounds.names[index] = id;
}

int sound_city_t::channel(const xstring& id) const {
    if (id.empty()) {
        return 0;
    }
    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (sounds.names[i] == id) {
            return SOUND_CHANNEL_CITY_MIN + i;
        }
    }
    return 0;
}

// OG city_view.c is_silent_venue: quiet while enemies are in the city or when unstaffed.
static bool is_silent_venue(e_building_type type) {
    return type == BUILDING_BANDSTAND || type == BUILDING_BOOTH || type == BUILDING_SENET_HOUSE
           || type == BUILDING_PAVILLION || type == BUILDING_ZOO;
}

static void sound_city_subscribe_events() {
    sound_city().init();
    events::subscribe([](event_level_post_load) { sound_city().init(); });
}
static events::session_subscriber g_sound_city_session(&sound_city_subscribe_events);

void sound_city_t::init() {
    auto& channels = sounds.channels;
    sounds.last_update_time = time_get_millis();
    memset(channels.data(), 0, channels.size() * sizeof(city_sound_channel));

    int i = SOUND_CHANNEL_CITY_MIN;
    for (auto &channel: channels) {
        channel.in_use = 1;
        channel.views_threshold = 200;
        channel.delay_millis = 30000;
        channel.last_played_time = 35000;
        channel.channel = i++;
    }
}

void sound_city_t::stop() {
    sound_manager().stop_city_channels();
}

int sound_city_t::building_type_channel(building* b) {
    if (b->type == BUILDING_HOUSE_CRUDE_HUT) {
        auto house = b->dcast_house();
        if (house && house->house_population() <= 0) {
            return 0;
        }
    }

    int16_t& channel = sounds.building_channels[b->type];
    if (channel < 0) {
        channel = (int16_t)this->channel(building_static_params::get(b->type).city_sound);
    }
    return channel;
}

void sound_city_t::add_channel(int system_channel_index, int direction) {
    main_thread::check("sound_city_add_channel");
    if (!system_channel_index) {
        return;
    }
    auto& slot = sounds.channels[system_channel_index - SOUND_CHANNEL_CITY_MIN];
    slot.available = 1;
    ++slot.total_views;
    ++slot.direction_views[direction];
}

struct terrain_sound_t {
    int terrain;
    xstring sound;
    int channel = -1;
};
ANK_CONFIG_STRUCT(terrain_sound_t, terrain, sound)
svector<terrain_sound_t, 16> ANK_VARIABLE(terrain_sounds);

void sound_city_t::mark_terrain_view(int terrain, int grid_offset, int direction) {
    for (auto& t : terrain_sounds) {
        if (terrain & t.terrain) {
            if (t.channel < 0) {
                t.channel = this->channel(t.sound);
            }
            add_channel(t.channel, direction);
            return;
        }
    }
}

int sound_city_t::building_channel(building* b) {
    if (b->state != BUILDING_STATE_VALID) {
        return 0;
    }

    e_building_type type = b->type;
    verify_no_crash(type <= BUILDING_MAX);
    if (is_silent_venue(type) && (city_figures().enemies > 0 || b->num_workers < 1)) {
        return 0;
    }
    return building_type_channel(b);
}

struct zoo_ambient_band_t {
    int min_population;
    xstring sound;
    int channel = -1;
};
ANK_CONFIG_STRUCT(zoo_ambient_band_t, min_population, sound)
svector<zoo_ambient_band_t, 8> ANK_VARIABLE(zoo_ambient_bands);

int sound_city_t::zoo_ambient_channel() {
    const int population = city_population().current;
    int channel = 0;
    for (auto& band : zoo_ambient_bands) {
        if (population >= band.min_population) {
            if (band.channel < 0) {
                band.channel = this->channel(band.sound);
            }
            channel = band.channel;
        }
    }
    return channel;
}

void sound_city_t::mark_building_view(building* b, int direction) {
    OZZY_PROFILER_FUNCTION()

    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_ZOO) {
        add_channel(zoo_ambient_channel(), direction);
    }

    const int system_channel_index = building_channel(b);
    add_channel(system_channel_index, direction);
}

void sound_city_t::decay_views() {
    auto& channels = sounds.channels;

    for (int i = 0; i < MAX_CHANNELS; i++) {
        for (int d = 0; d < 5; d++)
            channels[i].direction_views[d] = 0;
        channels[i].total_views /= 2;
    }
}

static void sound_city_play_channel(int channel, int direction) {
    if (!game_features::gameopt_sound_city_enabled.to_bool()) {
        return;
    }

    if (sound_manager().is_channel_playing(channel)) {
        return;
    }

    int left_pan;
    int right_pan;
    switch (direction) {
    case SOUND_DIRECTION_CENTER:
        left_pan = right_pan = 100;
        break;

    case SOUND_DIRECTION_LEFT:
        left_pan = 100;
        right_pan = 0;
        break;

    case SOUND_DIRECTION_RIGHT:
        left_pan = 0;
        right_pan = 100;
        break;

    default:
        left_pan = right_pan = 0;
        break;
    }

    sound_manager().play_channel_panned(channel, game_features::gameopt_sound_city_volume.to_int(), left_pan,
      right_pan);
}

void sound_city_t::play() {
    if (ambient_play()) {
        return;
    }

    auto& channels = sounds.channels;
    time_millis now = time_get_millis();
    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels[i].should_play = 0;
        if (channels[i].available) {
            channels[i].available = 0;
            if (channels[i].total_views >= channels[i].views_threshold) {
                if (now - channels[i].last_played_time >= channels[i].delay_millis)
                    channels[i].should_play = 1;
            }
        } else {
            channels[i].total_views = 0;
            for (int d = 0; d < 5; d++) {
                channels[i].direction_views[d] = 0;
            }
        }
    }

    if (now - sounds.last_update_time < 2000) {
        // Only play 1 sound every 2 seconds
        return;
    }

    time_millis max_delay = 0;
    int max_sound_id = -1;
    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (channels[i].should_play) {
            if (now - channels[i].last_played_time > max_delay) {
                max_delay = now - channels[i].last_played_time;
                max_sound_id = i;
            }
        }
    }

    if (max_sound_id < 0) {
        return;
    }

    // always only one channel available... use it
    int channel = channels[max_sound_id].channel;
    int direction;
    if (channels[max_sound_id].direction_views[SOUND_DIRECTION_CENTER] > 10) {
        direction = SOUND_DIRECTION_CENTER;
    } else if (channels[max_sound_id].direction_views[SOUND_DIRECTION_LEFT] > 10) {
        direction = SOUND_DIRECTION_LEFT;
    } else if (channels[max_sound_id].direction_views[SOUND_DIRECTION_RIGHT] > 10) {
        direction = SOUND_DIRECTION_RIGHT;
    } else {
        direction = SOUND_DIRECTION_CENTER;
    }

    sound_city_play_channel(channel, direction);
    sounds.last_update_time = now;
    channels[max_sound_id].last_played_time = now;
    channels[max_sound_id].total_views = 0;
    for (int d = 0; d < 5; d++) {
        channels[max_sound_id].direction_views[d] = 0;
    }
    channels[max_sound_id].times_played++;
}

struct city_ambient_config_t {
    int max_voices = 4;
    int min_gain_pct = 5;
    int crossfade_ms = 600;
    int duck_pct = 35;
    int duck_ms = 300;
    int gap_min_ms = 400;
    int gap_max_ms = 2500;
    int full_tiles = 16;
};
ANK_CONFIG_STRUCT(city_ambient_config_t, max_voices, min_gain_pct, crossfade_ms, duck_pct, duck_ms, gap_min_ms,
  gap_max_ms, full_tiles)
city_ambient_config_t ANK_VARIABLE_N(g_city_ambient_config, "city_ambient");

namespace {

    constexpr int ambient_voice_slots = 8;
    // next_play while the sample plays: the gap is drawn once it has ended.
    constexpr time_millis ambient_replay_pending = 0;


    struct ambient_choice {
        int channel;
        float gain;
        float pan;
    };

    float approach(float value, float target, float step) {
        return value < target ? std::min(target, value + step) : std::max(target, value - step);
    }

} // namespace

void city_ambient_t::reset() {
    for (auto& v : voices) {
        if (v.active) {
            sound_manager().stop_city_channel(v.channel);
        }
        v = {};
    }
    seen.fill({});
    last_camera = {-1, -1};
    duck = 1.f;
    running = false;
    summary.clear();
}

void sound_city_t::ambient_note(int channel, vec2i pixel) {
    main_thread::check("sound_city_ambient_note");
    const int index = channel - SOUND_CHANNEL_CITY_MIN;
    if (index < 0 || index >= MAX_CHANNELS) {
        return;
    }

    auto& a = ambient;
    a.view_offset = g_camera.offset;
    a.view_size = g_camera.size_pixels;
    const float dx = (float)(pixel.x - (a.view_offset.x + a.view_size.x / 2));
    const float dy = (float)(pixel.y - (a.view_offset.y + a.view_size.y / 2));
    const float dist = std::sqrt(dx * dx + dy * dy);
    city_ambient_t::seen_t& s = a.seen[index];
    if (!s.tiles || dist < s.best_dist) {
        s.best_dist = dist;
        s.best_x = pixel.x;
    }
    s.tiles++;
}

void sound_city_t::ambient_reset() {
    ambient.reset();
}

const char* sound_city_t::ambient_summary() const {
    return ambient.summary.c_str();
}

// Enhanced model: every building drawn this frame is a source; per sample the nearest one sets the gain (by its
// distance to the screen centre, scaled by how much of it is on screen) and the pan (its x). The loudest
// max_voices samples play, gains crossfade when the set changes and duck while the camera moves; a voice
// replays its sample after a random gap. Returns false when the feature is off, so the OG model runs.
bool sound_city_t::ambient_play() {
    auto& a = ambient;
    if (!game_features::gameplay_enhanced_city_ambient) {
        if (a.running) {
            a.reset();
        }
        return false;
    }
    a.running = true;

    const auto& cfg = g_city_ambient_config;
    const time_millis now = time_get_millis();
    const float dt = (float)std::clamp<int>((int)(now - a.last_ms), 0, 100);
    a.last_ms = now;

    const float radius
      = std::max(1.f, 0.5f * std::sqrt((float)(a.view_size.x * a.view_size.x + a.view_size.y * a.view_size.y)));
    std::vector<ambient_choice> chosen;
    for (int i = 0; i < MAX_CHANNELS; i++) {
        const city_ambient_t::seen_t& s = a.seen[i];
        if (!s.tiles) {
            continue;
        }
        float gain = std::clamp(1.f - s.best_dist / radius, 0.f, 1.f);
        gain *= std::min(1.f, 0.5f + 0.5f * (float)s.tiles / (float)std::max(1, cfg.full_tiles));
        if (gain * 100.f < (float)cfg.min_gain_pct) {
            continue;
        }
        const float pan = std::clamp((float)(s.best_x - a.view_offset.x) / (float)std::max(1, a.view_size.x), 0.f, 1.f);
        chosen.push_back({i + SOUND_CHANNEL_CITY_MIN, gain, pan});
    }
    a.seen.fill({});

    std::sort(chosen.begin(), chosen.end(), [](const ambient_choice& l, const ambient_choice& r) {
        return l.gain != r.gain ? l.gain > r.gain : l.channel < r.channel;
    });
    const int max_voices = std::clamp(cfg.max_voices, 0, ambient_voice_slots);
    if ((int)chosen.size() > max_voices) {
        chosen.resize(max_voices);
    }

    for (auto& v : a.voices) {
        if (!v.active) {
            continue;
        }
        auto it
          = std::find_if(chosen.begin(), chosen.end(), [&](const ambient_choice& c) { return c.channel == v.channel; });
        v.target = it == chosen.end() ? 0.f : it->gain;
        if (it != chosen.end()) {
            v.pan = it->pan;
        }
    }
    for (const auto& c : chosen) {
        auto has = std::find_if(a.voices.begin(), a.voices.end(),
          [&](const city_ambient_t::voice_t& v) { return v.active && v.channel == c.channel; });
        if (has != a.voices.end()) {
            continue;
        }
        auto slot
          = std::find_if(a.voices.begin(), a.voices.end(), [](const city_ambient_t::voice_t& v) { return !v.active; });
        if (slot == a.voices.end()) {
            continue;
        }
        *slot = {c.channel, 0.f, c.gain, c.pan, now ? now : 1, true};
    }

    const bool camera_moved = a.last_camera != g_camera.camera_position && a.last_camera != vec2i{-1, -1};
    a.last_camera = g_camera.camera_position;
    const float duck_target = camera_moved ? (float)cfg.duck_pct / 100.f : 1.f;
    a.duck = approach(a.duck, duck_target, dt / (float)std::max(1, cfg.duck_ms));

    const int city_volume = game_features::gameopt_sound_city_enabled.to_bool()
                              ? calc_bound(game_features::gameopt_sound_city_volume.to_int(), 0, 100)
                              : 0;
    std::string summary;
    for (auto& v : a.voices) {
        if (!v.active) {
            continue;
        }
        v.gain = approach(v.gain, v.target, dt / (float)std::max(1, cfg.crossfade_ms));
        if (v.target <= 0.f && v.gain <= 0.f) {
            sound_manager().stop_city_channel(v.channel);
            v = {};
            continue;
        }

        const int volume = (int)((float)city_volume * v.gain * a.duck);
        const int left = (int)(std::min(1.f, 2.f * (1.f - v.pan)) * 100.f);
        const int right = (int)(std::min(1.f, 2.f * v.pan) * 100.f);
        if (sound_manager().is_channel_playing(v.channel)) {
            sound_manager().set_channel_volume(v.channel, volume);
            sound_manager().set_channel_pan(v.channel, left, right);
        } else if (v.next_play == ambient_replay_pending) {
            const int gap_min = std::max(0, cfg.gap_min_ms);
            const int gap_max = std::max(gap_min, cfg.gap_max_ms);
            v.next_play = now + (time_millis)std::uniform_int_distribution<int>(gap_min, gap_max)(a.rng);
        } else if (v.target > 0.f && city_volume > 0 && now >= v.next_play) {
            sound_manager().play_channel_panned(v.channel, volume, left, right);
            v.next_play = ambient_replay_pending;
        }

        if (v.target > 0.f) {
            char buf[48];
            snprintf(buf, sizeof(buf), "%s%d:%d:%d", summary.empty() ? "" : " ", v.channel, (int)(v.target * 10.f) * 10,
              (int)(v.pan * 10.f) * 10);
            summary += buf;
        }
    }

    if (summary != a.summary) {
        a.summary = summary;
        if (sound_manager().log_events()) {
            logs::info("[sound] ambient voices %s", summary.empty() ? "-" : summary.c_str());
        }
    }
    return true;
}
