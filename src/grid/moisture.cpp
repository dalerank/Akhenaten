#include "moisture.h"
#include "grid.h"
#include "terrain.h"
#include "tiles.h"
#include "io/io_buffer.h"
#include "core/log.h"

#include <algorithm>

static grid_xx terrain_moisture(FS_UINT8);

// Sampled at map load by map_moisture_recompute_profile(): per-ring grass
// byte for ring distances 1..16 from water. Index 0 is unused; values
// outside the sampled range are 0 (desert). When the brush refills moisture
// under cleared land, each tile looks up its ring distance in this table —
// so the painted band's plateau width and taper shape match the original
// mapper's brush instead of a synthetic linear formula.
static uint8_t s_moisture_profile[17] = {0};

// Cached largest ring with a non-zero profile entry. Used to widen the
// empty-land image refresh after a paint stroke. Default mirrors the
// load-time fallback for waterless maps.
static int s_map_grass_radius = 4;

uint8_t map_moisture_get(int grid_offset) {
    return map_grid_get(terrain_moisture, grid_offset);
}

void map_moisture_clear_tile(int grid_offset) {
    map_grid_set(terrain_moisture, grid_offset, 0);
}

uint8_t map_grasslevel_get(int grid_offset) {
    int moist = map_moisture_get(grid_offset);
    //    if (moist & MOISTURE_TALLGRASS)
    ////        return moist - MOISTURE_TALLGRASS + 20;
    //        return 64;
    if (moist & MOISTURE_TRANSITION)
        return moist - MOISTURE_TRANSITION + 16;
    if (moist & MOISTURE_GRASS)
        return (moist - MOISTURE_GRASS) / 8 + 1;
    if (!moist)
        return 0;
    return 13;
}
// bool map_is_4x4_tallgrass(pixel_coordinate pixel, tile2i point) {
//     int x_min, y_min, x_max, y_max;
//     map_grid_get_area(x, y, 1, 3, &x_min, &y_min, &x_max, &y_max);
//
//     for (int yy = y_min; yy <= y_max; yy++) {
//         for (int xx = x_min; xx <= x_max; xx++) {
//             if (map_grasslevel_get(map_grid_offset(xx, yy)) != 12)
//                 return false;
//         }
//     }
//     return true;
// }

// Expanding-ring probe for the nearest OPEN water tile (river / sea), with
// floodplain tiles deliberately excluded. Returns the ring distance
// (1..max_d), or max_d + 1 if no open water is within range.
//
// Floodplain tiles often carry the TERRAIN_WATER bit during the flood
// stage of the cycle, but the original game does not grow a grass band
// against the land/floodplain edge — only against open river/sea shore.
// Filtering out anything with TERRAIN_FLOODPLAIN keeps painted grass
// consistent with that behaviour. Deepwater still counts (the Nile is
// largely TERRAIN_DEEPWATER along its centre line).
static int distance_to_water(tile2i tile, int max_d) {
    for (int r = 1; r <= max_d; ++r) {
        const grid_area area = map_grid_get_area(tile, 1, r);
        for (int yy = area.tmin_y; yy <= area.tmax_y; ++yy) {
            for (int xx = area.tmin_x; xx <= area.tmax_x; ++xx) {
                const int n = MAP_OFFSET(xx, yy);
                if (map_terrain_is(n, TERRAIN_WATER | TERRAIN_DEEPWATER)
                    && !map_terrain_is(n, TERRAIN_FLOODPLAIN)) {
                    return r;
                }
            }
        }
    }
    return max_d + 1;
}

// Only refill moisture on empty land. TERRAIN_NOT_CLEAR covers water,
// deepwater, floodplain, building, road, rock, tree, marshland, etc. —
// keeping a single guard prevents the brush from clobbering authored
// moisture under non-empty tiles. Per-tile moisture = the map's authored
// profile at this tile's ring distance to water; tiles beyond the band get
// 0 (desert).
static void recompute_moisture_tile(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)) {
        return;
    }
    int d = distance_to_water(tile2i(grid_offset), 16);
    uint8_t m = (d >= 1 && d <= 16) ? s_moisture_profile[d] : 0;
    map_grid_set(terrain_moisture, grid_offset, m);
}

void map_moisture_update_region(tile2i tmin, tile2i tmax) {
    // Update moisture for EXACTLY the given region — no internal widening.
    // The right widening depends on what the brush did:
    //   * paint-over-water removed a water tile, so adjacent land's
    //     distance-to-water grew → widen by band radius
    //   * paint-over-land changed nobody's distance-to-water → no widening;
    //     widening here would rewrite the mapper's authored per-tile
    //     variation with the smoothed profile and turn authored desert into
    //     uniform low-grass anywhere within band radius of the brush
    // Callers (editor_tool_update_use) own that decision. map_grid_bound_area
    // still clamps the supplied rect safely if coordinates go off-map.
    map_tiles_foreach_region_tile(tmin, tmax, recompute_moisture_tile);
}

int map_moisture_band_radius() {
    return s_map_grass_radius;
}

void map_moisture_recompute_profile() {
    // Build the painted-grass profile from two summary measurements of the
    // authored map:
    //   * plateau_width P — the largest ring d at which a majority of the
    //     empty-land tiles are level 12 (the full-grass shore band)
    //   * band_radius   D — the largest ring d at which any grass tile
    //     appears at all (the taper's far edge)
    //
    // The painted profile then is a deterministic plateau + linear taper:
    //   d in [1, P]   → level 12   (byte 95)
    //   d in (P, D]   → linear from level 11 down to level 1
    //   d > D         → 0          (desert)
    //
    // This deliberately ignores per-tile noise in the authored gradient and
    // imitates the visual pattern Pharaoh maps almost always follow: a wide
    // level-12 plateau against the water, then a tapering transition into
    // desert. Inferring P and D from the map keeps painted bands consistent
    // with whatever the original mapper drew.
    constexpr int probe_cap = 16;
    int total_count[17] = {0};
    int level12_count[17] = {0};
    int grass_count[17] = {0};

    map_tiles_foreach_map_tile([&](int grid_offset) {
        if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)) {
            return;
        }
        uint8_t lvl = map_grasslevel_get(grid_offset);
        if (lvl > 12) {
            // level-13 fallback / level-16+ transitions are corner art,
            // not gradient samples
            return;
        }
        int d = distance_to_water(tile2i(grid_offset), probe_cap);
        if (d < 1 || d > probe_cap) {
            // farther than the probe cap from any water — not part of the
            // measured grass band
            return;
        }
        total_count[d] += 1;
        if (lvl > 0) {
            grass_count[d] += 1;
        }
        if (lvl == 12) {
            level12_count[d] += 1;
        }
    });

    // Plateau width: walk outward, advance as long as the current ring has
    // a meaningful density of level-12 tiles (>=25% of empty-land samples).
    // The 25% bar is intentionally lower than a strict majority: real
    // authored shores typically have ~30-45% level-12 tiles inside the
    // plateau (the rest are scattered shrubs, paths, lower-level grass)
    // and crash to single-digit percentages once the taper begins, which
    // makes 25% a clean cutoff at the discontinuity. Empty rings (no
    // samples) are skipped without breaking the plateau, so a map with
    // sparse data near the shore still measures a plateau if the next
    // sampled ring still has it.
    int plateau_width = 0;
    bool plateau_open = true;
    for (int d = 1; d <= probe_cap && plateau_open; ++d) {
        if (total_count[d] == 0) {
            continue;
        }
        if (level12_count[d] * 4 >= total_count[d]) {
            plateau_width = d;
        } else {
            plateau_open = false;
        }
    }

    // Band radius: the largest ring with any grass at all. Even rings with
    // just a few stray grass tiles count, so the taper extends as far as
    // the authored grass does.
    int band_radius = 0;
    for (int d = probe_cap; d >= 1; --d) {
        if (grass_count[d] > 0) {
            band_radius = d;
            break;
        }
    }
    if (band_radius < plateau_width) {
        band_radius = plateau_width; // safety: band ends no earlier than plateau
    }

    for (int d = 0; d < 17; ++d) {
        s_moisture_profile[d] = 0;
    }

    if (band_radius == 0) {
        // Waterless / grassless map — seed a synthetic fallback so the
        // brush still produces a reasonable band if the user later paints
        // water. Levels 12 → 9 → 6 → 3 = bytes 95 → 71 → 47 → 23.
        s_moisture_profile[1] = 95;
        s_moisture_profile[2] = 71;
        s_moisture_profile[3] = 47;
        s_moisture_profile[4] = 23;
        s_map_grass_radius = 4;
        return;
    }

    const int taper_span = band_radius - plateau_width;
    for (int d = 1; d <= band_radius; ++d) {
        int level;
        if (d <= plateau_width) {
            level = 12;
        } else {
            // Linear taper from level 11 (just past the plateau) down to
            // level 1 (at the band's far edge). Round to nearest.
            const int taper_d = d - plateau_width;
            level = (11 * (taper_span - taper_d + 1) + taper_span / 2) / taper_span;
            level = std::clamp(level, 1, 11);
        }
        s_moisture_profile[d] = static_cast<uint8_t>(MOISTURE_GRASS + 8 * (level - 1));
    }

    s_map_grass_radius = std::clamp(band_radius, 2, 16);

    // TEMPORARY DIAGNOSTIC: paste these lines back if the painted gradient
    // looks wrong. Per-ring counts of empty-land tiles, level-12 tiles, any
    // grass, and the final profile byte the brush will write at each ring.
    logs::info("[moisture] plateau=%d band=%d radius=%d", plateau_width, band_radius, s_map_grass_radius);
    for (int d = 1; d <= 16; ++d) {
        logs::info("[moisture]  d=%2d  total=%5d  lvl12=%5d  grass=%5d  profile=%3d",
                   d, total_count[d], level12_count[d], grass_count[d], (int)s_moisture_profile[d]);
    }
}

io_buffer* iob_moisture_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &terrain_moisture);
});
