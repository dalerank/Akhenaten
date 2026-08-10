// Integral-test helpers: dump mission1.pak scenario data WITHOUT JS mission overlays
// (see GamestateIO::load_mission_pak_raw). Call from ad-hoc tests/99_tmp_*.js via
// __test_mission_pak_dump(scenario_id); do not keep a permanent dump test.

#include "js_game.h"

#include "building/building.h"
#include "building/building_type.h"
#include "city/city.h"
#include "city/city_religion.h"
#include "core/log.h"
#include "core/profiler.h"
#include "core/string.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "empire/trade_route.h"
#include "empire/type.h"
#include "figure/figure_type.h"
#include "game/game_environment.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "grid/grid.h"
#include "grid/point.h"
#include "grid/terrain.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "js/js_defines.h"
#include "platform/arguments.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/types.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#ifdef main
#undef main
#endif

static void dump_marker(pcstr fmt, ...) {
    char buf[1280];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof buf, fmt, args);
    va_end(args);

    if (g_args.is_integral_tests()) {
        logs::info("[test-marker] %s", buf);
    }
    logs::info("%s", buf);
}

static pcstr safe_token(pcstr name) {
    return (name && name[0]) ? name : "?";
}

static void append_resource_list(char* out, size_t out_sz, const bool* flags) {
    out[0] = 0;
    size_t used = 0;
    for (int r = 1; r < RESOURCES_MAX; r++) {
        if (!flags[r]) {
            continue;
        }
        pcstr name = resource_name((e_resource)r);
        const size_t nlen = strlen(name);
        if (used + nlen + 2 >= out_sz) {
            break;
        }
        if (used > 0) {
            out[used++] = ',';
        }
        memcpy(out + used, name, nlen);
        used += nlen;
        out[used] = 0;
    }
}

static pcstr climate_name(int climate) {
    switch (climate) {
    case CLIMATE_CENTRAL: return "central";
    case CLIMATE_NORTHERN: return "northern";
    case CLIMATE_DESERT: return "desert";
    default: return "?";
    }
}

static void dump_scenario_header(int scenario_id) {
    dump_marker("pak_dump_ok:%d", scenario_id);
    dump_marker("pak_start_year:%d", g_scenario.start_year);
    dump_marker("pak_player_rank:%d", g_scenario.player_rank);
    dump_marker("pak_player_faction:%d|incarnation:%d|pharaoh:%d",
        g_scenario.player_faction,
        g_scenario.player_incarnation,
        g_scenario.current_pharaoh);
    dump_marker("pak_enemy_id:%d(%s)",
        (int)g_scenario.enemy_id,
        safe_token(e_enemy_type_tokens.name(g_scenario.enemy_id)));
    dump_marker("pak_funds:%d|loan:%d|debt_interest:%d",
        g_scenario.finance.initial_funds,
        g_scenario.finance.rescue_loan,
        g_scenario.debt_interest_rate);
    dump_marker("pak_climate:%d(%s)|open_play:%d|image_id:%d",
        g_scenario.climate,
        climate_name(g_scenario.climate),
        g_scenario.is_open_play ? 1 : 0,
        g_scenario.image_id);
    dump_marker("pak_env:animals=%d|flotsam=%d|alt_predator=%d",
        g_scenario.env.has_animals ? 1 : 0,
        g_scenario.env.flotsam_enabled ? 1 : 0,
        g_scenario.alt_predator_type ? 1 : 0);
    dump_marker("pak_empire:id=%d|expanded=%d|expansion_year=%d",
        g_scenario.empire.id,
        g_scenario.empire.is_expanded,
        g_scenario.empire.expansion_year);

    pcstr subtitle = g_scenario.subtitle.c_str();
    pcstr brief = g_scenario.brief_description.c_str();
    dump_marker("pak_subtitle:%s", (subtitle && subtitle[0]) ? subtitle : "-");
    dump_marker("pak_brief:%s", (brief && brief[0]) ? brief : "-");
}

static void dump_win_criteria() {
    const auto& w = g_scenario.win_criteria;
    dump_marker("pak_win:pop=%d/%d|culture=%d/%d|prosperity=%d/%d|monuments=%d/%d|kingdom=%d/%d",
        w.population.enabled ? 1 : 0,
        w.population.goal,
        w.culture.enabled ? 1 : 0,
        w.culture.goal,
        w.prosperity.enabled ? 1 : 0,
        w.prosperity.goal,
        w.monuments.enabled ? 1 : 0,
        w.monuments.goal,
        w.kingdom.enabled ? 1 : 0,
        w.kingdom.goal);
    dump_marker("pak_win_housing:count=%d/%d|level=%d/%d",
        w.housing_count.enabled ? 1 : 0,
        w.housing_count.goal,
        w.housing_level.enabled ? 1 : 0,
        w.housing_level.goal);
    dump_marker("pak_win_time:limit=%d/%d|survival=%d/%d|m25=%d|m50=%d|m75=%d",
        w.time_limit.enabled ? 1 : 0,
        w.time_limit.years,
        w.survival_time.enabled ? 1 : 0,
        w.survival_time.years,
        w.milestone25_year,
        w.milestone50_year,
        w.milestone75_year);
}

static void dump_map_points() {
    dump_marker("pak_map:w=%d|h=%d|start_offset=%d|border=%d",
        g_scenario.map.width,
        g_scenario.map.height,
        g_scenario.map.start_offset,
        g_scenario.map.border_size);

    auto dump_tile = [](pcstr tag, tile2i t) {
        if (!t.valid()) {
            dump_marker("%s:invalid", tag);
            return;
        }
        dump_marker("%s:x=%d|y=%d", tag, t.x(), t.y());
    };

    dump_tile("pak_entry", g_scenario.entry_point);
    dump_tile("pak_exit", g_scenario.exit_point);
    dump_tile("pak_river_entry", g_scenario.river_entry_point);
    dump_tile("pak_river_exit", g_scenario.river_exit_point);
    dump_tile("pak_earthquake", g_scenario.earthquake_point);

    int herd_n = 0;
    for (int i = 0; i < (int)g_scenario.herd_points_predator.size(); i++) {
        const herd_point_t &hp = g_scenario.herd_points_predator[i];
        if (!hp.valid()) {
            continue;
        }
        dump_marker("pak_herd:i=%d|x=%d|y=%d|type=%d(%s)",
            i,
            hp.tile.x(),
            hp.tile.y(),
            (int)hp.type,
            safe_token(e_figure_type_tokens.name(hp.type)));
        herd_n++;
    }
    dump_marker("pak_herd_count:%d", herd_n);

    int prey_n = 0;
    for (int i = 0; i < (int)g_scenario.herd_points_prey.size(); i++) {
        const herd_point_t &hp = g_scenario.herd_points_prey[i];
        if (!hp.valid()) {
            continue;
        }
        dump_marker("pak_prey:i=%d|x=%d|y=%d|type=%d(%s)",
            i,
            hp.tile.x(),
            hp.tile.y(),
            (int)hp.type,
            safe_token(e_figure_type_tokens.name(hp.type)));
        prey_n++;
    }
    dump_marker("pak_prey_count:%d", prey_n);

    int fish_n = 0;
    for (int i = 0; i < (int)g_scenario.fishing_points.size(); i++) {
        tile2i t = g_scenario.fishing_points[i];
        if (!t.valid()) {
            continue;
        }
        dump_marker("pak_fish:i=%d|x=%d|y=%d", i, t.x(), t.y());
        fish_n++;
    }
    dump_marker("pak_fish_count:%d", fish_n);

    int disembark_n = 0;
    for (int i = 0; i < (int)g_scenario.disembark_points.size(); i++) {
        tile2i t = g_scenario.disembark_points[i];
        if (!t.valid()) {
            continue;
        }
        dump_marker("pak_disembark:i=%d|x=%d|y=%d", i, t.x(), t.y());
        disembark_n++;
    }
    dump_marker("pak_disembark_count:%d", disembark_n);
}

static void dump_invasion_points() {
    int land_n = 0;
    for (int i = 0; i < (int)g_scenario.invasion_points_land.size(); i++) {
        tile2i t = g_scenario.invasion_points_land[i];
        if (!t.valid()) {
            continue;
        }
        dump_marker("pak_inv_land:i=%d|x=%d|y=%d", i, t.x(), t.y());
        land_n++;
    }

    int sea_n = 0;
    for (int i = 0; i < (int)g_scenario.invasion_points_sea.size(); i++) {
        tile2i t = g_scenario.invasion_points_sea[i];
        if (!t.valid()) {
            continue;
        }
        dump_marker("pak_inv_sea:i=%d|x=%d|y=%d", i, t.x(), t.y());
        sea_n++;
    }

    dump_marker("pak_inv_land_count:%d", land_n);
    dump_marker("pak_inv_sea_count:%d", sea_n);
}

static void dump_monuments() {
    dump_marker("pak_monuments:first=%d|second=%d|third=%d",
        g_scenario.monuments.first,
        g_scenario.monuments.second,
        g_scenario.monuments.third);

    int burial_n = 0;
    for (int r = 1; r < RESOURCES_MAX; r++) {
        const int req = g_scenario.monuments.burial_provisions[r].required;
        const int dispatched = g_scenario.monuments.burial_provisions[r].dispatched;
        if (req <= 0 && dispatched <= 0) {
            continue;
        }
        dump_marker("pak_burial:res=%s(%d)|required=%d|dispatched=%d",
            safe_token(resource_name((e_resource)r)),
            r,
            req,
            dispatched);
        burial_n++;
    }
    dump_marker("pak_burial_count:%d", burial_n);
}

static void dump_gods() {
    char known[256] = {0};
    size_t used = 0;
    for (int g = 0; g < MAX_GODS; g++) {
        const e_god_status st = g_city.religion.gods[g].is_known;
        if (st == GOD_STATUS_UNKNOWN) {
            continue;
        }
        pcstr name = e_god_tokens.name((e_god)g);
        const size_t nlen = name ? strlen(name) : 1;
        if (used + nlen + 8 >= sizeof known) {
            break;
        }
        if (used > 0) {
            known[used++] = ',';
        }
        if (name) {
            memcpy(known + used, name, nlen);
            used += nlen;
        } else {
            known[used++] = '?';
        }
        used += snprintf(known + used, sizeof known - used, ":%d", (int)st);
    }
    dump_marker("pak_gods:%s", known[0] ? known : "-");
}

static pcstr empire_city_type_name(e_empire_city type) {
    switch (type) {
    case EMPIRE_CITY_OURS: return "ours";
    case EMPIRE_CITY_PHARAOH_TRADING: return "pharaoh_trading";
    case EMPIRE_CITY_PHARAOH: return "pharaoh";
    case EMPIRE_CITY_EGYPTIAN_TRADING: return "egyptian_trading";
    case EMPIRE_CITY_EGYPTIAN: return "egyptian";
    case EMPIRE_CITY_FOREIGN_TRADING: return "foreign_trading";
    case EMPIRE_CITY_FOREIGN: return "foreign";
    default: return "?";
    }
}

static void dump_empire_cities() {
    char sells[512];
    char buys[512];
    int trade_cities = 0;
    int map_cities = 0;

    for (int i = 0; i < g_empire.get_cities().size(); i++) {
        const empire_city& city = g_empire.get_cities()[i];
        if (!city.in_use) {
            continue;
        }

        pcstr name = (pcstr)lang_get_string(195, city.name_id);
        if (!name || !name[0]) {
            name = "?";
        }

        append_resource_list(sells, sizeof sells, city.sells_resource);
        append_resource_list(buys, sizeof buys, city.buys_resource);

        const bool has_trade = sells[0] || buys[0] || city.can_trade();
        map_cities++;
        if (has_trade || city.type == EMPIRE_CITY_OURS) {
            trade_cities++;
        }

        // All in-use cities on the empire map (trading + display-only).
        dump_marker("pak_map_city:%s|id=%d|type=%s(%d)|trade=%d|open=%d|sea=%d|cost=%d|route=%d|sells=%s|buys=%s",
            name,
            i,
            empire_city_type_name(city.type),
            (int)city.type,
            has_trade ? 1 : 0,
            city.is_open ? 1 : 0,
            city.is_sea_trade ? 1 : 0,
            (int)city.cost_to_open,
            city.route_id,
            sells[0] ? sells : "-",
            buys[0] ? buys : "-");

        if (!has_trade && city.type != EMPIRE_CITY_OURS) {
            continue;
        }

        dump_marker("pak_city:%s|id=%d|type=%d|open=%d|sea=%d|cost=%d|route=%d|sells=%s|buys=%s",
            name,
            i,
            (int)city.type,
            city.is_open ? 1 : 0,
            city.is_sea_trade ? 1 : 0,
            (int)city.cost_to_open,
            city.route_id,
            sells[0] ? sells : "-",
            buys[0] ? buys : "-");

        // Per-route yearly limits (only non-zero).
        if (city.route_id > 0) {
            const trade_route& route = city.get_route();
            char limits[512] = {0};
            size_t used = 0;
            for (int r = 1; r < RESOURCES_MAX; r++) {
                const int lim = route.limit((e_resource)r, trade_route::e_limit_base_only);
                if (lim <= 0) {
                    continue;
                }
                pcstr rn = resource_name((e_resource)r);
                const int n = snprintf(limits + used, sizeof limits - used, "%s%s=%d",
                    used ? "," : "",
                    rn ? rn : "?",
                    lim);
                if (n <= 0 || used + (size_t)n >= sizeof limits) {
                    break;
                }
                used += (size_t)n;
            }
            if (limits[0]) {
                dump_marker("pak_route_limits:city=%s|route=%d|%s", name, city.route_id, limits);
            }
        }
    }

    dump_marker("pak_map_city_count:%d", map_cities);
    dump_marker("pak_trade_city_count:%d", trade_cities);
}

static pcstr empire_object_type_name(int type) {
    switch (type) {
    case EMPIRE_OBJECT_ORNAMENT: return "ornament";
    case EMPIRE_OBJECT_CITY: return "city";
    case EMPIRE_OBJECT_TEXT: return "text";
    case EMPIRE_OBJECT_BATTLE_ICON: return "battle_icon";
    case EMPIRE_OBJECT_LAND_TRADE_ROUTE: return "land_route";
    case EMPIRE_OBJECT_SEA_TRADE_ROUTE: return "sea_route";
    case EMPIRE_OBJECT_KINGDOME_ARMY: return "kingdome_army";
    case EMPIRE_OBJECT_ENEMY_ARMY: return "enemy_army";
    case EMPIRE_OBJECT_DISTANT_BATTLE_ROUTE: return "distant_battle_route";
    case EMPIRE_OBJECT_TRADER: return "trader";
    case EMPIRE_OBJECT_TRADE_ROUTE: return "trade_route";
    default: return "?";
    }
}

static void dump_empire_objects() {
    int counts[EMPIRE_OBJECT_COUNT] = {};
    int total = 0;

    g_empire.foreach_object([&](int object_index, const empire_object& obj) {
        total++;
        if (obj.type >= 0 && obj.type < EMPIRE_OBJECT_COUNT) {
            counts[obj.type]++;
        }

        pcstr city_name = "-";
        if (obj.type == EMPIRE_OBJECT_CITY) {
            const int city_id = g_empire.get_city_for_object(object_index);
            const empire_city* city = city_id ? g_empire.city(city_id) : nullptr;
            if (city) {
                pcstr name = (pcstr)lang_get_string(195, city->name_id);
                if (name && name[0]) {
                    city_name = name;
                }
            }
        } else if (obj.type == EMPIRE_OBJECT_TEXT) {
            const full_empire_object* full = g_empire.get_full_object(object_index);
            if (full) {
                pcstr name = (pcstr)lang_get_string(196, full->city_name_id);
                if (name && name[0]) {
                    city_name = name;
                }
            }
        }

        dump_marker("pak_map_obj:%s|idx=%d|pos=%d,%d|img=%d|route=%d|city=%s|path=%d|years=%d",
            empire_object_type_name(obj.type),
            object_index,
            obj.pos.x,
            obj.pos.y,
            obj.image_id,
            (int)obj.trade_route_id,
            city_name,
            obj.invasion_path_id,
            obj.invasion_years);

        if (obj.type == EMPIRE_OBJECT_ORNAMENT) {
            const full_empire_object* full = g_empire.get_full_object(object_index);
            dump_marker("pak_ornament_meta:idx=%d|img=%d|exp_img=%d|w=%d|h=%d",
                object_index,
                obj.image_id,
                full ? full->obj.expanded.image_id : -1,
                full ? full->obj.width : -1,
                full ? full->obj.height : -1);
        }
    });

    dump_marker("pak_map_obj_count:total=%d|ornament=%d|city=%d|text=%d|battle=%d|land_route=%d|sea_route=%d|army=%d|enemy_army=%d|distant=%d",
        total,
        counts[EMPIRE_OBJECT_ORNAMENT],
        counts[EMPIRE_OBJECT_CITY],
        counts[EMPIRE_OBJECT_TEXT],
        counts[EMPIRE_OBJECT_BATTLE_ICON],
        counts[EMPIRE_OBJECT_LAND_TRADE_ROUTE],
        counts[EMPIRE_OBJECT_SEA_TRADE_ROUTE],
        counts[EMPIRE_OBJECT_KINGDOME_ARMY],
        counts[EMPIRE_OBJECT_ENEMY_ARMY],
        counts[EMPIRE_OBJECT_DISTANT_BATTLE_ROUTE]);
}

static void dump_empire_routes() {
    int n = 0;
    for (int id = 0; id < 50; id++) {
        const map_route_object& route = g_empire.get_route_object(id);
        if (!route.in_use || route.num_points == 0) {
            continue;
        }

        char pts[2048] = {0};
        size_t used = 0;
        const int count = std::min<int>(route.num_points, 80);
        for (int i = 0; i < count; i++) {
            // Dump every slot up to num_points — is_in_use is often unset in pak polylines.
            const int w = snprintf(pts + used, sizeof pts - used, "%s%d,%d",
                used ? ";" : "",
                route.points[i].p.x,
                route.points[i].p.y);
            if (w <= 0 || used + (size_t)w >= sizeof pts) {
                break;
            }
            used += (size_t)w;
        }

        dump_marker("pak_map_route:id=%d|type=%d|n=%d|len=%d|pts=%s",
            id,
            (int)route.route_type,
            (int)route.num_points,
            route.length,
            pts[0] ? pts : "-");
        // Also split long routes for copy-paste into mission JS.
        const int chunk = 12;
        for (int start = 0; start < count; start += chunk) {
            char chunk_pts[512] = {0};
            size_t cu = 0;
            const int end = std::min(start + chunk, count);
            for (int i = start; i < end; i++) {
                const int w = snprintf(chunk_pts + cu, sizeof chunk_pts - cu, "%s[%d,%d]",
                    cu ? "," : "",
                    route.points[i].p.x,
                    route.points[i].p.y);
                if (w <= 0 || cu + (size_t)w >= sizeof chunk_pts) {
                    break;
                }
                cu += (size_t)w;
            }
            dump_marker("pak_map_route_chunk:id=%d|i=%d-%d|%s", id, start, end - 1, chunk_pts);
        }
        n++;
    }
    dump_marker("pak_map_route_count:%d", n);
}

static pcstr invader_name(int item) {
    switch (item) {
    case EVENT_INVADER_ENEMY: return "enemy";
    case EVENT_INVADER_EGYPT: return "egypt";
    case EVENT_INVADER_PHARAOH: return "pharaoh";
    case EVENT_INVADER_BEDUINS: return "beduins";
    default: return "?";
    }
}

static pcstr trigger_name(int trigger) {
    switch (trigger) {
    case EVENT_TRIGGER_ONCE: return "once";
    case EVENT_TRIGGER_ONLY_VIA_EVENT: return "chain_only";
    case EVENT_TRIGGER_RECURRING: return "recurring";
    case EVENT_TRIGGER_ALREADY_FIRED: return "already_fired";
    case EVENT_TRIGGER_ACTIVATED_8: return "activated_8";
    case EVENT_TRIGGER_BY_RATING: return "by_rating_legacy10";
    case EVENT_TRIGGER_ACTIVATED_12: return "activated_12";
    case EVENT_TRIGGER_BY_FAVOUR: return "by_favour";
    case EVENT_TRIGGER_BY_FAVOUR_IN_USE: return "by_favour_in_use";
    default: return "?";
    }
}

static pcstr invasion_semantics(int trigger, int invader, int amount) {
    if (trigger == EVENT_TRIGGER_BY_FAVOUR || trigger == EVENT_TRIGGER_BY_FAVOUR_IN_USE) {
        return "favour_kr_punishment";
    }
    if (trigger == EVENT_TRIGGER_ONLY_VIA_EVENT) {
        return "chain_child";
    }
    if (invader == EVENT_INVADER_PHARAOH && amount >= 32) {
        return "pharaoh_army_large";
    }
    return "timed_or_recurring";
}

static bool event_item_is_resource(int type, int subtype) {
    switch (type) {
    case EVENT_TYPE_REQUEST:
        return subtype != EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS;
    case EVENT_TYPE_DEMAND_INCREASE:
    case EVENT_TYPE_DEMAND_DECREASE:
    case EVENT_TYPE_PRICE_INCREASE:
    case EVENT_TYPE_PRICE_DECREASE:
    case EVENT_TYPE_GIFT_FROM_PHARAOH:
        return true;
    default:
        return false;
    }
}

static pcstr empire_city_name(int city_id) {
    if (city_id < 0) {
        return "-";
    }
    const empire_city *city = g_empire.city(city_id);
    if (!city || !city->in_use) {
        return "?";
    }
    pcstr name = (pcstr)lang_get_string(195, city->name_id);
    return (name && name[0]) ? name : "?";
}

static void mark_chain_ref(bool *inbound, int n, int ref, bool *has_oob) {
    if (ref < 0) {
        return;
    }
    if (ref >= n) {
        *has_oob = true;
        return;
    }
    inbound[ref] = true;
}

static void dump_scenario_events() {
    const int n = g_scenario.events.events_count();
    int requests = 0;
    int invasions = 0;
    int distant = 0;
    int other = 0;
    int orphan_inbound_count = 0;
    int oob_count = 0;

    // Pass 1: which event indices are referenced by any parent's ok/refuse/late/defeat.
    constexpr int kMaxEvents = 150;
    bool inbound[kMaxEvents];
    memset(inbound, 0, sizeof inbound);
    const int scan_n = std::min(n, kMaxEvents);
    for (int i = 0; i < scan_n; i++) {
        const event_ph_t *ev = g_scenario.events.at(i);
        if (!ev || ev->type == EVENT_TYPE_NONE) {
            continue;
        }
        bool unused_oob = false;
        mark_chain_ref(inbound, scan_n, (int)ev->on_completed_action, &unused_oob);
        mark_chain_ref(inbound, scan_n, (int)ev->on_refusal_action, &unused_oob);
        mark_chain_ref(inbound, scan_n, (int)ev->on_too_late_action, &unused_oob);
        mark_chain_ref(inbound, scan_n, (int)ev->on_defeat_action, &unused_oob);
        (void)unused_oob;
    }

    for (int i = 0; i < n; i++) {
        const event_ph_t* ev = g_scenario.events.at(i);
        if (!ev || ev->type == EVENT_TYPE_NONE) {
            continue;
        }

        bool oob = false;
        const int chain_refs[4] = {
            (int)ev->on_completed_action,
            (int)ev->on_refusal_action,
            (int)ev->on_too_late_action,
            (int)ev->on_defeat_action
        };
        for (int r = 0; r < 4; r++) {
            if (chain_refs[r] >= n) {
                oob = true;
                break;
            }
        }
        if (oob) {
            oob_count++;
        }

        const bool orphan_inbound = (ev->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT)
            && (i < scan_n) && !inbound[i];
        if (orphan_inbound) {
            orphan_inbound_count++;
        }

        const int item = (int)ev->item.value;
        const int city_id = (int)ev->city_id;
        char item_buf[64];
        if (ev->type == EVENT_TYPE_REQUEST
            && (int)ev->subtype == EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS) {
            snprintf(item_buf, sizeof item_buf, "troops(%d)", item);
        } else if (ev->type == EVENT_TYPE_INVASION) {
            snprintf(item_buf, sizeof item_buf, "%s(%d)", invader_name(item), item);
        } else if (event_item_is_resource((int)ev->type, (int)ev->subtype)) {
            snprintf(item_buf, sizeof item_buf, "%s(%d)",
                safe_token(resource_name((e_resource)item)), item);
        } else {
            snprintf(item_buf, sizeof item_buf, "%d", item);
        }

        dump_marker(
            "pak_event:i=%d|type=%d(%s)|year=%d|month=%d|item=%s|amount=%d|months=%d|"
            "loc=%d,%d,%d,%d|sender=%d|subtype=%d|city=%s(%d)|trigger=%d(%s)|active=%d|"
            "ok=%d|refuse=%d|late=%d|defeat=%d|attack=%d|orphan_inbound=%d|oob=%d",
            i,
            (int)ev->type,
            safe_token(e_event_type_tokens.name((e_event_type)ev->type)),
            (int)ev->time.year,
            (int)ev->time.month,
            item_buf,
            (int)ev->amount.value,
            (int)ev->months_initial,
            (int)ev->location_fields[0],
            (int)ev->location_fields[1],
            (int)ev->location_fields[2],
            (int)ev->location_fields[3],
            (int)ev->sender_faction,
            (int)ev->subtype,
            empire_city_name(city_id),
            city_id,
            (int)ev->event_trigger_type,
            trigger_name((int)ev->event_trigger_type),
            ev->is_active ? 1 : 0,
            (int)ev->on_completed_action,
            (int)ev->on_refusal_action,
            (int)ev->on_too_late_action,
            (int)ev->on_defeat_action,
            (int)ev->invasion_attack_target,
            orphan_inbound ? 1 : 0,
            oob ? 1 : 0);

        if (ev->type == EVENT_TYPE_REQUEST) {
            requests++;
            const int subtype = (int)ev->subtype;
            if (subtype == EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS) {
                dump_marker("pak_request:year=%d|month=%d|res=troops(subtype1)|amount=%d|months=%d|item_raw=%d",
                    (int)ev->time.year,
                    (int)ev->time.month,
                    (int)ev->amount.value,
                    (int)ev->months_initial,
                    (int)ev->item.value);
            } else {
                dump_marker("pak_request:year=%d|month=%d|res=%s(%d)|amount=%d|months=%d",
                    (int)ev->time.year,
                    (int)ev->time.month,
                    safe_token(resource_name((e_resource)ev->item.value)),
                    (int)ev->item.value,
                    (int)ev->amount.value,
                    (int)ev->months_initial);
            }
        } else if (ev->type == EVENT_TYPE_INVASION) {
            invasions++;
            dump_marker(
                "pak_invasion_event:year=%d|month=%d|amount=%d|invader=%s(%d)|trigger=%s(%d)|"
                "semantics=%s|loc=%d,%d|sender=%d|subtype=%d|attack=%d|ok=%d|refuse=%d|late=%d|defeat=%d",
                (int)ev->time.year,
                (int)ev->time.month,
                (int)ev->amount.value,
                invader_name((int)ev->item.value),
                (int)ev->item.value,
                trigger_name((int)ev->event_trigger_type),
                (int)ev->event_trigger_type,
                invasion_semantics((int)ev->event_trigger_type, (int)ev->item.value, (int)ev->amount.value),
                (int)ev->location_fields[0],
                (int)ev->location_fields[1],
                (int)ev->sender_faction,
                (int)ev->subtype,
                (int)ev->invasion_attack_target,
                (int)ev->on_completed_action,
                (int)ev->on_refusal_action,
                (int)ev->on_too_late_action,
                (int)ev->on_defeat_action);
        } else if (ev->type == EVENT_TYPE_DISTANT_BATTLE || ev->type == EVENT_TYPE_DISTANT_BATTLE_WON) {
            distant++;
            dump_marker("pak_distant_battle:year=%d|month=%d|amount=%d|city=%s(%d)|trigger=%s(%d)|months=%d",
                (int)ev->time.year,
                (int)ev->time.month,
                (int)ev->amount.value,
                empire_city_name((int)ev->city_id),
                (int)ev->city_id,
                trigger_name((int)ev->event_trigger_type),
                (int)ev->event_trigger_type,
                (int)ev->months_initial);
        } else {
            other++;
        }
    }

    dump_marker("pak_event_count:%d", n);
    dump_marker("pak_request_count:%d", requests);
    dump_marker("pak_invasion_event_count:%d", invasions);
    dump_marker("pak_distant_battle_count:%d", distant);
    dump_marker("pak_other_event_count:%d", other);
    dump_marker("pak_orphan_inbound_count:%d", orphan_inbound_count);
    dump_marker("pak_oob_count:%d", oob_count);
}

static void dump_legacy_tables() {
    // Caesar3-style tables — often empty in Pharaoh (events live in scenario_events).
    int inv_n = 0;
    for (int i = 0; i < 40; i++) {
        const invasion_t& inv = g_scenario.invasions[i];
        if (!inv.type) {
            continue;
        }
        dump_marker("pak_legacy_invasion:i=%d|year=%d|month=%d|type=%d|amount=%d|from=%d|attack=%d",
            i,
            inv.year,
            inv.month,
            inv.type,
            inv.amount,
            inv.from,
            (int)inv.attack_type);
        inv_n++;
    }
    dump_marker("pak_legacy_invasion_count:%d", inv_n);

    int demand_n = 0;
    for (int i = 0; i < 40; i++) {
        const demand_change_t& d = g_scenario.demand_changes[i];
        if (!d.year && !d.resource) {
            continue;
        }
        dump_marker("pak_demand_change:i=%d|year=%d|month=%d|res=%s(%d)|route=%d|rise=%d",
            i,
            d.year,
            d.month,
            safe_token(resource_name(d.resource)),
            (int)d.resource,
            d.route_id,
            d.is_rise);
        demand_n++;
    }
    dump_marker("pak_demand_change_count:%d", demand_n);

    int price_n = 0;
    for (int i = 0; i < 40; i++) {
        const price_change_t& p = g_scenario.price_changes[i];
        if (!p.year && !p.resource) {
            continue;
        }
        dump_marker("pak_price_change:i=%d|year=%d|month=%d|res=%s(%d)|amount=%d|rise=%d",
            i,
            p.year,
            p.month,
            safe_token(resource_name(p.resource)),
            (int)p.resource,
            p.amount,
            p.is_rise);
        price_n++;
    }
    dump_marker("pak_price_change_count:%d", price_n);
}

static void dump_terrain_stats() {
    // terrain_grid: uint32 bitmask per cell on the full 228² grid; playable
    // area is scenario map width×height starting at map.start_offset.
    struct bit_stat {
        uint32_t mask;
        pcstr name;
    };
    static const bit_stat bits[] = {
        {TERRAIN_TREE, "tree"},
        {TERRAIN_ROCK, "rock"},
        {TERRAIN_WATER, "water"},
        {TERRAIN_BUILDING, "building"},
        {TERRAIN_SHRUB, "shrub"},
        {TERRAIN_GARDEN, "garden"},
        {TERRAIN_ROAD, "road"},
        {TERRAIN_GROUNDWATER, "groundwater"},
        {TERRAIN_CANAL, "canal"},
        {TERRAIN_ELEVATION, "elevation"},
        {TERRAIN_MEADOW, "meadow"},
        {TERRAIN_RUBBLE, "rubble"},
        {TERRAIN_WALL, "wall"},
        {TERRAIN_FLOODPLAIN, "floodplain"},
        {TERRAIN_FERRY_ROUTE, "ferry_route"},
        {TERRAIN_MARSHLAND, "marshland"},
        {TERRAIN_ORE, "ore"},
        {TERRAIN_DUNE, "dune"},
        {TERRAIN_DEEPWATER, "deepwater"},
        {TERRAIN_SHORE, "shore"},
    };

    const int w = g_scenario.map.width;
    const int h = g_scenario.map.height;
    int empty = 0;
    int non_empty = 0;
    int bit_counts[sizeof(bits) / sizeof(bits[0])] = {0};

    // Top combo histogram (mask → count), capped.
    struct combo {
        uint32_t mask;
        int n;
    };
    combo top[16] = {};
    int top_n = 0;

    auto push_combo = [&](uint32_t mask) {
        for (int i = 0; i < top_n; i++) {
            if (top[i].mask == mask) {
                top[i].n++;
                // bubble toward front by count
                for (int j = i; j > 0 && top[j].n > top[j - 1].n; --j) {
                    combo tmp = top[j];
                    top[j] = top[j - 1];
                    top[j - 1] = tmp;
                }
                return;
            }
        }
        if (top_n < 16) {
            top[top_n++] = {mask, 1};
        } else if (top[15].n == 1) {
            // replace rarest of the tail only when tied at 1 — good enough for overview
            top[15] = {mask, 1};
        }
    };

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            const int offset = (int)MAP_OFFSET(x, y);
            const uint32_t t = (uint32_t)map_terrain_get(offset);
            if (t == 0) {
                empty++;
            } else {
                non_empty++;
                push_combo(t);
            }
            for (int i = 0; i < (int)(sizeof(bits) / sizeof(bits[0])); i++) {
                if (t & bits[i].mask) {
                    bit_counts[i]++;
                }
            }
        }
    }

    dump_marker("pak_terrain:w=%d|h=%d|tiles=%d|empty=%d|non_empty=%d",
        w, h, w * h, empty, non_empty);
    for (int i = 0; i < (int)(sizeof(bits) / sizeof(bits[0])); i++) {
        if (bit_counts[i] <= 0) {
            continue;
        }
        dump_marker("pak_terrain_bit:%s|n=%d|pct=%.1f",
            bits[i].name,
            bit_counts[i],
            100.0 * bit_counts[i] / (double)(w * h));
    }
    for (int i = 0; i < top_n; i++) {
        dump_marker("pak_terrain_combo:rank=%d|mask=0x%08x|n=%d", i + 1, top[i].mask, top[i].n);
    }
}

static void dump_starting_buildings() {
    int counts[BUILDING_MAX] = {0};
    int total = 0;

    for (building* b = building_begin(); b != building_end(); ++b) {
        if (!b || !b->is_valid()) {
            continue;
        }
        if (b->type > BUILDING_NONE && b->type < BUILDING_MAX) {
            counts[b->type]++;
            total++;
        }
        // Skip vacant lots / houses in the per-building list to keep logs readable;
        // still counted in the summary above.
        if (b->type >= BUILDING_HOUSE_VACANT_LOT && b->type <= BUILDING_HOUSE_PALATIAL_ESTATE) {
            continue;
        }
        dump_marker("pak_building:id=%d|type=%d(%s)|x=%d|y=%d",
            b->id,
            (int)b->type,
            safe_token(e_building_type_tokens.name(b->type)),
            b->tile.x(),
            b->tile.y());
    }

    dump_marker("pak_building_total:%d", total);
    for (int t = 1; t < BUILDING_MAX; t++) {
        if (counts[t] <= 0) {
            continue;
        }
        dump_marker("pak_building_count:type=%d(%s)|n=%d",
            t,
            safe_token(e_building_type_tokens.name((e_building_type)t)),
            counts[t]);
    }
}

static void dump_allowed_buildings() {
    int n = 0;
    for (int t = 1; t < BUILDING_MAX; t++) {
        if (!g_scenario.allowed_buildings[t]) {
            continue;
        }
        dump_marker("pak_allowed:type=%d(%s)",
            t,
            safe_token(e_building_type_tokens.name((e_building_type)t)));
        n++;
    }
    dump_marker("pak_allowed_count:%d", n);
}

static void append_mapped_types(char *out, size_t out_sz, int slot) {
    e_building_type types[8];
    const int n = scenario_editor_allow_mapped_types(slot, types, 8);
    if (n <= 0) {
        snprintf(out, out_sz, "?");
        return;
    }
    size_t used = 0;
    out[0] = 0;
    for (int i = 0; i < n; i++) {
        pcstr name = safe_token(e_building_type_tokens.name(types[i]));
        const size_t nlen = strlen(name);
        if (used + nlen + 16 >= out_sz) {
            break;
        }
        if (used > 0) {
            out[used++] = ',';
            out[used] = 0;
        }
        used += (size_t)snprintf(out + used, out_sz - used, "%d(%s)", (int)types[i], name);
    }
}

static pcstr editor_allow_slot_label(int slot) {
    pcstr s = lang_get_string(67, slot);
    if (s && s[0]) {
        return s;
    }
    switch (slot) {
    case scenario_data_t::EDITOR_ALLOW_SLOT_BRIDGE:
        return "Bridge";
    case scenario_data_t::EDITOR_ALLOW_SLOT_FERRY:
        return "Ferry Landing";
    default:
        return "?";
    }
}

static void dump_pak_reserved() {
    int nonzero = 0;
    for (int i = 0; i < scenario_data_t::SCENARIO_PAK_RESERVED_INT16S; i++) {
        const int16_t v = g_scenario.pak_reserved[i];
        dump_marker("pak_reserved:i=%d|v=%d", i, (int)v);
        if (v != 0) {
            nonzero++;
        }
    }
    dump_marker("pak_reserved_nonzero:%d", nonzero);

    char types_buf[256];
    int allow_on = 0;
    for (int slot = 1; slot <= scenario_data_t::SCENARIO_EDITOR_ALLOW_SLOTS; slot++) {
        const int16_t v = g_scenario.pak_editor_allow_flag(slot);
        append_mapped_types(types_buf, sizeof types_buf, slot);
        dump_marker("pak_editor_allow:slot=%d|name=%s|v=%d|types=%s",
            slot,
            editor_allow_slot_label(slot),
            (int)v,
            types_buf);
        if (v != 0) {
            allow_on++;
        }
    }
    dump_marker("pak_editor_allow_on:%d", allow_on);
}

static void dump_loaded_scenario(int scenario_id) {
    dump_scenario_header(scenario_id);
    dump_win_criteria();
    dump_map_points();
    dump_invasion_points();
    dump_monuments();
    dump_gods();
    dump_empire_cities();
    dump_empire_objects();
    dump_empire_routes();
    dump_scenario_events();
    dump_legacy_tables();
    dump_terrain_stats();
    dump_starting_buildings();
    dump_pak_reserved();
    dump_allowed_buildings();
}

// Export mission map grids (terrain/image/elevation/…) as FILE_FORMAT_MAP_FILE.
// Returns 1 on success.
static int __test_export_mission_map(int scenario_id, pcstr path) {
    if (g_args.no_resource()) {
        dump_marker("pak_export_skipped:no_resource");
        return 0;
    }
    if (!GamestateIO::export_mission_map(scenario_id, path)) {
        dump_marker("pak_export_fail:%d|%s", scenario_id, path ? path : "-");
        return 0;
    }
    dump_marker("pak_export_ok:%d|%s", scenario_id, path);
    return 1;
}
ANK_FUNCTION_2(__test_export_mission_map);

// Returns 1 on successful dump, 0 if skipped (--no-resource) or load failed.
static int __test_mission_pak_dump(int scenario_id) {
    if (g_args.no_resource()) {
        dump_marker("pak_dump_skipped:no_resource");
        return 0;
    }

    if (!GamestateIO::load_mission_pak_raw(scenario_id)) {
        logs::info("[test] load_mission_pak_raw(%d) failed", scenario_id);
        dump_marker("pak_dump_fail:%d", scenario_id);
        return 0;
    }

    dump_loaded_scenario(scenario_id);
    dump_marker("pak_dump_done:%d", scenario_id);
    return 1;
}
ANK_FUNCTION_1(__test_mission_pak_dump);

// Dump in-memory scenario events only (B9 smoke under --no-resource).
static int __test_dump_scenario_events() {
    dump_scenario_events();
    return 1;
}
ANK_FUNCTION(__test_dump_scenario_events);

// Compact herd/prey/fishing point dump for porting map points into mission JS.
static void dump_herd_points(int scenario_id) {
    auto join_herd_points = [](char *out, size_t out_sz, const auto &points) {
        out[0] = 0;
        size_t used = 0;
        for (const herd_point_t &hp : points) {
            if (!hp.valid()) {
                continue;
            }
            const int w = snprintf(out + used, out_sz - used, "%s[%d, %d]", used ? ", " : "", hp.tile.x(),
                                   hp.tile.y());
            if (w <= 0 || used + (size_t)w >= out_sz) {
                break;
            }
            used += (size_t)w;
        }
    };
    auto join_tiles = [](char *out, size_t out_sz, const auto &points) {
        out[0] = 0;
        size_t used = 0;
        for (const tile2i &t : points) {
            if (!t.valid()) {
                continue;
            }
            const int w = snprintf(out + used, out_sz - used, "%s[%d, %d]", used ? ", " : "", t.x(), t.y());
            if (w <= 0 || used + (size_t)w >= out_sz) {
                break;
            }
            used += (size_t)w;
        }
    };

    char predator[256];
    char prey[256];
    char fish[512];
    join_herd_points(predator, sizeof predator, g_scenario.herd_points_predator);
    join_herd_points(prey, sizeof prey, g_scenario.herd_points_prey);
    join_tiles(fish, sizeof fish, g_scenario.fishing_points);

    char types[128] = {0};
    size_t tused = 0;
    for (size_t i = 0; i < g_scenario.herd_points_predator.size(); i++) {
        const int w = snprintf(types + tused, sizeof types - tused, "%s%d", tused ? "," : "",
                               (int)g_scenario.herd_points_predator[i].type);
        if (w <= 0 || tused + (size_t)w >= sizeof types) {
            break;
        }
        tused += (size_t)w;
    }

    dump_marker("herd_dump:id=%d|climate=%s|animals_flag=%d|alt_predator=%d|types=%s", scenario_id,
                climate_name(g_scenario.climate), g_scenario.env.has_animals ? 1 : 0,
                g_scenario.alt_predator_type ? 1 : 0, types[0] ? types : "-");
    dump_marker("herd_dump_predator:id=%d|%s", scenario_id, predator[0] ? predator : "-");
    dump_marker("herd_dump_prey:id=%d|%s", scenario_id, prey[0] ? prey : "-");
    dump_marker("herd_dump_fish:id=%d|%s", scenario_id, fish[0] ? fish : "-");
}

static int __test_mission_herd_dump(int scenario_id) {
    if (g_args.no_resource()) {
        dump_marker("herd_dump_skipped:no_resource");
        return 0;
    }
    if (!GamestateIO::load_mission_pak_raw(scenario_id)) {
        dump_marker("herd_dump_fail:%d", scenario_id);
        return 0;
    }
    dump_herd_points(scenario_id);
    return 1;
}
ANK_FUNCTION_1(__test_mission_herd_dump);

static int __test_mission_map_herd_dump(int scenario_id, pcstr map_path) {
    if (!map_path || !map_path[0] || !GamestateIO::load_mission_map_raw(scenario_id, map_path)) {
        dump_marker("herd_dump_fail:%d", scenario_id);
        return 0;
    }
    dump_herd_points(scenario_id);
    return 1;
}
ANK_FUNCTION_2(__test_mission_map_herd_dump);

static void dump_bridge_allow_summary(int scenario_id, pcstr src) {
    const int16_t bridge = g_scenario.pak_editor_allow_flag(scenario_data_t::EDITOR_ALLOW_SLOT_BRIDGE);
    const int16_t ferry = g_scenario.pak_editor_allow_flag(scenario_data_t::EDITOR_ALLOW_SLOT_FERRY);
    int allow_on = 0;
    for (int slot = 1; slot <= scenario_data_t::SCENARIO_EDITOR_ALLOW_SLOTS; slot++) {
        if (g_scenario.pak_editor_allow_flag(slot) != 0) {
            allow_on++;
        }
    }
    dump_marker("bridge_allow:id=%d|src=%s|bridge=%d|ferry=%d|allow_on=%d",
        scenario_id,
        src ? src : "?",
        (int)bridge,
        (int)ferry,
        allow_on);
}

// Compact Bridge/Ferry allow dump from mission pak (no full scenario dump).
static int __test_mission_bridge_allow_dump(int scenario_id) {
    if (g_args.no_resource()) {
        dump_marker("bridge_allow_skipped:no_resource");
        return 0;
    }
    if (!GamestateIO::load_mission_pak_raw(scenario_id)) {
        dump_marker("bridge_allow_fail:%d|pak", scenario_id);
        return 0;
    }
    dump_bridge_allow_summary(scenario_id, "pak");
    return 1;
}
ANK_FUNCTION_1(__test_mission_bridge_allow_dump);

static int __test_mission_map_bridge_allow_dump(int scenario_id, pcstr map_path) {
    if (g_args.no_resource()) {
        dump_marker("bridge_allow_skipped:no_resource");
        return 0;
    }
    if (!map_path || !map_path[0]) {
        dump_marker("bridge_allow_fail:%d|-", scenario_id);
        return 0;
    }
    if (!GamestateIO::load_mission_map_raw(scenario_id, map_path)) {
        dump_marker("bridge_allow_fail:%d|%s", scenario_id, map_path);
        return 0;
    }
    dump_bridge_allow_summary(scenario_id, map_path);
    return 1;
}
ANK_FUNCTION_2(__test_mission_map_bridge_allow_dump);

// Dump a .map file WITHOUT JS mission overlay (load_mission_map_raw, no post_load).
// scenario_id is only for markers / campaign_scenario_id (e.g. 129 for Bridges.map).
static int __test_mission_map_dump(int scenario_id, pcstr map_path) {
    if (g_args.no_resource()) {
        dump_marker("pak_dump_skipped:no_resource");
        return 0;
    }
    if (!map_path || !map_path[0]) {
        dump_marker("map_dump_fail:%d|-", scenario_id);
        return 0;
    }

    if (!GamestateIO::load_mission_map_raw(scenario_id, map_path)) {
        logs::info("[test] load_mission_map_raw(%d, %s) failed", scenario_id, map_path);
        dump_marker("map_dump_fail:%d|%s", scenario_id, map_path);
        return 0;
    }

    g_empire.init_cities();
    dump_marker("map_dump_ok:%d|%s", scenario_id, map_path);
    dump_loaded_scenario(scenario_id);
    dump_marker("map_dump_done:%d", scenario_id);
    return 1;
}
ANK_FUNCTION_2(__test_mission_map_dump);
