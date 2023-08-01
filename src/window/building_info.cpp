#include "building_info.h"
#include <building/storage.h>

#include "building/barracks.h"
#include "building/building.h"
#include "building/house_evolution.h"
#include "building/model.h"
#include "building/warehouse.h"
#include "city/map.h"
#include "city/resource.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figure/formation_legion.h"
#include "figure/phrase.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "grid/aqueduct.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/property.h"
#include "grid/road_access.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "input/input.h"
#include "window/advisors.h"
#include "window/building/common.h"
#include "window/building/culture.h"
#include "window/building/distribution.h"
#include "window/building/figures.h"
#include "window/building/government.h"
#include "window/building/house.h"
#include "window/building/industry.h"
#include "window/building/military.h"
#include "window/building/terrain.h"
#include "window/building/utility.h"
#include "window/city.h"
#include "window/message_dialog.h"

// #define OFFSET(x,y) (x + GRID_SIZE_PH * y)

static void button_help(int param1, int param2);
static void button_close(int param1, int param2);
static void button_advisor(int advisor, int param2);
static void button_mothball(int mothball, int param2);

static image_button image_buttons_help_close[]
  = {{14, 0, 27, 27, IB_NORMAL, GROUP_CONTEXT_ICONS, 0, button_help, button_none, 0, 0, 1},
     {424, 3, 24, 24, IB_NORMAL, GROUP_CONTEXT_ICONS, 4, button_close, button_none, 0, 0, 1}};

static image_button image_buttons_advisor[] = {
  {350, -38, 28, 28, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 9, button_advisor, button_none, ADVISOR_RATINGS, 0, 1}};

static generic_button generic_button_mothball[] = {{400, 3, 24, 24, button_mothball, button_none, 0, 0}};

static building_info_context context;
static int focus_image_button_id;
static int focus_generic_button_id;

static int get_height_id(void) {
    if (context.type == BUILDING_INFO_TERRAIN) {
        switch (context.terrain_type) {
        case TERRAIN_INFO_AQUEDUCT:
            return 4;
        case TERRAIN_INFO_RUBBLE:
        case TERRAIN_INFO_WALL:
        case TERRAIN_INFO_GARDEN:
            return 1;
        default:
            return 5;
        }
    } else if (context.type == BUILDING_INFO_BUILDING) {
        const building* b = building_get(context.building_id);
        if (building_is_house(b->type) && b->house_population <= 0)
            return 5;

        switch (b->type) {
        case BUILDING_TEMPLE_OSIRIS:
        case BUILDING_TEMPLE_RA:
        case BUILDING_TEMPLE_PTAH:
        case BUILDING_TEMPLE_SETH:
        case BUILDING_TEMPLE_BAST:
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST:
        case BUILDING_ORACLE:
        case BUILDING_SMALL_STATUE:
        case BUILDING_MEDIUM_STATUE:
        case BUILDING_LARGE_STATUE:
        case BUILDING_CONSERVATORY:
        case BUILDING_DANCE_SCHOOL:
        case BUILDING_JUGGLER_SCHOOL:
        case BUILDING_CHARIOT_MAKER:
        case BUILDING_APOTHECARY:
        case BUILDING_MORTUARY:
        case BUILDING_MENU_MONUMENTS:
        case BUILDING_DENTIST:
        case BUILDING_BURNING_RUIN:
        case BUILDING_WATER_LIFT:
        case BUILDING_NATIVE_HUT:
        case BUILDING_NATIVE_MEETING:
        case BUILDING_NATIVE_CROPS:
        case BUILDING_MISSION_POST:
        case BUILDING_POLICE_STATION:
        case BUILDING_ENGINEERS_POST:
        case BUILDING_FIREHOUSE:
        case BUILDING_SCHOOL:
        case BUILDING_MENU_WATER_CROSSINGS:
        case BUILDING_LIBRARY:
        case BUILDING_GATEHOUSE:
        case BUILDING_TOWER:
        case BUILDING_MENU_FORTS:
        case BUILDING_MILITARY_ACADEMY:
        case BUILDING_MARKET:
        case BUILDING_GRANARY:
        case BUILDING_SHIPYARD:
        case BUILDING_DOCK:
        case BUILDING_FISHING_WHARF:
        case BUILDING_PERSONAL_MANSION:
        case BUILDING_FAMILY_MANSION:
        case BUILDING_DYNASTY_MANSION:
        case BUILDING_TAX_COLLECTOR:
        case BUILDING_ROADBLOCK:
        case BUILDING_TAX_COLLECTOR_UPGRADED:
        case BUILDING_BEER_WORKSHOP:
        case BUILDING_LINEN_WORKSHOP:
        case BUILDING_WEAPONS_WORKSHOP:
        case BUILDING_JEWELS_WORKSHOP:
        case BUILDING_POTTERY_WORKSHOP:
            return 1;

        case BUILDING_BOOTH:
        case BUILDING_SENET_HOUSE:
        case BUILDING_PAVILLION:
        case BUILDING_SENATE:
        case BUILDING_SENATE_UPGRADED:
        case BUILDING_MENU_BEAUTIFICATION:
            return 2;

        case BUILDING_RECRUITER:
        case BUILDING_BANDSTAND:
            return 3;

        case BUILDING_WELL:
        case BUILDING_SHRINE_OSIRIS:
        case BUILDING_SHRINE_RA:
        case BUILDING_SHRINE_PTAH:
        case BUILDING_SHRINE_SETH:
        case BUILDING_SHRINE_BAST:
            return 4;

        default:
            return 0;
        }
    }
    return 0;
}
static void get_tooltip(tooltip_context* c) {
    int text_id = 0, group_id = 0;
    if (focus_image_button_id)
        text_id = focus_image_button_id;

    else if (focus_generic_button_id) {
        if (building_get(context.building_id)->state == BUILDING_STATE_VALID) {
            text_id = 8;
            group_id = 54;
        } else {
            text_id = 10;
            group_id = 54;
        }
    } else if (context.type == BUILDING_INFO_LEGION)
        text_id = window_building_get_legion_info_tooltip_text(&context);
    else if (context.type == BUILDING_INFO_BUILDING && context.storage_show_special_orders) {
        switch (building_get(context.building_id)->type) {
        case BUILDING_GRANARY:
            window_building_get_tooltip_granary_orders(&group_id, &text_id);
            break;
        case BUILDING_WAREHOUSE:
            window_building_get_tooltip_warehouse_orders(&group_id, &text_id);
            break;
        }
    }
    if (text_id || group_id) {
        c->type = TOOLTIP_BUTTON;
        c->text_id = text_id;
        if (group_id)
            c->text_group = group_id;
    }
}

static int center_in_city(int element_width_pixels) {
    int x, y, width, height;
    city_view_get_viewport(&x, &y, &width, &height);
    int margin = (width - element_width_pixels) / 2;
    return x + margin;
}

void highlight_waypoints(building* b) // highlight the 4 routing tiles for roams from this building
{
    map_clear_highlights();
    if (b->type == BUILDING_MENU_FORTS || b->house_size) { // building doesn't send roamers
        return;
    }
    int hx, hy, roadx, roady;
    hx = b->tile.x();
    hy = b->tile.y() - 8;
    map_grid_bound(&hx, &hy);
    if (map_closest_road_within_radius(hx, hy, 1, 6, &roadx, &roady))
        map_highlight_set(MAP_OFFSET(roadx, roady));

    hx = b->tile.x() + 8;
    hy = b->tile.y();
    map_grid_bound(&hx, &hy);
    if (map_closest_road_within_radius(hx, hy, 1, 6, &roadx, &roady))
        map_highlight_set(MAP_OFFSET(roadx, roady));

    hx = b->tile.x();
    hy = b->tile.y() + 8;
    map_grid_bound(&hx, &hy);
    if (map_closest_road_within_radius(hx, hy, 1, 6, &roadx, &roady))
        map_highlight_set(MAP_OFFSET(roadx, roady));

    hx = b->tile.x() - 8;
    hy = b->tile.y();
    map_grid_bound(&hx, &hy);
    if (map_closest_road_within_radius(hx, hy, 1, 6, &roadx, &roady))
        map_highlight_set(MAP_OFFSET(roadx, roady));

    window_invalidate();
}

int OFFSET(int x, int y) {
    switch (GAME_ENV) {
    case ENGINE_ENV_PHARAOH:
        return GRID_OFFSET(x, y);
        break;
    }
    return 0;
}

static void init(map_point tile) {
    const int grid_offset = tile.grid_offset();
    context.can_play_sound = 1;
    context.storage_show_special_orders = 0;
    context.can_go_to_advisor = 0;
    context.building_id = map_building_at(grid_offset);
    context.rubble_building_type = map_rubble_building_type(grid_offset);
    context.has_reservoir_pipes = map_terrain_is(grid_offset, TERRAIN_GROUNDWATER);
    context.aqueduct_has_water
      = map_aqueduct_at(grid_offset) && map_image_at(grid_offset) - image_id_from_group(GROUP_BUILDING_AQUEDUCT) < 15;

    city_resource_determine_available();
    context.type = BUILDING_INFO_TERRAIN;
    context.figure.drawn = 0;
    if (!context.building_id && map_sprite_animation_at(grid_offset) > 0) {
        if (map_terrain_is(grid_offset, TERRAIN_WATER))
            context.terrain_type = TERRAIN_INFO_BRIDGE;
        else
            context.terrain_type = TERRAIN_INFO_EMPTY;
    } else if (map_property_is_plaza_or_earthquake(grid_offset)) {
        if (map_terrain_is(grid_offset, TERRAIN_ROAD))
            context.terrain_type = TERRAIN_INFO_PLAZA;

        if (map_terrain_is(grid_offset, TERRAIN_ROCK))
            context.terrain_type = TERRAIN_INFO_EARTHQUAKE;

    } else if (map_terrain_is(grid_offset, TERRAIN_TREE)) {
        context.terrain_type = TERRAIN_INFO_TREE;
    } else if (!context.building_id && map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
            context.terrain_type = TERRAIN_INFO_FLOODPLAIN_SUBMERGED;
        } else {
            context.terrain_type = TERRAIN_INFO_FLOODPLAIN;
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_MARSHLAND)) {
        context.terrain_type = TERRAIN_INFO_MARSHLAND;
    } else if (map_terrain_is(grid_offset, TERRAIN_DUNE)) {
        context.terrain_type = TERRAIN_INFO_DUNES;
    } else if (map_terrain_is(grid_offset, TERRAIN_ROCK)) {
        if (grid_offset == city_map_entry_flag().grid_offset()) {
            context.terrain_type = TERRAIN_INFO_ENTRY_FLAG;
        } else if (grid_offset == city_map_exit_flag().grid_offset()) {
            context.terrain_type = TERRAIN_INFO_EXIT_FLAG;
        } else {
            if (map_terrain_is(grid_offset, TERRAIN_ORE)) {
                context.terrain_type = TERRAIN_INFO_ORE_ROCK;
            } else {
                context.terrain_type = TERRAIN_INFO_ROCK;
            }
        }
    } else if ((map_terrain_get(grid_offset) & (TERRAIN_WATER | TERRAIN_BUILDING)) == TERRAIN_WATER) {
        context.terrain_type = TERRAIN_INFO_WATER;
    } else if (map_terrain_is(grid_offset, TERRAIN_SHRUB)) {
        context.terrain_type = TERRAIN_INFO_SHRUB;
    } else if (map_terrain_is(grid_offset, TERRAIN_GARDEN)) {
        context.terrain_type = TERRAIN_INFO_GARDEN;
    } else if ((map_terrain_get(grid_offset) & (TERRAIN_ROAD | TERRAIN_BUILDING)) == TERRAIN_ROAD) {
        context.terrain_type = TERRAIN_INFO_ROAD;
    } else if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT)) {
        context.terrain_type = TERRAIN_INFO_AQUEDUCT;
    } else if (map_terrain_is(grid_offset, TERRAIN_RUBBLE)) {
        context.terrain_type = TERRAIN_INFO_RUBBLE;
    } else if (map_terrain_is(grid_offset, TERRAIN_WALL)) {
        context.terrain_type = TERRAIN_INFO_WALL;
    } else if (!context.building_id) {
        context.terrain_type = TERRAIN_INFO_EMPTY;
    } else {
        building* b = building_get(context.building_id);
        context.type = BUILDING_INFO_BUILDING;
        context.worker_percentage = calc_percentage(b->num_workers, model_get_building(b->type)->laborers);
        highlight_waypoints(b);

        switch (b->type) {
        case BUILDING_FORT_GROUND:
            context.building_id = b->prev_part_building_id;
            // fallthrough
        case BUILDING_MENU_FORTS:
            context.formation_id = b->formation_id;
            break;
        case BUILDING_WAREHOUSE_SPACE:
        case BUILDING_SENET_HOUSE:
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST:
            b = b->main();
            context.building_id = b->id;
            break;
        case BUILDING_RECRUITER:
            context.barracks_soldiers_requested = formation_legion_recruits_needed();
            context.barracks_soldiers_requested += building_barracks_has_tower_sentry_request();
            break;
        default:
            if (b->house_size) {
                context.worst_desirability_building_id = building_house_determine_worst_desirability_building(b);
                building_house_determine_evolve_text(b, context.worst_desirability_building_id);
            }
            break;
        }
        context.has_road_access = 0;
        switch (b->type) {
            //            case BUILDING_GRANARY:
            //                if (map_has_road_access_granary(b->tile.x(), b->tile.y(), 0))
            //                    context.has_road_access = 1;
            //
            //                break;
            //            case BUILDING_SENET_HOUSE:
            //                if (map_has_road_access_hippodrome_rotation(b->tile.x(), b->tile.y(), 0,
            //                b->subtype.orientation))
            //                    context.has_road_access = 1;

            //            case BUILDING_TEMPLE_COMPLEX_OSIRIS:
            //            case BUILDING_TEMPLE_COMPLEX_RA:
            //            case BUILDING_TEMPLE_COMPLEX_PTAH:
            //            case BUILDING_TEMPLE_COMPLEX_SETH:
            //            case BUILDING_TEMPLE_COMPLEX_BAST:
            //                if (map_has_road_access_hippodrome_rotation(b->tile.x(), b->tile.y(), 0,
            //                b->subtype.orientation))
            //                    context.has_road_access = 1;
            //
            //                break;
            //            case BUILDING_WAREHOUSE:
            //                if (map_has_road_access_rotation(b->subtype.orientation, b->tile.x(), b->tile.y(), 3, 0))
            //                    context.has_road_access = 1;
            //
            //                context.warehouse_space_text = building_warehouse_get_space_info(b);
            //                break;
        default:
            if (b->has_road_access)
                context.has_road_access = 1;
            //                if (map_has_road_access(b->tile.x(), b->tile.y(), b->size, 0))
            //                    context.has_road_access = 1;

            break;
        }
    }
    // figures
    context.figure.selected_index = 0;
    context.figure.count = 0;
    for (int i = 0; i < 7; i++) {
        context.figure.figure_ids[i] = 0;
    }
    const int FIGURE_OFFSETS[] = {OFFSET(0, 0),
                                  OFFSET(0, -1),
                                  OFFSET(0, 1),
                                  OFFSET(1, 0),
                                  OFFSET(-1, 0),
                                  OFFSET(-1, -1),
                                  OFFSET(1, -1),
                                  OFFSET(-1, 1),
                                  OFFSET(1, 1)};
    for (int i = 0; i < 9 && context.figure.count < 7; i++) {
        int figure_id = map_figure_at(grid_offset + FIGURE_OFFSETS[i]);
        while (figure_id > 0 && context.figure.count < 7) {
            figure* f = figure_get(figure_id);
            if (f->state != FIGURE_STATE_DEAD && f->action_state != FIGURE_ACTION_149_CORPSE) {
                switch (f->type) {
                case FIGURE_NONE:
                case FIGURE_EXPLOSION:
                case FIGURE_MAP_FLAG:
                case FIGURE_FLOTSAM:
                case FIGURE_ARROW:
                case FIGURE_JAVELIN:
                case FIGURE_BOLT:
                case FIGURE_BALLISTA:
                case FIGURE_CREATURE:
                case FIGURE_FISH_GULLS:
                case FIGURE_SPEAR:
                case FIGURE_HIPPODROME_HORSES:
                    break;
                default:
                    context.figure.figure_ids[context.figure.count++] = figure_id;
                    //                        f->igure_phrase_determine();
                    break;
                }
            }
            if (figure_id != f->next_figure)
                figure_id = f->next_figure;
            else
                figure_id = 0;
        }
    }
    // check for legion figures
    for (int i = 0; i < 7; i++) {
        int figure_id = context.figure.figure_ids[i];
        if (figure_id <= 0)
            continue;

        figure* f = figure_get(figure_id);
        if (f->type == FIGURE_FORT_STANDARD || f->is_legion()) {
            context.type = BUILDING_INFO_LEGION;
            context.formation_id = f->formation_id;
            const formation* m = formation_get(context.formation_id);
            if (m->figure_type != FIGURE_FORT_LEGIONARY)
                context.formation_types = 5;
            else if (m->has_military_training)
                context.formation_types = 4;
            else {
                context.formation_types = 3;
            }
            break;
        }
    }
    // dialog size
    context.width_blocks = 29;
    switch (get_height_id()) {
    case 1:
        context.height_blocks = 16;
        break;
    case 2:
        context.height_blocks = 18;
        break;
    case 3:
        context.height_blocks = 19;
        break;
    case 4:
        context.height_blocks = 14;
        break;
    case 5:
        context.height_blocks = 23;
        break;
    default:
        context.height_blocks = 22;
        break;
    }
    // dialog placement
    int s_width = screen_width();
    int s_height = screen_height();
    context.x_offset = center_in_city(16 * context.width_blocks);
    if (s_width >= 1024 && s_height >= 768) {
        context.x_offset = mouse_get()->x;
        context.y_offset = mouse_get()->y;
        window_building_set_possible_position(
          &context.x_offset, &context.y_offset, context.width_blocks, context.height_blocks);
    } else if (s_height >= 600 && mouse_get()->y <= (s_height - 24) / 2 + 24)
        context.y_offset = s_height - 16 * context.height_blocks - MARGIN_POSITION;
    else
        context.y_offset = MIN_Y_POSITION;
}

static void draw_mothball_button(int x, int y, int focused) {
    uint8_t working_text[] = {'x', 0};
    button_border_draw(x, y, 20, 20, focused ? 1 : 0);
    building* b = building_get(context.building_id);
    if (b->state == BUILDING_STATE_VALID)
        text_draw_centered(working_text, x + 1, y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
}
static void draw_background(void) {
    window_city_draw_panels();
    window_city_draw();
    if (context.type == BUILDING_INFO_NONE)
        window_building_draw_no_people(&context);
    else if (context.type == BUILDING_INFO_TERRAIN)
        window_building_draw_terrain(&context);
    else if (context.type == BUILDING_INFO_BUILDING) {
        if (building_is_house(building_get(context.building_id)->type))
            window_building_draw_house(&context);
        else
            switch (building_get(context.building_id)->type) {
            case BUILDING_BARLEY_FARM:
                window_building_draw_wheat_farm(&context);
                break;
            case BUILDING_FLAX_FARM:
                window_building_draw_vegetable_farm(&context);
                break;
            case BUILDING_GRAIN_FARM:
                window_building_draw_fruit_farm(&context);
                break;
            case BUILDING_LETTUCE_FARM:
                window_building_draw_olive_farm(&context);
                break;
            case BUILDING_POMEGRANATES_FARM:
                window_building_draw_vines_farm(&context);
                break;
            case BUILDING_CHICKPEAS_FARM:
                window_building_draw_pig_farm(&context);
                break;
            case BUILDING_FIGS_FARM:
                window_building_draw_fig_farm(&context);
                break;
            case BUILDING_HENNA_FARM:
                window_building_draw_henna_farm(&context);
                break;
            case BUILDING_HUNTING_LODGE:
                window_building_draw_hunting_lodge(&context);
                break;
            case BUILDING_STONE_QUARRY:
                window_building_draw_marble_quarry(&context);
                break;
            case BUILDING_LIMESTONE_QUARRY:
                window_building_draw_iron_mine(&context);
                break;
            case BUILDING_WOOD_CUTTERS:
                window_building_draw_timber_yard(&context);
                break;
            case BUILDING_CLAY_PIT:
                window_building_draw_clay_pit(&context);
                break;
            case BUILDING_BEER_WORKSHOP:
                window_building_draw_wine_workshop(&context);
                break;
            case BUILDING_LINEN_WORKSHOP:
                window_building_draw_oil_workshop(&context);
                break;
            case BUILDING_WEAPONS_WORKSHOP:
                window_building_draw_weapons_workshop(&context);
                break;
            case BUILDING_JEWELS_WORKSHOP:
                window_building_draw_furniture_workshop(&context);
                break;
            case BUILDING_POTTERY_WORKSHOP:
                window_building_draw_pottery_workshop(&context);
                break;
            case BUILDING_MARKET:
                if (context.storage_show_special_orders)
                    window_building_draw_market_orders(&context);
                else
                    window_building_draw_market(&context);
                break;
            case BUILDING_GRANARY:
                if (context.storage_show_special_orders)
                    window_building_draw_granary_orders(&context);
                else
                    window_building_draw_granary(&context);
                break;
            case BUILDING_WAREHOUSE:
                if (context.storage_show_special_orders)
                    window_building_draw_warehouse_orders(&context);
                else
                    window_building_draw_warehouse(&context);
                break;
            case BUILDING_BANDSTAND:
                window_building_draw_amphitheater(&context);
                break;
            case BUILDING_BOOTH:
                window_building_draw_theater(&context);
                break;
            case BUILDING_SENET_HOUSE:
                window_building_draw_hippodrome(&context);
                break;
            case BUILDING_PAVILLION:
                window_building_draw_colosseum(&context);
                break;
            case BUILDING_CONSERVATORY:
                window_building_draw_gladiator_school(&context);
                break;
            case BUILDING_DANCE_SCHOOL:
                window_building_draw_lion_house(&context);
                break;
            case BUILDING_JUGGLER_SCHOOL:
                window_building_draw_actor_colony(&context);
                break;
            case BUILDING_CHARIOT_MAKER:
                window_building_draw_chariot_maker(&context);
                break;
            case BUILDING_APOTHECARY:
                window_building_draw_clinic(&context);
                break;
            case BUILDING_MORTUARY:
                window_building_draw_hospital(&context);
                break;
            case BUILDING_PHYSICIAN:
            case BUILDING_MENU_MONUMENTS:
                window_building_draw_bathhouse(&context);
                break;
            case BUILDING_DENTIST:
                window_building_draw_barber(&context);
                break;
            case BUILDING_SCHOOL:
                window_building_draw_school(&context);
                break;
            case BUILDING_MENU_WATER_CROSSINGS:
                window_building_draw_academy(&context);
                break;
            case BUILDING_LIBRARY:
                window_building_draw_library(&context);
                break;
            case BUILDING_TEMPLE_OSIRIS:
            case BUILDING_TEMPLE_COMPLEX_OSIRIS:
                window_building_draw_temple_ceres(&context);
                break;
            case BUILDING_TEMPLE_RA:
            case BUILDING_TEMPLE_COMPLEX_RA:
                window_building_draw_temple_neptune(&context);
                break;
            case BUILDING_TEMPLE_PTAH:
            case BUILDING_TEMPLE_COMPLEX_PTAH:
                window_building_draw_temple_mercury(&context);
                break;
            case BUILDING_TEMPLE_SETH:
            case BUILDING_TEMPLE_COMPLEX_SETH:
                window_building_draw_temple_mars(&context);
                break;
            case BUILDING_TEMPLE_BAST:
            case BUILDING_TEMPLE_COMPLEX_BAST:
                window_building_draw_temple_venus(&context);
                break;
            case BUILDING_SHRINE_OSIRIS:
                window_building_draw_shrine_osiris(&context);
                break;
            case BUILDING_SHRINE_RA:
                window_building_draw_shrine_ra(&context);
                break;
            case BUILDING_SHRINE_PTAH:
                window_building_draw_shrine_ptah(&context);
                break;
            case BUILDING_SHRINE_SETH:
                window_building_draw_shrine_seth(&context);
                break;
            case BUILDING_SHRINE_BAST:
                window_building_draw_shrine_bast(&context);
                break;

            case BUILDING_ORACLE:
                window_building_draw_oracle(&context);
                break;
            case BUILDING_PERSONAL_MANSION:
            case BUILDING_FAMILY_MANSION:
            case BUILDING_DYNASTY_MANSION:
                window_building_draw_governor_home(&context);
                break;
            case BUILDING_TAX_COLLECTOR:
            case BUILDING_TAX_COLLECTOR_UPGRADED:
                window_building_draw_forum(&context);
                break;
            case BUILDING_COURTHOUSE:
                window_building_draw_courthouse(&context);
                break;
            case BUILDING_SENATE:
            case BUILDING_SENATE_UPGRADED:
            case BUILDING_VILLAGE_PALACE:
            case BUILDING_TOWN_PALACE:
            case BUILDING_CITY_PALACE:
                window_building_draw_senate(&context);
                break;
            case BUILDING_ENGINEERS_POST:
                window_building_draw_engineers_post(&context);
                break;
            case BUILDING_SHIPYARD:
                window_building_draw_shipyard(&context);
                break;
            case BUILDING_DOCK:
                if (context.storage_show_special_orders)
                    window_building_draw_dock_orders(&context);
                else
                    window_building_draw_dock(&context);
                break;
            case BUILDING_FISHING_WHARF:
                window_building_draw_wharf(&context);
                break;
            case BUILDING_WATER_LIFT:
                window_building_draw_water_lift(&context);
                break;
            case BUILDING_MENU_BEAUTIFICATION:
                window_building_draw_fountain(&context);
                break;
            case BUILDING_WATER_SUPPLY:
                window_building_draw_water_supply(&context);
                break;
            case BUILDING_WELL:
                window_building_draw_well(&context);
                break;
            case BUILDING_SMALL_STATUE:
            case BUILDING_MEDIUM_STATUE:
            case BUILDING_LARGE_STATUE:
                window_building_draw_statue(&context);
                break;
            case BUILDING_TRIUMPHAL_ARCH:
                window_building_draw_triumphal_arch(&context);
                break;
            case BUILDING_POLICE_STATION:
                window_building_draw_prefect(&context);
                break;
            case BUILDING_ROADBLOCK:
                if (context.storage_show_special_orders)
                    window_building_draw_roadblock_orders(&context);
                else
                    window_building_draw_roadblock(&context);
                break;
            case BUILDING_GATEHOUSE:
                window_building_draw_gatehouse(&context);
                break;
            case BUILDING_TOWER:
                window_building_draw_tower(&context);
                break;
            case BUILDING_MILITARY_ACADEMY:
                window_building_draw_military_academy(&context);
                break;
            case BUILDING_RECRUITER:
                window_building_draw_barracks(&context);
                break;
            case BUILDING_MENU_FORTS:
                window_building_draw_fort(&context);
                break;
            case BUILDING_BURNING_RUIN:
                window_building_draw_burning_ruin(&context);
                break;
            case BUILDING_NATIVE_HUT:
                window_building_draw_native_hut(&context);
                break;
            case BUILDING_NATIVE_MEETING:
                window_building_draw_native_meeting(&context);
                break;
            case BUILDING_NATIVE_CROPS:
                window_building_draw_native_crops(&context);
                break;
            case BUILDING_MISSION_POST:
                window_building_draw_mission_post(&context);
                break;
            case BUILDING_FIREHOUSE:
                window_building_draw_firehouse(&context);
                break;
            case BUILDING_WORK_CAMP:
                window_building_draw_work_camp(&context);
                break;
            case BUILDING_FESTIVAL_SQUARE:
                window_building_draw_festival_square(&context);
                break;
            }

    } else if (context.type == BUILDING_INFO_LEGION)
        window_building_draw_legion_info(&context);
}
static void draw_foreground(void) {
    // building-specific buttons
    if (context.type == BUILDING_INFO_BUILDING) {
        switch (building_get(context.building_id)->type) {
        case BUILDING_GRANARY:
            if (context.storage_show_special_orders)
                window_building_draw_granary_orders_foreground(&context);
            else
                window_building_draw_granary_foreground(&context);
            break;
        case BUILDING_WAREHOUSE:
            if (context.storage_show_special_orders)
                window_building_draw_warehouse_orders_foreground(&context);
            else
                window_building_draw_warehouse_foreground(&context);
            break;
        case BUILDING_MARKET:
            if (context.storage_show_special_orders)
                window_building_draw_market_orders_foreground(&context);
            else
                window_building_draw_market_foreground(&context);
            break;
        case BUILDING_ROADBLOCK:
            if (context.storage_show_special_orders)
                window_building_draw_roadblock_orders_foreground(&context);
            else
                window_building_draw_roadblock_foreground(&context);
            break;
        case BUILDING_DOCK:
            if (context.storage_show_special_orders)
                window_building_draw_dock_orders_foreground(&context);
            else
                window_building_draw_dock_foreground(&context);
            break;
        case BUILDING_RECRUITER:
            window_building_draw_barracks_foreground(&context);
            break;
        }
    } else if (context.type == BUILDING_INFO_LEGION)
        window_building_draw_legion_info_foreground(&context);

    // general buttons
    if (context.storage_show_special_orders)
        image_buttons_draw(context.x_offset,
                           context.y_offset_submenu + 16 * context.height_blocks_submenu - 40,
                           image_buttons_help_close,
                           2);
    else
        image_buttons_draw(
          context.x_offset, context.y_offset + 16 * context.height_blocks - 40, image_buttons_help_close, 2);
    if (context.can_go_to_advisor)
        image_buttons_draw(
          context.x_offset, context.y_offset + 16 * context.height_blocks - 40, image_buttons_advisor, 1);
    if (!context.storage_show_special_orders) {
        int workers_needed = model_get_building(building_get(context.building_id)->type)->laborers;
        if (workers_needed)
            draw_mothball_button(
              context.x_offset + 400, context.y_offset + 3 + 16 * context.height_blocks - 40, focus_generic_button_id);
    }
}

static int handle_specific_building_info_mouse(const mouse* m) {
    // building-specific buttons
    if (context.type == BUILDING_INFO_NONE)
        return 0;

    if (context.type == BUILDING_INFO_LEGION)
        return window_building_handle_mouse_legion_info(m, &context);
    else if (context.figure.drawn)
        return window_building_handle_mouse_figure_list(m, &context);
    else if (context.type == BUILDING_INFO_BUILDING) {
        switch (building_get(context.building_id)->type) {
        case BUILDING_MARKET:
            if (context.storage_show_special_orders)
                window_building_handle_mouse_market_orders(m, &context);
            else
                window_building_handle_mouse_market(m, &context);
            break;
        case BUILDING_ROADBLOCK:
            if (context.storage_show_special_orders)
                return window_building_handle_mouse_roadblock_orders(m, &context);
            else
                return window_building_handle_mouse_roadblock(m, &context);
            break;
        case BUILDING_DOCK:
            if (context.storage_show_special_orders)
                return window_building_handle_mouse_dock_orders(m, &context);
            else
                return window_building_handle_mouse_dock(m, &context);
            break;
        case BUILDING_RECRUITER:
            return window_building_handle_mouse_barracks(m, &context);
        case BUILDING_GRANARY:
            if (context.storage_show_special_orders)
                return window_building_handle_mouse_granary_orders(m, &context);
            else
                return window_building_handle_mouse_granary(m, &context);
            break;
        case BUILDING_WAREHOUSE:
            if (context.storage_show_special_orders)
                return window_building_handle_mouse_warehouse_orders(m, &context);
            else
                window_building_handle_mouse_warehouse(m, &context);
            break;
        }
    }
    return 0;
}
static void handle_input(const mouse* m, const hotkeys* h) {
    bool button_id = 0;
    // general buttons
    if (context.storage_show_special_orders) {
        //        int y_offset = window_building_get_vertical_offset(&context, 28 + 5);
        button_id |= image_buttons_handle_mouse(m,
                                                context.x_offset,
                                                context.y_offset_submenu + 16 * context.height_blocks_submenu - 40,
                                                image_buttons_help_close,
                                                2,
                                                &focus_image_button_id);
    } else {
        button_id |= image_buttons_handle_mouse(m,
                                                context.x_offset,
                                                context.y_offset + 16 * context.height_blocks - 40,
                                                image_buttons_help_close,
                                                2,
                                                &focus_image_button_id);
        button_id = generic_buttons_handle_mouse(m,
                                                 context.x_offset,
                                                 context.y_offset + 16 * context.height_blocks - 40,
                                                 generic_button_mothball,
                                                 1,
                                                 &focus_generic_button_id);
    }
    if (context.can_go_to_advisor) {
        button_id |= image_buttons_handle_mouse(
          m, context.x_offset, context.y_offset + 16 * context.height_blocks - 40, image_buttons_advisor, 1, 0);
    }

    if (!button_id)
        button_id |= !!handle_specific_building_info_mouse(m);

    if (!button_id && input_go_back_requested(m, h)) {
        if (context.storage_show_special_orders)
            storage_settings_backup_check();
        else
            window_city_show();
    }
}

static void button_help(int param1, int param2) {
    if (context.help_id > 0) {
        window_message_dialog_show(context.help_id, -1, window_city_draw_all);
    } else {
        window_message_dialog_show(MESSAGE_DIALOG_HELP, -1, window_city_draw_all);
    }
    window_invalidate();
}
static void button_close(int param1, int param2) {
    if (context.storage_show_special_orders) {
        context.storage_show_special_orders = 0;
        storage_settings_backup_reset();
        window_invalidate();
    } else {
        window_city_show();
    }
}
static void button_advisor(int advisor, int param2) {
    window_advisors_show_advisor(advisor);
}
static void button_mothball(int mothball, int param2) {
    building* b = building_get(context.building_id);
    int workers_needed = model_get_building(b->type)->laborers;
    if (workers_needed) {
        building_mothball_toggle(b);
        window_invalidate();
    }
}

void window_building_info_show(const map_point &point) {
    window_type window = {WINDOW_BUILDING_INFO, draw_background, draw_foreground, handle_input, get_tooltip};

    init(point);
    window_show(&window);
}
int window_building_info_get_int(void) {
    if (context.type == BUILDING_INFO_BUILDING)
        return building_get(context.building_id)->type;

    return BUILDING_NONE;
}
void window_building_info_show_storage_orders(void) {
    context.storage_show_special_orders = 1;
    window_invalidate();
}
