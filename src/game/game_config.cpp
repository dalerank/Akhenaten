#include "game_config.h"

#include "content/vfs.h"
#include "core/log.h"
#include "js/js_game.h"

static const char* INI_FILENAME = "akhenaten.ini";
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

bool game_features::game_feature::to_bool() const {
    return g_ankh_config.settings.get_bool(name());
}

enhanced_option_t ini_keys_defaults[CONFIG_MAX_ENTRIES] = {
    {"gameplay_fix_100y_ghosts", true},
    {"gameplay_fix_editor_events", true},
    {"ui_sidebar_info", true},
    {"ui_show_intro_video", false},
    {"ui_smooth_scrolling", true},
    {"ui_walker_waypoints", false},
    {"ui_visual_feedback_on_delete", true},
    {"ui_show_water_structure_range", true},
    {"ui_show_construction_size", true},
    {"ui_zoom", true},
    {"ui_complete_ratings_columns", false},
    {"ui_highlight_legions", true},
    {"ui_rotate_manually", false},
    {"gameplay_change_grandfestival", false},
    {"gameplay_change_jealous_gods", false},
    {"gameplay_change_global_labour", false},
    {"gameplay_change_school_walkers", false},
    {"gameplay_change_retire_at_60", false},
    {"gameplay_change_fixed_workers", false},
    {"gameplay_enable_extra_forts", false},
    {"gameplay_wolves_block", false},
    {"gameplay_dynamic_granaries", false},
    {"gameplay_houses_stockpile_more", false},
    {"gameplay_buyers_dont_distribute", true},
    {"gameplay_change_immediate_delete", false},
    {"gameplay_change_getting_granaries_go_offroad", false},
    {"gameplay_change_granaries_get_double", false},
    {"gameplay_change_tower_sentries_go_offroad", false},
    {"gameplay_change_farms_deliver_close", false},
    {"gameplay_change_only_deliver_to_accepting_granaries", false},
    {"gameplay_change_all_houses_merge", false},
    {"gameplay_change_wine_open_trade_route_counts", false},
    {"gameplay_change_random_mine_or_pit_collapses_take_money", false},
    {"gameplay_change_multiple_barracks", false},
    {"gameplay_change_warehouses_dont_accept", false},
    {"gameplay_change_houses_dont_expand_into_gardens", false},
    ///
    {"gameplay_fix_irrigation_range", true},
    {"gameplay_fix_farm_produce_quantity", true},
    {"ui_keep_camera_inertia", true},
    {"gameplay_change_watercarriers_firefight", true},
    {"gameplay_change_cart_instant_unload", false},
    {"gameplay_change_understaffed_accept_goods", false},
    {"gameplay_change_multiple_temple_complexes", false},
    {"gameplay_change_multiple_monuments", false},
    {"gameplay_change_soil_depletion", true},
    {"gameplay_change_multiple_gatherers", false},
    {"gameplay_change_fireman_returning", true},
    {"ui_draw_fps", true},
    {"gameplay_change_cart_speed_depends_quntity", true},
    {"gameplay_change_citizen_road_offset", true},
    {"gameplay_change_work_camp_one_worker_per_month", true},
    {"gameplay_change_fire_risk_clay_pit_reduced", true},
    {"gameplay_change_has_animals", true},
    {"gameplay_change_goldmine_twice_production", true},
    {"gameplay_change_new_tax_collection_system", false},
    {"gameplay_change_small_hut_not_create_emigrant", true},
    {"gameplay_change_delivery_boy_goes_to_market_alone", true},
    {"gameplay_change_religion_coverage_influence_sentiment", true},
    {"gameplay_change_monuments_influence_sentiment", true},
    {"gameplay_change_well_radius_depends_moisture", true},
    {"gameplay_change_enter_point_on_nearest_tile", true},
    ///
    {"#god_osiris_disabled", false},
    {"#god_ra_disabled", false},
    {"#god_ptah_disabled", false},
    {"#god_seth_disabled", false},
    {"#god_bast_disabled", false},
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

    settings.sync("akhenaten.conf");
}
