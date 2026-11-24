#include "city/city_labor_chunks.h"

#include "city/city_labor.h"
#include "io/io_buffer.h"

void city_labor_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& labor = city_labor();
    iob->bind(BIND_SIGNATURE_INT32, &labor.workers_available);
    for (int i = 0; i < LABOR_CATEGORY_SAVE_SLOTS; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &labor.categories[i].workers_needed);
        iob->bind(BIND_SIGNATURE_INT32, &labor.categories[i].workers_allocated);
        iob->bind(BIND_SIGNATURE_INT32, &labor.categories[i].total_houses_covered);
        iob->bind(BIND_SIGNATURE_INT32, &labor.categories[i].buildings);
        iob->bind(BIND_SIGNATURE_INT32, &labor.categories[i].priority);
    }
    iob->bind(BIND_SIGNATURE_INT32, &labor.workers_employed);
    iob->bind(BIND_SIGNATURE_INT32, &labor.workers_unemployed);
    iob->bind(BIND_SIGNATURE_INT32, &labor.unemployment_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &labor.unemployment_percentage_for_goverment);
    iob->bind(BIND_SIGNATURE_INT32, &labor.workers_needed);
    verify_no_crash(iob->get_offset() == city_labor_chunk::size);
}

void labor_storage_priority_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &city_labor().categories[LABOR_CATEGORY_STORAGE].priority);
}

void labor_storage_priority_chunk::load_defaults(size_t version) {
    // before the labor split, STORAGE had no priority of its own
    city_labor().categories[LABOR_CATEGORY_STORAGE].priority = 0;
}
