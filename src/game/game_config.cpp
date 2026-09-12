#include "game_config.h"

#include "content/vfs.h"
#include "core/log.h"
#include "core/vec2i.h"

#include <variant>
#include "core/svector.h"
#include "js/js_game.h"
#include "dev/debug.h"

#include <SDL.h>

static const char* CONF_FILENAME = "akhenaten.conf";

void ANK_REGISTER_CONFIG_ITERATOR(config_load_game_settings) {
    game_features::load();
}

namespace game_features {
    svector<game_feature*, 160> _features;
    globals_settings_t _settings;

    game_feature gameplay_fix_immigration{ "gameplay_fix_immigration", "#TR_CONFIG_FIX_IMMIGRATION_BUG", false, false };
    game_feature gameplay_fix_100y_ghosts{ "gameplay_fix_100y_ghosts", "#TR_CONFIG_FIX_100_YEAR_GHOSTS", false, false };
    game_feature gameplay_fix_editor_events{ "gameplay_fix_editor_events", "#TR_CONFIG_FIX_EDITOR_EVENTS", false, false };
    game_feature gameui_sidebar_info{ "gameui_sidebar_info", "#TR_CONFIG_SIDEBAR_INFO", false, false };
    game_feature gameui_show_intro_video{ "gameui_show_intro_video", "#TR_CONFIG_SHOW_INTRO_VIDEO", true, true };
    game_feature gameui_smooth_scrolling{ "gameui_smooth_scrolling", "#TR_CONFIG_SMOOTH_SCROLLING", false, false };
    game_feature gameui_walker_waypoints{ "gameui_walker_waypoints", "#TR_CONFIG_DRAW_WALKER_WAYPOINTS", false, false };
    game_feature gameui_visual_feedback_on_delete{ "gameui_visual_feedback_on_delete", "#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", false, false };
    game_feature gameui_show_water_structure_range{ "gameui_show_water_structure_range", "#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", false, false };
    game_feature gameui_show_building_road_access{ "gameui_show_building_road_access", "#TR_CONFIG_SHOW_BUILDING_ROAD_ACCESS", false, false };
    game_feature gameui_show_delivery_paths{ "gameui_show_delivery_paths", "#TR_CONFIG_SHOW_DELIVERY_PATHS", false, false };
    game_feature gameui_flat_buildings{ "gameui_flat_buildings", "#TR_CONFIG_FLAT_BUILDINGS", false, false };
    game_feature gameui_show_construction_size{ "gameui_show_construction_size", "#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", false, false };
    game_feature gameui_show_current_select_tile{ "gameui_show_current_select_tile", "#TR_CONFIG_SHOW_CURRENT_SELECT_TILE", false, false };
    game_feature gameui_show_input_near_cursor{ "gameui_show_input_near_cursor", "#TR_CONFIG_SHOW_INPUT_NEAR_CURSOR", false, false };
    game_feature gameui_road_preview_in_map_order{ "gameui_road_preview_in_map_order", "#TR_CONFIG_ROAD_PREVIEW_IN_MAP_ORDER", false, false };
    game_feature gameui_zoom{ "gameui_zoom", "#TR_CONFIG_ZOOM_STEPPED", false, false };
    game_feature gameui_smooth_zoom{ "gameui_smooth_zoom", "#TR_CONFIG_SMOOTH_ZOOM", false, false };
    game_feature gameui_complete_ratings_columns{ "gameui_complete_ratings_columns", "#TR_CONFIG_COMPLETE_RATING_COLUMNS", false, false };
    game_feature gameui_highlight_legions{ "gameui_highlight_legions", "#TR_CONFIG_HIGHLIGHT_LEGIONS", false, false };
    game_feature gameui_rotate_manually{ "gameui_rotate_manually", "#TR_CONFIG_ROTATE_MANUALLY", false, false };
    game_feature gameplay_change_grandfestival{ "gameplay_change_grandfestival", "#TR_CONFIG_GRANDFESTIVAL", false, false };
    game_feature gameplay_change_hasanimals{ "gameplay_change_has_animals", "#TR_CONFIG_CITY_HAS_ANIMALS", false, false };
    game_feature gameplay_change_jealous_gods{ "gameplay_change_jealous_gods", "#TR_CONFIG_JEALOUS_GODS", false, false };
    game_feature gameplay_change_global_labour{ "gameplay_change_global_labour", "#TR_CONFIG_GLOBAL_LABOUR", false, false };
    game_feature gameplay_change_school_walkers{ "gameplay_change_school_walkers", "#TR_CONFIG_SCHOOL_WALKERS", false, false };
    game_feature gameplay_change_retire_at_60{ "gameplay_change_retire_at_60", "#TR_CONFIG_RETIRE_AT_60", false, false };
    game_feature gameplay_change_fixed_workers{ "gameplay_change_fixed_workers", "#TR_CONFIG_FIXED_WORKERS", false, false };
    game_feature gameplay_fixed_worker_percent{ "gameplay_fixed_worker_percent", "", 38.0f, 38.0f };
    game_feature gameplay_enable_extra_forts{ "gameplay_enable_extra_forts", "#TR_CONFIG_EXTRA_FORTS", false, false };
    game_feature gameplay_hyenas_block{ "gameplay_hyenas_block", "#TR_CONFIG_WOLVES_BLOCK", false, false };
    game_feature gameplay_dynamic_granaries{ "gameplay_dynamic_granaries", "#TR_CONFIG_DYNAMIC_GRANARIES", false, false };
    game_feature gameplay_houses_stockpile_more{ "gameplay_houses_stockpile_more", "#TR_CONFIG_MORE_STOCKPILE", false, false };
    game_feature gameplay_buyers_dont_distribute{ "gameplay_buyers_dont_distribute", "#TR_CONFIG_NO_BUYER_DISTRIBUTION", false, false };
    game_feature gameplay_change_immediate_delete{ "gameplay_change_immediate_delete", "#TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS", false, false };
    game_feature gameplay_change_getting_granaries_go_offroad{ "gameplay_change_getting_granaries_go_offroad", "#TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD", false, false };
    game_feature gameplay_change_granaries_get_double{ "gameplay_change_granaries_get_double", "#TR_CONFIG_GRANARIES_GET_DOUBLE", false, false };
    game_feature gameplay_change_dock_double_haul{ "gameplay_change_dock_double_haul", "#TR_CONFIG_DOCK_DOUBLE_HAUL", false, false };
    game_feature gameplay_change_bazaar_multi_buyers{ "gameplay_change_bazaar_multi_buyers", "#TR_CONFIG_BAZAAR_MULTI_BUYERS", false, false };
    game_feature gameplay_change_tower_sentries_go_offroad{ "gameplay_change_tower_sentries_go_offroad", "#TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD", false, false };
    game_feature gameplay_change_farms_deliver_close{ "gameplay_change_farms_deliver_close", "#TR_CONFIG_FARMS_DELIVER_CLOSE", false, false };
    game_feature gameplay_change_only_deliver_to_accepting_granaries{ "gameplay_change_only_deliver_to_accepting_granaries", "#TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES", false, false };
    game_feature gameplay_change_all_houses_merge{ "gameplay_change_all_houses_merge", "#TR_CONFIG_ALL_HOUSES_MERGE", false, false };
    game_feature gameplay_change_beer_open_trade_route_counts{ "gameplay_change_beer_open_trade_route_counts", "#TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE", false, false };
    game_feature gameplay_change_random_mine_or_pit_collapses_take_money{ "gameplay_change_random_mine_or_pit_collapses_take_money", "#TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY", false, false };
    game_feature gameplay_change_multiple_barracks{ "gameplay_change_multiple_barracks", "#TR_CONFIG_MULTIPLE_BARRACKS", false, false };
    game_feature gameplay_change_warehouses_dont_accept{ "gameplay_change_warehouses_dont_accept", "#TR_CONFIG_NOT_ACCEPTING_WAREHOUSES", false, false };
    game_feature gameplay_change_houses_dont_expand_into_gardens{ "gameplay_change_houses_dont_expand_into_gardens", "#TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS", false, false };
    game_feature gameplay_fix_irrigation_range{ "gameplay_fix_irrigation_range", "#TR_CONFIG_FIX_IRRIGATION_RANGE", false, false };
    game_feature gameplay_fix_farm_produce_quantity{ "gameplay_fix_farm_produce_quantity", "#TR_CONFIG_FIX_FARM_PRODUCING", false, false };
    game_feature gameui_keep_camera_inertia{ "gameui_keep_camera_inertia", "#TR_CONFIG_CAMERA_KEEP_INERTIA", false, false };
    game_feature gameplay_change_understaffed_accept_goods{ "gameplay_change_understaffed_accept_goods", "#TR_CONFIG_UNDERSTAFFED_ACCEPT_GOODS", false, false };
    game_feature gameplay_change_multiple_temple_complexes{ "gameplay_change_multiple_temple_complexes", "#TR_CONFIG_MULTIPLE_TEMPLE_COMPLEXES", false, false };
    game_feature gameplay_change_multiple_monuments{ "gameplay_change_multiple_monuments", "#TR_CONFIG_MULTIPLE_MONUMENTS", false, false };
    game_feature gameplay_change_soil_depletion{ "gameplay_change_soil_depletion", "#TR_CONFIG_SOIL_DEPLETION", false, false };
    game_feature gameplay_change_multiple_gatherers{ "gameplay_change_multiple_gatherers", "#TR_CONFIG_MULTIPLE_GATHERERS", false, false };
    game_feature gameplay_change_fireman_returning{ "gameplay_change_fireman_returning", "#TR_CONFIG_FIREMAN_RETURNING", false, false };
    game_feature gameplay_change_architect_patrol_most_damaged{ "gameplay_change_architect_patrol_most_damaged", "#TR_CONFIG_ARCHITECT_PATROL_MOST_DAMAGED", false, false };
    game_feature gameui_draw_fps{ "gameui_draw_fps", "#TR_CONFIG_DRAW_FPS", false, false };
    game_feature gameplay_change_cart_speed_depends_quntity{ "gameplay_change_cart_speed_depends_quntity", "#TR_CONFIG_CART_SPEED_DEPENDS_QUANTITY", false, false };
    game_feature gameplay_change_citizen_road_offset{ "gameplay_change_citizen_road_offset", "#TR_CONFIG_CH_CITIZEN_ROAD_OFFSET", false, false };
    game_feature gameplay_change_work_camp_one_worker_per_month{ "gameplay_change_work_camp_one_worker_per_month", "#TR_CONFIG_CH_WORK_CAMP_ONE_WORKER_PER_MONTH", false, false };
    game_feature gameplay_change_fire_risk_clay_pit_reduced{ "gameplay_change_fire_risk_clay_pit_reduced", "#TR_CONFIG_CH_CLAY_PIT_FIRE_RISK_REDUCED", false, false };
    game_feature gameplay_change_goldmine_twice_production{ "gameplay_change_goldmine_twice_production", "#TR_CONFIG_GOLDMINE_TWICE_PRODUCTION", false, false };
    game_feature gameplay_change_new_tax_collection_system{ "gameplay_change_new_tax_collection_system", "#TR_CONFIG_NEW_TAX_COLLECTION_SYSTEM", false, false };
    game_feature gameplay_change_small_hut_not_create_emigrant{ "gameplay_change_small_hut_not_create_emigrant", "#TR_CONFIG_SMALL_HUT_NOT_CREATE_EMIGRANT", false, false };
    game_feature gameplay_change_delivery_boy_goes_to_market_alone{ "gameplay_change_delivery_boy_goes_to_market_alone", "#TR_CONFIG_DELIVERY_BOY_GOES_TO_MARKET_ALONE", false, false };
    game_feature gameplay_change_religion_coverage_influence_sentiment{ "gameplay_change_religion_coverage_influence_sentiment", "#TR_CONFIG_RELIGION_COVERAGE_INFLUENCE_SENTIMENT", false, false };
    game_feature gameplay_change_monuments_influence_sentiment{ "gameplay_change_monuments_influence_sentiment", "#TR_CONFIG_MONUMENTS_INFLUENCE_SENTIMENT", false, false };
    game_feature gameplay_change_well_radius_depends_moisture{ "gameplay_change_well_radius_depends_moisture", "#TR_CONFIG_WELL_RADIUS_DEPENDS_MOISTURE", false, false };
    game_feature gameplay_change_enter_point_on_nearest_tile{ "gameplay_change_enter_point_on_nearest_tile", "#TR_CONFIG_ENTER_POINT_ON_NEAREST_TILE", false, false };
    game_feature gameplay_fishing_wharf_spawn_boats{ "gameplay_fishing_wharf_spawn_boats", "#TR_CONFIG_FISHING_WHARF_SPAWN_BOATS", false, false };
    game_feature gameplay_city_flotsam_enabled{ "gameplay_city_flotsam_enabled", "#TR_CONFIG_CITY_FLOTSAM_ENABLED", false, false };
    game_feature gameplay_copper_mine_can_build_near_mountains{ "gameplay_copper_mine_can_build_near_mountains", "#TR_CONFIG_COPPER_NEAR_MOUNTAINS", false, false };
    game_feature gameplay_recruiter_not_need_forts{ "gameplay_recruiter_not_need_forts", "#TR_CONFIG_RECRUITER_NOT_NEED_FORTS", false, false };
    game_feature gameui_highlight_top_menu_hover{ "gameui_highlight_top_menu_hover", "#TR_CONFIG_HIGHLIGHT_TOP_MENU_HOVER", false, false };
    game_feature gameui_empire_city_old_names{ "gameui_empire_city_old_names", "#TR_CONFIG_EMPIRE_CITY_OLD_NAMES", false, false };
    game_feature gameplay_draw_cloud_shadows{ "gameplay_draw_cloud_shadows", "#TR_CONFIG_DRAW_CLOUD_SHADOWS", false, false };
    game_feature gameplay_building_road_closest{ "gameplay_building_road_closest", "#TR_CONFIG_BUILDING_CLOSEST_ROAD", false, false };
    game_feature gameplay_floodplain_random_grow{ "gameplay_floodplain_random_grow", "#TR_CONFIG_FLOODPLAIN_RANDOM_GROW", false, false };
    game_feature gameui_hide_new_game_top_menu{ "gameui_hide_new_game_top_menu", "#TR_CONFIG_HIDE_NEW_GAME_TOP_MENU", false, false };
    game_feature gameplay_save_year_kingdome_rating{ "gameplay_save_year_kingdome_rating", "#TR_CONFIG_SAVE_YEAR_KINGDOME_RATING", false, false };
    game_feature gameopt_last_player{ "gameopt_last_player", "", "", "" };
    game_feature gameopt_language { "gameopt_language", "", "", "" };
    game_feature gameopt_last_save_filename{ "gameopt_last_save_filename", "", "", "" };
    game_feature gameopt_enabled_mods{ "gameopt_enabled_mods", "", "", "" };
    game_feature gameopt_last_game_version{ "gameopt_last_game_version", "", "", "" };
    game_feature gameopt_scroll_speed{ "gameopt_scroll_speed", "", 70.0f, 70.0f };
    game_feature gameopt_middle_mouse_camera_pan{ "gameopt_middle_mouse_camera_pan", "", true, true };
    game_feature gameopt_middle_mouse_pan_speed{ "gameopt_middle_mouse_pan_speed", "", 100.0f, 100.0f };
    game_feature gameopt_clouds_speed{ "gameopt_clouds_speed", "", 30.0f, 30.0f };
    game_feature gameopt_game_speed{ "gameopt_game_speed", "", 80.0f, 80.0f };
    game_feature gameopt_sound_effects_enabled{ "gameopt_sound_effects_enabled", "", true, true };
    game_feature gameopt_sound_effects_volume{ "gameopt_sound_effects_volume", "", 80.0f, 80.0f };
    game_feature gameopt_sound_music_enabled{ "gameopt_sound_music_enabled", "", true, true };
    game_feature gameopt_sound_music_volume{ "gameopt_sound_music_volume", "", 80.0f, 80.0f };
    game_feature gameopt_sound_speech_enabled{ "gameopt_sound_speech_enabled", "", true, true };
    game_feature gameopt_sound_speech_volume{ "gameopt_sound_speech_volume", "", 100.0f, 100.0f };
    game_feature gameopt_sound_city_enabled{ "gameopt_sound_city_enabled", "", true, true };
    game_feature gameopt_sound_city_volume{ "gameopt_sound_city_volume", "", 100.0f, 100.0f };
    game_feature gameplay_brewery_requires_water{ "gameplay_brewery_requires_water", "#TR_CONFIG_BREWERY_REQUIRES_WATER", false, false };
    game_feature gameplay_conservatory_helps_dance_school{ "gameplay_conservatory_helps_dance_school", "#TR_CONFIG_CONSERVATORY_HELPS_DANCE_SCHOOL", false, false };
    game_feature gameplay_jewels_workshops_culture_bonus{ "gameplay_jewels_workshops_culture_bonus", "#TR_CONFIG_JEWELS_WORKSHOPS_CULTURE_BONUS", false, false };
    game_feature gameui_overlay_show_gray_buildings{ "gameui_overlay_show_gray_buildings", "#TR_CONFIG_OVERLAY_SHOW_GRAY_BUILDINGS", false, false };
    game_feature gameplay_prevent_delete_near_burning_ruins{ "gameplay_prevent_delete_near_burning_ruins", "#TR_CONFIG_PREVENT_DELETE_NEAR_BURNING_RUINS", false, false };
    game_feature gameplay_change_cartpushers_yield_by_id{ "gameplay_change_cartpushers_yield_by_id", "#TR_CONFIG_CARTPUSHERS_YIELD_BY_ID", false, false };
    game_feature gameplay_rebalance_workshop_output{ "gameplay_rebalance_workshop_output", "#TR_CONFIG_REBALANCE_WORKSHOP_OUTPUT", false, false };
    game_feature gameopt_monthly_autosave{ "gameopt_monthly_autosave", "", true, true };
    game_feature gameopt_ironwill{ "gameopt_ironwill", "#TR_CONFIG_IRONWILL", false, false };
    game_feature gameopt_unlock_all_campaigns{ "gameopt_unlock_all_campaigns", "#TR_CONFIG_UNLOCK_ALL_CAMPAIGNS", false, false };
    game_feature gameopt_autosave_slots{ "gameopt_autosave_slots", "", 1.0f, 1.0f };
    game_feature gameopt_tooltips_mode{ "gameopt_tooltips_mode", "", 2.0f, 2.0f };
    game_feature gameopt_warnings{ "gameopt_warnings", "", true, true };
    game_feature gameopt_popup_messages{ "gameopt_popup_messages", "", 0.0f, 0.0f };
    game_feature gameopt_gods_enabled{ "gameopt_gods_enabled", "", true, true };
    game_feature gameopt_victory_video{ "gameopt_victory_video", "", false, false };
    game_feature gameopt_pyramid_speedup{ "gameopt_pyramid_speedup", "", false, false };
    game_feature gameopt_fullscreen{ "gameopt_fullscreen", "", true, true };
    game_feature gameopt_difficulty{ "gameopt_difficulty", "", 2.0f, 2.0f };
    game_feature gameopt_display_size{"gameopt_display_size", "", vec2i(1280, 800), vec2i(1280, 800)};
    game_feature gameopt_disable_victory{ "gameopt_disable_victory", "", false, false };
    game_feature gameopt_player_name{"gameopt_player_name", "", "", ""};
    game_feature gameplay_change_empire_map_runs_simulation{ "gameplay_change_empire_map_runs_simulation", "#TR_CONFIG_EMPIRE_MAP_RUNS_SIMULATION", false, false };
    game_feature gameui_disable_nilometer_popups{ "gameui_disable_nilometer_popups", "#TR_CONFIG_DISABLE_NILOMETER_POPUPS", false, false };
    game_feature gameui_enhanced_nilometer{ "gameui_enhanced_nilometer", "#TR_CONFIG_ENHANCED_NILOMETER", false, false };
    game_feature gameui_building_mothball_button{ "gameui_building_mothball_button", "#TR_CONFIG_BUILDING_MOTHBALL_BUTTON", false, false };
    game_feature gameui_enhanced_shrine_info{ "gameui_enhanced_shrine_info", "#TR_CONFIG_ENHANCED_SHRINE_INFO", false, false };
    game_feature gameui_prompt_save_on_exit{ "gameui_prompt_save_on_exit", "#TR_CONFIG_PROMPT_SAVE_ON_EXIT", false, false };
    game_feature gameplay_pause_sim_while_building{ "gameplay_pause_sim_while_building", "#TR_CONFIG_PAUSE_SIM_WHILE_BUILDING", false, false };
    game_feature gameplay_change_disaster_events_use_amount{ "gameplay_change_disaster_events_use_amount", "#TR_CONFIG_DISASTER_EVENTS_USE_AMOUNT", false, false };
    game_feature gameplay_change_trader_capacity_1600{ "gameplay_change_trader_capacity_1600", "#TR_CONFIG_TRADER_CAPACITY_1600", false, false };
    game_feature gameplay_change_trader_per_good_1600{ "gameplay_change_trader_per_good_1600", "#TR_CONFIG_TRADER_PER_GOOD_1600", false, false };
    game_feature gameplay_bast_lion_raid{ "gameplay_bast_lion_raid", "#TR_CONFIG_BAST_LION_RAID", false, false };
    game_feature gameplay_seth_asp_raid{ "gameplay_seth_asp_raid", "#TR_CONFIG_SETH_ASP_RAID", false, false };
    game_feature gameplay_ptah_scorpion_raid{ "gameplay_ptah_scorpion_raid", "#TR_CONFIG_PTAH_SCORPION_RAID", false, false };
    game_feature gameplay_enhanced_auto_resolve_invasions{ "gameplay_enhanced_auto_resolve_invasions", "#TR_CONFIG_AUTO_RESOLVE_INVASIONS", false, false };
    game_feature gameplay_enhanced_invasion_bribe{ "gameplay_enhanced_invasion_bribe", "#TR_CONFIG_INVASION_BRIBE", false, false };
    game_feature gameplay_enhanced_flood_basins{ "gameplay_enhanced_flood_basins", "#TR_CONFIG_FLOOD_BASINS", false, false };
    game_feature gameplay_enhanced_historical_economy{ "gameplay_enhanced_historical_economy", "#TR_CONFIG_HISTORICAL_ECONOMY", false, false };
    game_feature gameplay_enhanced_food_mill{ "gameplay_enhanced_food_mill", "#TR_CONFIG_FOOD_MILL", false, false };
    game_feature gameplay_enhanced_industry_office{ "gameplay_enhanced_industry_office", "#TR_CONFIG_INDUSTRY_OFFICE", false, false };
    game_feature gameplay_enhanced_labor_category_split{ "gameplay_enhanced_labor_category_split", "#TR_CONFIG_LABOR_CATEGORY_SPLIT", false, false };
    game_feature gameplay_enhanced_walker_spawn_boost{ "gameplay_enhanced_walker_spawn_boost", "#TR_CONFIG_WALKER_SPAWN_BOOST", false, false };
    game_feature gameplay_enhanced_walker_move_boost{ "gameplay_enhanced_walker_move_boost", "#TR_CONFIG_WALKER_MOVE_BOOST", false, false };
    game_feature gameplay_enhanced_festival_calendar{ "gameplay_enhanced_festival_calendar", "#TR_CONFIG_FESTIVAL_CALENDAR", false, false };
    game_feature gameplay_enhanced_local_cults{ "gameplay_enhanced_local_cults", "#TR_CONFIG_LOCAL_CULTS", false, false };
    game_feature graphics_atlas_render{ "graphics_atlas_render", "", true, true };
    game_feature graphics_atlas_max_sprite_width{ "graphics_atlas_max_sprite_width", "", 512.0f, 512.0f };
    game_feature graphics_atlas_page_size{ "graphics_atlas_page_size", "", 8192.0f, 8192.0f };

    xspan<game_feature*> all() {
        return { _features.data(), _features.size() };
    }

    game_feature *find(const xstring &name) {
        for (auto &feature : _features) {
            if (feature->name == name) {
                return feature;
            }
        }
        return nullptr;
    }

    bool is_toggleable(const game_feature &feature) {
        return feature.type() == setting_bool && !feature.text.empty();
    }

    void apply_og_profile() {
        for (auto *feature : _features) {
            if (!is_toggleable(*feature)) {
                continue;
            }
            if (std::holds_alternative<bool>(feature->ogv)) {
                feature->set(std::get<bool>(feature->ogv));
            }
        }
        logs::info("Applied OG game-features profile (original Pharaoh behavior)");
    }

    void apply_enhanced_profile() {
        for (auto *feature : _features) {
            if (!is_toggleable(*feature)) {
                continue;
            }
            feature->set(true);
        }
        logs::info("Applied Enhanced game-features profile (all toggleable features on)");
    }
}

game_features::game_feature::game_feature(const xstring &n, const xstring &t, setting_variant def, setting_variant og)
    : name(n), text(t), defaultv(def), ogv(og) {
    _features.push_back(this);
    _settings.set(name, defaultv);
}

bool game_features::game_feature::to_bool() const {
    return _settings.get_bool(name);
}

xstring game_features::game_feature::to_string() const {
    return _settings.get_string(name);
}

float game_features::game_feature::to_float() const {
    return _settings.get_float(name);
}

int game_features::game_feature::to_int() const {
    return _settings.get_int(name);
}

vec2i game_features::game_feature::to_vec2i() const {
    const setting_variant v = _settings.get(name, defaultv);
    if (std::holds_alternative<vec2i>(v)) {
        return std::get<vec2i>(v);
    }
    if (std::holds_alternative<vec2i>(defaultv)) {
        return std::get<vec2i>(defaultv);
    }
    return {};
}

void game_features::game_feature::set(bool value) {
    _settings.set_bool(name, value);
}

void game_features::game_feature::set(int value) {
    _settings.set_int(name, value);
}


void game_features::game_feature::set(float value) {
    _settings.set_float(name, value);
}

void game_features::game_feature::set(const xstring &value) {
    _settings.set_string(name, value);
}

void game_features::game_feature::set(pcstr value) {
    _settings.set_string(name, value);
}

void game_features::game_feature::set(vec2i value) {
    _settings.set(name, setting_variant(value));
}

setting_variant_type game_features::game_feature::type() const {
    return _settings.type(name);
}

void game_features::load() {
    _settings.load_global("game_settings");
}

void game_features::apply_cli_profiles(e_features_profile profile) {
    switch (profile) {
    case features_profile_enhanced:
        apply_enhanced_profile();
        break;
    case features_profile_og:
        apply_og_profile();
        break;
    case features_profile_default:
    default:
        break;
    }
}

void game_features::load(e_features_profile profile, const cli_overrides_t &overrides) {
    load();
    apply_cli_profiles(profile);
    apply_cli_overrides(overrides);
}

void game_features::save() {
    vfs::sync_em_fs();
    _settings.sync_global(CONF_FILENAME, "game_settings");
}

globals_settings_t &game_features::settings() {
    return _settings;
}

static bool parse_bool_setting_value(pcstr value) {
    if (SDL_strcasecmp(value, "true") == 0 || SDL_strcasecmp(value, "1") == 0 || SDL_strcasecmp(value, "yes") == 0
        || SDL_strcasecmp(value, "on") == 0) {
        return true;
    }
    if (SDL_strcasecmp(value, "false") == 0 || SDL_strcasecmp(value, "0") == 0 || SDL_strcasecmp(value, "no") == 0
        || SDL_strcasecmp(value, "off") == 0) {
        return false;
    }

    logs::warn("Invalid bool value '%s' for game feature, using false", value);
    return false;
}

static vec2i parse_vec2i_setting_value(pcstr value) {
    vec2i result;
    if (SDL_sscanf(value, "%dx%d", &result.x, &result.y) == 2) {
        return result;
    }
    if (SDL_sscanf(value, "%d,%d", &result.x, &result.y) == 2) {
        return result;
    }

    logs::warn("Invalid vec2i value '%s' for game feature, expected WxH or x,y", value);
    return {};
}

void game_features::apply_cli_overrides(const cli_overrides_t &overrides) {
    for (const auto& override_entry : overrides) {
        game_feature* feature = find(override_entry.first);
        if (!feature) {
            logs::warn("Unknown game feature from CLI: %s", override_entry.first.c_str());
            continue;
        }

        pcstr value = override_entry.second.c_str();
        switch (feature->type()) {
        case setting_bool:
            feature->set(parse_bool_setting_value(value));
            logs::info("CLI game feature override: %s = %s", override_entry.first.c_str(), value);
            break;

        case setting_float:
            feature->set((float)SDL_atof(value));
            logs::info("CLI game feature override: %s = %s", override_entry.first.c_str(), value);
            break;

        case setting_string:
            feature->set(value);
            logs::info("CLI game feature override: %s = %s", override_entry.first.c_str(), value);
            break;

        case setting_vec2i: {
            const vec2i parsed = parse_vec2i_setting_value(value);
            feature->set(parsed);
            logs::info("CLI game feature override: %s = %dx%d", override_entry.first.c_str(), parsed.x, parsed.y);
            break;
        }

        default:
            logs::warn("Unsupported game feature type for CLI override: %s", override_entry.first.c_str());
            break;
        }
    }
}

declare_console_command_p(savefeatures) {
    for (auto &feature : game_features::_features) {
        switch (feature->type()) {
        case setting_bool:
            {
                const bool old = feature->to_bool();
                feature->set(!old);
                feature->set(old);
            }
            break;

        case setting_string:
            {
                const xstring old = feature->to_string();
                feature->set(!!old ? "_" : "!");
                feature->set(old);
            }
            break;
        }
    }
    game_features::save();
}
