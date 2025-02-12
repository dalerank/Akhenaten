#include "building_temple_complex.h"

#include "city/city.h"
#include "game/undo.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "building/rotation.h"
#include "graphics/view/lookup.h"
#include "construction/build_planner.h"

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

template<class T>
void building_temple_complex::static_params_t<T>::load(archive arch) {
}

template<class T>
int building_temple_complex::static_params_t<T>::planer_setup_orientation(int orientation) const { 
    return 1;
}

template<class T>
int building_temple_complex::static_params_t<T>::planer_update_relative_orientation(build_planner &p, int global_rotation) const {
    return global_rotation + 1;
}

template<class T>
void building_temple_complex::static_params_t<T>::planer_setup_preview_graphics(build_planner &planer) const {
    int packid = -1;
    switch (this->TYPE) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS: packid = PACK_TEMPLE_NILE; break;
    case BUILDING_TEMPLE_COMPLEX_RA: packid = PACK_TEMPLE_RA; break;
    case BUILDING_TEMPLE_COMPLEX_PTAH: packid = PACK_TEMPLE_PTAH; break;
    case BUILDING_TEMPLE_COMPLEX_SETH: packid = PACK_TEMPLE_SETH; break;
    case BUILDING_TEMPLE_COMPLEX_BAST: packid = PACK_TEMPLE_BAST; break;
        break;
    }

    int main_image_id = image_id_from_group(packid, 1);
    int oracle_image_id = image_id_from_group(packid, 2);
    int altar_image_id = image_id_from_group(packid, 3);
    int flooring_image_id = image_id_from_group(packid, 4);
    int statue1_image_id = image_id_from_group(packid, 5);
    int statue2_image_id = image_id_from_group(packid, 6);

    int EMPTY = 0;
    int mn_1A = main_image_id;
    int mn_1B = main_image_id + 3;
    int mn_2A = oracle_image_id;
    int mn_2B = oracle_image_id + 3;
    int mn_3A = altar_image_id;
    int mn_3B = altar_image_id + 3;

    int til_0 = flooring_image_id + 0;
    int til_1 = flooring_image_id + 1;
    int til_2 = flooring_image_id + 2;
    int til_3 = flooring_image_id + 3;

    int smst0 = statue1_image_id + 0; // north
    int smst1 = statue1_image_id + 1; // east
    int smst2 = statue1_image_id + 2; // south
    int smst3 = statue1_image_id + 3; // west

    int lst0A = statue2_image_id + 0; // north
    int lst0B = statue2_image_id + 1;
    int lst1A = statue2_image_id + 2; // east
    int lst1B = statue2_image_id + 3;
    int lst2A = statue2_image_id + 4; // south
    int lst2B = statue2_image_id + 5;
    int lst3A = statue2_image_id + 6; // west
    int lst3B = statue2_image_id + 7;

    switch (planer.relative_orientation) {
    case 0:
        { // NE
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
                {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
                {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
                {til_0, til_0, EMPTY, EMPTY, EMPTY, til_0, til_0},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {smst3, til_0, mn_1B, EMPTY, EMPTY, til_0, smst1},
                {til_1, til_1, EMPTY, EMPTY, EMPTY, til_1, til_1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {smst3, til_0, mn_2B, EMPTY, EMPTY, til_0, smst1},
                {til_1, til_1, EMPTY, EMPTY, EMPTY, til_1, til_1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {smst3, til_0, mn_3B, EMPTY, EMPTY, til_0, smst1},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(7, 13));
            planer.pivot = { 2, 10 };
        }
        break;

    case 1:
        { // SE
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
                {smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0, til_0, til_2, til_3, til_2, til_3},
                {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst2B, lst2B, lst2B},
                {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, til_0, lst2A, lst2A, lst2A},
                {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, til_1, til_1, til_1, til_1},
                {mn_1A, EMPTY, EMPTY, mn_2A, EMPTY, EMPTY, mn_3A, EMPTY, EMPTY, til_0, lst0B, lst0B, lst0B},
                {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst0A, lst0A, lst0A},
                {smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2, til_0, til_2, til_3, til_2, til_3},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(13, 7));
            planer.pivot = { 0, 2 };
        }
        break;

    case 2:
        { // SW
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {til_1, til_1, mn_1B, EMPTY, EMPTY, til_1, til_1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {til_1, til_1, mn_2B, EMPTY, EMPTY, til_1, til_1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                {til_0, til_0, mn_3B, EMPTY, EMPTY, til_0, til_0},
                {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
                {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
                {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(7, 13));
            planer.pivot = { 2, 0 };
        }
    break;

    case 3:
        { // NW
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
                {til_3, til_2, til_3, til_2, til_0, smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0},
                {lst2B, lst2B, lst2B, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
                {lst2A, lst2A, lst2A, til_0, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                {til_1, til_1, til_1, til_1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                {lst0B, lst0B, lst0B, til_0, mn_1A, EMPTY, EMPTY, mn_2A, EMPTY, EMPTY, mn_3A, EMPTY, EMPTY},
                {lst0A, lst0A, lst0A, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
                {til_3, til_2, til_3, til_2, til_0, smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(13, 7));
            planer.pivot = { 10, 2 };
        }
        break;
    }
}

void building_temple_complex_altar::static_params::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    int city_orientation = city_view_orientation() / 2;
    int orientation = (1 + building_rotation_global_rotation() + city_orientation) % 2;
    int image_id = anim[animkeys().base].first_img() + orientation;
    auto complex = building_at_ex<building_temple_complex>(end);
    if (complex) {
        building *altar = complex->get_altar();

        tile2i offset = { 0, 0 };
        int bsize = building_size - 1;
        switch (city_orientation) {
        case 0: offset = { 0, bsize }; break;
        case 1: offset = { 0, 0 }; break;
        case 2: offset = { bsize, 0 }; break;
        case 3: offset = { bsize, bsize }; break;
        }

        vec2i pixel_altar = tile_to_pixel(altar->tile.shifted(offset));
        planer.draw_building_ghost(ctx, image_id, pixel_altar);
    }
}

building_temple_complex_osiris::static_params building_temple_complex_osiris_m;
building_temple_complex_ra::static_params building_temple_complex_ra_m;
building_temple_complex_ptah::static_params building_temple_complex_ptah_m;
building_temple_complex_seth::static_params building_temple_complex_seth_m;
building_temple_complex_bast::static_params building_temple_complex_bast_m;
building_temple_complex_altar::static_params building_temple_complex_altar_m;

void building_temple_complex::on_create(int orientation) {
    data.monuments.variant = (10 - (2 * orientation)) % 8; // ugh!
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
    g_city_planner.add_building_tiles_from_list(id(), false);

    tile2i offset = building_part_offset(orientation, 3);

    building *altar = add_temple_complex_element(tile().shifted(offset), BUILDING_TEMPLE_COMPLEX_ALTAR, orientation, &base);
    building *oracle = add_temple_complex_element(tile().shifted(offset * 2), BUILDING_TEMPLE_COMPLEX_ORACLE, orientation, altar);
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

void building_temple_complex::update_count() const {
    const bool is_active = num_workers() > 0;
    g_city.buildings.track_building(base, is_active);
}
