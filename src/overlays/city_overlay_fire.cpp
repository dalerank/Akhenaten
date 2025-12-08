#include "city_overlay_fire.h"

#include "game/state.h"
#include "grid/building.h"
#include "grid/property.h"
#include "figure/figure.h"
#include "game/game_config.h"
#include "building/building_house.h"
#include "building/building_firehouse.h"
#include "graphics/elements/tooltip.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "core/bstring.h"

city_overlay_fire g_city_overlay_fire;

int city_overlay_fire::get_column_height(const building *b) const {
    if (!!game_features::gameui_overlay_show_gray_buildings) {
        return COLUMN_TYPE_NONE;
    }

    if (b->prev_part_building_id || b->fire_proof) {
        return COLUMN_TYPE_NONE;
    }

    auto house = ((building*)b)->dcast_house();
    if ((house && house->house_population() <= 0) || b->type == BUILDING_GARDENS
        || b->type == BUILDING_BANDSTAND || b->type == BUILDING_BOOTH) {
        return COLUMN_TYPE_NONE;
    }

    return b->fire_risk / 100;
}

bool city_overlay_fire::show_building(const building *b) const {
    const bool need_show = std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
    if (need_show) {
        return true;
    }

    int percentage = calc_percentage<int>(b->fire_risk, 1000);
    return (percentage > 10);
}

color city_overlay_fire::color_mask_building(const building *b) const {
    const bool need_show = std::find(buildings.begin(), buildings.end(), b->type) != buildings.end();
    if (need_show) {
        return COLOR_MASK_NONE;
    }

    int percentage = calc_percentage<int>(b->fire_risk, 1000);
    return color_from_green_to_red(percentage);
}

xstring city_overlay_fire::get_tooltip_for_building(tooltip_context *c, const building *b) {
    // Find tooltips for this building type
    const building_tooltips_t *building_tooltip_config = nullptr;
    for (const auto &bt : building_tooltips) {
        if (bt.building_type == b->type) {
            building_tooltip_config = &bt;
            break;
        }
    }
    
    if (building_tooltip_config && !building_tooltip_config->tooltips.empty()) {
        vec2i mpos = c->mpos;
        building *building_ptr = const_cast<building*>(b);
        
        int num_lines = (int)building_tooltip_config->tooltips.size();
        int width = 220;
        int line_height = 14;
        int height = num_lines * line_height + 10;
        vec2i pos;
        
        // Position tooltip similar to palace
        if (mpos.x < width + 20)
            pos.x = mpos.x + 20;
        else {
            pos.x = mpos.x - width - 20;
        }
        
        if (mpos.y < 200) {
            pos.y = mpos.y + 10;
        } else if (mpos.y + height - 32 > screen_height()) {
            pos.y = screen_height() - height;
        } else {
            pos.y = mpos.y - 32;
        }
        
        ui::begin_widget(pos);
        
        ui::fill_rect({ 0, 0 }, { width, height }, COLOR_TOOLTIP_FILL);
        ui::border({ 0, 0 }, { width, height }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None);
        
        int y_offset = 5;
        int label_x = 5;
        int value_x = 140;
        
        ui::widget temp_widget;
        for (const auto &tooltip_line : building_tooltip_config->tooltips) {
            bstring1024 formatted = temp_widget.format(building_ptr->dcast(), tooltip_line.c_str());
            
            // Split line into label and value parts (format: "label\tvalue")
            int at_pos = formatted.find('\t');
            if (at_pos >= 0) {
                bstring512 label_part;
                label_part.ncat(formatted.c_str(), at_pos);
                ui::label_colored(label_part.c_str(), { label_x, y_offset }, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
                
                // Draw value part starting from value_x
                pcstr value_start = formatted.c_str() + at_pos;
                ui::label_colored(value_start, { value_x, y_offset }, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
            } else {
                // No \t separator, draw as single label
                ui::label(formatted.c_str(), { label_x, y_offset }, FONT_SMALL_SHADED, UiFlags_None);
            }
            
            y_offset += line_height;
        }
        
        ui::end_widget();
        
        return {}; // Return empty string to use custom draw function
    }
    
    // Default fire risk tooltip for other buildings
    auto main = const_cast<building*>(b)->main();
    if (main->fire_risk <= 0)
        return ui::str(66, 46);

    if (main->fire_risk <= 200)
        return ui::str(66, 47);

    if (main->fire_risk <= 400)
        return ui::str(66, 48);

    if (main->fire_risk <= 600)
        return ui::str(66, 49);

    if (main->fire_risk <= 800)
        return ui::str(66, 50);

    return ui::str(66, 51);
}
