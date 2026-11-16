#include "figure_tomb_artisan.h"

#include "building/building_artisans_guild.h"
#include "building/monument_royal_tomb.h"
#include "building/monuments.h"
#include "core/random.h"
#include "game/resource.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tomb_artisan);

bool figure_tomb_artisan::assign_task(building* site, e_resource material) {
    auto& rd = runtime_data();
    set_destination(site);
    rd.destination_bid = site->id;
    rd.delivered_materials = 0;
    rd.delivered_phase = 0xff;
    base.set_resource(material);

    auto* mm = site->dcast_monument();
    base.destination_tile = mm ? mm->access_point() : site->access_tile();
    base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    base.roam_length = 0;
    base.wait_ticks = 0;
    route_remove();
    if (auto* tomb = site->dcast_royal_tomb()) {
        if (!tomb->check_work_for_figure(FIGURE_TOMB_ARTISAN, id(), true)) {
            return false;
        }
    } else if (mm) {
        mm->add_workers(id());
    }
    advance_action(ACTION_11_TOMB_ARTISAN_GOING);
    return true;
}

bool figure_tomb_artisan::try_find_task() {
    // OG roaming artisan looks for a clay or a paint task without checking the guild stock.
    for (e_resource r : {RESOURCE_CLAY, RESOURCE_PAINT}) {
        building* site = building_artisans_guild::find_monument_task(r);
        if (site && assign_task(site, r)) {
            return true;
        }
    }
    return false;
}

void figure_tomb_artisan::figure_action() {
    const auto& params = current_params();
    base.use_cross_country = false;
    base.max_roam_length = params.max_roam_length;

    building *bhome = home();
    if (!bhome || !bhome->is_valid() || bhome->type != BUILDING_ARTISANS_GUILD) {
        poof();
        return;
    }

    auto& rd = runtime_data();
    building* b_dest = building_get(rd.destination_bid);
    if (!rd.destination_bid || !b_dest || !b_dest->is_valid()) {
        b_dest = destination();
    }

    switch (action_state()) {
    case ACTION_20_TOMB_ARTISAN_DESTROY:
        poof();
        break;

    case ACTION_10_TOMB_ARTISAN_CREATED:
        advance_action(ACTION_11_TOMB_ARTISAN_GOING);
        break;

    case ACTION_12_TOMB_ARTISAN_ROAM: {
        base.wait_ticks++;
        const int search_rand = params.task_search_rand > 0 ? (random_short() % params.task_search_rand) : 0;
        if (base.wait_ticks > params.task_search_base + search_rand) {
            try_find_task();
            base.wait_ticks = 0;
        }
        if (action_state() != ACTION_12_TOMB_ARTISAN_ROAM) {
            break;
        }

        base.terrain_usage = TERRAIN_USAGE_ROADS;
        if (++base.roam_length >= base.max_roam_length) {
            tile2i road = map_closest_road_within_radius(*bhome, params.guild_road_radius);
            if (!road.valid()) {
                poof();
                return;
            }
            base.destination_tile = road;
            base.roam_length = 0;
            route_remove();
            advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
        }
        base.roam_ticks(1);
        break;
    }

    case ACTION_11_TOMB_ARTISAN_GOING: {
        // OG ROADS_OR_MONUMENT for a royal tomb is building.guild_worker_terrain ANY in its config.
        const e_terrain_usage terrain
          = (b_dest && b_dest->is_valid())
              ? (e_terrain_usage)building_static_params::get(b_dest->type).guild_worker_terrain
              : TERRAIN_USAGE_PREFER_ROADS;
        if (do_goto(base.destination_tile, terrain, -1, ACTION_12_TOMB_ARTISAN_ROAM)) {
            if (b_dest && b_dest->is_valid() && b_dest->dcast_monument()) {
                advance_action(ACTION_14_TOMB_ARTISAN_WORK);
            } else {
                advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
            }
        }
        if (action_state() != ACTION_11_TOMB_ARTISAN_GOING) {
            base.wait_ticks = 0;
        }
        break;
    }

    case ACTION_14_TOMB_ARTISAN_WORK: {
        if (!b_dest || !b_dest->is_valid()) {
            advance_action(ACTION_12_TOMB_ARTISAN_ROAM);
            base.wait_ticks = 0;
            break;
        }

        if (auto* tomb = b_dest->dcast_royal_tomb()) {
            base.set_flag(e_figure_flag_invisible);
            if (tomb->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                tomb->remove_worker(id());
                advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
            }
            break;
        }

        auto* m = b_dest->dcast_monument();
        if (!m) {
            base.destination_tile = bhome->road_access;
            advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
            break;
        }

        // The guild spent one load at dispatch; credit the monument once for this trip.
        // If the tomb phase advanced after delivery, this load is spent and the artisan leaves.
        const uint8_t ph = m->phase();
        if (rd.delivered_materials && rd.delivered_phase != ph) {
            // Free the monument slot now so the guild can send a fresh load.
            m->remove_worker(base.id);
            advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
            break;
        }
        if (!rd.delivered_materials) {
            const e_resource material = base.get_resource();
            if (material != RESOURCE_NONE) {
                m->deliver_resource(material, building_artisans_guild::current_params().material_load);
            }
            rd.delivered_materials = 1;
            rd.delivered_phase = ph;
        }
        base.wait_ticks++;
        if (base.wait_ticks > params.work_ticks) {
            advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
        }
        break;
    }

    case ACTION_16_TOMB_ARTISAN_RETURN_HOME:
        base.set_flag(e_figure_flag_invisible, false);
        // OG return_and_disappear: the destination is still the work site after WORK, so the
        // artisan vanishes there; only a roam that ran out walks to the guild road first.
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, -1, ACTION_20_TOMB_ARTISAN_DESTROY)) {
            poof();
        }
        break;
    }
}

void figure_tomb_artisan::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_14_TOMB_ARTISAN_WORK:
        image_set_animation(animkeys().work);
        break;

    case ACTION_11_TOMB_ARTISAN_GOING:
    case ACTION_12_TOMB_ARTISAN_ROAM:
    case ACTION_16_TOMB_ARTISAN_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}

void figure_tomb_artisan::on_destroy() {
    figure_impl::on_destroy();

    building *b_dest = building_get(runtime_data().destination_bid);
    if (!b_dest || !b_dest->is_valid()) {
        b_dest = destination();
    }
    if (!b_dest || !b_dest->is_valid()) {
        return;
    }
    b_dest->dcast()->remove_worker(base.id);
    b_dest->remove_figure_by_id(base.id);
}
