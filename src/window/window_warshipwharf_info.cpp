#include "window_building_info.h"

#include "building/building_warship_wharf.h"
#include "figuretype/figure_war_ship.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "input/input.h"
#include "grid/water.h"
#include "graphics/window.h"
#include "building/common.h"
#include "figure/figure.h"

struct warshipwharf_info_window : public building_info_window_t<warshipwharf_info_window> {
    using widget::archive_load;
    virtual void archive_load(archive arch) override {
        widget::archive_load(arch);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->type == BUILDING_WARSHIP_WHARF;
    }
};

warshipwharf_info_window warshipwharf_infow;

void warshipwharf_info_window::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    map_water_update_docking_points(*b, b->dcast()->get_orientation(), 2);

    std::pair<int, int> reason = { c.group_id, 0 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } else if (!b->get_figure(BUILDING_SLOT_BOAT)->is_valid()) {
        reason = { c.group_id, 2 };
    } else {
        figure *boat = b->get_figure(BUILDING_SLOT_BOAT);
        switch (boat->action_state) {
        case ACTION_203_WARSHIP_MOORED: reason.second = 2; break;
        case ACTION_204_WARSHIP_ATTACK: reason.second = 3; break;
        default: reason.second = 8; break;
        }
    }

    ui["resource_img"].image(RESOURCE_FISH);
    ui["warning_text"] = ui::str(reason.first, reason.second);
    ui["storage_desc"].text_var("Stored weapons %d", b->stored_amount_first);
}