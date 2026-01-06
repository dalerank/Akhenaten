#include "building_temple_complex_upgrade.h"

#include "graphics/view/view.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "graphics/view/lookup.h"
#include "construction/build_planner.h"
#include "city/city_buildings.h"
#include "building/building_temple_complex.h"
#include "building/rotation.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_altar_amon);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_oracle_thoth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_altar_anubis);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_oracle_sekhmet);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_altar_sebek);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_oracle_min);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_altar_maat);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_oracle_horus);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_altar_isis);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_complex_oracle_hathor);

void building_temple_complex_altar::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);

    int city_orientation = city_view_orientation() / 2;
    int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
    pcstr orienation_key_fancy[] = { "fancy_n", "fancy_e", "fancy_s", "fancy_w" };

    int image_id = params.first_img(orienation_key_fancy[orientation]);
    auto complex = building_at_ex<building_temple_complex>(end);
    building *upgrade_base = complex ? complex->get_altar() : nullptr;
    if (!upgrade_base) {
        return;
    }

    tile2i offset = { 0, 0 };
    int bsize = params.building_size - 1;
    switch (city_orientation) {
    case 0: offset = { 0, bsize }; break;
    case 1: offset = { 0, 0 }; break;
    case 2: offset = { bsize, 0 }; break;
    case 3: offset = { bsize, bsize }; break;
    }

    vec2i pixel_upgrade = lookup_tile_to_pixel(upgrade_base->tile.shifted(offset));
    planer.draw_building_ghost(ctx, image_id, pixel_upgrade);
}

int building_temple_complex_altar::preview::construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const {
    auto complex = building_at(end)->main()->dcast_temple_complex();
    if (!complex) {
        return false;
    }

    const bool upgrade_exists = complex->has_upgrade(etc_upgrade_altar);
    if (upgrade_exists) {
        return false;
    }

    complex->build_upgrade(etc_upgrade_altar, p.build_type);
    return true;
}

void building_temple_complex_oracle::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);

    int city_orientation = city_view_orientation() / 2;
    int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
    pcstr orienation_key_fancy[] = { "fancy_n", "fancy_e", "fancy_s", "fancy_w" };

    int image_id = params.first_img(orienation_key_fancy[orientation]);
    auto complex = building_at_ex<building_temple_complex>(end);
    building *upgrade_base = complex ? complex->get_oracle() : nullptr;
    if (!upgrade_base) {
        return;
    }

    tile2i offset = { 0, 0 };
    int bsize = params.building_size - 1;
    switch (city_orientation) {
    case 0: offset = { 0, bsize }; break;
    case 1: offset = { 0, 0 }; break;
    case 2: offset = { bsize, -(bsize + params.building_size + 1) }; break;
    case 3: offset = { bsize, -(bsize + params.building_size - 1) }; break;
    }

    vec2i pixel_upgrade = lookup_tile_to_pixel(upgrade_base->tile.shifted(offset));
    planer.draw_building_ghost(ctx, image_id, pixel_upgrade);
}

int building_temple_complex_oracle::preview::construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const {
    auto complex = building_at(end)->main()->dcast_temple_complex();
    if (!complex) {
        return false;
    }

    const bool upgrade_exists = complex->has_upgrade(etc_upgrade_oracle);
    if (upgrade_exists) {
        return false;
    }

    complex->build_upgrade(etc_upgrade_oracle, p.build_type);
    return true;
}

void building_temple_complex_altar::update_map_orientation(int _) {
    int city_orientation = city_view_orientation() / 2;
    int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
    auto complex = ::smart_cast<building_temple_complex *>(main());
    pcstr orienation_key_base[] = { "base_n", "base_e", "base_s", "base_w" };
    pcstr orienation_key_fancy[] = { "fancy_n", "fancy_e", "fancy_s", "fancy_w" };

    const bool is_altar = current_params().needs.altar;
    pcstr *orientation_key = complex->has_upgrade(etc_upgrade_altar) ? orienation_key_fancy : orienation_key_base;
    
    int image_id = anim(orientation_key[orientation]).first_img();
    map_building_tiles_add(id(), tile(), 3, image_id, TERRAIN_BUILDING);
}

void building_temple_complex_oracle::update_map_orientation(int _) {
    int city_orientation = city_view_orientation() / 2;
    int orientation = (building_rotation_global_rotation() + city_orientation) % 4;
    auto complex = ::smart_cast<building_temple_complex *>(main());
    pcstr orienation_key_base[] = { "base_n", "base_e", "base_s", "base_w" };
    pcstr orienation_key_fancy[] = { "fancy_n", "fancy_e", "fancy_s", "fancy_w" };
    pcstr *orientation_key = complex->has_upgrade(etc_upgrade_oracle) ? orienation_key_fancy : orienation_key_base;

    if (orientation == 2 || orientation == 3) {
        orientation_key = orienation_key_base;
    }

    int image_id = anim(orientation_key[orientation]).first_img();
    map_building_tiles_add(id(), tile(), 3, image_id, TERRAIN_BUILDING);
}

void building_temple_complex_oracle::on_place_checks() {
    // nothhing
}
