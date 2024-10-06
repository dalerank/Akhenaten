#pragma once

#include "core/xstring.h"
#include "core/string.h"
#include "grid/point.h"
#include "core/vec2i.h"
#include "city/constants.h"
#include "overlays/city_overlay_fwd.h"
#include "core/svector.h"

enum terrain_info_type {
    TERRAIN_INFO_NONE = 0,
    TERRAIN_INFO_TREE = 1,
    TERRAIN_INFO_ROCK = 2,
    TERRAIN_INFO_WATER = 3,
    TERRAIN_INFO_SHRUB = 4,
    TERRAIN_INFO_EARTHQUAKE = 5,
    TERRAIN_INFO_ROAD = 6,
    TERRAIN_INFO_AQUEDUCT = 7,
    TERRAIN_INFO_RUBBLE = 8,
    TERRAIN_INFO_WALL = 9,
    TERRAIN_INFO_EMPTY = 10,
    TERRAIN_INFO_BRIDGE = 11,
    TERRAIN_INFO_GARDEN = 12,
    TERRAIN_INFO_PLAZA = 13,
    TERRAIN_INFO_ENTRY_FLAG = 14,
    TERRAIN_INFO_EXIT_FLAG = 15,
    //
    TERRAIN_INFO_ORE_ROCK = 16,
    TERRAIN_INFO_NORMAL_ROCK = 17,
    TERRAIN_INFO_SPECIAL_ROCK = 18,
    TERRAIN_INFO_FLOODPLAIN = 19,
    TERRAIN_INFO_FLOODPLAIN_SUBMERGED = 20,
    TERRAIN_INFO_MARSHLAND = 21,
    TERRAIN_INFO_DUNES = 22,
    TERRAIN_INFO_BRICK_WALL = 23,
    TERRAIN_INFO_MUD_WALL = 24,
    TERRAIN_INFO_MEADOWS = 25,
    TERRAIN_INFO_CLIFFS = 26,
};

struct common_info_window;
class figure;
class building;

struct object_info {
    vec2i offset;
    int y_offset_submenu;
    vec2i bgsize;
    inline vec2i bgsize_px() const { return bgsize * 16; }
    inline int bgwidth_px() const { return bgsize.x * 16; }
    int grid_offset;
    int height_blocks_submenu;
    int subwnd_wblocks_num;
    int subwnd_hblocks_num;
    int subwnd_y_offset;
    int help_id;
    uint16_t group_id;
    bool can_play_sound;
    int building_id;
    int has_road_access;
    int worker_percentage;
    int has_reservoir_pipes;
    int aqueduct_has_water;
    int formation_id;
    int formation_types;
    int barracks_soldiers_requested;
    int worst_desirability_building_id;
    int warehouse_space_text;
    common_info_window *ui = nullptr;
    terrain_info_type terrain_type;
    e_overlay show_overlay;
    struct {
        e_advisor first = ADVISOR_NONE;
        e_advisor left_a = ADVISOR_NONE;
        e_advisor left_b = ADVISOR_NONE;
    } go_to_advisor;

    int rubble_building_type;
    int storage_show_special_orders;
    struct {
        int draw_debug_path;
        textid phrase;
        xstring phrase_key;
        int selected_index;
        int drawn;
        svector<int, 7> ids;
    } nfigure;

    void reset(tile2i tile);
    void fill_figures_info(tile2i tile);
    figure *figure_get();
    int figure_get_id() const { return nfigure.ids[nfigure.selected_index]; }
    bool figure_phrase_valid() const { return nfigure.phrase.valid(); }
    building *building_get();
};