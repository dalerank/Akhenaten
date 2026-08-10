log_info("akhenaten: game started")

game = extend(__game, {
    // -> mission_choice_open_scenario_id
    // -> debug_properties
    // -> debug_terrain_paint
    // -> paused

    mission_briefing_scenario_id : 0
    mission_briefing_is_review : false

    simtime: __game_simtime

    @absolute_day { get: __game_absolute_day }
    simtime_year : __game_simtime.year

    @is_integral_tests { get: __game_is_integral_tests }
    @version { get: __game_version }
    @difficulty { get: __game_difficulty }
    @debug_render_mode { get: __game_debug_render_mode, set: __game_set_debug_render_mode }
    @debug_render_mode_name { get: __game_debug_render_mode_name, set: __game_set_debug_render_mode_name }
    @last_autosave { get: __game_get_last_autosave }
    @session_active { get: __game_session_active }
    @session_last_loaded_kind { get: __game_session_last_loaded_kind }
    @session_last_loaded_mission { get: __game_session_last_loaded_mission }
    @dynasty_name {
        get: function() { return game_features.gameopt_player_name },
        set: function(name) { game_features.gameopt_player_name = name }
    }
    @gods_enabled { get: __game_gods_enabled }
    @locale_year_before_ad { get: __game_locale_year_before_ad }

    save_screenshot: __game_save_screenshot
    set_screenshot_dir: __game_set_screenshot_dir

    languages {
        @count : { get: __game_languages_count }
        @current { get: __game_language_current, set: __game_language_set_current }

        get_caption : __game_language_caption
        get_id : __game_language_id
    }

    file_exists: __game_file_exists
    load_savegame: __game_load_savegame
    write_savegame: __game_write_savegame
    delete_savegame: __game_delete_savegame
    delete_map: __game_delete_map
    get_last_loaded_file: __game_get_last_loaded_file
    editor_load_scenario: __game_editor_load_scenario
    editor_write_scenario: __game_editor_write_scenario
    init_editor: __game_init_editor
    exit_editor: __game_exit_editor
    editor_is_active: __editor_is_active
    last_advisor: ADVISOR_NONE
})

screen = extend(__screen, {
    @is_fullscreen_only { get: __game_is_fullscreen_only }
})

video_capture = {
    @active { get: __video_capture_active }
    toggle: function() { emit event_video_capture_toggle{ reserved: 0 } }
}

game_features {
    __property_getter: function(property) { return __game_feature_get(property) }
    __property_setter: function(property, value) { __game_feature_set(property, value) }

    @gameui_hide_new_game_top_menu {}
    @gameui_empire_city_old_names {}
    @gameopt_monthly_autosave {}
    @gameopt_ironwill {}
    @gameopt_autosave_slots {}
    @gameopt_tooltips_mode {}
    @gameopt_warnings {}
    @gameopt_popup_messages {}
    @gameopt_gods_enabled {}
    @gameopt_victory_video {}
    @gameopt_pyramid_speedup {}
    @gameopt_fullscreen {}
    @gameopt_last_save_filename {  }
    @gameopt_last_player {  }
    @gameopt_player_name {  }
    @gameopt_sound_effects_enabled {}
    @gameopt_sound_effects_volume {}
    @gameopt_sound_music_enabled {}
    @gameopt_sound_music_volume {}
    @gameopt_sound_speech_enabled {}
    @gameopt_sound_speech_volume {}
    @gameopt_sound_city_enabled {}
    @gameopt_sound_city_volume {}
    @gameopt_game_speed {}
    @gameui_sidebar_info {}
    @gameui_building_mothball_button {}
    @gameui_prompt_save_on_exit {}
    @gameui_road_preview_in_map_order {}
    @gameui_enhanced_nilometer {}
    @gameopt_scroll_speed {}
    @gameopt_middle_mouse_camera_pan {}
    @gameopt_middle_mouse_pan_speed {}
    @gameopt_clouds_speed {}
    @gameplay_change_random_mine_or_pit_collapses_take_money {}
    @gameplay_change_disaster_events_use_amount {}
    @gameplay_change_trader_capacity_1600 {}
    @gameplay_change_trader_per_good_1600 {}
    @gameplay_bast_lion_raid {}
    @gameplay_seth_asp_raid {}
    @gameplay_ptah_scorpion_raid {}
    @gameplay_enhanced_auto_resolve_invasions {}
    @gameplay_enhanced_invasion_bribe {}
    @gameplay_enhanced_flood_basins {}
    @gameplay_enhanced_historical_economy {}
    @gameplay_enhanced_food_mill {}
    @gameplay_enhanced_industry_office {}
    @gameplay_enhanced_labor_category_split {}
    @gameplay_enhanced_walker_spawn_boost {}
    @gameplay_enhanced_walker_move_boost {}
    @gameplay_enhanced_festival_calendar {}
    @gameplay_enhanced_local_cults {}
    @gameplay_change_fixed_workers {}
    @gameplay_fixed_worker_percent {}
    @gameopt_display_size {}
    @gameplay_change_multiple_temple_complexes {}
    @gameplay_change_work_camp_one_worker_per_month {}
    @gameplay_fix_editor_events {}
    @gameopt_disable_victory {}
    @gameui_show_water_structure_range {}
    @gameui_show_building_road_access {}
    @gameui_show_delivery_paths {}
    @gameui_flat_buildings {}
    @count { get: __game_features_count }
}

game_features.name = __game_feature_name
game_features.text = __game_feature_text
game_features.get = __game_feature_get
game_features.set = __game_feature_set
game_features.count = __game_features_count
game_features.type = __game_feature_type
game_features.type_name = __game_feature_type_name
game_features.default = __game_feature_default

// Ironwill (IW*): player saves only via ironwill.svx checkpoint (Exit / Escape / Alt+F4).
// Choice is made on mission briefing (like difficulty); locked after Start until next briefing.
var IRONWILL_CHECKPOINT_FILENAME = "ironwill.svx"
var game_mission_options_locked = false

function game_decrease_difficulty_if_allowed() {
    if (game_mission_options_locked) {
        return
    }
    __game_decrease_difficulty()
}

function game_increase_difficulty_if_allowed() {
    if (game_mission_options_locked) {
        return
    }
    __game_increase_difficulty()
}

function game_allows_player_save() {
    return !game_features.gameopt_ironwill
}

function game_allows_midgame_load() {
    return !game_features.gameopt_ironwill
}

function game_write_ironwill_checkpoint() {
    return game.write_savegame(IRONWILL_CHECKPOINT_FILENAME)
}

/** @returns true if exit may proceed (Ironwill OFF, or checkpoint OK). */
function game_try_ironwill_checkpoint_before_menu() {
    if (!game_features.gameopt_ironwill) {
        return true
    }
    if (!game_write_ironwill_checkpoint()) {
        log_warning("Ironwill checkpoint failed on exit to menu")
        city.warnings.show("#ironwill_save_failed")
        return false
    }
    return true
}

/** File→Exit Game and Escape (city): confirm, optional Ironwill checkpoint, main menu. */
function game_confirm_exit_to_main_menu() {
    ui.show_yesno("#popup_dialog_quit",
        function() {
            widget_top_menu_clear_state()
            if (!game_try_ironwill_checkpoint_before_menu()) {
                ui.window_city_show()
                return
            }
            emit event_show_main_menu{ play_intro: true }
        },
        function() {
            ui.window_city_show()
        }
    )
}

function game_toast_ironwill_save_blocked() {
    city.warnings.show("#ironwill_save_blocked")
}

function game_toast_ironwill_load_blocked() {
    city.warnings.show("#ironwill_load_blocked")
}

[es=event_level_post_load]
function game_on_level_post_load_mission_options_lock(ev) {
    // Continue / mid-game load: lock immediately.
    // Campaign mission: unlock for briefing (Start locks again).
    // Custom map: do NOT lock here — map is often preview-loaded before Start.
    if (ev.session_kind === e_session_save) {
        game_mission_options_locked = true
    } else if (ev.session_kind === e_session_mission) {
        game_mission_options_locked = false
    }
}

[es=event_mission_start]
function game_on_mission_start_options_lock(ev) {
    // Sim/city about to run. Campaign briefing init unlocks again until Start.
    game_mission_options_locked = true
}

[es=event_mission_won]
function game_on_mission_won_troop_carry(ev) {
    if (ev.next_scenario_id < 0) {
        __campaign_carry_clear()
        return
    }
    __campaign_carry_snapshot_troops()
    __campaign_carry_snapshot_monuments()
}

[es=event_exit_to_menu_requested]
function game_on_exit_to_menu_requested(ev) {
    __video_stop()
    if (game.editor_is_active()) {
        ui.show_yesno("#popup_dialog_quit", function() {
            game.exit_editor()
        })
        return
    }
    game_confirm_exit_to_main_menu()
}

function calc_bound_scroll_speed(v, lo, hi) {
    if (v < lo) { return lo }
    if (v > hi) { return hi }
    return v
}

[es=event_change_scroll_speed]
function event_change_scroll_speed_handler(ev) {
    var s = Math.round(game_features.gameopt_scroll_speed)
    if (ev.increase) {
        s = calc_bound_scroll_speed(s + 10, 0, 100)
    } else {
        s = calc_bound_scroll_speed(s - 10, 0, 100)
    }
    game_features.gameopt_scroll_speed = s
}

[es=event_change_middle_mouse_pan_speed]
function event_change_middle_mouse_pan_speed_handler(ev) {
    var s = Math.round(game_features.gameopt_middle_mouse_pan_speed)
    if (ev.increase) {
        s = calc_bound_scroll_speed(s + 10, 0, 100)
    } else {
        s = calc_bound_scroll_speed(s - 10, 0, 100)
    }
    game_features.gameopt_middle_mouse_pan_speed = s
}

[es=event_change_clouds_speed]
function event_change_clouds_speed_handler(ev) {
    var s = Math.round(game_features.gameopt_clouds_speed)
    if (ev.increase) {
        s = calc_bound_scroll_speed(s + 10, 0, 100)
    } else {
        s = calc_bound_scroll_speed(s - 10, 0, 100)
    }
    game_features.gameopt_clouds_speed = s
}

[es=event_toggle_pause]
function event_toggle_pause_handler(ev) {
    game.paused = !game.paused
}

[es=event_change_gamespeed]
function event_change_gamespeed_handler(ev) {
    function calc_bound_game_speed(v, lo, hi) {
        if (v < lo) { return lo }
        if (v > hi) { return hi }
        return v
    }

    var s = Math.round(game_features.gameopt_game_speed)
    if (ev.increase) {
        if (s >= 100) {
            if (s < 1000) { s += 100 }
        } else {
            s = calc_bound_game_speed(s + 10, 10, 100)
        }
    } else {
        if (s > 100) {
            s -= 100
        } else {
            s = calc_bound_game_speed(s - 10, 10, 100)
        }
    }
    game_features.gameopt_game_speed = s
    emit event_update_game_tick_timer{ reserved: 0 }
}

var app_pending_exit_after_save = false

function app_clear_pending_exit_after_save() {
    app_pending_exit_after_save = false
}

function app_open_save_dialog_for_exit() {
    app_pending_exit_after_save = true
    ui.window_city_show()
    window_show_by_id("file_dialog_save")
}

function app_finish_exit_after_save() {
    if (app_pending_exit_after_save) {
        app_pending_exit_after_save = false
        emit event_request_exit{ value: true }
    }
}

[es=event_app_close_requested]
function app_on_close_requested(ev) {
    if (!game_features.gameui_prompt_save_on_exit) {
        emit event_request_exit{ value: true }
        return
    }

    if (game.session_active) {
        if (game_features.gameopt_ironwill) {
            ui.show_yesno("#popup_dialog_quit",
                function() {
                    if (!game_write_ironwill_checkpoint()) {
                        log_warning("Ironwill checkpoint failed on app quit")
                        city.warnings.show("#ironwill_save_failed")
                        return
                    }
                    emit event_request_exit{ value: true }
                },
                function() {
                    // stay in city
                }
            )
            return
        }

        ui.show_yesno("#popup_dialog_quit_without_saving",
            function() {
                emit event_request_exit{ value: true }
            },
            function() {
                app_open_save_dialog_for_exit()
            }
        )
        return
    }

    ui.show_yesno("#popup_dialog_quit", function() {
        emit event_request_exit{ value: true }
    })
}
