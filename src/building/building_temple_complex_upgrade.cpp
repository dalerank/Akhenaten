#include "building_temple_complex_upgrade.h"

#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "graphics/view/lookup.h"
#include "construction/build_planner.h"
#include "city/city_buildings.h"
#include "building/building_temple_complex.h"
#include "building/rotation.h"

building_temple_complex_altar::static_params building_temple_complex_altar_m;
building_temple_complex_oracle::static_params building_temple_complex_oracle_m;

buildings::model_t<building_temple_complex_altar_ra> temple_complex_altar_ra;

template<typename T>
void building_temple_complex_upgrade::static_params_t<T>::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    int city_orientation = city_view_orientation() / 2;
    int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
    pcstr orienation_key_fancy[] = { "fancy_n", "fancy_e", "fancy_s", "fancy_w" };
    int image_id = this->first_img(orienation_key_fancy[orientation]);
    auto complex = building_at_ex<building_temple_complex>(end);
    if (!complex) {
        return;
    }
    building *upgrade_base = complex->get_upgrade(this->TYPE);

    tile2i offset = { 0, 0 };
    int bsize = this->building_size - 1;
    switch (city_orientation) {
    case 0: offset = { 0, bsize }; break;
    case 1: offset = { 0, 0 }; break;
    case 2: offset = { bsize, 0 }; break;
    case 3: offset = { bsize, bsize }; break;
    }

    vec2i pixel_upgrade = lookup_tile_to_pixel(upgrade_base->tile.shifted(offset));
    planer.draw_building_ghost(ctx, image_id, pixel_upgrade);
}

void building_temple_complex_upgrade::update_map_orientation(int _) {
    int city_orientation = city_view_orientation() / 2;
    int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
    auto complex = ::smart_cast<building_temple_complex*>(main());
    pcstr orienation_key_base[] = { "base_n", "base_e", "base_s", "base_w" };
    pcstr orienation_key_fancy[] = { "fancy_n", "fancy_e", "fancy_s", "fancy_w" };
    pcstr *orientation_key = complex->has_upgrade(type()) ? orienation_key_fancy : orienation_key_base;
    int image_id = anim(orientation_key[orientation]).first_img() ;
    map_building_tiles_add(id(), tile(), 3, image_id, TERRAIN_BUILDING);
}

void building_temple_complex_oracle::on_place_checks() {
    // nothhing
}
