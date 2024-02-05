#include "building_firehouse.h"

#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"

#include "dev/debug.h"

static void console_command_nofire(std::istream &, std::ostream &) {
    buildings_valid_do([&] (building &b) {
        b.fire_risk = 0;
    });
}

declare_console_command(nofire, console_command_nofire);

void building_firehouse::spawn_figure() {
    base.common_spawn_roamer(FIGURE_FIREMAN, 50, FIGURE_ACTION_70_FIREMAN_CREATED);
}

void building_firehouse::window_info_background(object_info &c) {
    const int32_t LANG_GROUP_ID = 164;
    c.help_id = 81;                                      // TODO: change to firehouse
    window_building_play_sound(&c, "wavs/prefecture.wav"); // TODO: change to firehouse
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(LANG_GROUP_ID, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (!base.num_workers)
        window_building_draw_description(c, LANG_GROUP_ID, 9);
    else {
        if (base.has_figure(0))
            window_building_draw_description(c, LANG_GROUP_ID, 2);
        else
            window_building_draw_description(c, LANG_GROUP_ID, 3);

        if (c.worker_percentage >= 100)
            window_building_draw_description_at(c, 72, LANG_GROUP_ID, 4);
        else if (c.worker_percentage >= 75)
            window_building_draw_description_at(c, 72, LANG_GROUP_ID, 5);
        else if (c.worker_percentage >= 50)
            window_building_draw_description_at(c, 72, LANG_GROUP_ID, 6);
        else if (c.worker_percentage >= 25)
            window_building_draw_description_at(c, 72, LANG_GROUP_ID, 7);
        else
            window_building_draw_description_at(c, 72, LANG_GROUP_ID, 8);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}