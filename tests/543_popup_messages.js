// NT*: OG Popup Messages — category map + banner vs modal delivery.
// Markers:
//   [test-marker] popup_messages_category_map_ok
//   [test-marker] popup_messages_banner_unread_ok
//   [test-marker] popup_messages_banner_click_open_ok
//   [test-marker] popup_messages_modal_read_ok
//   [test-marker] popup_messages_unlisted_modal_ok

var POPUP_MSG_EMPLOYEES = 11
var POPUP_MSG_PRICE = 6

function find_last_message_key(key) {
    var total = __city_message_count()
    for (var i = total - 1; i >= 0; i--) {
        if (__lang_get_message_id(__city_message_mm_text_id(i)) == key) {
            return i
        }
    }
    return -1
}

function dismiss_message_dialog_if_open() {
    // Modal city message leaves a dialog on the stack; close so the next
    // use_popup can hit show_message_popup (marks read) instead of enqueue.
    var i
    for (i = 0; i < 4; i++) {
        window_go_back()
    }
}

function run_test() {
    __log_info_native('[test:543] popup messages filter')
    test_ensure_city_session('data/default.map')

    var prev_mask = Math.round(game_features.gameopt_popup_messages)

    var cat_emp = __popup_message_category_for_key('message_employees_needed')
    var cat_price = __popup_message_category_for_key('message_price_increased')
    var cat_wage = __popup_message_category_for_key('message_kingdome_raises_wages')
    var cat_trade = __popup_message_category_for_key('message_increased_trading')
    var cat_comply = __popup_message_category_for_key('message_storage_yards_ready_to_fulfill_request')
    var cat_none = __popup_message_category_for_key('message_fire_in_the_village')
    var cat_tmpl = __popup_message_category_for_key('message_template_general')
    if (cat_emp != POPUP_MSG_EMPLOYEES || cat_price != POPUP_MSG_PRICE || cat_wage != 8 || cat_trade != 7
        || cat_comply != 2 || cat_none != -1 || cat_tmpl != -1) {
        __log_info_native('[test:543] category map mismatch emp=' + cat_emp + ' price=' + cat_price
            + ' wage=' + cat_wage + ' trade=' + cat_trade + ' comply=' + cat_comply
            + ' none=' + cat_none + ' tmpl=' + cat_tmpl)
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    // Event-shell + random wage/price stubs must resolve.
    if (__lang_get_message_uid('message_template_general') == 0
        || __lang_get_message_uid('message_kingdome_raises_wages') == 0
        || __lang_get_message_uid('message_price_increased') == 0
        || __lang_get_message_uid('message_trade_stopped') == 0) {
        __log_info_native('[test:543] missing game_messages stubs for template/wage/price/trade')
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    __log_marker('popup_messages_category_map_ok')

    // Banner path: bit set → archive entry stays unread (no modal).
    __popup_messages_set_banner(POPUP_MSG_EMPLOYEES, true)
    if (!__popup_messages_want_banner(POPUP_MSG_EMPLOYEES)) {
        __log_info_native('[test:543] want_banner not set')
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }

    var before = __city_message_count()
    ui.popup_message('message_employees_needed')
    __test_process_events()
    var after = __city_message_count()
    if (after != before + 1) {
        __log_info_native('[test:543] banner post did not append message before=' + before + ' after=' + after)
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    var idx = find_last_message_key('message_employees_needed')
    if (idx < 0 || __city_message_is_read(idx)) {
        __log_info_native('[test:543] banner message should be unread idx=' + idx)
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    __log_marker('popup_messages_banner_unread_ok')

    // I1: banner click path — open archive entry by sequence → marks read.
    var seq = __city_message_sequence(idx)
    var found = __city_message_find_index_by_sequence(seq)
    if (found != idx) {
        __log_info_native('[test:543] sequence lookup failed seq=' + seq + ' found=' + found + ' idx=' + idx)
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    __city_message_show_from_archive(found)
    if (!__city_message_is_read(found)) {
        __log_info_native('[test:543] show_from_archive should mark read')
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    __log_marker('popup_messages_banner_click_open_ok')
    dismiss_message_dialog_if_open()

    // Modal path for same category with bit clear → show_message_popup marks read.
    __popup_messages_set_banner(POPUP_MSG_EMPLOYEES, false)
    before = __city_message_count()
    ui.popup_message('message_employees_needed')
    __test_process_events()
    after = __city_message_count()
    idx = find_last_message_key('message_employees_needed')
    if (after != before + 1 || idx < 0 || !__city_message_is_read(idx)) {
        __log_info_native('[test:543] modal message should be marked read idx=' + idx + ' after=' + after)
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    __log_marker('popup_messages_modal_read_ok')

    dismiss_message_dialog_if_open()

    // Unlisted key always modal even if mask is all-ones.
    game_features.gameopt_popup_messages = 0xffff
    before = __city_message_count()
    ui.popup_message('message_fire_in_the_village')
    __test_process_events()
    idx = find_last_message_key('message_fire_in_the_village')
    if (__city_message_count() != before + 1 || idx < 0 || !__city_message_is_read(idx)) {
        __log_info_native('[test:543] unlisted should stay modal/read idx=' + idx + ' count=' + __city_message_count())
        game_features.gameopt_popup_messages = prev_mask
        __test_signal_ready()
        return
    }
    __log_marker('popup_messages_unlisted_modal_ok')

    dismiss_message_dialog_if_open()
    game_features.gameopt_popup_messages = prev_mask
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'popup_messages_category_map_ok',
        'popup_messages_banner_unread_ok',
        'popup_messages_banner_click_open_ok',
        'popup_messages_modal_read_ok',
        'popup_messages_unlisted_modal_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            return false
        }
    }
    return true
}
