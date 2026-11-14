#include "graphics/render_stats.h"

#include <SDL.h>

namespace render_stats {

    namespace {

        frame_t g_current;
        frame_t g_last;
        frame_t g_sum;
        uint32_t g_sum_frames = 0;

        const SDL_Texture* g_batch_texture = nullptr;
        int g_batch_blend = -1;
        int g_last_blend = -1;

        Uint64 g_frame_start = 0;
        Uint64 g_draw_done = 0;
        Uint64 g_prev_frame_start = 0;

        double ticks_to_ms(Uint64 ticks) {
            const Uint64 freq = SDL_GetPerformanceFrequency();
            return freq ? (double)ticks * 1000.0 / (double)freq : 0.0;
        }

    } // namespace

    void note_draw(SDL_Texture* texture, int blend, bool resident) {
        ++g_current.draws;
        if (resident) {
            ++g_current.resident;
        }
        if (texture != g_batch_texture && g_batch_texture != nullptr) {
            ++g_current.texture_switches;
        }
        if (blend != g_last_blend && g_last_blend != -1) {
            ++g_current.blend_switches;
        }
        if (texture != g_batch_texture || blend != g_batch_blend) {
            ++g_current.batches;
        }
        g_batch_texture = texture;
        g_batch_blend = blend;
        g_last_blend = blend;
    }

    void note_break() {
        g_batch_texture = nullptr;
        g_batch_blend = -1;
    }

    void frame_begin() {
        const Uint64 now = SDL_GetPerformanceCounter();
        if (g_prev_frame_start != 0) {
            g_current.frame_ms = ticks_to_ms(now - g_prev_frame_start);
        }
        g_prev_frame_start = now;
        g_frame_start = now;
        g_draw_done = now;
    }

    void frame_draw_done() {
        g_draw_done = SDL_GetPerformanceCounter();
        g_current.draw_ms = ticks_to_ms(g_draw_done - g_frame_start);
    }

    void frame_end() {
        g_current.present_ms = ticks_to_ms(SDL_GetPerformanceCounter() - g_draw_done);
        g_last = g_current;

        g_sum.draws += g_last.draws;
        g_sum.resident += g_last.resident;
        g_sum.texture_switches += g_last.texture_switches;
        g_sum.blend_switches += g_last.blend_switches;
        g_sum.batches += g_last.batches;
        g_sum.frame_ms += g_last.frame_ms;
        g_sum.draw_ms += g_last.draw_ms;
        g_sum.present_ms += g_last.present_ms;
        ++g_sum_frames;

        g_current = frame_t{};
        note_break();
        g_last_blend = -1;
    }

    const frame_t& last_frame() {
        return g_last;
    }

    uint32_t take_average(frame_t& out) {
        const uint32_t n = g_sum_frames;
        out = frame_t{};
        if (n > 0) {
            out.draws = g_sum.draws / n;
            out.resident = g_sum.resident / n;
            out.texture_switches = g_sum.texture_switches / n;
            out.blend_switches = g_sum.blend_switches / n;
            out.batches = g_sum.batches / n;
            out.frame_ms = g_sum.frame_ms / n;
            out.draw_ms = g_sum.draw_ms / n;
            out.present_ms = g_sum.present_ms / n;
        }
        g_sum = frame_t{};
        g_sum_frames = 0;
        return n;
    }

} // namespace render_stats
