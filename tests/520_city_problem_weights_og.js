// OG figure_phrase_city_weights (figure/figure_phrase.c): 0/1/4/6/8 weights of the eight city problems, the
// labour pair cancelling its calm side, a defended invasion repeating the food weight and a fired favour invasion
// zeroing the kingdom weight.
// Markers:
//   [test-marker] problem_weights_calm_ok
//   [test-marker] problem_weights_crisis_ok
//   [test-marker] problem_weights_defended_ok
//   [test-marker] problem_weights_favour_ok
//   [test-marker] problem_weights_edges_ok

// health, food months, invasion, defenders, favour sent, allocated, needed, god mood, kingdom, population,
// unemployed, entertainment
var test520_cases = [
    { marker: 'problem_weights_calm_ok', args: [100, 12, 0, 0, 0, 0, 0, 100, 100, 0, 0, 100], want: '1,1,1,0,1,1,1,1,7,1' },
    { marker: 'problem_weights_crisis_ok', args: [15, 0, 1, 0, 0, 70, 100, 25, 0, 1000, 0, 0], want: '8,6,8,8,4,8,0,6,48,0' },
    { marker: 'problem_weights_defended_ok', args: [50, 1, 1, 1, 0, 100, 100, 50, 50, 100, 20, 50], want: '1,4,4,0,1,1,8,1,20,0' },
    { marker: 'problem_weights_favour_ok', args: [100, 12, 0, 0, 1, 0, 0, 100, 0, 0, 0, 100], want: '1,1,1,0,1,0,1,1,6,1' },
    { marker: 'problem_weights_edges_ok', args: [20, 1, 0, 0, 0, 80, 100, 30, 39, 100, 17, 19], want: '6,4,1,6,4,4,6,4,35,0' },
]

function run_test() {
    __log_info_native('[test:520] OG city problem weights')
    test_ensure_city_session('data/default.map')
    for (var i = 0; i < test520_cases.length; i++) {
        var c = test520_cases[i]
        var a = c.args
        var got = __test_city_problem_weights(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11])
        if (got != c.want) {
            __log_info_native('[test:520] ' + c.marker + ' want ' + c.want + ' got ' + got)
            continue
        }
        __log_marker(c.marker)
    }
    __test_signal_ready()
}

function check_valid() {
    for (var i = 0; i < test520_cases.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + test520_cases[i].marker)) {
            return false
        }
    }
    return true
}
