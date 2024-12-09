#include "building_warship_wharf.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "city/city.h"
#include "building/count.h"

building_warship_wharf::static_params warship_wharf_m;

void building_warship_wharf::static_params::load(archive arch) {
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
    int image_offset = city_view_relative_orientation(data.dock.orientation);
    int image_id = anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

void building_warship_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(100);
    }
}

void building_warship_wharf::update_count() const {
    building_increase_type_count(BUILDING_WARSHIP_WHARF, num_workers() > 0);
}

bool building_warship_wharf::ship_moored() const {
    figure *f = base.get_figure(BUILDING_SLOT_BOAT);
    if (!f->is_valid()) {
        return false;
    }

    const bool moored = f->action_state == FIGURE_ACTION_203_WARSHIP_MOORED;
    return moored;
}

void building_warship_wharf::update_month() {
    building_wharf::update_month();

    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        if (!boat->is_valid()) {
            g_city.buildings.request_warship_boat();
        }
    }
}
