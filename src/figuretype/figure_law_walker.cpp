#include "figure_law_walker.h"

#include "building/building.h"
#include "city/city_figures.h"
#include "grid/road_access.h"

void figure_law_walker::figure_before_action() {
    building* h = home();
    if (h->state != BUILDING_STATE_VALID || !h->has_figure(0, id())) {
        poof();
    }
}

void figure_law_walker::acquire_attack() {
    base.set_flag(e_figure_flag_inattack);
}

tile2i figure_law_walker::home_road() const {
    const building* h = home();
    return map_closest_road_within_radius(h->tile, h->size, home_road_radius());
}

void figure_law_walker::return_home() {
    const tile2i road = home_road();
    if (!road.valid()) {
        poof();
        return;
    }
    advance_action(ACTION_73_LAW_WALKER_RETURNING);
    base.destination_tile = road;
    route_remove();
}

void figure_law_walker::law_walker_action() {
    base.terrain_usage = TERRAIN_USAGE_ROADS;

    auto& d = runtime_data();
    const bool wrapped = ++d.walk_frame >= LAW_WALKER_ANIMATION_FRAMES;
    if (wrapped) {
        d.walk_frame = 0;
    }
    on_walk_cycle(wrapped);

    if (base.in_attack()) {
        on_attack_tick();
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_76_LAW_WALKER_CHASE:
        law_walker_chase();
        break;

    case ACTION_70_LAW_WALKER_CREATED:
        d.walk_frame = 0;
        if (--base.wait_ticks > 0) {
            break;
        }
        if (!home_road().valid()) {
            poof();
            break;
        }
        advance_action(ACTION_72_LAW_WALKER_ROAMING);
        base.roam_length = 0;
        break;

    case ACTION_71_LAW_WALKER_ENTERING_EXITING:
        do_enterbuilding(true, home());
        break;

    case ACTION_72_LAW_WALKER_ROAMING:
        if (++base.roam_length >= base.max_roam_length) {
            return_home();
        }
        base.roam_ticks(base.speed_multiplier);
        break;

    case ACTION_73_LAW_WALKER_RETURNING:
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        } else if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_71_LAW_WALKER_ENTERING_EXITING);
            base.destination_tile = home()->tile;
            base.roam_length = 0;
        }
        break;

    default:
        advance_action(ACTION_70_LAW_WALKER_CREATED);
        break;
    }
}

void figure_law_walker::law_walker_chase() {
    base.terrain_usage = TERRAIN_USAGE_ANY;
    if (!base.target_is_alive()) {
        return_home();
        base.roam_length = 0;
    }

    base.move_ticks(base.speed_multiplier);
    if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        poof();
    } else if (direction() == DIR_FIGURE_NONE) {
        base.destination_tile = figure_get(base.target_figure_id)->tile;
        route_remove();
    }
}

void figure_law_walker::update_animation() {
    figure_impl::update_animation();

    xstring anim_key = animkeys().walk;
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        anim_key = animkeys().death;
    } else if (base.in_attack()) {
        anim_key = animkeys().attack;
    }

    image_set_animation(anim_key);
}
