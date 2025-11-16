#include "building/building_brewery.h"

#include "building/building_workshop.h"
#include "widget/city/ornaments.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "empire/empire.h"
#include "game/game_config.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "figure/service.h"

#include "js/js_game.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "dev/debug.h"

#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_brewery);

declare_console_command(add_beer, game_cheat_add_resource<RESOURCE_BEER>);
declare_console_command(add_barley, game_cheat_add_resource<RESOURCE_BARLEY>);

bool building_brewery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &ranim = anim(animkeys().work);
    building_draw_normal_anim(ctx, point, &base, tile, ranim, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().barley);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}

void building_brewery::update_preproduction() {
    building_industry::update_preproduction();

    update_water_supply();
}

void building_brewery::on_place_checks() {
    construction_warnings warnings("#needs_barley");

    // Check for barley
    if (g_city.buildings.count_industry_active(RESOURCE_BARLEY) > 0) {
        // Barley available, skip barley warnings
    } else if (g_city.resource.yards_stored(RESOURCE_BARLEY) > 0) {
        // Barley in storage, skip barley warnings
    } else {
        const bool can_produce_barley = g_city.can_produce_resource(RESOURCE_BARLEY);
        const bool can_import_barley = g_empire.can_import_resource(RESOURCE_BARLEY, true);
        const bool is_import_barley = (city_resource_trade_status(RESOURCE_BARLEY) == TRADE_STATUS_IMPORT);
        
        warnings.add_if(!can_produce_barley, "#needs_barley");
        warnings.add_if(!can_import_barley, "#setup_trade_route_to_import");
        warnings.add_if(!is_import_barley, "#overseer_of_commerce_to_import");
    }

    // Check for water access if feature is enabled
    if (!!game_features::gameplay_brewery_requires_water) {
        bool has_water = map_terrain_exists_tile_in_area_with_type(base.tile, base.size, TERRAIN_GROUNDWATER) ||
                         map_terrain_exists_tile_in_area_with_type(base.tile, base.size, TERRAIN_FOUNTAIN_RANGE) ||
                         map_terrain_exists_tile_in_radius_with_type(base.tile, base.size, 3, TERRAIN_WATER) ||
                         map_terrain_exists_tile_in_radius_with_type(base.tile, base.size, 3, TERRAIN_FLOODPLAIN);
        
        warnings.add_if(!has_water, "#needs_water_access");
    }
}

void building_brewery::on_create(int orientation) {
    building_industry::on_create(orientation);
    
    if (!!game_features::gameplay_brewery_requires_water) {
        set_water_stored(0);
    }
}

void building_brewery::bind_dynamic(io_buffer *iob, size_t version) {
    building_industry::bind_dynamic(iob, version);
    
    // No additional binding needed
}

bool building_brewery::can_play_animation() const {
    if (!building_industry::can_play_animation()) {
        return false;
    }

    if (!!game_features::gameplay_brewery_requires_water) {
        // Need both barley and water to produce
        if (base.stored_amount(RESOURCE_BARLEY) < 100) {
            return false;
        }
        
        if (water_stored() < 50) {
            return false;
        }
    } else {
        // Original behavior: only check barley
        if (base.stored_amount(RESOURCE_BARLEY) < 100) {
            return false;
        }
    }

    return true;
}

void building_brewery::update_production() {
    if (!!game_features::gameplay_brewery_requires_water) {
        auto &d = runtime_data();

        // Consume 1 unit of water per day during active production
        if (water_stored() > 0) {
            set_water_stored(water_stored() - 1);
        } else {
            return; // No water, halt production
        }
        
        // Update water supply (slow replenishment from well)
        update_water_supply();
    }
    
    building_industry::update_production();
}

void building_brewery::production_started() {
    auto &d = runtime_data();
    if (!!game_features::gameplay_brewery_requires_water) {
        int current_water = water_stored();
        current_water = std::max(0, current_water - current_params().water_amount_for_production);
        set_water_stored(current_water);
    }
}

void building_brewery::start_production() {
    if (!!game_features::gameplay_brewery_requires_water) {
        // Check if we have enough water (need at least 50 units to start)
        if (water_stored() < current_params().water_amount_for_production) {
            return; // Can't start production without water
        }

        building_industry::start_production();
    } else {
        building_industry::start_production();
    }
}

bool building_brewery::has_water_access() const {
    if (!game_features::gameplay_brewery_requires_water) {
        return true; // Feature disabled, no water requirement
    }
    
    return map_terrain_exists_tile_in_area_with_type(base.tile, base.size, TERRAIN_GROUNDWATER) ||
           map_terrain_exists_tile_in_area_with_type(base.tile, base.size, TERRAIN_FOUNTAIN_RANGE) ||
           map_terrain_exists_tile_in_radius_with_type(base.tile, base.size, 3, TERRAIN_WATER) ||
           map_terrain_exists_tile_in_radius_with_type(base.tile, base.size, 3, TERRAIN_FLOODPLAIN);
}

void building_brewery::update_water_supply() {
    if (!game_features::gameplay_brewery_requires_water) {
        return;
    }
    
    int current_water = water_stored();
    if (current_water >= current_params().max_water_storage) {
        return;
    }
    
    // Slow water replenishment from nearby well (TERRAIN_FOUNTAIN_RANGE)
    if (!map_terrain_exists_tile_in_area_with_type(base.tile, base.size, TERRAIN_FOUNTAIN_RANGE)) {
        return;
    }
    
    set_water_stored(current_water + 1);
}
