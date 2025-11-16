#include "game_config.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "core/bstring.h"
#include <cctype>

ANK_REGISTER_PROPS_ITERATOR(config_show_game_features_properties);

static bool string_contains_ci(const char* str, const char* substr) {
    if (!substr || !*substr) {
        return true; // Empty filter matches everything
    }
    if (!str || !*str) {
        return false;
    }

    const char* s = str;
    const char* p = substr;
    
    while (*s) {
        const char* s_check = s;
        const char* p_check = p;
        
        while (*s_check && *p_check && 
               std::tolower(static_cast<unsigned char>(*s_check)) == 
               std::tolower(static_cast<unsigned char>(*p_check))) {
            s_check++;
            p_check++;
        }
        
        if (!*p_check) {
            return true; // Found match
        }
        
        s++;
    }
    
    return false;
}

static bool feature_matches_filter(game_features::game_feature* feature, const char* filter) {
    if (!filter || !*filter) {
        return true; // No filter means show all
    }
    
    if (string_contains_ci(feature->name.c_str(), filter)) {
        return true;
    }
    
    if (!feature->text.empty() && string_contains_ci(feature->text.c_str(), filter)) {
        return true;
    }
    
    return false;
}

void config_show_game_features_properties(bool header) {
    if (header) {
        return;
    }

    bool features_open = ImGui::TreeNodeEx("Game Features", ImGuiTreeNodeFlags_None, "Game Features");
    if (!features_open) {
        return;
    }

    static char filter_buffer[256] = "";
    ImGui::Text("Filter:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 100);
    ImGui::InputText("##filter", filter_buffer, sizeof(filter_buffer));
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        filter_buffer[0] = '\0';
    }

    auto all_features = game_features::all();

    ImGui::BeginTable("GameFeatures", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

    int bool_count = 0;
    int string_count = 0;
    int float_count = 0;
    int vec2i_count = 0;
    int total_count = static_cast<int>(all_features.size());

    for (auto* feature : all_features) {
        switch (feature->type()) {
            case setting_bool:
                bool_count++;
                break;
            case setting_string:
                string_count++;
                break;
            case setting_float:
                float_count++;
                break;
            case setting_vec2i:
                vec2i_count++;
                break;
        }
    }

    game_debug_show_property("total_features", total_count, true);
    game_debug_show_property("bool_features", bool_count, true);
    game_debug_show_property("string_features", string_count, true);
    if (float_count > 0) {
        game_debug_show_property("float_features", float_count, true);
    }
    if (vec2i_count > 0) {
        game_debug_show_property("vec2i_features", vec2i_count, true);
    }

    ImGui::EndTable();

    int filtered_bool_count = 0;
    int filtered_string_count = 0;
    for (auto* feature : all_features) {
        if (!feature_matches_filter(feature, filter_buffer)) {
            continue;
        }
        if (feature->type() == setting_bool) {
            filtered_bool_count++;
        } else if (feature->type() == setting_string) {
            filtered_string_count++;
        }
    }

    bstring256 bool_label;
    bool_label.printf("Bool Features (%d)", filtered_bool_count);
    bool bool_features_open = ImGui::TreeNodeEx("Bool Features", ImGuiTreeNodeFlags_None, "%s", bool_label.c_str());
    if (bool_features_open) {
        ImGui::BeginTable("BoolFeatures", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        for (auto* feature : all_features) {
            if (feature->type() != setting_bool) {
                continue;
            }

            if (!feature_matches_filter(feature, filter_buffer)) {
                continue;
            }

            bstring256 label;
            label.printf("%s", feature->name.c_str());
            bool current_value = feature->to_bool();
            bool save = current_value;
            game_debug_show_property(label.c_str(), current_value);
            if (save != current_value) {
                feature->set(current_value);
            }
        }

        ImGui::EndTable();
        ImGui::TreePop();
    }

    bstring256 string_label;
    string_label.printf("String Features (%d)", filtered_string_count);
    bool string_features_open = ImGui::TreeNodeEx("String Features", ImGuiTreeNodeFlags_None, "%s", string_label.c_str());
    if (string_features_open) {
        ImGui::BeginTable("StringFeatures", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        for (auto* feature : all_features) {
            if (feature->type() != setting_string) {
                continue;
            }

            if (!feature_matches_filter(feature, filter_buffer)) {
                continue;
            }

            bstring256 label;
            label.printf("%s", feature->name.c_str());
            xstring current_value = feature->to_string();
            game_debug_show_property(label.c_str(), current_value.c_str());
        }

        ImGui::EndTable();
        ImGui::TreePop();
    }

    int filtered_total = 0;
    for (auto* feature : all_features) {
        if (feature_matches_filter(feature, filter_buffer)) {
            filtered_total++;
        }
    }
    
    bstring256 detailed_label;
    detailed_label.printf("All Features (Detailed) (%d)", filtered_total);
    bool detailed_open = ImGui::TreeNodeEx("All Features (Detailed)", ImGuiTreeNodeFlags_None, "%s", detailed_label.c_str());
    if (detailed_open) {
        for (auto* feature : all_features) {
            if (!feature_matches_filter(feature, filter_buffer)) {
                continue;
            }

            bstring256 feature_label;
            feature_label.printf("%s", feature->name.c_str());

            ImGui::PushID(0x90000000 | ImHashStr(feature_label.c_str()));

            bool feature_open = ImGui::TreeNodeEx(feature_label.c_str(), ImGuiTreeNodeFlags_None, "%s", feature_label.c_str());

            if (feature_open) {
                ImGui::BeginTable(feature_label.c_str(), 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

                game_debug_show_property("name", feature->name.c_str());
                if (!feature->text.empty()) {
                    game_debug_show_property("text", feature->text.c_str());
                }
                game_debug_show_property("default", feature->defaultv);

                // Current value based on type
                switch (feature->type()) {
                    case setting_bool: {
                        bool current = feature->to_bool();
                        bool save = current;
                        game_debug_show_property("current_value", current);
                        if (save != current) {
                            feature->set(current);
                        }
                        break;
                    }
                    case setting_string: {
                        xstring current = feature->to_string();
                        game_debug_show_property("current_value", current.c_str());
                        break;
                    }
                    case setting_float:
                    case setting_vec2i:
                    case setting_none:
                        // These types are supported but don't have direct getters in game_feature
                        // The value can be viewed via defaultv or through _settings
                        break;
                }

                // Type information
                bstring256 type_str;
                switch (feature->type()) {
                    case setting_bool:
                        type_str = "bool";
                        break;
                    case setting_float:
                        type_str = "float";
                        break;
                    case setting_vec2i:
                        type_str = "vec2i";
                        break;
                    case setting_string:
                        type_str = "string";
                        break;
                    case setting_none:
                        type_str = "none";
                        break;
                    default:
                        type_str = "unknown";
                        break;
                }
                game_debug_show_property("type", type_str.c_str());

                ImGui::EndTable();
                ImGui::TreePop();
            }

            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    ImGui::TreePop();
}

