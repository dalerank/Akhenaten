#include "state.h"

#include "city/city.h"
#include "core/random.h"
#include "overlays/city_overlay.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/ring.h"
#include "game/game.h"

void game_state_init() {
    g_city.victory_state.reset();
    g_city.migration.reset();
    map_ring_init();

    city_view_reset_orientation();
    //    city_view_go_to_screen_tile_corner(screen_tile(76, 152), true);

    random_generate_pool();
}

void game_state_toggle_paused() {
    game.paused = !game.paused;
}

void game_state_reset_overlay() {
    game.current_overlay = OVERLAY_NONE;
    game.previous_overlay = OVERLAY_NONE;
}

void game_state_toggle_overlay() {
    e_overlay previous_overlay = game.previous_overlay;
    game.previous_overlay = game.current_overlay;
    game.current_overlay = previous_overlay;
    map_clear_highlights();
}

void game_state_set_overlay(e_overlay overlay) {
    if (overlay == OVERLAY_NONE) {
        game.previous_overlay = game.current_overlay;
    } else {
        game.previous_overlay = OVERLAY_NONE;
    }
    game.current_overlay = overlay;
    map_clear_highlights();
}
