#pragma once

#include "imgui.h"

namespace ui {

/**
 * Begin ImGui window with game-style background panel
 * This function draws a background panel using the game's UI style before
 * calling ImGui::Begin. The panel size matches the window size.
 * 
 * @param name Window name/ID
 * @param p_open Optional pointer to bool for close button
 * @param flags ImGui window flags
 * @return true if window is open and should be rendered
 */
bool Begin(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0);

/**
 * End ImGui window (wrapper for ImGui::End)
 */
inline void End() {
    ImGui::End();
}

} // namespace ui

