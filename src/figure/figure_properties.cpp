#include "figure/figure.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

ANK_REGISTER_PROPS_ITERATOR(config_load_figure_properties);

void game_debug_show_properties_object(pcstr prefix, figure *f) {
    // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
    ImGui::PushID(0x10000000 | f->id);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Figure", ImGuiTreeNodeFlags_DefaultOpen, "Common");
    ImGui::TableSetColumnIndex(1);
    //ImGui::Text("my sailor is rich");

    int i = 0;
    if (common_open) {
        game_debug_show_property(i, "Kill", [f] { f->poof(); });
        game_debug_show_property(i, "id", f->id, true);
        game_debug_show_property(i, "resource_id", resource_name(f->resource_id));
        game_debug_show_property(i, "resource_amount_full", f->resource_amount_full);
        game_debug_show_property(i, "home_building_id", f->home_building_id);
        game_debug_show_property(i, "destination_building_id", f->destination_building_id);
        game_debug_show_property(i, "action_state", f->action_state);
        game_debug_show_property(i, "type(name)", (pcstr)figure_impl::params(f->type).name);
        game_debug_show_property(i, "type", figure_impl::params(f->type).ftype, true);
        game_debug_show_property(i, "wait_ticks", f->wait_ticks);
        game_debug_show_property(i, "terrain_type", get_terrain_type("", f->terrain_type));
        game_debug_show_property(i, "roam_length", f->roam_length);
        game_debug_show_property(i, "sprite_image_id", f->sprite_image_id);
        game_debug_show_property(i, "cart_image_id", f->cart_image_id);
        game_debug_show_property(i, "use_cross_country", f->use_cross_country);
        game_debug_show_property(i, "state", f->state);
        game_debug_show_property(i, "faction_id", f->faction_id);
        game_debug_show_property(i, "action_state_before_attack", f->action_state_before_attack);
        game_debug_show_property(i, "direction", f->direction);
        game_debug_show_property(i, "previous_tile_direction", f->previous_tile_direction);
        game_debug_show_property(i, "attack_direction", f->attack_direction);
        game_debug_show_property(i, "tile", f->tile);
        int grid_offset = f->tile.grid_offset();
        game_debug_show_property(i, "grid_offset", grid_offset, true);
        game_debug_show_property(i, "previous_tile", f->previous_tile);
        game_debug_show_property(i, "source_tile", f->source_tile);
        game_debug_show_property(i, "destination_tile", f->destination_tile);
        game_debug_show_property(i, "missile_damage", f->missile_damage);
        game_debug_show_property(i, "damage", f->damage);
        game_debug_show_property(i, "wait_ticks", f->wait_ticks);
        game_debug_show_property(i, "action_state", f->action_state);
        game_debug_show_property(i, "progress_inside_speed", f->progress_inside_speed);
        game_debug_show_property(i, "progress_inside", f->progress_inside);
        game_debug_show_property(i, "progress_on_tile", f->progress_on_tile);
        game_debug_show_property(i, "routing_path_id", f->routing_path_id);
        game_debug_show_property(i, "routing_path_current_tile", f->routing_path_current_tile);
        game_debug_show_property(i, "routing_path_length", f->routing_path_length);
        game_debug_show_property(i, "in_building_wait_ticks", f->in_building_wait_ticks);
        game_debug_show_property(i, "outside_road_ticks", f->outside_road_ticks);
        game_debug_show_property(i, "max_roam_length", f->max_roam_length);
        game_debug_show_property(i, "roam_wander_freely", f->roam_wander_freely);
        game_debug_show_property(i, "roam_random_counter", f->roam_random_counter);
        game_debug_show_property(i, "roam_turn_direction", f->roam_turn_direction);
        game_debug_show_property(i, "roam_ticks_until_next_turn", f->roam_ticks_until_next_turn);
        game_debug_show_property(i, "cc_coords", f->cc_coords);
        game_debug_show_property(i, "cc_destination", f->cc_destination);
        game_debug_show_property(i, "cc_delta", f->cc_delta);
        game_debug_show_property(i, "cc_delta_xy", f->cc_delta_xy);
        game_debug_show_property(i, "cc_direction", f->cc_direction);
        game_debug_show_property(i, "speed_multiplier", f->speed_multiplier);
        game_debug_show_property(i, "migrant_num_people", f->migrant_num_people);
        game_debug_show_property(i, "min_max_seen", f->min_max_seen);
        game_debug_show_property(i, "movement_ticks_watchdog", f->movement_ticks_watchdog);
        game_debug_show_property(i, "leading_figure_id", f->leading_figure_id);
        game_debug_show_property(i, "cart_offset", f->cart_offset);
        game_debug_show_property(i, "empire_city_id", f->empire_city_id);
        game_debug_show_property(i, "trader_amount_bought", f->trader_amount_bought);
        game_debug_show_property(i, "name", f->name);
        game_debug_show_property(i, "terrain_usage", f->terrain_usage);
        game_debug_show_property(i, "allow_move_type", f->allow_move_type);
        game_debug_show_property(i, "height_adjusted_ticks", f->height_adjusted_ticks);
        game_debug_show_property(i, "current_height", f->current_height);
        game_debug_show_property(i, "target_height", f->target_height);
        game_debug_show_property(i, "collecting_item_id", f->collecting_item_id);
        game_debug_show_property(i, "trade_ship_failed_dock_attempts", f->trade_ship_failed_dock_attempts);
        game_debug_show_property(i, "phrase_sequence_exact", f->phrase_sequence_exact);
        game_debug_show_property(i, "phrase_group", f->phrase.group);
        game_debug_show_property(i, "phrase_id", f->phrase.id);
        game_debug_show_property(i, "phrase_key", f->phrase_key);
        game_debug_show_property(i, "phrase_sequence_city", f->phrase_sequence_city);
        game_debug_show_property(i, "trader_id", f->trader_id);
        game_debug_show_property(i, "cached_pos", f->cached_pos);

        if (f->type == FIGURE_IMMIGRANT) {
            game_debug_show_property(i, "immigrant_home_building_id", f->immigrant_home_building_id);
        }

        if (f->type == FIGURE_HERBALIST) {
            game_debug_show_property(i, "see_low_health", f->local_data.herbalist.see_low_health);
        }

        ImGui::TreePop();
    }
    ImGui::PopID();

    ImGui::PushID(0x20000000 | f->id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool anim_open = ImGui::TreeNodeEx("Anim", ImGuiTreeNodeFlags_DefaultOpen, "Anim");
    ImGui::TableSetColumnIndex(1);

    if (anim_open) {
        game_debug_show_property(i, "id", f->anim.id, true);
        game_debug_show_property(i, "base", f->anim.base);
        game_debug_show_property(i, "offset", f->anim.offset);
        game_debug_show_property(i, "hashtime", f->anim.hashtime);
        game_debug_show_property(i, "pos", f->anim.pos);
        game_debug_show_property(i, "frame_duration", f->anim.frame_duration);
        game_debug_show_property(i, "max_frames", f->anim.max_frames);
        game_debug_show_property(i, "frame", f->anim.frame);
        game_debug_show_property(i, "can_reverse", f->anim.can_reverse);
        game_debug_show_property(i, "loop", f->anim.loop);
        game_debug_show_property(i, "is_reverse", f->anim.is_reverse);
        game_debug_show_property(i, "was_finished", f->anim.was_finished);

        ImGui::TreePop();
    }
    ImGui::PopID();

    ImGui::PushID(0x40000000 | f->id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool formation_open = ImGui::TreeNodeEx("Formation", ImGuiTreeNodeFlags_DefaultOpen, "Formation");
    ImGui::TableSetColumnIndex(1);

    if (formation_open) {
        game_debug_show_property(i, "formation_id", f->formation_id, true);
        game_debug_show_property(i, "index_in_formation", f->index_in_formation, true);
        game_debug_show_property(i, "formation_at_rest", f->formation_at_rest, true);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void config_load_figure_properties(bool header) {
    static bool _debug_figure_open = true;

    if (header) {
        ImGui::Checkbox("Figure", &_debug_figure_open);
        return;
    } 

    if (_debug_figure_open && g_debug_figure_id > 0 && ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        figure *f = figure_get(g_debug_figure_id);
        game_debug_show_properties_object("Figure", f);
        ImGui::EndTable();
    }
}