#include "city/campaign_carry.h"

#include "building/building.h"
#include "building/monument_royal_tomb.h"
#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "core/vec2i.h"
#include "figure/formation.h"
#include "figuretype/figure_soldier.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/point.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/event_phrases.h"
#include "scenario/map.h"
#include "scenario/scenario_event_manager.h"

#include <algorithm>
#include <cstring>

campaign_carry_t g_campaign_carry;

e_troop_carry_slot troop_carry_slot_for_building(e_building_type type) {
    switch (type) {
    case BUILDING_FORT_INFANTRY: return TROOP_CARRY_INFANTRY;
    case BUILDING_FORT_ARCHERS: return TROOP_CARRY_ARCHER;
    case BUILDING_FORT_CHARIOTEERS: return TROOP_CARRY_CHARIOT;
    default: return TROOP_CARRY_MAX;
    }
}

e_troop_carry_slot troop_carry_slot_for_figure(e_figure_type type) {
    switch (type) {
    case FIGURE_INFANTRY: return TROOP_CARRY_INFANTRY;
    case FIGURE_ARCHER: return TROOP_CARRY_ARCHER;
    case FIGURE_FCHARIOTEER: return TROOP_CARRY_CHARIOT;
    default: return TROOP_CARRY_MAX;
    }
}

e_figure_type troop_carry_figure_type(e_troop_carry_slot slot) {
    switch (slot) {
    case TROOP_CARRY_INFANTRY: return FIGURE_INFANTRY;
    case TROOP_CARRY_ARCHER: return FIGURE_ARCHER;
    case TROOP_CARRY_CHARIOT: return FIGURE_FCHARIOTEER;
    default: return FIGURE_NONE;
    }
}

bool campaign_carry_is_fort_building(e_building_type type) {
    return type == BUILDING_FORT_INFANTRY
        || type == BUILDING_FORT_ARCHERS
        || type == BUILDING_FORT_CHARIOTEERS
        || type == BUILDING_FORT_GROUND;
}

bool campaign_carry_is_monument_type(e_building_type type) {
    switch (type) {
    case BUILDING_MAUSOLEUM:
    case BUILDING_ALEXANDRIA_LIBRARY:
    case BUILDING_PHAROS_LIGHTHOUSE:
    case BUILDING_SMALL_ROYAL_TOMB:
    case BUILDING_MEDIUM_ROYAL_TOMB:
    case BUILDING_LARGE_ROYAL_TOMB:
    case BUILDING_GRAND_ROYAL_TOMB:
        return true;
    default:
        return false;
    }
}

static bool campaign_carry_is_royal_tomb(e_building_type type) {
    return type == BUILDING_SMALL_ROYAL_TOMB
        || type == BUILDING_MEDIUM_ROYAL_TOMB
        || type == BUILDING_LARGE_ROYAL_TOMB
        || type == BUILDING_GRAND_ROYAL_TOMB;
}

uint8_t troop_carry_mask_parse_name(pcstr name) {
    if (!name || !name[0]) {
        return 0;
    }
    if (!strcmp(name, "infantry")) {
        return TROOP_CARRY_MASK_INFANTRY;
    }
    if (!strcmp(name, "archer") || !strcmp(name, "archers")) {
        return TROOP_CARRY_MASK_ARCHER;
    }
    if (!strcmp(name, "chariot") || !strcmp(name, "charioteer") || !strcmp(name, "charioteers")) {
        return TROOP_CARRY_MASK_CHARIOT;
    }
    return 0;
}

void campaign_carry_t::clear_troops() {
    memset(troops, 0, sizeof(troops));
    memset(troop_refund, 0, sizeof(troop_refund));
    notice_posted = 0;
}

void campaign_carry_t::clear_monuments() {
    memset(monuments, 0, sizeof(monuments));
}

void campaign_carry_t::clear() {
    clear_troops();
    clear_monuments();
    memset(pad_troops, 0, sizeof(pad_troops));
}

static int troop_carry_soldier_count(const formation *m) {
    if (!m || m->num_figures <= 0) {
        return 0;
    }
    int n = 0;
    for (int i = 0; i < m->num_figures; i++) {
        const int fid = m->figures[i];
        if (!fid) {
            continue;
        }
        const figure *f = figure_get(fid);
        if (f && f->type == m->figure_type) {
            n++;
        }
    }
    return n;
}

void campaign_carry_t::snapshot_from_formations() {
    campaign_troop_slot_t best[TROOP_CARRY_MAX]{};
    formations_foreach([&](formation *m) {
        if (!m || !m->own_batalion) {
            return;
        }
        const int soldiers = troop_carry_soldier_count(m);
        if (soldiers <= 0) {
            return;
        }
        const e_troop_carry_slot slot = troop_carry_slot_for_figure(m->figure_type);
        if (slot >= TROOP_CARRY_MAX) {
            return;
        }
        auto &cur = best[slot];
        const bool better = !cur.has_data
            || m->has_military_training > cur.has_military_training
            || (m->has_military_training == cur.has_military_training
                && (soldiers > cur.num_figures
                    || (soldiers == cur.num_figures && m->morale > cur.morale)));
        if (!better) {
            return;
        }
        cur.has_data = 1;
        cur.pending = 0;
        cur.num_figures = (uint8_t)std::min(soldiers, (int)m->max_figures);
        cur.has_military_training = m->has_military_training ? 1 : 0;
        cur.morale = m->morale;
        cur.experience = m->experience;
    });

    for (int i = 0; i < TROOP_CARRY_MAX; i++) {
        troops[i] = best[i];
        troop_refund[i] = {};
    }
    notice_posted = 0;
}

void campaign_carry_t::activate_for_mission(uint8_t mask) {
    notice_posted = 0;
    memset(troop_refund, 0, sizeof(troop_refund));
    if (!mask) {
        clear_troops();
        return;
    }

    for (int i = 0; i < TROOP_CARRY_MAX; i++) {
        auto &slot = troops[i];
        if ((mask & (1u << i)) && slot.has_data && slot.num_figures > 0) {
            slot.pending = 1;
        } else {
            slot = {};
        }
    }
}

void campaign_carry_t::expire_pending_troops() {
    for (int i = 0; i < TROOP_CARRY_MAX; i++) {
        if (troops[i].pending) {
            troops[i] = {};
        }
    }
    memset(troop_refund, 0, sizeof(troop_refund));
    notice_posted = 0;
}

int campaign_carry_t::pending_mask() const {
    int mask = 0;
    for (int i = 0; i < TROOP_CARRY_MAX; i++) {
        if (troops[i].pending && troops[i].num_figures > 0) {
            mask |= (1 << i);
        }
    }
    return mask;
}

static int troop_carry_reason_phrase(int mask) {
    const bool inf = (mask & TROOP_CARRY_MASK_INFANTRY) != 0;
    const bool arch = (mask & TROOP_CARRY_MASK_ARCHER) != 0;
    const bool chario = (mask & TROOP_CARRY_MASK_CHARIOT) != 0;
    const int count = (inf ? 1 : 0) + (arch ? 1 : 0) + (chario ? 1 : 0);
    if (count == 3) {
        return PHRASE_troopcarryover_all_three;
    }
    if (count == 1) {
        if (inf) {
            return PHRASE_troopcarryover_inf_only;
        }
        if (arch) {
            return PHRASE_troopcarryover_arch_only;
        }
        return PHRASE_troopcarryover_char_only;
    }
    if (inf && arch) {
        return PHRASE_troopcarryover_inf_arch;
    }
    if (inf && chario) {
        return PHRASE_troopcarryover_inf_char;
    }
    if (arch && chario) {
        return PHRASE_troopcarryover_arch_char;
    }
    return PHRASE_troopcarryover_all_three;
}

void campaign_carry_t::post_notice_if_needed() {
    const int mask = pending_mask();
    if (!mask || notice_posted) {
        return;
    }

    event_ph_t dummy{};
    city_message_post_full(true, "message_template_general", &dummy, -1, PHRASE_troopcarryover_title,
                           PHRASE_troopcarryover_initial_announcement, troop_carry_reason_phrase(mask), 0, 0);
    notice_posted = 1;
}

bool campaign_carry_t::try_apply_to_fort(e_building_type fort_type, int formation_id) {
    const e_troop_carry_slot slot_i = troop_carry_slot_for_building(fort_type);
    if (slot_i >= TROOP_CARRY_MAX || formation_id <= 0) {
        return false;
    }

    auto &slot = troops[slot_i];
    if (!slot.pending || slot.num_figures <= 0) {
        return false;
    }

    formation *m = formation_get(formation_id);
    if (!m || !m->in_use || !m->own_batalion) {
        return false;
    }

    const int want = std::min<int>(slot.num_figures, m->max_figures);
    if (want <= 0) {
        slot = {};
        return false;
    }

    tile2i entry = scenario_map_entry();
    if (!entry.valid()) {
        entry = g_city.map.entry_point;
    }

    m->morale = slot.morale;
    m->has_military_training = slot.has_military_training;
    m->experience = slot.experience;
    m->is_at_fort = 0;

    int spawned = 0;
    for (int i = 0; i < want; i++) {
        figure *f = figure_create(m->figure_type, entry, DIR_0_TOP_RIGHT);
        if (!f || f->id <= 0) {
            break;
        }
        m->figures[spawned] = f->id;
        f->formation_id = m->id;
        f->formation_at_rest = 0;
        f->advance_action(ACTION_81_SOLDIER_GOING_TO_FORT);
        spawned++;
    }
    if (spawned <= 0) {
        return false;
    }

    m->num_figures = (uint8_t)spawned;
    g_formations.calculate_batalion_totals();

    troop_refund[slot_i] = slot;
    slot.pending = 0;
    slot.has_data = 0;
    return true;
}

void campaign_carry_t::refund_fort_if_applied(e_building_type fort_type) {
    const e_troop_carry_slot slot_i = troop_carry_slot_for_building(fort_type);
    if (slot_i >= TROOP_CARRY_MAX) {
        return;
    }
    auto &refund = troop_refund[slot_i];
    if (!refund.has_data || refund.num_figures <= 0) {
        return;
    }
    troops[slot_i] = refund;
    troops[slot_i].pending = 1;
    refund = {};
}

static void monument_upsert(campaign_monument_slot_t *slots, e_building_type type, tile2i tile, uint8_t orientation,
                            uint8_t variant) {
    int free_i = -1;
    for (int i = 0; i < CAMPAIGN_CARRY_MONUMENT_MAX; i++) {
        if (slots[i].has_data && slots[i].type == (uint16_t)type) {
            slots[i].tile_x = (int16_t)tile.x();
            slots[i].tile_y = (int16_t)tile.y();
            slots[i].orientation = orientation;
            slots[i].variant = variant;
            return;
        }
        if (!slots[i].has_data && free_i < 0) {
            free_i = i;
        }
    }
    if (free_i < 0) {
        return;
    }
    auto &s = slots[free_i];
    s.has_data = 1;
    s.type = (uint16_t)type;
    s.tile_x = (int16_t)tile.x();
    s.tile_y = (int16_t)tile.y();
    s.orientation = orientation;
    s.variant = variant;
}

void campaign_carry_t::snapshot_monuments_from_city() {
    // Merge/upsert by type — win on Maritis (50) must not wipe Alex store.
    for (building &b : city_buildings()) {
        if (!b.is_main()) {
            continue;
        }
        if (!campaign_carry_is_monument_type(b.type)) {
            continue;
        }
        auto *mon = b.dcast_monument();
        if (!mon || !mon->is_finished()) {
            continue;
        }
        monument_upsert(monuments, b.type, b.tile, (uint8_t)b.orientation, mon->runtime_data().variant);
    }
}

namespace {

vec2i carry_oriented_wh(vec2i size, int rotation) {
    if ((rotation % 2) != 0) {
        return {size.y, size.x};
    }
    return size;
}

vec2i carry_monument_init_tiles(e_building_type type) {
    switch (type) {
    case BUILDING_MAUSOLEUM:
        return {8, 22};
    case BUILDING_ALEXANDRIA_LIBRARY:
        return {13, 14};
    case BUILDING_PHAROS_LIGHTHOUSE:
        return {6, 6};
    case BUILDING_SMALL_ROYAL_TOMB:
    case BUILDING_MEDIUM_ROYAL_TOMB:
    case BUILDING_LARGE_ROYAL_TOMB:
    case BUILDING_GRAND_ROYAL_TOMB: {
        // Cliff bulk + entrance depth (Heaven chart); oriented later.
        const auto &bp = building_royal_tomb::params_for(type);
        vec2i bulk = bp.init_tiles;
        if (bulk.x <= 0 || bulk.y <= 0) {
            bulk = {11, 20};
        }
        vec2i ent = bp.entrance_size;
        if (ent.x <= 0 || ent.y <= 0) {
            ent = {1, 1};
        }
        return {bulk.x, bulk.y + ent.y};
    }
    default:
        return {0, 0};
    }
}

vec2i carry_monument_footprint(e_building_type type, int orientation) {
    const vec2i init = carry_monument_init_tiles(type);
    if (init.x <= 0 || init.y <= 0) {
        return {0, 0};
    }
    return carry_oriented_wh(init, orientation % 4);
}

bool carry_tile_not_clear(tile2i t) {
    return map_terrain_is(t, TERRAIN_NOT_CLEAR)
        || (map_terrain_count_directly_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || (map_terrain_count_diagonally_adjacent_with_type(t, TERRAIN_FLOODPLAIN) > 0)
        || map_has_figure_at(t)
        || map_building_at(t);
}

bool carry_tile_not_rock(tile2i t) {
    if (!map_terrain_is(t, TERRAIN_ROCK)) {
        return true;
    }
    if (map_terrain_is(t, TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP
                           | TERRAIN_TREE | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD | TERRAIN_CANAL)) {
        return true;
    }
    if (map_has_figure_at(t) || map_building_at(t)) {
        return true;
    }
    return false;
}

bool carry_royal_tomb_area_ok(e_building_type type, tile2i origin, int orientation) {
    const auto &bp = building_royal_tomb::params_for(type);
    vec2i bulk = bp.init_tiles;
    if (bulk.x <= 0 || bulk.y <= 0) {
        bulk = {11, 20};
    }
    orientation %= 4;
    if (orientation == 1 || orientation == 3) {
        bulk = {bulk.y, bulk.x};
    }
    vec2i ent = bp.entrance_size;
    if (ent.x <= 0 || ent.y <= 0) {
        ent = {1, 1};
    }
    const vec2i total = {bulk.x, bulk.y + ent.y};
    for (int dy = 0; dy < total.y; dy++) {
        for (int dx = 0; dx < total.x; dx++) {
            if (building_royal_tomb::is_padding_local(dx, dy, bulk, ent)) {
                continue;
            }
            tile2i t = origin.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1)) {
                return false;
            }
            if (building_royal_tomb::is_entrance_local(dx, dy, bulk, ent)) {
                if (map_terrain_is(t, TERRAIN_NOT_CLEAR) || map_has_figure_at(t) || map_building_at(t)) {
                    return false;
                }
            } else {
                const uint32_t cliff = TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP;
                if (!map_terrain_is(t, cliff) || map_has_figure_at(t) || map_building_at(t)) {
                    return false;
                }
                const uint32_t blocked = TERRAIN_NOT_CLEAR & ~cliff;
                if (map_terrain_is(t, blocked)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool carry_area_ok(e_building_type type, tile2i origin, int w, int h) {
    if (w < 1 || h < 1 || !origin.valid()) {
        return false;
    }
    const bool need_rock = (type == BUILDING_PHAROS_LIGHTHOUSE);
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            tile2i t = origin.shifted(dx, dy);
            if (!map_grid_is_inside(t, 1)) {
                return false;
            }
            if (need_rock ? carry_tile_not_rock(t) : carry_tile_not_clear(t)) {
                return false;
            }
        }
    }
    return true;
}

bool carry_footprint_ok(e_building_type type, tile2i tile, int orientation) {
    if (campaign_carry_is_royal_tomb(type)) {
        return carry_royal_tomb_area_ok(type, tile, orientation);
    }
    const vec2i ft = carry_monument_footprint(type, orientation);
    return carry_area_ok(type, tile, ft.x, ft.y);
}

// CO1b: stored tile is from the previous map — try it first, then scan clear land / rock / cliff.
bool carry_find_place_tile(e_building_type type, uint8_t &orientation, tile2i preferred, tile2i &out_tile) {
    const vec2i init = carry_monument_init_tiles(type);
    if (init.x <= 0) {
        return false;
    }

    const bool square = (init.x == init.y);
    const uint8_t orients[2] = {orientation, (uint8_t)((orientation + 1) % 4)};
    const int orient_n = square ? 1 : 2;

    for (int oi = 0; oi < orient_n; oi++) {
        const uint8_t o = orients[oi];
        if (preferred.valid() && carry_footprint_ok(type, preferred, o)) {
            orientation = o;
            out_tile = preferred;
            return true;
        }
    }

    const int map_w = map_grid_width();
    const int map_h = map_grid_height();
    for (int oi = 0; oi < orient_n; oi++) {
        const uint8_t o = orients[oi];
        const vec2i ft = carry_monument_footprint(type, o);
        if (ft.x <= 0 || ft.y <= 0) {
            continue;
        }
        for (int y = 0; y <= map_h - ft.y; y++) {
            for (int x = 0; x <= map_w - ft.x; x++) {
                tile2i t(x, y);
                if (campaign_carry_is_royal_tomb(type)) {
                    if (!carry_royal_tomb_area_ok(type, t, o)) {
                        continue;
                    }
                } else if (!carry_area_ok(type, t, ft.x, ft.y)) {
                    continue;
                }
                orientation = o;
                out_tile = t;
                return true;
            }
        }
    }
    return false;
}

bool carry_monument_already_finished(e_building_type type) {
    for (building &b : city_buildings()) {
        if (!b.is_main() || b.type != type) {
            continue;
        }
        auto *mon = b.dcast_monument();
        if (mon && mon->is_finished()) {
            return true;
        }
    }
    return false;
}

bool carry_place_finished_monument(e_building_type type, tile2i tile, uint8_t orientation, uint8_t variant) {
    building *b = building_create(type, tile, orientation);
    if (!b || b->id <= 0) {
        return false;
    }

    auto *impl = b->dcast();
    auto *mon = b->dcast_monument();
    if (!impl || !mon) {
        b->state = BUILDING_STATE_UNUSED;
        return false;
    }

    b->state = BUILDING_STATE_VALID;
    mon->runtime_data().variant = variant;
    impl->on_place_update_tiles(orientation, variant);
    mon->set_phase(mon->phases());
    mon->set_preexisting(true);
    // Carried tombs already held their funeral in the prior Valley mission.
    if (campaign_carry_is_royal_tomb(type)) {
        mon->set_funeral_done(true);
    }
    return true;
}

} // namespace

void campaign_carry_t::apply_monuments() {
    for (int i = 0; i < CAMPAIGN_CARRY_MONUMENT_MAX; i++) {
        auto &slot = monuments[i];
        if (!slot.has_data) {
            continue;
        }
        const e_building_type type = (e_building_type)slot.type;
        if (!campaign_carry_is_monument_type(type)) {
            continue;
        }
        if (carry_monument_already_finished(type)) {
            continue;
        }

        tile2i preferred(slot.tile_x, slot.tile_y);
        tile2i tile;
        uint8_t orientation = slot.orientation;
        if (!carry_find_place_tile(type, orientation, preferred, tile)) {
            continue;
        }
        if (!carry_place_finished_monument(type, tile, orientation, slot.variant)) {
            continue;
        }

        // Remember actual place — next snapshot / remount uses this map's coords.
        slot.tile_x = (int16_t)tile.x();
        slot.tile_y = (int16_t)tile.y();
        slot.orientation = orientation;
    }
}

io_buffer *iob_campaign_carry_troops = new io_buffer([](io_buffer *iob, size_t version) {
    for (int i = 0; i < TROOP_CARRY_MAX; i++) {
        auto &s = g_campaign_carry.troops[i];
        iob->bind_u8(s.has_data);
        iob->bind_u8(s.pending);
        iob->bind_u8(s.num_figures);
        iob->bind_u8(s.has_military_training);
        iob->bind_i16(s.morale);
        iob->bind_u16(s.experience);
    }
    iob->bind_u8(g_campaign_carry.notice_posted);
    iob->bind____skip(7);
}, [](size_t version) {
    // troop carry lives outside city_data, so a save without this chunk would keep
    // the previous session's snapshot - the exact bug pre_load() was patched for
    g_campaign_carry.clear_troops();
});

// 8 slots × 12 bytes = 96
io_buffer *iob_campaign_carry_monuments = new io_buffer([](io_buffer *iob, size_t version) {
    for (int i = 0; i < CAMPAIGN_CARRY_MONUMENT_MAX; i++) {
        auto &s = g_campaign_carry.monuments[i];
        iob->bind_u8(s.has_data);
        iob->bind_u8(s.orientation);
        iob->bind_u8(s.variant);
        iob->bind_u8(s.pad);
        iob->bind_u16(s.type);
        iob->bind_i16(s.tile_x);
        iob->bind_i16(s.tile_y);
    }
}, [](size_t version) {
    g_campaign_carry.clear_monuments();
});
