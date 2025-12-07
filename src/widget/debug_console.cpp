#include "debug_console.h"

#include "core/custom_span.hpp"
#include "graphics/screen.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "building/destruction.h"
#include "game/game.h"
#include "dev/imgui_qconsole.h"
#include "building/building.h"

#include <SDL.h>
#include <SDL_keyboard.h>
#include "platform/keyboard_input.h"
#include "platform/renderer.h"

#include "imgui.h"
#include "graphics/elements/imui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "backends/imgui_impl_sdl2.h"
#include "dev/debug.h"

#include <iostream>

#if !defined(GAME_PLATFORM_ANDROID)

dev::imgui_qconsole *_debug_console = nullptr;

dev::imgui_qconsole &debug_console() {
    if (!_debug_console) {
        _debug_console = new dev::imgui_qconsole();
    }
    return *_debug_console;
}

static int game_debug_cli_guid = 0;
void game_debug_cli_draw() {
    SDL_Point platform_window_size;
    SDL_GetWindowSize(g_render.window(), &platform_window_size.x, &platform_window_size.y);

    debug_console().render("##console", game.debug_console, platform_window_size.x, platform_window_size.y * 0.33f);
    game_debug_cli_guid = 0;
}

static float property_opt_float = 0.0f;
static bool property_opt_enabled = false;
void game_debug_set_property_opt(float opt) {
    property_opt_float = opt;
    property_opt_enabled = true;
}

void game_debug_show_property_value(pcstr field, const float &v, bool disabled) {
    ImGui::InputFloat("##value", (float*)&v, property_opt_enabled ? property_opt_float : 1.0f);
    property_opt_enabled = false;
}

void game_debug_show_property_value(pcstr field, const double &v, bool disabled) {
    ImGui::InputDouble("##value", (double *)&v, 1.0f);
}

void game_debug_show_property_value(pcstr field, const int &v, bool disabled) {
    ImGuiInputTextFlags_ flags = disabled ? ImGuiInputTextFlags_ReadOnly : ImGuiInputTextFlags_None;
    ImGui::InputInt("##value", (int*)&v, 1, 100, flags);
}

void game_debug_show_property_value(pcstr field, const e_move_type &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_S8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const int8_t &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_S8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const short &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_S16, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const uint8_t &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_U8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const uint16_t &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_U16, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const bool &v, bool disabled) {
    ImGui::Checkbox("", (bool*)&v);
}

void game_debug_show_property_value(pcstr field, const pcstr v, bool disabled) {
    ImGui::Text("%s", !!v ? v : "none");
}

void game_debug_show_property_value(pcstr field, const bstring32 &v, bool disabled) {
    ImGui::Text("%s", !!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const bstring64 &v, bool disabled) {
    ImGui::Text("%s", !!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const bstring256 &v, bool disabled) {
    ImGui::Text("%s", !!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const xstring &v, bool disabled) {
    ImGui::Text("%s", !!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const vec2i &v, bool disabled) {
    ImGui::InputInt2(field, (int*)&v);
}

void game_debug_show_property_value(pcstr field, const tile2i &v, bool disabled) {
    ImGui::InputInt2(field, (int*)&v);
}

void game_debug_show_property_value(pcstr field, const setting_variant &v, bool disabled) {
    ImGuiInputTextFlags_ flags = disabled ? ImGuiInputTextFlags_ReadOnly : ImGuiInputTextFlags_None;
    
    switch (v.index()) {
    case setting_bool: {
            bool val = std::get<bool>(v);
            if (ImGui::Checkbox("##value", &val)) {
                if (!disabled) {
                    const_cast<setting_variant&>(v) = val;
                }
            }
            break;
        }
    case setting_float: {
            float val = std::get<float>(v);
            if (ImGui::InputFloat("##value", &val, 1.0f, 0.0f, "%.3f", flags)) {
                if (!disabled) {
                    const_cast<setting_variant&>(v) = val;
                }
            }
            break;
        }
    case setting_vec2i: {
            vec2i val = std::get<vec2i>(v);
            if (ImGui::InputInt2("##value", (int*)&val, flags)) {
                if (!disabled) {
                    const_cast<setting_variant&>(v) = val;
                }
            }
            break;
        }
    case setting_string: {
            const xstring& str = std::get<xstring>(v);
            if (disabled) {
                ImGui::Text("%s", str.c_str());
            } else {
                char buffer[256];
                strncpy(buffer, str.c_str(), sizeof(buffer) - 1);
                buffer[sizeof(buffer) - 1] = '\0';
                if (ImGui::InputText("##value", buffer, sizeof(buffer), flags)) {
                    const_cast<setting_variant&>(v) = xstring(buffer);
                }
            }
            break;
        }
    default:
        ImGui::Text("unknown type");
        break;
    }
}

void game_debug_show_property_value(pcstr field, const std::function<void()> &f, bool disabled) {
    if (ImGui::Button(field)) {
        f();
    }
}

void game_debug_show_property_value(pcstr field, const game_date_t& d, bool disabled) {
    int v[2] = { d.year, d.month };
    if (ImGui::InputInt2(field, v)) {
        ((game_date_t&)d).year = v[0];
        ((game_date_t&)d).month = v[1];
    }
}

template<typename T>
void game_debug_show_property_t(pcstr field, const T &v, bool disabled = false) {
    ImGui::PushID(game_debug_cli_guid);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx("Field", flags, "%s", field);
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(-FLT_MIN);

    if (disabled) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    }

    game_debug_show_property_value(field, v, disabled);
    
    if (disabled) {
        ImGui::PopItemFlag();
    }
    ImGui::NextColumn();
    ImGui::PopID();
    ++game_debug_cli_guid;
}

template<typename T>
void game_debug_show_property_t(pcstr field, const T &v, custom_span<pcstr> modes, bool disabled = false) {
    ImGui::PushID(game_debug_cli_guid);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx("Field", flags, "%s", field);
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(-FLT_MIN);

    if (disabled) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    }

    int item_current = v;
    ImGui::Combo("combo", &item_current, modes.data(), modes.size());
    const_cast<T&>(v) = item_current;

    if (disabled) {
        ImGui::PopItemFlag();
    }
    ImGui::NextColumn();
    ImGui::PopID();
    ++game_debug_cli_guid;
}

void game_debug_show_property_t(pcstr field, pcstr v) {
    bstring256 _v(v);
    game_debug_show_property_t(field, _v);
}

void game_debug_show_property(pcstr field, const int &v, bool disabled)  { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const uint8_t &v, custom_span<pcstr> modes, bool disabled)  { game_debug_show_property_t(field, v, modes, disabled); }
void game_debug_show_property(pcstr field, const float &v, bool disabled)  { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const double &v, bool disabled)  { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const e_move_type &v, bool disabled)  { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const int8_t &v, bool disabled)  { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const short &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const uint8_t &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const uint16_t &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const bool &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, pcstr v) { game_debug_show_property_t(field, v, true); }
void game_debug_show_property(pcstr field, const bstring32 &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const bstring64 &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const bstring256 &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const xstring &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const vec2i &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const tile2i &v, bool disabled) { game_debug_show_property_t(field, v, disabled); }
void game_debug_show_property(pcstr field, const std::function<void()> &f, bool disabled)  { game_debug_show_property_t(field, f, disabled); }
void game_debug_show_property(pcstr field, const game_date_t &d, bool disabled)  { game_debug_show_property_t(field, d, disabled); }
void game_debug_show_property(pcstr field, const setting_variant &d, bool disabled)  { game_debug_show_property_t(field, d, disabled); }

void game_debug_properties_draw() {
    if (!game.debug_properties) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
    if (!ui::Begin("Properties", &game.debug_properties)) {
        ImGui::End();
        return;
    }

    for (debug::PropertiesIterator *s = debug::PropertiesIterator::tail; s; s = s->next) {
        s->func(/*header*/true);
        if (s->next) {
            ImGui::SameLine();
        }
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    for (debug::PropertiesIterator *s = debug::PropertiesIterator::tail; s; s = s->next) {
        ImGui::NewLine();
        s->func(/*body*/false);
    }
    ImGui::PopStyleVar();

    ImGui::End();

    //g_debug_figure_id = 0;
}

void game_debug_cli_message(pcstr msg) {
    debug_console() << msg << std::endl;
}

void game_imgui_overlay_init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL2_InitForSDLRenderer(g_render.window(), g_render.renderer());
    ImGui_ImplSDLRenderer2_Init(g_render.renderer());

    debug_console().con.bind_command("close", [] (auto &, auto &) { game.debug_console = false; });
}

void game_imgui_overlay_destroy() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void game_imgui_overlay_begin_frame() {
    if (!game.debug_console) {
        //return;
    }

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void game_imgui_overlay_draw() {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), g_render.renderer());
}

bool game_imgui_overlay_handle_event(void *e) {
    const SDL_Event *event = (const SDL_Event *)e;

    if (event->type == SDL_KEYDOWN) {
        int key = event->key.keysym.scancode;

        if (key == SDL_SCANCODE_GRAVE) {
            game_toggle_debug_console();
        }
    }

    if (event->type == SDL_TEXTINPUT && *event->text.text == '`') {
        debug_console().skip_event = true;
    }

    if (!(game.debug_console || game.debug_properties)) {
        return false;
    }

    if (debug_console().skip_event) {
        debug_console().skip_event = false;
        return false;
    }

    ImGui_ImplSDL2_ProcessEvent(event);

    if (game.debug_console) {
        return true;
    }

    ImGuiIO &io = ImGui::GetIO();
    bool wants_capture = false;

    switch (event->type) {
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEMOTION:
    case SDL_MOUSEWHEEL:
        wants_capture = io.WantCaptureMouse;
        break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_TEXTINPUT:
    case SDL_TEXTEDITING:
        wants_capture = io.WantCaptureKeyboard;
        break;
    default:
        wants_capture = false;
        break;
    }

    return wants_capture;
}

void game_toggle_debug_console() {
    game.debug_console = !game.debug_console;
    if (game.debug_console) {
        debug_console().is.reclaim_focus = true;
    }
}

void bind_debug_command(pcstr cmd, std::function<void(std::istream &, std::ostream &)> f) {
    debug_console().con.bind_command(cmd, f);
}

void bind_debug_console_var_int(pcstr var, int &ref) {
    debug_console().con.bind_cvar(var, ref);
}

void bind_debug_console_var_int8(pcstr var, int8_t &ref) {
    debug_console().con.bind_cvar(var, ref);
}

void bind_debug_console_var_int16(pcstr var, int16_t &ref) {
    debug_console().con.bind_cvar(var, ref);
}

void bind_debug_console_var_uint8(pcstr var, uint8_t &ref) {
    debug_console().con.bind_cvar(var, ref);
}

void bind_debug_console_var_float(pcstr var, float &ref) {
    debug_console().con.bind_cvar(var, ref);
}

void bind_debug_console_var_bool(pcstr var, bool &ref) {
    debug_console().con.bind_cvar(var, ref);
}

#endif //GAME_PLATFORM_ANDROID