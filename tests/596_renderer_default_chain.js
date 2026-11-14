// Renderer choice: the user's renderer is tried first, then the platform chain, software last;
// a renderer the build does not list is skipped.

var __test596_ok = false

function t596_fail(msg) {
    __log_info_native('[test:596] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:596] renderer default chain')
    var all = 'direct3d,direct3d11,opengl,opengles2,software'

    var auto = __test_render_backend_order('', all).split(',')
    if (auto[auto.length - 1] != 'software') {
        return t596_fail('software is not the last resort: ' + auto.join(','))
    }

    var user = __test_render_backend_order('opengles2', all).split(',')
    if (user[0] != 'opengles2' || user.indexOf('software') < 0) {
        return t596_fail('user choice not first or no fallback: ' + user.join(','))
    }
    for (var i = 0; i < user.length; i++) {
        if (user.indexOf(user[i]) != i) {
            return t596_fail('renderer tried twice: ' + user.join(','))
        }
    }

    var missing = __test_render_backend_order('metal', 'opengl,software').split(',')
    if (missing.indexOf('metal') >= 0 || missing.indexOf('direct3d11') >= 0 || missing.indexOf('software') < 0) {
        return t596_fail('unlisted renderer kept or fallback lost: ' + missing.join(','))
    }

    __log_marker('renderer_default_chain_ok')
    __test596_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test596_ok && __test_find_inlog('[test-marker] renderer_default_chain_ok')
}
