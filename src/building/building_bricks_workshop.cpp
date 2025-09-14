#include "building_bricks_workshop.h"

#include "js/js_game.h"
#include "building/building_workshop.h"
#include "graphics/graphics.h"
#include "graphics/image.h"

building_bricks_workshop::static_params bricks_workshop_m;

bool building_bricks_workshop::can_play_animation() const {
    if (progress() == 0) {
        if (base.stored_amount(RESOURCE_CLAY) < 100) {
            return false;
        }

        if (base.stored_amount(RESOURCE_STRAW) < 100) {
            return false;
        }
    }

    return building_industry::can_play_animation();
}


bool building_bricks_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceilf(base.stored_amount(RESOURCE_CLAY) / 100.f);
    if (amount > 0) {
        const auto &ranim = anim(animkeys().clay);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = color_mask;

            pos += {5, -5};
        }
    }

    int amount2 = ceilf(base.stored_amount(RESOURCE_STRAW) / 100.f);
    if (amount2 > 0) {
        const auto &ranim = anim(animkeys().straw);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount2; ++i) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = color_mask;

            pos += {5, -5};
        }
    }

    return true;
}