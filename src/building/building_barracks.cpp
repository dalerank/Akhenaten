#include "building_barracks.h"

#include "building/count.h"
#include "building/model.h"
#include "city/buildings.h"
#include "city/military.h"
#include "city/resource.h"
#include "core/calc.h"
#include "figure/action.h"
#include "figure/formation_legion.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "config/config.h"

#include "game/game.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "graphics/image.h"

#define INFINITE 10000

int g_tower_sentry_request = 0;

static void button_priority(int index, int param2);

struct rectuiter_data_t {
    int focus_button_id;
    int focus_priority_button_id;
    int return_button_id;
    int building_id;
    object_info* context_for_callback;

    generic_button priority_buttons[2] = {
        {96, 0, 24, 24, button_priority, button_none, 0, 0},
        {96, 24, 24, 24, button_priority, button_none, 1, 0},
    };
};

rectuiter_data_t g_rectuiter_data;

void building::barracks_add_weapon(int amount) {
    if (id > 0) {
        stored_full_amount += amount;
    }
}

void building::monument_remove_worker(int fid) {
    for (auto &wid : data.monuments.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

static int get_closest_legion_needing_soldiers(building* barracks) {
    int recruit_type = LEGION_RECRUIT_NONE;
    int min_formation_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (!m->in_use || !m->is_legion)
            continue;

        if (m->in_distant_battle || m->legion_recruit_type == LEGION_RECRUIT_NONE)
            continue;

        if (m->legion_recruit_type == LEGION_RECRUIT_INFANTRY && barracks->stored_full_amount <= 0)
            continue;

        building* fort = building_get(m->building_id);
        int dist = calc_maximum_distance(barracks->tile, fort->tile);
        if (m->legion_recruit_type > recruit_type || (m->legion_recruit_type == recruit_type && dist < min_distance)) {
            recruit_type = m->legion_recruit_type;
            min_formation_id = m->id;
            min_distance = dist;
        }
    }
    return min_formation_id;
}
static int get_closest_military_academy(building* fort) {
    int min_building_id = 0;
    int min_distance = INFINITE;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_MILITARY_ACADEMY
            && b->num_workers >= model_get_building(BUILDING_MILITARY_ACADEMY)->laborers) {
            int dist = calc_maximum_distance(fort->tile, b->tile);
            if (dist < min_distance) {
                min_distance = dist;
                min_building_id = i;
            }
        }
    }
    return min_building_id;
}

int building::barracks_create_soldier() {
    int formation_id = get_closest_legion_needing_soldiers(this);
    if (formation_id > 0) {
        const formation* m = formation_get(formation_id);
        figure* f = figure_create(m->figure_type, road_access, DIR_0_TOP_RIGHT);
        f->formation_id = formation_id;
        f->formation_at_rest = 1;
        if (m->figure_type == FIGURE_STANDARD_BEARER) {
            if (stored_full_amount > 0)
                stored_full_amount -= 100;
        }
        int academy_id = get_closest_military_academy(building_get(m->building_id));
        if (academy_id) {
            tile2i road;
            building* academy = building_get(academy_id);
            if (map_get_road_access_tile(academy->tile, academy->size, road)) {
                f->action_state = FIGURE_ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY;
                f->destination_tile = road;
                //                f->destination_x = road.x();
                //                f->destination_y = road.y();
                //                f->destination_grid_offset = MAP_OFFSET(f->destination_x, f->destination_y);
            } else {
                f->action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
            }
        } else {
            f->action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
        }
    }
    formation_calculate_figures();
    return formation_id ? 1 : 0;
}

bool building::barracks_create_tower_sentry() {
    if (g_tower_sentry_request <= 0)
        return false;

    building* tower = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_MUD_TOWER && b->num_workers > 0 && !b->has_figure(0)
            && (b->road_network_id == road_network_id || config_get(CONFIG_GP_CH_TOWER_SENTRIES_GO_OFFROAD))) {
            tower = b;
            break;
        }
    }
    if (!tower)
        return false;

    figure* f = figure_create(FIGURE_TOWER_SENTRY, road_access, DIR_0_TOP_RIGHT);
    f->action_state = FIGURE_ACTION_174_TOWER_SENTRY_GOING_TO_TOWER;
    tile2i road;
    if (map_get_road_access_tile(tower->tile, tower->size, road)) {
        f->destination_tile = road;
        //        f->destination_x = road.x();
        //        f->destination_y = road.y();
    } else {
        f->poof();
    }
    tower->set_figure(0, f->id);
    f->set_home(tower->id);
    return true;
}

void building_barracks_request_tower_sentry() {
    g_tower_sentry_request = 2;
}

void building_barracks_decay_tower_sentry_request() {
    if (g_tower_sentry_request > 0)
        g_tower_sentry_request--;
}

int building_barracks_has_tower_sentry_request() {
    return g_tower_sentry_request;
}

void building_barracks_save_state(buffer* buf) {
    buf->write_i32(g_tower_sentry_request);
}
void building_barracks_load_state(buffer* buf) {
    g_tower_sentry_request = buf->read_i32();
}

void building::barracks_toggle_priority() {
    subtype.barracks_priority = 1 - subtype.barracks_priority;
}
int building::barracks_get_priority() {
    return subtype.barracks_priority;
}

void building_recruiter::on_create() {
    city_buildings_add_recruiter(&base);
}

void building_recruiter::spawn_figure() {
    check_labor_problem();
    //    map_point road;
    if (base.has_road_access) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        //        if (pct_workers >= 100)
        //            spawn_delay = 8;
        //        else if (pct_workers >= 75)
        //            spawn_delay = 12;
        //        else if (pct_workers >= 50)
        //            spawn_delay = 16;
        //        else if (pct_workers >= 25)
        //            spawn_delay = 32;
        //        else if (pct_workers >= 1)
        //            spawn_delay = 48;
        //        else
        //            return;
        base.figure_spawn_delay++;
        if (base.figure_spawn_delay > spawn_delay) {
            base.figure_spawn_delay = 0;
            switch (base.subtype.barracks_priority) {
            case PRIORITY_FORT:
            if (!base.barracks_create_soldier())
                base.barracks_create_tower_sentry();
            break;
            default:
            if (!base.barracks_create_tower_sentry())
                base.barracks_create_soldier();
            }
        }
    }
}

void building_recruiter::window_info_background(object_info &c) {
    c.barracks_soldiers_requested = formation_legion_recruits_needed();
    c.barracks_soldiers_requested += building_barracks_has_tower_sentry_request();
    painter ctx = game.painter();

    c.help_id = 37;
    g_rectuiter_data.building_id = c.building_id;

    window_building_play_sound(&c, "wavs/barracks.wav");
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(136, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_WEAPONS), c.offset + vec2i{64, 38});

    building* b = building_get(c.building_id);
    if (b->stored_full_amount < 100)
        lang_text_draw_amount(8, 10, 0, c.offset.x + 92, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    else
        lang_text_draw_amount(8, 10, b->stored_full_amount, c.offset.x + 92, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description_at(c, 70, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 70, 136, 3);
    else if (!c.barracks_soldiers_requested)
        window_building_draw_description_at(c, 70, 136, 4);
    else {
        int offset = 0;
        if (b->stored_full_amount > 0)
            offset = 4;

        if (c.worker_percentage >= 100)
            window_building_draw_description_at(c, 70, 136, 5 + offset);
        else if (c.worker_percentage >= 66)
            window_building_draw_description_at(c, 70, 136, 6 + offset);
        else if (c.worker_percentage >= 33)
            window_building_draw_description_at(c, 70, 136, 7 + offset);
        else {
            window_building_draw_description_at(c, 70, 136, 8 + offset);
        }
    }
    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
    lang_text_draw(50, 21, c.offset.x + 46, c.offset.y + 204, FONT_NORMAL_BLACK_ON_LIGHT); // "Priority"
    lang_text_draw(91, 0, c.offset.x + 46, c.offset.y + 224, FONT_NORMAL_BLACK_ON_LIGHT);  // "Tower"
    lang_text_draw(89, 0, c.offset.x + 46, c.offset.y + 244, FONT_NORMAL_BLACK_ON_LIGHT);  // "Fort"
}

static void draw_priority_buttons(int x, int y, int buttons) {
    
}

static void button_priority(int index, int param2) {
    auto& data = g_rectuiter_data;
    building* barracks = building_get(data.building_id);
    if (index != barracks->subtype.barracks_priority)
        barracks->barracks_toggle_priority();
}

int building_recruiter::window_info_handle_mouse(const mouse* m, object_info &c) {
    auto& data = g_rectuiter_data;
    if (generic_buttons_handle_mouse(m, c.offset.x + 46, c.offset.y + 224, data.priority_buttons, 2, &data.focus_priority_button_id)) {
        window_invalidate();
        return 1;
    }
    return 0;
}

void building_recruiter::window_info_foreground(object_info &c) {
    auto& data = g_rectuiter_data;
    int x = c.offset.x + 46;
    int y = c.offset.y + 224;
    int buttons = 2;

    uint8_t permission_selection_text[] = {'x', 0};
    for (int i = 0; i < buttons; i++) {
        int x_adj = x + data.priority_buttons[i].x;
        int y_adj = y + data.priority_buttons[i].y;
        building* barracks = building_get(data.building_id);
        int priority = barracks->barracks_get_priority();
        button_border_draw(x_adj, y_adj, 20, 20, data.focus_priority_button_id == i + 1 ? 1 : 0);
        if (priority == i) {
            text_draw_centered(permission_selection_text, x_adj + 1, y_adj + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        }
    }
}
