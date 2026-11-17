#include "scenario.h"

#include "io/io_buffer.h"
#include "city/campaign_carry.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/custom_span.hpp"
#include "empire/trade_route.h"
#include "earthquake.h"
#include "scenario_event_manager.h"
#include "game/difficulty.h"
#include "game/game.h"
#include "game/mission.h"
#include "dev/debug.h"
#include "core/log.h"

#include "js/js_game.h"

#include <cstring>
#include <initializer_list>

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

// Percent of the taxed amount the city keeps: the mission's tax_percentage, else the system table.
int scenario_data_t::city_tax_percentage() const {
    if (!meta.tax_percentage.value.empty()) {
        return meta.tax_percentage.get();
    }
    return finance_tax_rules.tax_percentage.get();
}

// Custom maps made with the original editor have no JS mission config: rebuild
// allowed_buildings from the map's own editor flags (pak_reserved slots 1..45),
// plus the buildings the original game never gates (housing, farms, industry,
// guilds, temples of known gods, monuments chosen in the editor).
static void scenario_allow_list(scenario_data_t &sc, std::initializer_list<e_building_type> types) {
    for (const e_building_type t : types) {
        sc.allowed_buildings[t] = true;
    }
}

void scenario_data_t::apply_editor_allowed_buildings() {
    memset(allowed_buildings, 0, sizeof(allowed_buildings));

    scenario_allow_list(*this, {
        BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD, BUILDING_WELL,
        BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
        BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_LETTUCE_FARM,
        BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM, BUILDING_FIGS_FARM,
        BUILDING_HUNTING_LODGE, BUILDING_CATTLE_RANCH,
        BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
        BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
        BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP,
        BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD, BUILDING_ARTISANS_GUILD,
    });

    // Original editor slots (group 67 texts) -> Akhenaten building types.
    struct slot_type { int slot; e_building_type type; };
    static const slot_type slots[] = {
        { 1, BUILDING_CLAY_PIT },
        { 1, BUILDING_REED_GATHERER },
        { 1, BUILDING_WOOD_CUTTERS },
        { 1, BUILDING_STONE_QUARRY },
        { 1, BUILDING_LIMESTONE_QUARRY },
        { 1, BUILDING_GRANITE_QUARRY },
        { 1, BUILDING_SANDSTONE_QUARRY },
        { 1, BUILDING_COPPER_MINE },
        { 1, BUILDING_GEMSTONE_MINE },
        { 2, BUILDING_GOLD_MINE },
        { 3, BUILDING_WATER_LIFT },
        { 4, BUILDING_IRRIGATION_DITCH },
        { 5, BUILDING_FISHING_WHARF },
        { 5, BUILDING_SHIPWRIGHT },
        { 6, BUILDING_WORK_CAMP },
        { 7, BUILDING_GRANARY },
        { 8, BUILDING_BAZAAR },
        { 9, BUILDING_STORAGE_YARD },
        { 10, BUILDING_DOCK },
        { 10, BUILDING_DOCK_UP },
        { 11, BUILDING_BOOTH },
        { 11, BUILDING_JUGGLER_SCHOOL },
        { 12, BUILDING_BANDSTAND },
        { 12, BUILDING_CONSERVATORY },
        { 13, BUILDING_PAVILLION },
        { 13, BUILDING_DANCE_SCHOOL },
        { 14, BUILDING_SENET_HOUSE },
        { 15, BUILDING_FESTIVAL_SQUARE },
        { 16, BUILDING_SCRIBAL_SCHOOL },
        { 17, BUILDING_LIBRARY },
        { 18, BUILDING_WATER_SUPPLY },
        { 19, BUILDING_DENTIST },
        { 20, BUILDING_APOTHECARY },
        { 21, BUILDING_PHYSICIAN },
        { 22, BUILDING_MORTUARY },
        { 23, BUILDING_TAX_COLLECTOR },
        { 24, BUILDING_COURTHOUSE },
        { 25, BUILDING_VILLAGE_PALACE },
        { 25, BUILDING_TOWN_PALACE },
        { 25, BUILDING_CITY_PALACE },
        { 26, BUILDING_PERSONAL_MANSION },
        { 26, BUILDING_FAMILY_MANSION },
        { 26, BUILDING_DYNASTY_MANSION },
        { 27, BUILDING_ROADBLOCK },
        { 28, BUILDING_LOW_BRIDGE },
        { 29, BUILDING_FERRY },
        { 30, BUILDING_GARDENS },
        { 31, BUILDING_PLAZA },
        { 32, BUILDING_SMALL_STATUE },
        { 32, BUILDING_MEDIUM_STATUE },
        { 32, BUILDING_LARGE_STATUE },
        { 33, BUILDING_MUD_WALL },
        { 33, BUILDING_BRICK_WALL },
        { 33, BUILDING_WALL },
        { 34, BUILDING_MUD_TOWER },
        { 34, BUILDING_BRICK_TOWER },
        { 34, BUILDING_TOWER },
        { 35, BUILDING_MUD_GATEHOUSE },
        { 35, BUILDING_BRICK_GATEHOUSE },
        { 35, BUILDING_GATEHOUSE },
        { 36, BUILDING_RECRUITER },
        { 37, BUILDING_FORT_INFANTRY },
        { 38, BUILDING_FORT_ARCHERS },
        { 39, BUILDING_FORT_CHARIOTEERS },
        { 40, BUILDING_MILITARY_ACADEMY },
        { 41, BUILDING_WEAPONSMITH },
        { 42, BUILDING_CHARIOTS_WORKSHOP },
        { 43, BUILDING_WARSHIP_WHARF },
        { 43, BUILDING_SHIPWRIGHT },
        { 44, BUILDING_TRANSPORT_WHARF },
        { 44, BUILDING_SHIPWRIGHT },
        { 45, BUILDING_ZOO },
    };
    for (const auto &s : slots) {
        if (pak_editor_allow_flag(s.slot)) {
            allowed_buildings[s.type] = true;
        }
    }

    // Temples, shrines and temple complexes of the gods known in this map.
    const e_building_type god_buildings[MAX_GODS][3] = {
        { BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS },
        { BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_COMPLEX_RA },
        { BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH },
        { BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_COMPLEX_SETH },
        { BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_TEMPLE_COMPLEX_BAST },
    };
    for (int god = 0; god < MAX_GODS; god++) {
        if (g_city.religion.gods[god].is_known != GOD_STATUS_UNKNOWN) {
            for (const e_building_type t : god_buildings[god]) {
                allowed_buildings[t] = true;
            }
        }
    }

    // Monuments chosen in the editor (OG monument def ids, see city/monuments.js).
    auto allow_monument_def = [this] (int def_id) {
        switch (def_id) {
        case 1: allowed_buildings[BUILDING_SMALL_BENT_PYRAMID] = true; break;
        case 2: allowed_buildings[BUILDING_MEDIUM_BENT_PYRAMID] = true; break;
        case 3: allowed_buildings[BUILDING_SMALL_MUDBRICK_PYRAMID] = true; break;
        case 4: allowed_buildings[BUILDING_MEDIUM_MUDBRICK_PYRAMID] = true; break;
        case 5: allowed_buildings[BUILDING_LARGE_MUDBRICK_PYRAMID] = true; break;
        case 6: allowed_buildings[BUILDING_MUDBRICK_PYRAMID_COMPLEX] = true; break;
        case 7: allowed_buildings[BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX] = true; break;
        case 8: allowed_buildings[BUILDING_SMALL_STEPPED_PYRAMID] = true; break;
        case 9: allowed_buildings[BUILDING_MEDIUM_STEPPED_PYRAMID] = true; break;
        case 10: allowed_buildings[BUILDING_LARGE_STEPPED_PYRAMID] = true; break;
        case 11: allowed_buildings[BUILDING_STEPPED_PYRAMID_COMPLEX] = true; break;
        case 12: allowed_buildings[BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX] = true; break;
        case 13: allowed_buildings[BUILDING_SMALL_PYRAMID] = true; break;
        case 14: allowed_buildings[BUILDING_MEDIUM_PYRAMID] = true; break;
        case 15: allowed_buildings[BUILDING_LARGE_PYRAMID] = true; break;
        case 16: allowed_buildings[BUILDING_PYRAMID_COMPLEX] = true; break;
        case 17: allowed_buildings[BUILDING_GRAND_PYRAMID_COMPLEX] = true; break;
        case 18: allowed_buildings[BUILDING_SMALL_MASTABA] = true; break;
        case 19: allowed_buildings[BUILDING_MEDIUM_MASTABA] = true; break;
        case 20: allowed_buildings[BUILDING_LARGE_MASTABA] = true; break;
        case 21: allowed_buildings[BUILDING_SPHINX] = true; break;
        case 22: allowed_buildings[BUILDING_SMALL_OBELISK] = true; break;
        case 23: allowed_buildings[BUILDING_LARGE_OBELISK] = true; break;
        case 24: allowed_buildings[BUILDING_SUN_TEMPLE] = true; break;
        case 25: case 26: case 27: allowed_buildings[BUILDING_MAUSOLEUM] = true; break;
        case 28: allowed_buildings[BUILDING_PHAROS_LIGHTHOUSE] = true; break;
        case 29: allowed_buildings[BUILDING_ALEXANDRIA_LIBRARY] = true; break;
        case 30: allowed_buildings[BUILDING_CAESAREUM] = true; break;
        case 31: allowed_buildings[BUILDING_COLOSSI] = true; break;
        case 32: allowed_buildings[BUILDING_TEMPLE_OF_LUXOR] = true; break;
        case 33: allowed_buildings[BUILDING_SMALL_ROYAL_TOMB] = true; break;
        case 34: allowed_buildings[BUILDING_MEDIUM_ROYAL_TOMB] = true; break;
        case 35: allowed_buildings[BUILDING_LARGE_ROYAL_TOMB] = true; break;
        case 36: allowed_buildings[BUILDING_GRAND_ROYAL_TOMB] = true; break;
        case 37: allowed_buildings[BUILDING_ABU_SIMBEL] = true; break;
        default: break;
        }
    };
    allow_monument_def(monuments.first);
    allow_monument_def(monuments.second);
    allow_monument_def(monuments.third);
}

void scenario_data_t::load_metadata(const mission_id_t &missionid, bool is_new_mission) {
    bool mission_config_found = false;
    g_config_arch.r_section(missionid, [this, is_new_mission, &mission_config_found](archive arch) {
        mission_config_found = true;
        meta.tax_percentage.value.clear();
        meta.house_tax_multipliers.value.clear();
        arch.r(meta);
        if (!meta.house_tax_multipliers.value.empty()) {
            static bool warned = false;
            if (!warned) {
                warned = true;
                logs::warn("[scenario] house_tax_multipliers is obsolete and ignored; use tax_percentage (percent the "
                           "city keeps, OG 50)");
            }
        }
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
        // The criteria come from the mission script only; start clean so a previous mission's goals do not linger.
        win_criteria = {};
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

    if (!mission_config_found) {
        apply_editor_allowed_buildings();
    }

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
        // A damaged save may leave the chunk without a terminator.
        vars.load(std::string(data, strnlen(data, sizeof(data))));
    } else {
        std::string save_data = vars.save();
        if (save_data.size() >= sizeof(data)) {
            // Keep whole "key=value\n" lines only, so the truncated text still loads.
            const size_t last_newline = save_data.rfind('\n', sizeof(data) - 2);
            const size_t keep = (last_newline == std::string::npos) ? 0 : last_newline + 1;
            logs::error("scenario vars: %u bytes do not fit the %u-byte save chunk, saving the first %u",
              (unsigned)save_data.size(), (unsigned)sizeof(data), (unsigned)keep);
            save_data.resize(keep);
        }
        memcpy(data, save_data.data(), save_data.size());
        iob->bind(BIND_SIGNATURE_RAW, &data, sizeof(data));
    }
}

bool scenario_building_allowed(e_building_type building_type) {
    if (building_type == BUILDING_DOCK_UP) {
        return g_scenario.allowed_buildings[BUILDING_DOCK]
            || g_scenario.allowed_buildings[BUILDING_DOCK_UP];
    }
    return g_scenario.allowed_buildings[building_type];
}

void scenario_building_allow(e_building_type btype, bool allow) {
    g_scenario.allowed_buildings[btype] = allow;
    if (btype == BUILDING_DOCK) {
        g_scenario.allowed_buildings[BUILDING_DOCK_UP] = allow;
    }
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

    int tmp = 0;
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
    events.update_tick();
    //scenario_slave_revolt_process();
}
