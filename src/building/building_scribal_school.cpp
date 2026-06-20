#include "building_scribal_school.h"

#include "js/js_game.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_scribal_school);

bool building_scribal_school::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_PAPYRUS) {
        return false;
    }

    verify_no_crash(id() > 0);
    store_resource(RESOURCE_PAPYRUS, amount);
    return true;
}

void building_scribal_school::spawn_figure() {
    if (common_spawn_figure_trigger(current_params().min_houses_coverage, BUILDING_SLOT_SERVICE)) {
        create_roaming_figure(FIGURE_TEACHER, (e_figure_action)ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE);
    }
}

void building_scribal_school::update_graphic() {
    update_graphic_work_anim();
}

bool building_scribal_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, mask);

    int amount = ceil((float)stored_amount(RESOURCE_PAPYRUS) / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().papyrus);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = mask;

            pos += {5, -5};
        }
    }

    return true;
}
