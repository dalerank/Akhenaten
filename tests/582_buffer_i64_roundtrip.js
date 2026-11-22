// Save binds of BIND_SIGNATURE_INT64 / UINT64 (building flags) go through buffer::write_i64/read_i64 and the u64
// pair: a value written must read back unchanged.

var __test582_ok = false

function run_test() {
    var cases = [
        ['0', '0/0'],
        ['1', '1/1'],
        ['-1', '-1/18446744073709551615'],
        ['1099511627776', '1099511627776/1099511627776'],
        ['123456789012345678', '123456789012345678/123456789012345678'],
        ['-9000000000000000000', '-9000000000000000000/9446744073709551616']
    ]
    for (var i = 0; i < cases.length; i++) {
        var got = __test_buffer_roundtrip_i64(cases[i][0])
        if (got != cases[i][1]) {
            __log_info_native('[test:582] FAIL: ' + cases[i][0] + ' read back as ' + got + ', expected ' + cases[i][1])
            __test_signal_ready()
            return
        }
    }
    __log_marker('buffer_i64_roundtrip_ok')
    __test582_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test582_ok && __test_find_inlog('[test-marker] buffer_i64_roundtrip_ok')
}
