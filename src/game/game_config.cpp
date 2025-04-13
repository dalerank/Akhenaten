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

namespace game_features {
    svector<game_feature*, 128> _features;

    game_feature gameplay_fix_immigration{ "gameplay_fix_immigration", "#TR_CONFIG_FIX_IMMIGRATION_BUG", false };
    game_feature gameplay_fix_100y_ghosts{ "gameplay_fix_100y_ghosts", "#TR_CONFIG_FIX_100_YEAR_GHOSTS", true };
    game_feature gameplay_fix_editor_events{ "gameplay_fix_editor_events", "#TR_CONFIG_FIX_EDITOR_EVENTS", true };
    game_feature gameui_sidebar_info{ "gameui_sidebar_info", "#TR_CONFIG_SIDEBAR_INFO", true };
    game_feature gameui_show_intro_video{ "gameui_show_intro_video", "#TR_CONFIG_SHOW_INTRO_VIDEO", false };
    game_feature gameui_smooth_scrolling{ "gameui_smooth_scrolling", "#TR_CONFIG_SMOOTH_SCROLLING", true };
    game_feature gameui_walker_waypoints{ "gameui_walker_waypoints", "#TR_CONFIG_DRAW_WALKER_WAYPOINTS", true };
    game_feature gameui_visual_feedback_on_delete{ "gameui_visual_feedback_on_delete", "#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", true };
    game_feature gameui_show_water_structure_range{ "gameui_show_water_structure_range", "#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", true };
    game_feature gameui_show_construction_size{ "gameui_show_construction_size", "#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", true };
    game_feature gameui_zoom{ "gameui_zoom", "#TR_CONFIG_ZOOM_STEPPED", true };
    game_feature gameui_complete_ratings_columns{ "gameui_complete_ratings_columns", "#TR_CONFIG_COMPLETE_RATING_COLUMNS", true };
    game_feature gameui_highlight_legions{ "gameui_highlight_legions", "#TR_CONFIG_HIGHLIGHT_LEGIONS", true };
    game_feature gameui_rotate_manually{ "gameui_rotate_manually", "#TR_CONFIG_ROTATE_MANUALLY", true };
    game_feature gameplay_change_grandfestival{ "gameplay_change_grandfestival", "#TR_CONFIG_GRANDFESTIVAL", true };
    game_feature gameplay_change_jealous_gods{ "gameplay_change_jealous_gods", "#TR_CONFIG_JEALOUS_GODS", true };
    game_feature gameplay_change_global_labour{ "gameplay_change_global_labour", "#TR_CONFIG_GLOBAL_LABOUR", false };
    game_feature gameplay_change_school_walkers{ "gameplay_change_school_walkers", "#TR_CONFIG_SCHOOL_WALKERS", false };
    game_feature gameplay_change_retire_at_60{ "gameplay_change_retire_at_60", "#TR_CONFIG_RETIRE_AT_60", true };
    game_feature gameplay_change_fixed_workers{ "gameplay_change_fixed_workers", "#TR_CONFIG_FIXED_WORKERS", false };
    game_feature gameplay_enable_extra_forts{ "gameplay_enable_extra_forts", "#TR_CONFIG_EXTRA_FORTS", false };
    game_feature gameplay_hyenas_block{ "gameplay_hyenas_block", "#TR_CONFIG_WOLVES_BLOCK", false };
    game_feature gameplay_dynamic_granaries{ "gameplay_dynamic_granaries", "#TR_CONFIG_DYNAMIC_GRANARIES", false };
    game_feature gameplay_houses_stockpile_more{ "gameplay_houses_stockpile_more", "#TR_CONFIG_MORE_STOCKPILE", false };
    game_feature gameplay_buyers_dont_distribute{ "gameplay_buyers_dont_distribute", "#TR_CONFIG_NO_BUYER_DISTRIBUTION", true };
    game_feature gameplay_change_immediate_delete{ "gameplay_change_immediate_delete", "#TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS", false };
    game_feature gameplay_change_getting_granaries_go_offroad{ "gameplay_change_getting_granaries_go_offroad", "#TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD", false };
    game_feature gameplay_change_granaries_get_double{ "gameplay_change_granaries_get_double", "#TR_CONFIG_GRANARIES_GET_DOUBLE", false };
    game_feature gameplay_change_tower_sentries_go_offroad{ "gameplay_change_tower_sentries_go_offroad", "#TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD", false };
    game_feature gameplay_change_farms_deliver_close{ "gameplay_change_farms_deliver_close", "#TR_CONFIG_FARMS_DELIVER_CLOSE", false };
    game_feature gameplay_change_only_deliver_to_accepting_granaries{ "gameplay_change_only_deliver_to_accepting_granaries", "#TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES", false };
    game_feature gameplay_change_all_houses_merge{ "gameplay_change_all_houses_merge", "#TR_CONFIG_ALL_HOUSES_MERGE", false };
    game_feature gameplay_change_beer_open_trade_route_counts{ "gameplay_change_beer_open_trade_route_counts", "#TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE", false };
    game_feature gameplay_change_random_mine_or_pit_collapses_take_money{ "gameplay_change_random_mine_or_pit_collapses_take_money", "#TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY", true };
    game_feature gameplay_change_multiple_barracks{ "gameplay_change_multiple_barracks", "#TR_CONFIG_MULTIPLE_BARRACKS", false };
    game_feature gameplay_change_warehouses_dont_accept{ "gameplay_change_warehouses_dont_accept", "#TR_CONFIG_NOT_ACCEPTING_WAREHOUSES", false };
    game_feature gameplay_change_houses_dont_expand_into_gardens{ "gameplay_change_houses_dont_expand_into_gardens", "#TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS", false };
    game_feature gameplay_fix_irrigation_range{ "gameplay_fix_irrigation_range", "#TR_CONFIG_FIX_IRRIGATION_RANGE", true };
    game_feature gameplay_fix_farm_produce_quantity{ "gameplay_fix_farm_produce_quantity", "#TR_CONFIG_FIX_FARM_PRODUCING", true };
    game_feature gameui_keep_camera_inertia{ "gameui_keep_camera_inertia", "#TR_CONFIG_CAMERA_KEEP_INERTIA", true };
    game_feature gameplay_change_understaffed_accept_goods{ "gameplay_change_understaffed_accept_goods", "#TR_CONFIG_UNDERSTAFFED_ACCEPT_GOODS", false };
    game_feature gameplay_change_multiple_temple_complexes{ "gameplay_change_multiple_temple_complexes", "#TR_CONFIG_MULTIPLE_TEMPLE_COMPLEXES", false };
    game_feature gameplay_change_multiple_monuments{ "gameplay_change_multiple_monuments", "#TR_CONFIG_MULTIPLE_MONUMENTS", false };
    game_feature gameplay_change_soil_depletion{ "gameplay_change_soil_depletion", "#TR_CONFIG_SOIL_DEPLETION", true };
    game_feature gameplay_change_multiple_gatherers{ "gameplay_change_multiple_gatherers", "#TR_CONFIG_MULTIPLE_GATHERERS", false };
    game_feature gameplay_change_fireman_returning{ "gameplay_change_fireman_returning", "#TR_CONFIG_FIREMAN_RETURNING", true };
    game_feature gameui_draw_fps{ "gameui_draw_fps", "#TR_CONFIG_DRAW_FPS", true };
    game_feature gameplay_change_cart_speed_depends_quntity{ "gameplay_change_cart_speed_depends_quntity", "#TR_CONFIG_CART_SPEED_DEPENDS_QUANTITY", true };
    game_feature gameplay_change_citizen_road_offset{ "gameplay_change_citizen_road_offset", "#TR_CONFIG_CH_CITIZEN_ROAD_OFFSET", true };
    game_feature gameplay_change_work_camp_one_worker_per_month{ "gameplay_change_work_camp_one_worker_per_month", "#TR_CONFIG_CH_WORK_CAMP_ONE_WORKER_PER_MONTH", true };
    game_feature gameplay_change_fire_risk_clay_pit_reduced{ "gameplay_change_fire_risk_clay_pit_reduced", "#TR_CONFIG_CH_CLAY_PIT_FIRE_RISK_REDUCED", true };
    game_feature gameplay_change_goldmine_twice_production{ "gameplay_change_goldmine_twice_production", "#TR_CONFIG_GOLDMINE_TWICE_PRODUCTION", true };
    game_feature gameplay_change_new_tax_collection_system{ "gameplay_change_new_tax_collection_system", "#TR_CONFIG_NEW_TAX_COLLECTION_SYSTEM", false };
    game_feature gameplay_change_small_hut_not_create_emigrant{ "gameplay_change_small_hut_not_create_emigrant", "#TR_CONFIG_SMALL_HUT_NOT_CREATE_EMIGRANT", true };
    game_feature gameplay_change_delivery_boy_goes_to_market_alone{ "gameplay_change_delivery_boy_goes_to_market_alone", "#TR_CONFIG_DELIVERY_BOY_GOES_TO_MARKET_ALONE", true };
    game_feature gameplay_change_religion_coverage_influence_sentiment{ "gameplay_change_religion_coverage_influence_sentiment", "#TR_CONFIG_RELIGION_COVERAGE_INFLUENCE_SENTIMENT", true };
    game_feature gameplay_change_monuments_influence_sentiment{ "gameplay_change_monuments_influence_sentiment", "#TR_CONFIG_MONUMENTS_INFLUENCE_SENTIMENT", true };
    game_feature gameplay_change_well_radius_depends_moisture{ "gameplay_change_well_radius_depends_moisture", "#TR_CONFIG_WELL_RADIUS_DEPENDS_MOISTURE", true };
    game_feature gameplay_change_enter_point_on_nearest_tile{ "gameplay_change_enter_point_on_nearest_tile", "#TR_CONFIG_ENTER_POINT_ON_NEAREST_TILE", true };
    game_feature gameplay_fishing_wharf_spawn_boats{ "gameplay_fishing_wharf_spawn_boats", "#TR_CONFIG_FISHING_WHARF_SPAWN_BOATS", true };
    game_feature gameplay_city_flotsam_enabled{ "gameplay_city_flotsam_enabled", "#TR_CONFIG_CITY_FLOTSAM_ENABLED", true };
    game_feature gameplay_copper_mine_can_build_near_mountains{ "gameplay_copper_mine_can_build_near_mountains", "#TR_CONFIG_COPPER_NEAR_MOUNTAINS", true };
    game_feature gameplay_recruiter_not_need_forts{ "gameplay_recruiter_not_need_forts", "#TR_CONFIG_RECRUITER_NOT_NEED_FORTS", true };
    game_feature gameui_highlight_top_menu_hover{ "gameui_highlight_top_menu_hover", "#TR_CONFIG_HIGHLIGHT_TOP_MENU_HOVER", true };
    game_feature gameui_empire_city_old_names{ "gameui_empire_city_old_names", "#TR_CONFIG_EMPIRE_CITY_OLD_NAMES", true };
    game_feature gameplay_draw_cloud_shadows{ "gameplay_draw_cloud_shadows", "#TR_CONFIG_DRAW_CLOUD_SHADOWS", true };
    game_feature gameplay_building_road_closest{ "gameplay_building_road_closest", "#TR_CONFIG_BUILDING_CLOSEST_ROAD", true };
    game_feature gameplay_floodplain_random_grow{ "gameplay_floodplain_random_grow", "#TR_CONFIG_FLOODPLAIN_RANDOM_GROW", true };
    game_feature gameui_hide_new_game_top_menu{ "gameui_hide_new_game_top_menu", "#TR_CONFIG_HIDE_NEW_GAME_TOP_MENU", true };
    game_feature gameplay_save_year_kingdome_rating{ "gameplay_save_year_kingdome_rating", "#TR_CONFIG_SAVE_YEAR_KINGDOME_RATING", true };
    game_feature gameopt_last_player{ "gameopt_last_playerg", "#TR_CONFIG_SAVE_YEAR_KINGDOME_RATING", "" };

    custom_span<game_feature*> features() {
        return { _features.data(), _features.size() };
    }
}

game_features::game_feature::game_feature(const xstring &n, const xstring &t, setting_variant def) : name(n), text(t), defaultv(def) {
    _features.push_back(this);
    g_ankh_config.settings.set(name, defaultv);
}

bool game_features::game_feature::to_bool() const {
    return g_ankh_config.settings.get_bool(name);
}

const xstring &game_features::game_feature::to_string() const {
    return g_ankh_config.settings.get_string(name);
}

void game_features::game_feature::set(bool value) {
    g_ankh_config.settings.set_bool(name, value);
}

void game_features::game_feature::set(const xstring &value) {
    g_ankh_config.settings.set_string(name, value);
}

setting_variant_type game_features::game_feature::type() const {
    return g_ankh_config.settings.type(name);
}

static pcstr ini_string_keys[] = {
  "ui_language_dir",
  "last_save_filename",
  "reserved_2",
  "0",
};

pcstr default_string_values[CONFIG_STRING_MAX_ENTRIES];

xstring ankh_config_t::get(e_config_str key) {
    return string_values[key];
}

void ankh_config_t::set(e_config_str key, const xstring value) {
    string_values[key] = value;
}

void ankh_config_t::set(e_config_str key, pcstr value) {
    string_values[key] = value;
}

const char* config_get_default_string_value(int key) {
    return default_string_values[key];
}

void ankh_config_t::reset_defaults() {
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
    for (int i = 0; i < CONFIG_STRING_MAX_ENTRIES; i++) {
        fprintf(fp, "%s=%s\n", ini_string_keys[i], string_values[i].c_str());
    }
    vfs::file_close(fp);
    vfs::sync_em_fs();

    settings.sync(CONF_FILENAME);
}
