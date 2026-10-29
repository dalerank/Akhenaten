// OG FIG_LEG_AUX=12 (melee infantry), FIG_LEG_HEAVY=13 (chariot).
// Regression: these were swapped (charioteer@12, infantry@13).

function run_test() {
    __log_info_native('[test-leg-aux] infantry=' + FIGURE_INFANTRY
        + ' charioteer=' + FIGURE_FCHARIOTEER
        + ' archer=' + FIGURE_ARCHER)
    __test_signal_ready()
}

function check_valid() {
    return FIGURE_ARCHER == 11
        && FIGURE_INFANTRY == 12
        && FIGURE_FCHARIOTEER == 13
        && __test_find_inlog('[test-leg-aux] infantry=12 charioteer=13 archer=11')
}
