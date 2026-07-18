log_info("akhenaten: building_work_camp started")

building_work_camp = {
    animations {
        preview { pos : [0, 0], pack:PACK_GENERAL, id:77 }
        base { pos : [0, 0], pack:PACK_GENERAL, id:77 }
        work { pos : [ 25, -12], pack:PACK_GENERAL, id:77, offset:1, max_frames:19, can_reverse:true, duration:3 }
        minimap {pack:PACK_GENERAL, id:149, offset:160}
    }

    labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
    meta { help_id: 81, text_id: 179 }
    info_sound : "Wavs/eng_r.wav"
    building_size : 2
    cost [ 12, 20, 40, 80, 120 ]
    desirability { value [-3], step [1], step_size [1], range [3] }
    laborers [20]
    fire_risk [4]
    damage_risk [2]

    flags {
    }

    search_radius : 100
}

function building_work_camp_tile_dist_sq(a, b) {
    var xx = b.x - a.x
    var yy = b.y - a.y
    return xx * xx + yy * yy
}

building_work_camp.nearest_eligible_farm = function(building) {
    if (!city.floods.state_is(FLOOD_STATE_FARMABLE)) {
        return 0
    }

    var camp_tile = building.tile
    var mindist_sq = 9999
    var result = 0
    var farms = city.find_farms(camp_tile, building_work_camp.search_radius)

    for (var i = 0; i < farms.length; i++) {
        var farm = city.get_farm(farms[i])
        if (!farm || !farm.is_floodplain) {
            continue
        }
        if (!farm.has_road_access || !farm.requested_workers()) {
            continue
        }

        var dist_sq = building_work_camp_tile_dist_sq(camp_tile, farm.tile)
        if (dist_sq < mindist_sq) {
            mindist_sq = dist_sq
            result = farm.id
        }
    }

    return result
}

building_work_camp.nearest_eligible_monument = function(building) {
    var camp_tile = building.tile
    var mindist_sq = 9999
    var result = 0
    var monuments = city.find_monuments(camp_tile, building_work_camp.search_radius)

    for (var i = 0; i < monuments.length; i++) {
        var monument = city.get_monument(monuments[i])
        if (!monument || !monument.need_workers() || monument.phase() >= 2) {
            continue
        }

        var dist_sq = building_work_camp_tile_dist_sq(camp_tile, monument.tile)
        if (dist_sq < mindist_sq) {
            mindist_sq = dist_sq
            result = monument.id
        }
    }

    return result
}

[es=(building_work_camp, spawn_figure)]
function building_work_camp_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    var min_coverage = building.params.min_houses_coverage

    if (!building.common_spawn_figure_trigger(min_coverage, BUILDING_SLOT_SERVICE)) {
        return
    }

    if (game_features.gameplay_change_work_camp_one_worker_per_month && building.spawned_worker_this_month) {
        return
    }

    var dest_id = building_work_camp.nearest_eligible_farm(building)
    if (!dest_id) {
        dest_id = building_work_camp.nearest_eligible_monument(building)
    }

    if (!dest_id) {
        return
    }

    var figure_id = building.create_figure_with_destination(FIGURE_LABORER, dest_id, ACTION_9_WORKER_CREATED, BUILDING_SLOT_SERVICE)
    if (!figure_id) {
        return
    }

    building.spawned_worker_this_month = 1
    city.get_building(dest_id).add_workers(figure_id)
}

[es=(building_work_camp, update_month)]
function building_work_camp_update_month(ev) {
    city.get_building(ev.bid).spawned_worker_this_month = 0
}

[es=(building_work_camp, update_graphic)]
function building_work_camp_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}
