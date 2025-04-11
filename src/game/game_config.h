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
    extern game_feature gameplay_change_new_tax_collection_system;
    extern game_feature gameplay_change_small_hut_not_create_emigrant;
    extern game_feature gameplay_change_delivery_boy_goes_to_market_alone;
    extern game_feature gameplay_change_religion_coverage_influence_sentiment;
    extern game_feature gameplay_change_monuments_influence_sentiment;
    extern game_feature gameplay_change_well_radius_depends_moisture;
    extern game_feature gameplay_change_enter_point_on_nearest_tile;
    extern game_feature gameplay_fishing_wharf_spawn_boats;
    extern game_feature gameplay_city_flotsam_enabled;
    extern game_feature gameplay_copper_mine_can_build_near_mountains;
    extern game_feature gameplay_recruiter_not_need_forts;

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
    CONFIG_RESERVED_55,
    CONFIG_RESERVED_56,
    CONFIG_RESERVED_57,
    CONFIG_RESERVED_58,
    CONFIG_RESERVED_59,
    CONFIG_RESERVED_60,
    CONFIG_RESERVED_61,

    CONFIG_RESERVED_62,
    CONFIG_RESERVED_63,
    CONFIG_RESERVED_64,
    CONFIG_RESERVED_65,
    CONFIG_RESERVED_66,
    ///
    CONFIG_RESERVED_67,
    CONFIG_RESERVED_68,
    CONFIG_RESERVED_69,
    CONFIG_RESERVED_70,
    CONFIG_RESERVED_71,
    CONFIG_RESERVED_72,
    CONFIG_RESERVED_73,

    CONFIG_RESERVED_74,
    CONFIG_RESERVED_75,
    CONFIG_RESERVED_76,
    CONFIG_RESERVED_77,
    CONFIG_RESERVED_78,
    
    CONFIG_RESERVED_79,
    CONFIG_RESERVED_80,
    CONFIG_RESERVED_81,
    CONFIG_RESERVED_82,
    CONFIG_RESERVED_83,
    CONFIG_RESERVED_84,
    CONFIG_RESERVED_85,
    CONFIG_RESERVED_86,
    CONFIG_RESERVED_87,
    CONFIG_RESERVED_88,
    CONFIG_RESERVED_89,
    CONFIG_RESERVED_90,
    CONFIG_RESERVED_91,
    CONFIG_RESERVED_92,
    CONFIG_RESERVED_93,
    CONFIG_RESERVED_94,
    CONFIG_RESERVED_95,

    CONFIG_RESERVED_96,
    CONFIG_RESERVED_97,
    CONFIG_RESERVED_98,
    CONFIG_RESERVED_99,
    CONFIG_RESERVED_100,
    CONFIG_RESERVED_101,
    CONFIG_RESERVED_102,
    CONFIG_RESERVED_103,
    CONFIG_RESERVED_104,
    CONFIG_RESERVED_105,
    CONFIG_RESERVED_106,
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