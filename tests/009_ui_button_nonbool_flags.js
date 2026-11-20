// Regression test for a hard crash in __ui_draw_button.
//
// The "take config as bvariant_map" refactor made __ui_draw_button read the
// `border` and `body` keys through bvariant::as_bool(). Several button configs
// pass these keys as non-bool values (e.g. body:"" in the chief advisor,
// border:3 in the population/housing advisors, body:2 in the campaign selection).
// as_bool() does std::get<bool> on a variant that does not hold a bool, which
// throws bad_variant_access and aborts the whole process under -fno-exceptions.
//
// The fix only honours these keys when they are an actual bool (disable the
// border/body when explicitly false, otherwise keep the default). This data-less
// check draws buttons with non-bool border/body and asserts the process survives.

function run_test() {
    try {
        // non-bool body (string) + non-bool border (number) -- used to abort here
        __ui_draw_button({ text: "x", pos: [0, 0], size: [20, 20], body: "", border: 3 });
        // non-bool body (number)
        __ui_draw_button({ text: "y", pos: [0, 0], size: [20, 20], body: 2 });
        // explicit false must still be honoured (no crash, disables border/body)
        __ui_draw_button({ text: "z", pos: [0, 0], size: [20, 20], body: false, border: false });
    } catch (e) {
        // a catchable JS error is acceptable -- the regression we guard against is a
        // non-recoverable abort that would kill the process before we get here.
        __log_info_native("[btnflags] threw (non-fatal): " + e);
    }

    __log_info_native("[btnflags] survived");
    __test_signal_ready();
}

function check_valid() {
    return __test_find_inlog("[btnflags] survived");
}
