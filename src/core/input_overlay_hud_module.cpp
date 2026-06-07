#include "core/app.h"

#include "core/svector.h"
#include "game/game_config.h"
#include "graphics/color.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "input/keyboard.h"
#include "input/keys.h"
#include "input/mouse.h"

#include <SDL.h>

struct input_overlay_hud_module_t {
    void draw(hud_end_context_t* ctx);
};

static void collect_input_labels(svector<pcstr, 32>& labels) {
    const mouse& m = mouse::get();

    if (m.left.is_down) {
        labels.push_back("LMB");
    }
    if (m.middle.is_down) {
        labels.push_back("MMB");
    }
    if (m.right.is_down) {
        labels.push_back("RMB");
    }

    const SDL_Keymod mod = SDL_GetModState();
    if (mod & KMOD_SHIFT) {
        labels.push_back(keyboard_t::key_modifier_name(KEY_MOD_SHIFT));
    }
    if (mod & KMOD_CTRL) {
        labels.push_back(keyboard_t::key_modifier_name(KEY_MOD_CTRL));
    }
    if (mod & KMOD_ALT) {
        labels.push_back(keyboard_t::key_modifier_name(KEY_MOD_ALT));
    }
    if (mod & KMOD_GUI) {
        labels.push_back(keyboard_t::key_modifier_name(KEY_MOD_GUI));
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    for (int key = KEY_A; key < KEY_MAX_ITEMS; key++) {
        const uint32_t scancode = keyboard_t::get_scancode_from_key(key);
        if (scancode == SDL_SCANCODE_UNKNOWN || !state[scancode]) {
            continue;
        }
        labels.push_back(keyboard_t::key_name(key));
    }
}

void input_overlay_hud_module_t::draw(hud_end_context_t* ctx) {
    (void)ctx;

    if (!game_features::gameui_show_input_near_cursor.to_bool()) {
        return;
    }

    const mouse& m = mouse::get();
    if (!m.is_inside_window) {
        return;
    }

    svector<pcstr, 32> labels;
    collect_input_labels(labels);
    if (labels.empty()) {
        return;
    }

    constexpr int line_height = 12;
    constexpr int offset_x = 16;
    constexpr int offset_y = 20;

    int x = m.x + offset_x;
    int y = m.y + offset_y;
    const int total_height = (int)labels.size() * line_height;

    if (y + total_height > screen_height()) {
        y = screen_height() - total_height;
    }
    if (y < 0) {
        y = 0;
    }
    if (x + 80 > screen_width()) {
        x = screen_width() - 80;
    }
    if (x < 0) {
        x = 0;
    }

    for (pcstr label : labels) {
        text_draw(label, x, y, FONT_SMALL_OUTLINED, COLOR_WHITE);
        y += line_height;
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_input_overlay_hud_module) {
    static input_overlay_hud_module_t module;
    g_app.register_hud_end_handler([&](void* ctx) { module.draw((hud_end_context_t*)ctx); });
}
