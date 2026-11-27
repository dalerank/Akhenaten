// Reference playthrough of m003 Nekhen: plays REF_M003_PLAN through the build planner day by day until the mission
// is won. A row waits for its month, then for pop (population >= pop), unemployment (unemployment % >= value) and
// after (that building type unlocked). Log: one "[ref:m003] month=N ..." line per month (mood = sentiment / low mood
// cause, workers = employed / unfilled jobs / available, levels = houses at least modest homestead / spacious
// homestead / modest apartment, beer/pottery in storage yards), "placed"/"lost"/"cleared" per build action and
// "result won_month=N". Notes: tmp/reference-playthroughs.md.
var REF_M003_TAG = '[ref:m003]'
var REF_M003_MONTH_CAP = 36
var REF_M003_SEED = 1
var REF_M003_BLOCKED_DAYS = 32
var REF_M003_TICKS_PER_DAY = 50

var REF_M003_PLAN = [
    { month: 0, name: 'road_farm_entry', action: 'road', x: 57, y: 48, x2: 57, y2: 42 },
    { month: 0, name: 'road_farm_row', action: 'road', x: 56, y: 42, x2: 42, y2: 42 },
    { month: 0, name: 'road_street', action: 'road', x: 32, y: 53, x2: 50, y2: 53 },
    { month: 0, name: 'road_east_link', action: 'road', x: 51, y: 50, x2: 51, y2: 68 },
    { month: 0, name: 'road_west_link', action: 'road', x: 33, y: 54, x2: 33, y2: 68 },
    { month: 0, name: 'farm_grain_1', action: 'build', type: BUILDING_GRAIN_FARM, x: 40, y: 39 },
    { month: 0, name: 'farm_grain_2', action: 'build', type: BUILDING_GRAIN_FARM, x: 43, y: 39 },
    { month: 0, name: 'farm_barley_1', action: 'build', type: BUILDING_BARLEY_FARM, x: 46, y: 39 },
    { month: 0, name: 'farm_barley_2', action: 'build', type: BUILDING_BARLEY_FARM, x: 49, y: 39 },
    { month: 0, name: 'farm_barley_3', action: 'build', type: BUILDING_BARLEY_FARM, x: 52, y: 39 },
    { month: 0, name: 'farm_grain_3', action: 'build', type: BUILDING_GRAIN_FARM, x: 48, y: 43 },
    { month: 0, name: 'farm_grain_4', action: 'build', type: BUILDING_GRAIN_FARM, x: 51, y: 43 },
    { month: 0, name: 'firehouse_farms', action: 'build', type: BUILDING_FIREHOUSE, x: 56, y: 45 },
    { month: 0, name: 'architect_farms', action: 'build', type: BUILDING_ARCHITECT_POST, x: 56, y: 46 },
    { month: 0, name: 'work_camp_2', action: 'build', type: BUILDING_WORK_CAMP, x: 55, y: 47 },
    { month: 0, name: 'work_camp_1', action: 'build', type: BUILDING_WORK_CAMP, x: 72, y: 47 },
    { month: 0, name: 'granary', action: 'build', type: BUILDING_GRANARY, x: 60, y: 45 },
    { month: 0, name: 'architect_industry', action: 'build', type: BUILDING_ARCHITECT_POST, x: 58, y: 48 },
    { month: 0, name: 'firehouse_industry', action: 'build', type: BUILDING_FIREHOUSE, x: 59, y: 48 },
    { month: 0, name: 'water_supply_1', action: 'build', type: BUILDING_WATER_SUPPLY, x: 36, y: 51 },
    { month: 0, name: 'lots_north_west', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 37, y: 47, w: 5, h: 2 },
    { month: 0, name: 'lots_north_east', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 43, y: 48, w: 12, h: 1 },
    { month: 0, name: 'lots_target', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 34, y: 54, w: 17, h: 2 },

    { month: 1, pop: 120, name: 'water_supply_2', action: 'build', type: BUILDING_WATER_SUPPLY, x: 46, y: 51 },
    { month: 1, pop: 120, name: 'road_back_street', action: 'road', x: 34, y: 59, x2: 52, y2: 59 },
    { month: 1, pop: 120, name: 'shrine_osiris_1', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 42, y: 60 },
    { month: 1, pop: 120, name: 'shrine_bast_1', action: 'build', type: BUILDING_SHRINE_BAST, x: 43, y: 60 },
    { month: 1, pop: 120, name: 'booth', action: 'build', type: BUILDING_BOOTH, x: 32, y: 53 },
    { month: 1, pop: 120, name: 'juggler_school', action: 'build', type: BUILDING_JUGGLER_SCHOOL, x: 40, y: 60 },

    { month: 2, pop: 250, name: 'storage_yard_1', action: 'build', type: BUILDING_STORAGE_YARD, x: 66, y: 46 },
    { month: 2, pop: 250, name: 'brewery_1', action: 'build', type: BUILDING_BREWERY_WORKSHOP, x: 58, y: 46 },
    { month: 2, pop: 250, name: 'road_south_street', action: 'road', x: 34, y: 65, x2: 50, y2: 65 },
    { month: 2, pop: 250, name: 'lots_south_1', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 34, y: 63, w: 17, h: 2 },
    { month: 2, pop: 250, name: 'police', action: 'build', type: BUILDING_POLICE_STATION, x: 44, y: 60 },
    { month: 2, pop: 250, name: 'firehouse', action: 'build', type: BUILDING_FIREHOUSE, x: 45, y: 60 },
    { month: 2, pop: 250, name: 'architect', action: 'build', type: BUILDING_ARCHITECT_POST, x: 46, y: 60 },

    { month: 4, pop: 400, name: 'brewery_2', action: 'build', type: BUILDING_BREWERY_WORKSHOP, x: 74, y: 47 },
    { month: 4, pop: 400, name: 'storage_yard_2', action: 'build', type: BUILDING_STORAGE_YARD, x: 69, y: 46 },
    { month: 4, pop: 400, name: 'clay_pit', action: 'build', type: BUILDING_CLAY_PIT, x: 58, y: 44 },
    { month: 4, pop: 400, name: 'pottery', action: 'build', type: BUILDING_POTTERY_WORKSHOP, x: 64, y: 47 },
    { month: 4, pop: 400, name: 'bazaar_1', action: 'build', type: BUILDING_BAZAAR, x: 34, y: 51 },

    { month: 6, pop: 500, name: 'temple_ra', action: 'build', type: BUILDING_TEMPLE_RA, x: 34, y: 60 },
    { month: 6, pop: 500, name: 'shrine_osiris_2', action: 'build', type: BUILDING_SHRINE_OSIRIS, x: 47, y: 60 },
    { month: 6, pop: 500, name: 'shrine_bast_2', action: 'build', type: BUILDING_SHRINE_BAST, x: 48, y: 60 },
    { month: 6, pop: 500, name: 'bazaar_2', action: 'build', type: BUILDING_BAZAAR, x: 48, y: 51 },

    { month: 8, pop: 500, name: 'conservatory', action: 'build', type: BUILDING_CONSERVATORY, x: 37, y: 60 },
    { month: 8, pop: 500, name: 'bandstand', action: 'build', type: BUILDING_BANDSTAND, x: 50, y: 57 },
    { month: 10, pop: 500, name: 'village_palace', action: 'build', type: BUILDING_VILLAGE_PALACE, x: 33, y: 45 },

    { month: 10, unemployment: 20, name: 'brewery_3', action: 'build', type: BUILDING_BREWERY_WORKSHOP, x: 64, y: 50 },
    { month: 10, unemployment: 20, name: 'brewery_4', action: 'build', type: BUILDING_BREWERY_WORKSHOP, x: 66, y: 50 },
    { month: 10, unemployment: 20, name: 'granary_2', action: 'build', type: BUILDING_GRANARY, x: 68, y: 50 },
    { month: 10, unemployment: 20, name: 'storage_yard_3', action: 'build', type: BUILDING_STORAGE_YARD, x: 72, y: 50 },
    { month: 14, unemployment: 20, name: 'tax_collector_2', action: 'build', type: BUILDING_TAX_COLLECTOR, x: 30, y: 47 },
    { month: 14, unemployment: 20, name: 'work_camp_3', action: 'build', type: BUILDING_WORK_CAMP, x: 73, y: 53 },
    { month: 14, unemployment: 20, name: 'brewery_5', action: 'build', type: BUILDING_BREWERY_WORKSHOP, x: 73, y: 55 },
    { month: 14, unemployment: 20, name: 'bazaar_3', action: 'build', type: BUILDING_BAZAAR, x: 52, y: 61 },
    { month: 14, unemployment: 20, name: 'apothecary', action: 'build', type: BUILDING_APOTHECARY, x: 52, y: 63 },

    { month: 0, name: 'tax_collector', action: 'build', type: BUILDING_TAX_COLLECTOR, x: 49, y: 60 },
    { month: 0, name: 'physician', action: 'build', type: BUILDING_PHYSICIAN, x: 41, y: 51, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'road_far_south_street', action: 'road', x: 34, y: 68, x2: 50, y2: 68, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'lots_south_2', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 34, y: 66, w: 17, h: 2, after: BUILDING_TAX_COLLECTOR },
    { month: 0, pop: 750, name: 'lots_south_3', action: 'lots', type: BUILDING_HOUSE_VACANT_LOT, x: 34, y: 69, w: 17, h: 2, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_1', action: 'build', type: BUILDING_LARGE_STATUE, x: 34, y: 56, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_2', action: 'build', type: BUILDING_LARGE_STATUE, x: 37, y: 56, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_3', action: 'build', type: BUILDING_LARGE_STATUE, x: 40, y: 56, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_4', action: 'build', type: BUILDING_LARGE_STATUE, x: 43, y: 56, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_5', action: 'build', type: BUILDING_LARGE_STATUE, x: 46, y: 56, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_north_1', action: 'build', type: BUILDING_LARGE_STATUE, x: 38, y: 50, after: BUILDING_TAX_COLLECTOR },
    { month: 0, name: 'statue_north_2', action: 'build', type: BUILDING_LARGE_STATUE, x: 43, y: 50, after: BUILDING_TAX_COLLECTOR },
]

var __ref_m003 = { won_month: -1, failed: '', rows: [] }

function ref_m003_log(msg) {
    __log_info_native(REF_M003_TAG + ' ' + msg)
}

function ref_m003_date() {
    return 'y=' + game.simtime.year + ' m=' + game.simtime.month + ' d=' + game.simtime.day
}

function ref_m003_enter_build_mode(type) {
    emit event_city_building_mode{ value: type }
    __test_process_events()
    return city_planner.build_type == type
}

function ref_m003_exit_build_mode() {
    if (city_planner.in_progress) {
        city_planner.construction_cancel()
    }
    emit event_city_building_mode{ value: BUILDING_NONE }
    __test_process_events()
}

function ref_m003_place_road(row) {
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

function ref_m003_place_lots(row) {
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

function ref_m003_clear_site(row) {
    var size = __building_static_building_size(row.type)
    if (!ref_m003_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return 'build_mode'
    }
    var funds = city.finance.treasury
    city_planner.update(row.x, row.y)
    city_planner.construction_start(row.x, row.y)
    city_planner.construction_update(row.x + size - 1, row.y + size - 1)
    city_planner.construction_finalize()
    ref_m003_exit_build_mode()
    ref_m003_log('cleared ' + row.name + ' ' + ref_m003_date() + ' cost=' + (funds - city.finance.treasury))
    return ''
}

function ref_m003_place_building(row, state) {
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

function ref_m003_run_row(row, state) {
    if (row.action == 'set_tax') {
        __city_taxes.tax_percentage = row.value
        return ''
    }

    var type = row.action == 'road' ? BUILDING_ROAD : row.type
    if (!ref_m003_enter_build_mode(type)) {
        return 'build_mode'
    }
    var funds = city.finance.treasury
    var err
    if (row.action == 'road') {
        err = ref_m003_place_road(row)
    } else if (row.action == 'lots') {
        err = ref_m003_place_lots(row)
    } else {
        err = ref_m003_place_building(row, state)
    }
    ref_m003_exit_build_mode()
    if (!err) {
        ref_m003_log('placed ' + row.name + ' ' + ref_m003_date() + ' cost=' + (funds - city.finance.treasury))
    }
    return err
}

function ref_m003_ready(row, month) {
    if (month < row.month) {
        return false
    }
    if (row.pop && city.population < row.pop) {
        return false
    }
    if (row.unemployment && city.labor.unemployment_percentage < row.unemployment) {
        return false
    }
    if (row.after && !__scenario_building_allowed(row.after)) {
        return false
    }
    if (row.action == 'set_tax' || row.action == 'road') {
        return true
    }
    return !!__scenario_building_allowed(row.type)
}

function ref_m003_fail(msg) {
    __ref_m003.failed = msg
    ref_m003_log('FAIL ' + msg)
    return false
}

function ref_m003_play_rows(month) {
    for (var i = 0; i < REF_M003_PLAN.length; i++) {
        var row = REF_M003_PLAN[i]
        var state = __ref_m003.rows[i]
        if (state.done || !ref_m003_ready(row, month)) {
            continue
        }
        if (state.lost) {
            ref_m003_clear_site(row)
            state.lost = false
        }
        var err = ref_m003_run_row(row, state)
        if (err == 'blocked' && ++state.blocked_days <= REF_M003_BLOCKED_DAYS) {
            continue
        }
        if (err) {
            return ref_m003_fail(row.name + ': ' + err)
        }
        state.done = true
        state.blocked_days = 0
    }
    return true
}

function ref_m003_check_rows() {
    for (var i = 0; i < REF_M003_PLAN.length; i++) {
        var row = REF_M003_PLAN[i]
        var state = __ref_m003.rows[i]
        if (!state.bid) {
            continue
        }
        if (__building_type(state.bid) != row.type) {
            ref_m003_log('lost ' + row.name + ' ' + ref_m003_date())
            state.bid = 0
            state.done = false
            state.lost = true
            continue
        }
        if (state.check_access) {
            state.check_access = false
            if (!city.get_building(state.bid).has_road_access) {
                return ref_m003_fail(row.name + ': no road access')
            }
        }
    }
    return true
}

function ref_m003_reasons() {
    var reasons = city.victory.reasons
    var names = Object.keys(reasons)
    var out = []
    for (var i = 0; i < names.length; i++) {
        out.push(names[i] + '=' + (reasons[names[i]] ? 1 : 0))
    }
    return out.join(',')
}

function ref_m003_levels() {
    return city.count_houses_at_least(HOUSE_MODEST_HOMESTEAD)
        + '/' + city.count_houses_at_least(HOUSE_SPACIOUS_HOMESTEAD)
        + '/' + city.count_houses_at_least(HOUSE_MODEST_APARTMENT)
}

function ref_m003_month_line(month) {
    var wc = city.winning
    return 'month=' + month
        + ' ' + ref_m003_date()
        + ' pop=' + city.population
        + ' funds=' + city.finance.treasury
        + ' taxes=' + __city_finance_income('taxes', true)
        + ' culture=' + city.rating.culture
        + ' prosperity=' + city.rating.prosperity
        + ' monument=' + city.rating.monument
        + ' kingdom=' + city.kingdome.rating
        + ' houses=' + city.total_housing_buildings()
        + ' housing_goal=' + city.count_houses_at_least(wc.housing_level.goal) + '/' + wc.housing_count.goal
        + ' unemployment=' + city.labor.unemployment_percentage
        + ' mood=' + __city_sentiment.value + '/' + __city_sentiment.low_mood_cause
        + ' workers=' + city.labor.workers_employed + '/' + city.labor.workers_needed + '/' + city.labor.workers_available
        + ' levels=' + ref_m003_levels()
        + ' grain=' + city.resources.grain.city_stored
        + ' barley=' + city.resources.barley.city_stored
        + ' beer=' + city.resources.beer.yards_stored
        + ' pottery=' + city.resources.pottery.yards_stored
        + ' flood=' + city.floods.state
        + ' win=' + city.victory.state
        + ' reasons=' + ref_m003_reasons()
}

function ref_m003_run_day() {
    __test_run_ticks(REF_M003_TICKS_PER_DAY)
}

function ref_m003_run_month(month) {
    var start_month = game.simtime.month
    while (game.simtime.month == start_month) {
        if (!ref_m003_play_rows(month)) {
            return 'failed'
        }
        ref_m003_run_day()
        if (!ref_m003_check_rows()) {
            return 'failed'
        }
        if (city.victory.state == 1) {
            return 'won'
        }
    }
    return ''
}

function run_test() {
    __test_crt_srand(REF_M003_SEED)
    __game_load_mission(3, 1)
    __test_random_set_state(REF_M003_SEED, REF_M003_SEED)
    __test_process_events()

    for (var i = 0; i < REF_M003_PLAN.length; i++) {
        __ref_m003.rows.push({ done: false, bid: 0, blocked_days: 0, check_access: false, lost: false })
    }

    ref_m003_log('start difficulty=' + game.difficulty + ' funds=' + city.finance.treasury
        + ' map=' + __scenario_map.width + 'x' + __scenario_map.height)

    for (var month = 0; month < REF_M003_MONTH_CAP; month++) {
        var outcome = ref_m003_run_month(month)
        if (outcome == 'failed') {
            break
        }
        ref_m003_log(ref_m003_month_line(month + 1))
        if (outcome == 'won') {
            __ref_m003.won_month = month + 1
            break
        }
    }

    if (__ref_m003.won_month > 0) {
        ref_m003_log('result won_month=' + __ref_m003.won_month + ' ' + ref_m003_date())
    } else {
        ref_m003_log('result not_won' + (__ref_m003.failed ? ' failed=' + __ref_m003.failed : ''))
    }
    __test_signal_ready()
}

function check_valid() {
    return __ref_m003.won_month > 0
}
