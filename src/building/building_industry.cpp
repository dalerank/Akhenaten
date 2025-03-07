#include "building/building_industry.h"

#include "io/io_buffer.h"
#include "core/object_property.h"

constexpr short MAX_PROGRESS_RAW = 200;
#define MAX_PROGRESS_WORKSHOP 400

void building_industry::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, &d.ready_production);
    iob->bind(BIND_SIGNATURE_INT16, &d.progress);
    iob->bind(BIND_SIGNATURE_UINT8, &d.spawned_worker_this_month);
    iob->bind(BIND_SIGNATURE_UINT8, &d.max_gatheres);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.unk_b[i]);
    }
    iob->bind____skip(1);
    for (int i = 0; i < 13; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.unk_c[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &d.produce_multiplier);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &d.has_raw_materials);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT16, &d.progress_max);
    if (d.progress_max == 0) {
        d.progress_max = 400;
    }

    iob->bind____skip(1);
    for (int i = 0; i < 3; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.unk_6[i]);
    }
    iob->bind(BIND_SIGNATURE_INT16, &d.reserved_id_13);

    for (int i = 0; i < 40; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.unk_40[i]);
    }
    iob->bind____skip(1);
    iob->bind____skip(1);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.unk_12[i]);
    }
    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT8, &d.processed_figure);

    int tmp;
    iob->bind(BIND_SIGNATURE_UINT8, &tmp); // reserved for extended figure type
}

void building_industry::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_industry::on_create(int orientation) {
    building_impl::on_create(orientation);

    auto &d = runtime_data();
    if (d.progress_max <= 0) {
        const uint16_t maxp = building_is_workshop(type()) ? MAX_PROGRESS_WORKSHOP : MAX_PROGRESS_RAW;
        d.progress_max = maxp;
    }
}

bool building_industry::stored_amount(e_resource r) const {
    if (base.output_resource_first_id == r) {
        return runtime_data().ready_production;
    }
    return building_impl::stored_amount(r);
}

void building_industry::start_production() {
    bool can_start_b = false;
    if (base.second_material_id != RESOURCE_NONE) {
        can_start_b = (base.stored_amount_second >= 100);
    } else {
        can_start_b = true;
    }

    const bool can_start_a = (base.stored_amount_first >= 100);
    auto &d = runtime_data();
    if (can_start_b && can_start_a) {
        d.progress = 0;
        d.has_raw_materials = true;
        if (base.stored_amount_second >= 100) {
            base.stored_amount_second -= 100;
        }
        if (base.stored_amount_first >= 100) {
            base.stored_amount_first -= 100;
        }
    }
}

bvariant building_industry::get_property(const xstring &domain, const xstring &name) const {
    if (domain == tags().industry && name == tags().progress) {
       int pct_done = calc_percentage<int>(progress(), progress_max());
       return bvariant(pct_done);
    }

    return building_impl::get_property(domain, name);
}
