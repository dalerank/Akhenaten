#include "building_chariots_workshop.h"

#include "js/js_game.h"
#include "building/building_workshop.h"
#include "graphics/graphics.h"
#include "graphics/image.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_chariots_workshop);

bool building_chariots_workshop::can_play_animation() const {
    if (progress() == 0) {
        if (base.stored_amount(RESOURCE_TIMBER) < 100) {
            return false;
        }

        if (base.stored_amount(RESOURCE_WEAPONS) < 100) {
            return false;
        }
    }

    return building_industry::can_play_animation();
}

bool building_chariots_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceilf(base.stored_amount(RESOURCE_TIMBER) / 100.f);
    if (amount > 0) {
        const auto &ranim = anim("timber");
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = color_mask;

            pos += {5, -5};
        }
    }

    int amount2 = ceilf(base.stored_amount(RESOURCE_WEAPONS) / 100.f);
    if (amount2 > 0) {
        const auto &ranim = anim("weapon");
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
