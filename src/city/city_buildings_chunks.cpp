#include "city/city_buildings_chunks.h"

#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "io/io_buffer.h"

#include <vector>

static void bind_building_record(io_buffer* iob, building* b, building_id i, size_t version) {
    // 186 is header+runtime from record start (Pharaoh: ~82 header + ~102 runtime).
    const int sind = (int)iob->get_offset();

    iob->bind(BIND_SIGNATURE_UINT8, &b->state);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->faction_id);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->reserved_id);
    iob->bind(BIND_SIGNATURE_UINT8, &b->size);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->house_is_merged);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_UINT8, &b->house_size);
    iob->bind(BIND_SIGNATURE_TILE2I, b->tile);
    iob->bind(BIND_SIGNATURE_UINT8, &b->orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &b->spawned_worker_this_month);
    iob->bind(BIND_SIGNATURE_UINT8, &b->curse_days_left);
    iob->bind(BIND_SIGNATURE_UINT8, &b->blessing_days_left);
    iob->bind____skip(2);
    iob->bind_u16((uint16_t&)b->type);
    iob->bind_u16(b->structure_damage);
    iob->bind(BIND_SIGNATURE_UINT16, &b->road_network_id);
    iob->bind(BIND_SIGNATURE_INT16, &b->native_meeting_center_id);
    iob->bind(BIND_SIGNATURE_INT16, &b->houses_covered);
    iob->bind(BIND_SIGNATURE_INT16, &b->percentage_houses_covered);

    iob->bind(BIND_SIGNATURE_UINT32, &b->exceptions);
    iob->bind(BIND_SIGNATURE_INT16, &b->distance_from_entry);

    iob->bind(BIND_SIGNATURE_UINT16, &b->progress);
    iob->bind(BIND_SIGNATURE_UINT16, &b->progress_max);

    iob->bind(BIND_SIGNATURE_TILE2I, b->road_access);

    iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[0]);
    iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[1]);
    iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[2]);
    iob->bind(BIND_SIGNATURE_UINT16, &b->figure_ids[3]);

    iob->bind(BIND_SIGNATURE_INT16, &b->figure_spawn_delay);
    iob->bind(BIND_SIGNATURE_UINT8, &b->figure_roam_direction);
    iob->bind(BIND_SIGNATURE_UINT8, &b->has_water_access);

    iob->bind(BIND_SIGNATURE_UINT8, &b->common_health);
    iob->bind(BIND_SIGNATURE_UINT8, &b->malaria_risk);
    iob->bind(BIND_SIGNATURE_INT16, &b->prev_part_building_id);
    iob->bind(BIND_SIGNATURE_INT16, &b->next_part_building_id);
    iob->bind(BIND_SIGNATURE_UINT16, &b->residents_served_this_month);
    iob->bind(BIND_SIGNATURE_UINT8, &b->disease_days);
    iob->bind(BIND_SIGNATURE_UINT8, &b->has_well_access);

    iob->bind(BIND_SIGNATURE_INT16, &b->num_workers);
    iob->bind(BIND_SIGNATURE_UINT8, &b->labor_category); // FF
    iob->bind(BIND_SIGNATURE_UINT8, &b->output.resource);
    iob->bind(BIND_SIGNATURE_UINT8, &b->has_road_access);
    iob->bind____skip(1);

    iob->bind(BIND_SIGNATURE_INT16, &b->collapse_risk);
    iob->bind(BIND_SIGNATURE_INT16, &b->fire_risk);
    iob->bind(BIND_SIGNATURE_INT16, &b->fire_duration);
    iob->bind(BIND_SIGNATURE_UINT8, &b->fire_proof);

    iob->bind(BIND_SIGNATURE_UINT8, &b->map_random_7bit); // 20 (workcamp 1)
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &b->health_proof);
    iob->bind(BIND_SIGNATURE_INT16, &b->formation_id);

    static_assert(sizeof(building::runtime_data) == 186, "runtime_data more then 186 bytes");
    b->dcast()->bind_dynamic(iob, version); // 102 for PH

    const int currind = (int)iob->get_offset() - sind;
    verify_no_crash(currind >= 0);
    if (currind > 186) {
        // Saves before v196 hold pyramid/mastaba parts that ran past the record; they still load the old way.
        if (!iob->is_read_access() || version >= 196) {
            logs::error("[record-overflow] building %d (%s): header + runtime data take %d bytes, the record holds 186",
              i, token::find_name(e_building_type_tokens, b->type), currind);
        }
        iob->set_offset(sind + 186);
    } else {
        iob->bind____skip(186 - currind);
    }

    iob->bind____skip(2);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &b->has_plague); // 1

    iob->bind(BIND_SIGNATURE_INT8, &b->current_desirability);
    iob->bind(BIND_SIGNATURE_UINT8, &b->is_deleted);
    iob->bind(BIND_SIGNATURE_UINT8, &b->is_adjacent_to_water);

    iob->bind(BIND_SIGNATURE_UINT8, &b->storage_id);
    iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_INT8, &b->sentiment.house_happiness); // which union field we use
                          // does not matter // 90 for house, 50 for wells
    iob->bind(BIND_SIGNATURE_UINT8, &b->show_on_problem_overlay);     // 1
    iob->bind(BIND_SIGNATURE_UINT16, &b->deben_storage);              // 2
    iob->bind(BIND_SIGNATURE_UINT8, &b->has_open_water_access);       // 1
    iob->bind(BIND_SIGNATURE_UINT8, &b->output.resource_second);      // 1
    iob->bind(BIND_SIGNATURE_UINT8, &b->output_resource_second_rate); // 1

    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT8, &b->input.resource);
    iob->bind(BIND_SIGNATURE_INT8, &b->input.resource_second);
    iob->bind(BIND_SIGNATURE_INT64, b->flags.data_ptr());
    iob->bind(BIND_SIGNATURE_INT8, &b->storage.at(0).type);
    iob->bind(BIND_SIGNATURE_UINT16, &b->storage.at(0).value);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT8, &b->storage.at(1).type);
    iob->bind(BIND_SIGNATURE_INT16, &b->storage.at(1).value);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT8, &b->storage.at(2).type);
    iob->bind(BIND_SIGNATURE_INT16, &b->storage.at(2).value);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT8, &b->storage.at(3).type);
    iob->bind(BIND_SIGNATURE_INT16, &b->storage.at(3).value);
    iob->bind____skip(1);

    // 31 additional bytes
    iob->bind____skip(35); // temp for debugging
    //            assert(iob->get_offset() - sind == 264);
    b->id = i;

    if (version <= 164) {
        b->common_health = 100;
        b->malaria_risk = 0;
        b->disease_days = 0;
        b->health_proof = 0;
    }

    const auto& params = building_static_params::get(b->type);
    b->des_influence = params.desirability.to_influence();
    b->crime_influence = params.crime.to_influence();
    b->fire_risk_increase = params.fire_risk;
    b->collapse_risk_increase = params.damage_risk;
    b->max_workers = params.laborers;
}

void buildings_chunk::bind_data(io_buffer* iob, size_t version) {
    if (iob->is_read_access()) {
        stub_records_guard_reset();
    }
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        bind_building_record(iob, building_get(i), i, version);
    }
    // building_extra_data.created_sequence = 0;
}

void buildings_chunk::reset() {
    building_clear_all();
}

namespace {
    struct stub_records_guard_t {
        bool armed = false;
        std::vector<uint8_t> building0;
        std::vector<uint8_t> figure0;
    };
    stub_records_guard_t g_stub_guard;

    void bind_building0(io_buffer* iob, size_t version) {
        bind_building_record(iob, building_get(0), 0, version);
    }

    void bind_figure0(io_buffer* iob, size_t) {
        figure_get(0)->bind(iob);
    }

    struct record_buffer : io_buffer {
        void (*bind_record)(io_buffer* iob, size_t version);

        explicit record_buffer(void (*fn)(io_buffer*, size_t)) : bind_record(fn) {}

        void bind_data(size_t version) override { bind_record(this, version); }
    };

    std::vector<uint8_t> serialize_record(void (*bind)(io_buffer*, size_t)) {
        buffer buf(1024);
        record_buffer iob(bind);
        iob.hook(&buf, (int)buf.size(), false, "stub_record");
        iob.write();
        return std::vector<uint8_t>(buf.get_data(), buf.get_data() + buf.get_offset());
    }

    // OG figure_movement_can_launch_cross_country_missile (movement.c) traces the missile path in figure 0,
    // so these fields legitimately change; they are masked out of the comparison.
    std::vector<uint8_t> serialize_figure0_masked() {
        figure* f = figure_get(0);
        const vec2i cc_coords = f->cc_coords;
        const vec2i cc_destination = f->cc_destination;
        const vec2i cc_delta = f->cc_delta;
        const short cc_delta_xy = f->cc_delta_xy;
        const uint8_t cc_direction = f->cc_direction;
        const tile2i tile = f->tile;

        f->cc_coords = {};
        f->cc_destination = {};
        f->cc_delta = {};
        f->cc_delta_xy = 0;
        f->cc_direction = 0;
        f->tile = tile2i(0, 0);
        auto bytes = serialize_record(bind_figure0);

        f->cc_coords = cc_coords;
        f->cc_destination = cc_destination;
        f->cc_delta = cc_delta;
        f->cc_delta_xy = cc_delta_xy;
        f->cc_direction = cc_direction;
        f->tile = tile;
        return bytes;
    }

    void report_change(pcstr record, pcstr phase, const std::vector<uint8_t>& was, const std::vector<uint8_t>& now) {
        const size_t n = std::min(was.size(), now.size());
        size_t first = 0;
        while (first < n && was[first] == now[first]) {
            ++first;
        }
        const int was_v = first < was.size() ? was[first] : -1;
        const int now_v = first < now.size() ? now[first] : -1;
        logs::error("[stub-record] %s changed %s: first byte %u of the saved record %d -> %d", record, phase,
          (unsigned)first, was_v, now_v);
    }
} // namespace

void stub_records_guard_reset() {
    g_stub_guard.armed = false;
}

void stub_records_guard_check(pcstr phase) {
    auto building0 = serialize_record(bind_building0);
    auto figure0 = serialize_figure0_masked();
    if (g_stub_guard.armed) {
        if (building0 != g_stub_guard.building0) {
            report_change("building 0", phase, g_stub_guard.building0, building0);
        }
        if (figure0 != g_stub_guard.figure0) {
            report_change("figure 0", phase, g_stub_guard.figure0, figure0);
        }
    }
    g_stub_guard.building0 = std::move(building0);
    g_stub_guard.figure0 = std::move(figure0);
    g_stub_guard.armed = true;
}
