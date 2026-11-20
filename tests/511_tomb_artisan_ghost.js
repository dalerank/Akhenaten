// OG building_artisans_guild_spawn_figure / figure_tomb_artisan_action (construction_worker.c):
// - a guild with a free worker slot and no task still creates an artisan: an invisible corpse (ghost)
//   that holds the slot for 128 ticks and takes no stock; it survives a save/load;
// - count_guild_workers counts a dying artisan, so its corpse holds the slot too;
// - an artisan whose roam ran out with no guild road becomes a corpse instead of vanishing;
// - an artisan at work is visible again once its work site is gone;
// - a roaming artisan draws the city random every tick.
// Each section runs on its own; a failing one logs t511_<section>_fail and the rest still run.
// Markers: t511_ghost_ok t511_slot_held_ok t511_saveload_ok t511_lifetime_ok t511_dying_holds_ok
//   t511_roam_corpse_ok t511_work_visible_ok t511_roam_random_ok

var T760_ROAM = 12
var T760_WORK = 14
var T760_CORPSE = 149
var T760_SECTIONS = ['ghost', 'slot_held', 'saveload', 'lifetime', 'dying_holds', 'roam_corpse', 'work_visible', 'roam_random']

var t760 = { guild: 0, x: 0, y: 0 }

function t511_check(section, ok, detail) {
    if (ok) {
        __log_marker('t511_' + section + '_ok')
    } else {
        __log_info_native('[test:511] ' + section + ': ' + detail)
        __log_marker('t511_' + section + '_fail')
    }
    return ok
}

function t511_slot() {
    var f = city.get_building(t760.guild).get_figure(BUILDING_SLOT_SERVICE)
    return (f && f.valid && f.type == FIGURE_TOMB_ARTISAN) ? f.id : 0
}

function t511_reset_guild() {
    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    var g = city.get_building(t760.guild)
    g.num_workers = Math.ceil(g.max_workers / 4)
    g.consume_resource(RESOURCE_CLAY, g.stored_resource(RESOURCE_CLAY) - 100)
    g.consume_resource(RESOURCE_PAINT, g.stored_resource(RESOURCE_PAINT) - 100)
}

function t511_artisan(action) {
    var fid = __test_figure_create(FIGURE_TOMB_ARTISAN, t760.x, t760.y + 3)
    __test_figure_set_home(fid, t760.guild)
    __test_figure_set_action(fid, action)
    __test_figure_set_wait_ticks(fid, 0)
    return fid
}

function t511_clear_roads(radius) {
    for (var y = t760.y - radius; y <= t760.y + radius; y++) {
        for (var x = t760.x - radius; x <= t760.x + radius; x++) {
            terrain.remove({ x: x, y: y }, TERRAIN_ROAD)
        }
    }
    __test_update_road_network()
}

function t511_ghost_sections() {
    t511_reset_guild()
    __test_building_spawn_figure(t760.guild)
    var ghost = t511_slot()
    var g = city.get_building(t760.guild)
    var count = __test_count_figures(FIGURE_TOMB_ARTISAN)
    if (!t511_check('ghost', ghost && count == 1 && __test_figure_is_visible(ghost) == 0 && __test_figure_get_action(ghost) == T760_CORPSE
            && g.stored_resource(RESOURCE_CLAY) == 100 && g.stored_resource(RESOURCE_PAINT) == 100,
            'ghost=' + ghost + ' count=' + count + ' visible=' + __test_figure_is_visible(ghost) + ' action=' + __test_figure_get_action(ghost)
            + ' clay=' + g.stored_resource(RESOURCE_CLAY) + ' paint=' + g.stored_resource(RESOURCE_PAINT))) {
        return
    }

    __test_building_spawn_figure(t760.guild)
    t511_check('slot_held', __test_count_figures(FIGURE_TOMB_ARTISAN) == 1 && t511_slot() == ghost,
        'count=' + __test_count_figures(FIGURE_TOMB_ARTISAN) + ' slot=' + t511_slot())

    for (var i = 0; i < 60; i++) {
        __test_figure_action_perform(ghost)
    }
    var save_name = 'test_760_ghost.svx'
    var saved = __test_save_memory(save_name) && __test_load_memory(save_name)
    __test_drop_memory_save(save_name)
    t511_check('saveload', saved && __test_figure_is_alive(ghost) == 1 && __test_figure_is_visible(ghost) == 0
        && __test_figure_get_action(ghost) == T760_CORPSE && __test_figure_get_wait_ticks(ghost) == 60,
        'saved=' + saved + ' alive=' + __test_figure_is_alive(ghost) + ' visible=' + __test_figure_is_visible(ghost)
        + ' action=' + __test_figure_get_action(ghost) + ' wait=' + __test_figure_get_wait_ticks(ghost))
    city.get_building(t760.guild).num_workers = Math.ceil(city.get_building(t760.guild).max_workers / 4)

    for (var i = 60; i < 127; i++) {
        __test_figure_action_perform(ghost)
    }
    var alive_127 = __test_figure_is_alive(ghost)
    __test_figure_action_perform(ghost)
    var alive_128 = __test_figure_is_alive(ghost)
    __test_building_spawn_figure(t760.guild)
    var next = t511_slot()
    t511_check('lifetime', alive_127 == 1 && alive_128 != 1 && next && __test_figure_get_wait_ticks(next) == 0,
        'alive at 127=' + alive_127 + ' at 128=' + alive_128 + ' next=' + next + ' wait=' + __test_figure_get_wait_ticks(next))
}

function t511_dying_section() {
    t511_reset_guild()
    var dying = t511_artisan(T760_ROAM)
    __test_figure_kill(dying)
    var is_dying = __test_figure_is_dying(dying)
    __test_building_spawn_figure(t760.guild)
    var count = __test_count_figures(FIGURE_TOMB_ARTISAN)
    t511_check('dying_holds', is_dying == 1 && count == 0, 'dying=' + is_dying + ' count=' + count)
}

function t511_roam_corpse_section() {
    t511_reset_guild()
    var roamer = t511_artisan(T760_ROAM)
    __test_figure_set_roam_length(roamer, __test_figure_type_max_roam(FIGURE_TOMB_ARTISAN) - 1)
    __test_figure_action_perform(roamer)
    t511_check('roam_corpse', __test_figure_is_alive(roamer) == 1 && __test_figure_get_action(roamer) == T760_CORPSE
        && __test_figure_is_visible(roamer) == 1,
        'alive=' + __test_figure_is_alive(roamer) + ' action=' + __test_figure_get_action(roamer) + ' visible=' + __test_figure_is_visible(roamer))
}

function t511_work_visible_section() {
    t511_reset_guild()
    var worker = t511_artisan(T760_WORK)
    __test_figure_set_visible(worker, 0)
    __test_figure_action_perform(worker)
    t511_check('work_visible', __test_figure_get_action(worker) == T760_ROAM && __test_figure_is_visible(worker) == 1,
        'action=' + __test_figure_get_action(worker) + ' visible=' + __test_figure_is_visible(worker))
}

function t511_roam_random_section() {
    t511_reset_guild()
    var walker = t511_artisan(T760_ROAM)
    __test_random_set_state(12345, 67890)
    __test_figure_action_perform(walker)
    var after_one = __test_random_iv1()
    __test_random_set_state(12345, 67890)
    __test_random_generate_next()
    var want = __test_random_iv1()
    t511_check('roam_random', after_one == want, 'iv1=' + after_one + ' want ' + want)
}

function run_test() {
    __log_info_native('[test:511] tomb artisan ghost')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_ARTISANS_GUILD)) {
        __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)
    }
    t760.guild = test_building_place(BUILDING_ARTISANS_GUILD, -1, -1)
    if (!t760.guild) {
        __log_marker('t511_place_fail')
        __test_signal_ready()
        return
    }
    t760.x = __building_tile(t760.guild).x
    t760.y = __building_tile(t760.guild).y
    t511_clear_roads(6)

    t511_ghost_sections()
    t511_dying_section()
    t511_roam_corpse_section()
    t511_work_visible_section()
    t511_roam_random_section()
    __test_signal_ready()
}

function check_valid() {
    var ok = !__test_find_inlog('[test-marker] t511_place_fail')
    for (var i = 0; i < T760_SECTIONS.length; i++) {
        if (!__test_find_inlog('[test-marker] t511_' + T760_SECTIONS[i] + '_ok')) {
            __log_info_native('[test:511] missing marker t511_' + T760_SECTIONS[i] + '_ok')
            ok = false
        }
    }
    return ok
}
