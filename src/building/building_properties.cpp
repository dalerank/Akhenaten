#include "building/building.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "building/destruction.h"

ANK_REGISTER_PROPS_ITERATOR(config_load_building_properties);
void game_debug_show_properties_object(pcstr prefix, building *b) {
    ImGui::PushID(0x80000000 | b->id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Building", ImGuiTreeNodeFlags_DefaultOpen, "Building");
    ImGui::TableSetColumnIndex(1); 

    int i = 0;
    if (common_open) {
        game_debug_show_property(i, "Untype/Destroy", [b] { building_destroy_by_collapse(b); });
        game_debug_show_property(i, "id", b->id, true);
        game_debug_show_property(i, "state", token::find_name(e_building_state_tokens, b->state));
        game_debug_show_property(i, "size", b->size);
        game_debug_show_property(i, "house_is_merged", b->house_is_merged);
        game_debug_show_property(i, "house_size", b->house_size);
        game_debug_show_property(i, "tile", b->tile);
        bstring256 type_name; type_name.printf("%s [%d]", token::find_name(e_building_type_tokens, b->type), b->type);
        game_debug_show_property(i, "type", type_name);
        game_debug_show_property(i, "road_network_id", b->road_network_id);
        game_debug_show_property(i, "houses_covered", b->houses_covered);
        game_debug_show_property(i, "percentage_houses_covered", b->percentage_houses_covered);
        game_debug_show_property(i, "house_population", b->house_population);
        game_debug_show_property(i, "house_population_room", b->house_population_room);
        game_debug_show_property(i, "distance_from_entry", b->distance_from_entry);
        game_debug_show_property(i, "house_highest_population", b->house_highest_population);
        game_debug_show_property(i, "house_unreachable_ticks", b->house_unreachable_ticks);
        game_debug_show_property(i, "road_access", b->road_access);
        game_debug_show_property(i, "figure_spawn_delay", b->figure_spawn_delay);
        game_debug_show_property(i, "figure_roam_direction", b->figure_roam_direction);
        game_debug_show_property(i, "has_water_access", b->has_water_access);
        game_debug_show_property(i, "has_open_water_access", b->has_open_water_access);
        game_debug_show_property(i, "prev_part_building_id", b->prev_part_building_id);
        game_debug_show_property(i, "next_part_building_id", b->next_part_building_id);
        game_debug_show_property(i, "stored_full_amount", b->stored_full_amount);
        game_debug_show_property(i, "num_workers", b->num_workers);
        game_debug_show_property(i, "fancy_state", b->fancy_state);
        game_debug_show_property(i, "labor_category", b->labor_category);
        game_debug_show_property(i, "output_resource_first_id", b->output_resource_first_id);
        game_debug_show_property(i, "output_resource_second_id", b->output_resource_second_id);
        game_debug_show_property(i, "output_resource_second_rate", b->output_resource_second_rate);
        game_debug_show_property(i, "has_road_access", b->has_road_access);
        game_debug_show_property(i, "house_criminal_active", b->house_criminal_active);
        game_debug_show_property(i, "disease_days", b->disease_days);
        game_debug_show_property(i, "common_health", b->common_health);
        game_debug_show_property(i, "malaria_risk", b->malaria_risk);
        game_debug_show_property(i, "damage_risk", b->damage_risk);
        game_debug_show_property(i, "fire_risk", b->fire_risk);
        game_debug_show_property(i, "fire_duration", b->fire_duration);
        game_debug_show_property(i, "health_proof", b->health_proof);
        game_debug_show_property(i, "fire_proof", b->fire_proof);
        game_debug_show_property(i, "damage_proof", b->damage_proof);
        game_debug_show_property(i, "house_tax_coverage", b->house_tax_coverage);
        game_debug_show_property(i, "tax_collector_id", b->tax_collector_id);
        game_debug_show_property(i, "formation_id", b->formation_id);
        game_debug_show_property(i, "tax_income_or_storage", b->tax_income_or_storage);
        game_debug_show_property(i, "house_days_without_food", b->house_days_without_food);
        game_debug_show_property(i, "has_plague", b->has_plague);
        game_debug_show_property(i, "desirability", b->desirability);
        game_debug_show_property(i, "is_adjacent_to_water", b->is_adjacent_to_water);
        game_debug_show_property(i, "storage_id", b->storage_id);
        game_debug_show_property(i, "show_on_problem_overlay", b->show_on_problem_overlay);
        game_debug_show_property(i, "deben_storage", b->deben_storage);

        ImGui::TreePop();
    }
    ImGui::PopID();

    ImGui::PushID(0x81000000 | b->id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool anim_open = ImGui::TreeNodeEx("Anim", ImGuiTreeNodeFlags_DefaultOpen, "Anim");
    ImGui::TableSetColumnIndex(1);

    if (anim_open) {
        game_debug_show_property(i, "id", b->anim.id, true);
        game_debug_show_property(i, "base", b->anim.base);
        game_debug_show_property(i, "offset", b->anim.offset);
        game_debug_show_property(i, "hashtime", b->anim.hashtime);
        game_debug_show_property(i, "pos", b->anim.pos);
        game_debug_show_property(i, "frame_duration", b->anim.frame_duration);
        game_debug_show_property(i, "max_frames", b->anim.max_frames);
        game_debug_show_property(i, "frame", b->anim.frame);
        game_debug_show_property(i, "can_reverse", b->anim.can_reverse);
        game_debug_show_property(i, "loop", b->anim.loop);
        game_debug_show_property(i, "is_reverse", b->anim.is_reverse);
        game_debug_show_property(i, "was_finished", b->anim.was_finished);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void config_load_building_properties(bool header) {
    static bool _debug_buildng_open = true;

    if (header) {
        ImGui::Checkbox("Building", &_debug_buildng_open);
        return;
    } 

    if (_debug_buildng_open && g_debug_building_id > 0 && ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        building *b = building_get(g_debug_building_id);
        game_debug_show_properties_object("Building", b);
        ImGui::EndTable();
    }
}