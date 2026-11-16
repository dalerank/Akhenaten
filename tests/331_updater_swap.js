// The updater's file swap (updater::swap_in / drop_asides / remove_leftovers) on a scratch install folder under the
// system temp folder, never the game's own: new files move in and old ones to *.old, a failure partway rolls every
// file back, and the next start removes what update_old.txt lists. Also reads a streamed zip as the download is.
// Markers:
//   [test-marker] updater_swap_moves_in
//   [test-marker] updater_swap_drops_asides
//   [test-marker] updater_swap_rolls_back
//   [test-marker] updater_swap_cleans_leftovers
//   [test-marker] updater_zip_streamed_ok

var updater_swap_failures = 0

// A streamed zip (sizes only in the data descriptors and the central directory), as GitHub serves its artifacts,
// with mixed-case names; written by Python's zipfile to a non-seekable stream.
var UPDATER_STREAMED_ZIP = '504b0304140008000800dcbc6b5d00000000000000000000000026000000616b68656e6174656e2e6170702f436f6e74656e'
    + '74732f4d61634f532f416b68656e6174656e2b28ca4f2f4acc552818a43400504b07086570e3620d000000a0000000504b03'
    + '04140008000800dcbc6b5d0000000000000000000000000d000000646174612f5061636b2e7367782b484cce5648492c4904'
    + '00504b0708c4ddf09f0b00000009000000504b01021400140008000800dcbc6b5d6570e3620d000000a00000002600000000'
    + '00000000000000800100000000616b68656e6174656e2e6170702f436f6e74656e74732f4d61634f532f416b68656e617465'
    + '6e504b01021400140008000800dcbc6b5dc4ddf09f0b000000090000000d0000000000000000000000800161000000646174'
    + '612f5061636b2e736778504b050600000000020002008f000000a70000000000'

function updater_swap_expect(what, got, want) {
    if (got !== want) {
        __log_info_native('[test:331] ' + what + ': got "' + got + '", want "' + want + '"')
        updater_swap_failures++
    }
}

function updater_swap_step(marker, body) {
    var before = updater_swap_failures
    body()
    if (updater_swap_failures == before) {
        __log_marker(marker)
    }
}

function run_test() {
    __log_info_native('[test:331] updater swap on a scratch folder')
    var root = __test_updater_scratch()
    var install = root + '/install'
    var staging = root + '/staging'

    __test_updater_write(install + '/akhenaten.exe', 'old program')
    __test_updater_write(install + '/data/pack.sgx', 'old pack')
    __test_updater_write(install + '/data/maps/m_000.map', 'old map')
    __test_updater_write(install + '/keep.cfg', 'player settings')
    __test_updater_write(staging + '/akhenaten.exe', 'new program')
    __test_updater_write(staging + '/data/pack.sgx', 'new pack')
    __test_updater_write(staging + '/data/maps/m_000.map', 'new map')
    __test_updater_write(staging + '/data/new_file.txt', 'added')

    updater_swap_step('updater_swap_moves_in', function () {
        updater_swap_expect('swap', __test_updater_swap(staging, install), true)
        updater_swap_expect('program', __test_updater_read(install + '/akhenaten.exe'), 'new program')
        updater_swap_expect('pack', __test_updater_read(install + '/data/pack.sgx'), 'new pack')
        updater_swap_expect('map', __test_updater_read(install + '/data/maps/m_000.map'), 'new map')
        updater_swap_expect('added', __test_updater_read(install + '/data/new_file.txt'), 'added')
        updater_swap_expect('untouched', __test_updater_read(install + '/keep.cfg'), 'player settings')
        updater_swap_expect('old program aside', __test_updater_read(install + '/akhenaten.exe.old'), 'old program')
        updater_swap_expect('old pack aside', __test_updater_read(install + '/data/pack.sgx.old'), 'old pack')
        updater_swap_expect('old map aside', __test_updater_read(install + '/data/maps/m_000.map.old'), 'old map')
        updater_swap_expect('no aside for a new file', __test_updater_exists(install + '/data/new_file.txt.old'), false)
        updater_swap_expect('staging emptied', __test_updater_exists(staging + '/akhenaten.exe'), false)
    })

    updater_swap_step('updater_swap_drops_asides', function () {
        __test_updater_drop_asides(root + '/update_old.txt')
        updater_swap_expect('program aside removed', __test_updater_exists(install + '/akhenaten.exe.old'), false)
        updater_swap_expect('map aside removed', __test_updater_exists(install + '/data/maps/m_000.map.old'), false)
        updater_swap_expect('nothing left to list', __test_updater_exists(root + '/update_old.txt'), false)
    })

    // "zz/blocked.txt" sorts last and cannot be placed: the install has a file named "zz"
    var install2 = root + '/install2'
    var staging2 = root + '/staging2'
    __test_updater_write(install2 + '/akhenaten.exe', 'old program')
    __test_updater_write(install2 + '/data/pack.sgx', 'old pack')
    __test_updater_write(install2 + '/zz', 'a file, not a folder')
    __test_updater_write(staging2 + '/akhenaten.exe', 'new program')
    __test_updater_write(staging2 + '/data/pack.sgx', 'new pack')
    __test_updater_write(staging2 + '/data/new_file.txt', 'added')
    __test_updater_write(staging2 + '/zz/blocked.txt', 'cannot land')

    updater_swap_step('updater_swap_rolls_back', function () {
        updater_swap_expect('swap fails', __test_updater_swap(staging2, install2), false)
        updater_swap_expect('program restored', __test_updater_read(install2 + '/akhenaten.exe'), 'old program')
        updater_swap_expect('pack restored', __test_updater_read(install2 + '/data/pack.sgx'), 'old pack')
        updater_swap_expect('added file removed', __test_updater_exists(install2 + '/data/new_file.txt'), false)
        updater_swap_expect('blocker kept', __test_updater_read(install2 + '/zz'), 'a file, not a folder')
        updater_swap_expect('no program aside', __test_updater_exists(install2 + '/akhenaten.exe.old'), false)
        updater_swap_expect('no pack aside', __test_updater_exists(install2 + '/data/pack.sgx.old'), false)
    })

    updater_swap_step('updater_swap_cleans_leftovers', function () {
        var list = root + '/install/update_old.txt'
        __test_updater_write(install + '/akhenaten.exe.old', 'locked last time')
        __test_updater_write(install + '/old_bundle.app.old/Contents/x', 'a folder')
        __test_updater_write(list, install + '/akhenaten.exe.old\r\n' + install + '/old_bundle.app.old\n')
        __test_updater_remove_leftovers(list)
        updater_swap_expect('file removed', __test_updater_exists(install + '/akhenaten.exe.old'), false)
        updater_swap_expect('folder removed', __test_updater_exists(install + '/old_bundle.app.old'), false)
        updater_swap_expect('list removed', __test_updater_exists(list), false)
        updater_swap_expect('program kept', __test_updater_read(install + '/akhenaten.exe'), 'new program')
    })

    updater_swap_step('updater_zip_streamed_ok', function () {
        var zip = root + '/streamed.zip'
        updater_swap_expect('zip written', __test_updater_write_hex(zip, UPDATER_STREAMED_ZIP), true)
        updater_swap_expect('names keep their case', __test_updater_zip_names(zip), 'akhenaten.app/Contents/MacOS/Akhenaten|data/Pack.sgx')
        var program = ''
        for (var i = 0; i < 20; i++) {
            program += 'program '
        }
        updater_swap_expect('first entry', __test_updater_zip_read(zip, 0), program)
        updater_swap_expect('second entry', __test_updater_zip_read(zip, 1), 'pack data')
    })

    __test_updater_scratch()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'updater_swap_moves_in',
        'updater_swap_drops_asides',
        'updater_swap_rolls_back',
        'updater_swap_cleans_leftovers',
        'updater_zip_streamed_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:331] missing marker: ' + marker)
            return false
        }
    }
    return true
}
