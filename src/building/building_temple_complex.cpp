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
    int EMPTY = 0;
    int main_n = this->anim["main_n"].first_img();
    int main_w = this->anim["main_w"].first_img();
    int oracle_n = this->anim["oracle_n"].first_img();
    int oracle_e = this->anim["oracle_w"].first_img();
    int altar_n = this->anim["altar_n"].first_img();
    int altar_w = this->anim["altar_w"].first_img();

    int tiles_0 = this->anim["tiles_0"].first_img();
    int tiles_1 = this->anim["tiles_1"].first_img();
    int tiles_2 = this->anim["tiles_2"].first_img();
    int tiles_3 = this->anim["tiles_3"].first_img();

    int statue1_image_id = this->anim["statue_1"].first_img();
    int statue_0 = statue1_image_id + 0; // north
    int statue_1 = statue1_image_id + 1; // east
    int statue_2 = statue1_image_id + 2; // south
    int statue_3 = statue1_image_id + 3; // west

    int statue2n = this->anim["statue_2n"].first_img();
    int statue_2n_F = statue2n + 0; // north
    int statue_2n_B = statue2n + 1;
    int statue2e = this->anim["statue_2e"].first_img();
    int statue_2e_A = statue2e + 0; // east
    int statue_2e_B = statue2e + 1;
    int statue2s = this->anim["statue_2s"].first_img();
    int statue_2s_A = statue2s + 0; // south
    int statue_2s_B = statue2s + 1;
    int statue2w = this->anim["statue_2w"].first_img();
    int statue_2w_A = statue2w + 0; // west
    int statue_2w_B = statue2w + 1;

    switch (planer.relative_orientation) {
    case 0:
        { // NE
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
                {tiles_3, statue_2e_A, statue_2e_B, tiles_1, statue_2w_A, statue_2w_B, tiles_3},
                {tiles_2, statue_2e_A, statue_2e_B, tiles_1, statue_2w_A, statue_2w_B, tiles_2},
                {tiles_3, statue_2e_A, statue_2e_B, tiles_1, statue_2w_A, statue_2w_B, tiles_3},
                {tiles_2, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_2},
                {tiles_0, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, tiles_0},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {statue_3, tiles_0, main_w, EMPTY, EMPTY, tiles_0, statue_1},
                {tiles_1, tiles_1, EMPTY, EMPTY, EMPTY, tiles_1, tiles_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {statue_3, tiles_0, oracle_e, EMPTY, EMPTY, tiles_0, statue_1},
                {tiles_1, tiles_1, EMPTY, EMPTY, EMPTY, tiles_1, tiles_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {statue_3, tiles_0, altar_w, EMPTY, EMPTY, tiles_0, statue_1},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(7, 13));
            planer.pivot = { 2, 10 };
        }
        break;

    case 1:
        { // SE
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
                {statue_0, statue_0, tiles_1, statue_0, statue_0, tiles_1, statue_0, statue_0, tiles_0, tiles_2, tiles_3, tiles_2, tiles_3},
                {tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_0, tiles_0, statue_2s_B, statue_2s_B, statue_2s_B},
                {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, tiles_0, statue_2s_A, statue_2s_A, statue_2s_A},
                {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, tiles_1, tiles_1, tiles_1, tiles_1},
                {main_n, EMPTY, EMPTY, oracle_n, EMPTY, EMPTY, altar_n, EMPTY, EMPTY, tiles_0, statue_2n_B, statue_2n_B, statue_2n_B},
                {tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_0, tiles_0, statue_2n_F, statue_2n_F, statue_2n_F},
                {statue_2, statue_2, tiles_1, statue_2, statue_2, tiles_1, statue_2, statue_2, tiles_0, tiles_2, tiles_3, tiles_2, tiles_3},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(13, 7));
            planer.pivot = { 0, 2 };
        }
        break;

    case 2:
        { // SW
            int TEMPLE_COMPLEX_SCHEME[13][7] = {
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {tiles_1, tiles_1, main_w, EMPTY, EMPTY, tiles_1, tiles_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {tiles_1, tiles_1, oracle_e, EMPTY, EMPTY, tiles_1, tiles_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {statue_3, tiles_0, EMPTY, EMPTY, EMPTY, tiles_0, statue_1},
                {tiles_0, tiles_0, altar_w, EMPTY, EMPTY, tiles_0, tiles_0},
                {tiles_2, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_2},
                {tiles_3, statue_2e_A, statue_2e_B, tiles_1, statue_2w_A, statue_2w_B, tiles_3},
                {tiles_2, statue_2e_A, statue_2e_B, tiles_1, statue_2w_A, statue_2w_B, tiles_2},
                {tiles_3, statue_2e_A, statue_2e_B, tiles_1, statue_2w_A, statue_2w_B, tiles_3},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(7, 13));
            planer.pivot = { 2, 0 };
        }
    break;

    case 3:
        { // NW
            int TEMPLE_COMPLEX_SCHEME[7][13] = {
                {tiles_3, tiles_2, tiles_3, tiles_2, tiles_0, statue_0, statue_0, tiles_1, statue_0, statue_0, tiles_1, statue_0, statue_0},
                {statue_2s_B, statue_2s_B, statue_2s_B, tiles_0, tiles_0, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0},
                {statue_2s_A, statue_2s_A, statue_2s_A, tiles_0, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                {tiles_1, tiles_1, tiles_1, tiles_1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                {statue_2n_B, statue_2n_B, statue_2n_B, tiles_0, main_n, EMPTY, EMPTY, oracle_n, EMPTY, EMPTY, altar_n, EMPTY, EMPTY},
                {statue_2n_F, statue_2n_F, statue_2n_F, tiles_0, tiles_0, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0, tiles_1, tiles_0, tiles_0},
                {tiles_3, tiles_2, tiles_3, tiles_2, tiles_0, statue_2, statue_2, tiles_1, statue_2, statue_2, tiles_1, statue_2, statue_2},
            };
            planer.set_graphics_array(make_span((int*)TEMPLE_COMPLEX_SCHEME, std::size(TEMPLE_COMPLEX_SCHEME)), vec2i(13, 7));
            planer.pivot = { 10, 2 };
        }
        break;
    }
}

template<typename T>
void building_temple_complex_upgrade::static_params_t<T>::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    int city_orientation = city_view_orientation() / 2;
    int orientation = (1 + building_rotation_global_rotation() + city_orientation) % 2;
    int image_id = this->anim[animkeys().base].first_img() + orientation;
    auto complex = building_at_ex<building_temple_complex>(end);
    if (complex) {
        building *upgrade_base = nullptr;
        if (this->TYPE == BUILDING_TEMPLE_COMPLEX_ALTAR) {
            upgrade_base = complex->get_altar();
        } else if (this->TYPE == BUILDING_TEMPLE_COMPLEX_ORACLE) {
            upgrade_base = complex->get_oracle();
        } else {
            upgrade_base = &complex->main()->base;
        }

        tile2i offset = { 0, 0 };
        int bsize = this->building_size - 1;
        switch (city_orientation) {
        case 0: offset = { 0, bsize }; break;
        case 1: offset = { 0, 0 }; break;
        case 2: offset = { bsize, 0 }; break;
        case 3: offset = { bsize, bsize }; break;
        }

        vec2i pixel_upgrade = tile_to_pixel(upgrade_base->tile.shifted(offset));
        planer.draw_building_ghost(ctx, image_id, pixel_upgrade);
    }
}

building_temple_complex_osiris::static_params building_temple_complex_osiris_m;
building_temple_complex_ra::static_params building_temple_complex_ra_m;
building_temple_complex_ptah::static_params building_temple_complex_ptah_m;
building_temple_complex_seth::static_params building_temple_complex_seth_m;
building_temple_complex_bast::static_params building_temple_complex_bast_m;
building_temple_complex_altar::static_params building_temple_complex_altar_m;
building_temple_complex_oracle::static_params building_temple_complex_oracle_m;

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

void building_temple_complex::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(34);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.monuments.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.statue_offset);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.temple_complex_attachments);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.resources_pct[i]);
    }
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

void building_temple_complex::update_count() const {
    const bool is_active = num_workers() > 0;
    g_city.buildings.track_building(base, is_active);
}
