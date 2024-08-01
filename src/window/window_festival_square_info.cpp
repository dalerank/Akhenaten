#include "building/building_festival_square.h"

#include "sound/sound_building.h"
#include "window/building/common.h"
#include "city/city.h"

ui::widget g_festival_square_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_festival_square_info_window);
void config_load_festival_square_info_window() {
    g_festival_square_info_window.load("festival_square_info_window");
}

void building_festival_square::window_info_background(object_info &c) {
    auto &ui = g_festival_square_info_window;

    c.help_id = params().meta.help_id;
    int group_id = params().meta.text_id;

    window_building_play_sound(&c, snd::get_building_info_sound(type()));

    ui["warning"] = ui::str(group_id, 1);
    ui["fest_months_last"].text_var("%d %s %s", g_city.festival.months_since_festival, ui::str(8, 5), ui::str(58, 15));
}

void building_festival_square::window_info_foreground(object_info &ctx) {
    g_festival_square_info_window.draw();
}