#include "window_info.h"

#include "building/building_bazaar.h"
#include "window/building/distribution.h"
#include "window/window_building_info.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "graphics/window.h"
#include "game/game.h"
#include "js/js_game.h"

struct bazaar_orders_window : public building_info_window_t<bazaar_orders_window> {
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
};

bazaar_orders_window bazaar_ordersw;


void window_bazaar_orders_show(object_info &c) {
    c.ui = &bazaar_ordersw;
    c.ui->window_info_background(c);
}

void bazaar_orders_window::window_info_background(object_info &c) {
}

void bazaar_orders_window::window_info_foreground(object_info &c) {
}