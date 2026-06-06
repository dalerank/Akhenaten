#include "window/console.h"
#include "game/game.h"
#include "input/mouse.h"
#include "input/hotkey.h"
#include "input/keyboard.h"
#include "input/keys.h"
#include "core/app.h"

#include <SDL.h>

struct keyboard_module_t {
    e_key_mode get_modifier(int mod);

    void handle_key_down(SDL_Event* ev);
    void handle_key_up(SDL_Event* ev);
    void handle_text(SDL_Event* ev);
};

static int is_alt_down(SDL_KeyboardEvent* event) {
    return (event->keysym.mod & KMOD_ALT) != 0;
}

e_key_mode keyboard_module_t::get_modifier(int mod) {
    int key_mod = KEY_MOD_NONE;
    if (mod & KMOD_SHIFT)
        key_mod |= KEY_MOD_SHIFT;

    if (mod & KMOD_CTRL)
        key_mod |= KEY_MOD_CTRL;

    if (mod & KMOD_ALT)
        key_mod |= KEY_MOD_ALT;

    if (mod & KMOD_GUI)
        key_mod |= KEY_MOD_GUI;

    return (e_key_mode)key_mod;
}

void keyboard_module_t::handle_key_down(SDL_Event* ev) {
    if (SDL_KEYDOWN != ev->type) {
        return;
    }

    SDL_KeyboardEvent* event = &ev->key;
    // handle keyboard input keys
    switch (event->keysym.sym) {
    case SDLK_RETURN:
    case SDLK_KP_ENTER:
        // only send enter if no modifier is also down
        if ((event->keysym.mod & (KMOD_CTRL | KMOD_ALT | KMOD_GUI)) == 0)
            g_keyboard.press_return();

        break;
    case SDLK_BACKSPACE:
        g_keyboard.press_backspace();
        break;
    case SDLK_DELETE:
        g_keyboard.press_delete();
        break;
    case SDLK_INSERT:
        g_keyboard.press_insert();
        break;
    case SDLK_LEFT:
        g_keyboard.press_left();
        break;
    case SDLK_RIGHT:
        g_keyboard.press_right();
        break;
    case SDLK_UP:
        g_keyboard.press_left();
        break;
    case SDLK_DOWN:
        g_keyboard.press_right();
        break;
    case SDLK_HOME:
        g_keyboard.press_home();
        break;
    case SDLK_END:
        g_keyboard.press_end();
        break;
    case SDLK_AC_BACK:
#if !defined(GAME_PLATFORM_ANDROID)
        event->keysym.scancode = SDL_SCANCODE_ESCAPE;
        break;
#else
    // Hack: since Android handles the right mouse button as a back button
    // (or even as an "ESC" keypress) and SDL doesn't yet have a proper implementation 
    // for this, we'll treat the back button as a right mouse button when the mouse is active
    case SDLK_ESCAPE:
        if (!mouse::get().is_touch) {
            mouse::ref().set_right_down(1);
            return;
        } else {
            event->keysym.scancode = SDL_SCANCODE_ESCAPE;
        }
        break;
#endif
    }

    // handle hotkeys
    if (game.debug_console) {
        return;
    }
    e_key key = (e_key)keyboard_t::get_key_from_scancode(event->keysym.scancode);
    e_key_mode mod = get_modifier(event->keysym.mod);

    // when a text field is capturing input, suppress global hotkeys so typing
    // characters like digits or '-' doesn't trigger advisor/menu shortcuts.
    // Escape is allowed through so dialogs can still be cancelled.
    if (g_keyboard.is_capturing() && key != KEY_ESCAPE) {
        return;
    }

    hotkey_key_pressed(key, mod, event->repeat);
}

void keyboard_module_t::handle_key_up(SDL_Event* ev) {
    if (SDL_KEYUP != ev->type) {
        return;
    }

    SDL_KeyboardEvent* event = &ev->key;
#if defined(GAME_PLATFORM_ANDROID)
    // Right mouse button hack: read above for explanation
    if ((event->keysym.sym == SDLK_ESCAPE || event->keysym.sym == SDLK_AC_BACK) && !mouse::get().is_touch) {
        mouse::ref().set_right_down(0);
        return;
    }
#endif

    if (game.debug_console) {
        return;
    }

    e_key key = (e_key)keyboard_t::get_key_from_scancode(event->keysym.scancode);
    int mod = get_modifier(event->keysym.mod);
    hotkey_key_released(key, mod);
}

void keyboard_module_t::handle_text(SDL_Event* event) {
    if (SDL_TEXTINPUT != event->type) {
        return;
    }

    SDL_TextInputEvent* text_event = &event->text;
    g_keyboard.set_text(text_event->text);
}

void ANK_REGISTER_APPLICATION_MODULE(register_keyboard_module) {
    static keyboard_module_t kb;
    g_app.register_keyboard_event_handler([&](void* ev) { kb.handle_key_down((SDL_Event*)ev); });
    g_app.register_keyboard_event_handler([&](void* ev) { kb.handle_key_up((SDL_Event*)ev); });
    g_app.register_keyboard_event_handler([&](void* ev) { kb.handle_text((SDL_Event*)ev); });
}


