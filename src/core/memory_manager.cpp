#include "core/memory_manager.h"

#include "core/log.h"
#include "dev/debug.h"

#include <algorithm>

memory_manager_t g_memory;

const char *memory_manager_t::bucket_name(e_memory_bucket bucket) {
    switch (bucket) {
    case MEMORY_PACK_TEXTURES:
        return "pack_textures";
    default:
        return "unknown";
    }
}

void memory_manager_t::alloc(e_memory_bucket bucket, int64_t bytes) {
    if (bucket >= MEMORY_BUCKET_COUNT || bytes <= 0) {
        return;
    }
    _used[bucket] += bytes;
}

void memory_manager_t::free(e_memory_bucket bucket, int64_t bytes) {
    if (bucket >= MEMORY_BUCKET_COUNT || bytes <= 0) {
        return;
    }
    _used[bucket] = std::max<int64_t>(0, _used[bucket] - bytes);
}

void memory_manager_t::set(e_memory_bucket bucket, int64_t bytes) {
    if (bucket >= MEMORY_BUCKET_COUNT) {
        return;
    }
    _used[bucket] = std::max<int64_t>(0, bytes);
}

int64_t memory_manager_t::used(e_memory_bucket bucket) const {
    if (bucket >= MEMORY_BUCKET_COUNT) {
        return 0;
    }
    return _used[bucket];
}

int64_t memory_manager_t::total() const {
    int64_t sum = 0;
    for (int i = 0; i < MEMORY_BUCKET_COUNT; ++i) {
        sum += _used[i];
    }
    return sum;
}

void memory_manager_t::track_pack_texture(pcstr name, int width, int height, bool allocate) {
    if (width <= 0 || height <= 0) {
        return;
    }
    const int64_t bytes = (int64_t)width * height * 4;
    const pcstr label = (name && *name) ? name : "unknown";

    if (allocate) {
        alloc(MEMORY_PACK_TEXTURES, bytes);
        _pack_allocs.push_back(memory_pack_alloc_t{label, width, height, bytes});
        return;
    }

    free(MEMORY_PACK_TEXTURES, bytes);
    for (auto it = _pack_allocs.rbegin(); it != _pack_allocs.rend(); ++it) {
        if (it->width == width && it->height == height && it->name == label) {
            _pack_allocs.erase(std::next(it).base());
            break;
        }
    }
}

void memory_manager_t::log() const {
    logs::info("memory: total=%.2f MiB", total() / (1024.0 * 1024.0));
    for (int i = 0; i < MEMORY_BUCKET_COUNT; ++i) {
        const auto bucket = (e_memory_bucket)i;
        logs::info("memory:   %s=%.2f MiB (%lld bytes)", memory_manager_t::bucket_name(bucket),
                   _used[i] / (1024.0 * 1024.0), (long long)_used[i]);
    }
    for (const auto &a : _pack_allocs) {
        logs::info("memory:     %s %dx%d = %.2f MiB", a.name.c_str(), a.width, a.height,
                   a.bytes / (1024.0 * 1024.0));
    }
}

declare_console_command_p(memory) {
    g_memory.log();
    out.printf("memory: total %.2f MiB, pack_textures %.2f MiB (%d allocs)\n",
               g_memory.total() / (1024.0 * 1024.0),
               g_memory.used(MEMORY_PACK_TEXTURES) / (1024.0 * 1024.0),
               (int)g_memory.pack_texture_allocs().size());
}
