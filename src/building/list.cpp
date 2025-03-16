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
        int items[MAX_LARGE];
    } large;
};

list_data_t g_list_data;

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

io_buffer* iob_building_list_small = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_list_data;
    for (int i = 0; i < MAX_SMALL; i++) {
        int16_t tmp;
        iob->bind(BIND_SIGNATURE_INT16, &tmp);
    }
});

io_buffer* iob_building_list_large = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_list_data;
    for (int i = 0; i < MAX_LARGE; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.large.items[i]);
    }
});