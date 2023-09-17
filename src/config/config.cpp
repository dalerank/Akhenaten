#include "config.h"

#include "content/vfs.h"
#include "core/log.h"

#include <string.h>

#define MAX_LINE 100

static const char* INI_FILENAME = "ozymandias.ini";

// Keep this in the same order as the ints in config.h
struct enhanced_option_t {
    const char* name;
    const bool enabled;
};

enhanced_option_t ini_keys_defaults[CONFIG_MAX_ENTRIES] = {
  {"gameplay_fix_immigration", true},
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

  ///

  {"#god_osiris_disabled", false},
  {"#god_ra_disabled", false},
  {"#god_ptah_disabled", false},
  {"#god_seth_disabled", false},
  {"#god_bast_disabled", false},
};

static const char* ini_string_keys[] = {
  "ui_language_dir",
};

bool g_ozzy_config[CONFIG_MAX_ENTRIES];
static char string_values[CONFIG_STRING_MAX_ENTRIES][CONFIG_STRING_VALUE_MAX];
static char default_string_values[CONFIG_STRING_MAX_ENTRIES][CONFIG_STRING_VALUE_MAX];

int config_get(int key) {
    return g_ozzy_config[key];
}
void config_set(int key, int value) {
    g_ozzy_config[key] = value;
}

const char* config_get_string(int key) {
    return string_values[key];
}
void config_set_string(int key, const char* value) {
    if (!value)
        string_values[key][0] = 0;
    else {
        strncpy(string_values[key], value, CONFIG_STRING_VALUE_MAX - 1);
    }
}
bool config_get_default_value(int key) {
    return ini_keys_defaults[key].enabled;
}
const char* config_get_default_string_value(int key) {
    return default_string_values[key];
}

void config_set_defaults() {
    for (int i = 0; i < CONFIG_MAX_ENTRIES; ++i) {
        g_ozzy_config[i] = ini_keys_defaults[i].enabled;
    }
    strncpy(string_values[CONFIG_STRING_UI_LANGUAGE_DIR],
            default_string_values[CONFIG_STRING_UI_LANGUAGE_DIR],
            CONFIG_STRING_VALUE_MAX);
}
void config_load() {
    config_set_defaults();
    bstring256 fs_file = vfs::dir_get_path(INI_FILENAME);

    FILE* fp = vfs::file_open(fs_file, "rt");
    if (!fp)
        return;
    char line_buffer[MAX_LINE];
    char* line;
    while ((line = fgets(line_buffer, MAX_LINE, fp))) {
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
                    g_ozzy_config[i] = value;
                    break;
                }
            }
            for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
                if (strcmp(ini_string_keys[i], line) == 0) {
                    const char* value = &equals[1];
                    logs::info("Config key %s", ini_string_keys[i]);
                    logs::info("Config value %s", value);
                    strncpy(string_values[i], value, CONFIG_STRING_VALUE_MAX);
                    break;
                }
            }
        }
    }
    vfs::file_close(fp);
}

void config_save() {
    bstring256 fs_file = vfs::dir_get_path(INI_FILENAME);

    FILE* fp = vfs::file_open(fs_file, "wt");
    if (!fp) {
        logs::error("Unable to write configuration file %s", INI_FILENAME);
        return;
    }
    for (int i = 0; i < CONFIG_MAX_ENTRIES; i++) {
        fprintf(fp, "%s=%d\n", ini_keys_defaults[i].name, g_ozzy_config[i]);
    }

    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
        fprintf(fp, "%s=%s\n", ini_string_keys[i], string_values[i]);
    }
    vfs::file_close(fp);
}
