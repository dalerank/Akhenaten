#include "scenario.h"

#include "io/io_buffer.h"
#include "city/campaign_carry.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/custom_span.hpp"
#include "empire/trade_route.h"
#include "earthquake.h"
#include "farao_change.h"
#include "scenario_event_manager.h"
#include "game/difficulty.h"
#include "game/game.h"
#include "game/mission.h"
#include "dev/debug.h"

#include "js/js_game.h"

scenario_data_t g_scenario;
std::unordered_set<custom_mission_config> ANK_VARIABLE(custom_missions);

void ANK_REGISTER_CONFIG_ITERATOR(config_load_scenario_load_meta_data) {
    mission_id_t missionid(g_scenario.campaign_scenario_id);

    g_scenario.load_metadata(missionid, /*is_new_mission*/ true);
    js_register_mission_vars(g_scenario.vars);
}


int get_custom_mission_id(xstring mission) {
    for (const auto& m : custom_missions) {
        if (m.filename == mission) {
            return m.mission_id;
        }
    }

    verify_no_crash(false && "no custom scenario config");
    return -1;
}

void scenario_data_t::init() {
    campaign_scenario_id = 0;
    campaign_mission_rank = 0;
    carry_troops_mask = 0;
    carry_monuments = false;
    reset_personal_savings = false;
    scmode = e_scenario_normal;
    settings.starting_kingdom = difficulty_starting_kingdom();
    if (debt_interest_rate <= 0) {
        debt_interest_rate = 10;
    }
}

void scenario_data_t::distant_battle_set_enemy_travel_months(int value) {
    empire.distant_battle_enemy_travel_months = value;
}

int scenario_data_t::startup_funds() const {
    const int funds = meta.initial_funds.get();
    if (funds > 0) {
        return funds;
    }

    return difficulty.adjust_money(finance.initial_funds);
}

int scenario_data_t::rescue_loan() const {
    const int loan = meta.rescue_loans.get();
    if (loan > 0) {
        return loan;
    }

    return difficulty.loan_money(finance.rescue_loan);
}

int scenario_data_t::house_tax_multiplier(int v) const {
    const int multiplier = meta.house_tax_multipliers.get();
    if (multiplier > 0) {
        return calc_adjust_with_percentage<int>(v, multiplier);
    }

    return difficulty.house_tax_multiplier(v);
}

int scenario_data_t::debt_interest() const {
    const int rate = meta.debt_interest.get();
    if (rate > 0) {
        return rate;
    }
    if (debt_interest_rate > 0) {
        return debt_interest_rate;
    }
    return 10;
}

void scenario_data_t::load_metadata(const mission_id_t &missionid, bool is_new_mission) {
    g_config_arch.r_section(missionid, [this, is_new_mission] (archive arch) {
        arch.r(meta);
        arch.r("env", env);

        int rank = std::min(arch.r_int("player_rank", -1), 10);
        if (rank >= 0) {
            g_city.kingdome.player_rank = rank;
        }

        memset(allowed_buildings, 0, sizeof(allowed_buildings));
        auto buildings = arch.r_array_num<e_building_type>("buildings");
        for (const auto &b : buildings) {
            allowed_buildings[b] = true;
        }

        init_resources.clear();
        arch.r("init_resources", init_resources);

        carry_troops_mask = 0;
        for (const auto &name : arch.r_array_str("carry_troops")) {
            carry_troops_mask |= troop_carry_mask_parse_name(name.c_str());
        }
        carry_monuments = arch.r_bool("carry_monuments");
        reset_personal_savings = arch.r_bool("reset_personal_savings");
        if (is_new_mission && reset_personal_savings) {
            g_city.kingdome.campaign_carry_personal_savings = 0;
        }

        arch.r("invasion_points_land", invasion_points_land);
        arch.r("invasion_points_sea", invasion_points_sea);
        arch.r("win_criteria", win_criteria);
        arch.r("sounds", sounds);

        // Optional map-point overlays (pak remains if the key is absent).
        // Accept [x, y] or { x, y }. Missing key keeps the current (pak) value.
        auto overlay_tile = [&] (pcstr name, tile2i &dest) {
            vec2i cur{ dest.x(), dest.y() };
            vec2i v = arch.r_vec2i(name, cur);
            dest = tile2i(v.x, v.y);
        };
        overlay_tile("entry_point", entry_point);
        overlay_tile("exit_point", exit_point);
        overlay_tile("river_entry_point", river_entry_point);
        overlay_tile("river_exit_point", river_exit_point);
        overlay_tile("earthquake_point", earthquake_point);
        // disembark_points: mission config only (pak discarded). Absent key → empty.
        arch.r_vector("disembark_points", disembark_points, MAX_DISEMBARK_POINTS);

        // fishing / herd points: mission config only (map/pak discarded). Absent key → empty.
        // herd entries: [x,y] or { tile:[x,y], type, count, radius }.
        arch.r("fishing_points", fishing_points);
        arch.r("herd_points_predator", herd_points_predator);
        arch.r("herd_points_prey", herd_points_prey);

        // Legacy positional types overlay (prefer per-point type in the object form).
        const auto herd_types = arch.r_array_num<e_figure_type>("herd_types_predator");
        for (size_t i = 0; i < herd_types.size() && i < herd_points_predator.size(); i++) {
            if (herd_types[i] != FIGURE_NONE && herd_points_predator[i].type == FIGURE_NONE) {
                herd_points_predator[i].type = herd_types[i];
            }
        }

        // Mission list is unlock source of truth; appeased/bonuses come from save chunk.
        g_city.local_cults.load_mission_unlocks(arch.r_array_str("local_cults"));

        // Burial provisions: omit keys → keep pak. hide_pak_burial clears then JS list
        // replaces. On save load, required is overwritten from JS; dispatched is kept.
        if (arch.r_bool("hide_pak_burial", false)) {
            for (int r = 0; r < RESOURCES_MAX; r++) {
                monuments.burial_provisions[r].required = 0;
                if (is_new_mission) {
                    monuments.burial_provisions[r].dispatched = 0;
                }
            }
        }
        arch.r_array("burial_provisions", [&] (archive entry) {
            const e_resource res = entry.r_type<e_resource>("resource", RESOURCE_NONE);
            const int required = entry.r_int("required", 0);
            if (res <= RESOURCE_NONE || res >= RESOURCES_MAX || required <= 0) {
                return;
            }
            monuments.burial_provisions[res].required = required;
            if (is_new_mission) {
                monuments.burial_provisions[res].dispatched = 0;
            }
        });

        settings_vars_t newvars;
        arch.r("vars", newvars);
        vars.insert(newvars);
    });

    // Keep pak rate if present; otherwise default 10%. Mission meta ladder is read via debt_interest().
    if (debt_interest_rate <= 0) {
        debt_interest_rate = 10;
    }

    if (is_new_mission) {
        events.load_mission_metadata(missionid);
    }
}

void scenario_data_t::bind_data(io_buffer *iob, size_t version, size_t size) {
    assert(size == 2000);
    char data[2000] = { 0 };
    if (iob->is_read_access()) {
        iob->bind(BIND_SIGNATURE_RAW, &data, sizeof(data));
        vars.load(data);
    } else {
        std::string save_data = vars.save();
        assert(save_data.size() < sizeof(data));
        memcpy(data, save_data.data(), save_data.size() + 1);
        iob->bind(BIND_SIGNATURE_RAW, &data, sizeof(data));
    }
}

bool scenario_building_allowed(e_building_type building_type) {
    return g_scenario.allowed_buildings[building_type];
}

void scenario_building_allow(e_building_type btype, bool allow) {
    g_scenario.allowed_buildings[btype] = allow;
}

int16_t scenario_data_t::pak_editor_allow_flag(int slot) const {
    if (slot < 1 || slot > SCENARIO_EDITOR_ALLOW_SLOTS) {
        return 0;
    }
    return pak_reserved[slot - 1];
}

int scenario_editor_allow_mapped_types(int slot, e_building_type *out, int max_out) {
    if (!out || max_out <= 0) {
        return 0;
    }
    switch (slot) {
    case scenario_data_t::EDITOR_ALLOW_SLOT_BRIDGE:
        out[0] = BUILDING_LOW_BRIDGE;
        return 1;
    case scenario_data_t::EDITOR_ALLOW_SLOT_FERRY:
        out[0] = BUILDING_FERRY;
        return 1;
    default:
        return 0;
    }
}

int scenario_building_image_native_hut() {
    return g_scenario.native_images.hut;
}

int scenario_building_image_native_meeting() {
    return g_scenario.native_images.meeting;
}

int scenario_building_image_native_crops() {
    return g_scenario.native_images.crops;
}


// fancy lambdas! probably gonna create many problems down the road. :3
io_buffer* iob_scenario_mission_id = new io_buffer([](io_buffer* iob, size_t version) {
    // Chunk is 4 bytes; INT8 truncated custom mission ids > 127 (e.g. mission 129).
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.campaign_scenario_id);
});

e_scenario_mode scenario_data_t::mode() {
    return scmode;
}

bool scenario_data_t::is_scenario_id(xspan<int> missions) {
    const bool is_custom_map = scmode != e_scenario_normal;
    if (is_custom_map) {
        return false;
    }

    for (const int rank : missions) {
        if (g_scenario.campaign_scenario_id == rank - 1) {
            return true;
        }
    }

    return false;
}

int scenario_data_t::is_before_mission(int mission) {
    const bool is_custom_map = (mode() != e_scenario_normal);
    return !is_custom_map && campaign_mission_rank < mission;
}

void scenario_set_name(pcstr name) {
    g_scenario.scenario_name = (name && *name) ? name : "";
}

int scenario_open_play_id() {
    return g_scenario.open_play_scenario_id;
}

int scenario_property_enemy() {
    return g_scenario.enemy_id;
}
int scenario_property_player_rank() {
    return g_scenario.player_rank;
}

io_buffer *iob_scenario_info = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.start_year);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.empire.id);
    iob->bind____skip(4);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &g_city.religion.gods[i].is_known);
        iob->bind____skip(1);
    }
    iob->bind____skip(10);
    iob->bind____skip(2); // 2 bytes ???        03 00

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.finance.initial_funds);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.enemy_id);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.width);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.height);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.start_offset);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.border_size);
    iob->bind(BIND_SIGNATURE_XSTR, g_scenario.subtitle, MAX_SUBTITLE);
    iob->bind(BIND_SIGNATURE_XSTR, g_scenario.brief_description, MAX_BRIEF_DESCRIPTION);

    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.image_id);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.is_open_play);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.player_rank);

    iob->bind_hvector_point_tiles_xy_u16(g_scenario.herd_points_predator);

    iob->bind_hvector_tiles_xy_u16(g_scenario.fishing_points, MAX_FISH_POINTS);

    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.alt_predator_type);

    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.herd_points_predator[i].type);
    }
    iob->bind____skip(34);

    iob->bind_hvector_tiles_xy_u16(g_scenario.invasion_points_land, MAX_INVASION_POINTS_LAND);
    iob->bind_hvector_tiles_xy_u16(g_scenario.invasion_points_sea, MAX_INVASION_POINTS_SEA);

    iob->bind____skip(36); // 18 * 2

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.culture.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.prosperity.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.monuments.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.kingdom.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.housing_count.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.housing_level.goal);

    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.culture.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.prosperity.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.monuments.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.kingdom.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.housing_count.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.housing_level.enabled);

    iob->bind____skip(6); // ???
                          //    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.earthquake.severity);
                          //    iob->bind(BIND_SIGNATURE_INT16, g_scenario.earthquake.private_access(_Y)ear); // ??

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.time_limit.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.time_limit.years);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.survival_time.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.survival_time.years);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.population.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.population.goal);

    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.earthquake_point);

    *g_scenario.entry_point.private_access(_GRID_OFFSET) = -1;
    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.entry_point);

    *g_scenario.exit_point.private_access(_GRID_OFFSET) = -1;
    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.exit_point);

    // junk 4a
    iob->bind____skip(28); // 14 * 2
    iob->bind____skip(4);  // 2 * 2 (58, 64)

    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.river_entry_point);
    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.river_exit_point);

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.finance.rescue_loan);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.milestone25_year);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.milestone50_year);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.milestone75_year);

    // junk 4b
    iob->bind____skip(10); // 3 * 4 (usually go n, n+2, n+1497)
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.env.has_animals);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.env.flotsam_enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.climate);

    // junk 4e
    iob->bind____skip(1);
    iob->bind____skip(1); // used?
    iob->bind____skip(1); // used?
    iob->bind____skip(8);

    int tmp;
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.player_faction);

    // junk 4f
    iob->bind____skip(1); // -1 or -31
    iob->bind____skip(1); // -1

    iob->bind_hvector_point_tiles_xy_i32(g_scenario.herd_points_prey);
    for (int i = 0; i < scenario_data_t::SCENARIO_PAK_RESERVED_INT16S; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &g_scenario.pak_reserved[i]);
    }

    iob->bind_hvector_tiles_xy_i32(g_scenario.disembark_points, MAX_DISEMBARK_POINTS);

    iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.debt_interest_rate);

    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.monuments.first);
    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.monuments.second);
    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.monuments.third);

    // junk 6a
    iob->bind____skip(2);

    for (int i = 0; i < RESOURCES_MAX; ++i)
        iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.monuments.burial_provisions[i].required);
    for (int i = 0; i < RESOURCES_MAX; ++i)
        iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.monuments.burial_provisions[i].dispatched);

    iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.current_pharaoh);
    iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.player_incarnation);

    ///

    g_scenario.is_saved = true;
});

io_buffer* iob_scenario_carry_settings = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.settings.starting_kingdom);
    iob->bind____skip(4); // legacy starting_personal_savings (mission scripts set kingdome savings)
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.campaign_mission_rank);
});

io_buffer* iob_scenario_is_custom = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.scmode);
    iob->bind____skip(3);
});

io_buffer* iob_scenario_map_name = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_XSTR, g_scenario.scenario_name, MAX_SCENARIO_NAME);
});

void scenario_data_t::update() {
    scenario_earthquake_process();
    //scenario_slave_revolt_process();
    scenario_kingdome_change_process();
}
