#include "city/city_taxes_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_taxes_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.untaxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.untaxed_nobles);
    iob->bind(BIND_SIGNATURE_INT8, &data.taxes.percentage_taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT8, &data.taxes.percentage_taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT8, &data.taxes.percentage_taxed_people);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.estimated_uncollected);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.estimated_income);
    verify_no_crash(iob->get_offset() == city_taxes_chunk::size);
}
