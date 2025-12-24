#include "building_temple_complex.h"

#include "city/city.h"
#include "game/undo.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "building/rotation.h"
#include "graphics/view/lookup.h"
#include "construction/build_planner.h"
#include "js/js_game.h"

tile2i building_part_offset(int orientation, int size) {
    tile2i offset = { 0, 0 };
    switch (orientation) {
    case 0: offset = { 0, -size }; break;
    case 1: offset = { size, 0 }; break;
    case 2: offset = { 0, size }; break;
    case 3: offset = { -size, 0 }; break;
    }

    return offset;
}

int building_temple_complex::preview::setup_orientation(int orientation) const { 
    return 1;
}

int building_temple_complex::preview::update_relative_orientation(build_planner &p, tile2i tile, int global_rotation) const {
    return global_rotation + 1;
}

void building_temple_complex::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);

    int EMPTY______ = 0;
    int main______n = params.first_img("main_n");
    int main______w = params.first_img("main_w");
    int oracle____n = params.first_img("oracle_n");
    int oracle____w = params.first_img("oracle_w");
    int altar_____n = params.first_img("altar_n");
    int altar_____w = params.first_img("altar_w");

    int tiles_____0 = params.first_img("tiles_0");
    int tiles_____1 = params.first_img("tiles_1");
    int tiles_____2 = params.first_img("tiles_2");
    int tiles_____3 = params.first_img("tiles_3");

    int statue1_image_id = params.first_img("statue_1");
    int statue____0 = statue1_image_id + 0; // north
    int statue____1 = statue1_image_id + 1; // east
    int statue____2 = statue1_image_id + 2; // south
    int statue____3 = statue1_image_id + 3; // west

    int statue2n = params.first_img("statue_2n");
    int statue_2n_F = statue2n + 0; // north
    int statue_2n_B = statue2n + 1;
    int statue2e = params.first_img("statue_2e");
    int statue_2e_A = statue2e + 0; // east
    int statue_2e_B = statue2e + 1;
    int statue2s = params.first_img("statue_2s");
    int statue_2s_A = statue2s + 0; // south
    int statue_2s_B = statue2s + 1;
    int statue2w = params.first_img("statue_2w");
    int statue_2w_A = statue2w + 0; // west
    int statue_2w_B = statue2w + 1;

    switch (planer.relative_orientation) {
    case 0:
        { // NE
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
                {tiles_____3, statue_2e_A, statue_2e_B, tiles_____1, statue_2w_A, statue_2w_B, tiles_____3},
                {tiles_____2, statue_2e_A, statue_2e_B, tiles_____1, statue_2w_A, statue_2w_B, tiles_____2},
                {tiles_____3, statue_2e_A, statue_2e_B, tiles_____1, statue_2w_A, statue_2w_B, tiles_____3},
                {tiles_____2, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____2},
                {tiles_____0, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, tiles_____0},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {statue____3, tiles_____0, main______w, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {tiles_____1, tiles_____1, EMPTY______, EMPTY______, EMPTY______, tiles_____1, tiles_____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {statue____3, tiles_____0, oracle____w, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {tiles_____1, tiles_____1, EMPTY______, EMPTY______, EMPTY______, tiles_____1, tiles_____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {statue____3, tiles_____0, altar_____w, EMPTY______, EMPTY______, tiles_____0, statue____1},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(7, 13));
            planer.pivot = { 2, 10 };
        }
        break;

    case 1:
        { // SE
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
                {statue____0, statue____0, tiles_____1, statue____0, statue____0, tiles_____1, statue____0, statue____0, tiles_____0, tiles_____2, tiles_____3, tiles_____2, tiles_____3},
                {tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____0, tiles_____0, statue_2s_B, statue_2s_B, statue_2s_B},
                {EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue_2s_A, statue_2s_A, statue_2s_A},
                {EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, tiles_____1, tiles_____1, tiles_____1, tiles_____1},
                {main______n, EMPTY______, EMPTY______, oracle____n, EMPTY______, EMPTY______, altar_____n, EMPTY______, EMPTY______, tiles_____0, statue_2n_B, statue_2n_B, statue_2n_B},
                {tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____0, tiles_____0, statue_2n_F, statue_2n_F, statue_2n_F},
                {statue____2, statue____2, tiles_____1, statue____2, statue____2, tiles_____1, statue____2, statue____2, tiles_____0, tiles_____2, tiles_____3, tiles_____2, tiles_____3},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(13, 7));
            planer.pivot = { 0, 2 };
        }
        break;

    case 2:
        { // SW
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {tiles_____1, tiles_____1, main______w, EMPTY______, EMPTY______, tiles_____1, tiles_____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {tiles_____1, tiles_____1, oracle____w, EMPTY______, EMPTY______, tiles_____1, tiles_____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {statue____3, tiles_____0, EMPTY______, EMPTY______, EMPTY______, tiles_____0, statue____1},
                {tiles_____0, tiles_____0, altar_____w, EMPTY______, EMPTY______, tiles_____0, tiles_____0},
                {tiles_____2, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____2},
                {tiles_____3, statue_2e_A, statue_2e_B, tiles_____1, statue_2w_A, statue_2w_B, tiles_____3},
                {tiles_____2, statue_2e_A, statue_2e_B, tiles_____1, statue_2w_A, statue_2w_B, tiles_____2},
                {tiles_____3, statue_2e_A, statue_2e_B, tiles_____1, statue_2w_A, statue_2w_B, tiles_____3},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(7, 13));
            planer.pivot = { 2, 0 };
        }
    break;

    case 3:
        { // NW
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
                {tiles_____3, tiles_____2, tiles_____3, tiles_____2, tiles_____0, statue____0, statue____0, tiles_____1, statue____0, statue____0, tiles_____1, statue____0, statue____0},
                {statue_2s_B, statue_2s_B, statue_2s_B, tiles_____0, tiles_____0, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0},
                {statue_2s_A, statue_2s_A, statue_2s_A, tiles_____0, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______},
                {tiles_____1, tiles_____1, tiles_____1, tiles_____1, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______},
                {statue_2n_B, statue_2n_B, statue_2n_B, tiles_____0, main______n, EMPTY______, EMPTY______, oracle____n, EMPTY______, EMPTY______, altar_____n, EMPTY______, EMPTY______},
                {statue_2n_F, statue_2n_F, statue_2n_F, tiles_____0, tiles_____0, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0, tiles_____1, tiles_____0, tiles_____0},
                {tiles_____3, tiles_____2, tiles_____3, tiles_____2, tiles_____0, statue____2, statue____2, tiles_____1, statue____2, statue____2, tiles_____1, statue____2, statue____2},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(13, 7));
            planer.pivot = { 10, 2 };
        }
        break;
    }
}

void map_add_temple_complex_base_tiles(e_building_type type, tile2i north_tile, int orientation) {
    int packid = -1;
    switch (type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS: packid = PACK_TEMPLE_NILE; break;
    case BUILDING_TEMPLE_COMPLEX_RA: packid = PACK_TEMPLE_RA; break;
    case BUILDING_TEMPLE_COMPLEX_PTAH: packid = PACK_TEMPLE_PTAH; break;
    case BUILDING_TEMPLE_COMPLEX_SETH: packid = PACK_TEMPLE_SETH; break;
    case BUILDING_TEMPLE_COMPLEX_BAST: packid = PACK_TEMPLE_BAST; break;
        break;
    }

    int flooring_image_id = image_id_from_group(packid, 4);
    int statue1_image_id = image_id_from_group(packid, 5);
    int statue2_image_id = image_id_from_group(packid, 6);

    int EMPTY______ = 0;

    // floor tiles
    int til_0 = flooring_image_id + 0;
    int til_1 = flooring_image_id + 1;
    int til_2 = flooring_image_id + 2;
    int til_3 = flooring_image_id + 3;

    // small (1x1) statues
    int smst0 = statue1_image_id + (4 - city_view_orientation() / 2) % 4; // north
    int smst1 = statue1_image_id + (5 - city_view_orientation() / 2) % 4; // east
    int smst2 = statue1_image_id + (6 - city_view_orientation() / 2) % 4; // south
    int smst3 = statue1_image_id + (7 - city_view_orientation() / 2) % 4; // west

    // long (1x2) statues
    int lst0B = statue2_image_id + (8 - city_view_orientation()) % 8; // north
    int lst0A = statue2_image_id + (9 - city_view_orientation()) % 8;
    int lst1B = statue2_image_id + (10 - city_view_orientation()) % 8; // east
    int lst1A = statue2_image_id + (11 - city_view_orientation()) % 8;
    int lst2B = statue2_image_id + (12 - city_view_orientation()) % 8; // south
    int lst2A = statue2_image_id + (13 - city_view_orientation()) % 8;
    int lst3B = statue2_image_id + (14 - city_view_orientation()) % 8; // west
    int lst3A = statue2_image_id + (15 - city_view_orientation()) % 8;

    // correct long statues graphics for relative orientation
    switch (city_view_orientation() / 2) {
    case 1:
    case 0:
        lst1A = statue2_image_id + (10 - city_view_orientation()) % 8; // east
        lst1B = statue2_image_id + (11 - city_view_orientation()) % 8;
        lst3A = statue2_image_id + (14 - city_view_orientation()) % 8; // west
        lst3B = statue2_image_id + (15 - city_view_orientation()) % 8;
        break;
    }
    switch (city_view_orientation() / 2) {
    case 3:
    case 0:
        lst0A = statue2_image_id + (8 - city_view_orientation()) % 8; // north
        lst0B = statue2_image_id + (9 - city_view_orientation()) % 8;
        lst2A = statue2_image_id + (12 - city_view_orientation()) % 8; // south
        lst2B = statue2_image_id + (13 - city_view_orientation()) % 8;
        break;
    }

    // adjust northern tile offset
    switch (orientation) {
    case 0: // NE
        north_tile.shift(-2, -10);
        //            north_tile.x -= 2;
        //            north_tile.y -= 10;
        break;
    case 1: // SE
        north_tile.shift(0, -2);
        //            north_tile.y -= 2;
        break;
    case 2: // SW
        north_tile.shift(-2, 0);
        //            north_tile.x -= 2;
        break;
    case 3: // NW
        north_tile.shift(-10, -2);
        //            north_tile.x -= 10;
        //            north_tile.y -= 2;
        break;
    }

    // first, add base tiles
    switch (orientation) {
    case 0:
    { // NE
        int TEMPLE_COMPLEX_SCHEME[13][7] = {
          {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
          {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
          {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
          {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
          {til_0, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, til_0},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {til_1, til_1, EMPTY______, EMPTY______, EMPTY______, til_1, til_1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {til_1, til_1, EMPTY______, EMPTY______, EMPTY______, til_1, til_1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
        };
        for (int row = 0; row < 13; row++) {
            for (int column = 0; column < 7; column++)
                map_image_set(north_tile.shifted(column, row), TEMPLE_COMPLEX_SCHEME[row][column]);
        }
        break;
    }
    case 1:
    { // SE
        int TEMPLE_COMPLEX_SCHEME[7][13] = {
          {smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0, til_0, til_2, til_3, til_2, til_3},
          {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst2B, lst2B, lst2B},
          {EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, til_0, lst2A, lst2A, lst2A},
          {EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, til_1, til_1, til_1, til_1},
          {EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, til_0, lst0B, lst0B, lst0B},
          {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst0A, lst0A, lst0A},
          {smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2, til_0, til_2, til_3, til_2, til_3},
        };
        for (int row = 0; row < 7; row++) {
            for (int column = 0; column < 13; column++)
                map_image_set(north_tile.shifted(column, row), TEMPLE_COMPLEX_SCHEME[row][column]);
        }
        break;
    }
    case 2:
    { // SW
        int TEMPLE_COMPLEX_SCHEME[13][7] = {
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {til_1, til_1, EMPTY______, EMPTY______, EMPTY______, til_1, til_1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {til_1, til_1, EMPTY______, EMPTY______, EMPTY______, til_1, til_1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {smst3, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, smst1},
          {til_0, til_0, EMPTY______, EMPTY______, EMPTY______, til_0, til_0},
          {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
          {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
          {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
          {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
        };
        for (int row = 0; row < 13; row++) {
            for (int column = 0; column < 7; column++)
                map_image_set(north_tile.shifted(column, row), TEMPLE_COMPLEX_SCHEME[row][column]);
        }
        break;
    }
    case 3:
    { // NW
        int TEMPLE_COMPLEX_SCHEME[7][13] = {
          {til_3, til_2, til_3, til_2, til_0, smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0},
          {lst2B, lst2B, lst2B, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
          {lst2A, lst2A, lst2A, til_0, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______},
          {til_1, til_1, til_1, til_1, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______},
          {lst0B, lst0B, lst0B, til_0, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______, EMPTY______},
          {lst0A, lst0A, lst0A, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
          {til_3, til_2, til_3, til_2, til_0, smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2},
        };
        for (int row = 0; row < 7; row++) {
            for (int column = 0; column < 13; column++)
                map_image_set(north_tile.shifted(column, row), TEMPLE_COMPLEX_SCHEME[row][column]);
        }
        break;
    }
    }
}

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_osiris);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_ra);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_ptah);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_seth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_bast);

void building_temple_complex::on_create(int orientation) {
    runtime_data().variant = (10 - (2 * orientation)) % 8; // ugh!
    g_city.buildings.track_building(base, false);
}

void building_temple_complex::on_post_load() {
    const bool is_active = num_workers() > 0;
    g_city.buildings.track_building(base, is_active);
}

building *add_temple_complex_element(tile2i tile, e_building_type type, int orientation, building *prev) {
    building *b = building_create(type, tile, orientation);
    game_undo_add_building(b);

    b->size = 3;
    b->prev_part_building_id = prev->id;
    prev->next_part_building_id = b->id;
    int image_id = map_image_at(tile);
    map_building_tiles_add(b->id, b->tile, 3, image_id, TERRAIN_BUILDING);

    return b;
}

void building_temple_complex::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    g_city_planner.add_building_tiles_from_list(id(), false);

    tile2i offset = building_part_offset(orientation, 3);

    building *altar = add_temple_complex_element(tile().shifted(offset), BUILDING_TEMPLE_COMPLEX_ALTAR, orientation, &base);
    building *oracle = add_temple_complex_element(tile().shifted(offset * 2), BUILDING_TEMPLE_COMPLEX_ORACLE, orientation, altar);
}

void building_temple_complex::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_UINT8, &d.temple_complex_upgrades);
    iob->bind(BIND_SIGNATURE_UINT8, &d.variant);
}

bool building_temple_complex::has_upgrade(e_building_type btype) const {
    switch (btype) {
    case BUILDING_TEMPLE_COMPLEX_ALTAR: return has_upgrade(etc_upgrade_altar);
    case BUILDING_TEMPLE_COMPLEX_ORACLE: return has_upgrade(etc_upgrade_oracle);
    default:
        verify_no_crash(false);
        break;
    }
    return false;
}

building *building_temple_complex::get_altar() const {
    building *next = base.next();
    while (next) {
        if (next->type == BUILDING_TEMPLE_COMPLEX_ALTAR) {
            break;
        }
        next = next->next();
    }

    return next;
}

building *building_temple_complex::get_oracle() const {
    building *next = base.next();
    while (next) {
        if (next->type == BUILDING_TEMPLE_COMPLEX_ORACLE) {
            break;
        }
        next = next->next();
    }

    return next;
}

building *building_temple_complex::get_upgrade(e_building_type type) const {
    if (type == BUILDING_TEMPLE_COMPLEX_ALTAR) {
        return get_altar();
    } 
    
    if (type == BUILDING_TEMPLE_COMPLEX_ORACLE) {
        return get_oracle();
    } 

    return &base;
}

void building_temple_complex::update_map_orientation(int orientation) {
    if (!is_main()) {
        return;
    }

    // first, add the base tiles
    orientation = (5 - (runtime_data().variant / 2)) % 4;
    map_add_temple_complex_base_tiles(type(), tile(), orientation);
    // then, the main building parts
    // map_building_tiles_add_temple_complex_parts(&base);
    building *building_main = &main()->base;
    if (building_main) {
        int city_orientation = city_view_orientation() / 2;
        int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
        pcstr orient_key[] = { "main_n", "main_e", "main_s", "main_w" };
        int image_id = anim(orient_key[orientation]).first_img();
        map_building_tiles_add(id(), tile(), current_params().building_size, image_id, TERRAIN_BUILDING);
    }

    building *altar = get_altar();
    if (altar) {
        altar->dcast()->update_map_orientation(orientation);
    }

    building *oracle = get_oracle();
    if (oracle) {
        oracle->dcast()->update_map_orientation(orientation);
    }
}

void building_temple_complex::update_count() const {
    const bool is_active = num_workers() > 0;
    g_city.buildings.track_building(base, is_active);
}
