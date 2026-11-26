#include "io/save_layout.h"

#include "io/io_buffer.h"

#include <array>
#include <cstring>

save_layout_entry* save_layout_entry::first = nullptr;

save_layout_entry::save_layout_entry(const char* n, uint16_t c) : name(n), current(c), next(first) {
    first = this;
}

namespace {
    struct file_layout {
        char name[save_layouts_chunk::NAME_LEN];
        uint16_t layout;
    };
    std::array<file_layout, save_layouts_chunk::MAX_ENTRIES> g_file_layouts;
    int g_file_layouts_count = 0;
} // namespace

namespace save_layouts {
    void clear() {
        g_file_layouts_count = 0;
    }

    void set(const char* name, uint16_t layout) {
        if (g_file_layouts_count >= save_layouts_chunk::MAX_ENTRIES) {
            return;
        }
        file_layout& e = g_file_layouts[g_file_layouts_count++];
        strncpy(e.name, name, save_layouts_chunk::NAME_LEN - 1);
        e.name[save_layouts_chunk::NAME_LEN - 1] = 0;
        e.layout = layout;
    }

    int find(const char* name) {
        for (int i = 0; i < g_file_layouts_count; i++) {
            if (strcmp(g_file_layouts[i].name, name) == 0) {
                return g_file_layouts[i].layout;
            }
        }
        return 0;
    }
} // namespace save_layouts

void save_layouts_chunk::bind_data(io_buffer* iob) {
    if (iob->is_read_access()) {
        save_layouts::clear();
        int32_t count = 0;
        iob->bind_i32(count);
        for (int i = 0; i < MAX_ENTRIES; i++) {
            char name[NAME_LEN] = {};
            uint16_t layout = 0;
            iob->bind(BIND_SIGNATURE_RAW, name, NAME_LEN);
            iob->bind_u16(layout);
            if (i < count) {
                name[NAME_LEN - 1] = 0;
                save_layouts::set(name, layout);
            }
        }
        return;
    }

    std::array<save_layout_entry*, MAX_ENTRIES> entries = {};
    int32_t count = 0;
    for (save_layout_entry* e = save_layout_entry::first; e && count < MAX_ENTRIES; e = e->next) {
        entries[count++] = e;
    }
    iob->bind_i32(count);
    for (int i = 0; i < MAX_ENTRIES; i++) {
        char name[NAME_LEN] = {};
        uint16_t layout = 0;
        if (i < count) {
            strncpy(name, entries[i]->name, NAME_LEN - 1);
            layout = entries[i]->current;
        }
        iob->bind(BIND_SIGNATURE_RAW, name, NAME_LEN);
        iob->bind_u16(layout);
    }
}

void save_layouts_chunk::load_defaults() {
    save_layouts::clear();
}
