#include "debug_console.h"

#include "graphics/screen.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "game/game.h"
#include "dev/imgui_qconsole.h"

#include <SDL.h>
#include <SDL_keyboard.h>
#include "platform/keyboard_input.h"
#include "platform/renderer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"
#include "imgui/backends/imgui_impl_sdl.h"

#include <iostream>

dev::imgui_qconsole *_debug_console = nullptr;

dev::imgui_qconsole &debug_console() {
    if (!_debug_console) {
        _debug_console = new dev::imgui_qconsole();
    }
    return *_debug_console;
}

void game_debug_cli_draw() {
    auto renderer = graphics_renderer();
    SDL_Point platform_window_size;
    SDL_GetWindowSize(renderer->window(), &platform_window_size.x, &platform_window_size.y);

    debug_console().render("##console", game.console, platform_window_size.x, platform_window_size.y * 0.33f);
}

void game_debug_cli_message(pcstr msg) {
    debug_console() << msg << std::endl;
}

void game_imgui_overlay_init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    auto renderer = graphics_renderer();
    ImGui_ImplSDL2_InitForSDLRenderer(renderer->window(), renderer->renderer());
    ImGui_ImplSDLRenderer_Init(renderer->renderer());

    debug_console().con.bind_command("close", [] (auto &, auto &) { game.console = false; });
}

void game_imgui_overlay_destroy() {
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void game_imgui_overlay_begin_frame() {
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void game_imgui_overlay_draw() {
    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

bool game_imgui_overlay_handle_event(void *e) {
    const SDL_Event *event = (const SDL_Event *)e;

    if (event->type == SDL_KEYDOWN) {
        int key = event->key.keysym.scancode;

        if (key == SDL_SCANCODE_GRAVE) {
            game_toggle_debug_console();
        }
    }

    if (!game.console) {
        return false;
    }

    ImGui_ImplSDL2_ProcessEvent(event);
    return false;
}

void bind_debug_command(pcstr cmd, std::function<void(std::istream &, std::ostream &)> f) {
    debug_console().con.bind_command(cmd, f);
}

void bind_debug_console_var_int(pcstr var, int &ref) {
    debug_console().con.bind_cvar(var, ref);
}

