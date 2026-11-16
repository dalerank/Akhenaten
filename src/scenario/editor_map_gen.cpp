#include "editor_map_gen.h"

#include "core/random.h"
#include "grid/elevation.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "scenario/editor_map.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

namespace {

enum TerrainType {
    unknown = 0,
    deepWater = 1,
    water = 2,
    coast = 3,
    grass = 4,
    hills = 5,
    trees = 6,
    ground = 7,
    shallowMountain = 8,
};

// Own xorshift32 instead of std::rand: same map for the same seed on every platform and run.
class GenRandom {
public:
    void seed(uint32_t value) { state_ = value ? value : 0x9E3779B9u; }

    int to_int(int minimum, int maximum) {
        if (maximum <= minimum)
            return minimum;
        return minimum + static_cast<int>(next() % static_cast<uint32_t>(maximum - minimum + 1));
    }

    float to_float(float minimum, float maximum) {
        const float unit = static_cast<float>(next() >> 8) / 16777216.f;
        return minimum + unit * (maximum - minimum);
    }

private:
    uint32_t next() {
        state_ ^= state_ << 13;
        state_ ^= state_ >> 17;
        state_ ^= state_ << 5;
        return state_;
    }

    uint32_t state_ = 0x9E3779B9u;
};

GenRandom g_rng;

class MidpointDisplacement {
public:
    MidpointDisplacement(int n, int wmult, int hmult, float smoothness, float terrain_square)
        : n_(n), wmult_(wmult), hmult_(hmult), smoothness_(smoothness), terrain_square_(terrain_square) {}

    int width() const {
        return width_;
    }
    int height() const {
        return height_;
    }

    std::vector<int> map() {
        const int power = 1 << n_;
        width_ = wmult_ * power + 1;
        height_ = hmult_ * power + 1;

        std::vector<float> heightmap(width_ * height_, 0.f);
        std::vector<int> return_map(width_ * height_, unknown);

        int step = power / 2;
        float h = terrain_square_;

        for (int i = 0; i < width_; i += 2 * step) {
            for (int j = 0; j < height_; j += 2 * step) {
                heightmap[idx(i, j)] = g_rng.to_float(0, 2 * h);
            }
        }

        for (int i = 0; i < width_; i++) {
            heightmap[idx(i, 0)] = g_rng.to_float(-3, -2);
            heightmap[idx(i, height_ - 1)] = g_rng.to_float(-2, -1);
        }
        for (int i = 0; i < height_; i++) {
            heightmap[idx(0, i)] = g_rng.to_float(-3, -2);
            heightmap[idx(width_ - 1, i)] = g_rng.to_float(-3, -2);
        }

        heightmap[idx((width_ - 1) / 2, (height_ - 1) / 2)] = (2 * h) + g_rng.to_float(1, 5);

        while (step > 0) {
            for (int x = step; x < width_; x += 2 * step) {
                for (int y = step; y < height_; y += 2 * step) {
                    const float sum = heightmap[idx(x - step, y - step)] + heightmap[idx(x - step, y + step)]
                                    + heightmap[idx(x + step, y - step)] + heightmap[idx(x + step, y + step)];
                    heightmap[idx(x, y)] = sum / 4.f + g_rng.to_float(-h, h);
                }
            }

            for (int x = 0; x < width_; x += step) {
                for (int y = step * (1 - (x / step) % 2); y < height_; y += 2 * step) {
                    float sum = 0.f;
                    int count = 0;
                    if (x - step >= 0) {
                        sum += heightmap[idx(x - step, y)];
                        count++;
                    }
                    if (x + step < width_) {
                        sum += heightmap[idx(x + step, y)];
                        count++;
                    }
                    if (y - step >= 0) {
                        sum += heightmap[idx(x, y - step)];
                        count++;
                    }
                    if (y + step < height_) {
                        sum += heightmap[idx(x, y + step)];
                        count++;
                    }
                    heightmap[idx(x, y)] = count > 0 ? sum / count + g_rng.to_float(-h, h) : 0.f;
                }
            }
            h /= smoothness_;
            step /= 2;
        }

        for (size_t i = 0; i < heightmap.size(); i++) {
            const float value = heightmap[i];
            int new_value = ground;
            if (value < deep_water_threshold_)
                new_value = deepWater;
            else if (value < water_threshold_)
                new_value = water;
            else if (value < sand_threshold_)
                new_value = coast;
            else if (value < grass_threshold_)
                new_value = grass;
            else if (value < hills_threshold_)
                new_value = hills;
            else if (value < trees_threshold_)
                new_value = trees;
            else if (value < shmountains_threshold_)
                new_value = shallowMountain;
            else
                new_value = ground;
            return_map[i] = new_value;
        }
        return return_map;
    }

private:
    int idx(int x, int y) const {
        return x + y * width_;
    }

    float grass_threshold_ = 2.25f;
    float water_threshold_ = 0.55f;
    float sand_threshold_ = 0.70f;
    float deep_water_threshold_ = 0.0001f;
    float hills_threshold_ = 3.75f;
    float trees_threshold_ = 4.0f;
    float shmountains_threshold_ = 4.90f;
    int n_;
    int wmult_;
    int hmult_;
    float smoothness_;
    float terrain_square_;
    int width_ = 0;
    int height_ = 0;
};

int map_w() {
    return g_scenario.map.width;
}
int map_h() {
    return g_scenario.map.height;
}

bool in_bounds(int x, int y) {
    return x >= 0 && y >= 0 && x < map_w() && y < map_h();
}

int offset_xy(int x, int y) {
    return MAP_OFFSET(x, y);
}

bool is_water(int x, int y) {
    const int t = map_terrain_get(offset_xy(x, y));
    return (t & (TERRAIN_WATER | TERRAIN_DEEPWATER)) != 0;
}

bool is_land_for_river(int x, int y) {
    if (!in_bounds(x, y))
        return false;
    const int t = map_terrain_get(offset_xy(x, y));
    if (t & (TERRAIN_WATER | TERRAIN_DEEPWATER | TERRAIN_ROCK | TERRAIN_ELEVATION))
        return false;
    return true;
}

bool is_walkable_for_road(int x, int y) {
    if (!in_bounds(x, y))
        return false;
    const int t = map_terrain_get(offset_xy(x, y));
    if (t & (TERRAIN_WATER | TERRAIN_DEEPWATER | TERRAIN_ROCK | TERRAIN_ELEVATION))
        return false;
    return true;
}

int n2size_for_map(int map_size) {
    // width = 8 * 2^n + 1 must cover map_size
    for (int n = 2; n <= 7; n++) {
        if (8 * (1 << n) + 1 >= map_size)
            return n;
    }
    return 7;
}

void paint_heightfield(const std::vector<int> &gen, int gen_w, int gen_h) {
    const int mw = map_w();
    const int mh = map_h();
    const int ox = std::max(0, (gen_w - mw) / 2);
    const int oy = std::max(0, (gen_h - mh) / 2);

    for (int y = 0; y < mh; y++) {
        for (int x = 0; x < mw; x++) {
            const int gx = std::min(gen_w - 1, ox + x);
            const int gy = std::min(gen_h - 1, oy + y);
            const int type = gen[gx + gy * gen_w];
            const int off = offset_xy(x, y);
            map_elevation_set(off, 0);

            switch (type) {
            case deepWater:
                map_terrain_set(off, TERRAIN_WATER | TERRAIN_DEEPWATER);
                break;
            case water:
                map_terrain_set(off, TERRAIN_WATER);
                break;
            case hills:
                map_terrain_set(off, TERRAIN_ROCK);
                break;
            case trees:
                map_terrain_set(off, TERRAIN_TREE);
                break;
            case shallowMountain:
                map_terrain_set(off, TERRAIN_ROCK);
                map_elevation_set(off, 1);
                break;
            case coast:
            case grass:
            case ground:
            case unknown:
            default:
                map_terrain_set(off, TERRAIN_NONE);
                break;
            }
        }
    }
}

void clear_land_next_to_water() {
    const int mw = map_w();
    const int mh = map_h();
    static const int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    static const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

    for (int y = 0; y < mh; y++) {
        for (int x = 0; x < mw; x++) {
            if (is_water(x, y))
                continue;
            const int off = offset_xy(x, y);
            const int t = map_terrain_get(off);
            if (t & (TERRAIN_ROCK | TERRAIN_TREE))
                continue;
            for (int k = 0; k < 8; k++) {
                const int nx = x + dx[k];
                const int ny = y + dy[k];
                if (in_bounds(nx, ny) && is_water(nx, ny)) {
                    map_terrain_set(off, TERRAIN_NONE);
                    map_elevation_set(off, 0);
                    break;
                }
            }
        }
    }
}

void create_meadows() {
    const int mw = map_w();
    const int mh = map_h();
    const int tiles = mw * mh;
    const int field_size = std::max(20, tiles / 7000);

    for (int k = 0; k < field_size; k++) {
        const int ox = g_rng.to_int(0, mw - 1);
        const int oy = g_rng.to_int(0, mh - 1);
        const int width = field_size;
        const int height = std::max(1, field_size / 2);
        const double angle = g_rng.to_float(0.f, 180.f) * 3.14159265358979323846 / 180.0;
        const double c = std::cos(angle);
        const double s = std::sin(angle);

        for (int y = -height; y <= height; y++) {
            for (int x = -width; x <= width; x++) {
                if (x * x * height * height + y * y * width * width > height * height * width * width)
                    continue;
                const int xt = static_cast<int>(c * x + s * y);
                const int yt = static_cast<int>(-s * x + c * y);
                const int mx = ox + xt;
                const int my = oy + yt;
                if (!in_bounds(mx, my) || is_water(mx, my))
                    continue;
                const int off = offset_xy(mx, my);
                const int t = map_terrain_get(off);
                if (t & (TERRAIN_ROCK | TERRAIN_TREE | TERRAIN_ROAD))
                    continue;
                map_terrain_set(off, TERRAIN_MEADOW);
            }
        }
    }
}

// BFS parents stored as flat grid; returns path from start to goal inclusive.
bool bfs_path(int sx, int sy, int gx, int gy, bool (*passable)(int, int), std::vector<std::pair<int, int>> &out) {
    const int mw = map_w();
    const int mh = map_h();
    const int n = mw * mh;
    std::vector<int> parent(n, -1);
    std::vector<uint8_t> visited(n, 0);
    std::queue<int> q;

    const int start = sy * mw + sx;
    const int goal = gy * mw + gx;
    q.push(start);
    visited[start] = 1;

    static const int dx[4] = {0, 1, 0, -1};
    static const int dy[4] = {-1, 0, 1, 0};

    bool found = false;
    while (!q.empty()) {
        const int cur = q.front();
        q.pop();
        if (cur == goal) {
            found = true;
            break;
        }
        const int cx = cur % mw;
        const int cy = cur / mw;
        for (int d = 0; d < 4; d++) {
            const int nx = cx + dx[d];
            const int ny = cy + dy[d];
            if (!in_bounds(nx, ny))
                continue;
            const int ni = ny * mw + nx;
            if (visited[ni])
                continue;
            // Allow stepping onto the goal even if not otherwise passable (water target).
            if (!(nx == gx && ny == gy) && !passable(nx, ny))
                continue;
            visited[ni] = 1;
            parent[ni] = cur;
            q.push(ni);
        }
    }

    if (!found)
        return false;

    out.clear();
    for (int cur = goal; cur >= 0; cur = parent[cur]) {
        out.emplace_back(cur % mw, cur / mw);
        if (cur == start)
            break;
    }
    std::reverse(out.begin(), out.end());
    return true;
}

void create_rivers() {
    const int mw = map_w();
    const int mh = map_h();
    const int max_rivers = std::max(1, mw / 60);
    int river_count = 0;

    std::vector<std::pair<int, int>> land;
    land.reserve(mw * mh / 2);
    for (int y = 0; y < mh; y++) {
        for (int x = 0; x < mw; x++) {
            if (is_land_for_river(x, y))
                land.emplace_back(x, y);
        }
    }
    if (land.empty())
        return;

    for (int try_count = 0; try_count < 20 && river_count < max_rivers; try_count++) {
        const auto &start = land[g_rng.to_int(0, static_cast<int>(land.size()) - 1)];
        bool got_path = false;
        std::vector<std::pair<int, int>> path;

        for (int range = 1; range < 99 && !got_path; range++) {
            for (int y = start.second - range; y <= start.second + range && !got_path; y++) {
                for (int x = start.first - range; x <= start.first + range && !got_path; x++) {
                    if (!in_bounds(x, y) || !is_water(x, y))
                        continue;
                    // Only ring edge
                    if (std::abs(x - start.first) != range && std::abs(y - start.second) != range)
                        continue;
                    if (bfs_path(start.first, start.second, x, y, is_land_for_river, path))
                        got_path = true;
                }
            }
        }

        if (!got_path)
            continue;

        river_count++;
        for (const auto &p : path) {
            if (is_water(p.first, p.second))
                break;
            map_terrain_set(offset_xy(p.first, p.second), TERRAIN_WATER);
            map_elevation_set(offset_xy(p.first, p.second), 0);
        }
    }
}

void collect_border_land(std::vector<std::pair<int, int>> &out) {
    const int mw = map_w();
    const int mh = map_h();
    out.clear();
    for (int x = 0; x < mw; x++) {
        if (is_walkable_for_road(x, 0))
            out.emplace_back(x, 0);
        if (is_walkable_for_road(x, mh - 1))
            out.emplace_back(x, mh - 1);
    }
    for (int y = 1; y < mh - 1; y++) {
        if (is_walkable_for_road(0, y))
            out.emplace_back(0, y);
        if (is_walkable_for_road(mw - 1, y))
            out.emplace_back(mw - 1, y);
    }
}

void collect_border_water(std::vector<std::pair<int, int>> &out) {
    const int mw = map_w();
    const int mh = map_h();
    out.clear();
    for (int x = 0; x < mw; x++) {
        if (is_water(x, 0))
            out.emplace_back(x, 0);
        if (is_water(x, mh - 1))
            out.emplace_back(x, mh - 1);
    }
    for (int y = 1; y < mh - 1; y++) {
        if (is_water(0, y))
            out.emplace_back(0, y);
        if (is_water(mw - 1, y))
            out.emplace_back(mw - 1, y);
    }
}

bool side_tile(int side, int t, int &x, int &y) {
    const int mw = map_w();
    const int mh = map_h();
    // side: 0=N 1=E 2=S 3=W
    switch (side & 3) {
    case 0:
        x = t % mw;
        y = 0;
        break;
    case 1:
        x = mw - 1;
        y = t % mh;
        break;
    case 2:
        x = t % mw;
        y = mh - 1;
        break;
    default:
        x = 0;
        y = t % mh;
        break;
    }
    return is_walkable_for_road(x, y);
}

bool is_not_border_water(int x, int y) {
    return in_bounds(x, y) && !is_water(x, y);
}

bool is_any_tile(int x, int y) {
    return in_bounds(x, y);
}

// Rocks, hills or a river can cut every walkable route between the map edges. A map always needs a road
// from entry to exit, so join two opposite edge tiles through rock (cleared below) and, if water still
// separates them, through water (turned into land).
bool carve_road_path(std::vector<std::pair<int, int>>& path) {
    const int mw = map_w();
    const int mh = map_h();
    const int sx = 0;
    const int sy = mh / 2;
    const int gx = mw - 1;
    const int gy = mh / 2;
    if (!bfs_path(sx, sy, gx, gy, is_not_border_water, path) && !bfs_path(sx, sy, gx, gy, is_any_tile, path)) {
        return false;
    }

    for (const auto& p : path) {
        const int off = offset_xy(p.first, p.second);
        map_terrain_set(off, TERRAIN_NONE);
        map_elevation_set(off, 0);
    }
    return true;
}

void create_road_and_points() {
    const int mw = map_w();
    const int mh = map_h();
    std::vector<std::pair<int, int>> path;
    bool have_path = false;
    int ex = -1, ey = -1, xx = -1, xy = -1;

    for (int side = 0; side < 2 && !have_path; side++) {
        for (int attempt = 0; attempt < 30 && !have_path; attempt++) {
            int sx, sy, gx, gy;
            if (!side_tile(side, g_rng.to_int(0, std::max(mw, mh) - 1), sx, sy))
                continue;
            if (!side_tile(side + 2, g_rng.to_int(0, std::max(mw, mh) - 1), gx, gy))
                continue;
            if (bfs_path(sx, sy, gx, gy, is_walkable_for_road, path)) {
                have_path = true;
                ex = sx;
                ey = sy;
                xx = gx;
                xy = gy;
            }
        }
        for (int delta = 1; delta <= 3 && !have_path; delta++) {
            for (int attempt = 0; attempt < 20 && !have_path; attempt++) {
                int sx, sy, gx, gy;
                if (!side_tile(side, g_rng.to_int(0, std::max(mw, mh) - 1), sx, sy))
                    continue;
                if (!side_tile(side + delta, g_rng.to_int(0, std::max(mw, mh) - 1), gx, gy))
                    continue;
                if (bfs_path(sx, sy, gx, gy, is_walkable_for_road, path)) {
                    have_path = true;
                    ex = sx;
                    ey = sy;
                    xx = gx;
                    xy = gy;
                }
            }
        }
    }

    if (!have_path) {
        std::vector<std::pair<int, int>> border;
        collect_border_land(border);
        if (border.size() >= 2) {
            for (int try_count = 0; try_count < 20 && !have_path; try_count++) {
                const auto &a = border[g_rng.to_int(0, static_cast<int>(border.size()) / 2)];
                const auto &b = border[g_rng.to_int(static_cast<int>(border.size()) / 2, static_cast<int>(border.size()) - 1)];
                if (bfs_path(a.first, a.second, b.first, b.second, is_walkable_for_road, path)) {
                    have_path = true;
                    ex = a.first;
                    ey = a.second;
                    xx = b.first;
                    xy = b.second;
                }
            }
        }
        if (!have_path && border.size() >= 2) {
            ex = border.front().first;
            ey = border.front().second;
            xx = border.back().first;
            xy = border.back().second;
        }
    }

    if (!have_path) {
        have_path = carve_road_path(path);
    }

    if (have_path) {
        for (const auto &p : path) {
            const int off = offset_xy(p.first, p.second);
            map_terrain_set(off, TERRAIN_ROAD);
            map_elevation_set(off, 0);
        }
        if (!path.empty()) {
            ex = path.front().first;
            ey = path.front().second;
            xx = path.back().first;
            xy = path.back().second;
        }
    }

    if (ex >= 0)
        scenario_editor_set_entry_point(ex, ey);
    if (xx >= 0)
        scenario_editor_set_exit_point(xx, xy);

    std::vector<std::pair<int, int>> water_border;
    collect_border_water(water_border);
    if (water_border.size() >= 2) {
        const auto &a = water_border[g_rng.to_int(0, static_cast<int>(water_border.size()) - 1)];
        const auto &b = water_border[g_rng.to_int(0, static_cast<int>(water_border.size()) - 1)];
        scenario_editor_set_river_entry_point(a.first, a.second);
        scenario_editor_set_river_exit_point(b.first, b.second);
    } else if (water_border.size() == 1) {
        scenario_editor_set_river_entry_point(water_border[0].first, water_border[0].second);
        scenario_editor_set_river_exit_point(water_border[0].first, water_border[0].second);
    }
}

} // namespace

void editor_map_generate(float smooth, float terrain_sq) {
    // From the game's RNG state (not advanced), never the wall clock.
    const random_data_t* rnd = random_data_struct();
    editor_map_generate_seeded(rnd->iv1 ^ (rnd->iv2 * 0x9E3779B1u), smooth, terrain_sq);
}

void editor_map_generate_seeded(uint32_t seed, float smooth, float terrain_sq) {
    const int size = scenario_map_size();
    if (size <= 0)
        return;

    g_rng.seed(seed);

    MidpointDisplacement diamond(n2size_for_map(size), 8, 8, smooth, terrain_sq);
    const std::vector<int> gen = diamond.map();
    paint_heightfield(gen, diamond.width(), diamond.height());
    clear_land_next_to_water();
    create_meadows();
    create_rivers();
    create_road_and_points();
}
