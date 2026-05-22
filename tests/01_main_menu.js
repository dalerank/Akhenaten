// Verifies that the game reaches the main menu after a clean boot.
// main_menu_screen::show() logs "[test-marker] main_menu_shown" before doing
// any heavy lifting (and before the async changelog HTTP fetch), so by the
// time setup() returns the marker is already in the log file.

function run_test() {
    __test_signal_ready();
}

function check_valid() {
    if (!__test_find_inlog('[test-marker] main_menu_shown')) {
        __log_info_native('main menu marker not found in log');
        return false;
    }
    return true;
}
