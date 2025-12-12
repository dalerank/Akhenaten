#include "building/building_guild.h"

#include "io/io_buffer.h"
#include "core/object_property.h"

constexpr uint16_t MAX_PROGRESS_GUILD = 400;

void building_guild::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(26);
    iob->bind____skip(56);

    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &d.max_workers);
    iob->bind(BIND_SIGNATURE_UINT16, &d.progress);
    iob->bind(BIND_SIGNATURE_UINT16, &d.progress_max);
}

void building_guild::on_create(int orientation) {
    building_impl::on_create(orientation);

    auto &d = runtime_data();
    if (d.progress_max <= 0) {
        d.progress_max = MAX_PROGRESS_GUILD;
    }
}

bool building_guild::has_resources() const {
    const bool hase_first_resource = (stored_amount(base.input.resource) >= 100);
    return hase_first_resource;
}

bvariant building_guild::get_property(const xstring &domain, const xstring &name) const {
    if (domain == tags().industry && name == tags().progress) {
        int pct_done = calc_percentage<int>(progress(), progress_max());
        return bvariant(pct_done);
    }

    return building_impl::get_property(domain, name);
}