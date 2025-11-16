#include "game_config.h"

#include "content/vfs.h"
#include "core/log.h"
#include "core/svector.h"
#include "js/js_game.h"
#include "dev/debug.h"

static const char* CONF_FILENAME = "akhenaten.conf";

void ANK_REGISTER_CONFIG_ITERATOR(config_load_game_settings) {
    game_features::load();
}

namespace game_features {
    svector<game_feature*, 128> _features;
    globals_settings_t _settings;

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
    game_feature gameui_smooth_zoom{ "gameui_smooth_zoom", "#TR_CONFIG_SMOOTH_ZOOM", true };
    game_feature gameui_complete_ratings_columns{ "gameui_complete_ratings_columns", "#TR_CONFIG_COMPLETE_RATING_COLUMNS", true };
    game_feature gameui_highlight_legions{ "gameui_highlight_legions", "#TR_CONFIG_HIGHLIGHT_LEGIONS", true };
    game_feature gameui_rotate_manually{ "gameui_rotate_manually", "#TR_CONFIG_ROTATE_MANUALLY", true };
    game_feature gameplay_change_grandfestival{ "gameplay_change_grandfestival", "#TR_CONFIG_GRANDFESTIVAL", true };
    game_feature gameplay_change_hasanimals{ "gameplay_change_grandfestival", "#TR_CONFIG_CITY_HAS_ANIMALS", true };
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
    game_feature gameopt_last_player{ "gameopt_last_player", "", "" };
    game_feature gameopt_language { "gameopt_language", "", "" };
    game_feature gameopt_last_save_filename{ "gameopt_last_save_filename", "", "" };
    game_feature gameopt_last_game_version{ "gameopt_last_game_version", "", "" };
    game_feature gameplay_brewery_requires_water{ "gameplay_brewery_requires_water", "#TR_CONFIG_BREWERY_REQUIRES_WATER", true };

    custom_span<game_feature*> all() {
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
}

game_features::game_feature::game_feature(const xstring &n, const xstring &t, setting_variant def) : name(n), text(t), defaultv(def) {
    _features.push_back(this);
    _settings.set(name, defaultv);
}

bool game_features::game_feature::to_bool() const {
    return _settings.get_bool(name);
}

xstring game_features::game_feature::to_string() const {
    return _settings.get_string(name);
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

setting_variant_type game_features::game_feature::type() const {
    return _settings.type(name);
}

void game_features::load() {
    _settings.load_global("game_settings");
}

void game_features::save() {
    vfs::sync_em_fs();
    _settings.sync_global(CONF_FILENAME, "game_settings");
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
