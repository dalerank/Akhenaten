#include "game_config.h"

#include "content/vfs.h"
#include "core/log.h"
#include "core/svector.h"
#include "js/js_game.h"

static const char* INI_FILENAME = "akhenaten.ini";
static const char* CONF_FILENAME = "akhenaten.conf";
ankh_config_t g_ankh_config;

ANK_REGISTER_CONFIG_ITERATOR(config_load_game_settings);
void config_load_game_settings() {
    g_ankh_config.load();
}

// Keep this in the same order as the ints in config.h
struct enhanced_option_t {
    const char* name;
    const bool enabled;
};

namespace game_features {
    svector<game_feature*, 64> _features;

    game_feature gameplay_fix_immigration{ "gameplay_fix_immigration", false };
    game_feature gameplay_fix_100y_ghosts{ "gameplay_fix_100y_ghosts", true };
    game_feature gameplay_fix_editor_events{ "gameplay_fix_editor_events", true };
    game_feature gameui_sidebar_info{ "gameui_sidebar_info", true };
    game_feature gameui_show_intro_video{ "gameui_show_intro_video", false };
    game_feature gameui_smooth_scrolling{ "gameui_smooth_scrolling", true };
    game_feature gameui_walker_waypoints{ "gameui_walker_waypoints", true };
    game_feature gameui_visual_feedback_on_delete{ "gameui_visual_feedback_on_delete", true };
    game_feature gameui_show_water_structure_range{ "gameui_show_water_structure_range", true };
    game_feature gameui_show_construction_size{ "gameui_show_construction_size", true };
    game_feature gameui_zoom{ "gameui_zoom", true };
    game_feature gameui_complete_ratings_columns{ "gameui_complete_ratings_columns", true };
    game_feature gameui_highlight_legions{ "gameui_highlight_legions", true };
    game_feature gameui_rotate_manually{ "gameui_rotate_manually", true };
    game_feature gameplay_change_grandfestival{ "gameplay_change_grandfestival", true };
    game_feature gameplay_change_jealous_gods{ "gameplay_change_jealous_godsk", true };
    game_feature gameplay_change_global_labour{ "gameplay_change_global_labour", false };
    game_feature gameplay_change_school_walkers{ "gameplay_change_school_walkers", false };
    game_feature gameplay_change_retire_at_60{ "gameplay_change_retire_at_60", true };
    game_feature gameplay_change_fixed_workers{ "gameplay_change_fixed_workers", false };
    game_feature gameplay_enable_extra_forts{ "gameplay_enable_extra_forts", false };
    game_feature gameplay_hyenas_block{ "gameplay_hyenas_block", false };
    game_feature gameplay_dynamic_granaries{ "gameplay_dynamic_granaries", false };
    game_feature gameplay_houses_stockpile_more{ "gameplay_houses_stockpile_more", false };
    game_feature gameplay_buyers_dont_distribute{ "gameplay_buyers_dont_distribute", true };
    game_feature gameplay_change_immediate_delete{ "gameplay_change_immediate_delete", false };
    game_feature gameplay_change_getting_granaries_go_offroad{ "gameplay_change_getting_granaries_go_offroad", false };
    game_feature gameplay_change_granaries_get_double{ "gameplay_change_granaries_get_double", false };
    game_feature gameplay_change_tower_sentries_go_offroad{ "gameplay_change_tower_sentries_go_offroad", false };
    game_feature gameplay_change_farms_deliver_close{ "gameplay_change_farms_deliver_close", false };
    game_feature gameplay_change_only_deliver_to_accepting_granaries{ "gameplay_change_only_deliver_to_accepting_granaries", false };
    game_feature gameplay_change_all_houses_merge{ "gameplay_change_all_houses_merge", false };
    game_feature gameplay_change_beer_open_trade_route_counts{ "gameplay_change_beer_open_trade_route_counts", false };
    game_feature gameplay_change_random_mine_or_pit_collapses_take_money{ "gameplay_change_random_mine_or_pit_collapses_take_money", true };
    game_feature gameplay_change_multiple_barracks{ "gameplay_change_multiple_barracks", false };
    game_feature gameplay_change_warehouses_dont_accept{ "gameplay_change_warehouses_dont_accept", false };
    game_feature gameplay_change_houses_dont_expand_into_gardens{ "gameplay_change_houses_dont_expand_into_gardens", false };
    game_feature gameplay_fix_irrigation_range{ "gameplay_fix_irrigation_range", true };
    game_feature gameplay_fix_farm_produce_quantity{ "gameplay_fix_farm_produce_quantity", true };
    game_feature gameui_keep_camera_inertia{ "gameui_keep_camera_inertia", true };
    game_feature gameplay_change_understaffed_accept_goods{ "gameplay_change_understaffed_accept_goods", false };
    game_feature gameplay_change_multiple_temple_complexes{ "gameplay_change_multiple_temple_complexes", false };
    game_feature gameplay_change_multiple_monuments{ "gameplay_change_multiple_monuments", false };
    game_feature gameplay_change_soil_depletion{ "gameplay_change_soil_depletion", true };
    game_feature gameplay_change_multiple_gatherers{ "gameplay_change_multiple_gatherers", false };
    game_feature gameplay_change_fireman_returning{ "gameplay_change_fireman_returning", true };
    game_feature gameui_draw_fps{ "gameui_draw_fps", true };
    game_feature gameplay_change_cart_speed_depends_quntity{ "gameplay_change_cart_speed_depends_quntity", true };
    game_feature gameplay_change_citizen_road_offset{ "gameplay_change_citizen_road_offset", true };
    game_feature gameplay_change_work_camp_one_worker_per_month{ "gameplay_change_work_camp_one_worker_per_month", true };
    game_feature gameplay_change_fire_risk_clay_pit_reduced{ "gameplay_change_fire_risk_clay_pit_reduced", true };
    game_feature gameplay_change_goldmine_twice_production{ "gameplay_change_goldmine_twice_production", true };
    game_feature gameplay_change_new_tax_collection_system{ "gameplay_change_new_tax_collection_system", false };
    game_feature gameplay_change_small_hut_not_create_emigrant{ "gameplay_change_small_hut_not_create_emigrant", true };
    game_feature gameplay_change_delivery_boy_goes_to_market_alone{ "gameplay_change_delivery_boy_goes_to_market_alone", true };
    game_feature gameplay_change_religion_coverage_influence_sentiment{ "gameplay_change_religion_coverage_influence_sentiment", true };
    game_feature gameplay_change_monuments_influence_sentiment{ "gameplay_change_monuments_influence_sentiment", true };
    game_feature gameplay_change_well_radius_depends_moisture{ "gameplay_change_well_radius_depends_moisture", true };
    game_feature gameplay_change_enter_point_on_nearest_tile{ "gameplay_change_enter_point_on_nearest_tile", true };

    custom_span<game_feature*> features() {
        return { _features.data(), _features.size() };
    }
}

game_features::game_feature::game_feature(const xstring &n, setting_variant def) : name(n), defaultv(def) {
    _features.push_back(this);
    g_ankh_config.settings.set(name, defaultv);
}

bool game_features::game_feature::to_bool() const {
    return g_ankh_config.settings.get_bool(name);
}

void game_features::game_feature::set(bool value) {
    g_ankh_config.settings.set_bool(name, value);
}

enhanced_option_t ini_keys_defaults[CONFIG_MAX_ENTRIES] = {
    {"reserved_0", false},
    {"reserved_1", true},
    {"reserved_2", true},
    {"reserved_3", true},
    {"reserved_4", false},
    {"reserved_5", true},
    {"reserved_6", false},
    {"reserved_7", true},
    {"reserved_8", true},
    {"reserved_9", true},
    {"reserved_10", true},
    {"reserved_11", false},
    {"reserved_12", true},
    {"reserved_13", false},
    {"reserved_14", false},
    {"reserved_15", false},
    {"reserved_16", false},
    {"reserved_17", false},
    {"reserved_18", false},
    {"reserved_19", false},
    {"reserved_20", false},
    {"reserved_21", false},
    {"reserved_22", false},
    {"reserved_23", false},
    {"reserved_24", true},
    {"reserved_25", false},
    {"reserved_26", false},
    {"reserved_27", false},
    {"reserved_28", false},
    {"reserved_29", false},
    {"reserved_30", false},
    {"reserved_31", false},
    {"reserved_32", false},
    {"reserved_33", false},
    {"reserved_34", false},
    {"reserved_35", false},
    {"reserved_36", false},
    ///
    {"reserved_37", true},
    {"reserved_38", true},
    {"reserved_39", true},
    {"reserved_40", true},
    {"reserved_41", false},
    {"reserved_42", false},
    {"reserved_43", false},
    {"reserved_44", false},
    {"reserved_45", true},
    {"reserved_46", false},
    {"reserved_47", true},
    {"reserved_48", true},
    {"reserved_49", true},
    {"reserved_50", true},
    {"reserved_51", true},
    {"reserved_52", true},
    {"reserved_53", true},
    {"reserved_54", true},
    {"reserved_55", false},
    {"reserved_56", true},
    {"reserved_57", true},
    {"reserved_58", true},
    {"reserved_59", true},
    {"reserved_60", true},
    {"reserved_61", true},
    ///
    {"reserved_62", false},
    {"reserved_63", false},
    {"reserved_64", false},
    {"reserved_65", false},
    {"reserved_66", false},
    ///
    {"city_building_wood_cutters", true},
    {"city_produce_timber", true},
    {"city_produce_chickpeas", true},
    {"city_produce_pomegranades", true},
    {"city_produce_lettuce", true},
    {"city_building_copper_mine", true},
    {"city_produce_copper", true},

    {"city_building_copper_reed_gatherer", true},
    {"city_building_copper_papyrus_maker", true},
    {"city_building_copper_scribal_school", true},
    {"city_produce_reed", true},
    {"city_produce_papyrus", true},

    {"city_building_shipyard", true},
    {"city_building_fishing_wharf", true},
    {"city_produce_fish", true},
    {"fishing_wharf_spawn_boats", false},
    {"city_flotsam_enabled", false},
    {"chickpeas_farm_enabled", true},
    {"lettuce_farm_enabled", true},
    {"pomegranates_farm_enabled", true},
    {"figs_farm_enabled", true},
    {"city_produce_figs", true},
    {"grain_farm_enabled", true},
    {"city_produce_grain", true},
    {"cattle_ranch_enabled", true},
    {"city_produce_meat", true},
    {"bricks_workshop_enabled", true},
    {"city_produce_bricks", true},
    {"city_produce_clay", true},
    {"city_building_work_camp", true},
    {"city_building_gold_mine", true},
    {"city_building_quarry_sandstone", true},
    {"city_building_quarry_granite", true},
    {"city_building_quarry_stone", true},
    {"city_building_quarry_limestone", true},
    {"city_building_claypit", true},
    {"city_building_weapon_workshop", true},
    {"copper_mine_can_build_near_mountains", false},
    {"city_building_recruter", false},
    {"recruiter_not_need_forts", false},
    {"ui_highlight_top_menu_hover", true},
    {"ui_empire_city_old_names", true},
    {"ui_draw_cloud_shadows", false},
    {"city_building_smal_mastaba", true},
    {"city_building_bricklayes", true},
    {"city_building_road_closest", true},
    {"floodplain_random_grow", true},
    {"city_building_booth", true},
    {"city_building_bandstand", true},
    {"ui_hide_new_game_top_menu", true},
    {"city_save_year_kingdome_rating", false},
    {"city_building_mastaba", true },
};

static pcstr ini_string_keys[] = {
  "ui_language_dir",
  "last_save_filename",
  "last_player",
  "0",
};

pcstr default_string_values[CONFIG_STRING_MAX_ENTRIES];

int ankh_config_t::get(e_config_key key) {
    return opts[key];
}
void ankh_config_t::set(e_config_key key, int value) {
    opts[key] = value;
}

xstring ankh_config_t::get(e_config_str key) {
    return string_values[key];
}

void ankh_config_t::set(e_config_str key, const xstring value) {
    string_values[key] = value;
}

void ankh_config_t::set(e_config_str key, pcstr value) {
    string_values[key] = value;
}

bool config_get_default_value(e_config_key key) {
    return ini_keys_defaults[key].enabled;
}

const char* config_get_default_string_value(e_config_key key) {
    return default_string_values[key];
}

void ankh_config_t::reset_defaults() {
    for (int i = 0; i < CONFIG_MAX_ENTRIES; ++i) {
        g_ankh_config.opts[i] = ini_keys_defaults[i].enabled;
    }
    string_values[CONFIG_STRING_UI_LANGUAGE_DIR] = default_string_values[CONFIG_STRING_UI_LANGUAGE_DIR];
}

void ankh_config_t::load() {
    reset_defaults();
    vfs::path fs_file = vfs::content_path(INI_FILENAME);

    vfs::reader fp = vfs::file_open(fs_file);
    if (!fp) {
        return;
    }

    bstring128 line_buffer;
    char* line;
    while ((line = fp->readline(line_buffer, line_buffer.capacity))) {
        // Remove newline from string
        size_t size = strlen(line);
        while (size > 0 && (line[size - 1] == '\n' || line[size - 1] == '\r')) {
            line[--size] = 0;
        }
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = 0;
            for (int i = 0; i < CONFIG_MAX_ENTRIES; i++) {
                if (strcmp(ini_keys_defaults[i].name, line) == 0) {
                    int value = atoi(&equals[1]);
                    logs::info("Config key %s [%d]", ini_keys_defaults[i].name, value);
                    g_ankh_config.opts[i] = value;
                    break;
                }
            }
            for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
                if (strcmp(ini_string_keys[i], line) == 0) {
                    pcstr value = &equals[1];
                    logs::info("Config key %s", ini_string_keys[i]);
                    logs::info("Config value %s", value);
                    string_values[i] = value;
                    break;
                }
            }
        }
    }

    settings.init();
}

void ankh_config_t::save() {
    vfs::path fs_file = vfs::content_path(INI_FILENAME);

    FILE* fp = vfs::file_open_os(fs_file, "wt");
    if (!fp) {
        logs::error("Unable to write configuration file %s", INI_FILENAME);
        return;
    }
    for (int i = 0; i < CONFIG_MAX_ENTRIES; i++) {
        fprintf(fp, "%s=%d\n", ini_keys_defaults[i].name, g_ankh_config.opts[i]);
    }

    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
        fprintf(fp, "%s=%s\n", ini_string_keys[i], string_values[i].c_str());
    }
    vfs::file_close(fp);
    vfs::sync_em_fs();

    settings.sync(CONF_FILENAME);
}
