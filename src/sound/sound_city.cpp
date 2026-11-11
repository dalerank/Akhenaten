#include "sound_city.h"

#include "game/game_config.h"

#include "building/building_house.h"
#include "city/city.h"
#include "core/profiler.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "sound/channel.h"
#include "sound/sound.h"
#include "js/js_game.h"

#include <assert.h>
#include <string.h>
#include <array>

// OG savegame city_sounds chunk holds 70 channels (8960 bytes); later channels are runtime-only.
#define SAVED_CHANNELS              70
#define MAX_CHANNELS                ((int)std::tuple_size<decltype(city_sounds_t::channels)>::value)
#define HEALTH_CITY_VIEWS_THRESHOLD 500
#define HEALTH_CITY_DELAY_MILLIS    90000

city_sounds_t g_city_sounds;
const e_sound_channel_city_tokens_t ANK_CONFIG_ENUM(e_sound_channel_city_tokens);
static_assert(SOUND_CHANNEL_CITY_COUNT - SOUND_CHANNEL_CITY_START <= MAX_CHANNELS, "city_sounds_t::channels too small");

const city_sounds_t &sound_city_channels() {
    return g_city_sounds;
}

static bool is_health_city_channel(int channel) {
    return channel == SOUND_CHANNEL_CITY_APOTHECARY
        || channel == SOUND_CHANNEL_CITY_PHYSICIAN
        || channel == SOUND_CHANNEL_CITY_MORTUARY
        || channel == SOUND_CHANNEL_CITY_DENTIST;
}

void sound_city_init() {
    auto &channels = g_city_sounds.channels;
    g_city_sounds.last_update_time = time_get_millis();
    memset(channels.data(), 0, channels.size() * sizeof(city_sound_channel));

    int i = SOUND_CHANNEL_CITY_START;
    for (auto &channel: channels) {
        channel.in_use = 1;
        channel.views_threshold = is_health_city_channel(i) ? HEALTH_CITY_VIEWS_THRESHOLD : 200;
        channel.delay_millis = is_health_city_channel(i) ? HEALTH_CITY_DELAY_MILLIS : 30000;
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

void sound_city_mark_terrain_view(int terrain, int grid_offset, int direction) {
    auto &channels = g_city_sounds.channels;
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

    if (!system_channel_index) {
        return;
    }

    int channel = system_channel_index - SOUND_CHANNEL_CITY_START;
    channels[channel].available = 1;
    ++channels[channel].total_views;
    ++channels[channel].direction_views[direction];
}

void sound_city_mark_building_view(building* b, int direction) {
    OZZY_PROFILER_FUNCTION()

    auto &channels = g_city_sounds.channels;
    if (b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    e_building_type type = b->type;
    verify_no_crash(type <= BUILDING_MAX);
    int system_channel_index = building_type_to_channel(b);
    if (!system_channel_index) {
        return;
    }

    int channel = system_channel_index - SOUND_CHANNEL_CITY_START;
    if (type == BUILDING_BOOTH || type == BUILDING_BANDSTAND || type == BUILDING_CONSERVATORY || type == BUILDING_SENET_HOUSE) {
        // entertainment is shut off when caesar invades
        if (b->num_workers <= 0 || g_city.figures.kingdome_soldiers > 0) {
            return;
        }
    }

    if (is_health_city_channel(system_channel_index)
        && (b->num_workers <= 0 || g_city.health.value >= 40)) {
        return;
    }

    channels[channel].available = 1;
    ++channels[channel].total_views;
    ++channels[channel].direction_views[direction];
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

void sound_city_play() {
    auto &channels = g_city_sounds.channels;
    time_millis now = time_get_millis();
    for (int i = 1; i < MAX_CHANNELS; i++) {
        channels[i].should_play = 0;
        if (channels[i].available) {
            channels[i].available = 0;
            const int views_threshold = is_health_city_channel(channels[i].channel)
                ? HEALTH_CITY_VIEWS_THRESHOLD
                : channels[i].views_threshold;
            const time_millis delay_millis = is_health_city_channel(channels[i].channel)
                ? HEALTH_CITY_DELAY_MILLIS
                : channels[i].delay_millis;
            if (channels[i].total_views >= views_threshold) {
                if (now - channels[i].last_played_time >= delay_millis)
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
    int max_sound_id = 0;
    for (int i = 1; i < MAX_CHANNELS; i++) {
        if (channels[i].should_play) {
            if (now - channels[i].last_played_time > max_delay) {
                max_delay = now - channels[i].last_played_time;
                max_sound_id = i;
            }
        }
    }

    if (!max_sound_id) {
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
