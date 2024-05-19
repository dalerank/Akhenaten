#include "building_gatehouse.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"

buildings::model_t<building_brick_gatehouse> brick_gatehouse_m;
buildings::model_t<building_mud_gatehouse> mud_gatehouse_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_raw_materials);
void config_load_building_raw_materials() {
    brick_gatehouse_m.load();
    mud_gatehouse_m.load();
}

void building_gatehouse::on_create(int orientation) {
    base.subtype.orientation = orientation;
}

void building_gatehouse::on_place(int orientation, int variant) {
    const auto &p = building_impl::params(type());
    map_building_tiles_add(id(), tile(), p.building_size, p.anim["base"].first_img() + orientation, TERRAIN_BUILDING | TERRAIN_GATEHOUSE);
    map_terrain_add_gatehouse_roads(tilex(), tiley(), orientation);
}
