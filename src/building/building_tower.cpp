#include "building_tower.h"

#include "js/js_game.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "grid/tiles.h"
#include "city/labor.h"

buildings::model_t<building_brick_tower> brick_tower_m;
buildings::model_t<building_mud_tower> mud_tower_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_tower);
void config_load_building_tower() {
    brick_tower_m.load();
    mud_tower_m.load();
}

void building_tower::on_create(int orientation) {
    map_terrain_remove_with_radius(tilex(), tiley(), 2, 0, TERRAIN_WALL);
    map_building_tiles_add(id(), tile(), params().building_size, params().anim["base"].first_img(), TERRAIN_BUILDING | TERRAIN_GATEHOUSE);
    map_tiles_update_area_walls(tile(), 5);
}
