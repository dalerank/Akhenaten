#include "building/building_weaponsmith.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"

#include "js/js_game.h"
#include "dev/debug.h"
#include "city/city_resource.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_weaponsmith);

declare_console_command(addweapons, game_cheat_add_resource<RESOURCE_WEAPONS>);
declare_console_command(addcopper, game_cheat_add_resource<RESOURCE_COPPER>);

void building_weaponsmith::update_animation() {
    building_industry::update_animation();
    auto &d = runtime_data();
    if (base.stored_amount(RESOURCE_COPPER) < 100 && d.progress == 0) {
        base.play_animation = false;
    }
}

bool building_weaponsmith::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_COPPER) / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().copper);

        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}