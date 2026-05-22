#include "city/city_buildings.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "building/building.h"
#include "building/building_type.h"
// Allowed-buildings toggling now drives the JS-side `building_menu_ctrl`
// via the event bus instead of the deleted g_building_menu_ctrl surface
// (header city/city_building_menu_ctrl.h was removed in 3301e49aa when
// the building menu was migrated to JS). build_planner.h declares the
// event types we emit (event_use_building, event_building_menu_changed).
#include "building/construction/build_planner.h"
#include "core/bstring.h"
#include "game/game_events.h"
#include "scenario/scenario.h"

#include <array>
#include <cstring>

ANK_REGISTER_PROPS_ITERATOR(config_show_city_buildings_properties);

namespace {
// Filter out enum slots that aren't real, player/dev-toggleable buildings:
//   - hex-fallback labels from unnamed enum gaps: token_holder in
//     core/tokenum.h auto-generates "(enum e_building_type)0xNN" for every
//     value in [BUILDING_NONE, BUILDING_MAX) via __FUNCSIG__ reflection,
//     so ~42 gaps in e_building_type get the compiler's hex string instead
//     of a real BUILDING_* name. The BUILDING_ prefix check rejects them all.
//   - BUILDING_MENU_* category sentinels (not buildings, just menu group IDs)
//   - BUILDING_HOUSE_* — evolved automatically from BUILDING_HOUSE_VACANT_LOT;
//     never built directly through the sidebar
//   - placeholder slots: RESERVED, RESERVER (typo), UNUSED, *_NONE
//   - dead trials: BUILDING_BIG_TEMPLE_* (never implemented; zero references
//     in C++/JS/static-params; BUILDING_MENU_LARGE_TEMPLES.items[] is empty)
//   - dead terrain placeholders: BUILDING_ORDINARY_ROCK, BUILDING_OREBEARING_ROCK
//     (zero references; reserved for a future Pharaoh-style harvest-from-terrain
//     feature — revive when that lands)
//   - explicit name skips:
//       ROAD, CLEAR_LAND     — top-level menu actions, always available
//       ACADEMY              — unused (the real one is MILITARY_ACADEMY)
//       MILITARY_ACADEMY_2/3 — internal upgrade-tier variants, not buildable
//       CLIFF                — terrain feature, not a building
//       MONUMENT_NONE        — sentinel for "no monument"
//   - internal monument sub-tile markers: *_PYRAMID_CORNER/WALL/SIDE/ENTRANCE
//     and *_MASTABA_CORNER/WALL/SIDE/ENTRANCE. These are *not* dead —
//     monument_pyramid.cpp and monument_mastaba.cpp spawn them as sub-tiles of
//     a built monument to drive corner/wall/entrance image selection during
//     rendering — but they're not player-placeable, so toggling them in a
//     build-menu debug pane is meaningless. We match the suffix explicitly so
//     we don't clobber legitimate names like BUILDING_PYRAMID_COMPLEX.
bool is_debug_pickable_type(const char *name) {
    if (!name || std::strncmp(name, "BUILDING_", 9) != 0) {
        return false; // empty, null, or compiler hex-fallback label
    }
    if (std::strncmp(name, "BUILDING_MENU_", 14) == 0) {
        return false;
    }
    if (std::strncmp(name, "BUILDING_HOUSE_", 15) == 0) {
        return false;
    }
    if (std::strncmp(name, "BUILDING_BIG_TEMPLE_", 20) == 0) {
        return false;
    }
    if (std::strstr(name, "RESERVED") != nullptr) {
        return false;
    }
    if (std::strstr(name, "RESERVER") != nullptr) {
        // BUILDING_RESERVER_MISSION_POST_80 — typo'd reserved slot
        return false;
    }
    if (std::strstr(name, "UNUSED") != nullptr) {
        return false;
    }
    if (std::strstr(name, "_ROCK") != nullptr) {
        // BUILDING_ORDINARY_ROCK / BUILDING_OREBEARING_ROCK — unimplemented
        return false;
    }
    static const char *const explicit_skips[] = {
        "BUILDING_ROAD",                // 5  — top-level menu action
        "BUILDING_CLEAR_LAND",          // 9  — top-level menu action
        "BUILDING_ACADEMY",             // 135 — unused; MILITARY_ACADEMY is the real one
        "BUILDING_MILITARY_ACADEMY_2",  // 185 — internal upgrade tier
        "BUILDING_MILITARY_ACADEMY_3",  // 186 — internal upgrade tier
        "BUILDING_CLIFF",               // 223 — terrain feature, not a building
        "BUILDING_MONUMENT_NONE",       //     — sentinel for "no monument"
    };
    for (const char *skip : explicit_skips) {
        if (std::strcmp(name, skip) == 0) {
            return false;
        }
    }
    // Monument sub-tile markers — internal rendering tags, not buildable.
    // Use the full suffix so we don't match real names containing _PYRAMID_
    // or _MASTABA_ (e.g. MUDBRICK_PYRAMID_COMPLEX, GRAND_PYRAMID_COMPLEX).
    static const char *const subtile_suffixes[] = {
        "_PYRAMID_CORNER", "_PYRAMID_WALL", "_PYRAMID_SIDE", "_PYRAMID_ENTRANCE",
        "_MASTABA_CORNER", "_MASTABA_WALL", "_MASTABA_SIDE", "_MASTABA_ENTRANCE",
    };
    for (const char *suffix : subtile_suffixes) {
        if (std::strstr(name, suffix) != nullptr) {
            return false;
        }
    }
    return true;
}
} // namespace

void config_show_city_buildings_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("City Buildings", ImGuiTreeNodeFlags_None, "City Buildings");
    if (!common_open) {
        return;
    }

    auto buildings = city_buildings();

    int total_slots = static_cast<int>(buildings.size());
    int valid_count = 0;
    std::array<int, BUILDING_MAX> type_counts{};

    for (const auto& b : buildings) {
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

    bool allowed_open = ImGui::TreeNodeEx("Allowed Buildings", ImGuiTreeNodeFlags_None, "Allowed Buildings");
    if (allowed_open) {
        // Flat filterable list. Toggling fires event_use_building which the JS
        // building_menu_ctrl subscriber translates into scenario_building_allow +
        // cascading category enables; event_building_menu_changed forces the
        // sidebar to rebuild so the change is visible immediately.
        static ImGuiTextFilter filter;
        filter.Draw("Filter (-excl,+incl)", 240.f);

        const ImGuiTableFlags table_flags = ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable
                                            | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg;
        ImGui::BeginTable("AllowedBuildings", 2, table_flags, ImVec2(0.f, 280.f));
        ImGui::TableSetupColumn("Building", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Allowed", ImGuiTableColumnFlags_WidthFixed, 70.f);
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();

        for (int t = BUILDING_NONE + 1; t < BUILDING_MAX; ++t) {
            const char *name = token::find_name(e_building_type_tokens, t);
            if (!is_debug_pickable_type(name)) {
                continue;
            }

            // strip BUILDING_ prefix for the display label
            const char *label = (std::strncmp(name, "BUILDING_", 9) == 0) ? name + 9 : name;
            bstring256 row_label;
            row_label.printf("%s [%d]", label, t);
            if (!filter.PassFilter(row_label.c_str())) {
                continue;
            }

            ImGui::PushID(t);
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted(row_label.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);

            bool allowed = scenario_building_allowed((e_building_type)t);
            if (ImGui::Checkbox("##cb", &allowed)) {
                events::emit(event_use_building{ t, allowed });
                events::emit(event_building_menu_changed{ true });
            }
            ImGui::PopID();
        }

        ImGui::EndTable();
        ImGui::TreePop();
    }

    ImGui::TreePop();
}

