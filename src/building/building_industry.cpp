#include "building/building_industry.h"

#include "io/io_buffer.h"

void building_industry::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &data.industry.ready_production);
    iob->bind(BIND_SIGNATURE_INT16, &data.industry.progress);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.spawned_worker_this_month);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.max_gatheres);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.industry.unk_b[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.has_fish);
    for (int i = 0; i < 13; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.industry.unk_c[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.produce_multiplier);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.blessing_days_left);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.has_raw_materials);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.curse_days_left);
    iob->bind(BIND_SIGNATURE_UINT16, &data.industry.progress_max);
    if (data.industry.progress_max == 0) {
        data.industry.progress_max = 400;
    }

    iob->bind____skip(1);
    for (int i = 0; i < 3; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.industry.unk_6[i]);
    }
    iob->bind(BIND_SIGNATURE_INT16, &data.industry.reserved_id_13);

    for (int i = 0; i < 40; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.industry.unk_40[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.labor_state);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.labor_days_left);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.industry.unk_12[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT16, &data.industry.work_camp_id);
    iob->bind(BIND_SIGNATURE_UINT16, &data.industry.worker_id);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.processed_figure);

    int tmp;
    iob->bind(BIND_SIGNATURE_UINT8, &tmp); // reserved for extended figure type
}

void building_industry::on_create(int orientation) {
    data.industry.progress_max = 400;
}
