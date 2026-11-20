#include "sound/sound_view_queue.h"

#include "building/building.h"
#include "city/city_buildings.h"
#include "game/game_config.h"
#include "grid/terrain.h"
#include "sound/sound_city.h"

#include <algorithm>

void sound_view_queue_t::push(int building_id, int grid_offset, int direction, vec2i pixel) {
    const int index = count.fetch_add(1, std::memory_order_relaxed);
    if (index < (int)entries.size()) {
        entries[index] = {building_id, grid_offset, direction, pixel};
    }
}

void sound_view_queue_t::apply() {
    const int n = std::min(count.load(std::memory_order_relaxed), (int)entries.size());
    for (int i = 0; i < n; i++) {
        const entry& en = entries[i];
        if (en.building_id) {
            building* b = building_get(en.building_id);
            sound_city_mark_building_view(b, en.direction);
            if (!!game_features::gameplay_enhanced_city_ambient) {
                if (const int channel = sound_city_building_channel(b)) {
                    sound_city_ambient_note(channel, en.pixel);
                }
            }
        } else {
            sound_city_mark_terrain_view(map_terrain_get(en.grid_offset), en.grid_offset, en.direction);
        }
    }
    count.store(0, std::memory_order_relaxed);
}
