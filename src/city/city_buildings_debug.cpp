#include "city/city_buildings.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "building/building.h"
#include "building/building_type.h"
#include "core/bstring.h"

#include <array>

ANK_REGISTER_PROPS_ITERATOR(config_show_city_buildings_properties);
void config_show_city_buildings_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("City Buildings", ImGuiTreeNodeFlags_None, "City Buildings");
    if (!common_open) {
        return;
    }

    auto &buildings = city_buildings();

    int total_slots = static_cast<int>(buildings.size());
    int valid_count = 0;
    std::array<int, BUILDING_MAX> type_counts{};

    for (auto &b : buildings) {
        if (!b.is_valid()) {
            continue;
        }

        valid_count++;
        if (b.type > BUILDING_NONE && b.type < BUILDING_MAX) {
            type_counts[b.type]++;
        }
    }

    ImGui::BeginTable("CityBuildings", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

    game_debug_show_property("total_slots", total_slots);
    game_debug_show_property("valid_buildings", valid_count);
    game_debug_show_property("invalid_slots", total_slots - valid_count);

    ImGui::EndTable();

    bool counts_open = ImGui::TreeNodeEx("Building Counts", ImGuiTreeNodeFlags_None, "Building Counts");
    if (counts_open) {
        ImGui::BeginTable("CityBuildingCounts", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        for (int type = BUILDING_NONE; type < BUILDING_MAX; ++type) {
            int count = type_counts[type];
            if (count <= 0) {
                continue;
            }

            const char *type_name = token::find_name(e_building_type_tokens, type);

            bstring256 label;
            label.printf("%s [%d]", (type_name && *type_name) ? type_name : "Unknown", type);
            game_debug_show_property(label.c_str(), count);
        }

        ImGui::EndTable();
        ImGui::TreePop();
    }

    ImGui::TreePop();
}

