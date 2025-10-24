#include "city_migration.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_migration_properties);
void config_show_migration_properties(bool header) {
    if (header) {
        return;
    }    
    bool common_open = ImGui::TreeNodeEx("Migration", ImGuiTreeNodeFlags_None, "Migration");
    if (common_open) {
        ImGui::BeginTable("Migration", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        auto &migration = g_city.migration;
        game_debug_show_property("invading_cap", migration.invading_cap);
        game_debug_show_property("migration_cap", migration.migration_cap);
        game_debug_show_property("percentage_by_sentiment", migration.percentage_by_sentiment);
        game_debug_show_property("emigration_message_shown", migration.emigration_message_shown);
        game_debug_show_property("newcomers", migration.newcomers);
        game_debug_show_property("percentage", migration.percentage);
        game_debug_show_property("no_immigration_cause", migration.no_immigration_cause);
        game_debug_show_property("refused_immigrants_today", migration.refused_immigrants_today);
        game_debug_show_property("emigrated_today", migration.emigrated_today);
        game_debug_show_property("immigrated_today", migration.immigrated_today);
        game_debug_show_property("emigration_queue_size", migration.emigration_queue_size);
        game_debug_show_property("immigration_queue_size", migration.immigration_queue_size);
        game_debug_show_property("immigration_duration", migration.immigration_duration);
        game_debug_show_property("emigration_amount_per_batch", migration.emigration_amount_per_batch);
        game_debug_show_property("emigration_duration", migration.emigration_duration);
        game_debug_show_property("immigration_amount_per_batch", migration.immigration_amount_per_batch);
        game_debug_show_property("nobles_leave_city_this_year", migration.nobles_leave_city_this_year);

        ImGui::EndTable();

        ImGui::TreePop();
    }
}
