#include "city/city_figures_chunks.h"

#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure_save.h"
#include "io/io_buffer.h"

void figures_chunk::bind_data(io_buffer* iob, size_t version) {
    city_figures().init_figures();
    for (int i = 0; i < MAX_FIGURES; i++) {
        bind_versioned<figure_save>(*figure_get(i), iob);
        figure_get(i)->id = i;
    }
}

void figure_sequence_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(4);
    // iob->bind(BIND_SIGNATURE_INT32, &g_figure_data.created_sequence);
}

void city_figures_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &city_figures().fish_number);
    iob->bind(BIND_SIGNATURE_INT32, &city_figures().rioters);
    iob->bind(BIND_SIGNATURE_UINT8, &city_figures().animals_number);
    iob->bind(BIND_SIGNATURE_INT32, &city_figures().security_breach_duration);
    iob->bind(BIND_SIGNATURE_INT16, &city_figures().enemies);
    iob->bind(BIND_SIGNATURE_UINT16, &city_figures().kingdome_soldiers);
    iob->bind(BIND_SIGNATURE_INT32, &city_figures().soldiers);
    iob->bind(BIND_SIGNATURE_INT32, &city_figures().attacking_natives);
    verify_no_crash(iob->get_offset() == city_figures_chunk::size);
}
