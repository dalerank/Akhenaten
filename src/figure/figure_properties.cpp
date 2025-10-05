#include "figure/figure.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "city/city_figures.h"

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

    if (common_open) {
        game_debug_show_property("Kill", [f] { f->poof(); });
        game_debug_show_property("id", f->id, true);
        game_debug_show_property("resource_id", resource_name(f->resource_id));
        game_debug_show_property("resource_amount_full", f->resource_amount_full);
        game_debug_show_property("home_building_id", f->home_building_id);
        game_debug_show_property("destination_building_id", f->destination_building_id);
        game_debug_show_property("action_state", f->action_state);
        game_debug_show_property("type(name)", (pcstr)figure_static_params::get(f->type).name);
        game_debug_show_property("type", figure_static_params::get(f->type).ftype, true);
        game_debug_show_property("wait_ticks", f->wait_ticks);
        game_debug_show_property("terrain_type", get_terrain_type("", f->terrain_type));
        game_debug_show_property("roam_length", f->roam_length);
        game_debug_show_property("main_image_id", f->main_image_id);
        game_debug_show_property("cart_image_id", f->cart_image_id);
        game_debug_show_property("use_cross_country", f->use_cross_country);
        game_debug_show_property("state", f->state);
        game_debug_show_property("faction_id", f->faction_id);
        game_debug_show_property("action_state_before_attack", f->action_state_before_attack);
        game_debug_show_property("direction", f->direction);
        game_debug_show_property("previous_tile_direction", f->previous_tile_direction);
        game_debug_show_property("attack_direction", f->attack_direction);
        game_debug_show_property("tile", f->tile);
        int grid_offset = f->tile.grid_offset();
        game_debug_show_property("grid_offset", grid_offset, true);
        game_debug_show_property("previous_tile", f->previous_tile);
        game_debug_show_property("source_tile", f->source_tile);
        game_debug_show_property("destination_tile", f->destination_tile);
        game_debug_show_property("missile_damage", f->missile_damage);
        game_debug_show_property("damage", f->damage);
        game_debug_show_property("wait_ticks", f->wait_ticks);
        game_debug_show_property("action_state", f->action_state);
        game_debug_show_property("progress_inside_speed", f->progress_inside_speed);
        game_debug_show_property("progress_inside", f->progress_inside);
        game_debug_show_property("progress_on_tile", f->progress_on_tile);
        game_debug_show_property("routing_path_id", f->routing_path_id);
        game_debug_show_property("routing_path_current_tile", f->routing_path_current_tile);
        game_debug_show_property("routing_path_length", f->routing_path_length);
        game_debug_show_property("in_building_wait_ticks", f->in_building_wait_ticks);
        game_debug_show_property("outside_road_ticks", f->outside_road_ticks);
        game_debug_show_property("max_roam_length", f->max_roam_length);
        game_debug_show_property("roam_wander_freely", f->roam_wander_freely);
        game_debug_show_property("roam_random_counter", f->roam_random_counter);
        game_debug_show_property("roam_turn_direction", f->roam_turn_direction);
        game_debug_show_property("roam_ticks_until_next_turn", f->roam_ticks_until_next_turn);
        game_debug_show_property("cc_coords", f->cc_coords);
        game_debug_show_property("cc_destination", f->cc_destination);
        game_debug_show_property("cc_delta", f->cc_delta);
        game_debug_show_property("cc_delta_xy", f->cc_delta_xy);
        game_debug_show_property("cc_direction", f->cc_direction);
        game_debug_show_property("speed_multiplier", f->speed_multiplier);
        game_debug_show_property("min_max_seen", f->min_max_seen);
        game_debug_show_property("movement_ticks_watchdog", f->movement_ticks_watchdog);
        game_debug_show_property("leading_figure_id", f->leading_figure_id);
        game_debug_show_property("cart_offset", f->cart_offset);
        game_debug_show_property("name", f->name);
        game_debug_show_property("terrain_usage", f->terrain_usage);
        game_debug_show_property("allow_move_type", f->allow_move_type);
        game_debug_show_property("height_adjusted_ticks", f->height_adjusted_ticks);
        game_debug_show_property("current_height", f->current_height);
        game_debug_show_property("target_height", f->target_height);
        game_debug_show_property("collecting_item_id", f->collecting_item_id);
        game_debug_show_property("phrase_sequence_exact", f->phrase_sequence_exact);
        game_debug_show_property("phrase_group", f->phrase.group);
        game_debug_show_property("phrase_id", f->phrase.id);
        game_debug_show_property("phrase_key", f->phrase_key);
        game_debug_show_property("phrase_sequence_city", f->phrase_sequence_city);
        game_debug_show_property("main_cached_pos", f->main_cached_pos);
        game_debug_show_property("cart_cached_pos", f->cart_cached_pos);

        f->dcast()->debug_show_properties();

        if (f->type == FIGURE_HERBALIST) {
            //game_debug_show_property("see_low_health", f->data.herbalist.see_low_health);
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
        game_debug_show_property("key", f->animctx.key, true);
        game_debug_show_property("base", f->animctx.base);
        game_debug_show_property("offset", f->animctx.offset);
        game_debug_show_property("hashtime", f->animctx.hashtime);
        game_debug_show_property("pos", f->animctx.pos);
        game_debug_show_property("frame_duration", f->animctx.frame_duration);
        game_debug_show_property("max_frames", f->animctx.max_frames);
        game_debug_show_property("frame", f->animctx.frame);
        game_debug_show_property("can_reverse", f->animctx.can_reverse);
        game_debug_show_property("loop", f->animctx.loop);
        game_debug_show_property("is_reverse", f->animctx.is_reverse);
        game_debug_show_property("was_finished", f->animctx.was_finished);

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
        game_debug_show_property("formation_id", f->formation_id, true);
        game_debug_show_property("index_in_formation", f->index_in_formation, true);
        game_debug_show_property("formation_at_rest", f->formation_at_rest, true);

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