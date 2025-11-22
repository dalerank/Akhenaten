#include "city/sound.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "city/city.h"
#include "game/game.h"
#include "sound/sound.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_sound_properties);
void config_show_sound_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Sound", ImGuiTreeNodeFlags_None, "Sound");
    if (common_open) {
        ImGui::BeginTable("Sound", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        const auto &channels = g_sound.channels();
        int cl = 180;
        for (const auto &ch : channels) {
            if (!ch.playing) {
                continue;
            }

            int i = &ch - channels.data();
            game_debug_show_property(bstring32("Channel", i).c_str(), bstring256().printf("L:%03u: R:%03u: %s", ch.left_pan, ch.right_pan, ch.filename.c_str()).c_str());
        }

        ImGui::EndTable();

        ImGui::TreePop();
    }
}