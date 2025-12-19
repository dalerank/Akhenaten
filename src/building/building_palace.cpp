
#include "building_palace.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/ratings.h"
#include "city/city.h"
#include "game/resource.h"
#include "core/object_property.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/tooltip.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/ui.h"
#include "core/bstring.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/animkeys.h"
#include "grid/desirability.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "widget/city/ornaments.h"
#include "window/advisors.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "js/js_game.h"

struct info_window_palace : public building_info_window_t<info_window_palace> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_palace();
    }
};

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_village_palace);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_town_palace);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_city_palace);

info_window_palace palace_infow;

void building_palace::on_create(int orientation) {
    base.labor_category = current_params().labor_category;
}

void building_palace::on_post_load() {
    g_city.buildings.track_building(base, true);
}

void building_palace::on_destroy() {
    g_city.buildings.remove_palace(base);
}

void building_palace::update_count() const {
    g_city.buildings.track_building(base, true);
}

bool building_palace::can_play_animation() const {
    return worker_percentage() > 50;
}

void building_palace::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

void building_palace::draw_tooltip(tooltip_context *c) const {
    vec2i mpos = c->mpos;
    
    const auto &tooltip_lines = palace_params().tooltips;
    
    if (tooltip_lines.empty()) {
        return;
    }
    
    int width = 220;
    int line_height = 14;
    int height = (int)tooltip_lines.size() * line_height + 10;
    vec2i pos;

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
    
    for (const auto &line : tooltip_lines) {
        bstring1024 formatted = ui::format(this, line.c_str());
        
        // Split line into label and value parts (format: "label@value" or "label@value (extra)")
        int at_pos = formatted.find('\t');
        if (at_pos >= 0) {
            bstring512 label_part;
            label_part.ncat(formatted.c_str(), at_pos);
            ui::label_colored(label_part.c_str(), { label_x, y_offset }, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
            
            // Draw value part starting from value_x
            pcstr value_start = formatted.c_str() + at_pos + 1; // "\t"
            int value_width = ui::label_colored(value_start, { value_x, y_offset }, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
        } else {
            // No \t separator, draw as single label
            ui::label(formatted.c_str(), { label_x, y_offset }, FONT_SMALL_SHADED, UiFlags_None);
        }
        
        y_offset += line_height;
    }
    
    ui::end_widget();
}

bool building_palace::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    // Draw rating indicators (flags/poles that show city ratings)
    // int image_id = image_id_from_group(GROUP_BUILDING_PALACE);
    // ctx.img_generic(image_id + 1, point + vec2i{138, 44 - g_city.ratings.culture / 2}, color_mask);
    // ctx.img_generic(image_id + 2, point + vec2i{168, 36 - g_city.ratings.prosperity / 2}, color_mask);
    // ctx.img_generic(image_id + 3, point + vec2i{198, 27 - g_city.ratings.monument / 2}, color_mask);
    // ctx.img_generic(image_id + 4, point + vec2i{228, 19 - g_city.kingdome.rating / 2}, color_mask);
    
    // Draw unemployed people when unemployment is high
    // int unemployment_pct = g_city.labor.unemployment_percentage;
    // int homeless_image_id = image_id_from_group(GROUP_FIGURE_PEASANT);
    // if (unemployment_pct > 0)  ctx.img_generic(homeless_image_id + 108, point + vec2i{80, 0}, color_mask);
    // if (unemployment_pct > 5)  ctx.img_generic(homeless_image_id + 104, point + vec2i{230, -30}, color_mask);
    // if (unemployment_pct > 10) ctx.img_generic(homeless_image_id + 107, point + vec2i{100, 20}, color_mask);
    // if (unemployment_pct > 15) ctx.img_generic(homeless_image_id + 106, point + vec2i{235, -10}, color_mask);
    // if (unemployment_pct > 20) ctx.img_generic(homeless_image_id + 106, point + vec2i{66, 20}, color_mask);

    return true;
}

void building_palace::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, &d.tax_income_or_storage);
}

void building_palace::spawn_figure() {
    common_spawn_figure_trigger(50);
}

bvariant building_palace::get_property(const xstring &domain, const xstring &name) const {
    auto &d = runtime_data();
    if (domain == tags().building && name == tags().tax_income_or_storage) {
        return bvariant(d.tax_income_or_storage);
    }

    return building_impl::get_property(domain, name);
}

void info_window_palace::init(object_info &c) {
    building_info_window::init(c);

    building_impl *palace = c.building_get()->dcast();

    std::pair<int, int> reason = { c.group_id, 0 };
    if (!palace->has_road_access()) reason = { 69, 25 };
    else if (palace->num_workers() <= 0) reason.second = 10;
    else reason.second = approximate_value(palace->worker_percentage() / 100.f, make_array(9, 8, 7, 6, 5));

    ui["workers_desc"] = ui::str(reason.first, reason.second);

    ui["visit_advisor"].onclick([] {
        window_advisors_show_advisor(ADVISOR_RATINGS);
    });
}

