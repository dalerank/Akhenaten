#include "window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "window/building/common.h"

struct entertainment_info_window_t : public building_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return building_get(c.building_id)->is_entertainment();
    }
};

entertainment_info_window_t g_entertainment_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_entertainment_info_window);
void config_load_entertainment_info_window() {
    g_entertainment_info_window.load("entertainment_info_window");
}

void entertainment_info_window_t::window_info_background(object_info &c) {
    c.go_to_advisor.first = ADVISOR_ENTERTAINMENT;
    building_info_window::window_info_background(c);

    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, b->dcast()->get_sound());

    auto &ui = *c.ui;
    ui["title"] = ui::str(group_id, 0);

    std::pair<int, int> reason = {group_id, 6};
    if (!c.has_road_access) { reason = {69, 25}; }
    else if (building_get(c.building_id)->num_workers <= 0) { reason.second = 7; }
    else if (c.worker_percentage >= 100) { reason.second = 2; }
    else if (c.worker_percentage >= 75) { reason.second = 3; }
    else if (c.worker_percentage >= 50) { reason.second = 4; }
    else if (c.worker_percentage >= 25) { reason.second = 5; }
 
    ui["warning_text"] = ui::str(reason.first, reason.second);
    draw_employment_details_ui(ui, c, b, -1);
}