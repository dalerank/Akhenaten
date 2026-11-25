#include "city/object_info.h"
#include "city/city_figures.h"

#include "window/window_info.h"
#include "figure/figure.h"
#include "figure/figure_static_params.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

ANK_GLOBAL_OBJECT(common_info_window::get_object_info(), __object_info, bid, group_id, grid_offset, offset,
  terrain_type, figure_selected_index, help_id, help_link, can_play_sound, go_to_advisor_first, go_to_advisor_left_a,
  go_to_advisor_left_b);

int __object_info_figure_count() {
    return (int)common_info_window::get_object_info().figure_ids.size();
}
ANK_FUNCTION(__object_info_figure_count)

int __object_info_figure_id() {
    return common_info_window::get_object_info().figure_get_id();
}
ANK_FUNCTION(__object_info_figure_id)

void __object_info_select_figure(int index) {
    object_info& info = common_info_window::get_object_info();
    if (index < 0 || index >= (int)info.figure_ids.size()) {
        return;
    }

    info.figure_selected_index = (uint8_t)index;
    info.can_play_sound = true;
    events::emit(event_update_tile_info{true});
}
ANK_FUNCTION_1(__object_info_select_figure)

void __figure_info_set_help(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    object_info& c = common_info_window::get_object_info();
    const auto& meta = figure_static_params::get(f->type).meta;
    c.help_link = meta.help_link;
    c.help_id = 0;
    c.group_id = meta.text_id;
}
ANK_FUNCTION_1(__figure_info_set_help)
