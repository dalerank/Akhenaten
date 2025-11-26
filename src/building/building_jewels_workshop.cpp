#include "building_jewels_workshop.h"

#include "building/building_workshop.h"
#include "empire/empire.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "js/js_game.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "widget/city/ornaments.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_jewels_workshop);

bool building_jewels_workshop::can_play_animation() const {
    if (base.stored_amount(RESOURCE_GEMS) < 100) {
        return false;
    }

    return building_industry::can_play_animation();
}

void building_jewels_workshop::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_GEMS) > 0) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_GEMS) > 0) {
        return;
    }

    construction_warnings warnings("#needs_gems");

    const bool can_produce_gems = g_city.can_produce_resource(RESOURCE_GEMS);
    warnings.add_if(!can_produce_gems, "#build_gem_mine");

    const bool can_import_gems = g_empire.can_import_resource(RESOURCE_GEMS, true);
    warnings.add_if(!can_import_gems, "#setup_trade_route_to_import");
    
    const bool is_import_gems = (city_resource_trade_status(RESOURCE_GEMS) == TRADE_STATUS_IMPORT);
    warnings.add_if(!is_import_gems, "#overseer_of_commerce_to_import");
}

bool building_jewels_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_GEMS) / 100.0) - 1);
    if (amount >= 0) {
        int image_id = image_id_from_group(GROUP_RESOURCE_STOCK_GEMS_2) + amount;
        
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = image_id;
        command.pixel = point + vec2i(65, 3);
        command.mask = color_mask;
    }

    return true;
}
