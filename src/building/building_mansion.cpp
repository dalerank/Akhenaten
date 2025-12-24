#include "building_mansion.h"

#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/text.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "figuretype/figure_governor.h"
#include "city/city.h"
#include "city/victory.h"
#include "city/buildings.h"
#include "city/city_finance.h"
#include "city/ratings.h"
#include "city/city_message.h"
#include "widget/city/ornaments.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "js/js_game.h"
#include "core/object_property.h"
#include "io/gamefiles/lang.h"
#include "game/game_events.h"
#include "figure/service.h"
#include "core/random.h"
#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_personal_mansion);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_family_mansion);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dynasty_mansion);

void building_mansion::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);
    g_city.buildings.track_building(base, false);
    auto &d = runtime_data();
    d.personal_savings_storage = 0;
}

void building_mansion::on_post_load() {
    g_city.buildings.track_building(base, true);
    // Sync personal savings from kingdome to mansion on load
    auto &d = runtime_data();
    if (d.personal_savings_storage == 0) {
        d.personal_savings_storage = g_city.kingdome.personal_savings;
    }
}

void building_mansion::update_count() const {
    // Mansion is active if it's valid and has road access (needed for salary payments and governor access)
    const bool is_active = (base.has_road_access);
    g_city.buildings.track_building(base, is_active);
}

void building_mansion::spawn_figure() {
    common_spawn_figure_trigger(current_params().min_houses_coverage);

    if (base.has_figure(BUILDING_SLOT_GOVERNOR)) {
        return;
    }

    tile2i road_tile = map_closest_road_within_radius(tile(), size(), 2);
    if (road_tile.valid()) {
        figure *f = figure_create(FIGURE_GOVERNOR, road_tile, DIR_4_BOTTOM_LEFT);
        f->advance_action(ACTION_120_GOVERNOR_CREATED);
        f->set_home(&base);
        f->wait_ticks = 10 + (base.map_random_7bit & 0xf);
        base.set_figure(BUILDING_SLOT_GOVERNOR, f);
    }
}

void building_mansion::update_graphic() {
    set_animation(animkeys().work);
}

int building_mansion::window_info_handle_mouse(const mouse *m, object_info &c) {
    return 0;
}

bool building_mansion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    switch (type()) {
    case BUILDING_PERSONAL_MANSION: 
    case BUILDING_FAMILY_MANSION:
    case BUILDING_DYNASTY_MANSION:
        {
            const animation_t &ranim = anim(animkeys().work);
            draw_normal_anim(ctx, point, tile, mask);
        }
        break;

    default:
        verify_no_crash(false);
    }
    return true;
}

void building_mansion::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_INT32, &d.personal_savings_storage);
}

bvariant building_mansion::get_property(const xstring &domain, const xstring &name) const {
    auto &d = runtime_data();
    if (domain == tags().building && name == tags().tax_income_or_storage) {
        // Sync with kingdome.personal_savings to show current total
        int32_t mansion_savings = d.personal_savings_storage;
        int32_t kingdome_savings = g_city.kingdome.personal_savings;
        // Return the maximum to ensure we show correct total
        return bvariant((int16_t)std::max(mansion_savings, (int32_t)kingdome_savings));
    }

    return building_impl::get_property(domain, name);
}

bool building_mansion::is_protected_by_police() const {
    // Check if there are constables near the mansion (within 2 tiles radius, similar to figure_provide_service)
    grid_area area = map_grid_get_area(tile(), size(), 2);
    bool has_protection = false;
    
    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i check_tile) {
        int figure_id = map_figure_id_get(check_tile);
        while (figure_id > 0 && !has_protection) {
            figure *f = figure_get(figure_id);
            if (f && f->type == FIGURE_CONSTABLE && f->state == FIGURE_STATE_ALIVE) {
                has_protection = true;
                return;
            }
            if (figure_id == f->next_figure) {
                break;
            }
            figure_id = f->next_figure;
        }
    });
    
    return has_protection;
}

void building_mansion::check_theft_from_mansions() {
    // Check for theft only if there are criminals in the city
    if (g_city.sentiment.criminals <= 0) {
        return;
    }
    
    // Check theft probability based on crime level
    int crime_chance = 100 - g_city.sentiment.value;
    if (crime_chance < 10) {
        return; // Too low crime, no theft
    }
    
    // Random chance based on crime level (1-5% per update cycle if high crime)
    if ((random_byte() % 100) > (crime_chance / 10)) {
        return;
    }
    
    const e_building_type mansion_types[] = {
        BUILDING_PERSONAL_MANSION,
        BUILDING_FAMILY_MANSION,
        BUILDING_DYNASTY_MANSION
    };
    
    for (e_building_type type : mansion_types) {
        const auto tracked = g_city.buildings.tracked_buildings()[type];
        for (auto id : tracked) {
            building *b = building_get(id);
            if (!b || !b->is_valid() || b->state != BUILDING_STATE_VALID) {
                continue;
            }
            
            auto mansion = b->dcast_mansion();
            if (!mansion || !mansion->has_road_access()) {
                continue;
            }
            
            // Check if protected by police
            if (mansion->is_protected_by_police()) {
                continue; // Protected, skip
            }
            
            auto &d = mansion->runtime_data();
            if (d.personal_savings_storage <= 0) {
                continue; // No savings to steal
            }
            
            // Calculate amount to steal (10-50% of savings, or max 200 Db)
            int savings = d.personal_savings_storage;
            int steal_amount = savings * (10 + (random_byte() % 40)) / 100;
            if (steal_amount > 200) {
                steal_amount = 200 - (random_byte() % 50);
            }
            if (steal_amount < 10) {
                steal_amount = 10;
            }
            
            if (steal_amount > savings) {
                steal_amount = savings;
            }
            
            if (steal_amount > 0) {
                // Steal from mansion
                d.personal_savings_storage -= steal_amount;
                
                // Also reduce from kingdome savings
                if (g_city.kingdome.personal_savings >= steal_amount) {
                    g_city.kingdome.personal_savings -= steal_amount;
                } else {
                    g_city.kingdome.personal_savings = 0;
                }
                
                // Process through finance system
                g_city.finance.process_stolen(steal_amount);
                
                // Show message
                bool show_popup = (g_city.sentiment.last_mugger_message <= 0);
                if (show_popup) {
                    g_city.sentiment.last_mugger_message = 90;
                }
                
                // Use the existing localization message for mansion theft
                // Show message similar to city_show_message_criminal
                bool show_popup_message = show_popup;
                events::emit(event_message{ show_popup_message, "thief_stole_savings", steal_amount, b->tile.grid_offset() });
                
                // Only steal from one mansion per check
                return;
            }
        }
    }
}

bool building_mansion::exist_in_city() {
    const e_building_type types[] = {
        BUILDING_PERSONAL_MANSION,
        BUILDING_FAMILY_MANSION,
        BUILDING_DYNASTY_MANSION
    };

    for (e_building_type type : types) {
        if (g_city.buildings.count_total(type) > 0)
            return true;
    }

    return false;
}
