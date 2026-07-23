#include "window/window_building_info.h"

#include "building/building_fishing_wharf.h"
#include "figuretype/figure_fishing_boat.h"
#include "window/building/common.h"
#include "city/object_info.h"

struct info_window_fishing_wharf : public building_info_window_t<info_window_fishing_wharf> {
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_fishing_wharf();
    }

    virtual void init(object_info &c) override;
};

info_window_fishing_wharf fishing_wharf_infow;

void info_window_fishing_wharf::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason = { c.group_id, 0 };
    if (!b->has_road_access) {
        ui["warning_text"] = lang_text_from_key("#building_no_road_access");
    } else if (!b->get_figure(BUILDING_SLOT_BOAT)->is_valid()) {
        reason = { c.group_id, 2 };
        ui["warning_text"] = reason;
    } else {
        figure *boat = b->get_figure(BUILDING_SLOT_BOAT);
        switch (boat->action_state) {
        case ACTION_191_FISHING_BOAT_GOING_TO_FISH: reason.id = 3; break;
        case ACTION_192_FISHING_BOAT_FISHING: reason.id = 4; break;
        case ACTION_193_FISHING_BOAT_GOING_TO_WHARF: reason.id = 5; break;
        case ACTION_194_FISHING_BOAT_AT_WHARF: reason.id = 6; break;
        case ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH: reason.id = 7; break;
        default: reason.id = 8; break;
        }
        ui["warning_text"] = reason;
    }

    ui["resource_img"].image(RESOURCE_FISH);
    ui["storage_desc"].text_var("Stored fish %d", b->stored_amount(RESOURCE_FISH));
}