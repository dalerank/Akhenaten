#include "input.h"

#include "input/hotkey.h"
#include "input/mouse.h"
#include "js/js_game.h"

int input_go_back_requested(const mouse* m, const hotkeys* h) {
    return m->right.went_up || h->escape_pressed;
}

int __input_go_back_requested() {
    return input_go_back_requested(&mouse::get(), hotkey_state());
}
ANK_FUNCTION(__input_go_back_requested)
