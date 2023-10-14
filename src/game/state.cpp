#include "state.h"

#include "city/victory.h"
#include "city/warning.h"
#include "core/random.h"
#include "overlays/city_overlay.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/ring.h"

struct state_data_t {
    bool paused;
    e_overlay current_overlay;
    e_overlay previous_overlay;
};

state_data_t g_state_data = {
    false,
    OVERLAY_NONE,
    OVERLAY_NONE
};

void game_state_init(void) {
    city_victory_reset();
    map_ring_init();

    city_view_reset_orientation();
    //    city_view_go_to_screen_tile_corner(screen_tile(76, 152), true);

    random_generate_pool();

    city_warning_clear_all();
}

bool game_state_is_paused(void) {
    return g_state_data.paused;
}

void game_state_unpause(void) {
    g_state_data.paused = 0;
}

void game_state_toggle_paused(void) {
    g_state_data.paused = g_state_data.paused ? 0 : 1;
}

e_overlay game_state_overlay() {
    return g_state_data.current_overlay;
}

void game_state_reset_overlay() {
    g_state_data.current_overlay = OVERLAY_NONE;
    g_state_data.previous_overlay = OVERLAY_NONE;
}

void game_state_toggle_overlay() {
    e_overlay previous_overlay = g_state_data.previous_overlay;
    g_state_data.previous_overlay = g_state_data.current_overlay;
    g_state_data.current_overlay = previous_overlay;
    map_clear_highlights();
}

void game_state_set_overlay(e_overlay overlay) {
    if (overlay == OVERLAY_NONE) {
        g_state_data.previous_overlay = g_state_data.current_overlay;
    } else {
        g_state_data.previous_overlay = OVERLAY_NONE;
    }
    g_state_data.current_overlay = overlay;
    map_clear_highlights();
}
