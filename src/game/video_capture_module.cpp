#include "video_capture_module.h"

#include "core/app.h"
#include "core/archive.h"
#include "core/log.h"
#include "core/system_time.h"
#include "core/xvalue.h"
#include "game/game.h"
#include "game/game_events.h"
#include "graphics/color.h"
#include "graphics/screen.h"
#include "io/movie_writer.h"
#include "js/js_events.h"
#include "js/js_game.h"
#include "platform/renderer.h"

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

struct video_writer_t {
    static constexpr int k_slot_count = 3;
    static constexpr int k_capture_fps = 4;
    static constexpr unsigned k_max_dst_w = 1280;
    static constexpr unsigned k_max_dst_h = 720;

    std::mutex queue_mu;
    std::condition_variable idle_cv;
    std::queue<int> filled;
    bool slot_free[k_slot_count] = {true, true, true};
    std::vector<color> slots[k_slot_count];
    std::vector<color> scratch;

    std::atomic<bool> pump_scheduled{false};
    std::atomic<bool> in_pump{false};
    std::atomic<bool> stopping{false};
    std::atomic<bool> active_flag{false};

    MovieWriter *writer = nullptr;
    unsigned src_w = 0;
    unsigned src_h = 0;
    unsigned dst_w = 0;
    unsigned dst_h = 0;
    time_millis last_capture_ms = 0;
    unsigned encoded = 0;
    unsigned dropped = 0;

    static void compute_dst_size(unsigned src_w, unsigned src_h, unsigned &dst_w, unsigned &dst_h) {
        const double scale = std::min({k_max_dst_w / double(src_w), k_max_dst_h / double(src_h), 1.0});
        dst_w = (unsigned(src_w * scale) & ~1u);
        dst_h = (unsigned(src_h * scale) & ~1u);
    }

    void register_callbacks() {
        events::subscribe_permanent([this](event_video_capture_start) {
            start();
        });
        events::subscribe_permanent([this](event_video_capture_stop) {
            stop();
        });
        events::subscribe_permanent([this](event_game_exit_requested) {
            stop();
        });
        events::subscribe_permanent([this](event_video_capture_toggle) {
            if (active()) {
                stop();
            } else {
                start();
            }
        });

        game.add_frame_pre_present_handler([this]() {
            on_frame_end();
        });
    }

    void free_resources_unlocked() {
        for (int i = 0; i < k_slot_count; ++i) {
            slots[i].clear();
            slots[i].shrink_to_fit();
            slot_free[i] = true;
        }
        while (!filled.empty()) {
            filled.pop();
        }
        scratch.clear();
        scratch.shrink_to_fit();
        src_w = src_h = dst_w = dst_h = 0;
        last_capture_ms = 0;
    }

    int claim_free_slot_unlocked() {
        for (int i = 0; i < k_slot_count; ++i) {
            if (slot_free[i]) {
                slot_free[i] = false;
                return i;
            }
        }
        return -1;
    }

    void recycle_slot_unlocked(int slot) {
        if (slot < 0 || slot >= k_slot_count) {
            return;
        }
        slot_free[slot] = true;
    }

    bool is_idle_unlocked() const {
        return !in_pump.load(std::memory_order_acquire) && !pump_scheduled.load(std::memory_order_acquire) && filled.empty();
    }

    bool active() const {
        return active_flag.load(std::memory_order_acquire);
    }

    void pump();
    bool start();
    void stop();
    void on_frame_end();

    static void downscale_bgra_nearest(const color *src, unsigned src_w, unsigned src_h, color *dst, unsigned dst_w,
                                       unsigned dst_h) {
        for (unsigned y = 0; y < dst_h; ++y) {
            const unsigned sy = y * src_h / dst_h;
            const color *src_row = src + sy * src_w;
            color *dst_row = dst + y * dst_w;
            for (unsigned x = 0; x < dst_w; ++x) {
                dst_row[x] = src_row[x * src_w / dst_w];
            }
        }
    }
};

void video_writer_t::pump() {
    in_pump.store(true, std::memory_order_release);
    for (;;) {
        int slot = -1;
        {
            std::unique_lock<std::mutex> lock(queue_mu);
            if (filled.empty()) {
                pump_scheduled.store(false, std::memory_order_release);
                if (!filled.empty()) {
                    pump_scheduled.store(true, std::memory_order_release);
                    continue;
                }
                break;
            }
            slot = filled.front();
            filled.pop();
        }

        if (writer && slot >= 0) {
            downscale_bgra_nearest(slots[slot].data(), src_w, src_h, scratch.data(), dst_w, dst_h);
            writer->addFrame(reinterpret_cast<const uint8_t *>(scratch.data()));
            ++encoded;
        }

        {
            std::lock_guard<std::mutex> lock(queue_mu);
            recycle_slot_unlocked(slot);
        }
    }
    in_pump.store(false, std::memory_order_release);
    idle_cv.notify_all();
}

bool video_writer_t::start() {
#ifndef GAME_HAS_VIDEO_RECORDING
    logs::info("VideoCapture: recording disabled at build time");
    return false;
#else
    if (active()) {
        return true;
    }

    const unsigned sw = (unsigned)screen_width();
    const unsigned sh = (unsigned)screen_height();
    if (sw < 2 || sh < 2) {
        logs::error("VideoCapture: invalid screen size %ux%u", sw, sh);
        return false;
    }

    unsigned dw = 0;
    unsigned dh = 0;
    compute_dst_size(sw, sh, dw, dh);
    if (dw < 2 || dh < 2) {
        logs::error("VideoCapture: invalid dst size %ux%u", dw, dh);
        return false;
    }

    std::vector<color> new_slots[k_slot_count];
    std::vector<color> new_scratch;
    for (int i = 0; i < k_slot_count; ++i) {
        new_slots[i].resize(size_t(sw) * sh);
    }
    new_scratch.resize(size_t(dw) * dh);

    MovieWriter *mw = new MovieWriter("akhenaten_capture.mp4", dw, dh, k_capture_fps);
    if (!mw->ok()) {
        logs::error("VideoCapture: MovieWriter failed to initialize");
        delete mw;
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(queue_mu);
        free_resources_unlocked();
        for (int i = 0; i < k_slot_count; ++i) {
            slots[i].swap(new_slots[i]);
            slot_free[i] = true;
        }
        scratch.swap(new_scratch);
        src_w = sw;
        src_h = sh;
        dst_w = dw;
        dst_h = dh;
        encoded = 0;
        dropped = 0;
        writer = mw;
        stopping.store(false, std::memory_order_release);
        pump_scheduled.store(false, std::memory_order_release);
        in_pump.store(false, std::memory_order_release);
    }

    last_capture_ms = 0;
    active_flag.store(true, std::memory_order_release);
    logs::info("VideoCapture: started %ux%u -> %ux%u @ %d fps", sw, sh, dw, dh, k_capture_fps);
    return true;
#endif
}

void video_writer_t::stop() {
    if (!active() && !writer) {
        return;
    }

    stopping.store(true, std::memory_order_release);

    {
        std::lock_guard<std::mutex> lock(queue_mu);
        if (!filled.empty() && !pump_scheduled.exchange(true, std::memory_order_acq_rel)) {
            game.mtrpc.detach_task([this]() {
                pump();
            });
        }
    }

    {
        std::unique_lock<std::mutex> lock(queue_mu);
        idle_cv.wait(lock, [this] {
            return is_idle_unlocked();
        });

        MovieWriter *mw = writer;
        writer = nullptr;
        const unsigned enc = encoded;
        const unsigned drop = dropped;
        free_resources_unlocked();
        active_flag.store(false, std::memory_order_release);
        stopping.store(false, std::memory_order_release);
        lock.unlock();

        delete mw;
        logs::info("VideoCapture: stopped (%u encoded, %u dropped)", enc, drop);
        logs::flush();
    }
}

void video_writer_t::on_frame_end() {
#ifndef GAME_HAS_VIDEO_RECORDING
    return;
#else
    if (!active() || stopping.load(std::memory_order_acquire)) {
        return;
    }

    const unsigned sw = (unsigned)screen_width();
    const unsigned sh = (unsigned)screen_height();
    if (sw != src_w || sh != src_h) {
        ++dropped;
        return;
    }

    const time_millis now = time_get_millis();
    constexpr time_millis interval_ms = 1000 / k_capture_fps;
    if (last_capture_ms != 0 && (now - last_capture_ms) < interval_ms) {
        return;
    }

    int slot = -1;
    {
        std::lock_guard<std::mutex> lock(queue_mu);
        if (stopping.load(std::memory_order_acquire)) {
            return;
        }
        slot = claim_free_slot_unlocked();
        if (slot < 0) {
            ++dropped;
            return;
        }
    }

    last_capture_ms = now;

    ::painter ctx = game.painter();
    if (!g_render.save_screen_buffer(ctx, slots[slot].data(), 0, 0, (int)sw, (int)sh, (int)sw)) {
        logs::error("VideoCapture: save_screen_buffer failed");
        last_capture_ms = 0;
        std::lock_guard<std::mutex> lock(queue_mu);
        recycle_slot_unlocked(slot);
        return;
    }

    {
        std::lock_guard<std::mutex> lock(queue_mu);
        if (stopping.load(std::memory_order_acquire)) {
            recycle_slot_unlocked(slot);
            return;
        }
        filled.push(slot);
    }

    if (!pump_scheduled.exchange(true, std::memory_order_acq_rel)) {
        game.mtrpc.detach_task([this]() {
            pump();
        });
    }
#endif
}

bool __video_capture_active() {
    return xvalue<video_writer_t>::ref().active();
}
ANK_FUNCTION(__video_capture_active)

ANK_SCRIPT_EVENT(event_video_capture_toggle, reserved)

void ANK_REGISTER_APPLICATION_MODULE(register_video_capture_module) {
    auto &writer = xvalue<video_writer_t>::ref();
    writer.register_callbacks();
}
