var REF_M002_TAG = '[ref:m002]'
var REF_M002_MONTH_CAP = 30
var REF_M002_SEED = 1
var REF_M002_BLOCKED_DAYS = 32
var REF_M002_TICKS_PER_DAY = 50

var REF_M002_PLAN = [
    { month: 0, name: 'road_workers', action: 'road', x: 40, y: 59, x2: 55, y2: 59 },
    { month: 0, name: 'road_farm_link', action: 'road', x: 69, y: 66, x2: 78, y2: 66 },
    { month: 0, name: 'road_farm_entry', action: 'road', x: 74, y: 65, x2: 74, y2: 60 },
    { month: 0, name: 'road_farm_row', action: 'road', x: 63, y: 60, x2: 77, y2: 60 },
    { month: 0, name: 'road_street', action: 'road', x: 42, y: 70, x2: 67, y2: 70 },
    { month: 0, name: 'road_street_east', action: 'road', x: 67, y: 70, x2: 68, y2: 70 },
    { month: 0, name: 'road_west_link', action: 'road', x: 43, y: 70, x2: 43, y2: 73 },
    { month: 0, name: 'road_back_street', action: 'road', x: 44, y: 73, x2: 58, y2: 73 },
    { month: 0, name: 'road_east_link', action: 'road', x: 58, y: 71, x2: 58, y2: 72 },
    { month: 0, name: 'road_industry', action: 'road', x: 31, y: 56, x2: 38, y2: 56 },
    { month: 0, name: 'farm_1', action: 'build', type: BUILDING_FIGS_FARM, x: 62, y: 57 },
    { month: 0, name: 'farm_2', action: 'build', type: BUILDING_FIGS_FARM, x: 65, y: 57 },
    { month: 0, name: 'farm_3', action: 'build', type: BUILDING_FIGS_FARM, x: 68, y: 57 },
    { month: 0, name: 'farm_4', action: 'build', type: BUILDING_FIGS_FARM, x: 71, y: 57 },
    { month: 0, name: 'farm_5', action: 'build', type: BUILDING_FIGS_FARM, x: 75, y: 57 },
    { month: 0, name: 'farm_6', action: 'build', type: BUILDING_FIGS_FARM, x: 71, y: 61 },
    { month: 0, name: 'farm_7', action: 'build', type: BUILDING_FIGS_FARM, x: 75, y: 61 },
    { month: 0, name: 'work_camp_1', action: 'build', type: BUILDING_WORK_CAMP, x: 75, y: 67 },
    { month: 0, name: 'work_camp_2', action: 'build', type: BUILDING_WORK_CAMP, x: 77, y: 67 },
    { month: 0, name: 'granary', action: 'build', type: BUILDING_GRANARY, x: 69, y: 67 },
    { month: 0, name: 'lots_farm_north', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 41, y: 57, w: 14, h: 2 },
    { month: 4, name: 'lots_farm_south', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 41, y: 60, w: 10, h: 2 },
    { month: 0, name: 'lots_farmhands', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 69, y: 71, w: 1, h: 14 },
    { month: 0, name: 'lots_target', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 44, y: 71, w: 14, h: 1 },
    { month: 0, name: 'lots_back', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 44, y: 74, w: 15, h: 1 },
    { month: 4, name: 'lots_back_2', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 44, y: 75, w: 15, h: 1 },
    { month: 4, name: 'lots_farmhands_2', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 70, y: 71, w: 1, h: 14 },
    { month: 0, name: 'temple_osiris', action: 'build', type: BUILDING_TEMPLE_OSIRIS, x: 44, y: 67 },
    { month: 0, name: 'water_supply_1', action: 'build', type: BUILDING_WATER_SUPPLY, x: 47, y: 68 },
    { month: 0, name: 'village_palace', action: 'build', type: BUILDING_VILLAGE_PALACE, x: 49, y: 66 },
    { month: 0, name: 'bazaar', action: 'build', type: BUILDING_BAZAAR, x: 53, y: 68 },
    { month: 0, name: 'water_supply_2', action: 'build', type: BUILDING_WATER_SUPPLY, x: 55, y: 68 },
    { month: 0, name: 'juggler_school', action: 'build', type: BUILDING_JUGGLER_SCHOOL, x: 57, y: 68 },
    { month: 0, name: 'booth', action: 'build', type: BUILDING_BOOTH, x: 42, y: 70 },
    { month: 0, name: 'firehouse', action: 'build', type: BUILDING_FIREHOUSE, x: 59, y: 69 },
    { month: 0, name: 'architect', action: 'build', type: BUILDING_ARCHITECT_POST, x: 60, y: 69 },
    { month: 0, name: 'firehouse_farms', action: 'build', type: BUILDING_FIREHOUSE, x: 73, y: 67 },
    { month: 0, name: 'architect_farms', action: 'build', type: BUILDING_ARCHITECT_POST, x: 74, y: 67 },
    { month: 0, name: 'shrine_1', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 44, y: 72 },
    { month: 0, name: 'shrine_2', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 46, y: 72 },
    { month: 0, name: 'shrine_3', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 48, y: 72 },
    { month: 0, name: 'shrine_4', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 50, y: 72 },
    { month: 0, name: 'shrine_5', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 52, y: 72 },
    { month: 0, name: 'shrine_6', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 54, y: 72 },
    { month: 0, name: 'shrine_7', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 56, y: 72 },
    { month: 0, name: 'clay_pit_1', action: 'build', type: BUILDING_CLAY_PIT, x: 31, y: 57 },
    { month: 0, name: 'clay_pit_2', action: 'build', type: BUILDING_CLAY_PIT, x: 33, y: 54 },
    { month: 0, name: 'pottery_1', action: 'build', type: BUILDING_POTTERY_WORKSHOP, x: 35, y: 54 },
    { month: 0, name: 'pottery_2', action: 'build', type: BUILDING_POTTERY_WORKSHOP, x: 37, y: 54 },
    { month: 0, name: 'storage_yard_1', action: 'build', type: BUILDING_STORAGE_YARD, x: 33, y: 57 },
    { month: 0, name: 'storage_yard_2', action: 'build', type: BUILDING_STORAGE_YARD, x: 36, y: 57 },
]

var __ref_m002 = { won_month: -1, failed: '', rows: [] }

function ref_m002_log(msg) {
    __log_info_native(REF_M002_TAG + ' ' + msg)
}

function ref_m002_date() {
    return 'y=' + game.simtime.year + ' m=' + game.simtime.month + ' d=' + game.simtime.day
}

function ref_m002_enter_build_mode(type) {
    emit event_city_building_mode{ value: type }
    __test_process_events()
    return city_planner.build_type == type
}

function ref_m002_exit_build_mode() {
    if (city_planner.in_progress) {
        city_planner.construction_cancel()
    }
    emit event_city_building_mode{ value: BUILDING_NONE }
    __test_process_events()
}

function ref_m002_place_road(row) {
    var start = { x: row.x, y: row.y }
    var end = { x: row.x2, y: row.y2 }
    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, start)) {
        return 'no_routing'
    }
    var preview = routed_building.preview_path(ROUTED_BUILDING_ROAD, start, end)
    if (!preview.ok) {
        return 'no_path'
    }
    city_planner.update(end.x, end.y)
    city_planner.construction_start(start.x, start.y)
    city_planner.construction_update(end.x, end.y)
    city_planner.construction_finalize()
    for (var i = 0; i < preview.tiles.length; i++) {
        if (!terrain.is(preview.tiles[i], TERRAIN_ROAD)) {
            return 'not_road:' + preview.tiles[i].x + ',' + preview.tiles[i].y
        }
    }
    return ''
}

function ref_m002_place_lots(row) {
    var x2 = row.x + row.w - 1
    var y2 = row.y + row.h - 1
    var before = city.count_total_buildings(row.type)
    city_planner.update(row.x, row.y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        return 'cannot_place'
    }
    city_planner.construction_start(row.x, row.y)
    city_planner.construction_update(x2, y2)
    city_planner.construction_finalize()
    var placed = city.count_total_buildings(row.type) - before
    if (placed != row.w * row.h) {
        return 'placed ' + placed + '/' + (row.w * row.h)
    }
    return ''
}

function ref_m002_clear_site(row) {
    var size = __building_static_building_size(row.type)
    if (!ref_m002_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return 'build_mode'
    }
    var funds = city.finance.treasury
    city_planner.update(row.x, row.y)
    city_planner.construction_start(row.x, row.y)
    city_planner.construction_update(row.x + size - 1, row.y + size - 1)
    city_planner.construction_finalize()
    ref_m002_exit_build_mode()
    ref_m002_log('cleared ' + row.name + ' ' + ref_m002_date() + ' cost=' + (funds - city.finance.treasury))
    return ''
}

function ref_m002_place_building(row, state) {
    city_planner.update(row.x, row.y)
    var can = city_planner.can_be_placed()
    if (can != CAN_PLACE) {
        return can == CAN_NOT_BUT_GREEN ? 'blocked' : 'cannot_place'
    }
    city_planner.construction_start(row.x, row.y)
    city_planner.construction_update(row.x, row.y)
    city_planner.construction_finalize()
    var bid = city_planner.last_created_building_id()
    city_planner.validate_last_created()
    if (!bid || __building_type(bid) != row.type) {
        return 'not_created'
    }
    state.bid = bid
    state.check_access = true
    return ''
}

function ref_m002_run_row(row, state) {
    if (row.action == 'set_tax') {
        __city_taxes.tax_percentage = row.value
        return ''
    }

    var type = row.action == 'road' ? BUILDING_ROAD : row.type
    if (!ref_m002_enter_build_mode(type)) {
        return 'build_mode'
    }
    var funds = city.finance.treasury
    var err
    if (row.action == 'road') {
        err = ref_m002_place_road(row)
    } else if (row.action == 'lots') {
        err = ref_m002_place_lots(row)
    } else {
        err = ref_m002_place_building(row, state)
    }
    ref_m002_exit_build_mode()
    if (!err) {
        ref_m002_log('placed ' + row.name + ' ' + ref_m002_date() + ' cost=' + (funds - city.finance.treasury))
    }
    return err
}

function ref_m002_ready(row, month) {
    if (month < row.month) {
        return false
    }
    if (row.action == 'set_tax' || row.action == 'road') {
        return true
    }
    return !!__scenario_building_allowed(row.type)
}

function ref_m002_fail(msg) {
    __ref_m002.failed = msg
    ref_m002_log('FAIL ' + msg)
    return false
}

function ref_m002_play_rows(month) {
    for (var i = 0; i < REF_M002_PLAN.length; i++) {
        var row = REF_M002_PLAN[i]
        var state = __ref_m002.rows[i]
        if (state.done || !ref_m002_ready(row, month)) {
            continue
        }
        if (state.lost) {
            ref_m002_clear_site(row)
            state.lost = false
        }
        var err = ref_m002_run_row(row, state)
        if (err == 'blocked' && ++state.blocked_days <= REF_M002_BLOCKED_DAYS) {
            continue
        }
        if (err) {
            return ref_m002_fail(row.name + ': ' + err)
        }
        state.done = true
        state.blocked_days = 0
    }
    return true
}

function ref_m002_check_rows() {
    for (var i = 0; i < REF_M002_PLAN.length; i++) {
        var row = REF_M002_PLAN[i]
        var state = __ref_m002.rows[i]
        if (!state.bid) {
            continue
        }
        if (__building_type(state.bid) != row.type) {
            ref_m002_log('lost ' + row.name + ' ' + ref_m002_date())
            state.bid = 0
            state.done = false
            state.lost = true
            continue
        }
        if (state.check_access) {
            state.check_access = false
            if (!city.get_building(state.bid).has_road_access) {
                return ref_m002_fail(row.name + ': no road access')
            }
        }
    }
    return true
}

function ref_m002_reasons() {
    var reasons = city.victory.reasons
    var names = Object.keys(reasons)
    var out = []
    for (var i = 0; i < names.length; i++) {
        out.push(names[i] + '=' + (reasons[names[i]] ? 1 : 0))
    }
    return out.join(',')
}

function ref_m002_granary_figs() {
    var most = 0
    for (var i = 0; i < REF_M002_PLAN.length; i++) {
        var state = __ref_m002.rows[i]
        if (REF_M002_PLAN[i].type == BUILDING_GRANARY && state.bid) {
            var granary = city.get_granary(state.bid)
            var amount = granary ? granary.amount(RESOURCE_FIGS) : 0
            most = Math.max(most, amount)
        }
    }
    return most
}

function ref_m002_month_line(month) {
    var wc = city.winning
    return 'month=' + month
        + ' ' + ref_m002_date()
        + ' pop=' + city.population
        + ' funds=' + city.finance.treasury
        + ' culture=' + city.rating.culture
        + ' prosperity=' + city.rating.prosperity
        + ' monument=' + city.rating.monument
        + ' kingdom=' + city.kingdome.rating
        + ' houses=' + city.total_housing_buildings()
        + ' housing_goal=' + city.count_houses_at_least(wc.housing_level.goal) + '/' + wc.housing_count.goal
        + ' unemployment=' + city.labor.unemployment_percentage
        + ' figs=' + city.resources.figs.city_stored
        + ' granary_figs=' + ref_m002_granary_figs()
        + ' pottery=' + city.resources.pottery.yards_stored
        + ' flood=' + city.floods.state
        + ' win=' + city.victory.state
        + ' reasons=' + ref_m002_reasons()
}

function ref_m002_run_day() {
    __test_run_ticks(REF_M002_TICKS_PER_DAY)
}

function ref_m002_run_month(month) {
    var start_month = game.simtime.month
    while (game.simtime.month == start_month) {
        if (!ref_m002_play_rows(month)) {
            return 'failed'
        }
        ref_m002_run_day()
        if (!ref_m002_check_rows()) {
            return 'failed'
        }
        if (city.victory.state == 1) {
            return 'won'
        }
    }
    return ''
}

function run_test() {
    __test_crt_srand(REF_M002_SEED)
    __game_load_mission(2, 1)
    __test_random_set_state(REF_M002_SEED, REF_M002_SEED)
    __test_process_events()

    for (var i = 0; i < REF_M002_PLAN.length; i++) {
        __ref_m002.rows.push({ done: false, bid: 0, blocked_days: 0, check_access: false, lost: false })
    }

    ref_m002_log('start difficulty=' + game.difficulty + ' funds=' + city.finance.treasury
        + ' map=' + __scenario_map.width + 'x' + __scenario_map.height)

    for (var month = 0; month < REF_M002_MONTH_CAP; month++) {
        var outcome = ref_m002_run_month(month)
        if (outcome == 'failed') {
            break
        }
        ref_m002_log(ref_m002_month_line(month + 1))
        if (outcome == 'won') {
            __ref_m002.won_month = month + 1
            break
        }
    }

    if (__ref_m002.won_month > 0) {
        ref_m002_log('result won_month=' + __ref_m002.won_month + ' ' + ref_m002_date())
    } else {
        ref_m002_log('result not_won' + (__ref_m002.failed ? ' failed=' + __ref_m002.failed : ''))
    }
    __test_signal_ready()
}

function check_valid() {
    return __ref_m002.won_month > 0
}
