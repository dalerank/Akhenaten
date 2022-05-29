#include "state.h"

#include "city/victory.h"
#include "graphics/view/view.h"
#include "city/warning.h"
#include "core/random.h"
#include "grid/ring.h"
#include "grid/building.h"

static struct {
    bool paused;
    int current_overlay;
    int previous_overlay;
} data = {false, OVERLAY_NONE, OVERLAY_NONE};

void game_state_init(void) {
    city_victory_reset();
    map_ring_init();

    city_view_reset_orientation();
//    city_view_go_to_screen_tile_corner(screen_tile(76, 152), true);

    random_generate_pool();

    city_warning_clear_all();
}
bool game_state_is_paused(void) {
    return data.paused;
}
void game_state_unpause(void) {
    data.paused = 0;
}
void game_state_toggle_paused(void) {
    data.paused = data.paused ? 0 : 1;
}
int game_state_overlay(void) {
    return data.current_overlay;
}
void game_state_reset_overlay(void) {
    data.current_overlay = OVERLAY_NONE;
    data.previous_overlay = OVERLAY_NONE;
}
void game_state_toggle_overlay(void) {
    int tmp = data.previous_overlay;
    data.previous_overlay = data.current_overlay;
    data.current_overlay = tmp;
    map_clear_highlights();
}
void game_state_set_overlay(int overlay) {
    if (overlay == OVERLAY_NONE)
        data.previous_overlay = data.current_overlay;
    else {
        data.previous_overlay = OVERLAY_NONE;
    }
    data.current_overlay = overlay;
    map_clear_highlights();
}
