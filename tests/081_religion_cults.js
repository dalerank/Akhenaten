// Enhanced religion cults / festival calendar (RC1–RC4).
// Markers:
//   [test-marker] religion_cults_flags_off_ok
//   [test-marker] religion_cults_calendar_rite_ok
//   [test-marker] religion_cults_inactive_without_altar_ok
//   [test-marker] religion_cults_active_with_altar_ok
//   [test-marker] religion_cults_festival_appeased_ok
//   [test-marker] religion_cults_theme_effect_ok

var LOCAL_CULT_ANUBIS = 1
var FESTIVAL_THEME_HARVEST = 1
var FESTIVAL_THEME_CRAFT = 3

function run_test() {
    __log_info_native('[test:081] religion cults / festival calendar')
    test_ensure_city_session('data/default.map')

    var prev_cal = game_features.get('gameplay_enhanced_festival_calendar')
    var prev_cult = game_features.get('gameplay_enhanced_local_cults')
    function finish() {
        game_features.set('gameplay_enhanced_festival_calendar', prev_cal)
        game_features.set('gameplay_enhanced_local_cults', prev_cult)
        __test_signal_ready()
    }

    if (game_features.default('gameplay_enhanced_festival_calendar')
        || game_features.default('gameplay_enhanced_local_cults')) {
        __log_info_native('[test:081] flags default should be OFF')
        finish()
        return
    }
    __log_marker('religion_cults_flags_off_ok')

    game_features.set('gameplay_enhanced_festival_calendar', true)
    game_features.set('gameplay_enhanced_local_cults', true)
    city.local_cults.unlock_all()
    city.local_cults.refresh()

    __city_local_cults.farm_bonus_months = 0
    __city_local_cults.last_rite_year = -1
    __city_local_cults.last_rite_month = 255
    __city_local_cults.last_rite_index = 255
    __game_simtime.month = 6
    city.local_cults.advance_month()
    if (__city_local_cults.farm_bonus_months < 1) {
        __log_info_native('[test:081] calendar rite should set farm_bonus_months, got '
            + __city_local_cults.farm_bonus_months)
        finish()
        return
    }
    __log_marker('religion_cults_calendar_rite_ok')

    city.local_cults.set_unlocked(LOCAL_CULT_ANUBIS, true)
    city.local_cults.refresh()
    if (city.local_cults.is_active(LOCAL_CULT_ANUBIS)) {
        __log_info_native('[test:081] anubis should be inactive without altar')
        finish()
        return
    }
    __log_marker('religion_cults_inactive_without_altar_ok')

    __scenario_building_allow(BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, true)
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var altar_id = __test_building_create(BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, cx, cy)
    if (!altar_id) {
        __log_info_native('[test:081] failed to create anubis altar')
        finish()
        return
    }
    city.local_cults.refresh()
    if (!city.local_cults.is_active(LOCAL_CULT_ANUBIS)) {
        __log_info_native('[test:081] anubis should be active with altar count='
            + city.count_active_buildings(BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS))
        finish()
        return
    }
    __log_marker('religion_cults_active_with_altar_ok')

    city.local_cults.apply_cult_festival(LOCAL_CULT_ANUBIS, FESTIVAL_THEME_HARVEST)
    if (city.local_cults.appeased_months(LOCAL_CULT_ANUBIS) < 1) {
        __log_info_native('[test:081] cult festival should set appeased_months')
        finish()
        return
    }
    __log_marker('religion_cults_festival_appeased_ok')

    __city_local_cults.craft_bonus_months = 0
    city.local_cults.apply_theme(FESTIVAL_THEME_CRAFT, 2)
    if (__city_local_cults.craft_bonus_months < 1) {
        __log_info_native('[test:081] craft theme should set craft_bonus_months')
        finish()
        return
    }
    __log_marker('religion_cults_theme_effect_ok')

    __log_info_native('[test:081] ok')
    finish()
}

function check_valid() {
    var markers = [
        'religion_cults_flags_off_ok',
        'religion_cults_calendar_rite_ok',
        'religion_cults_inactive_without_altar_ok',
        'religion_cults_active_with_altar_ok',
        'religion_cults_festival_appeased_ok',
        'religion_cults_theme_effect_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:081] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
