#include "city/city_labor_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_labor_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_available);
    for (int i = 0; i < LABOR_CATEGORY_SAVE_SLOTS; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].workers_needed);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].workers_allocated);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].total_houses_covered);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].buildings);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].priority);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_employed);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_unemployed);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.unemployment_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.unemployment_percentage_for_goverment);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_needed);
    verify_no_crash(iob->get_offset() == city_labor_chunk::size);
}
