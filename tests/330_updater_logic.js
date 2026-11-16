// The updater's offline logic (src/platform/app_updater.cpp): the GitHub API's time format and run answer, the date
// comparison, the per-platform workflow/artifact, the zip entry checks and the state machine. No network: the
// updater itself is off under --integraltests.
// Markers:
//   [test-marker] updater_off_in_tests
//   [test-marker] updater_time_ok
//   [test-marker] updater_run_ok
//   [test-marker] updater_newer_ok
//   [test-marker] updater_assets_ok
//   [test-marker] updater_paths_ok
//   [test-marker] updater_states_ok

var updater_test_failures = 0

function updater_expect(what, got, want) {
    if (got !== want) {
        __log_info_native('[test:330] ' + what + ': got "' + got + '", want "' + want + '"')
        updater_test_failures++
        return false
    }
    return true
}

function updater_check(marker, body) {
    var before = updater_test_failures
    body()
    if (updater_test_failures == before) {
        __log_marker(marker)
    }
}

var UPDATER_TEST_SHA = 'fed341e419eb3f6a8dbed1776a34dba16909b4b6'
var UPDATER_TEST_RUN = '{\n  "total_count": 1199,\n  "workflow_runs": [\n    {\n      "id": 42909862239,\n'
    + '      "name": "Akhenaten Build Windows",\n      "node_id": "WFR_kwLOJz_Dcs8AAAAJ_aCJXw",\n'
    + '      "head_branch": "master",\n      "head_sha": "' + UPDATER_TEST_SHA + '",\n'
    + '      "pull_requests": [ { "id": 3575805647, "number": 466 } ],\n'
    + '      "created_at": "2026-11-10T21:56:37Z",\n      "updated_at": "2026-11-10T22:15:09Z",\n'
    + '      "head_commit": { "id": "' + UPDATER_TEST_SHA + '", "timestamp": "2026-11-10T20:59:29Z" }\n'
    + '    }\n  ]\n}\n'

function run_test() {
    __log_info_native('[test:330] updater offline logic')

    if (__updater_state() == UPDATER_OFF) {
        __log_marker('updater_off_in_tests')
    }

    updater_check('updater_time_ok', function () {
        updater_expect('epoch', __test_updater_parse_time('1970-01-01T00:00:00Z'), '0')
        updater_expect('run time', __test_updater_parse_time('2026-11-10T21:56:37Z'), '1794347797')
        updater_expect('leap day', __test_updater_parse_time('2024-02-29T12:00:00Z'), '1709208000')
        updater_expect('no zone', __test_updater_parse_time('2026-11-10T21:56:37'), '!')
        updater_expect('bad month', __test_updater_parse_time('2026-13-10T21:56:37Z'), '!')
        updater_expect('empty', __test_updater_parse_time(''), '!')
    })

    updater_check('updater_run_ok', function () {
        updater_expect('run', __test_updater_parse_run(UPDATER_TEST_RUN), '42909862239|' + UPDATER_TEST_SHA + '|1794347797')
        updater_expect('no runs', __test_updater_parse_run('{ "total_count": 0, "workflow_runs": [] }'), '!')
        updater_expect('rate limited', __test_updater_parse_run('{ "message": "API rate limit exceeded" }'), '!')
        updater_expect('short sha', __test_updater_parse_run(UPDATER_TEST_RUN.replace(UPDATER_TEST_SHA, 'fed341e')), '!')
        updater_expect('not json', __test_updater_parse_run('<html>'), '!')
    })

    updater_check('updater_newer_ok', function () {
        var other = '8b5efd08d11f1e5eb5497a21a33e32859d7d7c27'
        updater_expect('same commit', __test_updater_is_newer(UPDATER_TEST_SHA, '1794347797', UPDATER_TEST_SHA, '1794344369'), false)
        updater_expect('later run', __test_updater_is_newer(other, '1794400000', UPDATER_TEST_SHA, '1794344369'), true)
        updater_expect('older run', __test_updater_is_newer(other, '1794300000', UPDATER_TEST_SHA, '1794344369'), false)
        updater_expect('equal time', __test_updater_is_newer(other, '1794344369', UPDATER_TEST_SHA, '1794344369'), false)
        updater_expect('unknown local', __test_updater_is_newer(other, '1794400000', '', '0'), true)
        updater_expect('no remote sha', __test_updater_is_newer('', '1794400000', UPDATER_TEST_SHA, '0'), false)
    })

    updater_check('updater_assets_ok', function () {
        updater_expect('windows', __test_updater_asset(UPDATER_PLATFORM_WINDOWS), 'akhenaten_windows|windows_build|akhenaten.exe')
        updater_expect('linux', __test_updater_asset(UPDATER_PLATFORM_LINUX), 'akhenaten_linux|linux_build|akhenaten.linux')
        updater_expect('mac arm', __test_updater_asset(UPDATER_PLATFORM_MACOS_ARM),
            'akhenaten_mac_arm|macos_arm_build|akhenaten.app/Contents/MacOS/akhenaten')
        updater_expect('mac x64', __test_updater_asset(UPDATER_PLATFORM_MACOS_X64),
            'akhenaten_mac_x64|macos_x64_build|akhenaten.app/Contents/MacOS/akhenaten')
        updater_expect('none', __test_updater_asset(UPDATER_PLATFORM_NONE), '!')
        updater_expect('runs url', __test_updater_runs_url(UPDATER_PLATFORM_WINDOWS),
            'https://api.github.com/repos/dalerank/Akhenaten/actions/workflows/akhenaten_windows.yml/runs'
            + '?branch=master&event=push&status=success&per_page=1')
        updater_expect('download url', __test_updater_download_url(UPDATER_PLATFORM_LINUX, '42909862239'),
            'https://nightly.link/dalerank/Akhenaten/actions/runs/42909862239/linux_build.zip')
        var current = __test_updater_current_platform()
        updater_expect('current platform has builds', current == UPDATER_PLATFORM_NONE || __test_updater_asset(current) != '!', true)
    })

    updater_check('updater_paths_ok', function () {
        updater_expect('plain', __test_updater_safe_path('akhenaten.exe'), 'akhenaten.exe')
        updater_expect('nested', __test_updater_safe_path('data/maps/m_000_nubt.map'), 'data/maps/m_000_nubt.map')
        updater_expect('dot slash', __test_updater_safe_path('./data/default.map'), 'data/default.map')
        updater_expect('backslash', __test_updater_safe_path('data\\default.map'), 'data/default.map')
        updater_expect('dots in name', __test_updater_safe_path('a..b/c'), 'a..b/c')
        updater_expect('parent', __test_updater_safe_path('../evil.exe'), '!')
        updater_expect('inner parent', __test_updater_safe_path('data/../../evil.exe'), '!')
        updater_expect('backslash parent', __test_updater_safe_path('data\\..\\..\\evil.exe'), '!')
        updater_expect('absolute', __test_updater_safe_path('/etc/passwd'), '!')
        updater_expect('drive', __test_updater_safe_path('C:/Windows/evil.dll'), '!')
        updater_expect('unc', __test_updater_safe_path('\\\\host\\share\\evil.dll'), '!')
        updater_expect('double slash', __test_updater_safe_path('data//x'), '!')
        updater_expect('directory', __test_updater_safe_path('data/'), '!')
        updater_expect('empty', __test_updater_safe_path(''), '!')
        updater_expect('has program', __test_updater_has_program('akhenaten.pdb|akhenaten.exe|data/default.map', 'akhenaten.exe'), true)
        updater_expect('no program', __test_updater_has_program('akhenaten.pdb|data/akhenaten.exe', 'akhenaten.exe'), false)
    })

    updater_check('updater_states_ok', function () {
        var next = __test_updater_next_state
        updater_expect('start', next(UPDATER_OFF, UPDATER_EV_START), UPDATER_CHECKING)
        updater_expect('off ignores answers', next(UPDATER_OFF, UPDATER_EV_NEWER_BUILD), UPDATER_OFF)
        updater_expect('no answer', next(UPDATER_CHECKING, UPDATER_EV_NO_ANSWER), UPDATER_NO_ANSWER)
        updater_expect('same build', next(UPDATER_CHECKING, UPDATER_EV_SAME_BUILD), UPDATER_UP_TO_DATE)
        updater_expect('newer build', next(UPDATER_CHECKING, UPDATER_EV_NEWER_BUILD), UPDATER_AVAILABLE)
        updater_expect('no download while checking', next(UPDATER_CHECKING, UPDATER_EV_DOWNLOAD), UPDATER_CHECKING)
        updater_expect('download', next(UPDATER_AVAILABLE, UPDATER_EV_DOWNLOAD), UPDATER_DOWNLOADING)
        updater_expect('one download at a time', next(UPDATER_DOWNLOADING, UPDATER_EV_DOWNLOAD), UPDATER_DOWNLOADING)
        updater_expect('downloaded', next(UPDATER_DOWNLOADING, UPDATER_EV_DOWNLOAD_OK), UPDATER_READY)
        updater_expect('download failed', next(UPDATER_DOWNLOADING, UPDATER_EV_DOWNLOAD_FAILED), UPDATER_FAILED)
        updater_expect('retry', next(UPDATER_FAILED, UPDATER_EV_DOWNLOAD), UPDATER_DOWNLOADING)
        updater_expect('ready stays', next(UPDATER_READY, UPDATER_EV_DOWNLOAD), UPDATER_READY)
        updater_expect('up to date stays', next(UPDATER_UP_TO_DATE, UPDATER_EV_DOWNLOAD), UPDATER_UP_TO_DATE)

        updater_expect('button ready', __test_updater_button(UPDATER_READY), UPDATER_BUTTON_RESTART)
        updater_expect('button available', __test_updater_button(UPDATER_AVAILABLE), UPDATER_BUTTON_DOWNLOAD_THEN_RESTART)
        updater_expect('button failed', __test_updater_button(UPDATER_FAILED), UPDATER_BUTTON_DOWNLOAD_THEN_RESTART)
        updater_expect('button downloading', __test_updater_button(UPDATER_DOWNLOADING), UPDATER_BUTTON_RESTART_WHEN_READY)
        updater_expect('button up to date', __test_updater_button(UPDATER_UP_TO_DATE), UPDATER_BUTTON_NONE)
        updater_expect('button off', __test_updater_button(UPDATER_OFF), UPDATER_BUTTON_NONE)
    })

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'updater_off_in_tests',
        'updater_time_ok',
        'updater_run_ok',
        'updater_newer_ok',
        'updater_assets_ok',
        'updater_paths_ok',
        'updater_states_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:330] missing marker: ' + marker)
            return false
        }
    }
    return true
}
