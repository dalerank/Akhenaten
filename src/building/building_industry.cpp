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
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.second_material_id);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.curse_days_left);
    iob->bind(BIND_SIGNATURE_UINT16, &data.industry.stored_amount_second);
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.first_material_id);
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
    iob->bind(BIND_SIGNATURE_UINT8, &data.industry.worker_id);
}
