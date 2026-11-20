// OG FIG_LEG_HEAVY (13): charioteer id, charge layout 0x0F, speed_mult=2 in soldier.js.

function run_test() {
    __log_info_native('[test-leg-heavy] id=' + FIGURE_FCHARIOTEER
        + ' layout_charge=' + FORMATION_CHARGE
        + ' column=' + FORMATION_COLUMN)
    __test_signal_ready()
}

function check_valid() {
    return FIGURE_FCHARIOTEER == 13
        && FORMATION_CHARGE == 15
        && FORMATION_COLUMN == 0
        && __test_find_inlog('[test-leg-heavy] id=13 layout_charge=15 column=0')
}
