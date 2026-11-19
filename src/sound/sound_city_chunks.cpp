#include "io/gamestate/presentation_chunks.h"

#include "io/io_buffer.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <iterator>

constexpr int SAVED_CHANNELS = 70;

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

// clang-format off
static const int32_t og_city_sound_channel_ids[64] = {
    0,   30,  34,  38,  42,  46,  50,  51,  52,  53,  54,  55,  56,  57,  58,  62,
    63,  64,  65,  66,  67,  68,  69,  70,  74,  78,  79,  80,  81,  82,  83,  87,
    89,  91,  93,  95,  97,  98,  99,  100, 101, 102, 106, 110, 111, 112, 113, 114,
    115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 132, 133,
};
// clang-format on

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

void city_sounds_chunk::bind_data(io_buffer* iob, size_t version) {
    static std::array<og_city_sound_slot, SAVED_CHANNELS> slots;
    og_city_sounds_image(slots);
    iob->bind(BIND_SIGNATURE_RAW, slots.data(), sizeof(og_city_sound_slot) * slots.size());
}
