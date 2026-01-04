#include "building_static_params.h"

#include "grid/building.h"
#include "city/city_labor.h"
#include "city/buildings.h"
#include "graphics/view/view.h"
#include "building/building.h"
#include "graphics/image.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "building/construction/build_planner.h"

void building_static_params::archive_unload() {
}

void building_static_params::initialize() {
    if (production_rate == 0) production_rate = 100;
    if (min_houses_coverage == 0) min_houses_coverage = 100;
    if (max_storage_amount == 0) max_storage_amount = 200;

    city_labor_t::set_category(type, labor_category);
}

void add_building(building *b, int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    const auto &params = b->params();
    switch (b->type) {
        // houses
    case BUILDING_HOUSE_STURDY_HUT:
    case BUILDING_HOUSE_MEAGER_SHANTY:
    case BUILDING_HOUSE_COMMON_SHANTY:
    case BUILDING_HOUSE_ROUGH_COTTAGE:
    case BUILDING_HOUSE_ORDINARY_COTTAGE:
    case BUILDING_HOUSE_MODEST_HOMESTEAD:
    case BUILDING_HOUSE_SPACIOUS_HOMESTEAD:
    case BUILDING_HOUSE_MODEST_APARTMENT:
    case BUILDING_HOUSE_SPACIOUS_APARTMENT:
    case BUILDING_HOUSE_COMMON_RESIDENCE:
    case BUILDING_HOUSE_SPACIOUS_RESIDENCE:
    case BUILDING_HOUSE_ELEGANT_RESIDENCE:
    case BUILDING_HOUSE_FANCY_RESIDENCE:
    case BUILDING_HOUSE_COMMON_MANOR:
    case BUILDING_HOUSE_SPACIOUS_MANOR:
    case BUILDING_HOUSE_ELEGANT_MANOR:
    case BUILDING_HOUSE_STATELY_MANOR:
    case BUILDING_HOUSE_MODEST_ESTATE:
    case BUILDING_HOUSE_PALATIAL_ESTATE: {
            int image_id = params.animations["house"].first_img();
            map_building_tiles_add(b->id, b->tile, b->size, image_id, TERRAIN_BUILDING);
        }
        break;

    case BUILDING_RESERVED_TRIUMPHAL_ARCH_56: {
            int image_id = image_id_from_group(GROUP_BUILDING_TRIUMPHAL_ARCH) + orientation - 1;
            map_building_tiles_add(b->id, b->tile, b->size, image_id, TERRAIN_BUILDING);
            map_terrain_add_triumphal_arch_roads(b->tile.x(), b->tile.y(), orientation);
            city_buildings_build_triumphal_obelisk();
            g_city_planner.reset();
        }
        break;

    default:
        b->dcast()->on_place(orientation, variant);
        break;
    }
}



uint16_t building_static_params::get_cost() const {
    const uint16_t mcost = this->cost.get();
    return mcost;
}