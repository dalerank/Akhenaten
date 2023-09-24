#include "city.h"

#include "building/building.h"
#include "city/figures.h"
#include "core/time.h"
#include "game/settings.h"
#include "io/io_buffer.h"
#include "sound/channel.h"
#include "sound/device.h"

#include <assert.h>
#include <string.h>

#define MAX_CHANNELS 70

struct city_channel {
    int in_use;
    int available;
    int total_views;
    int views_threshold;
    int direction_views[5];
    int channel;
    int times_played;
    time_millis last_played_time;
    time_millis delay_millis;
    int should_play;
};

struct city_sounds_t {
    time_millis last_update_time;
    city_channel channels[MAX_CHANNELS];
};

city_sounds_t g_city_sounds;

void sound_city_init() {
    auto &channels = g_city_sounds.channels;
    g_city_sounds.last_update_time = time_get_millis();
    memset(channels, 0, MAX_CHANNELS * sizeof(city_channel));
    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels[i].last_played_time = g_city_sounds.last_update_time;
    }

    for (int i = 1; i < 63; i++) {
        channels[i].in_use = 1;
        channels[i].views_threshold = 200;
        channels[i].delay_millis = 30000;
    }

    channels[1].channel = SOUND_CHANNEL_CITY_HOUSE_SLUM;
    channels[2].channel = SOUND_CHANNEL_CITY_HOUSE_POOR;
    channels[3].channel = SOUND_CHANNEL_CITY_HOUSE_MEDIUM;
    channels[4].channel = SOUND_CHANNEL_CITY_HOUSE_GOOD;
    channels[5].channel = SOUND_CHANNEL_CITY_HOUSE_POSH;
    channels[6].channel = SOUND_CHANNEL_CITY_AMPHITHEATER;
    channels[7].channel = SOUND_CHANNEL_CITY_THEATER;
    channels[8].channel = SOUND_CHANNEL_CITY_HIPPODROME;
    channels[9].channel = SOUND_CHANNEL_CITY_COLOSSEUM;
    channels[10].channel = SOUND_CHANNEL_CITY_GLADIATOR_SCHOOL;
    channels[11].channel = SOUND_CHANNEL_CITY_LION_PIT;
    channels[12].channel = SOUND_CHANNEL_CITY_ACTOR_COLONY;
    channels[13].channel = SOUND_CHANNEL_CITY_CHARIOT_MAKER;
    channels[14].channel = SOUND_CHANNEL_CITY_GARDEN;
    channels[15].channel = SOUND_CHANNEL_CITY_CLINIC;
    channels[16].channel = SOUND_CHANNEL_CITY_HOSPITAL;
    channels[17].channel = SOUND_CHANNEL_CITY_BATHHOUSE;
    channels[18].channel = SOUND_CHANNEL_CITY_BARBER;
    channels[19].channel = SOUND_CHANNEL_CITY_SCHOOL;
    channels[20].channel = SOUND_CHANNEL_CITY_ACADEMY;
    channels[21].channel = SOUND_CHANNEL_CITY_LIBRARY;
    channels[22].channel = SOUND_CHANNEL_CITY_PREFECTURE;
    channels[23].channel = SOUND_CHANNEL_CITY_FORT;
    channels[24].channel = SOUND_CHANNEL_CITY_TOWER;
    channels[25].channel = SOUND_CHANNEL_CITY_TEMPLE_CERES;
    channels[26].channel = SOUND_CHANNEL_CITY_TEMPLE_NEPTUNE;
    channels[27].channel = SOUND_CHANNEL_CITY_TEMPLE_MERCURY;
    channels[28].channel = SOUND_CHANNEL_CITY_TEMPLE_MARS;
    channels[29].channel = SOUND_CHANNEL_CITY_TEMPLE_VENUS;
    channels[30].channel = SOUND_CHANNEL_CITY_MARKET;
    channels[31].channel = SOUND_CHANNEL_CITY_GRANARY;
    channels[32].channel = SOUND_CHANNEL_CITY_WAREHOUSE;
    channels[33].channel = SOUND_CHANNEL_CITY_SHIPYARD;
    channels[34].channel = SOUND_CHANNEL_CITY_DOCK;
    channels[35].channel = SOUND_CHANNEL_CITY_WHARF;
    channels[36].channel = SOUND_CHANNEL_CITY_PALACE;
    channels[37].channel = SOUND_CHANNEL_CITY_ENGINEERS_POST;
    channels[38].channel = SOUND_CHANNEL_CITY_SENATE;
    channels[39].channel = SOUND_CHANNEL_CITY_FORUM;
    channels[40].channel = SOUND_CHANNEL_CITY_RESERVOIR;
    channels[41].channel = SOUND_CHANNEL_CITY_FOUNTAIN;
    channels[42].channel = SOUND_CHANNEL_CITY_WELL;
    channels[43].channel = SOUND_CHANNEL_CITY_MILITARY_ACADEMY;
    channels[44].channel = SOUND_CHANNEL_CITY_ORACLE;
    channels[45].channel = SOUND_CHANNEL_CITY_BURNING_RUIN;
    channels[46].channel = SOUND_CHANNEL_CITY_WHEAT_FARM;
    channels[47].channel = SOUND_CHANNEL_CITY_VEGETABLE_FARM;
    channels[48].channel = SOUND_CHANNEL_CITY_FRUIT_FARM;
    channels[49].channel = SOUND_CHANNEL_CITY_OLIVE_FARM;
    channels[50].channel = SOUND_CHANNEL_CITY_VINE_FARM;
    channels[51].channel = SOUND_CHANNEL_CITY_PIG_FARM;
    channels[52].channel = SOUND_CHANNEL_CITY_QUARRY;
    channels[53].channel = SOUND_CHANNEL_CITY_IRON_MINE;
    channels[54].channel = SOUND_CHANNEL_CITY_TIMBER_YARD;
    channels[55].channel = SOUND_CHANNEL_CITY_CLAY_PIT;
    channels[56].channel = SOUND_CHANNEL_CITY_WINE_WORKSHOP;
    channels[57].channel = SOUND_CHANNEL_CITY_OIL_WORKSHOP;
    channels[58].channel = SOUND_CHANNEL_CITY_WEAPONS_WORKSHOP;
    channels[59].channel = SOUND_CHANNEL_CITY_FURNITURE_WORKSHOP;
    channels[60].channel = SOUND_CHANNEL_CITY_POTTERY_WORKSHOP;
    channels[61].channel = SOUND_CHANNEL_CITY_EMPTY_LAND;
    channels[62].channel = SOUND_CHANNEL_CITY_RIVER;
    channels[63].channel = SOUND_CHANNEL_CITY_MISSION_POST;
}

void sound_city_set_volume(int percentage) {
    for (int i = SOUND_CHANNEL_CITY_MIN; i <= SOUND_CHANNEL_CITY_MAX; i++)
        sound_device_set_channel_volume(i, percentage);
}

int building_type_to_channel(building *b) {
    switch (b->type) {

    case BUILDING_HOUSE_SMALL_HUT:
        if (b->house_population <= 0)
            return 0;
        // falltrougth
    case BUILDING_HOUSE_LARGE_HUT:
    case BUILDING_HOUSE_SMALL_SHACK:
    case BUILDING_HOUSE_LARGE_SHACK:
        return SOUND_CHANNEL_CITY_HOUSE_SLUM;

    case BUILDING_HOUSE_SMALL_HOVEL:
    case BUILDING_HOUSE_LARGE_HOVEL:
    case BUILDING_HOUSE_SMALL_CASA:
    case BUILDING_HOUSE_LARGE_CASA:
        return SOUND_CHANNEL_CITY_HOUSE_POOR;

    case BUILDING_HOUSE_SMALL_INSULA:
    case BUILDING_HOUSE_MEDIUM_INSULA:
    case BUILDING_HOUSE_LARGE_INSULA:
    case BUILDING_HOUSE_GRAND_INSULA:
        return SOUND_CHANNEL_CITY_HOUSE_MEDIUM;

    case BUILDING_HOUSE_SMALL_VILLA:
    case BUILDING_HOUSE_MEDIUM_VILLA:
    case BUILDING_HOUSE_LARGE_VILLA:
    case BUILDING_HOUSE_GRAND_VILLA:
        return SOUND_CHANNEL_CITY_HOUSE_GOOD;

    case BUILDING_HOUSE_SMALL_PALACE:
    case BUILDING_HOUSE_MEDIUM_PALACE:
    case BUILDING_HOUSE_LARGE_PALACE:
    case BUILDING_HOUSE_LUXURY_PALACE:
        return SOUND_CHANNEL_CITY_HOUSE_POSH;
    }

    return 0;
}

void sound_city_mark_building_view(building* b, int direction) {
    auto &channels = g_city_sounds.channels;
    if (b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    int type = b->type;
    assert(type <= 236);
    int system_channel_index = building_type_to_channel(b);
    if (!system_channel_index) {
        return;
    }

    int channel = system_channel_index - SOUND_CHANNEL_CITY_START;
    if (type == BUILDING_BOOTH || type == BUILDING_BANDSTAND || type == BUILDING_CONSERVATORY || type == BUILDING_SENET_HOUSE) {
        // entertainment is shut off when caesar invades
        if (b->num_workers <= 0 || city_figures_imperial_soldiers() > 0) {
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
    if (!setting_sound(SOUND_CITY)->enabled) {
        return;
    }

    if (sound_device_is_channel_playing(channel)) {
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

    sound_device_play_channel_panned(channel, setting_sound(SOUND_CITY)->volume, left_pan, right_pan);
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
        city_channel* ch = &channels[i];
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
