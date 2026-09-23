#include "graphics/residency_atlas.h"

#include "platform/renderer.h"
#include "game/game.h"
#include "game/game_config.h"
#include "content/file_formats.h"
#include "core/log.h"
#include "dev/debug.h"

#include <SDL.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace res_atlas {

namespace detail {
bool g_enabled = false;
bool g_redirect = false;
}

namespace {

bool &g_enabled = detail::g_enabled;
bool &g_redirect = detail::g_redirect;

constexpr int DEFAULT_SIZE = 8192;
constexpr int MIN_SIZE = 1024;
constexpr int PADDING = 1;
constexpr int PREVIEW_MAX_DIM = 512;

struct key_t {
    SDL_Texture *tex;
    int ox, oy, w, h;
    bool operator==(const key_t &o) const {
        return tex == o.tex && ox == o.ox && oy == o.oy && w == o.w && h == o.h;
    }
};

struct key_hash {
    size_t operator()(const key_t &k) const {
        size_t h = std::hash<const void *>()(k.tex);
        auto mix = [&](int v) { h ^= (size_t)(uint32_t)v * 0x9e3779b1u + (h << 6) + (h >> 2); };
        mix(k.ox);
        mix(k.oy);
        mix(k.w);
        mix(k.h);
        return h;
    }
};

struct slot_t {
    int x, y, w, h;
    bool ready;
};

struct blit_t {
    SDL_Texture *src;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
};

struct skyline_node {
    int x, y, width;
};

bool g_preview = false;
bool g_handler_registered = false;
bool g_page_linear = false;
bool g_page_alloc_failed = false;
int g_max_sprite_width = 512;

SDL_Texture *g_atlas = nullptr;
int g_atlas_w = 0;
int g_atlas_h = 0;
int g_wanted_size = DEFAULT_SIZE;

std::unordered_map<key_t, slot_t, key_hash> g_slots;
std::unordered_set<const void *> g_sources;
std::unordered_set<const void *> g_packed_sources;
std::vector<blit_t> g_pending;
std::vector<skyline_node> g_skyline;

int g_distinct = 0;
int64_t g_used_area = 0;
int g_no_room = 0;
int64_t g_no_room_area = 0;

std::atomic<uint32_t> g_cnt_hit{0};
std::atomic<uint32_t> g_cnt_miss{0};
std::atomic<uint32_t> g_cnt_filter{0};
std::atomic<uint32_t> g_cnt_unregistered{0};
std::atomic<uint32_t> g_cnt_too_wide{0};
uint32_t g_last_hit = 0;
uint32_t g_last_miss = 0;
uint32_t g_last_filter = 0;
uint32_t g_last_unregistered = 0;
uint32_t g_last_too_wide = 0;
uint32_t g_last_requests = 0;
double g_last_frame_ms = 0.0;

std::mutex &buffers_mutex() {
    static std::mutex *m = new std::mutex();
    return *m;
}

struct tls_requests {
    std::unordered_set<key_t, key_hash> keys;

    tls_requests() {
        std::lock_guard<std::mutex> lock(buffers_mutex());
        buffers().push_back(this);
    }

    ~tls_requests() {
        std::lock_guard<std::mutex> lock(buffers_mutex());
        std::vector<tls_requests *> &all = buffers();
        all.erase(std::remove(all.begin(), all.end(), this), all.end());
    }

    static std::vector<tls_requests *> &buffers() {
        static std::vector<tls_requests *> *instances = new std::vector<tls_requests *>();
        return *instances;
    }
};

tls_requests &requests() {
    thread_local tls_requests tls;
    return tls;
}

bool skyline_fit(int index, int w, int h, int &out_y) {
    const int x = g_skyline[index].x;
    if (x + w > g_atlas_w) {
        return false;
    }
    int width_left = w;
    int i = index;
    int y = 0;
    while (width_left > 0) {
        if (i >= (int)g_skyline.size()) {
            return false;
        }
        y = std::max(y, g_skyline[i].y);
        if (y + h > g_atlas_h) {
            return false;
        }
        width_left -= g_skyline[i].width;
        ++i;
    }
    out_y = y;
    return true;
}

void skyline_add(int index, int x, int y, int w, int h) {
    g_skyline.insert(g_skyline.begin() + index, skyline_node{x, y + h, w});

    for (size_t i = index + 1; i < g_skyline.size();) {
        skyline_node &cur = g_skyline[i];
        const skyline_node &prev = g_skyline[i - 1];
        if (cur.x < prev.x + prev.width) {
            const int shrink = prev.x + prev.width - cur.x;
            cur.x += shrink;
            cur.width -= shrink;
            if (cur.width <= 0) {
                g_skyline.erase(g_skyline.begin() + i);
                continue;
            }
        }
        break;
    }

    for (size_t i = 0; i + 1 < g_skyline.size();) {
        if (g_skyline[i].y == g_skyline[i + 1].y) {
            g_skyline[i].width += g_skyline[i + 1].width;
            g_skyline.erase(g_skyline.begin() + i + 1);
        } else {
            ++i;
        }
    }
}

bool pack(int w, int h, int &rx, int &ry) {
    int best_bottom = INT32_MAX;
    int best_width = INT32_MAX;
    int best_index = -1;
    int best_x = 0, best_y = 0;
    for (int i = 0; i < (int)g_skyline.size(); ++i) {
        int y = 0;
        if (skyline_fit(i, w, h, y)) {
            if (y + h < best_bottom || (y + h == best_bottom && g_skyline[i].width < best_width)) {
                best_bottom = y + h;
                best_width = g_skyline[i].width;
                best_index = i;
                best_x = g_skyline[i].x;
                best_y = y;
            }
        }
    }
    if (best_index < 0) {
        return false;
    }
    skyline_add(best_index, best_x, best_y, w, h);
    rx = best_x;
    ry = best_y;
    return true;
}

int skyline_peak() {
    int peak = 0;
    for (const skyline_node &n : g_skyline) {
        peak = std::max(peak, n.y);
    }
    return peak;
}

struct draw_blend_guard {
    SDL_Renderer *r;
    SDL_BlendMode prev = SDL_BLENDMODE_BLEND;

    explicit draw_blend_guard(SDL_Renderer *renderer) : r(renderer) {
        SDL_GetRenderDrawBlendMode(r, &prev);
    }
    ~draw_blend_guard() {
        SDL_SetRenderDrawBlendMode(r, prev);
    }
};

void clear_atlas() {
    SDL_Renderer *r = g_render.renderer();
    draw_blend_guard blend_guard(r);
    SDL_Texture *prev = SDL_GetRenderTarget(r);
    SDL_Rect vp;
    SDL_RenderGetViewport(r, &vp);
    SDL_SetRenderTarget(r, g_atlas);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    SDL_RenderClear(r);
    SDL_SetRenderTarget(r, prev);
    SDL_RenderSetViewport(r, &vp);
}

void flush_pending() {
    if (g_pending.empty()) {
        return;
    }
    SDL_Renderer *r = g_render.renderer();
    draw_blend_guard blend_guard(r);
    SDL_Texture *prev = SDL_GetRenderTarget(r);
    SDL_Rect prev_vp;
    SDL_RenderGetViewport(r, &prev_vp);
    const SDL_bool had_clip = SDL_RenderIsClipEnabled(r);
    SDL_Rect prev_clip{};
    if (had_clip) {
        SDL_RenderGetClipRect(r, &prev_clip);
    }
    SDL_RenderSetClipRect(r, nullptr);
    SDL_SetRenderTarget(r, g_atlas);
    SDL_RenderSetViewport(r, nullptr);

    const bool can_scale_mode = g_render.has_texture_scale_mode();

    for (const blit_t &b : g_pending) {
        SDL_BlendMode old_mode = SDL_BLENDMODE_BLEND;
        SDL_GetTextureBlendMode(b.src, &old_mode);
        Uint8 old_r = 255, old_g = 255, old_b = 255, old_a = 255;
        SDL_GetTextureColorMod(b.src, &old_r, &old_g, &old_b);
        SDL_GetTextureAlphaMod(b.src, &old_a);
        SDL_ScaleMode old_scale = SDL_ScaleModeNearest;
        if (can_scale_mode) {
            SDL_GetTextureScaleMode(b.src, &old_scale);
            SDL_SetTextureScaleMode(b.src, SDL_ScaleModeNearest);
        }

        SDL_SetTextureBlendMode(b.src, SDL_BLENDMODE_NONE);
        SDL_SetTextureColorMod(b.src, 255, 255, 255);
        SDL_SetTextureAlphaMod(b.src, 255);
        SDL_RenderCopy(r, b.src, &b.srcrect, &b.dstrect);

        SDL_SetTextureBlendMode(b.src, old_mode);
        SDL_SetTextureColorMod(b.src, old_r, old_g, old_b);
        SDL_SetTextureAlphaMod(b.src, old_a);
        if (can_scale_mode) {
            SDL_SetTextureScaleMode(b.src, old_scale);
        }
    }
    g_pending.clear();

    SDL_SetRenderTarget(r, prev);
    SDL_RenderSetViewport(r, &prev_vp);
    SDL_RenderSetClipRect(r, had_clip ? &prev_clip : nullptr);
}

void draw_preview() {
    SDL_Renderer *r = g_render.renderer();
    draw_blend_guard blend_guard(r);
    const SDL_bool had_clip = SDL_RenderIsClipEnabled(r);
    SDL_Rect prev_clip{};
    if (had_clip) {
        SDL_RenderGetClipRect(r, &prev_clip);
    }
    SDL_Rect prev_vp;
    SDL_RenderGetViewport(r, &prev_vp);
    SDL_RenderSetClipRect(r, nullptr);
    SDL_RenderSetViewport(r, nullptr);

    const float scale = (float)PREVIEW_MAX_DIM / (float)std::max(g_atlas_w, g_atlas_h);
    const int margin = 10;
    SDL_Rect dst{margin, margin, (int)(g_atlas_w * scale), (int)(g_atlas_h * scale)};
    SDL_Rect frame{dst.x - 2, dst.y - 2, dst.w + 4, dst.h + 4};

    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 210);
    SDL_RenderFillRect(r, &frame);

    SDL_SetTextureBlendMode(g_atlas, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(g_atlas, 255, 255, 255);
    SDL_SetTextureAlphaMod(g_atlas, 255);
    SDL_RenderCopy(r, g_atlas, nullptr, &dst);

    const int peak_y = dst.y + (int)(skyline_peak() * scale);
    SDL_SetRenderDrawColor(r, 255, 80, 80, 255);
    SDL_RenderDrawLine(r, dst.x, peak_y, dst.x + dst.w, peak_y);

    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    SDL_RenderDrawRect(r, &frame);

    SDL_RenderSetViewport(r, &prev_vp);
    SDL_RenderSetClipRect(r, had_clip ? &prev_clip : nullptr);
}

void drop_contents() {
    if (g_atlas) {
        SDL_DestroyTexture(g_atlas);
        g_atlas = nullptr;
    }
    g_atlas_w = g_atlas_h = 0;
    g_page_alloc_failed = false;
    g_slots.clear();
    g_packed_sources.clear();
    g_pending.clear();
    g_skyline.clear();
    g_distinct = 0;
    g_used_area = 0;
    g_no_room = 0;
    g_no_room_area = 0;

    std::lock_guard<std::mutex> lock(buffers_mutex());
    for (tls_requests *b : tls_requests::buffers()) {
        b->keys.clear();
    }
}

int clamp_size(int size) {
    if (size <= 0) {
        size = DEFAULT_SIZE;
    }
    size = std::max(size, MIN_SIZE);
    const vec2i maxsz = g_render.get_max_image_size();
    if (maxsz.x > 0) {
        size = std::min(size, maxsz.x);
    }
    if (maxsz.y > 0) {
        size = std::min(size, maxsz.y);
    }
    return size;
}

std::mutex g_registry_mutex;
std::vector<std::pair<SDL_Texture *, bool>> g_registry_queue;
std::atomic<bool> g_registry_dirty{false};

void apply_forget(SDL_Texture *tex) {
    g_sources.erase(tex);

    for (auto it = g_slots.begin(); it != g_slots.end();) {
        if (it->first.tex == tex) {
            it = g_slots.erase(it);
        } else {
            ++it;
        }
    }
    g_pending.erase(std::remove_if(g_pending.begin(), g_pending.end(), [tex](const blit_t &b) { return b.src == tex; }),
                    g_pending.end());
    g_packed_sources.erase(tex);

    std::lock_guard<std::mutex> lock(buffers_mutex());
    for (tls_requests *b : tls_requests::buffers()) {
        for (auto it = b->keys.begin(); it != b->keys.end();) {
            if (it->tex == tex) {
                it = b->keys.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void apply_registry_changes() {
    if (!g_registry_dirty.load(std::memory_order_acquire)) {
        return;
    }
    std::vector<std::pair<SDL_Texture *, bool>> queue;
    {
        std::lock_guard<std::mutex> lock(g_registry_mutex);
        queue.swap(g_registry_queue);
        g_registry_dirty.store(false, std::memory_order_release);
    }

    bool forgot_any = false;
    for (const auto &entry : queue) {
        if (entry.second) {
            g_sources.insert(entry.first);
        } else {
            apply_forget(entry.first);
            forgot_any = true;
        }
    }

    if (forgot_any && g_sources.empty()) {
        drop_contents();
        logs::info("residency_atlas: all sources unloaded, atlas content reset");
    }
}

bool ensure_page() {
    if (g_atlas) {
        return true;
    }
    if (g_page_alloc_failed) {
        return false;
    }
    SDL_Renderer *r = g_render.renderer();
    for (int size = clamp_size(g_wanted_size); size >= MIN_SIZE; size /= 2) {
        g_atlas = SDL_CreateTexture(r, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, size, size);
        if (!g_atlas) {
            logs::warn("residency_atlas: driver rejected a %dx%d target texture (%s), trying %dx%d", size, size,
                       SDL_GetError(), size / 2, size / 2);
            continue;
        }
        SDL_SetTextureBlendMode(g_atlas, SDL_BLENDMODE_BLEND);
        g_render.set_texture_scale_mode(g_atlas, 1.0f, g_page_linear);
        g_atlas_w = g_atlas_h = size;
        g_wanted_size = size;
        g_skyline.clear();
        g_skyline.push_back(skyline_node{0, 0, size});
        clear_atlas();
        logs::info("residency_atlas: page allocated %dx%d (%s, %lld MiB)", size, size,
                   g_page_linear ? "linear" : "nearest", (long long)((int64_t)size * size * 4 / (1024 * 1024)));
        return true;
    }

    logs::error("residency_atlas: no usable atlas size down to %dx%d, disabling: %s", MIN_SIZE, MIN_SIZE,
                SDL_GetError());
    g_page_alloc_failed = true;
    g_enabled = false;
    g_redirect = false;
    return false;
}

std::vector<key_t> g_batch;

void collect_requests() {
    g_batch.clear();
    {
        std::lock_guard<std::mutex> lock(buffers_mutex());
        for (tls_requests *b : tls_requests::buffers()) {
            g_batch.insert(g_batch.end(), b->keys.begin(), b->keys.end());
            b->keys.clear();
        }
    }
    std::sort(g_batch.begin(), g_batch.end(), [](const key_t &a, const key_t &b) {
        if (a.tex != b.tex) {
            return std::less<const void *>()(a.tex, b.tex);
        }
        if (a.ox != b.ox) {
            return a.ox < b.ox;
        }
        if (a.oy != b.oy) {
            return a.oy < b.oy;
        }
        if (a.w != b.w) {
            return a.w < b.w;
        }
        return a.h < b.h;
    });
    g_batch.erase(std::unique(g_batch.begin(), g_batch.end()), g_batch.end());
}

void process_requests() {
    collect_requests();
    g_last_requests = (uint32_t)g_batch.size();
    if (g_batch.empty()) {
        return;
    }
    if (!ensure_page()) {
        g_batch.clear();
        return;
    }

    std::sort(g_batch.begin(), g_batch.end(), [](const key_t &a, const key_t &b) { return a.h > b.h; });

    for (const key_t &k : g_batch) {
        if (g_slots.find(k) != g_slots.end()) {
            continue;
        }
        int rx = 0, ry = 0;
        if (pack(k.w + PADDING, k.h + PADDING, rx, ry)) {
            g_slots.emplace(k, slot_t{rx, ry, k.w, k.h, true});
            g_packed_sources.insert(k.tex);
            ++g_distinct;
            g_used_area += (int64_t)k.w * k.h;
            g_pending.push_back(blit_t{k.tex, {k.ox, k.oy, k.w, k.h}, {rx, ry, k.w, k.h}});
        } else {
            g_slots.emplace(k, slot_t{0, 0, k.w, k.h, false});
            ++g_no_room;
            g_no_room_area += (int64_t)k.w * k.h;
        }
    }
    g_batch.clear();
}

void snapshot_counters() {
    g_last_hit = g_cnt_hit.exchange(0, std::memory_order_relaxed);
    g_last_miss = g_cnt_miss.exchange(0, std::memory_order_relaxed);
    g_last_filter = g_cnt_filter.exchange(0, std::memory_order_relaxed);
    g_last_unregistered = g_cnt_unregistered.exchange(0, std::memory_order_relaxed);
    g_last_too_wide = g_cnt_too_wide.exchange(0, std::memory_order_relaxed);
}

}

bool resolve(SDL_Texture *src, vec2i offset, vec2i size, bool want_linear, SDL_Texture *&out_tex, SDL_Rect &out_src) {
    if (!g_enabled || src == nullptr) {
        return false;
    }
    if (g_registry_dirty.load(std::memory_order_acquire)) {
        return false;
    }
    if (offset.x < 0 || offset.y < 0 || size.x <= 0 || size.y <= 0) {
        return false;
    }
    if (size.x > g_max_sprite_width) {
        g_cnt_too_wide.fetch_add(1, std::memory_order_relaxed);
        return false;
    }
    if (want_linear != g_page_linear) {
        g_cnt_filter.fetch_add(1, std::memory_order_relaxed);
        return false;
    }
    if (g_sources.find(src) == g_sources.end()) {
        g_cnt_unregistered.fetch_add(1, std::memory_order_relaxed);
        return false;
    }

    const key_t k{src, offset.x, offset.y, size.x, size.y};

    if (g_atlas == nullptr) {
        requests().keys.insert(k);
        g_cnt_miss.fetch_add(1, std::memory_order_relaxed);
        return false;
    }

    auto it = g_slots.find(k);
    if (it == g_slots.end()) {
        requests().keys.insert(k);
        g_cnt_miss.fetch_add(1, std::memory_order_relaxed);
        return false;
    }
    if (!it->second.ready) {
        g_cnt_miss.fetch_add(1, std::memory_order_relaxed);
        return false;
    }

    out_tex = g_atlas;
    out_src = SDL_Rect{it->second.x, it->second.y, it->second.w, it->second.h};
    g_cnt_hit.fetch_add(1, std::memory_order_relaxed);
    return true;
}

void register_source(SDL_Texture *tex) {
    if (!tex) {
        return;
    }
    std::lock_guard<std::mutex> lock(g_registry_mutex);
    g_registry_queue.emplace_back(tex, true);
    g_registry_dirty.store(true, std::memory_order_release);
}

void forget_source(SDL_Texture *tex) {
    if (!tex) {
        return;
    }
    std::lock_guard<std::mutex> lock(g_registry_mutex);
    g_registry_queue.emplace_back(tex, false);
    g_registry_dirty.store(true, std::memory_order_release);
}

void enable(int size) {
    if (size <= 0) {
        size = game_features::graphics_atlas_page_size.to_int();
    }
    const int wanted = clamp_size(size);
    if (g_atlas && g_atlas_w != wanted) {
        drop_contents();
    }
    g_wanted_size = wanted;

    const int max_width = game_features::graphics_atlas_max_sprite_width.to_int();
    if (max_width > 0 && max_width != g_max_sprite_width) {
        g_max_sprite_width = max_width;
        drop_contents();
    }

    g_page_alloc_failed = false;
    g_enabled = true;
    if (!g_handler_registered) {
        game.add_frame_pre_present_handler([]() { res_atlas::frame_pre_present(); });
        g_handler_registered = true;
    }
    logs::info("residency_atlas: recording enabled (page %dx%d allocated on demand, sprites wider than %d px excluded)",
               wanted, wanted, g_max_sprite_width);
}

void disable() {
    g_enabled = false;
    g_redirect = false;
    logs::info("residency_atlas: recording stopped, redirect off (data kept)");
}

void reset() {
    g_redirect = false;
    drop_contents();
    snapshot_counters();
    g_last_requests = 0;
}

void invalidate() {
    if (!g_atlas && g_slots.empty()) {
        return;
    }
    drop_contents();
    logs::info("residency_atlas: atlas invalidated, will repack");
}

void set_preview(bool on) {
    g_preview = on;
}

void set_render(bool on) {
    g_redirect = on;
    if (on && !g_enabled) {
        enable(0);
    }
}

void set_page_linear(bool linear) {
    if (g_page_linear == linear) {
        return;
    }
    g_page_linear = linear;
    drop_contents();
}

bool page_linear() {
    return g_page_linear;
}

void frame_pre_present() {
    const Uint64 t0 = SDL_GetPerformanceCounter();

    apply_registry_changes();
    if (g_enabled || g_atlas) {
        if (g_enabled) {
            process_requests();
        }
        flush_pending();
    }

    const Uint64 t1 = SDL_GetPerformanceCounter();
    const Uint64 freq = SDL_GetPerformanceFrequency();
    g_last_frame_ms = freq ? (double)(t1 - t0) * 1000.0 / (double)freq : 0.0;

    if (g_enabled && g_preview && g_atlas) {
        draw_preview();
    }
    if (g_enabled || g_atlas) {
        snapshot_counters();
    }
}

double fill_percent() {
    if (!g_atlas) {
        return 0.0;
    }
    const int64_t total = (int64_t)g_atlas_w * g_atlas_h;
    return total > 0 ? 100.0 * (double)g_used_area / (double)total : 0.0;
}

double frame_time_ms() {
    return g_last_frame_ms;
}

void log_stats() {
    if (!g_enabled && !g_atlas) {
        logs::info("residency_atlas: not enabled");
        return;
    }
    logs::info("residency_atlas: recording=%s redirect=%s filter=%s max_sprite_width=%d", g_enabled ? "on" : "off",
               g_redirect ? "on" : "off", g_page_linear ? "linear" : "nearest", g_max_sprite_width);
    if (!g_atlas) {
        logs::info("residency_atlas: page %dx%d not allocated yet (%u requests pending)", g_wanted_size, g_wanted_size,
                   g_last_requests);
        return;
    }

    const int peak = skyline_peak();
    const int64_t total = (int64_t)g_atlas_w * g_atlas_h;
    const int64_t bbox = (int64_t)g_atlas_w * peak;
    const double coverage = 100.0 * (double)g_used_area / (double)total;
    const double peak_pct = 100.0 * (double)peak / (double)g_atlas_h;
    const double pack_eff = bbox > 0 ? 100.0 * (double)g_used_area / (double)bbox : 0.0;
    logs::info("residency_atlas %dx%d: distinct=%d from %d source textures (%d registered) | placed area=%lld px "
               "(%.2f%% of atlas) | skyline peak=%d px (%.1f%% height, %.1f%% packing efficiency) | no_room=%d imgs / "
               "%lld px | VRAM=%lld MiB",
               g_atlas_w, g_atlas_h, g_distinct, (int)g_packed_sources.size(), (int)g_sources.size(),
               (long long)g_used_area, coverage, peak, peak_pct, pack_eff, g_no_room, (long long)g_no_room_area,
               (long long)(total * 4 / (1024 * 1024)));
    logs::info("residency_atlas last frame: resident=%u | from source=%u | filter mismatch=%u | unregistered=%u | "
               "too wide=%u | distinct requests=%u",
               g_last_hit, g_last_miss, g_last_filter, g_last_unregistered, g_last_too_wide, g_last_requests);
}

void dump(const char *filename) {
    if (!g_atlas) {
        logs::info("residency_atlas: nothing to dump");
        return;
    }
    const bool ok = g_render.save_texture_to_file(filename, g_atlas, FILE_FORMAT_PNG);
    logs::info("residency_atlas: dumped '%s' -> %s", filename, ok ? "ok" : "FAILED");
    log_stats();
}

}

declare_console_command_p(residency_atlas) {
    const bstring128 sub = args.next_str();
    if (sub == "on") {
        res_atlas::enable(args.next_int(0));
        res_atlas::set_preview(true);
        out.println("residency_atlas: recording on, preview on");
    } else if (sub == "off") {
        res_atlas::disable();
        res_atlas::set_preview(false);
        out.println("residency_atlas: recording off, redirect off, preview off");
    } else if (sub == "reset") {
        res_atlas::reset();
        out.println("residency_atlas: reset");
    } else if (sub == "render") {
        const bool on = (args.next_str() == "on");
        res_atlas::set_render(on);
        out.printf("residency_atlas: render %s\n", on ? "on (recording forced on)" : "off");
    } else if (sub == "filter") {
        const bstring128 v = args.next_str();
        if (v != "linear" && v != "nearest") {
            out.println("usage: residency_atlas filter nearest|linear");
            return;
        }
        res_atlas::set_page_linear(v == "linear");
        out.printf("residency_atlas: filter %s (atlas repacked)\n", v);
    } else if (sub == "preview") {
        const bool on = (args.next_str() != "off");
        res_atlas::set_preview(on);
        out.printf("residency_atlas: preview %s\n", on ? "on" : "off");
    } else if (sub == "stats") {
        res_atlas::log_stats();
        out.println("residency_atlas: stats written to log");
    } else if (sub == "dump") {
        bstring256 fn;
        if (!args.next(fn)) {
            fn = "residency_atlas.png";
        }
        res_atlas::dump(fn.c_str());
        out.printf("residency_atlas: dumped to %s\n", fn);
    } else {
        out.println("usage: residency_atlas on [size] | off | render on|off | filter nearest|linear | preview [on|off] | "
                    "stats | dump [file] | reset");
    }
}
