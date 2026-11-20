// Renderer choice: the user's renderer is tried first, then the platform chain (opengl first on Windows),
// software last; a renderer the build does not list is skipped.

var __test440_ok = false

function t440_fail(msg) {
    __log_info_native('[test:440] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:440] renderer default chain')
    var all = 'direct3d,direct3d11,opengl,opengles2,software'

    var auto = __test_render_backend_order('', all).split(',')
    if (auto[auto.length - 1] != 'software') {
        return t440_fail('software is not the last resort: ' + auto.join(','))
    }
    if (__platform_is_windows() && auto[0] != 'opengl') {
        return t440_fail('opengl is not the first renderer on Windows: ' + auto.join(','))
    }

    var user = __test_render_backend_order('opengles2', all).split(',')
    if (user[0] != 'opengles2' || user.indexOf('software') < 0) {
        return t440_fail('user choice not first or no fallback: ' + user.join(','))
    }
    for (var i = 0; i < user.length; i++) {
        if (user.indexOf(user[i]) != i) {
            return t440_fail('renderer tried twice: ' + user.join(','))
        }
    }

    var missing = __test_render_backend_order('metal', 'opengl,software').split(',')
    if (missing.indexOf('metal') >= 0 || missing.indexOf('direct3d11') >= 0 || missing.indexOf('software') < 0) {
        return t440_fail('unlisted renderer kept or fallback lost: ' + missing.join(','))
    }

    __log_marker('renderer_default_chain_ok')
    __test440_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test440_ok && __test_find_inlog('[test-marker] renderer_default_chain_ok')
}
