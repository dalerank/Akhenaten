#include "figure/figure.h"

#include "building/monument_mastaba.h"
#include "figure/image.h"
#include "graphics/image_groups.h"

void figure::worker_action() {
    use_cross_country = false;
    max_roam_length = 384;
    building* bhome = home();
    building* b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    bool stop_at_road = true;
    if (!bhome->is_valid() || !b_dest->is_valid()) {
        poof();
        return;
    }

    if (b_dest->is_industry()) {
        if (b_dest->data.industry.worker_id != id) {
            poof();
            return;
        }

        terrain_usage = TERRAIN_USAGE_ROADS;
    } else if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        stop_at_road = false;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (action_state) {
    case 9:
        break;

    case FIGURE_ACTION_10_WORKER_GOING:
        if (do_gotobuilding(destination(), stop_at_road, terrain_usage)) {
            if (building_is_farm(b_dest->type)) {
                b_dest->num_workers = std::clamp<int>((1.f - bhome->tile.dist(b_dest->tile) / 20.f) * 12, 2, 10);
                b_dest->data.industry.work_camp_id = bhome->id;
                b_dest->data.industry.worker_id = 0;
                b_dest->data.industry.labor_state = LABOR_STATE_JUST_ENTERED;
                b_dest->data.industry.labor_days_left = 96;
            } else if (b_dest->type == BUILDING_PYRAMID) {
                // todo: MONUMENTSSSS
            } else if (building_type_any_of(b_dest->type, BUILDING_SMALL_MASTABA, BUILDING_SMALL_MASTABA_SIDE, BUILDING_SMALL_MASTABA_WALL, BUILDING_SMALL_MASTABA_ENTRANCE)) {
                tile2i tile_need_leveling = building_small_mastaba_tile4work(b_dest);
                if (tile_need_leveling == tile2i{-1, -1}) {
                    poof();
                    return;
                }
                map_monuments_set_progress(tile_need_leveling, 1);
                destination_tile = tile_need_leveling;
                advance_action(FIGURE_ACTION_11_WORKER_GOING_TO_PLACE);
            }
        }
        break;

    case FIGURE_ACTION_11_WORKER_GOING_TO_PLACE:
        if (do_goto(destination_tile, false, TERRAIN_USAGE_ANY)) {
            wait_ticks = 0;
            direction = 0;
            advance_action(FIGURE_ACTION_12_WORKER_LEVELING_GROUND);
        }
        break;

    case FIGURE_ACTION_12_WORKER_LEVELING_GROUND:
        int progress = map_monuments_get_progress(tile);
        if (progress < 200) {
            map_monuments_set_progress(tile, progress + 1);
        } else {
            poof();
        }
        break;
    }

    switch (action_state) {
    case FIGURE_ACTION_12_WORKER_LEVELING_GROUND:
        image_set_animation(IMG_WORKER_AKNH_WORK, 0, 12);
        break;
    }
}