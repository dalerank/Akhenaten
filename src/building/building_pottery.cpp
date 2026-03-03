#include "building/building_pottery.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "city/city.h"

#include "widget/city/ornaments.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_pottery);

declare_console_command(addpottery, game_cheat_add_resource<RESOURCE_POTTERY>);

bool building_pottery::can_play_animation() const {
    auto &d = runtime_data();
    if (base.stored_amount(RESOURCE_POTTERY) < 100 && d.progress == 0) {
        return false;
    }

    return building_industry::can_play_animation();
}

bool building_pottery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceilf(base.stored_amount(RESOURCE_CLAY) / 100.f);
    if (amount > 0) {
        const auto &ranim = anim(animkeys().clay);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = color_mask;

            pos += {5, -5};
        }
    }

    return true;
}

void building_pottery::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
}