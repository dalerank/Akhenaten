#include "list.h"

#include "io/io_buffer.h"
#include "core/buffer.h"
#include "core/custom_span.hpp"
#include "core/svector.h"
#include <string.h>

#define MAX_SMALL 2500
#define MAX_LARGE 10000

struct list_data_t {
    struct {
        int size;
        int items[MAX_SMALL];
    } small;
    struct {
        int size;
        int items[MAX_LARGE];
    } large;

    svector<uint16_t, 2500> burning;
};

list_data_t g_list_data;

void building_list_small_clear(void) {
    auto& data = g_list_data;
    data.small.size = 0;
}

void building_list_small_add(int building_id) {
    auto& data = g_list_data;
    data.small.items[data.small.size++] = building_id;
    if (data.small.size >= MAX_SMALL)
        data.small.size = MAX_SMALL - 1;
}

int building_list_small_size(void) {
    auto& data = g_list_data;
    return data.small.size;
}

const int* building_list_small_items(void) {
    auto& data = g_list_data;
    return data.small.items;
}

void building_list_large_clear(int clear_entries) {
    auto& data = g_list_data;
    data.large.size = 0;
    if (clear_entries)
        memset(data.large.items, 0, MAX_LARGE * sizeof(int));
}

void building_list_large_add(int building_id) {
    auto& data = g_list_data;
    if (data.large.size < MAX_LARGE)
        data.large.items[data.large.size++] = building_id;
}

int building_list_large_size() {
    auto& data = g_list_data;
    return data.large.size;
}

const int* building_list_large_items() {
    auto& data = g_list_data;
    return data.large.items;
}

void building_list_burning_clear() {
    auto& data = g_list_data;
    data.burning.clear();
}

void building_list_burning_add(int building_id) {
    auto& data = g_list_data;
    data.burning.push_back(building_id);
}

custom_span<uint16_t> building_list_burning_items() {
    auto& data = g_list_data;
    return make_span(data.burning.data(), data.burning.size());
}

io_buffer* iob_building_list_small = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_list_data;
    for (int i = 0; i < MAX_SMALL; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.small.items[i]);
    }
});

io_buffer* iob_building_list_large = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_list_data;
    for (int i = 0; i < MAX_LARGE; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.large.items[i]);
    }
});

io_buffer* iob_building_list_burning = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_list_data;
    for (int i = 0; i < data.burning.capacity(); i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.burning[i]);
    }
});

io_buffer* iob_building_burning_list_info = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_list_data;
    uint32_t total = data.burning.capacity();
    uint32_t size = data.burning.size();
    iob->bind(BIND_SIGNATURE_UINT32, &total);
    iob->bind(BIND_SIGNATURE_UINT32, &size);

    data.burning.resize(size);
});