#include "building_jewels_workshop.h"

#include "building/building_workshop.h"
#include "city/city_resource_handle.h"
#include "empire/empire.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "js/js_game.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/animkeys.h"
#include "widget/city/ornaments.h"
#include "grid/building.h"
#include "grid/grid.h"
#include <set>

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

    const bool is_import_gems = (city_resource_gems.trade_status() == TRADE_STATUS_IMPORT);

    warnings.add_if(!city_resource_gems.can_produce(), "#build_gem_mine");
    warnings.add_if(!city_resource_gems.can_import(true), "#setup_trade_route_to_import");
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

void building_jewels_workshop::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
}

int building_jewels_workshop::count_nearby_workshops() const {
    std::set<building_id> nearby_workshop_ids;
    
    // Get main building ID of current workshop
    building *current_main = base.main();
    building_id current_main_id = current_main->id;
    
    // Get all tiles adjacent to this building
    grid_tiles_sm adjacent_tiles = map_grid_get_adjacent_tiles_sm(&base, 1);
    
    for (const auto &tile : adjacent_tiles) {
        building_id bid = map_building_at(tile);
        if (bid > 0) {
            building *b = building_get(bid);
            if (b && b->state == BUILDING_STATE_VALID) {
                // Get main building to avoid counting parts separately
                building *main_b = b->main();
                if (main_b && main_b->type == BUILDING_JEWELS_WORKSHOP && main_b->id != current_main_id) {
                    nearby_workshop_ids.insert(main_b->id);
                }
            }
        }
    }
    
    return nearby_workshop_ids.size();
}

void building_jewels_workshop::start_production() {
    bool can_start_b = true;
    if (base.input.resource_second != RESOURCE_NONE) {
        can_start_b = (base.stored_amount_second >= 100);
    } 
    
    bool can_start_a = true;
    if (base.input.resource != RESOURCE_NONE) {
        can_start_a = (base.stored_amount_first >= 100);
    }
    
    if (can_start_b && can_start_a) {
        auto &d = runtime_data();
        d.progress = 0;
       // d.has_raw_materials = true;
        
        int nearby_count = count_nearby_workshops();
        int reduction_per_workshop = current_params().material_reduction_per_nearby_workshop;
        int material_reduction = nearby_count * reduction_per_workshop;
        
        // Apply reduction to second resource if present
        if (base.stored_amount_second >= 100) {
            int amount_to_consume = std::max(100 - material_reduction, 50); // Minimum 50, maximum reduction to 50
            base.stored_amount_second -= amount_to_consume;
        }
        
        // Apply reduction to first resource
        if (base.stored_amount_first >= 100) {
            int amount_to_consume = std::max(100 - material_reduction, 50); // Minimum 50, maximum reduction to 50
            base.stored_amount_first -= amount_to_consume;
        }
        
        production_started();
    }
}
