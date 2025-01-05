#include "sound_city.h"

#include "building/building.h"
#include "city/city.h"
#include "game/settings.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "sound/channel.h"
#include "sound/sound.h"

#include <assert.h>
#include <string.h>
#include <array>

#define MAX_CHANNELS 70

city_sounds_t g_city_sounds;
const token_holder<e_sound_channel_city, SOUND_CHANNEL_CITY_NONE, SOUND_CHANNEL_CITY_COUNT> e_sound_channel_city_tokens;

const city_sounds_t &sound_city_channels() {
    return g_city_sounds;
}

void sound_city_init() {
    auto &channels = g_city_sounds.channels;
    g_city_sounds.last_update_time = time_get_millis();
    memset(channels.data(), 0, channels.size() * sizeof(city_sound_channel));
    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels[i].last_played_time = g_city_sounds.last_update_time;
    }

    int i = SOUND_CHANNEL_CITY_START;
    for (auto &channel: channels) {
        channel.in_use = 1;
        channel.views_threshold = 200;
        channel.delay_millis = 30000;
        channel.last_played_time = 35000;
        channel.channel = i++;
    }
}

int building_type_to_channel(building *b) {
    switch (b->type) {
    default:
        ; // nothing
        break;

    case BUILDING_HOUSE_CRUDE_HUT:
        if (b->house_population <= 0) {
            return 0;
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
    auto &channels = g_city_sounds.channels;
    if (b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    e_building_type type = b->type;
    assert(type <= BUILDING_MAX);
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
    if (!g_settings.get_sound(SOUND_CITY)->enabled) {
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

    g_sound.play_channel_panned(channel, g_settings.get_sound(SOUND_CITY)->volume, left_pan, right_pan);
}

void sound_city_play() {
    auto &channels = g_city_sounds.channels;
    time_millis now = time_get_millis();
    for (int i = 1; i < MAX_CHANNELS; i++) {
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

io_buffer* iob_city_sounds = new io_buffer([](io_buffer* iob, size_t version) {
    auto &channels = g_city_sounds.channels;
    for (int i = 0; i < MAX_CHANNELS; i++) {
        city_sound_channel* ch = &channels[i];
        iob->bind(BIND_SIGNATURE_INT32, &ch->available);
        iob->bind(BIND_SIGNATURE_INT32, &ch->total_views);
        iob->bind(BIND_SIGNATURE_INT32, &ch->views_threshold);
        for (int d = 0; d < 5; d++) {
            iob->bind(BIND_SIGNATURE_INT32, &ch->direction_views[d]);
        }
        iob->bind____skip(4); // current channel
        iob->bind____skip(4); // num channels
        iob->bind(BIND_SIGNATURE_INT32, &ch->channel);
        iob->bind____skip(28);
        iob->bind(BIND_SIGNATURE_INT32, &ch->in_use);
        iob->bind(BIND_SIGNATURE_INT32, &ch->times_played);
        iob->bind(BIND_SIGNATURE_UINT32, &ch->last_played_time);
        iob->bind(BIND_SIGNATURE_UINT32, &ch->delay_millis);
        iob->bind(BIND_SIGNATURE_INT32, &ch->should_play);
        iob->bind____skip(36);
    }
});
