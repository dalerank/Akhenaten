#include "window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "window/building/common.h"

struct entertainment_info_window : public building_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return building_get(c.building_id)->is_entertainment();
    }
};

entertainment_info_window entertainment_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_entertainment_info_window);
void config_load_entertainment_info_window() {
    entertainment_infow.load("entertainment_info_window");
}

void entertainment_info_window::window_info_background(object_info &c) {
    c.go_to_advisor.first = ADVISOR_ENTERTAINMENT;
    building_info_window::window_info_background(c);

    building *b = building_get(c.building_id);

    std::pair<int, int> reason = {c.group_id, 6};
    if (!c.has_road_access) { reason = {69, 25}; }
    else if (building_get(c.building_id)->num_workers <= 0) { reason.second = 7; }
    else { reason.second = approximate_value(c.worker_percentage / 100.f, make_array(5, 4, 3, 2)); }
 
    ui["warning_text"] = ui::str(reason.first, reason.second);
    draw_employment_details(c);
}