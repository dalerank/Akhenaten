#include "building_mansion.h"

#include "city/city.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "figuretype/figure_governor.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "widget/city/ornaments.h"

#include <algorithm>
#include <cstdint>

BUILDING_RUNTIME_DATA_IMPL(building_mansion)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_personal_mansion);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_family_mansion);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dynasty_mansion);

namespace {

// OG mansion_share_table weights: Personal=1, Family=2, Dynasty=3.
constexpr int k_mansion_share_weight[3] = {1, 2, 3};
constexpr e_building_type k_mansion_types[3] = {
    BUILDING_PERSONAL_MANSION,
    BUILDING_FAMILY_MANSION,
    BUILDING_DYNASTY_MANSION,
};

// OG enemy_theft_percentages by difficulty.
constexpr int k_enemy_theft_pct[5] = {0, 15, 30, 60, 100};

} // namespace

void building_mansion::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);
    g_city.buildings.track_building(base, false);
    auto &d = runtime_data();
    d.personal_savings_storage = 0;
    update_money_values();
}

void building_mansion::on_post_load() {
    building_impl::on_post_load();
    g_city.buildings.track_building(base, true);
    update_money_values();
}

void building_mansion::on_before_collapse() {
    // OG destroy_enemy mansion: lose difficulty-% of personal_savings (not on fire/collapse).
    if (base.destroy_reason == e_destroy_enemy) {
        const int diff = std::clamp<int>(game_difficulty(), 0, 4);
        const int pct = k_enemy_theft_pct[diff];
        const int amount = calc_adjust_with_percentage<int>((int)g_city.kingdome.personal_savings, pct);
        if (amount > 0) {
            if (g_city.kingdome.personal_savings >= (uint16_t)amount) {
                g_city.kingdome.personal_savings -= (uint16_t)amount;
            } else {
                g_city.kingdome.personal_savings = 0;
            }
            g_city.finance.process_stolen(amount);
            update_money_values();
            events::emit(event_city_warning{xstring("#thief_stole_savings")});
        }
    }
    building_impl::on_before_collapse();
}

void building_mansion::update_count() const {
    const bool is_active = (base.has_road_access);
    g_city.buildings.track_building(base, is_active);
}

void building_mansion::spawn_figure() {
    // OG: labor_category -1, no service walkers / labor seekers.
    // Remake: one governor walks mansion → palace (phrases). Fixed delay — 0 laborers
    // makes figure_spawn_timer() always -1, so common_spawn_figure_trigger cannot pace this.
    if (!has_road_access()) {
        return;
    }
    if (base.has_figure(BUILDING_SLOT_GOVERNOR)) {
        return;
    }

    constexpr int k_governor_spawn_delay = 32;
    base.figure_spawn_delay++;
    if (base.figure_spawn_delay <= k_governor_spawn_delay) {
        return;
    }
    base.figure_spawn_delay = 0;

    // Prefer cached road_access (same as create_figure_generic); closest-road is fallback.
    tile2i spawn_tile = base.road_access;
    if (!spawn_tile.valid()) {
        spawn_tile = map_closest_road_within_radius(tile(), size(), 2);
    }
    if (!spawn_tile.valid()) {
        return;
    }

    figure *f = figure_create(FIGURE_GOVERNOR, spawn_tile, DIR_4_BOTTOM_LEFT);
    f->advance_action(ACTION_0_GOVERNOR_CREATED);
    f->set_home(&base);
    f->wait_ticks = 10 + (base.map_random_7bit & 0xf);
    base.set_figure(BUILDING_SLOT_GOVERNOR, f);
}

void building_mansion::update_graphic() {
    set_animation(animkeys().work);
}

bool building_mansion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    switch (type()) {
    case BUILDING_PERSONAL_MANSION:
    case BUILDING_FAMILY_MANSION:
    case BUILDING_DYNASTY_MANSION: {
        draw_normal_anim(ctx, point, tile, mask);
        break;
    }
    default:
        verify_no_crash(false);
    }
    return true;
}

void building_mansion::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_INT32, &d.personal_savings_storage);
}

bool building_mansion::is_protected_by_police() const {
    grid_area area = map_grid_get_area(tile(), size(), 2);
    bool has_protection = false;

    map_grid_area_foreach(area, [&](tile2i check_tile) {
        int figure_id = map_figure_id_get(check_tile);
        while (figure_id > 0 && !has_protection) {
            figure *f = figure_get(figure_id);
            if (f && f->type == FIGURE_CONSTABLE && f->state == FIGURE_STATE_ALIVE) {
                has_protection = true;
                return;
            }
            if (figure_id == f->next_figure) {
                break;
            }
            figure_id = f->next_figure;
        }
    });

    return has_protection;
}

void building_mansion::update_money_values() {
    // OG city_finance_building_money_value + mansion_share_table.
    // Count live buildings only — track_building totals can lag after enemy destroy.
    int counts[3] = {};
    buildings_valid_do([&](building &b) {
        for (int i = 0; i < 3; i++) {
            if (b.type == k_mansion_types[i]) {
                counts[i]++;
                break;
            }
        }
    });

    int total_weight = 0;
    for (int i = 0; i < 3; i++) {
        total_weight += k_mansion_share_weight[i] * counts[i];
    }

    const int savings = (int)g_city.kingdome.personal_savings;
    buildings_valid_do([&](building &b) {
        int idx = -1;
        for (int i = 0; i < 3; i++) {
            if (b.type == k_mansion_types[i]) {
                idx = i;
                break;
            }
        }
        if (idx < 0) {
            return;
        }
        int value = 0;
        if (savings > 0 && total_weight > 0) {
            value = (int)(((double)k_mansion_share_weight[idx] / (double)total_weight) * (double)savings);
        }
        b.tax_income_or_storage = (int16_t)std::clamp(value, 0, (int)INT16_MAX);
        if (auto *m = b.dcast_mansion()) {
            m->runtime_data().personal_savings_storage = value;
        }
    });
}

void building_mansion::check_theft_from_mansions() {
    // Remake ambient mansion theft — OG thieves steal only on arrival (figure_robber).
    if (!game_features::gameplay_change_robber_remake.to_bool()) {
        return;
    }
    if (g_city.sentiment.criminals <= 0) {
        return;
    }

    int crime_chance = 100 - g_city.sentiment.value;
    if (crime_chance < 10) {
        return;
    }

    if ((random_byte() % 100) > (crime_chance / 10)) {
        return;
    }

    for (e_building_type type : k_mansion_types) {
        const auto tracked = g_city.buildings.tracked_buildings()[type];
        for (auto id : tracked) {
            building *b = building_get(id);
            if (!b || !b->is_valid() || b->state != BUILDING_STATE_VALID) {
                continue;
            }

            auto mansion = b->dcast_mansion();
            if (!mansion || !mansion->has_road_access()) {
                continue;
            }

            if (mansion->is_protected_by_police()) {
                continue;
            }

            if (g_city.kingdome.personal_savings <= 0) {
                continue;
            }

            int savings = (int)g_city.kingdome.personal_savings;
            int steal_amount = savings * (10 + (random_byte() % 40)) / 100;
            if (steal_amount > 200) {
                steal_amount = 200 - (random_byte() % 50);
            }
            if (steal_amount < 10) {
                steal_amount = 10;
            }
            if (steal_amount > savings) {
                steal_amount = savings;
            }

            if (steal_amount <= 0) {
                continue;
            }

            if (g_city.kingdome.personal_savings >= (uint16_t)steal_amount) {
                g_city.kingdome.personal_savings -= (uint16_t)steal_amount;
            } else {
                g_city.kingdome.personal_savings = 0;
            }
            g_city.finance.process_stolen(steal_amount);
            update_money_values();

            bool show_popup = (g_city.sentiment.last_mugger_message <= 0);
            if (show_popup) {
                g_city.sentiment.last_mugger_message = 90;
            }
            events::emit(event_message{show_popup, "thief_stole_savings", steal_amount, b->tile.grid_offset(), SOURCE_LOCATION});
            return;
        }
    }
}

bool building_mansion::exist_in_city() {
    for (e_building_type type : k_mansion_types) {
        if (g_city.buildings.count_total(type) > 0) {
            return true;
        }
    }
    return false;
}
