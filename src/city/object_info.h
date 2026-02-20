#pragma once

#include "core/xstring.h"
#include "core/string.h"
#include "grid/point.h"
#include "core/vec2i.h"
#include "city/constants.h"
#include "overlays/city_overlay_fwd.h"
#include "core/svector.h"
#include "figure/figure.h"
#include "core/tokenum.h"

enum terrain_info_type {
    terrain_info_none = 0,
    terrain_info_tree = 1,
    terrain_info_rock = 2,
    terrain_info_water = 3,
    terrain_info_shrub = 4,
    terrain_info_earthquake = 5,
    terrain_info_road = 6,
    terrain_info_canal = 7,
    terrain_info_rubble = 8,
    terrain_info_wall = 9,
    terrain_info_empty = 10,
    terrain_info_bridge = 11,
    terrain_info_garden = 12,
    terrain_info_plaza = 13,
    terrain_info_entry_flag = 14,
    terrain_info_exit_flag = 15,
    //
    terrain_info_ore_rock = 16,
    terrain_info_normal_rock = 17,
    terrain_info_special_rock = 18,
    terrain_info_floodplain = 19,
    terrain_info_floodplain_submerged = 20,
    terrain_info_marshland = 21,
    terrain_info_dunes = 22,
    terrain_info_brick_wall = 23,
    terrain_info_mud_wall = 24,
    terrain_info_meadows = 25,
    terrain_info_cliffs = 26,

    terrain_info_count
};
using terrain_info_type_tokens_t = token_holder<terrain_info_type, terrain_info_none, terrain_info_count>;
extern const terrain_info_type_tokens_t terrain_info_type_tokens;

struct common_info_window;
class building;

struct object_info {
    vec2i offset;
    vec2i bgsize;
    inline vec2i bgsize_px() const { return bgsize * 16; }
    inline int bgwidth_px() const { return bgsize.x * 16; }
    svector<e_figure_type, 16> forbidden_figure_types;
    int grid_offset = 0;
    int help_id;
    uint16_t group_id;
    bool can_play_sound;
    building_id bid = 0;
    common_info_window *ui = nullptr;
    terrain_info_type terrain_type;

    struct {
        e_advisor first = ADVISOR_NONE;
        e_advisor left_a = ADVISOR_NONE;
        e_advisor left_b = ADVISOR_NONE;
    } go_to_advisor;

    int storage_show_special_orders;
    struct nfigure_t {
        uint8_t selected_index;
        bool drawn;
        svector<figure_id, 7> ids;
        figure *get() const;
    } nfigure;

    void reset(tile2i tile);
    void fill_figures_info(tile2i tile);
    figure *figure_get();
    int figure_get_id() const { return nfigure.ids.empty() ? 0 : nfigure.ids[nfigure.selected_index]; }
    //bool figure_phrase_valid() const { return nfigure.phrase.valid(); }
    building *building_get();

    template<typename T>
    T* building_get() {
        return smart_cast<T>(building_get());
    }

    template<typename T>
    T* figure_get() {
        if (!figure_get_id()) {
            return nullptr;
        }

        return smart_cast<T>(figure_get());
    }
};
ANK_CONFIG_STRUCT(object_info, forbidden_figure_types)