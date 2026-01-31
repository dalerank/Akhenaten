#include "building/building_bazaar.h"
#include "window/window_building_info.h"
#include "js/js_game.h"
#include "graphics/elements/ui_js.h"
#include "js/js_events.h"

struct bazaar_info_window : public building_info_window_t<bazaar_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_bazaar();
    }
};

bazaar_info_window g_bazaar_infow;

struct bazaar_info_window_init { vec2i pos; int bid; };
ANK_REGISTER_STRUCT_WRITER(bazaar_info_window_init, pos, bid);

void bazaar_info_window::init(object_info &c) {
    building_info_window::init(c);
    ui.event(bazaar_info_window_init{ pos, c.bid });
}