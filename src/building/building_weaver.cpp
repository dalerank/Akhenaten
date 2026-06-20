#include "building_weaver.h"

#include "building/building_workshop.h"
#include "graphics/graphics.h"
#include "city/city_resource.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_weaver);

bool building_weaver::can_play_animation() const {
    auto &d = runtime_data();
    if (base.stored_amount(RESOURCE_FLAX) < 100 && d.progress == 0) {
        return false;
    }

    return building_industry::can_play_animation();
}

bool building_weaver::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_FLAX) / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().flax);
        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}
