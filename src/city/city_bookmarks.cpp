#include "city/city_bookmarks.h"

#include "city/city_bookmarks_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"

map_bookmarks_t& city_bookmarks() {
    return xvalue<map_bookmarks_t>::ref();
}

class bookmarks_system : public sim_system {
public:
    const char* name() const override { return "bookmarks"; }
    void on_reset() override { city_bookmarks().reset(); }
    void push_save_sections(int file_version) override { g_chunk_io.push_chunk<bookmarks_chunk>(32, false); }
};

void ANK_REGISTER_APPLICATION_MODULE(register_bookmarks_system) {
    static bookmarks_system system;
    g_simulation.register_system(&system);
}

void map_bookmarks_t::reset(void) {
    for (auto& b : points) {
        b = tile2i::invalid;
    }
}

void map_bookmarks_t::set(int i, tile2i tile) {
    if (i >= 0 && i < MAX_BOOKMARKS) {
        points[i] = tile;
    }
}

tile2i map_bookmarks_t::get(int i) {
    if (i >= 0 && i < MAX_BOOKMARKS) {
        return points[i];
    }
    return tile2i::invalid;
}