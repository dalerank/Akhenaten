#include "building_fishing_wharf.h"

#include "js/js_game.h"
#include "city/city.h"
#include "grid/water.h"
#include "grid/building.h"
#include "city/buildings.h"
#include "city/warnings.h"
#include "building/count.h"
#include "config/config.h"
#include "figure/figure.h"
#include "core/random.h"
#include "grid/image.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "window/window_building_info.h"

#include "dev/debug.h"
#include <iostream>

declare_console_command_p(killfishboats, game_cheat_kill_fish_boats);
void game_cheat_kill_fish_boats(std::istream &is, std::ostream &os) {
    figure_valid_do([] (figure &f) { f.poof(); }, FIGURE_FISHING_BOAT);
}

struct info_window_fishing_wharf : public building_info_window_t<info_window_fishing_wharf> {
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_fishing_wharf();
    }

    virtual void init(object_info &c) override;
};

info_window_fishing_wharf fishing_wharf_infow;
building_fishing_wharf::static_params fishing_wharf_m;

void building_fishing_wharf::static_params::load(archive arch) {

}

void building_fishing_wharf::on_create(int orientation) {
    data.industry.orientation = orientation;
}

void building_fishing_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    int img_id = anim(animkeys().base).first_img();
    map_water_add_building(id(), tile(), size(), img_id + orientation_rel);
}

void building_fishing_wharf::update_count() const {
    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        if (!boat->is_valid()) {
            g_city.buildings.request_fishing_boat();
        }
    }

    building_increase_industry_count(RESOURCE_FISH, num_workers() > 0);
}

void building_fishing_wharf::update_day() {
    building_impl::update_day();

    int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
    if (boat_id > 0) {
        figure *f = get_figure(BUILDING_SLOT_BOAT);
        if (!f->is_valid() || f->type != FIGURE_FISHING_BOAT) {
            base.set_figure(BUILDING_SLOT_BOAT, 0);
        }
    }
}

void building_fishing_wharf::update_graphic() {
    building_impl::update_graphic();

    if (!can_play_animation()) {
        set_animation(animkeys().none);
        return;
    }
    
    figure *f = base.get_figure(BUILDING_SLOT_BOAT);
    if (!f->is_valid()) {
        set_animation(animkeys().none);
        return;
    }

    int image_warf = map_image_at(tile());
    int image_warf_base = anim(animkeys().base).first_img();
    const bool has_cart = base.get_figure_id(BUILDING_SLOT_CARTPUSHER);
    xstring animkey;
    if (f->action_state != FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF) {
        if (image_warf == image_warf_base) animkey = animkeys().wait_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().wait_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().wait_s;
        else animkey = animkeys().wait_e;
    } else {
        if (has_cart) animkey = animkeys().none;
        else if (image_warf == image_warf_base) animkey = animkeys().work_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().work_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().work_s;
        else animkey = animkeys().work_e;
    }

    set_animation(animkey);
}

void building_fishing_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            ; // nothing
        } else {
            base.figure_spawn_delay++;
            int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
            if (!boat_id && base.figure_spawn_delay > spawn_delay) {
                base.figure_spawn_delay = 0;

                int dock_tile = data.dock.dock_tiles[0];
                if (config_get(CONFIG_GP_CH_FISHING_WHARF_SPAWN_BOATS) && dock_tile > 0) {
                    figure* f = figure_create(FIGURE_FISHING_BOAT, tile2i(dock_tile), DIR_4_BOTTOM_LEFT);
                    f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
                    f->set_home(id());
                    base.set_figure(BUILDING_SLOT_BOAT, f);
                    random_generate_next();
                    f->wait_ticks = random_short() % 30; // ok
                    f->allow_move_type = EMOVE_WATER;
                }
            }
        }
    }

    bool cart_spawned = base.common_spawn_goods_output_cartpusher();
    if (cart_spawned) {
        if (data.industry.has_fish) {
            data.industry.has_fish = (base.stored_amount_first > 0);
        }
    }
}

void building_fishing_wharf::on_place_checks() {
    building_impl::on_place_checks();

    if (!g_city.buildings.has_working_shipyard()) {
        building_construction_warning_show(WARNING_SHIPWRIGHT_NEEDED);
    }
}

void building_fishing_wharf::on_undo() {
    base.set_figure(BUILDING_SLOT_BOAT, 0);
}

void building_fishing_wharf::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    int image_id = this->anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

bool building_fishing_wharf::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    auto &anim_wharf = base.anim;
    if (anim_wharf.valid()) {
        int img_id = anim_wharf.start() + (data.dock.docker_anim_frame / anim_wharf.frame_duration) * 4;
        const image_t *img = image_get(img_id);
        ImageDraw::img_generic(ctx, img_id, point + anim_wharf.pos, color_mask, 1.f, true);
    }

    return true;
}

void building_fishing_wharf::highlight_waypoints() {
    building_impl::highlight_waypoints();

    map_highlight_set(data.dock.dock_tiles[0], 3);
    map_highlight_set(data.dock.dock_tiles[1], 3);
}

void info_window_fishing_wharf::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    std::pair<int, int> reason = { c.group_id, 0 };
    if (!c.has_road_access) {
        reason = { 69, 25 };
    } else if (!b->get_figure(BUILDING_SLOT_BOAT)->is_valid()) {
        reason = { c.group_id, 2 };
    } else {
        figure *boat = b->get_figure(BUILDING_SLOT_BOAT);
        switch (boat->action_state) {
        case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH: reason.second = 3; break;
        case FIGURE_ACTION_192_FISHING_BOAT_FISHING: reason.second = 4; break;
        case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF: reason.second = 5; break;
        case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF: reason.second = 6; break;
        case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH: reason.second = 7; break;
        default: reason.second = 8; break;
        }
    }

    ui["resource_img"].image(RESOURCE_FISH);
    ui["warning_text"] = ui::str(reason.first, reason.second);
    ui["storage_desc"].text_var("Stored fish %d", b->stored_amount_first);

    fill_employment_details(c);
}
