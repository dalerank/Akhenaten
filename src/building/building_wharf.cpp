#include "building_wharf.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "grid/water.h"

buildings::model_t<building_transport_wharf> transport_wharf_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_wharf);
void config_load_building_wharf() {
    transport_wharf_m.load();
}

void building_wharf::on_create(int orientation) {
    data.industry.orientation = orientation;
}

void building_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), transport_wharf_m.building_size, params().anim["base"].first_img() + orientation_rel);
}
