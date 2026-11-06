#include "monument_pyramid_ramp.h"

#include "building/monument_pyramid.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_mastaba_engine.h"
#include "city/city_buildings.h"
#include "core/calc.h"
#include "core/direction.h"
#include "figure/figure.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/grid.h"

#include <algorithm>
#include <cstring>

int pyramid_ramp_og_subtype(int part_count, tile2i footprint_nw, tile2i part_tile) {
    auto &engine = g_monument_pyramid_engine;
    const int n = std::clamp(part_count, 0, (int)PYRAMID_PARTS_CAPACITY);
    const auto &offsets = engine.part_grid_offsets();
    int min_dx = 0, min_dy = 0;
    engine.size_norm_origin(n, min_dx, min_dy);
    const int want_dx = part_tile.x() - footprint_nw.x();
    const int want_dy = part_tile.y() - footprint_nw.y();
    for (int i = 0; i < n; ++i) {
        int dx = 0, dy = 0;
        engine.offset_to_xy(offsets[i], dx, dy);
        if (dx - min_dx == want_dx && dy - min_dy == want_dy) {
            return i;
        }
    }
    return -1;
}

int pyramid_engine_part_needs_ramp(building_id part_id) {
    building *part = building_get(part_id);
    if (!part) {
        return PYRAMID_RAMP_NONE;
    }
    building *head = part->main();
    if (!head || !g_monument_pyramid_engine.uses_block_engine(head)) {
        return PYRAMID_RAMP_NONE;
    }
    const e_pyramid_style style = g_monument_pyramid_engine.style_of(head);
    if (style == PYRAMID_STYLE_NONE || style == PYRAMID_STYLE_MASTABA) {
        return PYRAMID_RAMP_NONE;
    }
    auto *ps = pyramid_part_state_get(part_id);
    auto *ms = pyramid_main_state_get(head->id);
    if (!ps || !ms) {
        return PYRAMID_RAMP_NONE;
    }
    // OG: both part and main in casing → no more ramp work.
    auto *main_ps = pyramid_part_state_get(head->id);
    if (ps->stage == PYRAMID_STAGE_CASING && main_ps && main_ps->stage == PYRAMID_STAGE_CASING) {
        return PYRAMID_RAMP_NONE;
    }

    const int subtype = ps->subtype;
    const int height = g_monument_pyramid_engine.part_height(*ps);
    for (const auto &ramp : g_monument_pyramid_engine.ramp_specs_for(head)) {
        if (ramp.part != subtype) {
            continue;
        }
        if (ramp.ramp1_height > 0 && ramp.ramp1_height <= height && ps->ramp1_height == 0) {
            return PYRAMID_RAMP_FIRST;
        }
        if (ramp.ramp2_height < 1 || height < ramp.ramp2_height || ps->ramp2_height != 0) {
            return PYRAMID_RAMP_NONE;
        }
        return PYRAMID_RAMP_SECOND;
    }
    return PYRAMID_RAMP_NONE;
}

bool pyramid_engine_has_ramp_work(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head || !g_monument_pyramid_engine.uses_block_engine(head)) {
        return false;
    }
    auto *ms = pyramid_main_state_get(head->id);
    if (!ms || !ms->block_phase_active) {
        return false;
    }
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);
    for (building *p : parts) {
        if (pyramid_engine_part_needs_ramp(p->id) != PYRAMID_RAMP_NONE) {
            return true;
        }
    }
    return false;
}

building_id pyramid_engine_find_ramp_part(building *main, figure_id claim_fid) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head) {
        return 0;
    }
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);

    // OG: walk ramp schedule in order; first needing part wins (busy → skip pyramid).
    for (const auto &ramp : g_monument_pyramid_engine.ramp_specs_for(head)) {
        building *part = nullptr;
        for (building *p : parts) {
            auto *ps = pyramid_part_state_get(p->id);
            if (ps && ps->subtype == ramp.part) {
                part = p;
                break;
            }
        }
        if (!part || pyramid_engine_part_needs_ramp(part->id) == PYRAMID_RAMP_NONE) {
            continue;
        }
        auto *ps = pyramid_part_state_get(part->id);
        if (!ps) {
            return 0;
        }
        if (ps->worker_figure_id != 0 && pyramid_engine_part_has_active_worker(part->id)) {
            return 0;
        }
        if (claim_fid) {
            ps->worker_figure_id = claim_fid;
        }
        return part->id;
    }
    return 0;
}

void pyramid_engine_update_part_ramp_image(building_id part_id) {
    building *part = building_get(part_id);
    auto *ps = pyramid_part_state_get(part_id);
    if (!part || !ps) {
        return;
    }
    building *head = part->main();
    if (!head) {
        return;
    }
    const e_pyramid_style style = g_monument_pyramid_engine.style_of(head);
    if (style == PYRAMID_STYLE_NONE || style == PYRAMID_STYLE_MASTABA) {
        ps->ramp_image_id = 0;
        return;
    }

    auto &engine = g_monument_pyramid_engine;
    // OG uses pyramid_part_layout[size][subtype].kind — not full-footprint geometry
    // (inner-ring edge parts stay EDGE_BOTTOM_* so they still get ramp sprites).
    int kind = engine.layout_kind(head, ps->subtype);
    kind = engine.rotated_kind(kind, g_camera.orientation / 2);

    const int ramp_img = engine.ramp_base_image(*part, kind, style);
    if ((ps->ramp1_height == 0 && ps->ramp2_height == 0) || ramp_img <= 0) {
        ps->ramp_image_id = 0;
        ps->ramp_image_x1 = ps->ramp_image_y1 = 0;
        ps->ramp_image_x2 = ps->ramp_image_y2 = 0;
        return;
    }
    engine.set_ramp_offsets(*ps, kind, style);
    ps->ramp_image_id = (uint32_t)ramp_img;
}

void pyramid_engine_clear_part_ramps(building_id part_id) {
    auto *ps = pyramid_part_state_get(part_id);
    if (!ps) {
        return;
    }
    ps->ramp1_height = 0;
    ps->ramp2_height = 0;
    ps->ramp_image_id = 0;
    ps->ramp_image_x1 = ps->ramp_image_y1 = 0;
    ps->ramp_image_x2 = ps->ramp_image_y2 = 0;
    ps->ramp_link_part_id = 0;
    ps->ramp_link_draw_x = ps->ramp_link_draw_y = 0;
}

void pyramid_engine_clear_all_ramps(building *main) {
    building *head = g_monument_pyramid_engine.chain_head(main);
    if (!head) {
        return;
    }
    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    g_monument_pyramid_engine.collect_parts(head, parts);
    for (building *p : parts) {
        pyramid_engine_clear_part_ramps(p->id);
    }
}

void pyramid_engine_set_force_show_ramps(building *main, bool enable) {
    auto &engine = g_monument_pyramid_engine;
    building *head = engine.chain_head(main);
    if (!head || !engine.uses_block_engine(head)) {
        return;
    }

    auto *ms = pyramid_main_state_get(head->id);
    if (!ms || ms->style == PYRAMID_STYLE_NONE) {
        pyramid_engine_init(head);
        ms = pyramid_main_state_get(head->id);
    }
    if (!ms) {
        return;
    }

    ms->force_show_ramps = enable ? 1 : 0;
    if (!enable) {
        pyramid_engine_clear_all_ramps(head);
        return;
    }

    const e_pyramid_style style = engine.style_of(head);
    if (style == PYRAMID_STYLE_NONE || style == PYRAMID_STYLE_MASTABA) {
        return;
    }

    svector<building *, PYRAMID_PARTS_CAPACITY> parts;
    engine.collect_parts(head, parts);

    auto find_by_subtype = [&](uint8_t subtype) -> building * {
        for (building *p : parts) {
            auto *ps = pyramid_part_state_get(p->id);
            if (ps && ps->subtype == subtype) {
                return p;
            }
        }
        return nullptr;
    };

    auto set_height = [&](building *part, bool first, uint8_t height) {
        if (!part || !height) {
            return;
        }
        auto *ps = pyramid_part_state_get(part->id);
        if (!ps) {
            return;
        }
        if (first) {
            ps->ramp1_height = height;
        } else {
            ps->ramp2_height = height;
        }
        pyramid_engine_update_part_ramp_image(part->id);
    };

    for (const auto &ramp : engine.ramp_specs_for(head)) {
        building *part = find_by_subtype(ramp.part);
        set_height(part, true, ramp.ramp1_height);
        set_height(part, false, ramp.ramp2_height);
        if (style == PYRAMID_STYLE_STEPPED) {
            set_height(find_by_subtype(ramp.ramp1_linked_part), true, ramp.ramp1_height);
            set_height(find_by_subtype(ramp.ramp2_linked_part), false, ramp.ramp2_height);
        }
    }
}

void pyramid_engine_build_ramp(building_id part_id) {
    building *part = building_get(part_id);
    auto *ps = pyramid_part_state_get(part_id);
    if (!part || !ps) {
        return;
    }
    building *head = part->main();
    if (!head) {
        return;
    }
    const e_pyramid_style style = g_monument_pyramid_engine.style_of(head);
    if (style == PYRAMID_STYLE_NONE || style == PYRAMID_STYLE_MASTABA) {
        return;
    }
    if (pyramid_engine_part_needs_ramp(part_id) == PYRAMID_RAMP_NONE) {
        return;
    }

    for (const auto &ramp : g_monument_pyramid_engine.ramp_specs_for(head)) {
        if (ramp.part != ps->subtype) {
            continue;
        }
        int height = 0;
        int link = 0;
        bool is_first = false;
        if (ramp.ramp1_height > 0 && ramp.ramp1_height <= g_monument_pyramid_engine.part_height(*ps) && ps->ramp1_height == 0) {
            height = ramp.ramp1_height;
            link = ramp.ramp1_linked_part;
            ps->ramp1_height = (uint8_t)height;
            is_first = true;
        } else if (ramp.ramp2_height > 0 && ramp.ramp2_height <= g_monument_pyramid_engine.part_height(*ps) && ps->ramp2_height == 0) {
            height = ramp.ramp2_height;
            link = ramp.ramp2_linked_part;
            ps->ramp2_height = (uint8_t)height;
        }
        if (height == 0) {
            continue;
        }
        pyramid_engine_update_part_ramp_image(part_id);
        if (style != PYRAMID_STYLE_STEPPED || link == 0) {
            return;
        }
        // Linked part shares height (stepped). Find by subtype.
        svector<building *, PYRAMID_PARTS_CAPACITY> parts;
        g_monument_pyramid_engine.collect_parts(head, parts);
        for (building *lp : parts) {
            auto *lps = pyramid_part_state_get(lp->id);
            if (!lps || lps->subtype != (uint8_t)link) {
                continue;
            }
            if (is_first) {
                lps->ramp1_height = (uint8_t)height;
            } else {
                lps->ramp2_height = (uint8_t)height;
            }
            pyramid_engine_update_part_ramp_image(lp->id);
            return;
        }
        return;
    }
}

static int pyramid_ramp_sprite_for(building &part, const pyramid_part_state &ps, uint8_t height) {
    building *head = part.main();
    const e_pyramid_style style = head ? g_monument_pyramid_engine.style_of(head) : PYRAMID_STYLE_NONE;
    if (style != PYRAMID_STYLE_STEPPED || height == 0) {
        return 0;
    }
    int kind = g_monument_pyramid_engine.layout_kind(head, ps.subtype);
    kind = g_monument_pyramid_engine.rotated_kind(kind, g_camera.orientation / 2);
    if (kind >= PYRAMID_PART_EDGE_TOP_LEFT) {
        return (height - 1) % 3;
    }
    switch (height % PYRAMID_RAMP_BLOCKS_PER_LAYER) {
    case 2: return 1;
    case 4: return 2;
    case 5: return 3;
    default: return 0;
    }
}

static vec2i pyramid_ramp_stepped_shift(building &part, int image_id) {
    building *head = part.main();
    const e_pyramid_style style = head ? g_monument_pyramid_engine.style_of(head) : PYRAMID_STYLE_NONE;
    if (style != PYRAMID_STYLE_STEPPED) {
        return {};
    }
    const int base = building_static_params::get(part.type).first_img("ramps");
    if (base <= 0) {
        return {};
    }
    const int index = image_id - base;
    if (index < 0 || index >= (int)pyramid_engine_config.stepped_ramp_shift.size()) {
        return {};
    }
    return pyramid_engine_config.stepped_ramp_shift[index];
}

static void pyramid_ramp_draw_sprites(painter &ctx, building &part, vec2i part_anchor_px, color mask) {
    auto *ps = pyramid_part_state_get(part.id);
    if (!ps || ps->ramp_image_id == 0) {
        return;
    }

    // draw_one_ramp → image_draw (plain), not isometric footprint draw.
    // ert_drawtile_full applies size-based Y shift and breaks ramp_base/offsets.
    mask = mask ? mask : 0xffffffff;
    if (ps->ramp1_height) {
        const int sprite = pyramid_ramp_sprite_for(part, *ps, ps->ramp1_height);
        const int image_id = (int)ps->ramp_image_id + sprite;
        auto &cmd = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        cmd.image_id = image_id;
        cmd.pixel = part_anchor_px + vec2i{ps->ramp_image_x1, ps->ramp_image_y1}
            + pyramid_ramp_stepped_shift(part, image_id);
        cmd.mask = mask;
    }
    if (ps->ramp2_height) {
        const int sprite = pyramid_ramp_sprite_for(part, *ps, ps->ramp2_height);
        const int image_id = (int)ps->ramp_image_id + sprite;
        auto &cmd = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        cmd.image_id = image_id;
        cmd.pixel = part_anchor_px + vec2i{ps->ramp_image_x2, ps->ramp_image_y2}
            + pyramid_ramp_stepped_shift(part, image_id);
        cmd.mask = mask;
    }
}

static building *pyramid_ramp_neighbour_at(building &part, int32_t delta) {
    const int offset = part.tile.grid_offset() + delta;
    if (offset < 0 || offset >= GRID_SIZE_TOTAL) {
        return nullptr;
    }
    const int nid = map_building_at(offset);
    if (!nid) {
        return nullptr;
    }
    building *neighbor = building_get(nid);
    if (!neighbor) {
        return nullptr;
    }
    building *head = part.main();
    if (!head || neighbor->main() != head) {
        return nullptr;
    }
    if (!g_monument_pyramid_engine.uses_block_engine(neighbor)) {
        return nullptr;
    }
    return neighbor;
}

static tile2i pyramid_part_draw_anchor(building &part) {
    switch (g_camera.orientation) {
    case DIR_0_TOP_RIGHT: return part.tile.shifted(0, 1);
    case DIR_4_BOTTOM_LEFT: return part.tile.shifted(1, 0);
    case DIR_6_TOP_LEFT: return part.tile.shifted(1, 1);
    default: return part.tile;
    }
}

static building *pyramid_ramp_link_neighbor(building &part, const pyramid_part_state &ps) {
    building *head = part.main();
    const e_pyramid_style style = head ? g_monument_pyramid_engine.style_of(head) : PYRAMID_STYLE_NONE;
    if (ps.ramp1_height < 7 || style == PYRAMID_STYLE_NONE || style == PYRAMID_STYLE_MASTABA) {
        return nullptr;
    }
    bool special = false;
    if (style == PYRAMID_STYLE_STEPPED) {
        special = ((int)ps.ramp1_height - 1) % PYRAMID_RAMP_BLOCKS_PER_LAYER < 3;
    } else {
        special = (ps.ramp1_height % PYRAMID_RAMP_BLOCKS_PER_LAYER) == 1;
    }
    if (!special) {
        return nullptr;
    }
    int kind = g_monument_pyramid_engine.layout_kind(head, ps.subtype);
    kind = g_monument_pyramid_engine.rotated_kind(kind, g_camera.orientation / 2);
    const bool attach = (style == PYRAMID_STYLE_STEPPED)
        ? (kind != PYRAMID_PART_CORNER_TOP && kind != PYRAMID_PART_EDGE_TOP_LEFT
            && kind != PYRAMID_PART_EDGE_TOP_RIGHT)
        : (kind == PYRAMID_PART_EDGE_BOTTOM_LEFT || kind == PYRAMID_PART_EDGE_BOTTOM_RIGHT);
    if (!attach) {
        return nullptr;
    }
    const int view = g_camera.orientation / 2;
    const int slot = (kind == PYRAMID_PART_CORNER_BOTTOM) ? 0 : 1;
    const int32_t delta = pyramid_engine_config.neighbour_offsets[view * 3 + slot];
    return pyramid_ramp_neighbour_at(part, delta);
}

static vec2i pyramid_ramp_origin_for_part(building &part) {
    const tile2i anchor = pyramid_part_draw_anchor(part);
    const vec2i anchor_px = g_camera.lookup_tile_to_pixel(anchor);
    int L = 0;
    if (auto *mon = part.dcast_monument()) {
        L = mon->runtime_data().layer;
    }
    const vec2i pixel = anchor_px - vec2i{0, TILE_HEIGHT_PIXELS * 3 * L};
    return pixel + vec2i{HALF_TILE_WIDTH_PIXELS + 1, -HALF_TILE_HEIGHT_PIXELS};
}

void pyramid_ramp_prepare_frame_links() {
    // Serial pre-pass: OG stores ramp-link on the closer neighbor before city draw.
    // Height ornaments later run in parallel row blocks — in-draw store/consume races
    // and a sort_pixel stand-in both break under camera rotate.
    for (int id = 1; id < MAX_BUILDINGS; ++id) {
        auto *ps = pyramid_part_state_get(id);
        if (!ps) {
            continue;
        }
        ps->ramp_link_part_id = 0;
        ps->ramp_link_draw_x = ps->ramp_link_draw_y = 0;
    }
    for (int id = 1; id < MAX_BUILDINGS; ++id) {
        building *part = building_get(id);
        auto *ps = pyramid_part_state_get(id);
        if (!part || !ps || (ps->ramp1_height == 0 && ps->ramp2_height == 0)) {
            continue;
        }
        building *neighbor = pyramid_ramp_link_neighbor(*part, *ps);
        if (!neighbor) {
            continue;
        }
        auto *nps = pyramid_part_state_get(neighbor->id);
        if (!nps) {
            continue;
        }
        const vec2i origin = pyramid_ramp_origin_for_part(*part);
        nps->ramp_link_part_id = part->id;
        nps->ramp_link_draw_x = origin.x;
        nps->ramp_link_draw_y = origin.y;
    }
}

void pyramid_ramp_draw_part(painter &ctx, building &part, vec2i part_anchor_px, color mask) {
    auto *ps = pyramid_part_state_get(part.id);
    if (!ps) {
        return;
    }
    // Consume links stored by pyramid_ramp_prepare_frame_links (OG: draw during neighbor).
    if (ps->ramp_link_part_id) {
        building *other = building_get(ps->ramp_link_part_id);
        if (other) {
            pyramid_ramp_draw_sprites(ctx, *other,
                vec2i{ps->ramp_link_draw_x, ps->ramp_link_draw_y}, mask);
        }
        ps->ramp_link_part_id = 0;
        ps->ramp_link_draw_x = ps->ramp_link_draw_y = 0;
    }
    // Source part that attached to a neighbor: skip own ramps this frame.
    if (pyramid_ramp_link_neighbor(part, *ps)) {
        return;
    }
    pyramid_ramp_draw_sprites(ctx, part, part_anchor_px, mask);
}
