#include "building/building_industry.h"

#include "io/io_buffer.h"
#include "city/city.h"
#include "core/object_property.h"
#include "figuretype/figure_cartpusher.h"
#include "game/game_events.h"
#include "city/city_resource.h"
#include "widget/debug_console.h"

constexpr short MAX_PROGRESS_RAW = 200;
constexpr short MAX_PROGRESS_WORKSHOP = 400;

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

bool building_industry::can_play_animation() const {
    if (g_city.resource.is_mothballed(base.output.resource)) {
        return false;
    }

    return building_impl::can_play_animation();
}

void building_industry::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_industry::update_production() {
    auto &d = runtime_data();
    d.has_raw_materials = false;

    if (g_city.resource.is_mothballed(base.output.resource)) {
        return;
    }

    if (base.num_workers <= 0) {
        return;
    }

    if (base.curse_days_left) {
        base.curse_days_left--;
        return;
    } 

    if (base.blessing_days_left > 0) {
        base.blessing_days_left--;
    }

    const int progress_per_day = produce_uptick_per_day();
    d.progress += progress_per_day;

    if (base.blessing_days_left) {
        const float normal_progress = progress_per_day;
        d.progress += normal_progress;
    }

    d.progress = std::clamp<short>(d.progress, 0, d.progress_max);
}

void building_industry::on_create(int orientation) {
    building_impl::on_create(orientation);

    auto &d = runtime_data();
    if (d.progress_max <= 0) {
        const uint16_t maxp = building_is_workshop(type()) ? MAX_PROGRESS_WORKSHOP : MAX_PROGRESS_RAW;
        d.progress_max = maxp;
    }
}

int building_industry::stored_amount(e_resource r) const {
    if (base.output.resource == r) {
        return runtime_data().ready_production;
    }
    return building_impl::stored_amount(r);
}

void building_industry::start_production() {
    bool can_start_b = true;
    if (base.input.resource_second != RESOURCE_NONE) {
        can_start_b = (base.stored_amount_second >= 100);
    } 

    bool can_start_a = true;
    if (base.input.resource != RESOURCE_NONE) {
        can_start_a = (base.stored_amount_first >= 100);
    }

    if (can_start_b && can_start_a) {
        auto &d = runtime_data();
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

void building_industry::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return;
    }

    const auto &industryd = runtime_data();
    assert(industryd.progress_max > 100);
    const bool has_produced_resource = (industryd.progress >= industryd.progress_max);

    if (has_produced_resource) {
        start_production();
        const int expected_produce = ready_production();
        create_cartpusher(base.output.resource, expected_produce, (e_figure_action)ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);
        events::emit(event_produced_resources{ base.output.resource, expected_produce });
    }
}

void building_industry::update_count() const {
    building_impl::update_count();

    if (base.output.resource != RESOURCE_NONE) {
        g_city.buildings.increase_industry_count(base.output.resource, num_workers() > 0);
    }

    if (base.output.resource_second != RESOURCE_NONE) {
        g_city.buildings.increase_industry_count(base.output.resource_second, num_workers() > 0);
    }
}

bvariant building_industry::get_property(const xstring &domain, const xstring &name) const {
    if (domain == tags().industry && name == tags().progress) {
       int pct_done = calc_percentage<int>(progress(), progress_max());
       return bvariant(pct_done);
    }

    return building_impl::get_property(domain, name);
}

void building_industry::debug_draw_properties() {
    auto &d = runtime_data();
    game_debug_show_property("ready_production", d.ready_production);
    game_debug_show_property("progress", d.progress);
    game_debug_show_property("progress_max", d.progress_max);
    game_debug_show_property("spawned_worker_this_month", d.spawned_worker_this_month);
    game_debug_show_property("max_gatheres", d.max_gatheres);
    game_debug_show_property("produce_multiplier", d.produce_multiplier);
    game_debug_show_property("has_raw_materials", d.has_raw_materials);
    game_debug_show_property("processed_figure", d.processed_figure);
}
