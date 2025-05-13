#include "window_building_info.h"

#include "building/building_tax_collector.h"
#include "city/object_info.h"
#include "city/city_finance.h"
#include "window/building/common.h"
#include "graphics/window.h"
#include "game/game_config.h"
#include "game/game_events.h"

struct taxcollector_info_window : public building_info_window_t<taxcollector_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_tax_collector();
    }
};

taxcollector_info_window taxcollector_infow;

void taxcollector_info_window::init(object_info &c) {
    c.go_to_advisor.left_a = ADVISOR_FINANCIAL;

    building_info_window::init(c);

    auto collector = c.building_get()->dcast_tax_collector();
    if (!collector) {
        return;
    }

    int amount = !!game_features::gameplay_change_new_tax_collection_system ? collector->deben_storage() : collector->tax_storage();
    ui["money_text"].text_var("%s %d %s", ui::str(c.group_id, 2), amount, ui::str(8, 0));

    ui["dec_tax"].onclick([] {
        events::emit(event_finance_change_tax{ -1 });
    });

    ui["inc_tax"].onclick([] {
        events::emit(event_finance_change_tax{ 1 });
    });

    textid reason = {c.group_id, 0};
    if (!collector->has_road_access()) { reason = {69, 25}; }
   
    
    ui["warning_text"] = ui::str(reason);
    
    uint8_t workers_desc = approximate_value(collector->worker_percentage() / 100.f, make_array(10, 9, 8, 7, 6, 5));
    ui["workers_desc"] = textid{c.group_id, workers_desc};
}
