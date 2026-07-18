#include "options_window.h"

#include "platform/arguments.h"
#include "platform/platform.h"
#include "platform/renderer.h"
#include "platform/version.hpp"
#include "core/archive.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/settings_vars.h"
#include "game/game_config.h"
#include "js/js_defines.h"
#include "content/vfs.h"

#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "dev/imguifiledialog.h"
#include "misc/cpp/imgui_stdlib.h"
#include "mujs/mujs.h"
#include "mujs/jsi.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <variant>

namespace {

constexpr int BASE_CONFIG_WINDOW_W = 1280;
constexpr int BASE_CONFIG_WINDOW_H = 720;
constexpr pcstr CONF_FILENAME = "akhenaten.conf";

void js_conf_panic(js_State *J) {
    logs::error("MuJS panic in settings conf: %s", js_strnode_cstr(js_tostring(J, -1)));
}

void js_conf_log_info(js_State *J) {
    if (!js_isundefined(J, 1)) {
        logs::info("%s", js_strnode_cstr(js_tostring(J, 1)));
    }
    J->pushundefined();
}

js_State *create_conf_vm() {
    js_State *J = js_newstate(nullptr, nullptr, JS_STRICT);
    js_atpanic(J, js_conf_panic);
    REGISTER_GLOBAL_FUNCTION(J, js_conf_log_info, "log_info", 1);
    return J;
}

struct conf_vm_scope {
    js_State *J = nullptr;
    void *prev_arch = nullptr;

    explicit conf_vm_scope(js_State *state) : J(state), prev_arch(g_config_arch.state) {
        g_config_arch = {J};
    }

    ~conf_vm_scope() {
        g_config_arch = {prev_arch};
        if (J) {
            js_freestate(J);
            J = nullptr;
        }
    }

    conf_vm_scope(const conf_vm_scope &) = delete;
    conf_vm_scope &operator=(const conf_vm_scope &) = delete;
};

void push_setting_to_js(const xstring &key, const setting_variant &value) {
    switch (value.index()) {
    case setting_bool:
        g_config_arch.w_property("game_settings", key.c_str(), std::get<bool>(value));
        break;
    case setting_float:
        g_config_arch.w_property("game_settings", key.c_str(), std::get<float>(value));
        break;
    case setting_vec2i:
        g_config_arch.w_property("game_settings", key.c_str(), std::get<vec2i>(value));
        break;
    case setting_string:
        g_config_arch.w_property("game_settings", key.c_str(), std::get<xstring>(value));
        break;
    default:
        break;
    }
}

bool load_settings_file(pcstr path) {
    if (!path || !*path) {
        return false;
    }

    FILE *fp = vfs::file_open_os(path, "rb");
    if (!fp) {
        return false;
    }
    vfs::file_close(fp);

    js_State *J = create_conf_vm();
    conf_vm_scope scope(J);

    if (js_dofile(J, path) != 0) {
        logs::warn("Failed to evaluate settings file %s", path);
        return false;
    }

    game_features::settings().load_global("game_settings");
    logs::info("Loaded settings from %s", path);
    return true;
}

bool save_settings_file(pcstr path) {
    if (!path || !*path) {
        return false;
    }

    js_State *J = create_conf_vm();
    conf_vm_scope scope(J);

    if (js_dostring(J, "var game_settings = {}") != 0) {
        logs::error("Unable to create game_settings object for %s", path);
        return false;
    }

    auto &settings = game_features::settings();
    settings.foreach_vars([] (xstring key, const setting_variant &value) {
        push_setting_to_js(key, value);
    });
    settings.mark_dirty();
    settings.sync_global(path, "game_settings");
    logs::info("Saved settings to %s", path);
    return true;
}

void try_load_game_features(pcstr data_directory) {
    bstring512 path;
    if (data_directory && *data_directory) {
        path.printf("%s/%s", data_directory, CONF_FILENAME);
        if (load_settings_file(path.c_str())) {
            return;
        }
    }

    path.printf("%s/%s", platform.user_directory(), CONF_FILENAME);
    if (load_settings_file(path.c_str())) {
        return;
    }

    load_settings_file(CONF_FILENAME);
}

void try_save_game_features(pcstr data_directory) {
    bstring512 path;
    if (data_directory && *data_directory) {
        path.printf("%s/%s", data_directory, CONF_FILENAME);
        if (save_settings_file(path.c_str())) {
            return;
        }
    }

    path.printf("%s/%s", platform.user_directory(), CONF_FILENAME);
    if (save_settings_file(path.c_str())) {
        return;
    }

    save_settings_file(CONF_FILENAME);
}

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

bool feature_matches_filter(const game_features::game_feature *feature, const std::string &filter) {
    if (filter.empty()) {
        return true;
    }

    auto contains_ci = [] (pcstr haystack, const std::string &needle) {
        if (!haystack || !*haystack) {
            return false;
        }
        std::string lower_hay = haystack;
        std::string lower_needle = needle;
        std::transform(lower_hay.begin(), lower_hay.end(), lower_hay.begin(),
          [] (unsigned char c) { return static_cast<char>(std::tolower(c)); });
        std::transform(lower_needle.begin(), lower_needle.end(), lower_needle.begin(),
          [] (unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return lower_hay.find(lower_needle) != std::string::npos;
    };

    if (contains_ci(feature->name.c_str(), filter)) {
        return true;
    }
    return contains_ci(feature->text.c_str(), filter);
}

void draw_game_features_section(std::string &filter, bool &features_changed) {
    ImGui::Text("Game features:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 80.0f);
    ImGui::InputTextWithHint("##features_filter", "Filter...", &filter);
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        filter.clear();
    }

    ImGui::BeginChild("FeaturesList", ImVec2(0, 0), ImGuiChildFlags_Borders);
    for (auto *feature : game_features::all()) {
        if (feature->type() != setting_bool) {
            continue;
        }
        // Skip internal options without localization text (gameopt_* runtime state).
        if (feature->text.empty()) {
            continue;
        }
        if (!feature_matches_filter(feature, filter)) {
            continue;
        }

        bool value = feature->to_bool();
        if (ImGui::Checkbox(feature->name.c_str(), &value)) {
            feature->set(value);
            features_changed = true;
        }
        if (ImGui::IsItemHovered() && !feature->text.empty()) {
            ImGui::SetTooltip("%s", feature->text.c_str());
        }
    }
    ImGui::EndChild();
}

void push_changed_feature_overrides(Arguments &args,
  const std::unordered_map<std::string, bool> &snapshot) {
    for (auto *feature : game_features::all()) {
        if (feature->type() != setting_bool) {
            continue;
        }
        if (feature->text.empty()) {
            continue;
        }

        const bool current = feature->to_bool();
        const auto it = snapshot.find(feature->name.c_str());
        if (it != snapshot.end() && it->second == current) {
            continue;
        }

        args.add_game_config_cli_override(feature->name, current ? "true" : "false");
    }
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
    bool features_changed = false;
    std::string features_filter;

    try_load_game_features(args.get_data_directory().c_str());

    std::unordered_map<std::string, bool> features_snapshot;
    for (auto *feature : game_features::all()) {
        if (feature->type() == setting_bool && !feature->text.empty()) {
            features_snapshot.emplace(feature->name.c_str(), feature->to_bool());
        }
    }

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
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                args.set_data_directory(data_directory.c_str());
            }
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
                    data_directory = args.get_data_directory().c_str();
                }
                ImGuiFileDialog::Instance()->Close();
            }

            const float bottom_bar_h = 36.0f * ui_scale;
            const float render_section_h = window_size.y * 0.28f;

            ImGui::BeginChild("RenderSection", ImVec2(0, render_section_h), ImGuiChildFlags_Borders);
            ImVec2 size_window = ImGui::GetWindowSize();
            { ImGui::BeginChild("ResolitionSection", ImVec2(size_window.x / 2, 0));
            ImGui::Text("Resolution:");
            static int item_mode_current_idx = 0;
            auto video_modes = get_video_modes();
            if (ImGui::BeginListBox("##resolution", ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() * 5.5f))) {
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
            if (ImGui::BeginListBox("##drivers", ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() * 6.5f))) {
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

            ImGui::BeginChild("FeaturesSection", ImVec2(0, -bottom_bar_h), ImGuiChildFlags_Borders);
            draw_game_features_section(features_filter, features_changed);
            ImGui::EndChild();

            {ImGui::BeginChild("StartSection", ImVec2(0, 0));
                if (ImGui::Button("RUN GAME")) {
                    args.set_data_directory(data_directory.c_str());
                    if (store_configuration) {
                        arguments::store(args);
                    }
                    if (features_changed || store_configuration) {
                        try_save_game_features(args.get_data_directory().c_str());
                    }
                    push_changed_feature_overrides(args, features_snapshot);
                    done = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Quit")) {
                    exit(EXIT_SUCCESS);
                }
                ImGui::SameLine();
                ImGui::Text("%s", get_version().c_str());
            ImGui::EndChild();}
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
