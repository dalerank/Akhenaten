#include "building_farm.h"

#include "building/building.h"
#include "building/animation.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "game/time.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/boilerplate.h"
#include "grid/floodplain.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "city/floods.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "game/game.h"

static void building_farm_draw_info(object_info &c, const char* type, e_resource resource) {
    painter ctx = game.painter();
    auto &meta = building::get_info(type);

    c.help_id = meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    ctx.draw(sprite_resource_icon(resource), c.offset + vec2i{10, 10});
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);

    int pct_grown = calc_percentage<int>(b->data.industry.progress, 2000);
    int width = lang_text_draw(meta.text_id, 2, c.offset.x + 32, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_grown, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    width += lang_text_draw(meta.text_id, 3, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    // fertility
    int pct_fertility = map_get_fertility_for_farm(b->tile.grid_offset());
    width += lang_text_draw(meta.text_id, 12, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_fertility, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(meta.text_id, 13, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description_at(c, 70, 69, 25);
    else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, 70, meta.text_id, 4);
    else if (b->data.industry.curse_days_left > 4)
        window_building_draw_description_at(c, 70, meta.text_id, 11);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 70, meta.text_id, 5);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 70, meta.text_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 70, meta.text_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 70, meta.text_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 70, meta.text_id, 9);
    else
        window_building_draw_description_at(c, 70, meta.text_id, 10);

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    if (building_is_floodplain_farm(*b)) {
        window_building_draw_employment_flood_farm(&c, 142);

        // next flood info
        int month_id = 8; // TODO: fetch flood info
        width = lang_text_draw(177, 2, c.offset.x + 32, c.offset.y + 16 * c.height_blocks - 136, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw(160, month_id, c.offset.x + 32 + width, c.offset.y + 16 * c.height_blocks - 136, FONT_NORMAL_BLACK_ON_LIGHT);

        // irrigated?
        int is_not_irrigated = 0; // TODO: fetch irrigation info
        lang_text_draw(177, is_not_irrigated, c.offset.x + 32, c.offset.y + 16 * c.height_blocks - 120,FONT_NORMAL_BLACK_ON_LIGHT);

        window_building_draw_description_at(c, 16 * c.height_blocks - 96, meta.text_id, 1);
    } else {
        window_building_draw_employment(&c, 142);
        window_building_draw_description_at(c, 16 * c.height_blocks - 136, meta.text_id, 1);
    }
}

void building_farm_draw_info(object_info& c) {
    building *b = building_get(c.building_id);

    switch (b->type) {
    case BUILDING_BARLEY_FARM: building_farm_draw_info(c, "barley_farm", RESOURCE_BARLEY); break;
    case BUILDING_FLAX_FARM: building_farm_draw_info(c, "flax_farm", RESOURCE_FLAX); break;
    case BUILDING_GRAIN_FARM: building_farm_draw_info(c, "grain_farm", RESOURCE_GRAIN); break;
    case BUILDING_LETTUCE_FARM: building_farm_draw_info(c, "lettuce_farm", RESOURCE_LETTUCE); break;
    case BUILDING_POMEGRANATES_FARM: building_farm_draw_info(c, "pomegranades_farm", RESOURCE_POMEGRANATES); break;
    case BUILDING_CHICKPEAS_FARM: building_farm_draw_info(c, "chickpeas_farm", RESOURCE_CHICKPEAS); break;
    case BUILDING_FIGS_FARM: building_farm_draw_info(c, "figs_farm", RESOURCE_FIGS); break;
    case BUILDING_HENNA_FARM: building_farm_draw_info(c, "henna_farm", RESOURCE_HENNA); break;
    }
}

void draw_farm_worker(painter &ctx, int direction, int action, int frame_offset, vec2i coords, color color_mask = COLOR_MASK_NONE) {
    e_image_id action_img;
    switch (action) {
    case FARM_WORKER_TILING: action_img = IMG_WORKER_AKNH_TILING; break;
    case FARM_WORKER_SEEDING: action_img = IMG_WORKER_AKNH_SEEDING; break;
    case FARM_WORKER_HARVESTING: coords.y += 10; action_img = IMG_WORKER_AKNH_HARVESTING; break;
    }
    ImageDraw::img_sprite(ctx, image_group(action_img) + direction + 8 * (frame_offset - 1), coords.x, coords.y, color_mask);
}

static const vec2i FARM_TILE_OFFSETS_FLOODPLAIN[9] = {{60, 0}, {90, 15}, {120, 30}, {30, 15}, {60, 30}, {90, 45}, {0, 30}, {30, 45}, {60, 60}};
static const vec2i FARM_TILE_OFFSETS_MEADOW[5] = {{0, 30}, {30, 45}, {60, 60}, {90, 45}, {120, 30}};

static vec2i farm_tile_coords(vec2i pos, int tile_x, int tile_y) {
    int tile_id = 3 * abs(tile_y) + abs(tile_x);
    return pos + FARM_TILE_OFFSETS_FLOODPLAIN[tile_id];
}

int get_crops_image(e_building_type type, int growth) {
    int base = 0;
    base = image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH);
    switch (type) {
    case BUILDING_BARLEY_FARM:
    return base + 6 * 0 + growth;
    case BUILDING_FLAX_FARM:
    return base + 6 * 6 + growth;
    case BUILDING_GRAIN_FARM:
    return base + 6 * 2 + growth;
    case BUILDING_LETTUCE_FARM:
    return base + 6 * 3 + growth;
    case BUILDING_POMEGRANATES_FARM:
    return base + 6 * 4 + growth;
    case BUILDING_CHICKPEAS_FARM:
    return base + 6 * 5 + growth;
    case BUILDING_FIGS_FARM:
    return base + 6 * 1 + growth;
    //            case BUILDING_HENNA_FARM:
    //                return base + 6 * 0 + growth;
    }

    return image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH) + (type - BUILDING_BARLEY_FARM) * 6; // temp
}

void draw_farm_crops(painter &ctx, e_building_type type, int progress, int grid_offset, vec2i tile, color color_mask) {
    int image_crops = get_crops_image(type, 0);
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) { // on floodplains - all
        for (int i = 0; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i * 200) / 100));
            ImageDraw::img_from_below(ctx, image_crops + growth_offset, tile.x + FARM_TILE_OFFSETS_FLOODPLAIN[i].x, tile.y + FARM_TILE_OFFSETS_FLOODPLAIN[i].y, color_mask);
        }
    } else { // on dry meadows
        for (int i = 0; i < 5; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i * 400) / 100));

            ImageDraw::img_from_below(ctx, image_crops + growth_offset, tile.x + FARM_TILE_OFFSETS_MEADOW[i].x, tile.y + FARM_TILE_OFFSETS_MEADOW[i].y, color_mask);
        }
    }
}

void building_farm_draw_workers(painter &ctx, building* b, int grid_offset, vec2i pos) {
    if (b->num_workers == 0) {
        return;
    }

    pos += {30, -15};
    int animation_offset = 0;
    int random_seed = 1234.567f * (1 + game_time_day()) * map_random_get(b->tile.grid_offset());
    int d = random_seed % 8;
    if (building_is_floodplain_farm(*b)) {
        if (floodplains_is(FLOOD_STATE_IMMINENT)) {
            //int random_x = random_seed % 3;
            //int random_y = int(1234.567f * random_seed) % 3;
            //auto coords = farm_tile_coords(x, y, random_x, random_y);
            //draw_ph_worker(d, 2, animation_offset, coords);
        } else {
            animation_offset = generic_sprite_offset(grid_offset, 13, 1);
            if (b->data.industry.progress < 400)
                draw_farm_worker(ctx, game_time_absolute_tick() % 128 / 16, 1, animation_offset, farm_tile_coords(pos, 1, 1));
            else if (b->data.industry.progress < 500)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 1, 0));
            else if (b->data.industry.progress < 600)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 2, 0));
            else if (b->data.industry.progress < 700)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 0, 1));
            else if (b->data.industry.progress < 800)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 1, 1));
            else if (b->data.industry.progress < 900)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 2, 1));
            else if (b->data.industry.progress < 1000)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 0, 2));
            else if (b->data.industry.progress < 1100)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 1, 2));
            else if (b->data.industry.progress < 1200)
                draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 2, 2));
            else if (b->data.industry.progress < 1300)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 1, 0));
            else if (b->data.industry.progress < 1400)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 2, 0));
            else if (b->data.industry.progress < 1500)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 0, 1));
            else if (b->data.industry.progress < 1600)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 1, 1));
            else if (b->data.industry.progress < 1700)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 2, 1));
            else if (b->data.industry.progress < 1800)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 0, 2));
            else if (b->data.industry.progress < 1900)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 1, 2));
            else if (b->data.industry.progress < 2000)
                draw_farm_worker(ctx, d, 2, animation_offset, farm_tile_coords(pos, 2, 2));
        }
    } else {
        animation_offset = generic_sprite_offset(grid_offset, 13, 1);
        if (b->data.industry.progress < 100)
            draw_farm_worker(ctx, game_time_absolute_tick() % 128 / 16, 1, animation_offset, farm_tile_coords(pos, 1, 1));
        else if (b->data.industry.progress < 400)
            draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 0, 2));
        else if (b->data.industry.progress < 800)
            draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 1, 2));
        else if (b->data.industry.progress < 1200)
            draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 2, 2));
        else if (b->data.industry.progress < 1600)
            draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 2, 1));
        else if (b->data.industry.progress < 2000)
            draw_farm_worker(ctx, d, 0, animation_offset, farm_tile_coords(pos, 2, 0));
    }
}

static bool farm_harvesting_month_for_produce(int resource_id, int month) {
    switch (resource_id) {
        // annual meadow farms
    case RESOURCE_CHICKPEAS:
    case RESOURCE_LETTUCE:
        return (month == MONTH_APRIL);

    case RESOURCE_FIGS:
        return (month == MONTH_SEPTEMPTER);

    case RESOURCE_FLAX:
        return (month == MONTH_DECEMBER);

    // biannual meadow farms
    case RESOURCE_GRAIN:
    return (month == MONTH_JANUARY || month == MONTH_MAY);
    break;
    case RESOURCE_BARLEY:
    return (month == MONTH_FEBRUARY || month == MONTH_AUGUST);
    break;
    case RESOURCE_POMEGRANATES:
    return (month == MONTH_JUNE || month == MONTH_NOVEMBER);
    break;
    }
    return false;
}

bool building_farm_time_to_deliver(bool floodplains, int resource_id) {
    if (floodplains) {
        auto current_cycle = floods_current_cycle();
        auto start_cycle = floods_start_cycle();
        auto harvest_cycle = start_cycle - 28.0f;
        return floodplains_is(FLOOD_STATE_IMMINENT) && current_cycle >= harvest_cycle;
    } else {
        if (game_time_day() < 2 && farm_harvesting_month_for_produce(resource_id, game_time_month()))
            return true;

        return false;
    }
}

void building::spawn_figure_farms() {
    bool is_floodplain = building_is_floodplain_farm(*this);
    if (!is_floodplain && has_road_access) { // only for meadow farms
        common_spawn_labor_seeker(50);
        if (building_farm_time_to_deliver(false, output_resource_first_id)) { // UGH!!
            spawn_figure_farm_harvests();
        }
    } else if (is_floodplain) {
        if (building_farm_time_to_deliver(true)) {
            spawn_figure_farm_harvests();
        }
    }
}