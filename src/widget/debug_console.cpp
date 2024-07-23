#include "debug_console.h"

#include "figure/figure.h"
#include "graphics/screen.h"
#include "graphics/graphics.h"
#include "graphics/text.h"
#include "game/game.h"
#include "dev/imgui_qconsole.h"
#include "building/building.h"

#include <SDL.h>
#include <SDL_keyboard.h>
#include "platform/keyboard_input.h"
#include "platform/renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "dev/debug.h"

#include <iostream>

dev::imgui_qconsole *_debug_console = nullptr;

dev::imgui_qconsole &debug_console() {
    if (!_debug_console) {
        _debug_console = new dev::imgui_qconsole();
    }
    return *_debug_console;
}

void game_debug_cli_draw() {
    auto renderer = graphics_renderer();
    SDL_Point platform_window_size;
    SDL_GetWindowSize(renderer->window(), &platform_window_size.x, &platform_window_size.y);

    debug_console().render("##console", game.debug_console, platform_window_size.x, platform_window_size.y * 0.33f);
}

void game_debug_show_property_value(pcstr field, const float &v, bool disabled) {
    ImGui::InputFloat("##value", (float*)&v, 1.0f);
}

void game_debug_show_property_value(pcstr field, const int &v, bool disabled) {
    ImGuiInputTextFlags_ flags = disabled ? ImGuiInputTextFlags_ReadOnly : ImGuiInputTextFlags_None;
    ImGui::InputInt("##value", (int*)&v, 1, 100, flags);
}

void game_debug_show_property_value(pcstr field, const e_move_type &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_S8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const int8_t &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_S8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const short &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_S16, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const uint8_t &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_U8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const uint16_t &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_U16, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const bool &v, bool disabled) {
    ImGui::InputScalar(field, ImGuiDataType_U8, (void *)&v);
}

void game_debug_show_property_value(pcstr field, const bstring64 &v, bool disabled) {
    ImGui::Text(!!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const bstring256 &v, bool disabled) {
    ImGui::Text(!!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const xstring &v, bool disabled) {
    ImGui::Text(!!v ? v.c_str() : "none");
}

void game_debug_show_property_value(pcstr field, const vec2i &v, bool disabled) {
    ImGui::InputInt2(field, (int*)&v);
}

void game_debug_show_property_value(pcstr field, const tile2i &v, bool disabled) {
    ImGui::InputInt2(field, (int*)&v);
}

void game_debug_show_property_value(pcstr field, const std::function<void()> &f, bool disabled) {
    if (ImGui::Button(field)) {
        f();
    }
}

template<typename T>
void game_debug_show_property_t(int &i, pcstr field, const T &v, bool disabled = false) {
    ImGui::PushID(i); 
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx("Field", flags, "%s", field);
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(-FLT_MIN);

    if (disabled) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    }

    game_debug_show_property_value(field, v, disabled);
    
    if (disabled) {
        ImGui::PopItemFlag();
    }
    ImGui::NextColumn();
    ImGui::PopID();
    ++i;
}

void game_debug_show_property_t(int &i, pcstr field, pcstr v) {
    bstring256 _v(v);
    game_debug_show_property_t(i, field, _v);
}

static void game_debug_show_properties_object(pcstr prefix, building *b) {
    ImGui::PushID(0x80000000 | b->id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Building", ImGuiTreeNodeFlags_DefaultOpen, "Building");
    ImGui::TableSetColumnIndex(1); 

    int i = 0;
    if (common_open) {
        game_debug_show_property_t(i, "id", b->id, true);
        game_debug_show_property_t(i, "state", token::find_name(e_building_state_tokens, b->state));
        game_debug_show_property_t(i, "size", b->size);
        game_debug_show_property_t(i, "house_is_merged", b->house_is_merged);
        game_debug_show_property_t(i, "house_size", b->house_size);
        game_debug_show_property_t(i, "tile", b->tile);
        bstring256 type_name; type_name.printf("%s [%d]", token::find_name(e_building_type_tokens, b->type), b->type);
        game_debug_show_property_t(i, "type", type_name);
        game_debug_show_property_t(i, "road_network_id", b->road_network_id);
        game_debug_show_property_t(i, "houses_covered", b->houses_covered);
        game_debug_show_property_t(i, "percentage_houses_covered", b->percentage_houses_covered);
        game_debug_show_property_t(i, "house_population", b->house_population);
        game_debug_show_property_t(i, "house_population_room", b->house_population_room);
        game_debug_show_property_t(i, "distance_from_entry", b->distance_from_entry);
        game_debug_show_property_t(i, "house_highest_population", b->house_highest_population);
        game_debug_show_property_t(i, "house_unreachable_ticks", b->house_unreachable_ticks);
        game_debug_show_property_t(i, "road_access", b->road_access);
        game_debug_show_property_t(i, "figure_spawn_delay", b->figure_spawn_delay);
        game_debug_show_property_t(i, "figure_roam_direction", b->figure_roam_direction);
        game_debug_show_property_t(i, "has_water_access", b->has_water_access);
        game_debug_show_property_t(i, "has_open_water_access", b->has_open_water_access);
        game_debug_show_property_t(i, "prev_part_building_id", b->prev_part_building_id);
        game_debug_show_property_t(i, "next_part_building_id", b->next_part_building_id);
        game_debug_show_property_t(i, "stored_full_amount", b->stored_full_amount);
        game_debug_show_property_t(i, "num_workers", b->num_workers);
        game_debug_show_property_t(i, "fancy_state", b->fancy_state);
        game_debug_show_property_t(i, "labor_category", b->labor_category);
        game_debug_show_property_t(i, "output_resource_first_id", b->output_resource_first_id);
        game_debug_show_property_t(i, "output_resource_second_id", b->output_resource_second_id);
        game_debug_show_property_t(i, "output_resource_second_rate", b->output_resource_second_rate);
        game_debug_show_property_t(i, "has_road_access", b->has_road_access);
        game_debug_show_property_t(i, "house_criminal_active", b->house_criminal_active);
        game_debug_show_property_t(i, "disease_days", b->disease_days);
        game_debug_show_property_t(i, "common_health", b->common_health);
        game_debug_show_property_t(i, "malaria_risk", b->malaria_risk);
        game_debug_show_property_t(i, "damage_risk", b->damage_risk);
        game_debug_show_property_t(i, "fire_risk", b->fire_risk);
        game_debug_show_property_t(i, "fire_duration", b->fire_duration);
        game_debug_show_property_t(i, "health_proof", b->health_proof);
        game_debug_show_property_t(i, "fire_proof", b->fire_proof);
        game_debug_show_property_t(i, "damage_proof", b->damage_proof);
        game_debug_show_property_t(i, "house_tax_coverage", b->house_tax_coverage);
        game_debug_show_property_t(i, "tax_collector_id", b->tax_collector_id);
        game_debug_show_property_t(i, "formation_id", b->formation_id);
        game_debug_show_property_t(i, "tax_income_or_storage", b->tax_income_or_storage);
        game_debug_show_property_t(i, "house_days_without_food", b->house_days_without_food);
        game_debug_show_property_t(i, "has_plague", b->has_plague);
        game_debug_show_property_t(i, "desirability", b->desirability);
        game_debug_show_property_t(i, "is_adjacent_to_water", b->is_adjacent_to_water);
        game_debug_show_property_t(i, "storage_id", b->storage_id);
        game_debug_show_property_t(i, "show_on_problem_overlay", b->show_on_problem_overlay);
        game_debug_show_property_t(i, "deben_storage", b->deben_storage);

        ImGui::TreePop();
    }

    ImGui::PushID(0x81000000 | b->id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool anim_open = ImGui::TreeNodeEx("Anim", ImGuiTreeNodeFlags_DefaultOpen, "Anim");
    ImGui::TableSetColumnIndex(1);

    if (anim_open) {
        game_debug_show_property_t(i, "id", b->anim.id, true);
        game_debug_show_property_t(i, "base", b->anim.base);
        game_debug_show_property_t(i, "offset", b->anim.offset);
        game_debug_show_property_t(i, "hashtime", b->anim.hashtime);
        game_debug_show_property_t(i, "pos", b->anim.pos);
        game_debug_show_property_t(i, "frame_duration", b->anim.frame_duration);
        game_debug_show_property_t(i, "max_frames", b->anim.max_frames);
        game_debug_show_property_t(i, "frame", b->anim.frame);
        game_debug_show_property_t(i, "can_reverse", b->anim.can_reverse);
        game_debug_show_property_t(i, "loop", b->anim.loop);
        game_debug_show_property_t(i, "is_reverse", b->anim.is_reverse);
        game_debug_show_property_t(i, "was_finished", b->anim.was_finished);

        ImGui::TreePop();
    }
    ImGui::PopID();
    ImGui::PopID();
}


static void game_debug_show_properties_object(pcstr prefix, figure *f) {
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
        game_debug_show_property_t(i, "Actions", [f] { f->poof(); });
        game_debug_show_property_t(i, "id", f->id, true);
        game_debug_show_property_t(i, "resource_id", resource_name(f->resource_id));
        game_debug_show_property_t(i, "resource_amount_full", f->resource_amount_full);
        game_debug_show_property_t(i, "home_building_id", f->home_building_id);
        game_debug_show_property_t(i, "destination_building_id", f->destination_building_id);
        game_debug_show_property_t(i, "action_state", f->action_state);
        game_debug_show_property_t(i, "type", figure_impl::params(f->type).name);
        game_debug_show_property_t(i, "wait_ticks", f->wait_ticks);
        game_debug_show_property_t(i, "terrain_type", get_terrain_type("", f->terrain_type));
        game_debug_show_property_t(i, "roam_length", f->roam_length);
        game_debug_show_property_t(i, "sprite_image_id", f->sprite_image_id);
        game_debug_show_property_t(i, "cart_image_id", f->cart_image_id);
        game_debug_show_property_t(i, "use_cross_country", f->use_cross_country);
        game_debug_show_property_t(i, "state", f->state);
        game_debug_show_property_t(i, "faction_id", f->faction_id);
        game_debug_show_property_t(i, "action_state_before_attack", f->action_state_before_attack);
        game_debug_show_property_t(i, "direction", f->direction);
        game_debug_show_property_t(i, "previous_tile_direction", f->previous_tile_direction);
        game_debug_show_property_t(i, "attack_direction", f->attack_direction);
        game_debug_show_property_t(i, "tile", f->tile);
        int grid_offset = f->tile.grid_offset();
        game_debug_show_property_t(i, "grid_offset", grid_offset, true);
        game_debug_show_property_t(i, "previous_tile", f->previous_tile);
        game_debug_show_property_t(i, "source_tile", f->source_tile);
        game_debug_show_property_t(i, "destination_tile", f->destination_tile);
        game_debug_show_property_t(i, "missile_damage", f->missile_damage);
        game_debug_show_property_t(i, "damage", f->damage);
        game_debug_show_property_t(i, "wait_ticks", f->wait_ticks);
        game_debug_show_property_t(i, "action_state", f->action_state);
        game_debug_show_property_t(i, "progress_inside_speed", f->progress_inside_speed);
        game_debug_show_property_t(i, "progress_inside", f->progress_inside);
        game_debug_show_property_t(i, "progress_on_tile", f->progress_on_tile);
        game_debug_show_property_t(i, "routing_path_id", f->routing_path_id);
        game_debug_show_property_t(i, "routing_path_current_tile", f->routing_path_current_tile);
        game_debug_show_property_t(i, "routing_path_length", f->routing_path_length);
        game_debug_show_property_t(i, "in_building_wait_ticks", f->in_building_wait_ticks);
        game_debug_show_property_t(i, "outside_road_ticks", f->outside_road_ticks);
        game_debug_show_property_t(i, "max_roam_length", f->max_roam_length);
        game_debug_show_property_t(i, "roam_wander_freely", f->roam_wander_freely);
        game_debug_show_property_t(i, "roam_random_counter", f->roam_random_counter);
        game_debug_show_property_t(i, "roam_turn_direction", f->roam_turn_direction);
        game_debug_show_property_t(i, "roam_ticks_until_next_turn", f->roam_ticks_until_next_turn);
        game_debug_show_property_t(i, "cc_coords", f->cc_coords);
        game_debug_show_property_t(i, "cc_destination", f->cc_destination);
        game_debug_show_property_t(i, "cc_delta", f->cc_delta);
        game_debug_show_property_t(i, "cc_delta_xy", f->cc_delta_xy);
        game_debug_show_property_t(i, "cc_direction", f->cc_direction);
        game_debug_show_property_t(i, "speed_multiplier", f->speed_multiplier);
        game_debug_show_property_t(i, "migrant_num_people", f->migrant_num_people);
        game_debug_show_property_t(i, "min_max_seen", f->min_max_seen);
        game_debug_show_property_t(i, "movement_ticks_watchdog", f->movement_ticks_watchdog);
        game_debug_show_property_t(i, "leading_figure_id", f->leading_figure_id);
        game_debug_show_property_t(i, "cart_offset", f->cart_offset);
        game_debug_show_property_t(i, "empire_city_id", f->empire_city_id);
        game_debug_show_property_t(i, "trader_amount_bought", f->trader_amount_bought);
        game_debug_show_property_t(i, "name", f->name);
        game_debug_show_property_t(i, "terrain_usage", f->terrain_usage);
        game_debug_show_property_t(i, "allow_move_type", f->allow_move_type);
        game_debug_show_property_t(i, "height_adjusted_ticks", f->height_adjusted_ticks);
        game_debug_show_property_t(i, "current_height", f->current_height);
        game_debug_show_property_t(i, "target_height", f->target_height);
        game_debug_show_property_t(i, "collecting_item_id", f->collecting_item_id);
        game_debug_show_property_t(i, "trade_ship_failed_dock_attempts", f->trade_ship_failed_dock_attempts);
        game_debug_show_property_t(i, "phrase_sequence_exact", f->phrase_sequence_exact);
        game_debug_show_property_t(i, "phrase_group", f->phrase_group);
        game_debug_show_property_t(i, "phrase_id", f->phrase_id);
        game_debug_show_property_t(i, "phrase_key", f->phrase_key);
        game_debug_show_property_t(i, "phrase_sequence_city", f->phrase_sequence_city);
        game_debug_show_property_t(i, "trader_id", f->trader_id);
        game_debug_show_property_t(i, "cached_pos", f->cached_pos);

        if (f->type == FIGURE_IMMIGRANT) {
            game_debug_show_property_t(i, "immigrant_home_building_id", f->immigrant_home_building_id);
        }

        if (f->type == FIGURE_HERBALIST) {
            game_debug_show_property_t(i, "see_low_health", f->local_data.herbalist.see_low_health);
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
        game_debug_show_property_t(i, "id", f->anim.id, true);
        game_debug_show_property_t(i, "base", f->anim.base);
        game_debug_show_property_t(i, "offset", f->anim.offset);
        game_debug_show_property_t(i, "hashtime", f->anim.hashtime);
        game_debug_show_property_t(i, "pos", f->anim.pos);
        game_debug_show_property_t(i, "frame_duration", f->anim.frame_duration);
        game_debug_show_property_t(i, "max_frames", f->anim.max_frames);
        game_debug_show_property_t(i, "frame", f->anim.frame);
        game_debug_show_property_t(i, "can_reverse", f->anim.can_reverse);
        game_debug_show_property_t(i, "loop", f->anim.loop);
        game_debug_show_property_t(i, "is_reverse", f->anim.is_reverse);
        game_debug_show_property_t(i, "was_finished", f->anim.was_finished);

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
        game_debug_show_property_t(i, "formation_id", f->formation_id, true);
        game_debug_show_property_t(i, "index_in_formation", f->index_in_formation, true);
        game_debug_show_property_t(i, "formation_at_rest", f->formation_at_rest, true);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void game_debug_properties_draw() {
    if (!game.debug_properties) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Properties", &game.debug_properties)) {
        ImGui::End();
        return;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        if (g_debug_figure_id > 0) {
            figure *f = figure_get(g_debug_figure_id);
            game_debug_show_properties_object("Figure", f);
        }

        if (g_debug_building_id > 0) {
            building *b = building_get(g_debug_building_id);
            game_debug_show_properties_object("Building", b);
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
    ImGui::End();

    //g_debug_figure_id = 0;
}

void game_debug_cli_message(pcstr msg) {
    debug_console() << msg << std::endl;
}

void game_imgui_overlay_init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    auto renderer = graphics_renderer();
    ImGui_ImplSDL2_InitForSDLRenderer(renderer->window(), renderer->renderer());
    ImGui_ImplSDLRenderer_Init(renderer->renderer());

    debug_console().con.bind_command("close", [] (auto &, auto &) { game.debug_console = false; });
}

void game_imgui_overlay_destroy() {
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void game_imgui_overlay_begin_frame() {
    if (!game.debug_console) {
        //return;
    }

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void game_imgui_overlay_draw() {
    if (!game.debug_console) {
    //    return;
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

bool game_imgui_overlay_handle_event(void *e) {
    const SDL_Event *event = (const SDL_Event *)e;

    if (event->type == SDL_KEYDOWN) {
        int key = event->key.keysym.scancode;

        if (key == SDL_SCANCODE_GRAVE) {
            game_toggle_debug_console();
        }
    }

    if (event->type == SDL_TEXTINPUT && *event->text.text == '`') {
        debug_console().skip_event = true;
    }

    if (!(game.debug_console || game.debug_properties)) {
        return false;
    }

    if (debug_console().skip_event) {
        debug_console().skip_event = false;
        return false;
    }

    ImGui_ImplSDL2_ProcessEvent(event);
    return false;
}

void game_toggle_debug_console() {
    game.debug_console = !game.debug_console;
    if (game.debug_console) {
        debug_console().is.reclaim_focus = true;
    }
}

void bind_debug_command(pcstr cmd, std::function<void(std::istream &, std::ostream &)> f) {
    debug_console().con.bind_command(cmd, f);
}

void bind_debug_console_var_int(pcstr var, int &ref) {
    debug_console().con.bind_cvar(var, ref);
}

void bind_debug_console_var_bool(pcstr var, bool &ref) {
    debug_console().con.bind_cvar(var, ref);
}
