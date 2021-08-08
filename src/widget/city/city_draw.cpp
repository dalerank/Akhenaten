#include <figure/formation_legion.h>
#include "city_draw.h"

#include "building/animation.h"
#include "building/construction.h"
#include "building/industry.h"
#include "city/view.h"
#include "core/config.h"
#include "core/log.h"
#include "game/resource.h"
#include "game/state.h"
#include "graphics/image.h"
#include "map/bridge.h"
#include "map/building.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/image.h"
#include "map/property.h"
#include "map/random.h"
#include "map/terrain.h"
#include "widget/city/bridges.h"
#include "widget/city/building_ghost.h"
#include "widget/city_overlay.h"
#include "widget/city_overlay_education.h"
#include "widget/city_overlay_entertainment.h"
#include "widget/city_overlay_health.h"
#include "widget/city_overlay_other.h"
#include "widget/city_overlay_risks.h"
#include "widget/city/tile_draw.h"

static const city_overlay *overlay = 0;

static const int ADJACENT_OFFSETS_C3[2][4][7] = {
        {
                {OFFSET_C3(-1, 0), OFFSET_C3(-1, -1), OFFSET_C3(-1, -2), OFFSET_C3(0, -2),  OFFSET_C3(1, -2)},
                {OFFSET_C3(0, -1), OFFSET_C3(1, -1), OFFSET_C3(2, -1), OFFSET_C3(2, 0),  OFFSET_C3(2, 1)},
                {OFFSET_C3(1, 0), OFFSET_C3(1, 1), OFFSET_C3(1, 2), OFFSET_C3(0, 2), OFFSET_C3(-1, 2)},
                {OFFSET_C3(0, 1), OFFSET_C3(-1, 1), OFFSET_C3(-2, 1), OFFSET_C3(-2, 0), OFFSET_C3(-2, -1)}
        },
        {
                {OFFSET_C3(-1, 0), OFFSET_C3(-1, -1), OFFSET_C3(-1, -2), OFFSET_C3(-1, -3), OFFSET_C3(0, -3), OFFSET_C3(
                                                                                                                      1,
                                                                                                                      -3), OFFSET_C3(
                                                                                                                                   2,
                                                                                                                                   -3)},
                {OFFSET_C3(0, -1), OFFSET_C3(1, -1), OFFSET_C3(2, -1), OFFSET_C3(3, -1), OFFSET_C3(3, 0), OFFSET_C3(3,
                                                                                                                    1), OFFSET_C3(
                                                                                                                                3,
                                                                                                                                2)},
                {OFFSET_C3(1, 0), OFFSET_C3(1, 1), OFFSET_C3(1, 2), OFFSET_C3(1, 3), OFFSET_C3(0, 3), OFFSET_C3(-1,
                                                                                                                3), OFFSET_C3(
                                                                                                                            -2,
                                                                                                                            3)},
                {OFFSET_C3(0, 1), OFFSET_C3(-1, 1), OFFSET_C3(-2, 1), OFFSET_C3(-3, 1), OFFSET_C3(-3, 0), OFFSET_C3(-3,
                                                                                                                    -1), OFFSET_C3(
                                                                                                                                 -3,
                                                                                                                                 -2)}
        }
};
static const int ADJACENT_OFFSETS_PH[2][4][7] = {
        {
                {OFFSET_PH(-1, 0), OFFSET_PH(-1, -1), OFFSET_PH(-1, -2), OFFSET_PH(0, -2),  OFFSET_PH(1, -2)},
                {OFFSET_PH(0, -1), OFFSET_PH(1, -1), OFFSET_PH(2, -1), OFFSET_PH(2, 0),  OFFSET_PH(2, 1)},
                {OFFSET_PH(1, 0), OFFSET_PH(1, 1), OFFSET_PH(1, 2), OFFSET_PH(0, 2), OFFSET_PH(-1, 2)},
                {OFFSET_PH(0, 1), OFFSET_PH(-1, 1), OFFSET_PH(-2, 1), OFFSET_PH(-2, 0), OFFSET_PH(-2, -1)}
        },
        {
                {OFFSET_PH(-1, 0), OFFSET_PH(-1, -1), OFFSET_PH(-1, -2), OFFSET_PH(-1, -3), OFFSET_PH(0, -3), OFFSET_PH(
                                                                                                                      1,
                                                                                                                      -3), OFFSET_PH(
                                                                                                                                   2,
                                                                                                                                   -3)},
                {OFFSET_PH(0, -1), OFFSET_PH(1, -1), OFFSET_PH(2, -1), OFFSET_PH(3, -1), OFFSET_PH(3, 0), OFFSET_PH(3,
                                                                                                                    1), OFFSET_PH(
                                                                                                                                3,
                                                                                                                                2)},
                {OFFSET_PH(1, 0), OFFSET_PH(1, 1), OFFSET_PH(1, 2), OFFSET_PH(1, 3), OFFSET_PH(0, 3), OFFSET_PH(-1,
                                                                                                                3), OFFSET_PH(
                                                                                                                            -2,
                                                                                                                            3)},
                {OFFSET_PH(0, 1), OFFSET_PH(-1, 1), OFFSET_PH(-2, 1), OFFSET_PH(-3, 1), OFFSET_PH(-3, 0), OFFSET_PH(-3,
                                                                                                                    -1), OFFSET_PH(
                                                                                                                                 -3,
                                                                                                                                 -2)}
        }
};

static const city_overlay *set_city_overlay(void) {
    switch (game_state_overlay()) {
        case OVERLAY_FIRE:
            return city_overlay_for_fire();
        case OVERLAY_CRIME:
            return city_overlay_for_crime();
        case OVERLAY_DAMAGE:
            return city_overlay_for_damage();
        case OVERLAY_PROBLEMS:
            return city_overlay_for_problems();
        case OVERLAY_NATIVE:
            return city_overlay_for_native();
        case OVERLAY_ENTERTAINMENT:
            return city_overlay_for_entertainment();
        case OVERLAY_THEATER:
            return city_overlay_for_theater();
        case OVERLAY_AMPHITHEATER:
            return city_overlay_for_amphitheater();
        case OVERLAY_COLOSSEUM:
            return city_overlay_for_colosseum();
        case OVERLAY_HIPPODROME:
            return city_overlay_for_hippodrome();
        case OVERLAY_EDUCATION:
            return city_overlay_for_education();
        case OVERLAY_SCHOOL:
            return city_overlay_for_school();
        case OVERLAY_LIBRARY:
            return city_overlay_for_library();
        case OVERLAY_ACADEMY:
            return city_overlay_for_academy();
        case OVERLAY_BARBER:
            return city_overlay_for_barber();
        case OVERLAY_BATHHOUSE:
            return city_overlay_for_bathhouse();
        case OVERLAY_CLINIC:
            return city_overlay_for_clinic();
        case OVERLAY_HOSPITAL:
            return city_overlay_for_hospital();
        case OVERLAY_RELIGION:
            return city_overlay_for_religion();
        case OVERLAY_TAX_INCOME:
            return city_overlay_for_tax_income();
        case OVERLAY_FOOD_STOCKS:
            return city_overlay_for_food_stocks();
        case OVERLAY_WATER:
            return city_overlay_for_water();
        case OVERLAY_DESIRABILITY:
            return city_overlay_for_desirability();
        default:
            return 0;
    }
}
const city_overlay *get_city_overlay(void) {
    return overlay;
}
static int select_city_overlay(void) {
    if (!overlay || overlay->type != game_state_overlay())
        overlay = set_city_overlay();

    return overlay != 0;
}
void city_with_overlay_update(void) {
    select_city_overlay();
}

/////////

void city_without_overlay_draw(int selected_figure_id, pixel_coordinate *figure_coord, const map_tile *tile) {
    int highlighted_formation = 0;
    if (config_get(CONFIG_UI_HIGHLIGHT_LEGIONS)) {
        highlighted_formation = formation_legion_at_grid_offset(tile->grid_offset);
        if (highlighted_formation > 0 && formation_get(highlighted_formation)->in_distant_battle)
            highlighted_formation = 0;
    }
    init_draw_context(selected_figure_id, figure_coord, highlighted_formation);

//    city_view_foreach_map_tile(draw_outside_map);
//    int x;
//    int y;
//    city_view_get_camera_scrollable_viewspace_clip(&x, &y);
//    graphics_set_clip_rectangle(x - 30, y, map_grid_width() * 30 - 60, map_grid_height() * 15 - 30);

    // do this for EVERY tile (not just valid ones)
    // to recalculate the pixel lookup offsets
    city_view_foreach_map_tile(draw_footprint);

    if (!city_building_ghost_mark_deleting(tile)) {
        city_view_foreach_map_tile(draw_footprint);
        city_view_foreach_valid_map_tile(
                draw_top,
                draw_ornaments,
                draw_figures);
        if (!selected_figure_id)
            city_building_ghost_draw(tile);
    } else {
        city_view_foreach_valid_map_tile(
                deletion_draw_top,
                deletion_draw_figures_animations,
                draw_elevated_figures);
    }

    // finally, draw these on top of everything else
    city_view_foreach_valid_map_tile(
            draw_debug,
            draw_debug_figures);
}
void city_with_overlay_draw(const map_tile *tile) {
    if (!select_city_overlay())
        return;

    // do this for EVERY tile (not just valid ones)
    // to recalculate the pixel lookup offsets
    city_view_foreach_map_tile(draw_footprint_overlay);

    if (!city_building_ghost_mark_deleting(tile)) {
        city_view_foreach_valid_map_tile(
                draw_top_overlay,
                draw_ornaments_overlay,
                draw_figures_overlay);
        city_building_ghost_draw(tile);
        city_view_foreach_map_tile(draw_elevated_figures);
    } else {
        city_view_foreach_valid_map_tile(
                deletion_draw_top,
                deletion_draw_figures_animations,
                draw_elevated_figures_overlay);
    }
}
int city_with_overlay_get_tooltip_text(tooltip_context *c, int grid_offset) {
    int overlay_type = overlay->type;
    int building_id = map_building_at(grid_offset);
    if (overlay->get_tooltip_for_building && !building_id)
        return 0;

    int overlay_requires_house =
            overlay_type != OVERLAY_WATER && overlay_type != OVERLAY_FIRE &&
            overlay_type != OVERLAY_DAMAGE && overlay_type != OVERLAY_NATIVE && overlay_type != OVERLAY_DESIRABILITY;
    building *b = building_get(building_id);
    if (overlay_requires_house && !b->house_size)
        return 0;

    if (overlay->get_tooltip_for_building)
        return overlay->get_tooltip_for_building(c, b);
    else if (overlay->get_tooltip_for_grid_offset)
        return overlay->get_tooltip_for_grid_offset(c, grid_offset);

    return 0;
}
