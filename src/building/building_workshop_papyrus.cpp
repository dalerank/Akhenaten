#include "building_workshop_papyrus.h"

#include "building_workshop.h"
#include "widget/city/ornaments.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_papyrus_maker);

void building_papyrus_maker::update_animation() {
    building_industry::update_animation();
    auto &d = runtime_data();
    if (base.stored_amount(RESOURCE_REEDS) < 100 && d.progress == 0) {
        base.play_animation = false;
    }
}

bool building_papyrus_maker::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_REEDS) / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().reeds);

        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }
    return true;
}
