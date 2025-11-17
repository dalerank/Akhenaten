#include "city_overlay_criminal.h"

#include "building/building_house.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "grid/crime.h"
#include "grid/random.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/state.h"
#include "game/game_config.h"
#include "graphics/elements/ui.h"
#include "city/city_buildings.h"

static int terrain_on_crime_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD
        | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE;
}

static int has_deleted_building(int grid_offset) {
    if (!game_features::gameui_visual_feedback_on_delete)
        return 0;

    building* b = building_at(grid_offset);
    b = b->main();
    return b->id && (b->is_deleted || map_property_is_deleted(b->tile));
}

static int get_crime_image_offset(int crime_level) {
    if (crime_level < -10)
        return 0;
    else if (crime_level < -5)
        return 1;
    else if (crime_level < 0)
        return 2;
    else if (crime_level == 0)
        return 3;
    else if (crime_level < 5)
        return 4;
    else if (crime_level < 10)
        return 5;
    else if (crime_level < 15)
        return 6;
    else if (crime_level < 20)
        return 7;
    else if (crime_level < 25)
        return 8;
    else
        return 9;
}

city_overlay_crime g_city_overlay_crime;

bool city_overlay_crime::show_figure(const figure *f) const {
    return false;
}

int city_overlay_crime::get_column_height(const building* b) const {
    return COLUMN_TYPE_NONE;
}

void city_overlay_crime::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    ; // nothing
}

xstring city_overlay_crime::get_tooltip_for_building(tooltip_context* c, const building* b) {
    return {};
}

xstring city_overlay_crime::get_tooltip(tooltip_context *c, tile2i tile) const {
    int crime = g_crime.get(tile);
    if (crime < 0) {
        return ui::str(66, 58); // Low crime
    } else if (crime == 0) {
        return ui::str(66, 59); // Normal crime
    } else {
        return ui::str(66, 60); // High crime
    }
}

bool city_overlay_crime::draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();
    int crime_level = g_crime.get(grid_offset);

    color color_mask = map_property_is_deleted(grid_offset) ? COLOR_MASK_RED : 0;
    if (map_terrain_is(grid_offset, terrain_on_crime_overlay()) && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        // display normal tile
        if (map_property_is_draw_tile(grid_offset)) {
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = map_image_at(grid_offset);
            command.pixel = pixel;
            command.mask = color_mask;
        }

    } else if (map_terrain_is(grid_offset, TERRAIN_CANAL | TERRAIN_WALL)) {
        // display empty land/groundwater

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
        command.pixel = pixel;
        command.mask = color_mask;

    } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || crime_level != 0) {
        if (has_deleted_building(grid_offset)) {
            color_mask = COLOR_MASK_RED;
        } 

        int offset = get_crime_image_offset(crime_level);
        int img_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY);

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
        command.image_id = img_id + offset;
        command.pixel = pixel;
        command.mask = color_mask;
    } else {
        int img_id = map_image_at(grid_offset);

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
        command.image_id = img_id;
        command.pixel = pixel;
        command.mask = color_mask;

    }

    return true;
}

bool city_overlay_crime::show_building(const building *b) const {
    return false;
}

city_overlay_criminal g_city_overlay_criminal;

bool city_overlay_criminal::show_figure(const figure *f) const {
    return false;
}

int city_overlay_criminal::get_column_height(const building* b) const {
    auto house = ((building*)b)->dcast_house();
    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    if (house->house_population() > 0) {
        int crime = house->runtime_data().criminal_active;
        return crime / 10;
    }
    return COLUMN_TYPE_NONE;
}

void city_overlay_criminal::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    ; // nothing
}

xstring city_overlay_criminal::get_tooltip_for_building(tooltip_context* c, const building* b) {
    auto house = ((building *)b)->dcast_house();
    if (!house || house->house_population() <= 0) {
        return ui::str(66, 63);
    }

    auto &housed = house->runtime_data();
    if (housed.criminal_active >= 80)
        return ui::str(66, 63);
    else if (housed.criminal_active >= 60)
        return ui::str(66, 62);
    else if (housed.criminal_active >= 40)
        return ui::str(66, 61);
    else if (housed.criminal_active >= 30)
        return ui::str(66, 60);
    else if (housed.criminal_active >= 20)
        return ui::str(66, 59);
    else {
        return ui::str(66, 58);
    }
}

bool city_overlay_criminal::show_building(const building *b) const {
    return false;
}
