#include "city/city_taxes_chunks.h"

#include "city/city_taxes.h"
#include "io/io_buffer.h"

void city_taxes_chunk::bind_data(io_buffer* iob) {
    auto& taxes = city_taxes();
    iob->bind(BIND_SIGNATURE_INT32, &taxes.taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.untaxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.untaxed_nobles);
    iob->bind(BIND_SIGNATURE_INT8, &taxes.percentage_taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT8, &taxes.percentage_taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT8, &taxes.percentage_taxed_people);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.yearly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.yearly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.yearly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.yearly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.monthly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.monthly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.monthly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.monthly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.estimated_uncollected);
    iob->bind(BIND_SIGNATURE_INT32, &taxes.estimated_income);
    verify_no_crash(iob->get_offset() == city_taxes_chunk::size);
}
