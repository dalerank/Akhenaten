#include "settings.h"

#include "city/constants.h"
#include "js/js_game.h"
#include "game/game.h"
#include "platform/renderer.h"
#include "dev/debug.h"
#include "game/system.h"
#include "core/profiler.h"

void ank_global_obj_bind_field(js_State *J, js_StringNode name, e_tooltip_mode *ptr) {
    js_register_bound_int_property(J, name, reinterpret_cast<int *>(ptr));
}

void ank_global_obj_bind_field(js_State *J, js_StringNode name, vec2i *ptr) {
    js_newobject(J);
    ank_global_obj_bind_field(J, js_intern("x"), &ptr->x);
    ank_global_obj_bind_field(J, js_intern("y"), &ptr->y);
    js_setproperty(J, -2, name);
}

ANK_GLOBAL_OBJECT(g_settings, __game_settings,
    display_size,
    tooltips_mode,
    warnings,
    gods_enabled,
    victory_video,
    popup_messages,
    pyramid_speedup,
    last_advisor);

ANK_GLOBAL_OBJECT(game, __game,
    monthly_autosave,
    pending_load_type,
    pending_save_type,
    mission_choice_open_scenario_id);

int __game_difficulty() { return game_difficulty(); }
ANK_FUNCTION(__game_difficulty)

void __game_decrease_difficulty() { g_settings.difficulty.decrease(); }
ANK_FUNCTION(__game_decrease_difficulty)

void __game_increase_difficulty() { g_settings.difficulty.increase(); }
ANK_FUNCTION(__game_increase_difficulty)

bool __game_is_fullscreen_only() { return g_render.is_fullscreen_only(); }
ANK_FUNCTION(__game_is_fullscreen_only)

bool __game_debug_properties() { return game.debug_properties; }
ANK_FUNCTION(__game_debug_properties)

bool __game_writing_video() { return game.get_write_video(); }
ANK_FUNCTION(__game_writing_video)

void __game_toggle_writing_video() { game.set_write_video(!game.get_write_video()); }
ANK_FUNCTION(__game_toggle_writing_video)

int __game_debug_render_mode() { return debug_render_mode(); }
ANK_FUNCTION(__game_debug_render_mode)

void __game_set_debug_render_mode(int mode) { set_debug_render_mode((e_debug_render)mode); }
ANK_FUNCTION_1(__game_set_debug_render_mode)

int display_options_video_modes_count() { return (int)get_video_modes().size(); }
ANK_FUNCTION(display_options_video_modes_count)

pcstr display_options_video_get_mode(int index) {
    static thread_local bstring128 buf;
    const auto modes = get_video_modes();
    if (index < 0 || index >= (int)modes.size()) {
        buf.clear();
        return "";
    }
    buf = modes[index].str.c_str();
    return buf.c_str();
}
ANK_FUNCTION_1(display_options_video_get_mode)

bool __display_options_is_fullscreen() { return g_settings.is_fullscreen(e_setting_none); }
ANK_FUNCTION(__display_options_is_fullscreen)

xstring __display_options_video_driver_caption() {
    return get_video_driver();
}
ANK_FUNCTION(__display_options_video_driver_caption)