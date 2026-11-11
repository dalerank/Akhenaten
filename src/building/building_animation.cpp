#include "building/building.h"

#include "core/calc.h"
#include "graphics/image.h"
#include "game/game.h"
#include "grid/grid.h"
#include "grid/sprite.h"

#include <array>
#include <atomic>

namespace {
    // Draw workers compute the next frame but must not write the saved sprite grid; the main thread
    // stores the queued frames after the draw. Each entry of one draw is computed from the same grid,
    // so a tile drawn twice still steps once. Entries from a draw that was never applied (editor,
    // screenshot strips) are dropped: they may belong to a map that is no longer loaded.
    struct sprite_frame_queue_t {
        struct entry {
            int grid_offset;
            uint16_t value;
            uint32_t frame;
        };
        std::array<entry, GRID_SIZE_TOTAL> entries;
        std::atomic<int> count{0};

        void push(int grid_offset, int value) {
            const int index = count.fetch_add(1, std::memory_order_relaxed);
            if (index < (int)entries.size()) {
                entries[index] = {grid_offset, (uint16_t)value, game.frame};
            }
        }

        void apply() {
            const int n = std::min(count.load(std::memory_order_relaxed), (int)entries.size());
            for (int i = 0; i < n; i++) {
                if (entries[i].frame == game.frame) {
                    map_sprite_animation_set(entries[i].grid_offset, entries[i].value);
                }
            }
            count.store(0, std::memory_order_relaxed);
        }
    };
    sprite_frame_queue_t g_sprite_frame_queue;
} // namespace

void building_animation_frames_apply() {
    g_sprite_frame_queue.apply();
}

int building::animation_offset(int image_id, int grid_offset, int max_frames, int duration) {
    if (!play_animation) {
        return 0;
    }

    const image_t* img = image_get(image_id);
    if (!img) {
        return 0;
    }

    if (!max_frames) {
        max_frames = img->animation.num_sprites;
    }

    int anim_speed = dcast()->animation_speed(img->animation.speed_id);

    if (!game.animation_should_advance(anim_speed)) {
        return map_sprite_animation_at(grid_offset) & 0x7f;
    }

    // advance animation
    int new_sprite = 0;
    bool is_reverse = false;
    if (img->animation.can_reverse) {
        if (map_sprite_animation_at(grid_offset) & 0x80)
            is_reverse = true;

        int current_sprite = map_sprite_animation_at(grid_offset) & 0x7f;
        if (is_reverse) {
            new_sprite = current_sprite - 1;
            if (new_sprite < 1) {
                new_sprite = 1;
                is_reverse = false;
            }
        } else {
            new_sprite = current_sprite + 1;
            if (new_sprite > max_frames) {
                new_sprite = max_frames;
                is_reverse = true;
            }
        }
    } else {
        // Absolutely normal case
        new_sprite = map_sprite_animation_at(grid_offset) + 1;
        if (new_sprite > max_frames) {
            new_sprite = 1;
        }
    }

    g_sprite_frame_queue.push(grid_offset, is_reverse ? new_sprite | 0x80 : new_sprite);
    return new_sprite;
}