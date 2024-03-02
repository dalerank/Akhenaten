#include "building_farm.h"

#include "building/building.h"
#include "building/industry.h"
#include "building/building_animation.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "game/time.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/floodplain.h"
#include "grid/building_tiles.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "city/floods.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "figure/figure.h"

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

void building_farm::window_info_background(object_info& c) {
    switch (base.type) {
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
    case BUILDING_BARLEY_FARM: return base + 6 * 0 + growth;
    case BUILDING_FLAX_FARM: return base + 6 * 6 + growth;
    case BUILDING_GRAIN_FARM: return base + 6 * 2 + growth;
    case BUILDING_LETTUCE_FARM: return base + 6 * 3 + growth;
    case BUILDING_POMEGRANATES_FARM: return base + 6 * 4 + growth;
    case BUILDING_CHICKPEAS_FARM: return base + 6 * 5 + growth;
    case BUILDING_FIGS_FARM: return base + 6 * 1 + growth;
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

void building_farm_draw_workers(painter &ctx, building* b, tile2i tile, vec2i pos) {
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
            animation_offset = generic_sprite_offset(tile.grid_offset(), 13, 1);
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
        animation_offset = generic_sprite_offset(tile.grid_offset(), 13, 1);
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

void building_farm::on_create() {
    switch (type()) {
    case BUILDING_BARLEY_FARM:
        base.output_resource_first_id = RESOURCE_BARLEY;
        break;
    case BUILDING_FLAX_FARM:
        base.output_resource_first_id = RESOURCE_FLAX;
        break;
    case BUILDING_GRAIN_FARM:
        base.output_resource_first_id = RESOURCE_GRAIN;
        base.output_resource_second_id = RESOURCE_STRAW;
        base.output_resource_second_rate = 10;
        break;
    case BUILDING_LETTUCE_FARM:
        base.output_resource_first_id = RESOURCE_LETTUCE;
        break;
    case BUILDING_POMEGRANATES_FARM:
        base.output_resource_first_id = RESOURCE_POMEGRANATES;
        break;
    case BUILDING_CHICKPEAS_FARM:
        base.output_resource_first_id = RESOURCE_CHICKPEAS;
        break;
    case BUILDING_FIGS_FARM:
        base.output_resource_first_id = RESOURCE_FIGS;
        break;
    }
    base.fire_proof = 1;
}

bool building_farm::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i t, color mask) {
    if (map_terrain_is(t.grid_offset(), TERRAIN_BUILDING)) {
        draw_farm_crops(ctx, type(), data.industry.progress, tile().grid_offset(), point, mask);
        building_farm_draw_workers(ctx, &base, t, point);
    }

    return true;
}

e_sound_channel_city building_farm::sound_channel() const {
    switch (type()) {
    case BUILDING_CHICKPEAS_FARM:
        return SOUND_CHANNEL_CITY_CHICKFARM;
    }
    return SOUND_CHANNEL_CITY_NONE;
}

void building_farm::spawn_figure() {
    bool is_floodplain = building_is_floodplain_farm(base);
    if (!is_floodplain && base.has_road_access) { // only for meadow farms
        common_spawn_labor_seeker(50);
        if (building_farm_time_to_deliver(false, base.output_resource_first_id)) { // UGH!!
            spawn_figure_harvests();
        }
    } else if (is_floodplain) {
        if (building_farm_time_to_deliver(true)) {
            spawn_figure_harvests();
        }
    }
}

void building_farm::spawn_figure_harvests() {
    if (is_floodplain_farm()) { // floodplain farms
                                // In OG Pharaoh, farms can NOT send out a cartpusher if the cartpusher
                                // from the previous harvest is still alive. The farm will get "stuck"
                                // and remain in active production till flooded, though the farm worker
                                // still displays with the harvesting animation.
        if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
            return;
        }

        if (base.has_road_access && data.industry.progress > 0) {
            int farm_fertility = map_get_fertility_for_farm(tile());

            data.industry.ready_production = data.industry.progress * farm_fertility / 100;
            int expected_produce = farm_expected_produce(&base);
            {
                figure *f = create_cartpusher(base.output_resource_first_id, expected_produce);
                building_farm *farm = dcast_farm();
                farm->deplete_soil();

                f->sender_building_id = id();

                data.industry.progress = 0;
                data.industry.ready_production = 0;
                data.industry.worker_id = 0;
                data.industry.work_camp_id = 0;
                data.industry.labor_state = LABOR_STATE_NONE;
                data.industry.labor_days_left = 0;
                base.num_workers = 0;
            }

            if (base.output_resource_second_id != RESOURCE_NONE) {
                int rate = std::max<int>(1, base.output_resource_second_rate);
                int second_produce_expected = expected_produce / rate;
                figure *f = create_cartpusher(base.output_resource_second_id, second_produce_expected, FIGURE_ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER_2);
                f->sender_building_id = id();
            }
        }
    } else { // meadow farms
        if (base.has_road_access) {
            if (has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
                return;
            }
            create_cartpusher(base.output_resource_first_id, farm_expected_produce(&base));
            building_industry_start_new_production(&base);
        }
    }
}

void building_farm::update_tiles_image() {
    bool is_flooded = false;
    if (building_is_floodplain_farm(base)) {
        for (int _y = tile().y(); _y < tile().y() + size(); _y++) {
            for (int _x = tile().x(); _x < tile().x() + size(); _x++) {
                if (map_terrain_is(MAP_OFFSET(_x, _y), TERRAIN_WATER))
                    is_flooded = true;
            }
        }
    }

    if (!is_flooded) {
        map_building_tiles_add_farm(id(), tile(), image_id_from_group(GROUP_BUILDING_FARMLAND) + 5 * (base.output_resource_first_id - 1), data.industry.progress);
    }
}

void building_farm::deplete_soil() {
    // DIFFERENT from original Pharaoh... and a bit easier to do?
    if (config_get(CONFIG_GP_CH_SOIL_DEPLETION)) {
        int malus = (float)data.industry.progress / (float)MAX_PROGRESS_FARM_PH * (float)-100;
        for (int _y = tiley(); _y < tiley() + size(); _y++) {
            for (int _x = tilex(); _x < tilex() + size(); _x++) {
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    } else {
        for (int _y = tiley(); _y < tiley() + size(); _y++) {
            for (int _x = tilex(); _x < tilex() + size(); _x++) {
                int new_fert = map_get_fertility(MAP_OFFSET(_x, _y), FERT_WITH_MALUS) * 0.2f;
                int malus = new_fert - map_get_fertility(MAP_OFFSET(_x, _y), FERT_NO_MALUS);
                map_soil_set_depletion(MAP_OFFSET(_x, _y), malus);
            }
        }
    }
    update_tiles_image();
}