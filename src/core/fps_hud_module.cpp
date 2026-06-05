#include "core/app.h"

#include "game/game.h"
#include "game/game_config.h"
#include "graphics/color.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"

struct fps_hud_module_t {
    void draw(hud_end_context_t* ctx);
};

void fps_hud_module_t::draw(hud_end_context_t* ctx) {
    const bool main_windows = (g_window_manager.window_is("window_city") || g_window_manager.window_is("window_city_military")
                               || g_window_manager.window_is("window_city_warship") || g_window_manager.window_is("window_sliding_sidebar"));

    if (!game_features::gameui_draw_fps || !main_windows) {
        return;
    }

    const int y_offset = screen_height() - 24;
    const int y_offset_text = y_offset + 5;

    text_draw_number_colored(game.fps.last_fps, 'f', "", 5, y_offset_text, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
    text_draw_number_colored(ctx->time_between_run_and_draw - ctx->time_before_run, 'g', "", 40, y_offset_text,
      FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
    text_draw_number_colored(ctx->time_after_draw - ctx->time_between_run_and_draw, 'd', "", 70, y_offset_text,
      FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_RED);
}

void ANK_REGISTER_APPLICATION_MODULE(register_fps_hud_module) {
    static fps_hud_module_t module;
    g_app.register_hud_end_handler([&](void* ctx) { module.draw((hud_end_context_t*)ctx); });
}
