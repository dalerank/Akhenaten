#include <widget/sidebar/city.h>
#include <figure/formation_herd.h>
#include <SDL_log.h>
#include "construction.h"

#include "building/construction_clear.h"
#include "building/construction_routed.h"
#include "building/construction_warning.h"
#include "building/count.h"
#include "building/model.h"
#include "building/properties.h"
#include "building/storage.h"
#include "building/rotation.h"
#include "building/warehouse.h"
#include "building/dock.h"
#include "building/menu.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/resource.h"
#include "city/view.h"
#include "city/warning.h"
#include "core/calc.h"
#include "core/config.h"
#include "core/image.h"
#include "core/random.h"
#include "figure/formation.h"
#include "figure/formation_legion.h"
#include "game/undo.h"
#include "graphics/window.h"
#include "map/aqueduct.h"
#include "map/bridge.h"
#include "map/building.h"
#include "map/building_tiles.h"
#include "map/grid.h"
#include "map/image.h"
#include "map/orientation.h"
#include "map/point.h"
#include "map/property.h"
#include "map/routing.h"
#include "map/routing_terrain.h"
#include "map/terrain.h"
#include "map/tiles.h"
#include "map/water.h"

struct reservoir_info {
    int cost;
    int place_reservoir_at_start;
    int place_reservoir_at_end;
};

enum {
    PLACE_RESERVOIR_BLOCKED = -1,
    PLACE_RESERVOIR_NO = 0,
    PLACE_RESERVOIR_YES = 1,
    PLACE_RESERVOIR_EXISTS = 2
};

static struct {
    int type;
    int size;
    int sub_type;
    bool in_progress;
    map_tile start;
    map_tile end;
    int cost;
    struct {
        bool meadow;
        bool rock;
        bool ore;
        bool tree;
        bool water;
        bool groundwater;
        bool wall;
    } required_terrain;
    int draw_as_constructing;
    int start_offset_x_view;
    int start_offset_y_view;
} data;

static int last_items_cleared;

static const int FORT_X_OFFSET[4][4] = {{3,  4,  4,  3},
                                        {-1, 0,  0,  -1},
                                        {-4, -3, -3, 4},
                                        {0,  1,  1,  0}};
static const int FORT_Y_OFFSET[4][4] = {{-1, -1, 0,  0},
                                        {-4, -4, -3, -3},
                                        {0,  0,  1,  1},
                                        {3,  3,  4,  4}};

const int CROPS_OFFSETS[2] = {5, 6};

static void add_fort(int type, building *fort) {
    fort->prev_part_building_id = 0;
    map_building_tiles_add(fort->id, fort->x, fort->y, fort->size, image_id_from_group(GROUP_BUILDING_FORT),
                           TERRAIN_BUILDING);
    if (type == BUILDING_FORT_LEGIONARIES)
        fort->subtype.fort_figure_type = FIGURE_FORT_LEGIONARY;
    else if (type == BUILDING_FORT_JAVELIN)
        fort->subtype.fort_figure_type = FIGURE_FORT_JAVELIN;
    else if (type == BUILDING_FORT_MOUNTED)
        fort->subtype.fort_figure_type = FIGURE_FORT_MOUNTED;


    // create parade ground
    const int offsets_x[] = {3, -1, -4, 0};
    const int offsets_y[] = {-1, -4, 0, 3};
    building *ground = building_create(BUILDING_FORT_GROUND, fort->x + offsets_x[building_rotation_get_rotation()],
                                       fort->y + offsets_y[building_rotation_get_rotation()]);
    game_undo_add_building(ground);
    ground->prev_part_building_id = fort->id;
    fort->next_part_building_id = ground->id;
    ground->next_part_building_id = 0;
    map_building_tiles_add(ground->id, fort->x + offsets_x[building_rotation_get_rotation()],
                           fort->y + offsets_y[building_rotation_get_rotation()], 4,
                           image_id_from_group(GROUP_BUILDING_FORT) + 1, TERRAIN_BUILDING);

    fort->formation_id = formation_legion_create_for_fort(fort);
    ground->formation_id = fort->formation_id;
}
static void add_hippodrome(building *b) {
    int image1 = image_id_from_group(GROUP_BUILDING_HIPPODROME_1);
    int image2 = image_id_from_group(GROUP_BUILDING_HIPPODROME_2);
    city_buildings_add_hippodrome();

    building_rotation_force_two_orientations();
    int orientation = building_rotation_get_building_orientation(building_rotation_get_rotation());
    building *part1 = b;

    part1->prev_part_building_id = 0;
    int image_id;
    switch (orientation) {
        case DIR_0_TOP_RIGHT:
            image_id = image2;
            break;
        case DIR_2_BOTTOM_RIGHT:
            image_id = image1 + 4;
            break;
        case DIR_4_BOTTOM_LEFT:
            image_id = image2 + 4;
            break;
        case DIR_6_TOP_LEFT:
            image_id = image1;
            break;
        default:
            return;
    }
    map_building_tiles_add(b->id, b->x, b->y, b->size, image_id, TERRAIN_BUILDING);
    int x_offset, y_offset;
    building_rotation_get_offset_with_rotation(5, building_rotation_get_rotation(), &x_offset, &y_offset);
    building *part2 = building_create(BUILDING_HIPPODROME, b->x + x_offset, b->y + y_offset);
    game_undo_add_building(part2);

    part2->prev_part_building_id = part1->id;
    part1->next_part_building_id = part2->id;
    part2->next_part_building_id = 0;
    switch (orientation) {
        case DIR_0_TOP_RIGHT:
        case DIR_4_BOTTOM_LEFT:
            image_id = image2 + 2;
            break;
        case DIR_2_BOTTOM_RIGHT:
        case DIR_6_TOP_LEFT:
            image_id = image1 + 2;
            break;
    }
    map_building_tiles_add(part2->id, b->x + x_offset, b->y + y_offset, b->size, image_id, TERRAIN_BUILDING);

    building_rotation_get_offset_with_rotation(10, building_rotation_get_rotation(), &x_offset, &y_offset);
    building *part3 = building_create(BUILDING_HIPPODROME, b->x + x_offset, b->y + y_offset);
    game_undo_add_building(part3);

    part3->prev_part_building_id = part2->id;
    part2->next_part_building_id = part3->id;
    part3->next_part_building_id = 0;
    switch (orientation) {
        case DIR_0_TOP_RIGHT:
            image_id = image2 + 4;
            break;
        case DIR_2_BOTTOM_RIGHT:
            image_id = image1;
            break;
        case DIR_4_BOTTOM_LEFT:
            image_id = image2;
            break;
        case DIR_6_TOP_LEFT:
            image_id = image1 + 4;
            break;
    }
    map_building_tiles_add(part3->id, b->x + x_offset, b->y + y_offset, b->size, image_id, TERRAIN_BUILDING);
}

static building *add_temple_complex_element(int x, int y, int size, int image_id, building *prev) {
    building *b = building_create(prev->type, x, y);
    game_undo_add_building(b);

    b->size = size;
    b->grid_offset = map_grid_offset(b->x, b->y);
    b->prev_part_building_id = prev->id;
    prev->next_part_building_id = b->id;
    map_building_tiles_add(b->id, b->x, b->y, b->size, image_id, TERRAIN_BUILDING);

    return b;
}

// TODO: Fix the orientation
static void add_temple_complex(building *b) {
    auto properties = building_properties_for_type(b->type);
    int temple_complex_image_id = properties->image_group;
    building_rotation_force_two_orientations();
    int orientation = building_rotation_get_building_orientation(building_rotation_get_rotation());

    int empty = 0;
    int main1 = image_id_from_group(temple_complex_image_id);
    int main2 = main1 + 6;
    int main3 = main1 + 12;
    int tile0 = main1 + 22;
    int tile1 = main1 + 23;
    int tile2 = main1 + 24;
    int tile3 = main1 + 25;
    int tile4 = main1 + 26;
    int tile5 = main1 + 28;
    int tile6 = main1 + 30;
    int tile7 = main1 + 31;
    int tile8 = main1 + 34;
    int tile9 = main1 + 35;

    int TEMPLE_COMPLEX_SCHEME[7][13] = {{tile5, tile5, tile1, tile5, tile5, tile1, tile5, tile5, tile0, tile2, tile3, tile2, tile3},
                                          {  tile0, tile0, tile1, tile0, tile0, tile1, tile0, tile0, tile0, tile0, tile6, tile6, tile6},
                                          {  empty, empty, empty, empty, empty, empty, empty, empty, empty, tile0, tile7, tile7, tile7},
                                          {  empty, empty, empty, empty, empty, empty, empty, empty, empty, tile1, tile1, tile1, tile1},
                                          {  main1, empty, empty, main2, empty, empty, main3, empty, empty, tile0, tile8, tile8, tile8},
                                          {  tile0, tile0, tile1, tile0, tile0, tile1, tile0, tile0, tile0, tile0, tile9, tile9, tile9},
                                          {  tile4, tile4, tile1, tile4, tile4, tile1, tile4, tile4, tile0, tile2, tile3, tile2, tile3}
    };

    if (orientation == 0) {
        b->size = 1;
        b->prev_part_building_id = 0;
        building *prev = b;

        // Start draw from the back
        for (int i = 6; i >= 0; --i) {
            for (int j = 0; j < 13; j++) {
                int current_tile = TEMPLE_COMPLEX_SCHEME[i][j];

                int current_size = 1;
                if (current_tile == main1 || current_tile == main2 || current_tile == main3) {
                    current_size = 3;
                }

                if (current_tile > 0) {
                    prev = add_temple_complex_element(b->x + j, b->y - i, current_size, current_tile, prev);
                }
            }
        }
        prev->next_part_building_id = 0;
    }
}

static void latch_on_venue(int type, building *main, int dx, int dy, int orientation, bool main_venue = false) {
    int x = main->x + dx;
    int y = main->y + dy;
    int grid_offset = map_grid_offset(x, y);
    building *this_venue = main;
    if (main_venue) { // this is the main venue building!!
        if (type != main->type)
            return; // hmmm, this shouldn't happen
        main->grid_offset = grid_offset;
//        main->x += dx;
//        main->y += dy;
    } else if (type == BUILDING_GARDENS) { // add gardens
        map_terrain_add(grid_offset, TERRAIN_GARDEN);
    } else { // extra venue
        this_venue = building_create(type, x, y);
        building *parent = main; // link venue to last one in the chain
        while (parent->next_part_building_id)
            parent = building_get(parent->next_part_building_id);
        parent->next_part_building_id = this_venue->id;
        this_venue->prev_part_building_id = parent->id;

        map_building_set(grid_offset, this_venue->id);
        if (type == BUILDING_PAVILLION) {
            map_building_set(grid_offset + map_grid_delta(1, 0), this_venue->id);
            map_building_set(grid_offset + map_grid_delta(1, 1), this_venue->id);
            map_building_set(grid_offset + map_grid_delta(0, 1), this_venue->id);
        }
    }

    // set map graphics accordingly
    switch (type) {
        case BUILDING_GARDENS:
            map_tiles_update_all_gardens();
            break;
        case BUILDING_BOOTH:
            map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_BOOTH));
            break;
        case BUILDING_BANDSTAND:
            map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_BANDSTAND) + orientation);
            if (orientation == 1)
                latch_on_venue(BUILDING_BANDSTAND, main, dx, dy + 1, 0);
            else if (orientation == 2)
                latch_on_venue(BUILDING_BANDSTAND, main, dx + 1, dy, 3);
            map_add_bandstand_tiles(this_venue);
            break;
        case BUILDING_PAVILLION:
            map_building_tiles_add(this_venue->id, x, y, 2, image_id_from_group(GROUP_BUILDING_PAVILLION), TERRAIN_BUILDING);
            break;
    }
}
static void add_entertainment_venue(building *b) {
    b->data.entertainment.booth_corner_grid_offset = b->grid_offset;
    int size = 0;
    switch (b->type) {
        case BUILDING_BOOTH:
            size = 2; break;
        case BUILDING_BANDSTAND:
            size = 3; break;
        case BUILDING_PAVILLION:
            size = 4; break;
        case BUILDING_FESTIVAL_SQUARE:
            size = 5; break;
    }
    if (!map_grid_is_inside(b->x, b->y, size))
        return;
    int orientation = -1;
    int image_id = 0;
    switch (b->type) {
        case BUILDING_BOOTH:
            map_orientation_for_venue(b->x, b->y, 0, &orientation);
            image_id = image_id_from_group(GROUP_BOOTH_SQUARE);
            break;
        case BUILDING_BANDSTAND:
            map_orientation_for_venue(b->x, b->y, 1, &orientation);
            image_id = image_id_from_group(GROUP_BANDSTAND_SQUARE);
            break;
        case BUILDING_PAVILLION:
            map_orientation_for_venue(b->x, b->y, 2, &orientation);
            image_id = image_id_from_group(GROUP_PAVILLION_SQUARE);
            break;
        case BUILDING_FESTIVAL_SQUARE:
            map_orientation_for_venue(b->x, b->y, 3, &orientation);
            image_id = image_id_from_group(GROUP_FESTIVAL_SQUARE);
            break;
    }

    // add underlying plaza first
    map_add_venue_plaza_tiles(b->id, size, b->x, b->y, image_id, false);

    // add additional building parts, update graphics accordingly
    switch (b->type) {
        case BUILDING_BOOTH:
            switch (orientation / 2) {
                case 0:
                    latch_on_venue(BUILDING_BOOTH, b, 0, 0, 0, true);
                    break;
                case 1:
                    latch_on_venue(BUILDING_BOOTH, b, 1, 0, 0, true);
                    break;
                case 2:
                    latch_on_venue(BUILDING_BOOTH, b, 1, 1, 0, true);
                    break;
                case 3:
                    latch_on_venue(BUILDING_BOOTH, b, 0, 1, 0, true);
                    break;
            }
            break;
        case BUILDING_BANDSTAND:
            switch (orientation / 2) {
                case 0:
                    latch_on_venue(BUILDING_GARDENS, b, 2, 1, 0);
                    latch_on_venue(BUILDING_BANDSTAND, b, 0, 0, 1, true);
                    latch_on_venue(BUILDING_BOOTH, b, 2, 0, 0);
                    break;
                case 1:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 2, 0);
                    latch_on_venue(BUILDING_BANDSTAND, b, 1, 0, 2, true);
                    latch_on_venue(BUILDING_BOOTH, b, 2, 2, 0);
                    break;
                case 2:
                    latch_on_venue(BUILDING_GARDENS, b, 2, 1, 0);
                    latch_on_venue(BUILDING_BANDSTAND, b, 0, 1, 1, true);
                    latch_on_venue(BUILDING_BOOTH, b, 2, 2, 0);
                    break;
                case 3:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 2, 0);
                    latch_on_venue(BUILDING_BANDSTAND, b, 0, 0, 2, true);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 2, 0);
                    break;
            }
            break;
        case BUILDING_PAVILLION:
            // todo
            switch (orientation) {
                case 0:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 2, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 3, 2, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 0, 0, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 3, 0, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 2, 0);
                    break;
                case 1:
                    latch_on_venue(BUILDING_GARDENS, b, 2, 2, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 3, 2, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 2, 0, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 0, 0, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 2, 0);
                    break;
                case 2:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 3, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 2, 3, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 1, 0, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 3, 0, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 3, 3, 0);
                    break;
                case 3:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 0, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 2, 0, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 1, 2, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 3, 2, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 3, 0, 0);
                    break;
                case 4:
                    latch_on_venue(BUILDING_GARDENS, b, 2, 3, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 3, 3, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 2, 1, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 0, 1, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 3, 0);
                    break;
                case 5:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 3, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 3, 3, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 0, 1, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 3, 1, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 3, 0);
                    break;
                case 6:
                    // in the original game, this orientation is not allowed for some reason?
                    latch_on_venue(BUILDING_GARDENS, b, 1, 0, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 2, 0, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 0, 2, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 2, 2, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 0, 0);
                    break;
                case 7:
                    latch_on_venue(BUILDING_GARDENS, b, 1, 3, 0);
                    latch_on_venue(BUILDING_GARDENS, b, 2, 3, 0);
                    latch_on_venue(BUILDING_PAVILLION, b, 0, 0, 0, true);
                    latch_on_venue(BUILDING_BANDSTAND, b, 2, 0, 1);
                    latch_on_venue(BUILDING_BOOTH, b, 0, 3, 0);
                    break;
            }
            break;
    }
}
static building *add_warehouse_space(int x, int y, building *prev) {
    building *b = building_create(BUILDING_WAREHOUSE_SPACE, x, y);
    game_undo_add_building(b);
    b->prev_part_building_id = prev->id;
    prev->next_part_building_id = b->id;
    map_building_tiles_add(b->id, x, y, 1,
                           image_id_from_group(GROUP_BUILDING_WAREHOUSE_STORAGE_EMPTY), TERRAIN_BUILDING);
    return b;
}
static void add_warehouse(building *b) {
    int x_offset[9] = {0, 0, 1, 1, 0, 2, 1, 2, 2};
    int y_offset[9] = {0, 1, 0, 1, 2, 0, 2, 1, 2};
    int corner = building_rotation_get_corner(2 * building_rotation_get_rotation());

    b->storage_id = building_storage_create(BUILDING_WAREHOUSE);
    if (config_get(CONFIG_GP_CH_WAREHOUSES_DONT_ACCEPT))
        building_storage_accept_none(b->storage_id);

    b->prev_part_building_id = 0;
    map_building_tiles_add(b->id, b->x + x_offset[corner], b->y + y_offset[corner], 1,
                           image_id_from_group(GROUP_BUILDING_WAREHOUSE), TERRAIN_BUILDING);

    building *prev = b;
    for (int i = 0; i < 9; i++) {
        if (i == corner) {
            continue;
        }
        prev = add_warehouse_space(b->x + x_offset[i], b->y + y_offset[i], prev);
    }
    // adjust BUILDING_WAREHOUSE
    b->x = b->x + x_offset[corner];
    b->y = b->y + y_offset[corner];
    b->grid_offset = map_grid_offset(b->x, b->y);
    game_undo_adjust_building(b);

    prev->next_part_building_id = 0;
}
static void add_building_tiles_image(building *b, int image_id) {
    map_building_tiles_add(b->id, b->x, b->y, b->size, image_id, TERRAIN_BUILDING);
}
static void add_to_map(int type, building *b, int size, int orientation, int waterside_orientation_abs, int waterside_orientation_rel) {
    switch (type) {
        // houses
        case BUILDING_HOUSE_LARGE_TENT:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_TENT) + 2);
            break;
        case BUILDING_HOUSE_SMALL_SHACK:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_SHACK));
            break;
        case BUILDING_HOUSE_LARGE_SHACK:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_SHACK) + 2);
            break;
        case BUILDING_HOUSE_SMALL_HOVEL:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_HOVEL));
            break;
        case BUILDING_HOUSE_LARGE_HOVEL:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_HOVEL) + 2);
            break;
        case BUILDING_HOUSE_SMALL_CASA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_CASA));
            break;
        case BUILDING_HOUSE_LARGE_CASA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_CASA) + 2);
            break;
        case BUILDING_HOUSE_SMALL_INSULA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_INSULA_1));
            break;
        case BUILDING_HOUSE_MEDIUM_INSULA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_INSULA_1) + 2);
            break;
        case BUILDING_HOUSE_LARGE_INSULA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_INSULA_2));
            break;
        case BUILDING_HOUSE_GRAND_INSULA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_INSULA_2) + 2);
            break;
        case BUILDING_HOUSE_SMALL_VILLA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_VILLA_1));
            break;
        case BUILDING_HOUSE_MEDIUM_VILLA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_VILLA_1) + 2);
            break;
        case BUILDING_HOUSE_LARGE_VILLA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_VILLA_2));
            break;
        case BUILDING_HOUSE_GRAND_VILLA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_VILLA_2) + 1);
            break;
        case BUILDING_HOUSE_SMALL_PALACE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_PALACE_1));
            break;
        case BUILDING_HOUSE_MEDIUM_PALACE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_PALACE_1) + 1);
            break;
        case BUILDING_HOUSE_LARGE_PALACE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_PALACE_2));
            break;
        case BUILDING_HOUSE_LUXURY_PALACE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOUSE_PALACE_2) + 1);
            break;
            // entertainment
        case BUILDING_THEATER: // GROUP_BUILDING_BOOTH
            if (GAME_ENV == ENGINE_ENV_C3)
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_THEATER));
            else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                add_entertainment_venue(b);
            break;
        case BUILDING_AMPHITHEATER: // BUILDING_BANDSTAND
            if (GAME_ENV == ENGINE_ENV_C3)
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_AMPHITHEATER));
            else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                add_entertainment_venue(b);
            break;
        case BUILDING_COLOSSEUM: // BUILDING_PAVILLION
            if (GAME_ENV == ENGINE_ENV_C3)
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_COLOSSEUM));
            else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                add_entertainment_venue(b);
            break;
        case BUILDING_FESTIVAL_SQUARE:
            add_entertainment_venue(b);
            city_buildings_add_festival_square(b);
            break;
        case BUILDING_GLADIATOR_SCHOOL:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_GLADIATOR_SCHOOL));
            break;
        case BUILDING_LION_HOUSE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_LION_HOUSE));
            break;
        case BUILDING_ACTOR_COLONY:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_ACTOR_COLONY));
            break;
        case BUILDING_CHARIOT_MAKER:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_CHARIOT_MAKER));
            break;
            // statues
        case BUILDING_SMALL_STATUE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_STATUE));
            break;
        case BUILDING_MEDIUM_STATUE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_STATUE) + 1);
            break;
        case BUILDING_LARGE_STATUE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_STATUE) + 2);
            break;
            // health
        case BUILDING_DOCTOR:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_DOCTOR));
            break;
        case BUILDING_HOSPITAL:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_HOSPITAL));
            break;
        case BUILDING_BATHHOUSE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_BATHHOUSE_NO_WATER));
            break;
        case BUILDING_BARBER:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_BARBER));
            break;
            // education
        case BUILDING_SCHOOL:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_SCHOOL));
            break;
        case BUILDING_ACADEMY:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_ACADEMY));
            break;
        case BUILDING_LIBRARY:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_LIBRARY));
            break;
            // security
        case BUILDING_PREFECTURE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_PREFECTURE));
            break;
            // farms
        case BUILDING_WHEAT_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, 0, 0);
            break;
        case BUILDING_VEGETABLE_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV], 0);
            break;
        case BUILDING_FRUIT_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV] * 2, 0);
            break;
        case BUILDING_OLIVE_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV] * 3, 0);
            break;
        case BUILDING_VINES_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV] * 4, 0);
            break;
        case BUILDING_PIG_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV] * 5, 0);
            break;
        case BUILDING_FIGS_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV] * 6, 0);
            break;
        case BUILDING_HENNA_FARM:
            map_building_tiles_add_farm(b->id, b->x, b->y, CROPS_OFFSETS[GAME_ENV] * 7, 0);
            break;
            // industry
        case BUILDING_MARBLE_QUARRY:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_MARBLE_QUARRY));
            break;
        case BUILDING_IRON_MINE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_IRON_MINE));
            break;
        case BUILDING_TIMBER_YARD:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TIMBER_YARD));
            break;
        case BUILDING_CLAY_PIT:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_CLAY_PIT));
            break;
            // workshops
        case BUILDING_WINE_WORKSHOP:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_WINE_WORKSHOP));
            break;
        case BUILDING_OIL_WORKSHOP:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_OIL_WORKSHOP));
            break;
        case BUILDING_WEAPONS_WORKSHOP:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_WEAPONS_WORKSHOP));
            break;
        case BUILDING_FURNITURE_WORKSHOP:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_FURNITURE_WORKSHOP));
            break;
        case BUILDING_POTTERY_WORKSHOP:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_POTTERY_WORKSHOP));
            break;
            // distribution
        case BUILDING_GRANARY:
            b->storage_id = building_storage_create(BUILDING_GRANARY);
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_GRANARY));
            map_tiles_update_area_roads(b->x, b->y, 5);
            break;
        case BUILDING_MARKET:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_MARKET));
            break;
            // government
        case BUILDING_GOVERNORS_HOUSE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_GOVERNORS_HOUSE));
            city_buildings_add_mansion(b);
            break;
        case BUILDING_GOVERNORS_VILLA:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_GOVERNORS_VILLA));
            city_buildings_add_mansion(b);
            break;
        case BUILDING_GOVERNORS_PALACE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_GOVERNORS_PALACE));
            city_buildings_add_mansion(b);
            break;
        case BUILDING_MISSION_POST:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_MISSION_POST));
            break;
        case BUILDING_ENGINEERS_POST:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_ENGINEERS_POST));
            break;
        case BUILDING_FORUM:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_FORUM));
            break;
            // water
        case BUILDING_FOUNTAIN:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_FOUNTAIN_1));
            break;
        case BUILDING_WELL:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_WELL));
            break;
            // military
        case BUILDING_MILITARY_ACADEMY:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_MILITARY_ACADEMY));
            break;
            // religion
        case BUILDING_SMALL_TEMPLE_CERES:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_CERES));
            break;
        case BUILDING_SMALL_TEMPLE_NEPTUNE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_NEPTUNE));
            break;
        case BUILDING_SMALL_TEMPLE_MERCURY:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_MERCURY));
            break;
        case BUILDING_SMALL_TEMPLE_MARS:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_MARS));
            break;
        case BUILDING_SMALL_TEMPLE_VENUS:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_VENUS));
            break;
        case BUILDING_LARGE_TEMPLE_CERES:
            if (GAME_ENV == ENGINE_ENV_C3) {
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_CERES) + 1);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                add_temple_complex(b);
            }
            break;
        case BUILDING_LARGE_TEMPLE_NEPTUNE:
            if (GAME_ENV == ENGINE_ENV_C3) {
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_NEPTUNE) + 1);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                add_temple_complex(b);
            }
            break;
        case BUILDING_LARGE_TEMPLE_MERCURY:
            if (GAME_ENV == ENGINE_ENV_C3) {
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_MERCURY) + 1);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                add_temple_complex(b);
            }
            break;
        case BUILDING_LARGE_TEMPLE_MARS:
            if (GAME_ENV == ENGINE_ENV_C3) {
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_MARS) + 1);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                add_temple_complex(b);
            }
            break;
        case BUILDING_LARGE_TEMPLE_VENUS:
            if (GAME_ENV == ENGINE_ENV_C3) {
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TEMPLE_VENUS) + 1);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                add_temple_complex(b);
            }
            break;
        case BUILDING_ORACLE:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_ORACLE));
            break;
        case BUILDING_ROADBLOCK:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_ROADBLOCK));
            map_terrain_add_roadblock_road(b->x, b->y, orientation);
            map_tiles_update_area_roads(b->x, b->y, 5);
            map_tiles_update_all_plazas();
            break;
            // ships
        case BUILDING_SHIPYARD:
            b->data.industry.orientation = waterside_orientation_abs;
            map_water_add_building(b->id, b->x, b->y, 2,
                                   image_id_from_group(GROUP_BUILDING_SHIPYARD) + waterside_orientation_rel);
            break;
        case BUILDING_WHARF:
            b->data.industry.orientation = waterside_orientation_abs;
            map_water_add_building(b->id, b->x, b->y, 2,
                                   image_id_from_group(GROUP_BUILDING_WHARF) + waterside_orientation_rel);
            break;
        case BUILDING_DOCK:
            city_buildings_add_dock();
            b->data.dock.orientation = waterside_orientation_abs;
            {
                int image_id;
                switch (waterside_orientation_rel) {
                    case 0:
                        image_id = image_id_from_group(GROUP_BUILDING_DOCK_1);
                        break;
                    case 1:
                        image_id = image_id_from_group(GROUP_BUILDING_DOCK_2);
                        break;
                    case 2:
                        image_id = image_id_from_group(GROUP_BUILDING_DOCK_3);
                        break;
                    default:
                        image_id = image_id_from_group(GROUP_BUILDING_DOCK_4);
                        break;
                }
                map_water_add_building(b->id, b->x, b->y, size, image_id);
            }
            break;
            // defense
        case BUILDING_TOWER:
            map_terrain_remove_with_radius(b->x, b->y, 2, 0, TERRAIN_WALL);
            map_building_tiles_add(b->id, b->x, b->y, size, image_id_from_group(GROUP_BUILDING_TOWER),
                                   TERRAIN_BUILDING | TERRAIN_GATEHOUSE);
            map_tiles_update_area_walls(b->x, b->y, 5);
            break;
        case BUILDING_GATEHOUSE_PH:
        case BUILDING_GATEHOUSE:
            map_building_tiles_add(b->id, b->x, b->y, size,
                                   image_id_from_group(GROUP_BUILDING_TOWER) + orientation,
                                   TERRAIN_BUILDING | TERRAIN_GATEHOUSE);
            b->subtype.orientation = orientation;
            map_orientation_update_buildings();
            map_terrain_add_gatehouse_roads(b->x, b->y, orientation);
            map_tiles_update_area_roads(b->x, b->y, 5);
            map_tiles_update_all_plazas();
            map_tiles_update_area_walls(b->x, b->y, 5);
            break;
        case BUILDING_TRIUMPHAL_ARCH:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TRIUMPHAL_ARCH) + orientation - 1);
            b->subtype.orientation = orientation;
            map_orientation_update_buildings();
            map_terrain_add_triumphal_arch_roads(b->x, b->y, orientation);
            map_tiles_update_area_roads(b->x, b->y, 5);
            map_tiles_update_all_plazas();
            city_buildings_build_triumphal_arch();
            building_menu_update(BUILDSET_NORMAL);
            building_construction_clear_type();
            break;
        case BUILDING_VILLAGE_PALACE:
        case BUILDING_TOWN_PALACE:
        case BUILDING_CITY_PALACE:
        case BUILDING_SENATE_UPGRADED:
            switch (type) {
                case BUILDING_VILLAGE_PALACE:
                    add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_VILLAGE_PALACE));
                    break;
                case GROUP_BUILDING_TOWN_PALACE:
                    add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_TOWN_PALACE));
                    break;
                case GROUP_BUILDING_CITY_PALACE:
                    add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_CITY_PALACE));
                    break;
                case BUILDING_SENATE_UPGRADED:
                    add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_SENATE));
                    break;
            }
            city_buildings_add_senate(b);
            break;
        case BUILDING_BARRACKS:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_BARRACKS));
            city_buildings_add_barracks(b);
            break;
        case BUILDING_WAREHOUSE:
            add_warehouse(b);
            break;
        case BUILDING_HIPPODROME:
            if (GAME_ENV == ENGINE_ENV_C3) {
                add_hippodrome(b);
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_SENET_HOUSE));
            break;
        case BUILDING_FORT_LEGIONARIES:
        case BUILDING_FORT_JAVELIN:
        case BUILDING_FORT_MOUNTED:
            add_fort(type, b);
            break;
            // native buildings (unused, I think)
        case BUILDING_NATIVE_HUT:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_NATIVE) + (random_byte() & 1));
            break;
        case BUILDING_NATIVE_MEETING:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_NATIVE) + 2);
            break;
        case BUILDING_NATIVE_CROPS:
            add_building_tiles_image(b, image_id_from_group(GROUP_BUILDING_FARMLAND));
            break;
            // distribution center (also unused)
        case BUILDING_DISTRIBUTION_CENTER_UNUSED:
            city_buildings_add_distribution_center(b);
            break;
        case BUILDING_DRAGGABLE_RESERVOIR:
        case BUILDING_RESERVOIR:
            if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                b->data.industry.orientation = waterside_orientation_abs;
                map_water_add_building(b->id, b->x, b->y, 2,
                                       image_id_from_group(GROUP_BUILDING_RESERVOIR) + waterside_orientation_rel);
                break;
            }
        default:
            auto p = building_properties_for_type(type);
            add_building_tiles_image(b, image_id_from_group(p->image_group) + p->image_offset);
            break;
    }
    map_routing_update_land();
    map_routing_update_walls();
}

static void mark_construction(int x, int y, int size, int terrain, int absolute_xy) {
    if (map_building_tiles_mark_construction(x, y, size, terrain, absolute_xy))
        data.draw_as_constructing = 1;

}
static int has_nearby_enemy(int x_start, int y_start, int x_end, int y_end) {
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure *f = figure_get(i);
        if (config_get(CONFIG_GP_CH_WOLVES_BLOCK)) {
            if (f->state != FIGURE_STATE_ALIVE || (!f->is_enemy() && f->type != FIGURE_WOLF))
                continue;

        } else if (f->state != FIGURE_STATE_ALIVE || !f->is_enemy())
            continue;

        int dx = (f->tile_x > x_start) ? (f->tile_x - x_start) : (x_start - f->tile_x);
        int dy = (f->tile_y > y_start) ? (f->tile_y - y_start) : (y_start - f->tile_y);
        if (dx <= 12 && dy <= 12)
            return 1;

        dx = (f->tile_x > x_end) ? (f->tile_x - x_end) : (x_end - f->tile_x);
        dy = (f->tile_y > y_end) ? (f->tile_y - y_end) : (y_end - f->tile_y);
        if (dx <= 12 && dy <= 12)
            return 1;

    }
    return 0;
}

static int place_houses(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    int x_min, x_max, y_min, y_max;
    map_grid_start_end_to_area(x_start, y_start, x_end, y_end, &x_min, &y_min, &x_max, &y_max);

    int needs_road_warning = 0;
    int items_placed = 0;
    game_undo_restore_building_state();
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            int grid_offset = map_grid_offset(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR) || map_terrain_exists_tile_in_radius_with_type(x, y, 1, 1, TERRAIN_FLOODPLAIN))
                continue;

            if (measure_only) {
                map_property_mark_constructing(grid_offset);
                items_placed++;
            } else {
                if (formation_herd_breeding_ground_at(x, y, 1)) {
                    map_property_clear_constructing_and_deleted();
                    city_warning_show(WARNING_HERD_BREEDING_GROUNDS);
                } else {
                    building *b = building_create(BUILDING_HOUSE_VACANT_LOT, x, y);
                    game_undo_add_building(b);
                    if (b->id > 0) {
                        items_placed++;
                        map_building_tiles_add(b->id, x, y, 1,
                                               image_id_from_group(GROUP_BUILDING_HOUSE_VACANT_LOT), TERRAIN_BUILDING);
                        if (!map_terrain_exists_tile_in_radius_with_type(x, y, 1, 2, TERRAIN_ROAD))
                            needs_road_warning = 1;
                    }
                }
            }
        }
    }
    if (!measure_only) {
        building_construction_warning_check_food_stocks(BUILDING_HOUSE_VACANT_LOT);
        if (needs_road_warning)
            city_warning_show(WARNING_HOUSE_TOO_FAR_FROM_ROAD);

        map_routing_update_land();
        window_invalidate();
    }
    return items_placed;
}
static int place_plaza(int x_start, int y_start, int x_end, int y_end) {
    int x_min, y_min, x_max, y_max;
    map_grid_start_end_to_area(x_start, y_start, x_end, y_end, &x_min, &y_min, &x_max, &y_max);
    game_undo_restore_map(1);

    int items_placed = 0;
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            int grid_offset = map_grid_offset(x, y);
            if (map_terrain_is(grid_offset, TERRAIN_ROAD) &&
                !map_terrain_is(grid_offset, TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_AQUEDUCT)
                && map_tiles_is_paved_road(grid_offset)) {
                if (!map_property_is_plaza_or_earthquake(grid_offset))
                    items_placed++;

                map_image_set(grid_offset, 0);
                map_property_mark_plaza_or_earthquake(grid_offset);
                map_property_set_multi_tile_size(grid_offset, 1);
                map_property_mark_draw_tile(grid_offset);
            }
        }
    }
    map_tiles_update_all_plazas();
    return items_placed;
}
static int place_garden(int x_start, int y_start, int x_end, int y_end) {
    game_undo_restore_map(1);

    int x_min, y_min, x_max, y_max;
    map_grid_start_end_to_area(x_start, y_start, x_end, y_end, &x_min, &y_min, &x_max, &y_max);

    int items_placed = 0;
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            int grid_offset = map_grid_offset(x, y);
            if (!map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR) &&  !map_terrain_exists_tile_in_radius_with_type(x, y, 1, 1, TERRAIN_FLOODPLAIN)) {
                if (formation_herd_breeding_ground_at(x, y, 1)) {
                    map_property_clear_constructing_and_deleted();
                    city_warning_show(WARNING_HERD_BREEDING_GROUNDS);
                } else {
                    items_placed++;
                    map_terrain_add(grid_offset, TERRAIN_GARDEN);
                }
            }
        }
    }
    map_tiles_update_all_gardens();
    return items_placed;
}
static int place_reservoir_and_aqueducts(bool measure_only, int x_start, int y_start, int x_end, int y_end, struct reservoir_info *info) {
    info->cost = 0;
    info->place_reservoir_at_start = PLACE_RESERVOIR_NO;
    info->place_reservoir_at_end = PLACE_RESERVOIR_NO;

    game_undo_restore_map(0);

    int distance = calc_maximum_distance(x_start, y_start, x_end, y_end);
    if (measure_only && !data.in_progress)
        distance = 0;

    if (distance > 0) {
        if (map_building_is_reservoir(x_start - 1, y_start - 1))
            info->place_reservoir_at_start = PLACE_RESERVOIR_EXISTS;
        else if (map_tiles_are_clear(x_start - 1, y_start - 1, 3, TERRAIN_ALL))
            info->place_reservoir_at_start = PLACE_RESERVOIR_YES;
        else {
            info->place_reservoir_at_start = PLACE_RESERVOIR_BLOCKED;
        }
    }
    if (map_building_is_reservoir(x_end - 1, y_end - 1))
        info->place_reservoir_at_end = PLACE_RESERVOIR_EXISTS;
    else if (map_tiles_are_clear(x_end - 1, y_end - 1, 3, TERRAIN_ALL))
        info->place_reservoir_at_end = PLACE_RESERVOIR_YES;
    else {
        info->place_reservoir_at_end = PLACE_RESERVOIR_BLOCKED;
    }
    if (info->place_reservoir_at_start == PLACE_RESERVOIR_BLOCKED ||
        info->place_reservoir_at_end == PLACE_RESERVOIR_BLOCKED)
        return 0;

    if (info->place_reservoir_at_start == PLACE_RESERVOIR_YES && info->place_reservoir_at_end == PLACE_RESERVOIR_YES &&
        distance < 3)
        return 0;

    if (!distance) {
        if (info->place_reservoir_at_end == PLACE_RESERVOIR_YES)
            info->cost = model_get_building(BUILDING_RESERVOIR)->cost;

        return 1;
    }
    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_AQUEDUCT, x_start, y_start))
        return 0;

    if (info->place_reservoir_at_start != PLACE_RESERVOIR_NO) {
        map_routing_block(x_start - 1, y_start - 1, 3);
        mark_construction(x_start - 1, y_start - 1, 3, TERRAIN_ALL, 1);
    }
    if (info->place_reservoir_at_end != PLACE_RESERVOIR_NO) {
        map_routing_block(x_end - 1, y_end - 1, 3);
        mark_construction(x_end - 1, y_end - 1, 3, TERRAIN_ALL, 1);
    }
    const int aqueduct_offsets_x[] = {0, 2, 0, -2};
    const int aqueduct_offsets_y[] = {-2, 0, 2, 0};
    int min_dist = 10000;
    int min_dir_start = 0, min_dir_end = 0;
    for (int dir_start = 0; dir_start < 4; dir_start++) {
        int dx_start = aqueduct_offsets_x[dir_start];
        int dy_start = aqueduct_offsets_y[dir_start];
        for (int dir_end = 0; dir_end < 4; dir_end++) {
            int dx_end = aqueduct_offsets_x[dir_end];
            int dy_end = aqueduct_offsets_y[dir_end];
            int dist;
            if (building_construction_place_aqueduct_for_reservoir(1,
                                                                   x_start + dx_start, y_start + dy_start,
                                                                   x_end + dx_end, y_end + dy_end, &dist)) {
                if (dist && dist < min_dist) {
                    min_dist = dist;
                    min_dir_start = dir_start;
                    min_dir_end = dir_end;
                }
            }
        }
    }
    if (min_dist == 10000)
        return 0;

    int x_aq_start = aqueduct_offsets_x[min_dir_start];
    int y_aq_start = aqueduct_offsets_y[min_dir_start];
    int x_aq_end = aqueduct_offsets_x[min_dir_end];
    int y_aq_end = aqueduct_offsets_y[min_dir_end];
    int aq_items;
    building_construction_place_aqueduct_for_reservoir(0, x_start + x_aq_start, y_start + y_aq_start,
                                                       x_end + x_aq_end, y_end + y_aq_end, &aq_items);
    if (info->place_reservoir_at_start == PLACE_RESERVOIR_YES)
        info->cost += model_get_building(BUILDING_RESERVOIR)->cost;

    if (info->place_reservoir_at_end == PLACE_RESERVOIR_YES)
        info->cost += model_get_building(BUILDING_RESERVOIR)->cost;

    if (aq_items)
        info->cost += aq_items * model_get_building(BUILDING_AQUEDUCT)->cost;

    return 1;
}

static bool attempt_placing_generic(int type, int x, int y, int orientation, int terrain_exception = TERRAIN_NONE) {
    // by default, get size from building's properties
    int size = building_properties_for_type(type)->size;
    switch (type) { // special cases
        case BUILDING_WAREHOUSE:
            size = 3; break;
        case BUILDING_BOOTH:
            size = 2; break;
        case BUILDING_BANDSTAND:
            size = 3; break;
        case BUILDING_PAVILLION:
            size = 4; break;
        case BUILDING_FESTIVAL_SQUARE:
            size = 5; break;
    }

    // correct building placement for city orientations
    switch (city_view_orientation()) {
        case DIR_2_BOTTOM_RIGHT:
            x = x - size + 1;
            break;
        case DIR_4_BOTTOM_LEFT:
            x = x - size + 1;
            y = y - size + 1;
            break;
        case DIR_6_TOP_LEFT:
            y = y - size + 1;
            break;
    }

    // check if terrain is fully suitable for construction
    if (!map_tiles_are_clear(x, y, size, TERRAIN_ALL - terrain_exception)) {
        city_warning_show(WARNING_CLEAR_LAND_NEEDED);
        return false;
    }

    // extra terrain checks
    int warning_id = 0;
    if (!building_construction_can_place_on_terrain(x, y, &warning_id, size)) {
        city_warning_show(warning_id);
        return false;
    }

    // final generic checks
    building_construction_warning_generic_checks(type, x, y, size);

    // checks done!!!
    building *b;
    if (building_is_fort(type))
        b = building_create(BUILDING_MENU_FORTS, x, y);
    else
        b = building_create(type, x, y);
    game_undo_add_building(b);
    if (b->id <= 0) // building creation failed????
        return false;
    add_to_map(type, b, size, orientation, orientation, (4 + orientation - city_view_orientation() / 2) % 4);

    // reset grass growth when placing floodplain farms
    if (building_is_floodplain_farm(b)) {
        for (int _y = b->y; _y < b->y + b->size; _y++)
            for (int _x = b->x; _x < b->x + b->size; _x++)
                map_set_floodplain_growth(map_grid_offset(_x, _y), 0);
    }
    return true;
}
static bool attempt_placing_on_shore(int type, int x, int y, int shore_size, bool need_open_water) {
    int orientation = 0;
    switch (shore_size) { // different function calls for different shore sizes...
        case 2:
            if (map_water_determine_orientation_size2(x, y, 0, &orientation)) {
                city_warning_show(WARNING_SHORE_NEEDED);
                return false;
            } break;
        case 3:
            if (map_water_determine_orientation_size3(x, y, 0, &orientation)) {
                city_warning_show(WARNING_SHORE_NEEDED);
                return false;
            } break;
        default: // no other shore sizes supported
            return false;
    }

    // check if in open waters
    if (need_open_water && !building_dock_is_connected_to_open_water(x, y)) {
        city_warning_show(WARNING_DOCK_OPEN_WATER_NEEDED);
        return 0;
    }

    // place!
    if (!attempt_placing_generic(type, x, y, orientation, TERRAIN_WATER))
        return false;
    return true;
}

int building_attempt_placing_and_return_cost(int type, int x_start, int y_start, int x_end, int y_end) {
    int x = x_end;
    int y = y_end;

    // for debugging...
    SDL_Log("Attempting to place at: %03i %03i %06i", x, y, map_grid_offset(x, y));

    // Check warnings for placement and create building/update tiles accordingly.
    // Some of the buildings below have specific warning messages (e.g. roadblocks)
    // that can't be easily put in `building_construction_can_place_on_terrain()`!
    int placement_cost = model_get_building(type)->cost;
    switch (type) {
        case BUILDING_CLEAR_LAND: {
            // BUG in original (keep this behaviour): if confirmation has to be asked (bridge/fort),
            // the previous cost is deducted from treasury and if user chooses 'no', they still pay for removal.
            // If we don't do it this way, the user doesn't pay for the removal at all since we don't come back
            // here when the user says yes.
            int items_placed = building_construction_clear_land(0, x_start, y_start, x_end, y_end);
            if (items_placed < 0)
                items_placed = last_items_cleared;
            placement_cost *= items_placed;
            map_property_clear_constructing_and_deleted();
            break;
        }
        case BUILDING_WALL:
            placement_cost *= building_construction_place_wall(0, x_start, y_start, x_end, y_end);
            break;
        case BUILDING_ROAD:
            placement_cost *= building_construction_place_road(0, x_start, y_start, x_end, y_end);
            break;
        case BUILDING_PLAZA:
            placement_cost *= place_plaza(x_start, y_start, x_end, y_end);
            break;
        case BUILDING_GARDENS:
            placement_cost *= place_garden(x_start, y_start, x_end, y_end);
            map_routing_update_land();
            break;
        case BUILDING_LOW_BRIDGE:
        case BUILDING_SHIP_BRIDGE: {
            int length = map_bridge_add(x_end, y_end, type == BUILDING_SHIP_BRIDGE);
            if (length <= 1) {
                city_warning_show(WARNING_SHORE_NEEDED);
                return 0;
            }
            placement_cost *= length;
            break;
        }
        case BUILDING_AQUEDUCT: {
            int cost;
            if (!building_construction_place_aqueduct(x_start, y_start, x_end, y_end, &cost)) {
                city_warning_show(WARNING_CLEAR_LAND_NEEDED);
                return 0;
            }
            placement_cost = cost;
            map_tiles_update_all_aqueducts(0);
            map_routing_update_land();
            break;
        }
        case BUILDING_DRAGGABLE_RESERVOIR: { // doubles as BUILDING_WATER_LIFT
            if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                if (!attempt_placing_on_shore(type, x, y, 2, false))
                    return 0;
                break;
            }
            struct reservoir_info info;
            if (!place_reservoir_and_aqueducts(0, x_start, y_start, x_end, y_end, &info)) {
                map_property_clear_constructing_and_deleted();
                city_warning_show(WARNING_CLEAR_LAND_NEEDED);
                return 0;
            }
            if (info.place_reservoir_at_start == PLACE_RESERVOIR_YES) {
                building *reservoir = building_create(BUILDING_RESERVOIR, x_start - 1, y_start - 1);
                game_undo_add_building(reservoir);
                map_building_tiles_add(reservoir->id, x_start - 1, y_start - 1, 3,
                                       image_id_from_group(GROUP_BUILDING_RESERVOIR), TERRAIN_BUILDING);
                map_aqueduct_set(map_grid_offset(x_start - 1, y_start - 1), 0);
            }
            if (info.place_reservoir_at_end == PLACE_RESERVOIR_YES) {
                building *reservoir = building_create(BUILDING_RESERVOIR, x_end - 1, y_end - 1);
                game_undo_add_building(reservoir);
                map_building_tiles_add(reservoir->id, x_end - 1, y_end - 1, 3,
                                       image_id_from_group(GROUP_BUILDING_RESERVOIR), TERRAIN_BUILDING);
                map_aqueduct_set(map_grid_offset(x_end - 1, y_end - 1), 0);
                if (!map_terrain_exists_tile_in_area_with_type(x_start - 2, y_start - 2, 5, TERRAIN_WATER) &&
                    info.place_reservoir_at_start == PLACE_RESERVOIR_NO)
                    building_construction_warning_check_reservoir(BUILDING_RESERVOIR);
            }
            placement_cost = info.cost;
            map_tiles_update_all_aqueducts(0);
            map_routing_update_land();
            break;
        }
        case BUILDING_HOUSE_VACANT_LOT:
            placement_cost *= place_houses(0, x_start, y_start, x_end, y_end);
            if (placement_cost == 0) {
                city_warning_show(WARNING_CLEAR_LAND_NEEDED);
                return 0;
            }
            break;

        ////////

        case BUILDING_GATEHOUSE:
        case BUILDING_GATEHOUSE_PH: {
            int orientation = map_orientation_for_gatehouse(x, y);
            if (!orientation) { // leftover from C3?
                if (building_rotation_get_road_orientation() == 1)
                    orientation = 1;
                else
                    orientation = 2;
            }
            if (!map_terrain_all_tiles_in_area_are(x, y, 1, TERRAIN_ROAD)) {
//                city_warning_show(WARNING_ROADBLOCKS_ROAD_NEEDED); // TODO
                return 0;
            }
            if (!attempt_placing_generic(type, x, y, orientation, TERRAIN_ROAD))
                return 0;
            break;
        }
        case BUILDING_TRIUMPHAL_ARCH: {
            int orientation = map_orientation_for_triumphal_arch(x, y);
            if (!orientation) { // leftover from C3?
                if (building_rotation_get_road_orientation() == 1)
                    orientation = 1;
                else
                    orientation = 3;
            }
            if (!attempt_placing_generic(type, x, y, orientation, TERRAIN_ROAD))
                return 0;
            break;
        }
        case BUILDING_TOWER:
        case BUILDING_TOWER_PH:
            if (!map_terrain_all_tiles_in_area_are(x, y, 2, TERRAIN_WALL)) {
                city_warning_show(WARNING_WALL_NEEDED);
                return 0;
            }
            if (!attempt_placing_generic(type, x, y, 0, TERRAIN_WALL))
                return 0;
            break;
        case BUILDING_ROADBLOCK:
            if (!map_terrain_all_tiles_in_area_are(x, y, 1, TERRAIN_ROAD)) {
                city_warning_show(WARNING_ROADBLOCKS_ROAD_NEEDED);
                return 0;
            }
            if (!attempt_placing_generic(type, x, y, 0, TERRAIN_ROAD))
                return 0;
            break;
        case BUILDING_BOOTH:
        case BUILDING_BANDSTAND:
        case BUILDING_PAVILLION:
        case BUILDING_FESTIVAL_SQUARE:
            if (GAME_ENV == ENGINE_ENV_C3) {
                // default behavior
                if (!attempt_placing_generic(type, x, y, 0))
                    return 0;
            } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                int orientation = 0;
                int booth_warning = 0;
                if (type == BUILDING_BOOTH)
                    booth_warning = map_orientation_for_venue_with_map_orientation(x, y, 0, &orientation);
                if (type == BUILDING_BANDSTAND)
                    booth_warning = map_orientation_for_venue_with_map_orientation(x, y, 1, &orientation);
                if (type == BUILDING_PAVILLION)
                    booth_warning = map_orientation_for_venue_with_map_orientation(x, y, 2, &orientation);
                if (type == BUILDING_FESTIVAL_SQUARE) {
                    if (city_building_has_festival_square()) {
                        city_warning_show(WARNING_ONE_BUILDING_OF_TYPE);
                        return 0;
                    }
                    booth_warning = map_orientation_for_venue_with_map_orientation(x, y, 3, &orientation);
                }
                if (booth_warning != 1) {
                    if (booth_warning == -1)
                        city_warning_show(WARNING_BOOTH_ROAD_INTERSECTION_NEEDED);
                    else if (booth_warning == -2)
                        city_warning_show(WARNING_FESTIVAL_ROAD_INTERSECTION_NEEDED);
                    else if (booth_warning == 0)
                        city_warning_show(WARNING_CLEAR_LAND_NEEDED);
                    return 0;
                }
                if (!attempt_placing_generic(type, x, y, orientation, TERRAIN_ROAD))
                    return 0;
            }
            break;
        case BUILDING_WHARF:
            if (!attempt_placing_on_shore(type, x, y, 2, false))
                return 0;
            break;
        case BUILDING_DOCK:
            if (!attempt_placing_on_shore(type, x, y, 3, true))
                return 0;
            break;
        case BUILDING_SHIPYARD: {
            if (GAME_ENV == ENGINE_ENV_C3 && !attempt_placing_on_shore(type, x, y, 2, false)) // size 2 for C3
                return 0;
            else if (GAME_ENV == ENGINE_ENV_PHARAOH && !attempt_placing_on_shore(type, x, y, 3, true)) // size 3 for Pharaoh
                return 0;
            break;
        }
        case BUILDING_SENATE:
        case BUILDING_SENATE_UPGRADED:
        case BUILDING_VILLAGE_PALACE:
        case BUILDING_TOWN_PALACE:
        case BUILDING_CITY_PALACE:
            if (city_buildings_has_senate()) {
                city_warning_show(WARNING_ONE_BUILDING_OF_TYPE);
                return 0;
            }
            if (!attempt_placing_generic(type, x, y, 0))
                return 0;
            break;
        case BUILDING_BARRACKS:
            if (city_buildings_has_barracks() && !config_get(CONFIG_GP_CH_MULTIPLE_BARRACKS)) {
                city_warning_show(WARNING_ONE_BUILDING_OF_TYPE);
                return 0;
            }
            if (!attempt_placing_generic(type, x, y, 0))
                return 0;
            break;
        case BUILDING_WHEAT_FARM:
        case BUILDING_VEGETABLE_FARM:
        case BUILDING_FRUIT_FARM:
        case BUILDING_OLIVE_FARM:
        case BUILDING_VINES_FARM:
        case BUILDING_PIG_FARM:
        case BUILDING_FIGS_FARM:
        case BUILDING_HENNA_FARM:
            if (!attempt_placing_generic(type, x, y, 0, TERRAIN_FLOODPLAIN))
                return 0;
            break;
        case BUILDING_PYRAMID:
        case BUILDING_SPHYNX:
        case BUILDING_MAUSOLEUM:
        case BUILDING_ALEXANDRIA_LIBRARY:
        case BUILDING_CAESAREUM:
        case BUILDING_PHAROS_LIGHTHOUSE:
        case BUILDING_SMALL_ROYAL_TOMB:
        case BUILDING_ABU_SIMBEL:
        case BUILDING_MEDIUM_ROYAL_TOMB:
        case BUILDING_LARGE_ROYAL_TOMB:
        case BUILDING_GRAND_ROYAL_TOMB:
            // TODO
            return 0;
            break;
        default:
            int warning_id;
            if (!attempt_placing_generic(type, x, y, 0))
                return 0;
            break;
    }
    return placement_cost;

        // TODO
//    if (building_is_fort(type)) {
//        const int offsets_x[] = {3, -1, -4, 0};
//        const int offsets_y[] = {-1, -4, 0, 3};
//        int orient_index = building_rotation_get_rotation();
//        int x_offset = offsets_x[orient_index];
//        int y_offset = offsets_y[orient_index];
//        if (!map_tiles_are_clear(x + x_offset, y + y_offset, 4, terrain_mask)) {
//            city_warning_show(WARNING_CLEAR_LAND_NEEDED);
//            return 0;
//        }
//        if (formation_get_num_legions_cached() >= formation_get_max_legions()) {
//            city_warning_show(WARNING_MAX_LEGIONS_REACHED);
//            return 0;
//        }
//    }
}

bool building_check_preliminary_warnings(int type, int x_start, int y_start, int x_end, int y_end) {
    // reset all warnings before checking
    building_construction_warning_reset();

    // invalid build
    if (!type)
        return false;

    // todo: no money needed if building has zero cost?
    if (city_finance_out_of_money()) {
        map_property_clear_constructing_and_deleted();
        city_warning_show(WARNING_OUT_OF_MONEY);
        return false;
    }

    // check if enemy is nearby
    if (type != BUILDING_CLEAR_LAND && has_nearby_enemy(x_start, y_start, x_end, y_end)) {
        if (type == BUILDING_WALL || type == BUILDING_ROAD || type == BUILDING_AQUEDUCT)
            game_undo_restore_map(0);
        else if (type == BUILDING_PLAZA || type == BUILDING_GARDENS)
            game_undo_restore_map(1);
        else if (type == BUILDING_LOW_BRIDGE || type == BUILDING_SHIP_BRIDGE)
            map_bridge_reset_building_length();
        else
            map_property_clear_constructing_and_deleted();
        city_warning_show(WARNING_ENEMY_NEARBY);
        return false;
    }

    // game-specific builds that require resources
    if (GAME_ENV == ENGINE_ENV_C3) {
        // large temples requires marble in C3
        if (building_is_large_temple(type) && city_resource_count(RESOURCE_MARBLE_C3) < 2) {
            map_property_clear_constructing_and_deleted();
            city_warning_show(WARNING_MARBLE_NEEDED_LARGE_TEMPLE);
            return false;
        }
        // oracle requires marble in C3
        if (type == BUILDING_ORACLE && city_resource_count(RESOURCE_MARBLE_C3) < 2) {
            map_property_clear_constructing_and_deleted();
            city_warning_show(WARNING_MARBLE_NEEDED_ORACLE);
            return false;
        }
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        // todo
        // library: requires papyrus
        // obelisk: requires granite
        // (others?)
    }

    return true;
}
void building_consume_resources(int type) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (building_is_large_temple(type) || type == BUILDING_ORACLE)
            building_warehouses_remove_resource(RESOURCE_MARBLE_C3, 2);
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        // todo
        // library: requires papyrus
        // obelisk: requires granite
        // (others?)
    }
}

void building_construction_set_type(int type) { // select building for construction, set up main terrain restrictions/requirements
    data.type = type;
    data.size = building_properties_for_type(type)->size;
    data.sub_type = BUILDING_NONE;
    data.in_progress = 0;
    data.start.x = 0;
    data.start.y = 0;
    data.end.x = 0;
    data.end.y = 0;

    if (type != BUILDING_NONE) {
        data.required_terrain.wall = false;
        data.required_terrain.water = false;
        data.required_terrain.groundwater = false;
        data.required_terrain.tree = false;
        data.required_terrain.rock = false;
        data.required_terrain.ore = false;
        data.required_terrain.meadow = false;
        data.start.grid_offset = false;

        switch (type) {
            case BUILDING_WHEAT_FARM:
            case BUILDING_VEGETABLE_FARM:
            case BUILDING_FRUIT_FARM:
            case BUILDING_OLIVE_FARM:
            case BUILDING_VINES_FARM:
            case BUILDING_PIG_FARM:
            case BUILDING_FIGS_FARM:
            case BUILDING_HENNA_FARM:
                data.required_terrain.meadow = true;
                break;
            case BUILDING_MARBLE_QUARRY:
            case BUILDING_IRON_MINE:
            case BUILDING_GRANITE_QUARRY:
            case BUILDING_SANDSTONE_QUARRY:
                data.required_terrain.rock = true;
                break;
            case BUILDING_GOLD_MINE:
            case BUILDING_GEMSTONE_MINE:
            case BUILDING_COPPER_MINE:
                data.required_terrain.rock = true;
                data.required_terrain.ore = true;
                break;
            case BUILDING_TIMBER_YARD:
                if (GAME_ENV == ENGINE_ENV_C3)
                    data.required_terrain.tree = true;
                break;
            case BUILDING_CLAY_PIT:
                data.required_terrain.water = true;
                break;
            case BUILDING_TOWER:
                data.required_terrain.wall = true;
                break;
            case BUILDING_MENU_SMALL_TEMPLES:
                data.sub_type = BUILDING_SMALL_TEMPLE_CERES;
                break;
            case BUILDING_MENU_LARGE_TEMPLES:
                data.sub_type = BUILDING_LARGE_TEMPLE_CERES;
                break;
            case BUILDING_WELL:
            case BUILDING_WATER_SUPPLY:
            case BUILDING_VILLAGE_PALACE:
            case BUILDING_TOWN_PALACE:
            case BUILDING_CITY_PALACE:
                if (GAME_ENV == ENGINE_ENV_PHARAOH)
                    data.required_terrain.groundwater = true;
                break;
            default:
                break;
        }
    }
}
void building_construction_clear_type(void) {
    data.cost = 0;
    data.sub_type = BUILDING_NONE;
    data.type = BUILDING_NONE;
}
int building_construction_type(void) {
    return data.sub_type ? data.sub_type : data.type;
}
int building_construction_cost(void) {
    return data.cost;
}
int building_construction_size(int *x, int *y) {
    if (!config_get(CONFIG_UI_SHOW_CONSTRUCTION_SIZE) ||
        !building_construction_is_draggable() ||
        (data.type != BUILDING_CLEAR_LAND && !data.cost)) {
        return 0;
    }
    int size_x = data.end.x - data.start.x;
    int size_y = data.end.y - data.start.y;
    if (size_x < 0)
        size_x = -size_x;

    if (size_y < 0)
        size_y = -size_y;

    size_x++;
    size_y++;
    *x = size_x;
    *y = size_y;
    return 1;
}
bool building_construction_in_progress(void) {
    return data.in_progress;
}
bool building_construction_is_draggable(void) {
    switch (data.type) {
        case BUILDING_CLEAR_LAND:
        case BUILDING_ROAD:
        case BUILDING_AQUEDUCT:
        case BUILDING_WALL:
        case BUILDING_PLAZA:
        case BUILDING_GARDENS:
        case BUILDING_HOUSE_VACANT_LOT:
            return true;
        case BUILDING_DRAGGABLE_RESERVOIR:
            if (GAME_ENV == ENGINE_ENV_C3)
                return true;
            else
                return false;
        default:
            return false;
    }
}

void building_construction_start(int x, int y, int grid_offset) {
    data.start.grid_offset = grid_offset;
    data.start.x = data.end.x = x;
    data.start.y = data.end.y = y;

    if (game_undo_start_build(data.type)) {
        data.in_progress = 1;
        int can_start = 1;
        switch (data.type) {
            case BUILDING_ROAD:
                can_start = map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, data.start.x,
                                                                         data.start.y);
                break;
            case BUILDING_AQUEDUCT:
            case BUILDING_DRAGGABLE_RESERVOIR:
                can_start = map_routing_calculate_distances_for_building(ROUTED_BUILDING_AQUEDUCT, data.start.x,
                                                                         data.start.y);
                break;
            case BUILDING_WALL:
                can_start = map_routing_calculate_distances_for_building(ROUTED_BUILDING_WALL, data.start.x,
                                                                         data.start.y);
                break;
            default:
                break;
        }
        if (!can_start)
            building_construction_cancel();
    }
}
void building_construction_cancel(void) {
    map_property_clear_constructing_and_deleted();
    if (data.in_progress && building_construction_is_draggable()) {
        if (building_construction_is_draggable())
            game_undo_restore_map(1);

        data.in_progress = 0;
    } else {
        building_construction_set_type(BUILDING_NONE);
        widget_sidebar_city_release_build_buttons();
    }
    building_rotation_reset_rotation();
}
void building_construction_update(int x, int y, int grid_offset) {// update ghost placement (constructing e.g. roads)
    int type = data.sub_type ? data.sub_type : data.type;
    if (grid_offset) {
        data.end.x = x;
        data.end.y = y;
        data.end.grid_offset = grid_offset;
    } else {
        x = data.end.x;
        y = data.end.y;
        grid_offset = data.end.grid_offset;
    }
    if (!type || city_finance_out_of_money()) {
        data.cost = 0;
        return;
    }
    map_property_clear_constructing_and_deleted();
    int current_cost = model_get_building(type)->cost;

    if (type == BUILDING_CLEAR_LAND) {
        int items_placed = last_items_cleared = building_construction_clear_land(1, data.start.x, data.start.y, x, y);
        if (items_placed >= 0) current_cost *= items_placed;
    } else if (type == BUILDING_WALL) {
        int items_placed = building_construction_place_wall(1, data.start.x, data.start.y, x, y);
        if (items_placed >= 0) current_cost *= items_placed;
    } else if (type == BUILDING_ROAD) {
        int items_placed = building_construction_place_road(1, data.start.x, data.start.y, x, y);
        if (items_placed >= 0) current_cost *= items_placed;
    } else if (type == BUILDING_PLAZA) {
        int items_placed = place_plaza(data.start.x, data.start.y, x, y);
        if (items_placed >= 0) current_cost *= items_placed;
    } else if (type == BUILDING_GARDENS) {
        int items_placed = place_garden(data.start.x, data.start.y, x, y);
        if (items_placed >= 0) current_cost *= items_placed;
    } else if (type == BUILDING_LOW_BRIDGE || type == BUILDING_SHIP_BRIDGE) {
        int length = map_bridge_building_length();
        if (length > 1) current_cost *= length;
    } else if (type == BUILDING_AQUEDUCT) {
        building_construction_place_aqueduct(data.start.x, data.start.y, x, y, &current_cost);
        map_tiles_update_all_aqueducts(0);
    } else if (type == BUILDING_DRAGGABLE_RESERVOIR) {
        struct reservoir_info info;
        place_reservoir_and_aqueducts(1, data.start.x, data.start.y, x, y, &info);
        current_cost = info.cost;
        map_tiles_update_all_aqueducts(1);
        data.draw_as_constructing = 0;
    } else if (type == BUILDING_HOUSE_VACANT_LOT) {
        int items_placed = place_houses(1, data.start.x, data.start.y, x, y);
        if (items_placed >= 0) current_cost *= items_placed;
    } else if (type == BUILDING_GATEHOUSE || type == BUILDING_GATEHOUSE_PH)
        mark_construction(x, y, 2, ~TERRAIN_ROAD, 0);
    else if (type == BUILDING_ROADBLOCK) {
        // Don't show the footprint for roadblocks
    } else if (type == BUILDING_TRIUMPHAL_ARCH)
        mark_construction(x, y, 3, ~TERRAIN_ROAD, 0);
    else if (type == BUILDING_WAREHOUSE)
        mark_construction(x, y, 3, TERRAIN_ALL, 0);
    else if (building_is_fort(type)) {
        if (formation_get_num_legions_cached() < 6) {
            if (map_building_tiles_are_clear(x, y, 3, TERRAIN_ALL) &&
                map_building_tiles_are_clear(
                        x + FORT_X_OFFSET[building_rotation_get_rotation()][city_view_orientation() / 2],
                        y + FORT_Y_OFFSET[building_rotation_get_rotation()][city_view_orientation() / 2], 4,
                        TERRAIN_ALL)) {
                mark_construction(x, y, 3, TERRAIN_ALL, 0);
            }
        }
    } else if (type == BUILDING_HIPPODROME) {
        int x_offset_1, y_offset_1;
        building_rotation_get_offset_with_rotation(5, building_rotation_get_rotation(), &x_offset_1, &y_offset_1);
        int x_offset_2, y_offset_2;
        building_rotation_get_offset_with_rotation(10, building_rotation_get_rotation(), &x_offset_2, &y_offset_2);
        if (map_building_tiles_are_clear(x, y, 5, TERRAIN_ALL) &&
            map_building_tiles_are_clear(x + x_offset_1, y + y_offset_1, 5, TERRAIN_ALL) &&
            map_building_tiles_are_clear(x + x_offset_2, y + y_offset_2, 5, TERRAIN_ALL)) {
            mark_construction(x, y, 5, TERRAIN_ALL, 0);
        }
    } else if (type == BUILDING_SHIPYARD || type == BUILDING_WHARF) {
        if (!map_water_determine_orientation_size2(x, y, 1, 0))
            data.draw_as_constructing = 1;
    } else if (type == BUILDING_DOCK) {
        if (!map_water_determine_orientation_size3(x, y, 1, 0))
            data.draw_as_constructing = 1;
    } else if (data.required_terrain.meadow || data.required_terrain.rock || data.required_terrain.tree ||
               data.required_terrain.water || data.required_terrain.wall || data.required_terrain.groundwater) {
        // never mark as constructing
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH && (type == BUILDING_BOOTH || type == BUILDING_BANDSTAND
        || type == BUILDING_PAVILLION || type == BUILDING_FESTIVAL_SQUARE)) {
        // never mark as constructing; todo?
    } else {
        if (!(type == BUILDING_SENATE_UPGRADED && city_buildings_has_senate()) &&
            !(type == BUILDING_BARRACKS && city_buildings_has_barracks() &&
              !config_get(CONFIG_GP_CH_MULTIPLE_BARRACKS)) &&
            !(type == BUILDING_DISTRIBUTION_CENTER_UNUSED && city_buildings_has_distribution_center())) {
            int size = building_properties_for_type(type)->size;
            mark_construction(x, y, size, TERRAIN_ALL, 0);
        }
    }
    data.cost = current_cost;
}
void building_construction_finalize(void) { // confirm final placement
    data.in_progress = 0;
    int x_start = data.start.x;
    int y_start = data.start.y;
    int x_end = data.end.x;
    int y_end = data.end.y;
    int type = data.sub_type ? data.sub_type : data.type;

    // preliminary, global checks
    if (!building_check_preliminary_warnings(type, x_start, y_start, x_end, y_end))
        return;

    // attempt placing!
    int placement_cost = building_attempt_placing_and_return_cost(type, x_start, y_start, x_end, y_end);
    if (placement_cost == 0)
        return;

    // consume resources for specific buildings (e.g. marble, granite)
    building_consume_resources(type);

    // advance temple picker (C3 only)
    if (data.type == BUILDING_MENU_SMALL_TEMPLES) {
        data.sub_type++;
        if (data.sub_type > BUILDING_SMALL_TEMPLE_VENUS)
            data.sub_type = BUILDING_SMALL_TEMPLE_CERES;
    }
    if (data.type == BUILDING_MENU_LARGE_TEMPLES) {
        data.sub_type++;
        if (data.sub_type > BUILDING_LARGE_TEMPLE_VENUS)
            data.sub_type = BUILDING_LARGE_TEMPLE_CERES;
    }

    // finilize process
    if (placement_cost == 0)
        return;
    formation_move_herds_away(x_end, y_end);
    city_finance_process_construction(placement_cost);
    game_undo_finish_build(placement_cost);
    map_tiles_update_region_empty_land(false, x_start - 2, y_start - 2, x_end + data.size + 2, y_end + data.size + 2);
}

static void set_warning(int *warning_id, int warning) {
    if (warning_id)
        *warning_id = warning;
}

bool building_construction_can_place_on_terrain(int x, int y, int *warning_id, int size) {
    if (data.required_terrain.meadow) {
        int can_place = false;
        if (map_terrain_exists_tile_in_radius_with_type(x, y, size, 0, TERRAIN_MEADOW)) {
            set_warning(warning_id, WARNING_MEADOW_NEEDED);
            can_place = true;
        }
        if (GAME_ENV == ENGINE_ENV_PHARAOH && map_terrain_all_tiles_in_radius_are(x, y, size, 0, TERRAIN_FLOODPLAIN)) {
            set_warning(warning_id, WARNING_MEADOW_NEEDED);
            can_place = true;
        }
        if (!can_place)
            return false;
    } else if (data.required_terrain.rock) {
        if (!map_terrain_exists_tile_in_radius_with_type(x, y, size, 1, TERRAIN_ROCK)) { // todo: add ore rock
            set_warning(warning_id, WARNING_ROCK_NEEDED);
            return false;
        }
        if (data.required_terrain.ore && !map_terrain_exists_tile_in_radius_with_type(x, y, size, 1, TERRAIN_ORE)) { // todo: add ore rock
            set_warning(warning_id, WARNING_ROCK_NEEDED);
            return false;
        }
    } else if (data.required_terrain.tree) {
        if (!map_terrain_exists_tile_in_radius_with_type(x, y, size, 1, TERRAIN_SHRUB | TERRAIN_TREE)) {
            set_warning(warning_id, WARNING_TREE_NEEDED);
            return false;
        }
    } else if (data.required_terrain.water) {
        if (!map_terrain_exists_tile_in_radius_with_type(x, y, size, 3, TERRAIN_WATER)
        && !map_terrain_exists_tile_in_radius_with_type(x, y, size, 3, TERRAIN_FLOODPLAIN)) { // todo: add inundable lands check
            set_warning(warning_id, WARNING_WATER_NEEDED);
            return false;
        }
    } else if (data.required_terrain.wall) {
        if (!map_terrain_all_tiles_in_radius_are(x, y, size, 0, TERRAIN_WALL)) {
            set_warning(warning_id, WARNING_WALL_NEEDED);
            return false;
        }
    } else if (data.required_terrain.groundwater) {
        if (!map_terrain_exists_tile_in_radius_with_type(x, y, size, 0, TERRAIN_GROUNDWATER)) {
            set_warning(warning_id, WARNING_GROUNDWATER_NEEDED);
            return false;
        }
    }
    return true;
}
void building_construction_record_view_position(int view_x, int view_y, int grid_offset) {
    if (grid_offset == data.start.grid_offset) {
        data.start_offset_x_view = view_x;
        data.start_offset_y_view = view_y;
    }
}
void building_construction_get_view_position(int *view_x, int *view_y) {
    *view_x = data.start_offset_x_view;
    *view_y = data.start_offset_y_view;
}
int building_construction_get_start_grid_offset(void) {
    return data.start.grid_offset;
}
void building_construction_reset_draw_as_constructing(void) {
    data.draw_as_constructing = 0;
}
int building_construction_draw_as_constructing(void) {
    return data.draw_as_constructing;
}
