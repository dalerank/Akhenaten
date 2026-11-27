#pragma once

#include <cstdint>

struct SDL_Texture;

namespace render_stats {

    enum e_phase {
        phase_update,
        phase_record,
        phase_merge,
        phase_sort,
        phase_execute,
        phase_ui,
        phase_device,
        phase_atlas,
        phase_present,
        phase_count
    };

    const char* phase_name(e_phase phase);

    struct frame_t {
        uint32_t draws = 0;
        uint32_t resident = 0;
        uint32_t texture_switches = 0;
        uint32_t blend_switches = 0;
        uint32_t batches = 0;
        uint32_t flushes = 0;
        uint32_t window_immediate = 0;
        double frame_ms = 0.0;
        double draw_ms = 0.0;
        double present_ms = 0.0;
        double phase_ms[phase_count] = {};
    };

    struct phase_scope {
        explicit phase_scope(e_phase phase);
        ~phase_scope();

        int prev;
        bool active;
    };

    void note_draw(SDL_Texture* texture, int blend, bool linear, bool resident);
    void note_break();
    void note_flush();
    void note_primitive();

    void window_draw_begin();
    void window_draw_end();

    struct recorded_scope {
        recorded_scope();
        ~recorded_scope();
    };

    void frame_begin();
    void frame_draw_done();
    void frame_end();

    const frame_t& last_frame();
    uint32_t take_average(frame_t& out);

} // namespace render_stats
