#include "sound_city.h"

#include "game/game_config.h"

#include "building/building_house.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/log.h"
#include "core/profiler.h"
#include "graphics/view/view.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "sound/channel.h"
#include "sound/sound.h"
#include "js/js_game.h"

#include <assert.h>
#include <string.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <string>
#include <vector>

// OG savegame city_sounds chunk holds 70 channels (8960 bytes); later channels are runtime-only.
#define SAVED_CHANNELS              70
#define MAX_CHANNELS                ((int)std::tuple_size<decltype(city_sounds_t::channels)>::value)

city_sounds_t g_city_sounds;
const e_sound_channel_city_tokens_t ANK_CONFIG_ENUM(e_sound_channel_city_tokens);
static_assert(SOUND_CHANNEL_CITY_COUNT - SOUND_CHANNEL_CITY_START <= MAX_CHANNELS, "city_sounds_t::channels too small");

const city_sounds_t &sound_city_channels() {
    return g_city_sounds;
}

// OG city_view.c is_silent_venue: quiet while enemies are in the city or when unstaffed.
static bool is_silent_venue(e_building_type type) {
    return type == BUILDING_BANDSTAND || type == BUILDING_BOOTH || type == BUILDING_SENET_HOUSE
           || type == BUILDING_PAVILLION || type == BUILDING_ZOO;
}

void sound_city_init() {
    auto &channels = g_city_sounds.channels;
    g_city_sounds.last_update_time = time_get_millis();
    memset(channels.data(), 0, channels.size() * sizeof(city_sound_channel));

    int i = SOUND_CHANNEL_CITY_START;
    for (auto &channel: channels) {
        channel.in_use = 1;
        channel.views_threshold = 200;
        channel.delay_millis = 30000;
        channel.last_played_time = 35000;
        channel.channel = i++;
    }
}

void sound_city_stop() {
    g_sound.stop_city_channels();
}

int building_type_to_channel(building *b) {
    switch (b->type) {
    default:
        ; // nothing
        break;

    case BUILDING_HOUSE_CRUDE_HUT:
        {
            auto house = b->dcast_house();
            if (house && house->house_population() <= 0) {
                return 0;
            }
        }
        // falltrougth
    case BUILDING_HOUSE_STURDY_HUT:
    case BUILDING_HOUSE_MEAGER_SHANTY:
    case BUILDING_HOUSE_COMMON_SHANTY:
        return SOUND_CHANNEL_CITY_HOUSE_SLUM;

    case BUILDING_HOUSE_ROUGH_COTTAGE:
    case BUILDING_HOUSE_ORDINARY_COTTAGE:
    case BUILDING_HOUSE_MODEST_HOMESTEAD:
    case BUILDING_HOUSE_SPACIOUS_HOMESTEAD:
        return SOUND_CHANNEL_CITY_HOUSE_POOR;

    case BUILDING_HOUSE_MODEST_APARTMENT:
    case BUILDING_HOUSE_SPACIOUS_APARTMENT:
    case BUILDING_HOUSE_COMMON_RESIDENCE:
    case BUILDING_HOUSE_SPACIOUS_RESIDENCE:
        return SOUND_CHANNEL_CITY_HOUSE_MEDIUM;

    case BUILDING_HOUSE_ELEGANT_RESIDENCE:
    case BUILDING_HOUSE_FANCY_RESIDENCE:
    case BUILDING_HOUSE_COMMON_MANOR:
    case BUILDING_HOUSE_SPACIOUS_MANOR:
        return SOUND_CHANNEL_CITY_HOUSE_GOOD;

    case BUILDING_HOUSE_STATELY_MANOR:
    case BUILDING_HOUSE_MODEST_ESTATE:
    case BUILDING_HOUSE_PALATIAL_ESTATE:
        return SOUND_CHANNEL_CITY_HOUSE_POSH;

    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        return 0;

    case BUILDING_LOW_BRIDGE:
    case BUILDING_UNUSED_SHIP_BRIDGE_83:
        return 0;
    }

    return b->dcast()->sound_channel();
}

void sound_city_add_channel(int system_channel_index, int direction) {
    if (!system_channel_index) {
        return;
    }
    auto &slot = g_city_sounds.channels[system_channel_index - SOUND_CHANNEL_CITY_START];
    slot.available = 1;
    ++slot.total_views;
    ++slot.direction_views[direction];
}

void sound_city_mark_terrain_view(int terrain, int grid_offset, int direction) {
    int system_channel_index = 0;
    if (terrain & TERRAIN_TREE) {
        system_channel_index = SOUND_CHANNEL_CITY_TREE;
    } else if (terrain & TERRAIN_ROCK) {
        system_channel_index = SOUND_CHANNEL_CITY_ROCK;
    } else if (terrain & TERRAIN_WATER) {
        system_channel_index = SOUND_CHANNEL_CITY_WATER;
    } else if (terrain & TERRAIN_SHRUB) {
        system_channel_index = SOUND_CHANNEL_CITY_SHRUB;
    } else if (terrain & TERRAIN_GARDEN) {
        system_channel_index = SOUND_CHANNEL_CITY_GARDEN;
    } else if (terrain & TERRAIN_CANAL) {
        system_channel_index = SOUND_CHANNEL_CITY_CANAL;
    } else if (terrain & TERRAIN_MEADOW) {
        system_channel_index = SOUND_CHANNEL_CITY_MEADOW;
    } else if (terrain & TERRAIN_FLOODPLAIN) {
        system_channel_index = SOUND_CHANNEL_CITY_FLOODPLAIN;
    } else if (terrain & TERRAIN_MARSHLAND) {
        system_channel_index = SOUND_CHANNEL_CITY_MARSHLAND;
    }

    sound_city_add_channel(system_channel_index, direction);
}

int sound_city_building_channel(building* b) {
    if (b->state != BUILDING_STATE_VALID) {
        return 0;
    }

    e_building_type type = b->type;
    verify_no_crash(type <= BUILDING_MAX);
    if (is_silent_venue(type) && (g_city.figures.enemies > 0 || b->num_workers < 1)) {
        return 0;
    }
    return building_type_to_channel(b);
}

void sound_city_mark_building_view(building* b, int direction) {
    OZZY_PROFILER_FUNCTION()

    if (b->state == BUILDING_STATE_VALID) {
        if (building_impl *impl = b->dcast()) {
            impl->add_ambient_sound(direction);
        }
    }

    const int system_channel_index = sound_city_building_channel(b);
    sound_city_add_channel(system_channel_index, direction);
}

void sound_city_decay_views(void) {
    auto &channels = g_city_sounds.channels;

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

    if (g_sound.is_channel_playing(channel)) {
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

    g_sound.play_channel_panned(channel, game_features::gameopt_sound_city_volume.to_int(), left_pan, right_pan);
}

static bool sound_city_ambient_play();

void sound_city_play() {
    if (sound_city_ambient_play()) {
        return;
    }

    auto &channels = g_city_sounds.channels;
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

    if (now - g_city_sounds.last_update_time < 2000) {
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
    g_city_sounds.last_update_time = now;
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

    struct ambient_seen {
        int tiles = 0;
        float best_dist = 0.f;
        int best_x = 0;
    };

    struct ambient_voice {
        int channel = 0;
        float gain = 0.f;
        float target = 0.f;
        float pan = 0.5f;
        time_millis next_play = 0;
        bool active = false;
    };

    struct ambient_choice {
        int channel;
        float gain;
        float pan;
    };

    struct city_ambient_t {
        std::array<ambient_seen, MAX_CHANNELS> seen;
        std::array<ambient_voice, ambient_voice_slots> voices;
        vec2i last_camera = {-1, -1};
        vec2i view_offset = {0, 0};
        vec2i view_size = {0, 0};
        float duck = 1.f;
        time_millis last_ms = 0;
        bool running = false;
        // Cosmetic: never the simulation LFSR, crt_rand or libc rand().
        std::minstd_rand rng{std::random_device{}()};
        std::string summary;

        void reset() {
            for (auto& v : voices) {
                if (v.active) {
                    g_sound.stop_city_channel(v.channel);
                }
                v = {};
            }
            seen.fill({});
            last_camera = {-1, -1};
            duck = 1.f;
            running = false;
            summary.clear();
        }
    };

    city_ambient_t g_city_ambient;

    float approach(float value, float target, float step) {
        return value < target ? std::min(target, value + step) : std::max(target, value - step);
    }

} // namespace

void sound_city_ambient_note(int channel, vec2i pixel) {
    const int index = channel - SOUND_CHANNEL_CITY_START;
    if (index < 0 || index >= MAX_CHANNELS) {
        return;
    }

    auto& a = g_city_ambient;
    a.view_offset = g_camera.offset;
    a.view_size = g_camera.size_pixels;
    const float dx = (float)(pixel.x - (a.view_offset.x + a.view_size.x / 2));
    const float dy = (float)(pixel.y - (a.view_offset.y + a.view_size.y / 2));
    const float dist = std::sqrt(dx * dx + dy * dy);
    ambient_seen& s = a.seen[index];
    if (!s.tiles || dist < s.best_dist) {
        s.best_dist = dist;
        s.best_x = pixel.x;
    }
    s.tiles++;
}

void sound_city_ambient_reset() {
    g_city_ambient.reset();
}

const char* sound_city_ambient_summary() {
    return g_city_ambient.summary.c_str();
}

// Enhanced model: every building drawn this frame is a source; per sample the nearest one sets the gain (by its
// distance to the screen centre, scaled by how much of it is on screen) and the pan (its x). The loudest
// max_voices samples play, gains crossfade when the set changes and duck while the camera moves; a voice
// replays its sample after a random gap. Returns false when the feature is off, so the OG model runs.
static bool sound_city_ambient_play() {
    auto& a = g_city_ambient;
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
        const ambient_seen& s = a.seen[i];
        if (!s.tiles) {
            continue;
        }
        float gain = std::clamp(1.f - s.best_dist / radius, 0.f, 1.f);
        gain *= std::min(1.f, 0.5f + 0.5f * (float)s.tiles / (float)std::max(1, cfg.full_tiles));
        if (gain * 100.f < (float)cfg.min_gain_pct) {
            continue;
        }
        const float pan = std::clamp((float)(s.best_x - a.view_offset.x) / (float)std::max(1, a.view_size.x), 0.f, 1.f);
        chosen.push_back({i + SOUND_CHANNEL_CITY_START, gain, pan});
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
          [&](const ambient_voice& v) { return v.active && v.channel == c.channel; });
        if (has != a.voices.end()) {
            continue;
        }
        auto slot = std::find_if(a.voices.begin(), a.voices.end(), [](const ambient_voice& v) { return !v.active; });
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
            g_sound.stop_city_channel(v.channel);
            v = {};
            continue;
        }

        const int volume = (int)((float)city_volume * v.gain * a.duck);
        const int left = (int)(std::min(1.f, 2.f * (1.f - v.pan)) * 100.f);
        const int right = (int)(std::min(1.f, 2.f * v.pan) * 100.f);
        if (g_sound.is_channel_playing(v.channel)) {
            g_sound.set_channel_volume(v.channel, volume);
            g_sound.set_channel_pan(v.channel, left, right);
        } else if (v.next_play == ambient_replay_pending) {
            const int gap_min = std::max(0, cfg.gap_min_ms);
            const int gap_max = std::max(gap_min, cfg.gap_max_ms);
            v.next_play = now + (time_millis)std::uniform_int_distribution<int>(gap_min, gap_max)(a.rng);
        } else if (v.target > 0.f && city_volume > 0 && now >= v.next_play) {
            g_sound.play_channel_panned(v.channel, volume, left, right);
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
        if (g_sound.log_events()) {
            logs::info("[sound] ambient voices %s", summary.empty() ? "-" : summary.c_str());
        }
    }
    return true;
}

// OG city_sound_types.h: one 128-byte record per slot, 70 slots.
struct og_city_sound_slot {
    int32_t available;
    int32_t total_views;
    int32_t views_threshold;
    int32_t direction_views[5];
    int32_t current_channel;
    int32_t num_channels;
    int32_t channels[8];
    int32_t in_use;
    int32_t times_played;
    uint32_t last_played_time;
    uint32_t delay_millis;
    int32_t should_play;
    int32_t unused[9];
};
static_assert(sizeof(og_city_sound_slot) == 128, "OG city_sound_channel is a 128-byte savegame record");

// OG city_view.c city_sound_channel_ids: the sample bound to each set-up slot (1..63); slot 0 stays empty.
// clang-format off
static const int32_t og_city_sound_channel_ids[64] = {
    0,   30,  34,  38,  42,  46,  50,  51,  52,  53,  54,  55,  56,  57,  58,  62,
    63,  64,  65,  66,  67,  68,  69,  70,  74,  78,  79,  80,  81,  82,  83,  87,
    89,  91,  93,  95,  97,  98,  99,  100, 101, 102, 106, 110, 111, 112, 113, 114,
    115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 132, 133,
};
// clang-format on

// Loading always rebuilds the city sounds with sound_city_init() (as OG game_file.c does), so the chunk is
// written as OG's sound_city_init() leaves it, minus the wall-clock last_played_time: the view counters
// depend on what was drawn and the clock on when, and neither may make save -> load -> save differ.
static void og_city_sounds_image(std::array<og_city_sound_slot, SAVED_CHANNELS>& slots) {
    memset(slots.data(), 0, sizeof(og_city_sound_slot) * slots.size());
    for (int i = 1; i < (int)std::size(og_city_sound_channel_ids); i++) {
        og_city_sound_slot& slot = slots[i];
        slot.views_threshold = 200;
        slot.num_channels = 1;
        slot.channels[0] = og_city_sound_channel_ids[i];
        slot.in_use = 1;
        slot.delay_millis = 30000;
    }
}

io_buffer* iob_city_sounds = new io_buffer([](io_buffer* iob, size_t version) {
    static std::array<og_city_sound_slot, SAVED_CHANNELS> slots;
    og_city_sounds_image(slots);
    iob->bind(BIND_SIGNATURE_RAW, slots.data(), sizeof(og_city_sound_slot) * slots.size());
});
