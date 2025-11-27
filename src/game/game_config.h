#pragma once

#include "core/xstring.h"
#include "core/settings_vars.h"
#include "core/typename.h"
#include "core/custom_span.hpp"
#include <array>

namespace game_features {
    struct game_feature {
        const xstring name;
        const xstring text;
        const setting_variant defaultv;

        game_feature(const xstring &n, const xstring &t, setting_variant def);
        bool to_bool() const;
        xstring to_string() const;
        inline bool operator!() const { return !to_bool(); }
        void set(bool value);
        void set(float value);
        void set(int value);
        void set(const xstring &value);
        void set(pcstr value);
        setting_variant_type type() const;

        inline game_feature& operator=(pcstr value) {
            set(value);
            return *this;
        }

        inline game_feature &operator=(const xstring& value) {
            set(value.c_str());
            return *this;
        }
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
    extern game_feature gameui_smooth_zoom;
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
    extern game_feature gameui_highlight_top_menu_hover;
    extern game_feature gameui_empire_city_old_names;
    extern game_feature gameplay_draw_cloud_shadows;
    extern game_feature gameplay_building_road_closest;
    extern game_feature gameplay_floodplain_random_grow;
    extern game_feature gameui_hide_new_game_top_menu;
    extern game_feature gameplay_save_year_kingdome_rating;
    extern game_feature gameopt_last_player;
    extern game_feature gameopt_language;
    extern game_feature gameopt_last_save_filename;
    extern game_feature gameopt_last_game_version;
    extern game_feature gameplay_change_hasanimals;
    extern game_feature gameplay_brewery_requires_water;
    extern game_feature gameplay_conservatory_helps_dance_school;
    extern game_feature gameplay_jewels_workshops_culture_bonus;

    custom_span<game_feature*> all();
    game_feature* find(const xstring& name);

    void load();
    void save();
}