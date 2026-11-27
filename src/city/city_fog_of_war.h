#pragma once

#include "building/building_type.h"
#include "core/archive.h"
#include "core/svector.h"
#include "core/xstring.h"
#include "figure/figure_type.h"
#include "grid/grid.h"
#include "grid/point.h"

#include <array>
#include <cstdint>

class figure;
class building;

enum e_fog_shade : uint8_t {
    fog_visible,
    fog_fogged,
    fog_unexplored,
};

struct event_fog_explored {};

struct fog_building_size_radius {
    int32_t size = 0;
    int32_t radius = 0;
    xstring hint;
};
ANK_CONFIG_STRUCT(fog_building_size_radius, size, radius, hint)

struct fog_building_radius {
    e_building_type building = BUILDING_NONE;
    int32_t radius = 0;
    xstring hint;
};
ANK_CONFIG_STRUCT(fog_building_radius, building, radius, hint)

struct fog_figure_category_radius {
    e_figure_category category = figure_category_inactive;
    int32_t radius = 0;
    xstring hint;
};
ANK_CONFIG_STRUCT(fog_figure_category_radius, category, radius, hint)

struct fog_figure_radius {
    e_figure_type figure = FIGURE_NONE;
    int32_t radius = 0;
    xstring hint;
};
ANK_CONFIG_STRUCT(fog_figure_radius, figure, radius, hint)

struct fog_of_war_config_t {
    int32_t update_every_ticks = 5;
    int32_t soft_edge_tiles = 2;
    uint32_t fogged_mask = 0xff606060;
    uint32_t edge_mask = 0xffa0a0a0;
    int32_t initial_reveal_radius = 12;
    int32_t default_building_radius = 3;
    svector<fog_building_size_radius, 8> building_radius_by_size;
    svector<fog_building_radius, 32> building_radius;
    svector<fog_figure_category_radius, figure_category_max> figure_radius_by_category;
    svector<fog_figure_radius, 32> figure_radius;
};
ANK_CONFIG_STRUCT(fog_of_war_config_t, update_every_ticks, soft_edge_tiles, fogged_mask, edge_mask,
  initial_reveal_radius, default_building_radius, building_radius_by_size, building_radius, figure_radius_by_category,
  figure_radius)

struct city_fog_of_war_t {
    static constexpr int8_t reach_far = -128;
    static constexpr int8_t no_radius = -128;

    std::array<int8_t, GRID_SIZE_TOTAL> reach;
    std::array<int8_t, BUILDING_MAX> radius_of_building;
    std::array<int8_t, FIGURE_MAX> radius_of_figure;
    std::array<int8_t, figure_category_max> radius_of_category;
    fog_of_war_config_t config;
    bool active = false;
    bool in_editor = false;

    bool is_explored(tile2i tile) const;
    bool is_visible(tile2i tile) const;
    e_fog_shade shade(tile2i tile) const;
    int edge(tile2i tile) const;
    bool figure_seen(const figure& f) const;

    void reset();
    void reload_config();
    void on_post_load();
    void update(int tick);
    void recompute(bool explore);
    void set_editor(bool editor);

private:
    bool sync_active();
    bool any_explored() const;
    void initial_reveal();
    void reveal_area(tile2i center, int radius);
    void reveal_rect(tile2i from, tile2i to);
    int building_vision(const building& b) const;
    int figure_vision(const figure& f) const;
};

city_fog_of_war_t& city_fog_of_war();
