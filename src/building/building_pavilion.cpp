#include "building/building_pavilion.h"

#include "building/count.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/labor.h"
#include "city/warnings.h"
#include "construction/build_planner.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/orientation.h"
#include "grid/building_tiles.h"
#include "js/js_game.h"

struct pavilion_model : public buildings::model_t<building_pavilion> {
    using inherited = buildings::model_t<building_pavilion>;

    int dancer_tile = 0;
    int booth_tile = 0;
    int musician_tile_s = 0;
    int musician_tile_e = 0;
    struct preview_offset {
        vec2i stand, stand_b, stand_e, booth;
        int stand_b_img = 0, stand_e_img = 0;
        void load(archive arch, pcstr section) {
            arch.r_section(section, [this] (archive d_arch) {
                stand = d_arch.r_vec2i("stand");
                stand_b = d_arch.r_vec2i("stand_b");
                stand_e = d_arch.r_vec2i("stand_e");
                booth = d_arch.r_vec2i("booth");
                stand_b_img = d_arch.r_int("stand_b_img");
                stand_e_img = d_arch.r_int("stand_e_img");
            });
        }
    };
    struct place_offset {
        struct item {
            e_building_type type = BUILDING_NONE;
            vec2i offset;
            bool main;
            void load(archive arch) {
                main = arch.r_bool("main");
                offset = arch.r_vec2i("offset");
                type = arch.r_type<e_building_type>("type");
            }
        };
        svector<item, 8> items;
        void load(archive arch, pcstr section) {
            arch.r_array(section, items, [this] (archive d_arch, auto &item) {
                item.load(d_arch);
            });
        }
    };

    using inherited::load;
    virtual void load(archive arch) override {
        for (auto &pdir: preview_dir) {
            pdir.load(arch, bstring32().printf("preview_dir_%d", std::distance(preview_dir, &pdir)).c_str());
        }

        for (auto &pdir : place_dir) {
            pdir.load(arch, bstring32().printf("place_dir_%d", std::distance(place_dir, &pdir)).c_str());
        }
    }

    preview_offset preview_dir[8];
    place_offset place_dir[8];
} pavilion_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_pavilion);
void config_load_building_pavilion() {
    pavilion_m.load();
    pavilion_m.dancer_tile = pavilion_m.anim["base"].first_img();
    pavilion_m.booth_tile = pavilion_m.anim["booth"].first_img();
    pavilion_m.musician_tile_s = pavilion_m.anim["stand_sn_s"].first_img();
    pavilion_m.musician_tile_e = pavilion_m.anim["stand_sn_e"].first_img();
}

void building_pavilion::on_create(int orientation) {

}

void building_pavilion::update_month() {
    data.entertainment.play_index = std::rand() % 10;
}

void building_pavilion::update_day() {
    building_impl::update_day();

    int shows = 0;
    auto update_shows = [&] (auto &days) { if (days > 0) { --days; ++shows; } };
    update_shows(data.entertainment.juggler_visited);
    update_shows(data.entertainment.musician_visited);
    update_shows(data.entertainment.dancer_visited);

    data.entertainment.num_shows = shows;
}

void building_pavilion::on_place_update_tiles(int orientation, int variant) {
    data.entertainment.booth_corner_grid_offset = tile().grid_offset();
    data.entertainment.orientation = orientation;

    int size = pavilion_m.building_size;
    int image_id = pavilion_m.anim["square"].first_img();

    int basic_orientation;
    map_orientation_for_venue_with_map_orientation(tile(), e_venue_mode_pavilion, &basic_orientation);

    // add underlying plaza first
    map_add_venue_plaza_tiles(id(), size, tile(), image_id, false);
    int absolute_orientation = abs(basic_orientation + (8 - city_view_orientation())) % 8;
    for (const auto &item: pavilion_m.place_dir[absolute_orientation].items) {
        build_planner_latch_on_venue(item.type, &base, item.offset.x, item.offset.y, orientation, item.main);
    }
}

void building_pavilion::on_place_checks() {
    if (building_count_active(BUILDING_DANCE_SCHOOL) <= 0) {
        building_construction_warning_show(WARNING_BUILD_DANCERS_SCHOOL);
    }
}

bool building_pavilion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (data.entertainment.dancer_visited && map_image_at(tile) == pavilion_m.dancer_tile) {
        const animation_t &anim = pavilion_m.anim["dancer"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    if (data.entertainment.musician_visited) {
        if (map_image_at(tile) == pavilion_m.musician_tile_s) {
            const animation_t &anim = pavilion_m.anim["musician_sn"];
            building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
        } else if (map_image_at(tile) == pavilion_m.musician_tile_e) {
            const animation_t &anim = pavilion_m.anim["musician_we"];
            building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
        }
    }

    if (data.entertainment.juggler_visited && map_image_at(tile) == pavilion_m.booth_tile) {
        const animation_t &anim = pavilion_m.anim["juggler"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    return true;
}

void building_pavilion::update_count() const {
    building_increase_type_count(BUILDING_BANDSTAND, num_workers() > 0);
    building_increase_type_count(BUILDING_BOOTH, num_workers() > 0);
}

void building_pavilion::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (!common_spawn_figure_trigger(100)) {
        return;
    }

    if (data.entertainment.juggler_visited > 0) {
        base.create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }

    if (data.entertainment.musician_visited > 0) {
        base.create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }

    if (data.entertainment.dancer_visited > 0) {
        base.create_roaming_figure(FIGURE_DANCER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }
}

void building_pavilion::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int size = pavilion_m.building_size;
    int square_id = building_impl::params(BUILDING_PAVILLION).anim["square"].first_img();
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, COLOR_MASK_GREEN);
    }
    int stand_sn_n = pavilion_m.anim["stand_sn_n"].first_img();
    int stand_sn_s = pavilion_m.anim["stand_sn_s"].first_img();
    int booth = pavilion_m.anim["booth"].first_img();
    int stand = pavilion_m.anim["base"].first_img();
    const auto &preview_conf = pavilion_m.preview_dir[orientation];
    draw_building_ghost(ctx, stand, pixel + preview_conf.stand, COLOR_MASK_GREEN);
    draw_building_ghost(ctx, stand_sn_n + preview_conf.stand_b_img, pixel + preview_conf.stand_b, COLOR_MASK_GREEN);
    draw_building_ghost(ctx, stand_sn_s + preview_conf.stand_e_img, pixel + preview_conf.stand_e, COLOR_MASK_GREEN);
    draw_building_ghost(ctx, booth, pixel + preview_conf.booth, COLOR_MASK_GREEN);
}

void building_pavilion::window_info_background(object_info &c) {
    c.help_id = 73;
    window_building_play_sound(&c, "Wavs/colloseum.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(74, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 74, 6);
    else if (!b->data.entertainment.num_shows)
        window_building_draw_description(c, 74, 2);
    else if (b->data.entertainment.num_shows == 2)
        window_building_draw_description(c, 74, 3);
    else if (b->data.entertainment.juggler_visited)
        window_building_draw_description(c, 74, 5);
    else if (b->data.entertainment.musician_visited)
        window_building_draw_description(c, 74, 4);

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 6 });
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.juggler_visited > 0) {
        int width = lang_text_draw(74, 8, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.juggler_visited, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 7, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
    if (b->data.entertainment.musician_visited > 0) {
        int width = lang_text_draw(74, 10, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.musician_visited, c.offset.x + width + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 9, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void building_pavilion::on_undo() {
    for (int dy = 0; dy < 4; dy++) {
        for (int dx = 0; dx < 4; dx++) {
            if (map_building_at(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy)) == 0)
                map_building_set(data.entertainment.booth_corner_grid_offset + GRID_OFFSET(dx, dy), id());
        }
    }
}
