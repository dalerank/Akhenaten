var REF_M001_TAG = '[ref:m001]'
var REF_M001_MONTH_CAP = 15
var REF_M001_SEED = 1
var REF_M001_BLOCKED_DAYS = 32
var REF_M001_TICKS_PER_DAY = 50

var REF_M001_PLAN = [
    { month: 0, name: 'road_street', action: 'road', x: 37, y: 56, x2: 54, y2: 56 },
    { month: 0, name: 'road_west_link', action: 'road', x: 38, y: 55, x2: 38, y2: 59 },
    { month: 0, name: 'road_east_link', action: 'road', x: 52, y: 57, x2: 52, y2: 59 },
    { month: 0, name: 'road_mines_south', action: 'road', x: 25, y: 61, x2: 25, y2: 70 },
    { month: 0, name: 'road_mines_east', action: 'road', x: 26, y: 70, x2: 31, y2: 72 },
    { month: 0, name: 'road_hunt', action: 'road', x: 64, y: 61, x2: 64, y2: 74 },
    { month: 0, name: 'lots_target', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 39, y: 57, w: 12, h: 1 },
    { month: 0, name: 'lots_workers', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 26, y: 61, w: 14, h: 2 },
    { month: 0, name: 'lots_hunters', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 65, y: 62, w: 2, h: 8 },
    { month: 0, name: 'granary', action: 'build', type: BUILDING_GRANARY, x: 56, y: 61 },
    { month: 0, name: 'bazaar', action: 'build', type: BUILDING_BAZAAR, x: 50, y: 54 },
    { month: 0, name: 'hunting_lodge_1', action: 'build', type: BUILDING_HUNTING_LODGE, x: 65, y: 73 },
    { month: 0, name: 'hunting_lodge_2', action: 'build', type: BUILDING_HUNTING_LODGE, x: 62, y: 73 },
    { month: 0, name: 'hunting_lodge_3', action: 'build', type: BUILDING_HUNTING_LODGE, x: 62, y: 71 },
    { month: 0, name: 'architect_hunt', action: 'build', type: BUILDING_ARCHITECT_POST, x: 63, y: 70 },
    { month: 0, name: 'firehouse_hunt', action: 'build', type: BUILDING_FIREHOUSE, x: 63, y: 69 },
    { month: 0, name: 'water_supply_1', action: 'build', type: BUILDING_WATER_SUPPLY, x: 47, y: 54 },
    { month: 0, name: 'water_supply_2', action: 'build', type: BUILDING_WATER_SUPPLY, x: 53, y: 54 },
    { month: 0, name: 'village_palace', action: 'build', type: BUILDING_VILLAGE_PALACE, x: 39, y: 52 },
    { month: 0, name: 'gold_mine_1', action: 'build', type: BUILDING_GOLD_MINE, x: 24, y: 71 },
    { month: 0, name: 'gold_mine_2', action: 'build', type: BUILDING_GOLD_MINE, x: 32, y: 73 },
    { month: 0, name: 'firehouse', action: 'build', type: BUILDING_FIREHOUSE, x: 36, y: 59 },
    { month: 0, name: 'architect', action: 'build', type: BUILDING_ARCHITECT_POST, x: 37, y: 59 },
    { month: 0, name: 'temple_bast', action: 'build', type: BUILDING_TEMPLE_BAST, x: 44, y: 53 },
    { month: 0, name: 'shrine_1', action: 'build', type: BUILDING_SHRINE_BAST, x: 40, y: 59 },
    { month: 0, name: 'shrine_2', action: 'build', type: BUILDING_SHRINE_BAST, x: 42, y: 59 },
    { month: 0, name: 'shrine_3', action: 'build', type: BUILDING_SHRINE_BAST, x: 44, y: 59 },
    { month: 0, name: 'shrine_4', action: 'build', type: BUILDING_SHRINE_BAST, x: 46, y: 59 },
    { month: 0, name: 'shrine_5', action: 'build', type: BUILDING_SHRINE_BAST, x: 48, y: 59 },
    { month: 0, name: 'shrine_6', action: 'build', type: BUILDING_SHRINE_BAST, x: 50, y: 59 },
    { month: 0, name: 'juggler_school', action: 'build', type: BUILDING_JUGGLER_SCHOOL, x: 53, y: 57 },
    { month: 0, name: 'booth', action: 'build', type: BUILDING_BOOTH, x: 37, y: 55 },
]

var __ref_m001 = { won_month: -1, failed: '', rows: [] }

function ref_m001_log(msg) {
    __log_info_native(REF_M001_TAG + ' ' + msg)
}

function ref_m001_date() {
    return 'y=' + game.simtime.year + ' m=' + game.simtime.month + ' d=' + game.simtime.day
}

function ref_m001_enter_build_mode(type) {
    emit event_city_building_mode{ value: type }
    __test_process_events()
    return city_planner.build_type == type
}

function ref_m001_exit_build_mode() {
    if (city_planner.in_progress) {
        city_planner.construction_cancel()
    }
    emit event_city_building_mode{ value: BUILDING_NONE }
    __test_process_events()
}

function ref_m001_place_road(row) {
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

function ref_m001_place_lots(row) {
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

function ref_m001_clear_site(row) {
    var size = __building_static_building_size(row.type)
    if (!ref_m001_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return 'build_mode'
    }
    var funds = city.finance.treasury
    city_planner.update(row.x, row.y)
    city_planner.construction_start(row.x, row.y)
    city_planner.construction_update(row.x + size - 1, row.y + size - 1)
    city_planner.construction_finalize()
    ref_m001_exit_build_mode()
    ref_m001_log('cleared ' + row.name + ' ' + ref_m001_date() + ' cost=' + (funds - city.finance.treasury))
    return ''
}

function ref_m001_place_building(row, state) {
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

function ref_m001_run_row(row, state) {
    if (row.action == 'set_tax') {
        city.finance.tax_percentage = row.value
        return ''
    }

    var type = row.action == 'road' ? BUILDING_ROAD : row.type
    if (!ref_m001_enter_build_mode(type)) {
        return 'build_mode'
    }
    var funds = city.finance.treasury
    var err
    if (row.action == 'road') {
        err = ref_m001_place_road(row)
    } else if (row.action == 'lots') {
        err = ref_m001_place_lots(row)
    } else {
        err = ref_m001_place_building(row, state)
    }
    ref_m001_exit_build_mode()
    if (!err) {
        ref_m001_log('placed ' + row.name + ' ' + ref_m001_date() + ' cost=' + (funds - city.finance.treasury))
    }
    return err
}

function ref_m001_ready(row, month) {
    if (month < row.month) {
        return false
    }
    if (row.action == 'set_tax' || row.action == 'road') {
        return true
    }
    return !!__scenario_building_allowed(row.type)
}

function ref_m001_fail(msg) {
    __ref_m001.failed = msg
    ref_m001_log('FAIL ' + msg)
    return false
}

function ref_m001_play_rows(month) {
    for (var i = 0; i < REF_M001_PLAN.length; i++) {
        var row = REF_M001_PLAN[i]
        var state = __ref_m001.rows[i]
        if (state.done || !ref_m001_ready(row, month)) {
            continue
        }
        if (state.lost) {
            ref_m001_clear_site(row)
            state.lost = false
        }
        var err = ref_m001_run_row(row, state)
        if (err == 'blocked' && ++state.blocked_days <= REF_M001_BLOCKED_DAYS) {
            continue
        }
        if (err) {
            return ref_m001_fail(row.name + ': ' + err)
        }
        state.done = true
        state.blocked_days = 0
    }
    return true
}

function ref_m001_check_rows() {
    for (var i = 0; i < REF_M001_PLAN.length; i++) {
        var row = REF_M001_PLAN[i]
        var state = __ref_m001.rows[i]
        if (!state.bid) {
            continue
        }
        if (__building_type(state.bid) != row.type) {
            ref_m001_log('lost ' + row.name + ' ' + ref_m001_date())
            state.bid = 0
            state.done = false
            state.lost = true
            continue
        }
        if (state.check_access) {
            state.check_access = false
            if (!city.get_building(state.bid).has_road_access) {
                return ref_m001_fail(row.name + ': no road access')
            }
        }
    }
    return true
}

function ref_m001_reasons() {
    var reasons = city.victory.reasons
    var names = Object.keys(reasons)
    var out = []
    for (var i = 0; i < names.length; i++) {
        out.push(names[i] + '=' + (reasons[names[i]] ? 1 : 0))
    }
    return out.join(',')
}

function ref_m001_month_line(month) {
    var wc = city.winning
    return 'month=' + month
        + ' ' + ref_m001_date()
        + ' pop=' + city.population
        + ' funds=' + city.finance.treasury
        + ' culture=' + city.rating.culture
        + ' prosperity=' + city.rating.prosperity
        + ' monument=' + city.rating.monument
        + ' kingdom=' + city.kingdome.rating
        + ' houses=' + city.total_housing_buildings()
        + ' housing_goal=' + city.count_houses_at_least(wc.housing_level.goal) + '/' + wc.housing_count.goal
        + ' unemployment=' + city.labor.unemployment_percentage
        + ' gamemeat=' + city.resources.gamemeat.city_stored
        + ' gold=' + city.finance.this_year.income.gold_delivered
        + ' win=' + city.victory.state
        + ' reasons=' + ref_m001_reasons()
}

function ref_m001_run_day() {
    __test_run_ticks(REF_M001_TICKS_PER_DAY)
}

function ref_m001_run_month(month) {
    var start_month = game.simtime.month
    while (game.simtime.month == start_month) {
        if (!ref_m001_play_rows(month)) {
            return 'failed'
        }
        ref_m001_run_day()
        if (!ref_m001_check_rows()) {
            return 'failed'
        }
        if (city.victory.state == 1) {
            return 'won'
        }
    }
    return ''
}

function run_test() {
    __test_crt_srand(REF_M001_SEED)
    __game_load_mission(1, 1)
    __test_random_set_state(REF_M001_SEED, REF_M001_SEED)
    __test_process_events()

    for (var i = 0; i < REF_M001_PLAN.length; i++) {
        __ref_m001.rows.push({ done: false, bid: 0, blocked_days: 0, check_access: false, lost: false })
    }

    ref_m001_log('start difficulty=' + game.difficulty + ' funds=' + city.finance.treasury
        + ' map=' + __scenario_map.width + 'x' + __scenario_map.height)

    for (var month = 0; month < REF_M001_MONTH_CAP; month++) {
        var outcome = ref_m001_run_month(month)
        if (outcome == 'failed') {
            break
        }
        ref_m001_log(ref_m001_month_line(month + 1))
        if (outcome == 'won') {
            __ref_m001.won_month = month + 1
            break
        }
    }

    if (__ref_m001.won_month > 0) {
        ref_m001_log('result won_month=' + __ref_m001.won_month + ' ' + ref_m001_date())
    } else {
        ref_m001_log('result not_won' + (__ref_m001.failed ? ' failed=' + __ref_m001.failed : ''))
    }
    __test_signal_ready()
}

function check_valid() {
    return __ref_m001.won_month > 0
}
