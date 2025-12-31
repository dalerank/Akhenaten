#include "building/building_festival_square.h"

#include "sound/sound_building.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "window/hold_festival.h"
#include "game/game.h"
#include "city/city.h"

struct festival_square_info_window : building_info_window_t<festival_square_info_window> {
    virtual void window_info_background(object_info &c) override;
    virtual void init(object_info &c) override;
    
    void update_festival_state();

    virtual bool check(object_info &c) override {
        return !!c.building_get()->dcast_festival_square();
    }
};

festival_square_info_window festival_square_infow;

void festival_square_info_window::update_festival_state() {
    if (g_city.festival.is_planned()) {
        int size = g_city.festival.selected_size;
        int months_left = g_city.festival.months_till_next();
        int planned_month = (game.simtime.month + months_left) % simulation_time_t::months_in_year;
        int festival_text_iffs[] = { 0, 10, 20, 31 };

        ui["hold_festival"].enabled = false;
        ui["planed_festival"].text_var("%s %s", ui::str(58, 34), ui::str(160, planned_month));
        ui["festival_advice"] = ui::str(295, festival_text_iffs[size] + months_left - 1);
        return;
    }

    ui["planed_festival"] = "";
    ui["hold_festival"].enabled = true;
    ui["hold_festival"] = ui::str(58, 16);
    ui["festival_advice"] = ui::str(58, 18 + g_city.festival.get_advice());
}

void festival_square_info_window::init(object_info &c) {
    ui["hold_festival"].onclick([this] {
        if (g_city.festival.is_planned()) {
            return;
        }
        
        ui::hold_festival_window::show(false, [this] {
            update_festival_state();
        });
    });

    update_festival_state();
}

void festival_square_info_window::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);
}