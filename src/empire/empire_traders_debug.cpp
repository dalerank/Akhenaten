#include "empire_traders.h"

#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "game/resource.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_empire_traders_properties);

namespace {

using empire_trader_state_tokens_t = token_holder<empire_trader::e_state, empire_trader::estate_moving_to_destination, empire_trader::estate_count>;
empire_trader_state_tokens_t empire_trader_state_tokens;

void show_resource_block(pcstr label, const uint16_t resources[RESOURCES_MAX]) {
    bool block_open = ImGui::TreeNodeEx(label, ImGuiTreeNodeFlags_None, "%s", label);
    if (!block_open) {
        return;
    }

    for (int resource = RESOURCES_MIN; resource < RESOURCES_MAX; ++resource) {
        uint16_t amount = resources[resource];
        if (!amount) {
            continue;
        }

        game_debug_show_property(resource_name(static_cast<e_resource>(resource)), amount);
    }

    ImGui::TreePop();
}

} // namespace

void config_show_empire_traders_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Empire Traders", ImGuiTreeNodeFlags_None, "Empire Traders");
    if (!common_open) {
        return;
    }

    bool has_active_traders = false;
    for (const auto &trader : g_empire_traders.traders) {
        if (trader.is_active) {
            has_active_traders = true;
            break;
        }
    }

    if (!has_active_traders) {
        ImGui::TextUnformatted("No active empire traders");
    } else {
        ImGui::BeginTable("EmpireTraders", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);
        for (auto &trader : g_empire_traders.traders) {
            if (!trader.is_active) {
                continue;
            }

            ImGui::PushID(trader.id);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            bool trader_open = ImGui::TreeNodeEx("Trader", ImGuiTreeNodeFlags_DefaultOpen, "Trader #%u", trader.id);

            ImGui::TableSetColumnIndex(1);
            if (trader_open) {
                game_debug_show_property("id", trader.id);
                game_debug_show_property("trade_route_id", trader.trade_route_id);
                game_debug_show_property("destination_city_id", trader.destination_city_id);
                game_debug_show_property("owner_figure_id", trader.owner_figure_id);
                game_debug_show_property("current_position", trader.current_position);
                game_debug_show_property("current_route_point", trader.current_route_point);
                game_debug_show_property("movement_delay", trader.movement_delay);
                game_debug_show_property("is_ship", trader.is_ship);
                game_debug_show_property("state", empire_trader_state_tokens.name(trader.state));
                game_debug_show_property("bought_amount", trader.bought_amount);
                game_debug_show_property("bought_value", trader.bought_value);
                game_debug_show_property("sold_amount", trader.sold_amount);
                game_debug_show_property("sold_value", trader.sold_value);

                show_resource_block("Bought Resources", trader.bought_resources);
                show_resource_block("Sold Resources", trader.sold_resources);

                ImGui::TreePop();
            }

            ImGui::PopID();
        }
        ImGui::EndTable();
    }

    ImGui::TreePop();
}

