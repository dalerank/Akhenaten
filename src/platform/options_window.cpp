#include "options_window.h"

#include "platform/arguments.h"
#include "platform/renderer.h"
#include "platform/version.hpp"
#include "core/bstring.h"
#include "core/log.h"

#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "dev/imguifiledialog.h"
#include "misc/cpp/imgui_stdlib.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace {

constexpr int BASE_CONFIG_WINDOW_W = 1280;
constexpr int BASE_CONFIG_WINDOW_H = 720;

float get_ui_scale_for_display(int display_index) {
    float scale = ImGui_ImplSDL2_GetContentScaleForDisplay(display_index);
    if (scale <= 0.0f || !std::isfinite(scale)) {
        scale = 1.0f;
    }

    SDL_DisplayMode desktop{};
    if (SDL_GetDesktopDisplayMode(display_index, &desktop) == 0) {
        if (desktop.h >= 2160) {
            scale = std::max(scale, 2.0f);
        } else if (desktop.h >= 1440) {
            scale = std::max(scale, 1.5f);
        }
    }

    return std::clamp(scale, 1.0f, 3.0f);
}

void apply_imgui_ui_scale(float ui_scale) {
    ImGui::GetStyle().ScaleAllSizes(ui_scale);
    ImGui::GetIO().FontGlobalScale = ui_scale;
}

} // namespace

void show_options_window(Arguments& args) {
#if defined(_WIN32)
    auto const window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
#else
    // SDL_WINDOW_ALLOW_HIGHDPI breaks mouse coordinates on macOS and Linux/Wayland compositors.
    auto const window_flags = SDL_WINDOW_RESIZABLE;
#endif

    const int display_index = 0;
    const float ui_scale = get_ui_scale_for_display(display_index);

    SDL_DisplayMode desktop{};
    int window_w = static_cast<int>(BASE_CONFIG_WINDOW_W * ui_scale);
    int window_h = static_cast<int>(BASE_CONFIG_WINDOW_H * ui_scale);
    if (SDL_GetDesktopDisplayMode(display_index, &desktop) == 0) {
        window_w = std::min(window_w, static_cast<int>(desktop.w * 0.9f));
        window_h = std::min(window_h, static_cast<int>(desktop.h * 0.9f));
    }

    if (args.get_display_scale_percentage() == 100 && ui_scale > 1.0f) {
        args.set_display_scale_percentage(static_cast<int>(ui_scale * 100.0f));
    }

    SDL_Window* platform_window = SDL_CreateWindow("Akhenaten: configuration", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, window_w, window_h, window_flags);

    SDL_Renderer* renderer = SDL_CreateRenderer(platform_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        logs::info("Error creating SDL_Renderer!");
        exit(-1);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(platform_window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
    apply_imgui_ui_scale(ui_scale);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool store_configuration = false;

    auto video_drivers = get_video_drivers(false);
    for (bool done = false; !done;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                exit(1);
            }

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
                && event.window.windowID == SDL_GetWindowID(platform_window)) {
                exit(1);
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Use ImGui display size (matches mouse coordinates after NewFrame).
        {
            bstring512 data_directory = args.get_data_directory().c_str();
            ImVec2 window_size = ImGui::GetIO().DisplaySize;

            ImVec2 window_pos(0, 0);
            ImGui::SetNextWindowPos(window_pos);
            ImGui::SetNextWindowSize(window_size);

            ImGui::Begin("Configuration", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
            ImGui::Text("Folder with original game data:");
            ImGui::InputText("default", data_directory.data(), data_directory.capacity);
            ImGui::SameLine();
            if (ImGui::Button("...")) {
                IGFD::FileDialogConfig config;
                config.path = ".";
                config.countSelectionMax = 1;
                config.flags = ImGuiFileDialogFlags_Modal;
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFolderDlgKey", "Choose Folder", nullptr, config);
            }

            ImVec2 filedialog_size(window_size.x * 0.5f, window_size.y * 0.5f);
            if (ImGuiFileDialog::Instance()->Display("ChooseFolderDlgKey", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize, filedialog_size)) {
                ImGui::SetWindowFocus();
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    args.set_data_directory(ImGuiFileDialog::Instance()->GetCurrentPath().c_str());
                }
                ImGuiFileDialog::Instance()->Close();
            }

            ImGui::BeginChild("RenderSection");
            ImVec2 size_window = ImGui::GetWindowSize();
            { ImGui::BeginChild("ResolitionSection", ImVec2(size_window.x / 2, size_window.y / 2));
            ImGui::Text("Resolution:");
            static int item_mode_current_idx = 0;
            auto video_modes = get_video_modes();
            if (ImGui::BeginListBox("##resolution")) {
                int index = 0;
                for (auto it = video_modes.begin(); it != video_modes.end(); ++it, ++index) {
                    const bool is_selected = (item_mode_current_idx == index);
                    if (ImGui::Selectable(it->str.c_str(), is_selected)) {
                        item_mode_current_idx = index;
                        args.set_window_size({it->x, it->y});
                    }

                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }

            bool is_window_mode = args.is_window_mode();
            if (ImGui::Checkbox("Window mode", &is_window_mode)) {
                args.set_window_mode(is_window_mode);
            }

            int display_scale = args.get_display_scale_percentage();
            if (ImGui::SliderInt("Display scale %", &display_scale, 50, 300)) {
                args.set_display_scale_percentage(display_scale);
            }
            ImGui::SameLine();
            ImGui::TextDisabled("(?)");
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("UI scale in game. Use 150-200%% on 4K monitors.");
            }

            if (ImGui::Checkbox("Store configuration (to skip this dialog for the next time)", &store_configuration)) {
                if (store_configuration) {
                    arguments::store(args);
                }
            }

            ImGui::EndChild();} // ResolitionSection
            ImGui::SameLine();
            {ImGui::BeginChild("DriverSection");
            ImGui::Text("Driver:");
            static int item_driver_current_idx = 0;
            if (ImGui::BeginListBox("##drivers")) {
                int index = 0;
                for (auto it = video_drivers.begin(); it != video_drivers.end(); ++it, ++index) {
                    const bool is_selected = (item_driver_current_idx == index);
                    if (ImGui::Selectable(it->c_str(), is_selected)) {
                        item_driver_current_idx = index;
                        args.set_renderer(it->c_str());
                    }

                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }
            ImGui::EndChild();} // DriverSection

            ImGui::EndChild(); // RenderSection

            ImVec2 left_bottom_corner{5, window_size.y - 30.0f * ui_scale};
            ImGui::SetCursorPos(left_bottom_corner);
            {ImGui::BeginChild("StartSection");
                if (ImGui::Button("RUN GAME")) {
                    if (store_configuration) {
                        arguments::store(args);
                    }
                    done = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Quit")) {
                    exit(EXIT_SUCCESS);
                }
                ImGui::SameLine();
                ImGui::Text("%s", get_version().c_str());
            ImGui::EndChild();}
            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
            // ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer,
                               (Uint8)(clear_color.x * 255),
                               (Uint8)(clear_color.y * 255),
                               (Uint8)(clear_color.z * 255),
                               (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(platform_window);
}

