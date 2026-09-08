#include "figure_tomb_artisan.h"

#include "building/monuments.h"
#include "game/resource.h"
#include "game/simulation_time.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tomb_artisan);

void figure_tomb_artisan::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    building *bhome = home();
    building *b_dest = destination();
    if ((!b_dest || !b_dest->is_valid()) && runtime_data().destination_bid) {
        b_dest = building_get(runtime_data().destination_bid);
    }
    if (!b_dest || !b_dest->is_valid()) {
        poof();
        return;
    }
    // Home required to path back; WORK can finish deliver without a guild (test attach).
    if ((!bhome || !bhome->is_valid()) && action_state() != ACTION_14_TOMB_ARTISAN_WORK) {
        poof();
        return;
    }

    e_terrain_usage terrain_usage = b_dest->is_monument() ? TERRAIN_USAGE_PREFER_ROADS : TERRAIN_USAGE_ROADS;

    switch (action_state()) {
    case ACTION_20_TOMB_ARTISAN_DESTROY:
        poof();
        break;

    case ACTION_10_TOMB_ARTISAN_CREATED:
        runtime_data().destination_bid = b_dest->id;
        // Prefer monument access_point — access_tile() is road_access for most
        // monument types and is often unset when the guild spawns the walker.
        if (auto *m = b_dest->dcast_monument()) {
            base.destination_tile = m->access_point();
        } else {
            base.destination_tile = b_dest->access_tile();
        }
        advance_action(ACTION_11_TOMB_ARTISAN_GOING);
        break;

    case ACTION_11_TOMB_ARTISAN_GOING:
        if (do_goto(base.destination_tile, terrain_usage, ACTION_14_TOMB_ARTISAN_WORK, ACTION_16_TOMB_ARTISAN_RETURN_HOME)) {
            base.wait_ticks = 0;
            advance_action(ACTION_14_TOMB_ARTISAN_WORK);
        }
        break;

    case ACTION_14_TOMB_ARTISAN_WORK: {
        // Guild consumed 100 clay+paint at spawn — credit monument once for this trip.
        // If the tomb phase advanced after delivery, this load is spent: go home for a refill.
        auto &rd = runtime_data();
        if (auto *m = b_dest->dcast_monument()) {
            const uint8_t ph = m->phase();
            if (rd.delivered_materials && rd.delivered_phase != ph) {
                // Free the monument slot now — otherwise max_artisans blocks guild
                // refill while this walker walks home after a phase advance.
                if (auto *impl = b_dest->dcast()) {
                    impl->remove_worker(base.id);
                }
                if (bhome && bhome->is_valid()) {
                    advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
                } else {
                    advance_action(ACTION_20_TOMB_ARTISAN_DESTROY);
                }
                break;
            }
            if (!rd.delivered_materials) {
                m->deliver_resource(RESOURCE_CLAY, 100);
                m->deliver_resource(RESOURCE_PAINT, 100);
                rd.delivered_materials = 1;
                rd.delivered_phase = ph;
            }
        }
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
            if (bhome && bhome->is_valid()) {
                advance_action(ACTION_16_TOMB_ARTISAN_RETURN_HOME);
            } else {
                advance_action(ACTION_20_TOMB_ARTISAN_DESTROY);
            }
        }
        break;
    }

    case ACTION_16_TOMB_ARTISAN_RETURN_HOME:
        if (!bhome || !bhome->is_valid()) {
            poof();
            break;
        }
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, ACTION_20_TOMB_ARTISAN_DESTROY)) {
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

    case ACTION_16_TOMB_ARTISAN_RETURN_HOME:
    case ACTION_11_TOMB_ARTISAN_GOING:
        image_set_animation(animkeys().walk);
        break;
    }
}

void figure_tomb_artisan::on_destroy() {
    figure_impl::on_destroy();

    building *b_dest = building_get(runtime_data().destination_bid);
    if (!b_dest || !b_dest->is_valid()) {
        // Fallback if we never reached ACTION_10 (destination_bid still 0).
        b_dest = destination();
    }
    if (!b_dest || !b_dest->is_valid()) {
        return;
    }
    // Clear monument worker slot (add_workers) and any building figure_ids entry.
    b_dest->dcast()->remove_worker(base.id);
    b_dest->remove_figure_by_id(base.id);
}
