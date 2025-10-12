#include "building_statue.h"

#include "building/building.h"
#include "building/rotation.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "core/svector.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "io/io_buffer.h"
#include "window/window_building_info.h"
#include "construction/build_planner.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_statue);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_statue);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_statue);

template<typename T>
const building_statue::statue_params_t &statue_static_params(const building_static_params& params) {
    using static_params = typename T::static_params;
    const auto& bparams = (const static_params &)params;
    return (const building_statue::statue_params_t &)bparams;
}

int building_statue::get_image(e_building_type type, int orientation, int variant) {
    const auto &params = building_static_params::get(type);

    auto get_statue_params = [&] {
        switch(type) {
        case BUILDING_SMALL_STATUE: return statue_static_params<building_small_statue>(params);
        case BUILDING_MEDIUM_STATUE: return statue_static_params<building_medium_statue>(params);
        case BUILDING_LARGE_STATUE: return statue_static_params<building_large_statue>(params);
        }

        static building_statue::statue_params_t dummy;
        return dummy;
    };
    const auto &statue_params = get_statue_params();

    int image_id = 0;

    int size = statue_params.variants.size();

    if (!size) {
        return 0;
    }
    //
    while (orientation < 0) { orientation += 4; }
    //
    while (orientation > 3) { orientation -= 4; }

    while (variant < 0) { variant += 4; }

    while (variant > (size - 1)) { variant -= size; }

    variant %= size;
    return image_group(statue_params.variants[variant]);
}

void building_statue::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    int statue_img = get_image(planer.build_type, planer.relative_orientation, planer.building_variant);
    planer.set_tiles_building(statue_img, params.building_size);
}

template<typename T>
int building_statue::static_params_t<T>::planer_setup_building_variant(e_building_type type, tile2i tile, int variant) const {
    assert(building_is_statue(type));
    int size = this->variants.size();

    return rand() % size;
}

template<typename T>
int building_statue::static_params_t<T>::planer_next_building_variant(e_building_type type, tile2i tile, int variant) const {
    if (variant < 0) {
        return 0;
    }

    int size = this->variants.size();
    if (!size) {
        return variant;
    }

    variant = (variant + 1) % size;
    return variant;
}

template<class T>
int building_statue::static_params_t<T>::planer_update_relative_orientation(build_planner &p, tile2i tile, int global_rotation) const {
    return global_rotation + 1;;
}

template<class T>
int building_statue::static_params_t<T>::planer_update_building_variant(build_planner &planer) const {
    return planer.custom_building_variant; 
}

void building_statue::on_create(int o) {
    int orientation = (4 + building_rotation_global_rotation() + city_view_orientation() / 2) % 4;

    auto &d = runtime_data();
    d.variant = g_city_planner.building_variant;
    d.statue_offset = rand() % 4;
}

void building_statue::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);

    int image_id = get_image(type(), orientation_rel, variant);
    map_building_tiles_add(id(), tile(), size(), image_id, TERRAIN_BUILDING);
}

void building_statue::on_place_checks() {
    /*nothing*/
}

void building_statue::update_map_orientation(int map_orientation) {
    int variant = runtime_data().variant;
    int combined = 0;

    int orientation = combined % 4 - (map_orientation / 2);
    int image_id = get_image(type(), orientation - 1, variant);
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

void building_statue::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind____skip(10);
    iob->bind(BIND_SIGNATURE_UINT8, &d.service);
    iob->bind(BIND_SIGNATURE_UINT8, &d.statue_offset);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &d.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.resources_pct[i]);
    }
}

void building_statue::add_workers(figure_id fid) {
    base.set_figure(0, fid);
}

void building_statue::update_day() {
    building_impl::update_day();

    auto &d = runtime_data();
    if (d.service > 0) {
        d.service--;
    }
}
