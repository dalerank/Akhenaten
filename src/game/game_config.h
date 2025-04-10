#pragma once

#include "core/xstring.h"
#include "core/settings_vars.h"
#include "core/typename.h"
#include "core/custom_span.hpp"
#include <array>

namespace game_features {
    struct game_feature {
        const xstring name;
        const setting_variant defaultv;

        game_feature(const xstring &n, setting_variant def);
        bool to_bool() const;
        inline bool operator!() const { return !to_bool(); }
        void set(bool value);
    };

    extern game_feature gameplay_fix_immigration;
    extern game_feature gameplay_fix_100y_ghosts;
    extern game_feature gameplay_fix_editor_events;
    extern game_feature gameui_sidebar_info;
    extern game_feature gameui_show_intro_video;
    extern game_feature gameui_smooth_scrolling;
    extern game_feature gameui_walker_waypoints;
    extern game_feature gameui_visual_feedback_on_delete;
    extern game_feature gameui_show_water_structure_range;
    extern game_feature gameui_show_construction_size;
    extern game_feature gameui_zoom;
    extern game_feature gameui_complete_ratings_columns;
    extern game_feature gameui_highlight_legions;
    extern game_feature gameui_rotate_manually;
    extern game_feature gameplay_change_grandfestival;
    extern game_feature gameplay_change_jealous_gods;
    extern game_feature gameplay_change_global_labour;
    extern game_feature gameplay_change_school_walkers;
    extern game_feature gameplay_change_retire_at_60;
    extern game_feature gameplay_change_fixed_workers;
    extern game_feature gameplay_enable_extra_forts;
    extern game_feature gameplay_hyenas_block;
    extern game_feature gameplay_dynamic_granaries;
    extern game_feature gameplay_houses_stockpile_more;
    extern game_feature gameplay_buyers_dont_distribute;
    extern game_feature gameplay_change_immediate_delete;
    extern game_feature gameplay_change_getting_granaries_go_offroad;
    extern game_feature gameplay_change_granaries_get_double;
    extern game_feature gameplay_change_tower_sentries_go_offroad;
    extern game_feature gameplay_change_farms_deliver_close;
    extern game_feature gameplay_change_only_deliver_to_accepting_granaries;
    extern game_feature gameplay_change_all_houses_merge;
    extern game_feature gameplay_change_beer_open_trade_route_counts;
    extern game_feature gameplay_change_random_mine_or_pit_collapses_take_money;
    extern game_feature gameplay_change_multiple_barracks;
    extern game_feature gameplay_change_warehouses_dont_accept;
    extern game_feature gameplay_change_houses_dont_expand_into_gardens;
    extern game_feature gameplay_fix_irrigation_range;
    extern game_feature gameplay_fix_farm_produce_quantity;
    extern game_feature gameui_keep_camera_inertia;
    extern game_feature gameplay_change_understaffed_accept_goods;
    extern game_feature gameplay_change_multiple_temple_complexes;
    extern game_feature gameplay_change_multiple_monuments;
    extern game_feature gameplay_change_soil_depletion;
    extern game_feature gameplay_change_multiple_gatherers;
    extern game_feature gameplay_change_fireman_returning;
    extern game_feature gameui_draw_fps;
    extern game_feature gameplay_change_cart_speed_depends_quntity;
    extern game_feature gameplay_change_citizen_road_offset;
    extern game_feature gameplay_change_work_camp_one_worker_per_month;
    extern game_feature gameplay_change_fire_risk_clay_pit_reduced;
    extern game_feature gameplay_change_goldmine_twice_production;

    custom_span<game_feature*> features();
}

enum e_config_key {
    CONFIG_RESERVED_0 = 0,
    CONFIG_RESERVED_1,
    CONFIG_RESERVED_2,
    CONFIG_RESERVED_3,
    CONFIG_RESERVED_4,
    CONFIG_RESERVED_5,
    CONFIG_RESERVED_6,
    CONFIG_RESERVED_7,
    CONFIG_RESERVED_8,
    CONFIG_RESERVED_9,
    CONFIG_RESERVED_10,
    CONFIG_RESERVED_11,
    CONFIG_RESERVED_12,
    CONFIG_RESERVED_13,
    CONFIG_RESERVED_14,
    CONFIG_RESERVED_15,
    CONFIG_RESERVED_16,
    CONFIG_RESERVED_17,
    CONFIG_RESERVED_18,
    CONFIG_RESERVED_19,
    CONFIG_RESERVED_20,
    CONFIG_RESERVED_21,
    CONFIG_RESERVED_22,
    CONFIG_RESERVED_23,
    CONFIG_RESERVED_24,
    CONFIG_RESERVED_25,
    CONFIG_RESERVED_26,
    CONFIG_RESERVED_27,
    CONFIG_RESERVED_28,
    CONFIG_RESERVED_29,
    CONFIG_RESERVED_30,
    CONFIG_RESERVED_31,
    CONFIG_RESERVED_32,
    CONFIG_RESERVED_33,
    CONFIG_RESERVED_34,
    CONFIG_RESERVED_35,
    CONFIG_RESERVED_36,

    ///

    CONFIG_RESERVED_37,
    CONFIG_RESERVED_38,
    CONFIG_RESERVED_39,
    CONFIG_RESERVED_40,
    CONFIG_RESERVED_41,
    CONFIG_RESERVED_42,
    CONFIG_RESERVED_43,
    CONFIG_RESERVED_44,
    CONFIG_RESERVED_45,
    CONFIG_RESERVED_46,
    CONFIG_RESERVED_47,
    CONFIG_RESERVED_48,
    CONFIG_RESERVED_49,
    CONFIG_RESERVED_50,
    CONFIG_RESERVED_51,
    CONFIG_RESERVED_52,
    CONFIG_RESERVED_53,
    CONFIG_RESERVED_54,
    CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM,
    CONFIG_GP_CH_SMALL_HUT_NIT_CREATE_EMIGRANT,
    CONFIG_GP_CH_DELIVERY_BOY_GOES_TO_MARKET_ALONE,
    CONFIG_GP_CH_RELIGION_COVERAGE_INFLUENCE_SENTIMENT,
    CONFIG_GP_CH_MONUMENTS_INFLUENCE_SENTIMENT,
    CONFIG_GP_CH_WELL_RADIUS_DEPENDS_MOISTURE,
    CONFIG_GP_CH_ENTER_POINT_ON_NEAREST_TILE,

    CONFIG_GP_CH_GOD_OSIRIS_DISABLED,
    CONFIG_GP_CH_GOD_RA_DISABLED,
    CONFIG_GP_CH_GOD_PTAH_DISABLED,
    CONFIG_GP_CH_GOD_SETH_DISABLED,
    CONFIG_GP_CH_GOD_BAST_DISABLED,
    ///
    CONFIG_GP_CH_BUILDING_WOOD_CUTTER,
    CONFIG_GP_CH_RESOURCE_TIMBER,
    CONFIG_GP_CH_RESOURCE_CHICKPEAS,
    CONFIG_GP_CH_RESOURCE_POMEGRANADES,
    CONFIG_GP_CH_RESOURCE_LETTUCE,
    CONFIG_GP_CH_BUILDING_COPPER_MINE,
    CONFIG_GP_CH_RESOURCE_COPPER,

    CONFIG_GP_CH_BUILDING_REED_GATHERER,
    CONFIG_GP_CH_BUILDING_PAPYRUS_MAKER,
    CONFIG_GP_CH_BUILDING_SCRIBAL_SCHOOL,
    CONFIG_GP_CH_RESOURCE_REED,
    CONFIG_GP_CH_RESOURCE_PAPYRUS,
    
    CONFIG_GP_CH_BUILDING_SHIPYARD,
    CONFIG_GP_CH_BUILDING_FISHING_WHARF,
    CONFIG_GP_CH_RESOURCE_FISH,
    CONFIG_GP_CH_FISHING_WHARF_SPAWN_BOATS,
    CONFIG_GP_CH_FLOTSAM_ENABLED,
    CONFIG_GP_CH_BUILDING_CHICKPEAS_FARM,
    CONFIG_GP_CH_BUILDING_LETTUCE_FARM,
    CONFIG_GP_CH_BUILDING_POMEGRANATES_FARM,
    CONFIG_GP_CH_BUILDING_FIGS_FARM,
    CONFIG_GP_CH_RESOURCE_FIGS,
    CONFIG_GP_CH_BUILDING_GRAIN_FARM,
    CONFIG_GP_CH_RESOURCE_GRAIN,
    CONFIG_GP_CH_BUILDING_CATTLE_RANCH,
    CONFIG_GP_CH_RESOURCE_MEAT,
    CONFIG_GP_CH_BUILDING_BRICKS_WORKSHOP,
    CONFIG_GP_CH_RESOURCE_BRICKS,
    CONFIG_GP_CH_RESOURCE_CLAY,

    CONFIG_GP_CH_BUILDING_WORK_CAMP,
    CONFIG_GP_CH_BUILDING_GOLD_MINE,
    CONFIG_GP_CH_BUILDING_QUARRY_SANDSTONE,
    CONFIG_GP_CH_BUILDING_QUARRY_GRANITE,
    CONFIG_GP_CH_BUILDING_QUARRY_STONE,
    CONFIG_GP_CH_BUILDING_QUARRY_LIMESTONE,
    CONFIG_GP_CH_BUILDING_CLAY_PIT,
    CONFIG_GP_CH_BUILDING_WEAPONSMITH,
    CONFIG_GP_CH_COPPER_NEAR_MOUNTAINS,
    CONFIG_GP_CH_BUILDING_RECRUTER,
    CONFIG_GP_CH_RECRUITER_NOT_NEED_FORTS,
    CONFIG_UI_HIGHLIGHT_TOP_MENU_HOVER,
    CONFIG_UI_EMPIRE_CITY_OLD_NAMES,
    CONFIG_UI_DRAW_CLOUD_SHADOWS,
    CONFIG_GP_CH_BUILDING_SMALL_MASTABA,
    CONFIG_GP_CH_BUILDING_BRICKLAYERS,
    CONFIG_GP_CH_BUILDING_CLOSEST_ROAD,
    CONFIG_GP_CH_FLOODPLAIN_RANDOM_GROW,
    CONFIG_GP_CH_BUILDING_BOOTH,
    CONFIG_GP_CH_BUILDING_BANDSTAND,

    CONFIG_UI_HIDE_NEW_GAME_TOP_MENU,
    CONFIG_GP_CHANGE_SAVE_YEAR_KINGDOME_RATING,

    CONFIG_GP_CH_BUILDING_MEDIUM_MASTABA,

    CONFIG_MAX_ENTRIES
};

enum e_config_str {
    CONFIG_STRING_UI_LANGUAGE_DIR,
    CONFIG_STRING_LAST_SAVE,
    CONFIG_STRING_LAST_PLAYER,
    CONFIG_STRING_LAST_VERSION,

    CONFIG_STRING_MAX_ENTRIES
};

struct ankh_config_t {
    settings_vars_t settings;
    std::array<bool, CONFIG_MAX_ENTRIES> opts;
    std::array<xstring, CONFIG_STRING_MAX_ENTRIES> string_values;

    int get(e_config_key key);
    void set(e_config_key key, int value);

    xstring get(e_config_str key);
    void set(e_config_str key, const xstring value);
    void set(e_config_str key, pcstr value);

    void reset_defaults();

    void load();
    void save();
};

extern ankh_config_t g_ankh_config;

/**
 * Set a default config value
 * @param key Integer key
 * @return Default config value
 */
bool config_get_default_value(e_config_key key);

/**
 * Get a string default config value
 * @param key String key
 * @return Default config value, is always non-NULL but may be an empty string
 */
const char* config_get_default_string_value(e_config_key key);