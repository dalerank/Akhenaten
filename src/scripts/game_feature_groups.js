log_info("akhenaten: game feature groups started")

game_feature_groups = [
    {
        id: "interface", title: "#TR_CONFIG_HEADER_INTERFACE",
        features: ["gameui_sidebar_info", "gameui_show_intro_video", "gameui_complete_ratings_columns",
                   "gameui_highlight_legions", "gameui_highlight_top_menu_hover", "gameui_empire_city_old_names",
                   "gameui_hide_new_game_top_menu", "gameui_disable_nilometer_popups", "gameui_enhanced_nilometer",
                   "gameui_building_mothball_button", "gameui_enhanced_shrine_info", "gameui_prompt_save_on_exit",
                   "gameui_show_input_near_cursor"]
    }
    {
        id: "map_view", title: "#TR_CONFIG_HEADER_MAP_VIEW",
        features: ["gameui_smooth_scrolling", "gameui_keep_camera_inertia", "gameui_zoom", "gameui_smooth_zoom",
                   "gameui_rotate_manually", "gameui_walker_waypoints", "gameui_visual_feedback_on_delete",
                   "gameui_show_water_structure_range", "gameui_show_building_road_access", "gameui_show_delivery_paths",
                   "gameui_show_construction_size", "gameui_show_current_select_tile", "gameui_road_preview_in_map_order",
                   "gameui_overlay_show_gray_buildings"]
    }
    {
        id: "graphics_sound", title: "#TR_CONFIG_HEADER_GRAPHICS_SOUND",
        features: ["gameui_flat_buildings", "gameui_house_interior", "gameplay_draw_cloud_shadows",
                   "gameplay_change_abu_simbel_draw_scaffolds", "gameplay_change_citizen_road_offset", "gameui_draw_fps",
                   "gameplay_enhanced_city_ambient", "gameplay_change_walker_phrases_remake"]
    }
    {
        id: "game", title: "#TR_CONFIG_HEADER_GAME_OPTIONS",
        features: ["gameopt_ironwill", "gameopt_unlock_all_campaigns", "gameopt_auto_update",
                   "gameplay_pause_sim_while_building", "gameplay_change_empire_map_runs_simulation",
                   "gameplay_change_immediate_delete", "gameplay_prevent_delete_near_burning_ruins"]
    }
    {
        id: "fixes", title: "#TR_CONFIG_HEADER_FIXES",
        features: ["gameplay_fix_immigration", "gameplay_fix_100y_ghosts", "gameplay_fix_editor_events",
                   "gameplay_fix_farm_produce_quantity", "gameplay_og_architect", "gameplay_og_fireman",
                   "gameplay_og_warehouseman", "gameplay_og_trader"]
    }
    {
        id: "city", title: "#TR_CONFIG_HEADER_CITY",
        features: ["gameplay_change_global_labour", "gameplay_change_nobles_dont_provide_labor", "gameplay_change_fixed_workers",
                   "gameplay_change_retire_at_60", "gameplay_change_migration_unemployment",
                   "gameplay_change_small_hut_not_create_emigrant", "gameplay_change_all_houses_merge",
                   "gameplay_change_houses_dont_expand_into_gardens", "gameplay_change_house_evolve_delay",
                   "gameplay_change_food_consumption_remake", "gameplay_houses_stockpile_more",
                   "gameplay_change_new_tax_collection_system", "gameplay_save_year_kingdome_rating",
                   "gameplay_change_religion_coverage_influence_sentiment", "gameplay_change_monuments_influence_sentiment"]
    }
    {
        id: "services", title: "#TR_CONFIG_HEADER_SERVICES",
        features: ["gameplay_change_school_walkers", "gameplay_change_library_service_cap", "gameplay_change_dentist_service_cap",
                   "gameplay_change_dentist_toothache", "gameplay_change_physician_service_cap", "gameplay_change_apothecary_remake",
                   "gameplay_change_mortuary_service_cap", "gameplay_change_mortuary_linen_upkeep",
                   "gameplay_change_mortuary_mothballed_linen", "gameplay_conservatory_helps_dance_school",
                   "gameplay_juggler_school_one_walker", "gameplay_jewels_workshops_culture_bonus",
                   "gameplay_change_jealous_gods", "gameplay_change_grandfestival", "gameplay_change_shrine_house_access"]
    }
    {
        id: "industry", title: "#TR_CONFIG_HEADER_INDUSTRY",
        features: ["gameplay_change_soil_depletion", "gameplay_change_farms_deliver_close", "gameplay_change_farm_harvest_fertility",
                   "gameplay_change_farm_meadow_harvest_retry", "gameplay_change_irrigation_range_5x5",
                   "gameplay_floodplain_random_grow", "gameplay_change_well_radius_depends_moisture",
                   "gameplay_change_work_camp_one_worker_per_month", "gameplay_change_work_camp_destination_at_spawn",
                   "gameplay_change_work_camp_distance_scaled_farm_workers", "gameplay_change_industry_nearby_houses",
                   "gameplay_change_understaffed_accept_goods", "gameplay_change_industry_remake_rates",
                   "gameplay_rebalance_workshop_output", "gameplay_change_jeweler_nearby_discount",
                   "gameplay_chariots_workshop_needs_weapons", "gameplay_brewery_requires_water",
                   "gameplay_change_goldmine_reduced_production", "gameplay_change_random_mine_or_pit_collapses_take_money",
                   "gameplay_change_fire_risk_clay_pit_reduced", "gameplay_copper_mine_can_build_near_mountains",
                   "gameplay_change_multiple_gatherers", "gameplay_change_wood_cutter_single_gatherer",
                   "gameplay_fishing_wharf_spawn_boats", "gameplay_change_fishing_points_monthly_respawn",
                   "gameplay_change_fishing_points_drift", "gameplay_city_flotsam_enabled"]
    }
    {
        id: "storage_trade", title: "#TR_CONFIG_HEADER_STORAGE_TRADE",
        features: ["gameplay_dynamic_granaries", "gameplay_change_getting_granaries_go_offroad",
                   "gameplay_change_granaries_get_double", "gameplay_change_only_deliver_to_accepting_granaries",
                   "gameplay_change_warehouses_dont_accept", "gameplay_buyers_dont_distribute",
                   "gameplay_change_bazaar_multi_buyers", "gameplay_change_bazaar_buyer_spawn_timer",
                   "gameplay_change_bazaar_demand_from_trader", "gameplay_change_market_distribute_remake",
                   "gameplay_change_delivery_boy_goes_to_market_alone", "gameplay_change_dock_double_haul",
                   "gameplay_change_dock_smart_routing", "gameplay_change_trader_capacity_1600",
                   "gameplay_change_trader_per_good_1600"]
    }
    {
        id: "walkers", title: "#TR_CONFIG_HEADER_WALKERS_BUILDINGS",
        features: ["gameplay_change_follower_runaway", "gameplay_change_sled_pullers_flee", "gameplay_change_sled_return_empty",
                   "gameplay_change_fishing_boat_remake", "gameplay_change_ferry_remake",
                   "gameplay_change_architect_patrol_most_damaged", "gameplay_change_fireman_returning",
                   "gameplay_change_cart_speed_depends_quntity", "gameplay_change_cartpushers_yield_by_id",
                   "gameplay_change_enter_point_on_nearest_tile", "gameplay_building_road_closest",
                   "gameplay_change_multiple_temple_complexes", "gameplay_change_multiple_monuments",
                   "gameplay_change_statue_variants", "gameplay_change_guild_statue_service",
                   "gameplay_change_mastaba_clay_delivery", "gameplay_sphinx_artisans"]
    }
    {
        id: "military", title: "#TR_CONFIG_HEADER_MILITARY_DISASTERS",
        features: ["gameplay_enable_extra_forts", "gameplay_change_multiple_barracks", "gameplay_change_fort_rotation",
                   "gameplay_change_fort_refund_carry_troops", "gameplay_change_recruit_nearest_fort",
                   "gameplay_recruiter_not_need_forts", "gameplay_change_tower_sentries_go_offroad",
                   "gameplay_change_police_weapons", "gameplay_change_robber_remake", "gameplay_change_tomb_robber_remake",
                   "gameplay_change_protestor_hunt_nobles", "gameplay_change_plagued_citizen_remake",
                   "gameplay_change_disaster_events_use_amount", "gameplay_bast_lion_raid", "gameplay_seth_asp_raid",
                   "gameplay_ptah_scorpion_raid", "gameplay_change_has_animals", "gameplay_hyenas_block"]
    }
    {
        id: "enhanced", title: "#TR_CONFIG_HEADER_NEW_FEATURES",
        features: ["gameplay_enhanced_flood_basins", "gameplay_enhanced_historical_economy", "gameplay_enhanced_food_mill",
                   "gameplay_enhanced_industry_office", "gameplay_enhanced_labor_category_split",
                   "gameplay_enhanced_walker_spawn_boost", "gameplay_enhanced_walker_move_boost",
                   "gameplay_enhanced_festival_calendar", "gameplay_enhanced_local_cults",
                   "gameplay_enhanced_auto_resolve_invasions", "gameplay_enhanced_invasion_bribe"]
    }
]
