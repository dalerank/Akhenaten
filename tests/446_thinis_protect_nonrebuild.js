// Mission 23 protect: Osiris temple complex + mansions are map-only (non-rebuildable).
function run_test() {
    __game_load_mission(23)
    __test_signal_ready()
}

function check_valid() {
    if (__scenario_building_allowed(BUILDING_TEMPLE_COMPLEX_OSIRIS)) {
        return "temple complex Osiris must not be rebuildable"
    }
    if (__scenario_building_allowed(BUILDING_FAMILY_MANSION)) {
        return "family mansion must not be rebuildable"
    }
    if (__scenario_building_allowed(BUILDING_PERSONAL_MANSION)) {
        return "personal mansion must not be rebuildable"
    }
    // Upgrades for the pre-placed complex stay allowed.
    if (!__scenario_building_allowed(BUILDING_TEMPLE_COMPLEX_ALTAR_AMON)) {
        return "Osiris altar upgrade should be allowed"
    }
    if (!__scenario_building_allowed(BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH)) {
        return "Osiris oracle upgrade should be allowed"
    }
    return true
}
