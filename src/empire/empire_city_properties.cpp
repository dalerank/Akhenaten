#include "empire_city.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "empire/empire_map.h"
#include "empire/empire.h"

ANK_REGISTER_PROPS_ITERATOR(config_load_selected_empire_city_properties);
ANK_REGISTER_PROPS_ITERATOR(config_load_all_empire_city_properties);

void game_debug_show_properties_object(pcstr prefix, empire_city *c) {
    if (!c->in_use) {
        return;
    }

    ImGui::PushID(0x80000000 | c->lookup_id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    pcstr city_name = ui::str(195, c->name_id);
    bool common_open = ImGui::TreeNodeEx(city_name, ImGuiTreeNodeFlags_None, "%s", city_name);
    ImGui::TableSetColumnIndex(1); 

    if (common_open) {
        game_debug_show_property("in_use", c->in_use);
        bstring256 type_name; type_name.printf("%s [%d]", token::find_name(e_empire_city_tokens, c->type), c->type);
        game_debug_show_property("type<name>", type_name);
        game_debug_show_property("type", c->type);
        game_debug_show_property("name_id", c->name_id);
        game_debug_show_property("name", ui::str(195, c->name_id));
        game_debug_show_property("route_id", c->route_id);
        game_debug_show_property("is_open", c->is_open);
        game_debug_show_property("cost_to_open", c->cost_to_open);
        game_debug_show_property("ph_unk01", c->ph_unk01);
        game_debug_show_property("ph_unk02", c->ph_unk02);
        game_debug_show_property("trader_entry_delay", c->trader_entry_delay);
        game_debug_show_property("empire_object_id", c->empire_object_id);
        game_debug_show_property("is_sea_trade", c->is_sea_trade);
        game_debug_show_property("trader_figure_ids[0]", c->trader_figure_ids[0], true);
        game_debug_show_property("trader_figure_ids[1]", c->trader_figure_ids[1], true);
        game_debug_show_property("trader_figure_ids[2]", c->trader_figure_ids[2], true);

        {
            ImGui::PushID(0x81000000 | c->name_id);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            const bool buy_res_open = ImGui::TreeNodeEx("Buy Resources", ImGuiTreeNodeFlags_DefaultOpen, "Buy Resources");
            ImGui::TableSetColumnIndex(1);

            if (buy_res_open) {
                for (const auto r : resource_list::all) {
                    game_debug_show_property(ui::resource_name(r.type), c->buys_resource[r.type]);
                }

                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        {
            ImGui::PushID(0x41000000 | c->name_id);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            const bool sell_res_open = ImGui::TreeNodeEx("Sells Resources", ImGuiTreeNodeFlags_DefaultOpen, "Sells Resource");
            ImGui::TableSetColumnIndex(1);

            if (sell_res_open) {
                for (const auto r : resource_list::all) {
                    game_debug_show_property(ui::resource_name(r.type), c->sells_resource[r.type]);
                }

                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void config_load_selected_empire_city_properties(bool header) {
    if (header) {
        return;
    }

    int selected_object = g_empire_map.selected_object();
    int selected_city = selected_object ? g_empire.get_city_for_object(selected_object - 1) : 0;
    
    bool common_open = ImGui::TreeNodeEx("Selected Empire City", ImGuiTreeNodeFlags_None, "Selected Empire City");
    if (common_open) {
        if (selected_city > 0) {
            ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);
            empire_city *c = g_empire.city(selected_city);
            game_debug_show_properties_object("City", c);
            ImGui::EndTable();
        } else {
            ImGui::Text("No selected empire city");
        }

        ImGui::TreePop();
    }
}

void config_load_all_empire_city_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Empire Cities", ImGuiTreeNodeFlags_None, "Empire Cities");
    if (common_open) {
        ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);
        for (auto &city : g_empire.get_cities()) {
            game_debug_show_properties_object("City", &city);
        }
        ImGui::EndTable();

        ImGui::TreePop();
    }
}