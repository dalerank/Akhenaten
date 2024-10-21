#include "building_warship_wharf.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "grid/water.h"
#include "grid/building_tiles.h"

building_warship_wharf::static_params warship_wharf_m;

void building_warship_wharf::static_params::load(archive arch) {
}

void building_warship_wharf::on_create(int orientation) {
    data.wharf.orientation = orientation;
}

void building_warship_wharf::on_place(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), params().building_size, anim(animkeys().base).first_img() + orientation_rel);

    building_impl::on_place(orientation, variant);
}

void building_warship_wharf::on_place_update_tiles(int orientation, int variant) {
    int img_id = anim(animkeys().base).first_img() + orientation;
    map_water_add_building(id(), tile(), size(), img_id);
}

void building_warship_wharf::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.wharf.orientation);
    int image_id = anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

void building_warship_wharf::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &data.wharf.orientation);
}
