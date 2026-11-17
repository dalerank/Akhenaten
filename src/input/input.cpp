#include "input.h"

#include "input/hotkey.h"
#include "input/mouse.h"
#include "js/js_game.h"

bool input_go_back_requested(const mouse* m, const hotkeys* h) {
    return m->right.went_up || h->escape_pressed;
}

bool __input_go_back_requested() {
    return input_go_back_requested(&mouse::get(), &g_hotkeys);
}
ANK_FUNCTION(__input_go_back_requested)
