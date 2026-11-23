#include "city/city_figures_chunks.h"

#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure_save.h"
#include "io/io_buffer.h"

void figures_chunk::bind_data(io_buffer* iob, size_t version) {
    g_city.figures.init_figures();
    for (int i = 0; i < MAX_FIGURES; i++) {
        bind_versioned<figure_save>(*figure_get(i), iob, (int)version);
        figure_get(i)->id = i;
    }
}

void figures_chunk::reset() {
    stub_records_guard_reset();
    g_city.figures.init_figures();
}

void figure_sequence_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(4);
    // iob->bind(BIND_SIGNATURE_INT32, &g_figure_data.created_sequence);
}

void city_figures_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_UINT8, &data.figures.fish_number);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.rioters);
    iob->bind(BIND_SIGNATURE_UINT8, &data.figures.animals_number);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.security_breach_duration);
    iob->bind(BIND_SIGNATURE_INT16, &data.figures.enemies);
    iob->bind(BIND_SIGNATURE_UINT16, &data.figures.kingdome_soldiers);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.soldiers);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.attacking_natives);
    verify_no_crash(iob->get_offset() == city_figures_chunk::size);
}
