#include "city_overlay.h"

#include "game/state.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "core/direction.h"
#include "widget/city/tile_draw.h"
#include "graphics/graphics.h"
#include "figure/figure.h"
#include "graphics/image.h"
#include "city/city_buildings.h"

#include "overlays/city_overlay_education.h"
#include "overlays/city_overlay_entertainment.h"
#include "overlays/city_overlay_health.h"
#include "overlays/city_overlay_other.h"
#include "overlays/city_overlay_religion.h"
#include "overlays/city_overlay_risks.h"
#include "overlays/city_overlay_criminal.h"
#include "overlays/city_overlay_fertility.h"
#include "overlays/city_overlay_desirability.h"
#include "overlays/city_overlay_bazaar_access.h"
#include "overlays/city_overlay_fire.h"
#include "overlays/city_overlay_routing.h"
#include "overlays/city_overlay_physician.h"
#include "overlays/city_overlay_apothecary.h"
#include "overlays/city_overlay_dentist.h"
#include "overlays/city_overlay_mortuary.h"
#include "overlays/city_overlay_health.h"
#include "overlays/city_overlay_juggler.h"
#include "overlays/city_overlay_bandstand.h"
#include "overlays/city_overlay_pavilion.h"
#include "overlays/city_overlay_water.h"
#include "overlays/city_overlay_damage.h"
#include "overlays/city_overlay_labor.h"
#include "overlays/city_overlay_tax_income.h"
#include "overlays/city_overlay_courthouse.h"
#include "game/game.h"
#include "js/js_game.h"

const token_holder<e_overlay, OVERLAY_NONE, OVERLAY_SIZE> e_overlay_tokens;
const token_holder<e_column_type, COLUMN_TYPE_RISK, COLUMN_TYPE_SIZE> e_column_type_tokens;

const city_overlay* g_city_overlay = 0;

ANK_REGISTER_CONFIG_ITERATOR(config_load_city_overlays);
void config_load_city_overlays() {
    g_config_arch.r_array("overlays", [] (archive arch) {
        const e_overlay e_v = arch.r_type<e_overlay>("id");
        city_overlay* overlay = get_city_overlay(e_v);

        if (!overlay) {
            return;
        }

        const char *caption = arch.r_string("caption");
        int tooltip_base = arch.r_int("tooltip_base");

        if (tooltip_base) { overlay->tooltip_base = tooltip_base; }
        if (*caption) { overlay->caption = caption; }

        overlay->buildings = arch.r_array_num<e_building_type>("buildings");
        overlay->walkers = arch.r_array_num<e_figure_type>("walkers");
        overlay->column_type = arch.r_type<e_column_type>("column_type");
        overlay->tooltips = arch.r_array_num("tooltips");
        arch.r_anim("column_anim", overlay->anim);
    });
}


city_overlay* get_city_overlay(e_overlay ov) {
    switch (ov) {
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
    case OVERLAY_BOOTH:
        return city_overlay_for_booth();
    case OVERLAY_BANDSTAND:
        return city_overlay_for_bandstand();
    case OVERLAY_PAVILION:
        return city_overlay_for_pavilion();
    case OVERLAY_SENET_HOUSE:
        return city_overlay_for_senet_house();
    case OVERLAY_EDUCATION:
        return city_overlay_for_education();
    case OVERLAY_SCRIBAL_SCHOOL:
        return city_overlay_for_scribal_school();
    case OVERLAY_LIBRARY:
        return city_overlay_for_library();
    case OVERLAY_ACADEMY:
        return city_overlay_for_academy();
    case OVERLAY_APOTHECARY:
        return city_overlay_for_apothecary();
    case OVERLAY_DENTIST:
        return city_overlay_for_dentist();
    case OVERLAY_PHYSICIAN:
        return city_overlay_for_physician();
    case OVERLAY_MORTUARY:
        return city_overlay_for_mortuary();
    case OVERLAY_RELIGION:
        return city_overlay_for_religion();
    case OVERLAY_RELIGION_OSIRIS:
        return city_overlay_for_religion_osiris();
    case OVERLAY_RELIGION_RA:
        return city_overlay_for_religion_ra();
    case OVERLAY_RELIGION_PTAH:
        return city_overlay_for_religion_ptah();
    case OVERLAY_RELIGION_SETH:
        return city_overlay_for_religion_seth();
    case OVERLAY_RELIGION_BAST:
        return city_overlay_for_religion_bast();
    case OVERLAY_TAX_INCOME:
        return city_overlay_for_tax_income();
    case OVERLAY_FOOD_STOCKS:
        return city_overlay_for_food_stocks();
    case OVERLAY_WATER:
        return city_overlay_for_water();
    case OVERLAY_DESIRABILITY:
        return city_overlay_for_desirability();
    case OVERLAY_FERTILITY:
        return city_overlay_for_fertility();
    case OVERLAY_BAZAAR_ACCESS:
        return city_overlay_for_bazaar_access();
    case OVERLAY_ROUTING:
        return city_overlay_for_routing();
    case OVERLAY_HEALTH:
        return city_overlay_for_health();
    case OVERLAY_LABOR:
        return city_overlay_for_labor();
    case OVERLAY_COUTHOUSE:
        return city_overlay_for_courthouse();
    default:
        return nullptr;
    }
}

const city_overlay* get_city_overlay() {
    return g_city_overlay;
}

bool select_city_overlay() {
    if (!g_city_overlay || g_city_overlay->get_type() != game.current_overlay) {
        g_city_overlay = get_city_overlay(game.current_overlay);
    }

    return g_city_overlay != 0;
}

xstring widget_city_overlay_get_tooltip_text(tooltip_context* c, int grid_offset) {
    if (!g_city_overlay) {
        return {};
    }

    int overlay_type = g_city_overlay->get_type();
    int building_id = map_building_at(grid_offset);
    if (!building_id) {
        return {};
    }

    int overlay_requires_house = (overlay_type != OVERLAY_WATER) && (overlay_type != OVERLAY_FIRE)
                                    && (overlay_type != OVERLAY_DAMAGE) && (overlay_type != OVERLAY_NATIVE)
                                    && (overlay_type != OVERLAY_DESIRABILITY);

    auto b = building_get(building_id);
    auto house = b->dcast_house();
    if (overlay_requires_house && !house) {
        return {};
    }

    xstring tooltip = g_city_overlay->get_tooltip_for_building(c, b);
    if (!tooltip) {
        tooltip = g_city_overlay->get_tooltip_for_grid_offset(c, grid_offset);
    } 

    return tooltip;
}

bool city_overlay::is_drawable_farm_corner(tile2i tile) const {
    if (!map_property_is_draw_tile(tile)) {
        return false;
    }

    int map_orientation = city_view_orientation();
    int xy = map_property_multi_tile_xy(tile);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y2) {
        return true;
    } else if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0) {
        return true;
    } else if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X2Y0) {
        return true;
    } else if (map_orientation == DIR_6_TOP_LEFT && xy == EDGE_X2Y2) {
        return true;
    }

    return false;
}

bool city_overlay::is_drawable_building_corner(tile2i tile, tile2i main, int size) const {
    if (!map_property_is_draw_tile(tile)) {
        return false;
    }

    int map_orientation = city_view_orientation();
    tile2i offset_main;
    int offset = size - 1;
    if (map_orientation == DIR_0_TOP_RIGHT) {
        offset_main = tile.shifted(0, -offset);
    } else if (map_orientation == DIR_2_BOTTOM_RIGHT) {
        /*same*/
    } else if (map_orientation == DIR_4_BOTTOM_LEFT) {
        offset_main = tile.shifted(-offset, 0);
    } else if (map_orientation == DIR_6_TOP_LEFT) {
        offset_main = tile.shifted(-offset, -offset);
    }

    return (offset_main == main);
}

void city_overlay::draw_overlay_column(e_column_color color, vec2i pixel, int height, int column_style, painter &ctx) const {
    if (color == COLUMN_COLOR_NONE) {
        switch (column_style) {
        case COLUMN_TYPE_RISK:
            if (height <= 5) { color = COLUMN_COLOR_PLAIN; }
            else if (height < 7) { color = COLUMN_COLOR_YELLOW; }
            else if (height < 9) { color = COLUMN_COLOR_ORANGE; }
            else { color = COLUMN_COLOR_RED; }
            break;

        case COLUMN_TYPE_POSITIVE:
            color = COLUMN_COLOR_BLUE;
            break;

        case COLUMN_TYPE_WATER_ACCESS:
            color = COLUMN_COLOR_BLUE;
            break;
        }
    }

    int image_id = anim.first_img() + color;

    height = std::min(height, 10);
    int capital_height = image_get(image_id)->height;
    // base
    ImageDraw::img_generic(ctx, image_id + 2, pixel + vec2i{ 9, -8 });
    if (height) {
        // column
        for (int i = 1; i < height; i++) {
            ImageDraw::img_generic(ctx, image_id + 1, pixel + vec2i{ 17, -8 - 10 * i + 13 });
        }
        // capital
        ImageDraw::img_generic(ctx, image_id, pixel + vec2i{ 5, -8 - capital_height - 10 * (height - 1) + 13 });
    }
}

bool city_overlay::is_drawable_farmhouse(tile2i tile, int map_orientation) const {
    if (!map_property_is_draw_tile(tile))
        return false;

    int xy = map_property_multi_tile_xy(tile);
    if (map_orientation == DIR_0_TOP_RIGHT && xy == EDGE_X0Y1)
        return true;

    if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y0)
        return true;

    if (map_orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X1Y0)
        return true;

    if (map_orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X1Y1)
        return true;

    return false;
}

void city_overlay::draw_flattened_footprint_building(const building* b, vec2i pos, int image_offset, color color_mask, painter &ctx) const {
    draw_flattened_footprint_anysize(pos, b->size, b->size, image_offset, color_mask, ctx);
}

void city_overlay::draw_flattened_footprint_anysize(vec2i pos, int size_x, int size_y, int image_offset, color color_mask, painter &ctx) const {
    int image_base = image_id_from_group(GROUP_TERRAIN_OVERLAY_FLAT) + image_offset;

    for (int xx = 0; xx < size_x; xx++) {
        for (int yy = 0; yy < size_y; yy++) {
            vec2i tp = pos + vec2i{(30 * xx) + (30 * yy), (15 * xx) - (15 * yy)};

            // tile shape -- image offset
            // (0 = top corner, 1 = left edge, 2 = right edge, 3 = any other case)
            int shape_offset = 3;
            if (xx == 0) {
                shape_offset = 1;
                if (yy == size_y - 1)
                    shape_offset = 0;
            } else if (yy == size_y - 1) {
                shape_offset = 2;
            }

            ImageDraw::isometric_from_drawtile(ctx, image_base + shape_offset, tp, color_mask);
        }
    }
}

void city_overlay::draw_building_footprint(painter &ctx, vec2i pos, tile2i tile, int image_offset) const {
    int building_id = map_building_at(tile);
    if (!building_id) {
        return;
    }

    building* b = building_get(building_id);
    if (get_city_overlay()->show_building(b)) {
        if (building_is_farm(b->type)) {
            if (is_drawable_farmhouse(tile, city_view_orientation())) {
                ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pos, 0);
            } else if (map_property_is_draw_tile(tile)) {
                ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pos, 0);
            }
        } else {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pos, 0);
        }
    } else {
        bool draw = true;
        if (b->size == 3 && building_is_farm(b->type)) {
            draw = is_drawable_farm_corner(tile);
        } else if (building_type_any_of(*b, BUILDING_STORAGE_YARD, BUILDING_STORAGE_ROOM, 
                                            BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION, BUILDING_FESTIVAL_SQUARE)) {
            building *main = b->main();
            draw = is_drawable_building_corner(tile, main->tile, main->size);
            if (draw) {
                draw_flattened_footprint_anysize(pos, main->size, main->size, image_offset, 0, ctx);
            }
            draw = false;
        }

        if (draw) {
            draw_flattened_footprint_building(b, pos, image_offset, 0, ctx);
        }
    }
}

bool city_overlay::show_figure(const figure *f) const {
    return std::find(walkers.begin(), walkers.end(), f->type) != walkers.end();
}

void city_overlay::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

bool city_overlay::show_building(const building *b) const {
    return std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
}

void city_overlay::draw_building_top(vec2i pixel, tile2i tile, painter &ctx) const {
    building* b = building_at(tile);
    if (get_city_overlay()->get_type() == OVERLAY_PROBLEMS) {
        overlay_problems_prepare_building(b);
    }

    if (get_city_overlay()->show_building(b)) {
        map_render_set(tile, RENDER_TALL_TILE);
        draw_isometric_nonterrain_height(pixel, tile, ctx);
        return;
    }

    int column_height = get_city_overlay()->get_column_height(b);
    e_column_color column_color = get_city_overlay()->get_column_color(b);
    if (column_height == COLUMN_TYPE_NONE) {
        return;
    }

    bool draw = true;
    if (building_is_farm(b->type)) {
        draw = is_drawable_farm_corner(tile);
    }

    if (draw) {
        draw_overlay_column(column_color, pixel, column_height, get_city_overlay()->column_type, ctx);
    }
}