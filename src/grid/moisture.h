#pragma once

#include "grid/point.h"

#include <cstdint>

enum {
    // Pharaoh moisture combinators
    MOISTURE_GRASS = 0x7,
    MOISTURE_TRANSITION = 0x80,
    //    MOISTURE_TALLGRASS = 0x40,
    //    MOISTURE_SHORE_TIP = 0x24,
    MOISTURE_SHORE_TALLGRASS = 0x64
};

uint8_t map_moisture_get(int grid_offset);
uint8_t map_grasslevel_get(int grid_offset);

// Force a single tile's moisture to 0. Used by the out-of-diamond
// normalization pass — those tiles must render as plain desert, and
// map_grasslevel_get returns 0 only when moisture is 0.
void map_moisture_clear_tile(int grid_offset);
// bool map_is_4x4_tallgrass(pixel_coordinate pixel, map_point point);

// Editor-side moisture regrowth. The moisture grid drives grass-vs-desert in
// set_empty_land_pass2; in regular gameplay it is purely authored data, but
// the debug terrain-paint tools mutate water/land and need a way to refill
// moisture under the freshly-cleared land so a grassy shore band reappears.
//
// Updates EXACTLY the supplied region — does NOT widen by band radius. The
// caller owns that decision: paint-over-water needs widening by
// map_moisture_band_radius() (distance-to-water grew for surrounding land);
// paint-over-land needs no widening (distance did not change for any tile,
// so a wider rewrite would just clobber the mapper's authored per-tile
// variation with the smoothed profile, turning authored desert near water
// into uniform low-grass).
void map_moisture_update_region(tile2i tmin, tile2i tmax);

// Cached on map load: the farthest ring distance (1..12) at which the
// measured moisture profile is still non-zero. Used to widen the empty-land
// image refresh after a paint stroke so the outer grass-band tiles also
// regenerate. Falls back to 4 on waterless / grassless maps.
int map_moisture_band_radius();

// Sample the authored moisture grid into a per-ring-distance profile (mean
// moisture byte at each distance to water, smoothed monotonically). Called
// once at map load. Painted tiles replay this profile so the new grass band
// matches what the original mapper drew — plateau width and taper shape
// come from the data, not from a synthetic formula.
void map_moisture_recompute_profile();
