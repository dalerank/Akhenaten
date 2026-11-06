// Free play lists remake mission*.js configs (Pharaoh + Cleopatra), not campaign.txt alone.

function run_test() {
    var mock = {
        items: [],
        add_item: function(title, sid) {
            this.items.push({ title: title, sid: sid | 0 })
            this.items_count = this.items.length
        },
        items_count: 0
    }

    var first = scenario_selection_add_free_play_missions(mock)
    __log_info_native('[test:242] free_play items_count=' + mock.items_count + ' first=' + first)

    if (mock.items_count >= 40) {
        __log_info_native('[test-marker] free_play_list_size_ok')
    } else {
        __log_info_native('[test:242] list too short: ' + mock.items_count)
    }

    var want = [10, 48, 52]
    for (var w = 0; w < want.length; w++) {
        var sid = want[w]
        var found = false
        for (var i = 0; i < mock.items.length; i++) {
            if (mock.items[i].sid === sid) {
                found = true
                break
            }
        }
        if (found) {
            __log_info_native('[test-marker] free_play_has_mission_' + sid)
        } else {
            __log_info_native('[test:242] missing mission ' + sid)
        }
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] free_play_list_size_ok')
        && __test_find_inlog('[test-marker] free_play_has_mission_10')
        && __test_find_inlog('[test-marker] free_play_has_mission_48')
        && __test_find_inlog('[test-marker] free_play_has_mission_52')
}
