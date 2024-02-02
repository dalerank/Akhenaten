#pragma once

#include "game/resource.h"
#include "building/building.h"

class building_bazaar : public building_impl {
public:
    building_bazaar(building &b) : building_impl(b) {}
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual void update_day() override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;

    building *get_storage_destination();
};

int building_bazaar_get_max_food_stock(building* market);
int building_bazaar_get_max_goods_stock(building* market);
bool is_good_accepted(int index, building* market);
void toggle_good_accepted(int index, building* market);
void unaccept_all_goods(building* market);
