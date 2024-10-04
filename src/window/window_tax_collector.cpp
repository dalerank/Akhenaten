#include "window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/finance.h"
#include "window/building/common.h"
#include "graphics/window.h"
#include "config/config.h"
#include "js/js_game.h"

struct taxcollector_info_window_t : public building_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_tax_collector();
    }
};

taxcollector_info_window_t g_taxcollector_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_taxcollector_info_window);
void config_load_taxcollector_info_window() {
    g_taxcollector_info_window.load("taxcollector_info_window");
}

void taxcollector_info_window_t::window_info_background(object_info &c) {
    c.go_to_advisor.left_a = ADVISOR_FINANCIAL;

    building_info_window::window_info_background(c);

    building *b = c.building_get();

    ui["title"] = ui::str(106, 0);
    ui["deben_icon"].image(RESOURCE_DEBEN);

    int amount = config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM) ? b->deben_storage : b->tax_income_or_storage;
    ui["money_text"].text_var("%s %d %s", ui::str(106, 2), amount, ui::str(8, 0));

    int tax_block = c.bgsize.x * 16 / 2;
    ui["tax_level"].text_var("%s %d%%", ui::str(60, 1), city_finance_tax_percentage());
    ui["dec_tax"].onclick([] {
        city_finance_change_tax_percentage(-1);
        window_invalidate();
    });

    ui["inc_tax"].onclick([] {
        city_finance_change_tax_percentage(1);
        window_invalidate();
    });

    std::pair<int, int> reason = {106, 9};
    if (!c.has_road_access) { reason = {69, 25}; } 
    else if (b->num_workers <= 0) { reason = {106, 10}; }
    else if (c.worker_percentage >= 25) { reason.second = approximate_value(c.worker_percentage / 100.f, make_array(8, 7, 6, 5)); }

    ui["warning_text"] = ui::str(reason.first, reason.second);  

    fill_employment_details(c);
}
