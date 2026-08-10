#include "editor_map_meta.h"

#include "content/vfs.h"
#include "core/bstring.h"
#include "game/game_environment.h"
#include "game/resource.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/types.h"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>

#if defined(_MSC_VER)
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

namespace {

constexpr pcstr META_HEADER = "// akhenaten-editor-map-meta v1\n";

struct request_slot_snap {
    editor_request req{};
    bool filled = false;
};

request_slot_snap g_preserve[event_manager_t::editor_request_slots];
bool g_preserve_active = false;

bstring64 resource_js_token(e_resource r) {
    bstring64 token("RESOURCE_");
    for (pcstr p = resource_name(r); p && *p; ++p) {
        char c[2] = {(char)std::toupper((unsigned char)*p), 0};
        token.cat(c);
    }
    return token;
}

e_resource parse_resource_token(pcstr tok) {
    if (!tok || !tok[0]) {
        return RESOURCE_NONE;
    }
    if (std::isdigit((unsigned char)tok[0]) || tok[0] == '-') {
        int v = std::atoi(tok);
        if (v < 0 || v >= RESOURCE_COUNT) {
            return RESOURCE_NONE;
        }
        return (e_resource)v;
    }
    pcstr name = tok;
    if (strncasecmp(tok, "RESOURCE_", 9) == 0) {
        name = tok + 9;
    }
    bstring64 lower;
    for (pcstr p = name; *p; ++p) {
        char c[2] = {(char)std::tolower((unsigned char)*p), 0};
        lower.cat(c);
    }
    return resource_type(xstring(lower.c_str()));
}

void snapshot_slots(request_slot_snap *slots) {
    for (int i = 0; i < event_manager_t::editor_request_slots; ++i) {
        slots[i].filled = false;
        memset(&slots[i].req, 0, sizeof(slots[i].req));
        g_scenario.events.editor_request_get(i, &slots[i].req);
        if (slots[i].req.resource != RESOURCE_NONE && slots[i].req.amount > 0) {
            slots[i].filled = true;
        }
    }
}

void restore_slots(const request_slot_snap *slots) {
    g_scenario.events.clear_for_editor();
    for (int i = 0; i < event_manager_t::editor_request_slots; ++i) {
        if (slots[i].filled) {
            g_scenario.events.editor_request_save(i, &slots[i].req);
        }
    }
}

bool has_key(pcstr block, pcstr key) {
    bstring64 needle(key, ":");
    for (pcstr p = block; (p = std::strstr(p, needle.c_str())) != nullptr; ++p) {
        if (p > block) {
            const char prev = p[-1];
            if (std::isalnum((unsigned char)prev) || prev == '_') {
                continue;
            }
        }
        return true;
    }
    return false;
}

bool read_int_field(pcstr block, pcstr key, int *out) {
    // Match "key:" but not as a suffix of another identifier (e.g. type vs attack_type).
    bstring64 needle(key, ":");
    const size_t key_len = std::strlen(key);
    for (pcstr p = block; (p = std::strstr(p, needle.c_str())) != nullptr; ++p) {
        if (p > block) {
            const char prev = p[-1];
            if (std::isalnum((unsigned char)prev) || prev == '_') {
                continue;
            }
        }
        p += key_len + 1;
        while (*p && std::isspace((unsigned char)*p)) {
            ++p;
        }
        if (!*p) {
            return false;
        }
        *out = std::atoi(p);
        return true;
    }
    return false;
}

bool read_resource_field(pcstr block, e_resource *out) {
    if (!has_key(block, "resource")) {
        return false;
    }
    pcstr p = std::strstr(block, "resource:");
    // has_key already validated a word-boundary match; find that occurrence.
    for (; p; p = std::strstr(p + 1, "resource:")) {
        if (p > block) {
            const char prev = p[-1];
            if (std::isalnum((unsigned char)prev) || prev == '_') {
                continue;
            }
        }
        break;
    }
    if (!p) {
        return false;
    }
    p += 9;
    while (*p && std::isspace((unsigned char)*p)) {
        ++p;
    }
    char tok[64] = {0};
    int n = 0;
    while (*p && !std::isspace((unsigned char)*p) && *p != ',' && *p != '}' && n < 63) {
        tok[n++] = *p++;
    }
    tok[n] = 0;
    *out = parse_resource_token(tok);
    return true;
}

int count_filled_requests(const request_slot_snap *slots) {
    int filled = 0;
    for (int i = 0; i < event_manager_t::editor_request_slots; ++i) {
        filled += slots[i].filled ? 1 : 0;
    }
    return filled;
}

int count_filled_invasions() {
    int n = 0;
    for (int i = 0; i < MAX_INVASIONS; ++i) {
        if (g_scenario.invasions[i].type) {
            ++n;
        }
    }
    return n;
}

int count_filled_price_changes() {
    int n = 0;
    for (int i = 0; i < MAX_PRICE_CHANGES; ++i) {
        if (g_scenario.price_changes[i].resource != RESOURCE_NONE && g_scenario.price_changes[i].year) {
            ++n;
        }
    }
    return n;
}

int count_filled_demand_changes() {
    int n = 0;
    for (int i = 0; i < MAX_DEMAND_CHANGES; ++i) {
        if (g_scenario.demand_changes[i].resource != RESOURCE_NONE && g_scenario.demand_changes[i].year) {
            ++n;
        }
    }
    return n;
}

bool win_criteria_active() {
    const auto &w = g_scenario.win_criteria;
    return w.culture.enabled || w.prosperity.enabled || w.monuments.enabled || w.kingdom.enabled
           || w.population.enabled || w.housing_count.enabled || w.housing_level.enabled
           || w.time_limit.enabled || w.survival_time.enabled || g_scenario.is_open_play;
}

void apply_win_criteria_block(pcstr block) {
    auto &w = g_scenario.win_criteria;
    int v = 0;
    if (read_int_field(block, "culture_enabled", &v))
        w.culture.enabled = v ? 1 : 0;
    if (read_int_field(block, "culture_goal", &v))
        w.culture.goal = v;
    if (read_int_field(block, "prosperity_enabled", &v))
        w.prosperity.enabled = v ? 1 : 0;
    if (read_int_field(block, "prosperity_goal", &v))
        w.prosperity.goal = v;
    if (read_int_field(block, "monuments_enabled", &v))
        w.monuments.enabled = v ? 1 : 0;
    if (read_int_field(block, "monuments_goal", &v))
        w.monuments.goal = v;
    if (read_int_field(block, "kingdom_enabled", &v))
        w.kingdom.enabled = v ? 1 : 0;
    if (read_int_field(block, "kingdom_goal", &v))
        w.kingdom.goal = v;
    if (read_int_field(block, "population_enabled", &v))
        w.population.enabled = v ? 1 : 0;
    if (read_int_field(block, "population_goal", &v))
        w.population.goal = v;
    if (read_int_field(block, "housing_count_enabled", &v))
        w.housing_count.enabled = v ? 1 : 0;
    if (read_int_field(block, "housing_count_goal", &v))
        w.housing_count.goal = v;
    if (read_int_field(block, "housing_level_enabled", &v))
        w.housing_level.enabled = v ? 1 : 0;
    if (read_int_field(block, "housing_level_goal", &v))
        w.housing_level.goal = v;
    if (read_int_field(block, "time_limit_enabled", &v))
        w.time_limit.enabled = v ? 1 : 0;
    if (read_int_field(block, "time_limit_years", &v))
        w.time_limit.years = v;
    if (read_int_field(block, "survival_enabled", &v))
        w.survival_time.enabled = v ? 1 : 0;
    if (read_int_field(block, "survival_years", &v))
        w.survival_time.years = v;
    if (read_int_field(block, "milestone25", &v))
        w.milestone25_year = v;
    if (read_int_field(block, "milestone50", &v))
        w.milestone50_year = v;
    if (read_int_field(block, "milestone75", &v))
        w.milestone75_year = v;
    if (read_int_field(block, "open_play", &v))
        g_scenario.is_open_play = v != 0;
}

} // namespace

void editor_invasions_clear() {
    for (int i = 0; i < MAX_INVASIONS; ++i) {
        g_scenario.invasions[i] = {};
        g_scenario.invasions[i].from = 8;
        g_scenario.invasions[i].attack_type = FORMATION_ATTACK_FOOD_CHAIN;
    }
}

void editor_price_changes_clear() {
    for (int i = 0; i < MAX_PRICE_CHANGES; ++i) {
        g_scenario.price_changes[i] = {};
    }
}

void editor_demand_changes_clear() {
    for (int i = 0; i < MAX_DEMAND_CHANGES; ++i) {
        g_scenario.demand_changes[i] = {};
    }
}

vfs::path editor_map_meta_path(pcstr map_path) {
    bstring256 path(map_path ? map_path : "");
    char *dot = std::strrchr(path.data(), '.');
    if (dot && strcasecmp(dot, ".map") == 0) {
        std::snprintf(dot, (size_t)(bstring256::capacity - (dot - path.data())), ".meta.js");
    } else {
        path.cat(".meta.js");
    }
    vfs::path meta(path.c_str());
    vfs::path resolved = meta.resolve();
    return resolved.empty() ? meta : resolved;
}

void editor_requests_preserve_begin() {
    snapshot_slots(g_preserve);
    g_preserve_active = true;
    g_scenario.events.clear_for_editor();
}

void editor_requests_preserve_end() {
    if (!g_preserve_active) {
        return;
    }
    restore_slots(g_preserve);
    g_preserve_active = false;
}

void editor_map_meta_remove(pcstr map_path) {
    vfs::path meta = editor_map_meta_path(map_path);
    if (vfs::file_exists(meta)) {
        vfs::file_remove(meta.c_str());
    }
}

bool editor_map_meta_write(pcstr map_path) {
    if (!map_path || !map_path[0]) {
        return false;
    }

    request_slot_snap slots[event_manager_t::editor_request_slots];
    snapshot_slots(slots);
    const int req_n = count_filled_requests(slots);
    const int inv_n = count_filled_invasions();
    const int price_n = count_filled_price_changes();
    const int demand_n = count_filled_demand_changes();
    const bool win_n = win_criteria_active();

    if (req_n == 0 && inv_n == 0 && price_n == 0 && demand_n == 0 && !win_n) {
        editor_map_meta_remove(map_path);
        return true;
    }

    vfs::path meta = editor_map_meta_path(map_path);
    FILE *fp = vfs::file_open_os(meta.c_str(), "wb");
    if (!fp) {
        vfs::create_folders(vfs::MAPS_FOLDER);
        fp = vfs::file_open_os(meta.c_str(), "wb");
    }
    if (!fp) {
        return false;
    }

    std::fputs(META_HEADER, fp);
    std::fputs("// Editor / custom-map sidecar (schedules not in .map; win also in scenario_info).\n", fp);
    std::fputs("// requests / invasions / price_changes / demand_changes / win_criteria.\n", fp);
    std::fputs("editor_map_meta {\n", fp);

    std::fputs("\trequests [\n", fp);
    for (int i = 0; i < event_manager_t::editor_request_slots; ++i) {
        if (!slots[i].filled) {
            continue;
        }
        const editor_request &r = slots[i].req;
        bstring64 res_tok = resource_js_token(r.resource);
        std::fprintf(fp,
                     "\t\t{ slot: %d, year: %d, resource: %s, amount: %d, deadline_years: %d, kingdom: %d }\n",
                     i,
                     r.year,
                     res_tok.c_str(),
                     r.amount,
                     r.deadline_years,
                     r.kingdom);
    }
    std::fputs("\t]\n", fp);

    std::fputs("\tinvasions [\n", fp);
    for (int i = 0; i < MAX_INVASIONS; ++i) {
        const invasion_t &inv = g_scenario.invasions[i];
        if (!inv.type) {
            continue;
        }
        std::fprintf(fp,
                     "\t\t{ slot: %d, year: %d, type: %d, amount: %d, from: %d, attack_type: %d }\n",
                     i,
                     inv.year,
                     inv.type,
                     inv.amount,
                     inv.from,
                     (int)inv.attack_type);
    }
    std::fputs("\t]\n", fp);

    std::fputs("\tprice_changes [\n", fp);
    for (int i = 0; i < MAX_PRICE_CHANGES; ++i) {
        const price_change_t &pc = g_scenario.price_changes[i];
        if (pc.resource == RESOURCE_NONE || !pc.year) {
            continue;
        }
        bstring64 res_tok = resource_js_token(pc.resource);
        std::fprintf(fp,
                     "\t\t{ slot: %d, year: %d, resource: %s, amount: %d, is_rise: %d }\n",
                     i,
                     pc.year,
                     res_tok.c_str(),
                     pc.amount,
                     pc.is_rise ? 1 : 0);
    }
    std::fputs("\t]\n", fp);

    std::fputs("\tdemand_changes [\n", fp);
    for (int i = 0; i < MAX_DEMAND_CHANGES; ++i) {
        const demand_change_t &dc = g_scenario.demand_changes[i];
        if (dc.resource == RESOURCE_NONE || !dc.year) {
            continue;
        }
        bstring64 res_tok = resource_js_token(dc.resource);
        std::fprintf(fp,
                     "\t\t{ slot: %d, year: %d, resource: %s, route_id: %d, is_rise: %d }\n",
                     i,
                     dc.year,
                     res_tok.c_str(),
                     dc.route_id,
                     dc.is_rise ? 1 : 0);
    }
    std::fputs("\t]\n", fp);

    if (win_n) {
        const auto &w = g_scenario.win_criteria;
        std::fputs("\twin_criteria {\n", fp);
        std::fprintf(fp,
                     "\t\tculture_enabled: %d, culture_goal: %d\n"
                     "\t\tprosperity_enabled: %d, prosperity_goal: %d\n"
                     "\t\tmonuments_enabled: %d, monuments_goal: %d\n"
                     "\t\tkingdom_enabled: %d, kingdom_goal: %d\n"
                     "\t\tpopulation_enabled: %d, population_goal: %d\n"
                     "\t\thousing_count_enabled: %d, housing_count_goal: %d\n"
                     "\t\thousing_level_enabled: %d, housing_level_goal: %d\n"
                     "\t\ttime_limit_enabled: %d, time_limit_years: %d\n"
                     "\t\tsurvival_enabled: %d, survival_years: %d\n"
                     "\t\tmilestone25: %d, milestone50: %d, milestone75: %d\n"
                     "\t\topen_play: %d\n",
                     w.culture.enabled ? 1 : 0,
                     w.culture.goal,
                     w.prosperity.enabled ? 1 : 0,
                     w.prosperity.goal,
                     w.monuments.enabled ? 1 : 0,
                     w.monuments.goal,
                     w.kingdom.enabled ? 1 : 0,
                     w.kingdom.goal,
                     w.population.enabled ? 1 : 0,
                     w.population.goal,
                     w.housing_count.enabled ? 1 : 0,
                     w.housing_count.goal,
                     w.housing_level.enabled ? 1 : 0,
                     w.housing_level.goal,
                     w.time_limit.enabled ? 1 : 0,
                     w.time_limit.years,
                     w.survival_time.enabled ? 1 : 0,
                     w.survival_time.years,
                     w.milestone25_year,
                     w.milestone50_year,
                     w.milestone75_year,
                     g_scenario.is_open_play ? 1 : 0);
        std::fputs("\t}\n", fp);
    }

    std::fputs("}\n", fp);
    std::fclose(fp);
    return true;
}

bool editor_map_meta_load(pcstr map_path) {
    if (!map_path || !map_path[0]) {
        return false;
    }

    vfs::path meta = editor_map_meta_path(map_path);
    if (!vfs::file_exists(meta)) {
        return false;
    }

    FILE *fp = vfs::file_open_os(meta.c_str(), "rb");
    if (!fp) {
        return false;
    }

    std::fseek(fp, 0, SEEK_END);
    long sz = std::ftell(fp);
    std::fseek(fp, 0, SEEK_SET);
    if (sz <= 0 || sz > 256 * 1024) {
        std::fclose(fp);
        return false;
    }

    std::string text((size_t)sz, '\0');
    size_t nread = std::fread(text.data(), 1, (size_t)sz, fp);
    std::fclose(fp);
    text.resize(nread);

    editor_invasions_clear();
    editor_price_changes_clear();
    editor_demand_changes_clear();

    bool any = false;
    pcstr p = text.c_str();
    while ((p = std::strstr(p, "{")) != nullptr) {
        pcstr end = std::strstr(p, "}");
        if (!end) {
            break;
        }

        std::string block(p, end - p + 1);

        // Flat win_criteria { culture_enabled: … } — no slot field.
        if (has_key(block.c_str(), "culture_goal") || has_key(block.c_str(), "culture_enabled")
            || has_key(block.c_str(), "population_goal") || has_key(block.c_str(), "open_play")) {
            apply_win_criteria_block(block.c_str());
            any = true;
            p = end + 1;
            continue;
        }

        int slot = -1;
        if (!read_int_field(block.c_str(), "slot", &slot)) {
            p = end + 1;
            continue;
        }

        // Discriminate rows that share resource: — route_id=demand, is_rise=price,
        // deadline_years=request; invasions use type:/attack_type: without resource.
        if (has_key(block.c_str(), "route_id")) {
            int year = 0;
            int route_id = 0;
            int is_rise = 0;
            e_resource resource = RESOURCE_NONE;
            read_int_field(block.c_str(), "year", &year);
            read_int_field(block.c_str(), "route_id", &route_id);
            read_int_field(block.c_str(), "is_rise", &is_rise);
            read_resource_field(block.c_str(), &resource);

            if (slot >= 0 && slot < MAX_DEMAND_CHANGES && resource != RESOURCE_NONE && year > 0) {
                demand_change_t &dc = g_scenario.demand_changes[slot];
                dc.year = year;
                dc.resource = resource;
                dc.route_id = route_id;
                dc.is_rise = is_rise ? 1 : 0;
                dc.month = 0;
                any = true;
            }
        } else if (has_key(block.c_str(), "is_rise")) {
            int year = 0;
            int amount = 0;
            int is_rise = 0;
            e_resource resource = RESOURCE_NONE;
            read_int_field(block.c_str(), "year", &year);
            read_int_field(block.c_str(), "amount", &amount);
            read_int_field(block.c_str(), "is_rise", &is_rise);
            read_resource_field(block.c_str(), &resource);

            if (slot >= 0 && slot < MAX_PRICE_CHANGES && resource != RESOURCE_NONE && year > 0) {
                price_change_t &pc = g_scenario.price_changes[slot];
                pc.year = year;
                pc.resource = resource;
                pc.amount = amount;
                pc.is_rise = is_rise ? 1 : 0;
                pc.month = 0;
                any = true;
            }
        } else if (has_key(block.c_str(), "resource")) {
            int year = 0;
            int amount = 0;
            int deadline_years = 1;
            int kingdom = 0;
            e_resource resource = RESOURCE_NONE;
            read_int_field(block.c_str(), "year", &year);
            read_int_field(block.c_str(), "amount", &amount);
            read_int_field(block.c_str(), "deadline_years", &deadline_years);
            read_int_field(block.c_str(), "kingdom", &kingdom);
            read_resource_field(block.c_str(), &resource);

            if (slot >= 0 && slot < event_manager_t::editor_request_slots && resource != RESOURCE_NONE && amount > 0) {
                editor_request r{};
                r.year = year;
                r.resource = resource;
                r.amount = amount;
                r.deadline_years = deadline_years;
                r.kingdom = kingdom;
                g_scenario.events.editor_request_save(slot, &r);
                any = true;
            }
        } else if (has_key(block.c_str(), "type")) {
            int year = 0;
            int type = 0;
            int amount = 0;
            int from = 8;
            int attack_type = FORMATION_ATTACK_FOOD_CHAIN;
            read_int_field(block.c_str(), "year", &year);
            read_int_field(block.c_str(), "type", &type);
            read_int_field(block.c_str(), "amount", &amount);
            read_int_field(block.c_str(), "from", &from);
            read_int_field(block.c_str(), "attack_type", &attack_type);

            if (slot >= 0 && slot < MAX_INVASIONS && type > 0 && amount > 0) {
                invasion_t &inv = g_scenario.invasions[slot];
                inv.year = year;
                inv.type = type;
                inv.amount = amount;
                inv.from = from;
                inv.attack_type = (e_formation_attack_type)attack_type;
                inv.month = 0;
                any = true;
            }
        }

        p = end + 1;
    }

    return any;
}
