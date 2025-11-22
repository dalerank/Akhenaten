#include "building_scribal_school.h"

#include "js/js_game.h"
#include "core/calc.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "empire/empire.h"
#include "widget/city/ornaments.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_scribal_school);

void building_scribal_school::update_month() {
    if (base.stored_amount_first <= 0) {
        return;
    }

    short want_spent = calc_adjust_with_percentage<short>(base.num_workers, 50);
    short spent = std::min(base.stored_amount_first, want_spent);
    base.stored_amount_first -= spent;
}

void building_scribal_school::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_PAPYRUS) > 0) {
        return;
    }
        
    if (g_city.resource.yards_stored(RESOURCE_PAPYRUS) > 0) {
        return;
    }

    construction_warnings warnings("#needs_papyrus");

    const bool can_produce_papyrus = g_city.can_produce_resource(RESOURCE_PAPYRUS);
    const bool can_import_papyrus = g_empire.can_import_resource(RESOURCE_PAPYRUS, true);
    const bool is_import_papyrus = (city_resource_trade_status(RESOURCE_PAPYRUS) == TRADE_STATUS_IMPORT);

    warnings.add_if(!can_produce_papyrus, "#build_papyrus_maker");
    warnings.add_if(!can_import_papyrus, "#import_papyrus_overseer");
    warnings.add_if(!is_import_papyrus, "#import_papyrus_trade_route");
}

bool building_scribal_school::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_PAPYRUS) {
        return false;
    }

    assert(id() > 0);
    base.stored_amount_first += amount;
    return true;
}

void building_scribal_school::spawn_figure() {
    check_labor_problem();
    if (has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_TEACHER)) {
        return;
    }

    tile2i road = map_get_road_access_tile(tile(), size());
    if (!road.valid()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;

        figure* f = figure_create(FIGURE_TEACHER, road, DIR_0_TOP_RIGHT);
        f->action_state = ACTION_125_ROAMER_ROAMING;
        f->set_home(id());
        base.set_figure(BUILDING_SLOT_SERVICE, f->id);
        f->init_roaming_from_building(0);
    }
}

void building_scribal_school::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_scribal_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().papyrus);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = mask;

            pos += {5, -5};
        }
    }

    return true;
}
