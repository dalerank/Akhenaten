#pragma once

#include <cstdint>

struct SDL_Texture;

namespace render_stats {

    struct frame_t {
        uint32_t draws = 0;
        uint32_t resident = 0;
        uint32_t texture_switches = 0;
        uint32_t blend_switches = 0;
        uint32_t batches = 0;
        double frame_ms = 0.0;
        double draw_ms = 0.0;
        double present_ms = 0.0;
    };

    void note_draw(SDL_Texture* texture, int blend, bool resident);
    void note_break();

    void frame_begin();
    void frame_draw_done();
    void frame_end();

    const frame_t& last_frame();
    uint32_t take_average(frame_t& out);

} // namespace render_stats
