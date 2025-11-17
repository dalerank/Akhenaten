#include "building/building_conservatory.h"

#include "building/building_dance_school.h"
#include "building/building_festival_square.h"
#include "figuretype/figure_entertainer.h"
#include "widget/city/ornaments.h"
#include "city/city_labor.h"
#include "city/city_buildings.h"
#include "city/city.h"
#include "core/calc.h"
#include "grid/road_access.h"
#include "game/game_config.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_conservatory);

void building_conservatory::update_day() {
    building_impl::update_day();

    auto &d = runtime_data();
    if (d.spawned_entertainer_days > 0) {
        d.spawned_entertainer_days--;
    }
}

void building_conservatory::spend_musician_to_festival_square() {
    auto &d = runtime_data();
    if (d.months_until_square_send == 0) {
        building_id square_id = find_square_in_city();
        if (square_id == 0 || !has_road_access() || worker_percentage() == 0) {
            d.months_until_square_send = 2;
            return;
        }
    }

    if (d.months_until_square_send > 0) {
        d.months_until_square_send--;
    }

    // Check if we should send a musician to the square every 2 months
    if (d.months_until_square_send == 0) {
        building_id square_id = find_square_in_city();
        if (square_id > 0) {
            building *square = building_get(square_id);
            if (square->is_valid() && map_has_road_access(square->tile, square->size)) {
                // Check if we have road access and workers
                if (has_road_access() && worker_percentage() > 0) {
                    create_figure_with_destination(FIGURE_MUSICIAN, square, (e_figure_action)ACTION_96_ENTERTAINER_GOING_TO_SQUARE);
                }
            }
        }
        d.months_until_square_send = 2; // Reset counter to 2 months
    }
}

void building_conservatory::update_month() {
    building_impl::update_month();

    auto &d = runtime_data();
    d.spawned_special_figure = false;

    spend_musician_to_festival_square();
}

building_id building_conservatory::find_square_in_city() {
    // First check for festival square
    if (g_city.buildings.festival_square.grid_offset() > 0) {
        building* square = building_at(g_city.buildings.festival_square);
        if (square && square->is_valid() && square->type == BUILDING_FESTIVAL_SQUARE) {
            return square->id;
        }
    }

    return 0;
}

building_id building_conservatory::determine_dancer_school_destination() {
    if (!game_features::gameplay_conservatory_helps_dance_school) {
        return 0;
    }

    building_id best_dance_school_id = 0;
    int min_help_count = 255;
    int min_distance = 10000;

    // Find dance school with least help count (parameter value)
    buildings_valid_do([&] (building &b) {
        if (b.type != BUILDING_DANCE_SCHOOL || !b.is_valid()) {
            return;
        }

        if (!map_has_road_access(b.tile, b.size)) {
            return;
        }

        if (b.distance_from_entry <= 0 || b.road_network_id != base.road_network_id) {
            return;
        }

        building_dancer_school *dance_school = b.dcast_dancer_school();
        if (!dance_school) {
            return;
        }

        uint8_t help_count = dance_school->conservatory_help();
        int dist = calc_distance_with_penalty(b.tile, base.tile, base.distance_from_entry, b.distance_from_entry);

        // Prefer school with less help, or if equal help, prefer closer one
        if (help_count < min_help_count || (help_count == min_help_count && dist < min_distance)) {
            min_help_count = help_count;
            min_distance = dist;
            best_dance_school_id = b.id;
        }
    });

    return best_dance_school_id;
}

void building_conservatory::spawn_figure() {
    if (!common_spawn_figure_trigger(50)) {
        return;
    }

    auto &d = runtime_data();
    if (d.spawned_entertainer_days > 0) {
        return;
    }

    // If feature is enabled and we have a target dance school, send musician there
    if (!!game_features::gameplay_conservatory_helps_dance_school && !d.spawned_special_figure && worker_percentage() > 50) {
        building_id bid = determine_dancer_school_destination();
        building* dance_school = building_get(bid);
        if (dance_school->is_valid() && dance_school->type == BUILDING_DANCE_SCHOOL) {
            create_figure_with_destination(FIGURE_MUSICIAN, dance_school, (e_figure_action)ACTION_92_ENTERTAINER_GOING_TO_VENUE);
            d.spawned_entertainer_days = current_params().spawn_interval;
            d.spawned_special_figure = true;
            return;
        }
    }

    // Otherwise, send musician to normal venues (pavilion or bandstand)
    int dest_id = figure_entertainer::determine_venue_destination(base.road_access, FIGURE_MUSICIAN, {BUILDING_PAVILLION, BUILDING_BANDSTAND});
    building* dest = building_get(dest_id);
    if (dest->id > 0) {
        create_figure_with_destination(FIGURE_MUSICIAN, dest, (e_figure_action)ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        d.spawned_entertainer_days = current_params().spawn_interval;
    } else {
        common_spawn_roamer(FIGURE_MUSICIAN, current_params().min_houses_coverage, (e_figure_action)ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}

void building_conservatory::update_graphic() {
    const bool can_train_musicians = worker_percentage() > 50;
    const xstring &animkey = (can_train_musicians && can_play_animation())
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_conservatory::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}