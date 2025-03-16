#include "list.h"

#include "io/io_buffer.h"

#define MAX_SMALL 2500
#define MAX_LARGE 10000

io_buffer* iob_building_list_small = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind____skip(5000);
});

io_buffer* iob_building_list_large = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind____skip(20000);
});