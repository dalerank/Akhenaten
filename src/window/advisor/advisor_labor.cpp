#include "advisor_labor.h"

#include "city/city_finance.h"
#include "city/city.h"
#include "core/calc.h"
#include "graphics/elements/ui.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "window/window_labor_priority.h"
#include "game/game.h"

ui::advisor_labors_window g_advisor_labor_window;

void ui::advisor_labors_window::init() {
    advisor_window::init();

    ui["dec_wages"].onclick([] {
        events::emit(event_finance_change_wages{ -1 });
    });

    ui["inc_wages"].onclick([] {
        events::emit(event_finance_change_wages{ 1 });
    });
}

int ui::advisor_labors_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    return 0;
}

void ui::advisor_labors_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    auto cat_name = [] (int cat) {
        if (cat == LABOR_CATEGORY_CULTURE) 
             return "Culture";

        return ui::str(50, cat + 1);
    };

    const auto &item = ui["item"];
    const auto &item_image = ui["item_image"];
    const auto &items_area = ui["items_area"];
    const auto &item_priority = ui["item_priority"];
    const auto &item_category = ui["item_category"];
    const auto &item_needed = ui["item_needed"];
    const auto &item_allocated = ui["item_allocated"];
    for (int i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        vec2i offset = vec2i{ item.pos.x, item.pos.y * i } + items_area.pos;
        ui.button("", offset, item.pxsize())
            .onclick([category = i] {
                window_labor_priority_show(category);
            });

        const labor_category* cat = g_city.labor.category(i);
        if (cat->priority) {
            ui.image(item_image.image(), offset + item_image.pos );
            ui.label(bstring32(cat->priority), offset + item_priority.pos, item_priority.font());
        }

        ui.label(cat_name(i), offset + item_category.pos, item_category.font());
        ui.label(bstring32(cat->workers_needed), offset + item_needed.pos, item_needed.font());

        e_font font = (cat->workers_needed != cat->workers_allocated)
                            ? item_allocated.font()
                            : item_allocated.font_hover();
        ui.label(bstring32(cat->workers_allocated), offset + item_allocated.pos, font);
    }
    ui.end_widget();
}

advisor_window* ui::advisor_labors_window::instance() {
    return &g_advisor_labor_window;
}
