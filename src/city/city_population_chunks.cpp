#include "city/city_population_chunks.h"

#include "city/city_population.h"
#include "io/io_buffer.h"

void city_population_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &city_population().current);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().school_age);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().academy_age);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().total_capacity);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().room_in_houses);
    for (int i = 0; i < 2400; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_population().monthly.values[i]);
    }
    iob->bind(BIND_SIGNATURE_INT32, &city_population().monthly.next_index);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().monthly.count);
    for (int i = 0; i < 100; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &city_population().at_age[i]);
    }
    for (int i = 0; i < 20; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &city_population().at_level[i]);
    }
    iob->bind(BIND_SIGNATURE_INT32, &city_population().yearly_births);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().yearly_deaths);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().lost_removal);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().lost_homeless);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().last_change);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().average_per_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().total_all_years);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().people_in_shanties);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().people_in_manors);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().total_years);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().yearly_update_requested);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().last_used_house_add);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().last_used_house_remove);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().percentage_plebs);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().working_age);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().last_day_current);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().lost_troop_request);
    iob->bind(BIND_SIGNATURE_UINT16, &city_population().people_in_huts);
    iob->bind(BIND_SIGNATURE_UINT16, &city_population().people_in_residences);
    iob->bind(BIND_SIGNATURE_INT32, &city_population().highest_ever);
    verify_no_crash(iob->get_offset() == city_population_chunk::size);
}
