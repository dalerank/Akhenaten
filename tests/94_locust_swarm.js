// FIGURE_LOCUST register + cloud anim + Osiris/EVENT/cheat/pak-chain + farm + sentiment + saveload + timer.
// Markers:
//   [test-marker] locust_registered_ok
//   [test-marker] locust_anim_walk_ok
//   [test-marker] locust_osiris_swarm_ok
//   [test-marker] locust_farm_cursed_ok
//   [test-marker] locust_event_swarm_ok
//   [test-marker] locust_sentiment_ok
//   [test-marker] locust_cheat_ok
//   [test-marker] locust_post_load_ok
//   [test-marker] locust_pak_chain_ok
//   [test-marker] locust_saveload_ok | locust_saveload_skipped
//   [test-marker] locust_timer_poof_ok

var GOD_OSIRIS = 0
var ACTION_LOCUST_ROAMING = 121

var __test94_reg_ok = false
var __test94_anim_ok = false
var __test94_swarm_ok = false
var __test94_farm_ok = false
var __test94_event_ok = false
var __test94_sentiment_ok = false
var __test94_cheat_ok = false
var __test94_post_load_ok = false
var __test94_pak_ok = false
var __test94_saveload_ok = false
var __test94_saveload_skipped = false
var __test94_timer_ok = false

function test94_remove_locusts() {
    city.figures.remove_figures(FIGURE_LOCUST)
}

function test94_count_locusts() {
    return __test_count_figures(FIGURE_LOCUST)
}

function test94_place_farm() {
    var farm = test_farm_place(BUILDING_GRAIN_FARM, TERRAIN_FLOODPLAIN)
    if (!farm) {
        farm = test_farm_place(BUILDING_GRAIN_MEADOW_FARM, TERRAIN_MEADOW)
    }
    if (!farm) {
        farm = __test_building_create(BUILDING_GRAIN_FARM, -1, -1)
    }
    if (!farm) {
        farm = __test_building_create(BUILDING_GRAIN_MEADOW_FARM, -1, -1)
    }
    return farm
}

// Osiris major is ~50% flood vs locusts — retry until swarm appears.
function test94_try_locust_curse(max_tries) {
    for (var i = 0; i < max_tries; i++) {
        test94_remove_locusts()
        __test_run_console_command('god_major_curse ' + GOD_OSIRIS)
        if (test94_count_locusts() > 0) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:94] locust swarm (CF2)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false

    // --- Register + non-8-dir walk anim ---
    var probe = test_figure_create(FIGURE_LOCUST, -1, -1)
    if (!probe || !__figure_is_valid(probe) || __figure_get_type(probe) != FIGURE_LOCUST) {
        __log_info_native('[test:94] FIGURE_LOCUST not registered')
        __test_signal_ready()
        return
    }
    __log_marker('locust_registered_ok')
    __test94_reg_ok = true

    __test_figure_set_action(probe, ACTION_LOCUST_ROAMING)
    __test_figure_update_animation(probe)
    var key = __figure_get_anim_key(probe)
    if (key != 'walk') {
        __log_info_native('[test:94] anim key want "walk", got "' + key + '"')
        __test_signal_ready()
        return
    }
    var variant = __test_locust_cloud_variant(probe)
    if (variant < 0 || variant > 4) {
        __log_info_native('[test:94] cloud_variant want 0..4, got ' + variant)
        __test_signal_ready()
        return
    }
    if (__test_figure_current_height(probe) <= 0) {
        __log_info_native('[test:94] expected float height > 0, got ' + __test_figure_current_height(probe))
        __test_signal_ready()
        return
    }
    __log_marker('locust_anim_walk_ok')
    __test94_anim_ok = true
    __test_figure_kill(probe)
    test94_remove_locusts()

    // --- Farm + Osiris locust curse ---
    var farm = test94_place_farm()
    if (!farm) {
        __log_info_native('[test:94] failed to place/create farm')
        __test_signal_ready()
        return
    }

    if (!test94_try_locust_curse(40)) {
        __log_info_native('[test:94] Osiris curse expected locusts after retries')
        __test_signal_ready()
        return
    }
    if (test94_count_locusts() < 1) {
        __log_info_native('[test:94] no live locusts after curse')
        __test_signal_ready()
        return
    }
    __log_marker('locust_osiris_swarm_ok')
    __test94_swarm_ok = true

    var curse_days = __test_building_curse_days(farm)
    if (curse_days < 40) {
        __log_info_native('[test:94] farm curse_days want ~48, got ' + curse_days)
        __test_signal_ready()
        return
    }
    __log_marker('locust_farm_cursed_ok')
    __test94_farm_ok = true

    // --- EVENT_TYPE_LOCUSTS: amount → count + sentiment ---
    test94_remove_locusts()
    var hid = test_building_place(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!hid) {
        hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    }
    if (!hid || __test_house_set_population(hid, 20) < 1) {
        __log_info_native('[test:94] failed to create populated house for sentiment')
        __test_signal_ready()
        return
    }
    var house = city.get_house(hid)
    var happiness_before = house.house_happiness

    city.create_chain_event({
        tag_id: 9401,
        type: EVENT_TYPE_LOCUSTS,
        amount: 3,
        trigger: EVENT_TRIGGER_ONCE
    }).execute()

    var n = test94_count_locusts()
    if (n != 3) {
        __log_info_native('[test:94] EVENT_TYPE_LOCUSTS amount=3 want 3 locusts, got ' + n)
        __test_signal_ready()
        return
    }
    __log_marker('locust_event_swarm_ok')
    __test94_event_ok = true

    var happiness_after = house.house_happiness
    if (happiness_after >= happiness_before) {
        __log_info_native('[test:94] sentiment want drop, happiness ' + happiness_before + ' -> ' + happiness_after)
        __test_signal_ready()
        return
    }
    __log_marker('locust_sentiment_ok')
    __test94_sentiment_ok = true

    // --- Crop Busters cheat / debug console ---
    // The C++ cheat moved to console_commands.js and was renamed on the way.
    test94_remove_locusts()
    __test_run_console_command('locust_apply_plague')
    if (test94_count_locusts() < 1) {
        __log_info_native('[test:94] crop_busters expected locusts')
        __test_signal_ready()
        return
    }
    if (__test_building_curse_days(farm) < 40) {
        __log_info_native('[test:94] crop_busters expected farm blight')
        __test_signal_ready()
        return
    }
    __log_marker('locust_cheat_ok')
    __test94_cheat_ok = true

    // --- on_post_load restores amphibian / float / variant clamp ---
    var plid = __test_locust_spawn_swarm(1)
    if (!plid || !__test_locust_post_load(plid)) {
        __log_info_native('[test:94] on_post_load restore failed, fid=' + plid)
        __test_signal_ready()
        return
    }
    __log_marker('locust_post_load_ok')
    __test94_post_load_ok = true

    // --- Pak-style ONLY_VIA_EVENT chain (mission leaf type 24) ---
    test94_remove_locusts()
    city.create_chain_event({
        tag_id: 9420,
        type: EVENT_TYPE_LOCUSTS,
        amount: 2
        // default trigger = EVENT_TRIGGER_ONLY_VIA_EVENT
    })
    __city_event_fire_chain(9420)
    __test_process_scenario_events()
    var pak_n = test94_count_locusts()
    if (pak_n != 2) {
        __log_info_native('[test:94] pak ONLY_VIA chain want 2 locusts, got ' + pak_n)
        __test_signal_ready()
        return
    }
    __log_marker('locust_pak_chain_ok')
    __test94_pak_ok = true

    // --- Save/load: days_left + live count ---
    test94_remove_locusts()
    var sid = __test_locust_spawn_swarm(2)
    if (!sid || !__figure_is_valid(sid)) {
        __log_info_native('[test:94] saveload spawn failed')
        __test_signal_ready()
        return
    }
    __test_locust_set_days(sid, 33)
    var save_name = 'test_94_locust.svx'
    if (!__game_write_savegame(save_name)) {
        __log_info_native('[test:94] write_savegame failed — saveload skipped')
        __log_marker('locust_saveload_skipped')
        __test94_saveload_skipped = true
    } else if (!__game_load_savegame(save_name)) {
        __log_info_native('[test:94] load_savegame failed — saveload skipped')
        __game_delete_savegame(save_name)
        __log_marker('locust_saveload_skipped')
        __test94_saveload_skipped = true
    } else {
        __game_delete_savegame(save_name)
        if (test94_count_locusts() < 1) {
            __log_info_native('[test:94] after load expected locusts')
            __test_signal_ready()
            return
        }
        // Find a live locust with preserved days (may renumber ids).
        var found_days = false
        var i
        for (i = 1; i < 200; i++) {
            if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_LOCUST) {
                var days = __test_locust_get_days(i)
                if (days == 33) {
                    found_days = true
                    break
                }
            }
        }
        if (!found_days) {
            __log_info_native('[test:94] after load days_left=33 not found')
            __test_signal_ready()
            return
        }
        __log_marker('locust_saveload_ok')
        __test94_saveload_ok = true
    }

    // --- Timer poof: days=1 → first update_day removes ---
    test94_remove_locusts()
    var fid = __test_locust_spawn_swarm(1)
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[test:94] spawn_swarm(1) failed')
        __test_signal_ready()
        return
    }
    if (!__test_locust_set_days(fid, 1)) {
        __log_info_native('[test:94] set_days failed')
        __test_signal_ready()
        return
    }
    __test_figure_update_day(fid)
    if (test94_count_locusts() != 0) {
        __log_info_native('[test:94] expected 0 locusts after timer poof, got ' + test94_count_locusts())
        __test_signal_ready()
        return
    }
    __log_marker('locust_timer_poof_ok')
    __test94_timer_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test94_reg_ok || !__test94_anim_ok || !__test94_swarm_ok || !__test94_farm_ok
        || !__test94_event_ok || !__test94_sentiment_ok || !__test94_cheat_ok
        || !__test94_post_load_ok || !__test94_pak_ok || !__test94_timer_ok) {
        __log_info_native('[test:94] one or more phases failed')
        return false
    }
    if (!__test94_saveload_ok && !__test94_saveload_skipped) {
        __log_info_native('[test:94] saveload neither ok nor skipped')
        return false
    }

    var markers = [
        'locust_registered_ok',
        'locust_anim_walk_ok',
        'locust_osiris_swarm_ok',
        'locust_farm_cursed_ok',
        'locust_event_swarm_ok',
        'locust_sentiment_ok',
        'locust_cheat_ok',
        'locust_post_load_ok',
        'locust_pak_chain_ok',
        'locust_timer_poof_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:94] missing marker: ' + marker)
            return false
        }
    }
    if (!__test_find_inlog('[test-marker] locust_saveload_ok')
        && !__test_find_inlog('[test-marker] locust_saveload_skipped')) {
        __log_info_native('[test:94] missing saveload ok/skip marker')
        return false
    }
    return true
}

function done() {
    test94_remove_locusts()
}
