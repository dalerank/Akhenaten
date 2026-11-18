#include "figuretype/figure_plagued_citizen.h"

#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "city/city.h"
#include "city/buildings.h"
#include "city/city_health.h"
#include "figure/figure.h"
#include "figure/service.h"
#include "figuretype/figure_priest.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_plagued_citizen);

namespace {

    bool remake() {
        return !!game_features::gameplay_change_plagued_citizen_remake;
    }

    // OG figure_movement_init_roaming: uses the home's roam direction and turns it clockwise for the next walker.
    void init_roaming(figure& f, building& home) {
        f.init_roaming_from_building(home.figure_roam_direction);
        home.figure_roam_direction += 2;
        if (home.figure_roam_direction > 6) {
            home.figure_roam_direction = 0;
        }
    }

    bool is_bast_priest(figure& f) {
        auto* priest = f.dcast()->dcast_priest();
        const auto* god = priest ? priest->god() : nullptr;
        return god && god->god == GOD_BAST;
    }

    // OG: player->has_temple_complex, complex god Bast, upgrade 1 (altar).
    bool bast_complex_has_altar() {
        building* b = building_get(g_city.buildings.temple_complex_id());
        auto* complex = (b && b->type == BUILDING_TEMPLE_COMPLEX_BAST) ? b->dcast_temple_complex() : nullptr;
        return complex && complex->has_upgrade(etc_upgrade_altar);
    }

} // namespace

void figure_plagued_citizen::on_create() {
    figure_impl::on_create();
    // The walk from the house to the road is off-road; the remake's off-road poof must not end it.
    base.terrain_usage = TERRAIN_USAGE_ANY;
    advance_action(ACTION_8_PLAGUED_CREATED);
}

void figure_plagued_citizen::figure_action() {
    const auto& p = current_params();
    base.max_roam_length = base.wait_ticks;
    building* home = base.home();
    base.set_flag(e_figure_flag_invisible, false);

    switch (action_state()) {
    case ACTION_8_PLAGUED_CREATED: {
        base.set_flag(e_figure_flag_invisible, true);
        const tile2i road = map_closest_road_within_radius(home->tile, home->size, p.road_radius);
        if (!road.valid()) {
            poof();
            break;
        }
        advance_action(ACTION_9_PLAGUED_GOING_TO_ROAD);
        base.set_cross_country_destination(road);
        base.roam_length = 0;
        break;
    }

    case ACTION_9_PLAGUED_GOING_TO_ROAD:
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, true);
        if (base.move_ticks_cross_country(1)) {
            if (map_building_at(tile()) == home->id) {
                poof();
            } else {
                advance_action(ACTION_10_PLAGUED_ROAMING);
                base.terrain_usage = TERRAIN_USAGE_ROADS;
                init_roaming(base, *home);
                base.roam_length = 0;
            }
        }
        break;

    case ACTION_120_PLAGUED_LEGACY_CREATED:
    case ACTION_121_PLAGUED_LEGACY_ROAMING:
        advance_action(ACTION_10_PLAGUED_ROAMING);
        base.terrain_usage = TERRAIN_USAGE_ROADS;
        base.wait_ticks = p.spawn_wait_ticks;
        base.roam_length = 0;
        break;

    case ACTION_10_PLAGUED_ROAMING:
        if (++base.roam_length >= base.max_roam_length) {
            const tile2i road = map_closest_road_within_radius(home->tile, home->size, p.road_radius);
            poof();
            if (road.valid()) {
                break;
            }
        }
        base.roam_ticks(1);
        break;
    }
}

void figure_plagued_citizen::figure_dying_action() {
    // OG plagues.c has no corpse branch: the corpse stays until a herbalist or Bast priest steps on it.
    if (remake()) {
        figure_impl::figure_dying_action();
    }
}

void figure_plagued_citizen::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

void figure_plagued_citizen::main_image_update() {
    if (!action_state(FIGURE_ACTION_149_CORPSE) || remake()) {
        figure_impl::main_image_update();
        return;
    }

    // OG: death group + figure_corpse_offsets[wait_ticks / 2]; rows give the frame from each wait_ticks on.
    uint8_t frame = 0;
    for (const auto& row : current_params().corpse_frames) {
        if (base.wait_ticks < row.wait_ticks) {
            break;
        }
        frame = row.frame;
    }
    base.main_image_id = anim(animkeys().death).first_img() + frame;
}

int figure_plagued_citizen::provide_service() {
    // OG population_extra.c city_health_plague_spread; OG adds no houses to the home's coverage.
    figure_provide_service(tile(), &base, [](building* b, figure*) {
        auto house = b->dcast_house();
        auto main = house ? b->main()->dcast_house() : nullptr;
        if (!main || !house->hsize()) {
            return;
        }
        if (main->house_population() == 0 || main->base.has_plague) {
            return;
        }
        g_city.health.infect_house(main->base);
    });
    return 0;
}

int figure_plagued_citizen::create_at_house(building& house) {
    if (!house.is_valid() || !house.is_main()) {
        return 0;
    }

    figure* f = figure_create(FIGURE_PLAGUED_CITIZEN, house.tile, DIR_0_TOP_RIGHT);
    if (!f || !f->is_alive()) {
        return 0;
    }
    f->wait_ticks = current_params().spawn_wait_ticks;
    f->set_home(house.id);
    f->advance_action(ACTION_8_PLAGUED_CREATED);
    init_roaming(*f, house);
    return f->id;
}

bool figure_plagued_citizen::cure_on_meeting(figure& f, figure& opponent) {
    if (f.type == FIGURE_HERBALIST && opponent.type == FIGURE_PLAGUED_CITIZEN) {
        opponent.poof();
        return true;
    }
    if (f.type == FIGURE_PLAGUED_CITIZEN && opponent.type == FIGURE_HERBALIST) {
        f.poof();
        return true;
    }

    const bool priest_meets = (f.type == FIGURE_PRIEST && opponent.type == FIGURE_PLAGUED_CITIZEN)
                              || (f.type == FIGURE_PLAGUED_CITIZEN && opponent.type == FIGURE_PRIEST);
    if (!priest_meets || !bast_complex_has_altar()) {
        return false;
    }
    if (f.type == FIGURE_PRIEST && is_bast_priest(f)) {
        opponent.poof();
        return true;
    }
    if (opponent.type == FIGURE_PRIEST && is_bast_priest(opponent)) {
        f.poof();
        return true;
    }
    return false;
}

int figure_plagued_citizen::cure_nearby(tile2i tile, int radius) {
    if (!remake()) {
        return 0;
    }

    int cured = 0;
    grid_area area = map_grid_get_area(tile, 1, radius);
    map_grid_area_foreach(area, [&](tile2i t) {
        int fid = map_figure_id_get(t);
        while (fid > 0) {
            figure *f = figure_get(fid);
            int next = f->next_figure;
            if (f->type == FIGURE_PLAGUED_CITIZEN && f->is_alive()) {
                f->poof();
                cured++;
            }
            fid = next;
        }
    });
    return cured;
}
