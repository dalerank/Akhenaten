log_info("akhenaten: building_architect_post started")


building_architect_post {
    animations {
        _pack {pack:PACK_GENERAL}
        preview { id:81 },
        base { id:81 },
        work { pos[20, -35], id:81, offset:1, max_frames:11 },
    }
    labor_category : LABOR_CATEGORY_INFRASTRUCTURE
    overlay: OVERLAY_DAMAGE
    sound_channel : SOUND_CHANNEL_CITY_ENGINEERS_POST
    min_houses_coverage : 50
    building_size : 1
    meta { help_id: 81, text_id: 104 }
    cost [ 6, 12, 25, 40, 60 ]
    laborers[5], fire_risk[2], damage_risk[0]
    flags {
        is_infrastructure: true
    }
}

[es=(building_architect_post, spawn_figure)]
function building_architect_post_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_ARCHITECT, building_architect_post.min_houses_coverage, ACTION_1_ENGINEER_CREATED)
}

[es=(building_architect_post, update_graphic)]
function building_architect_post_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.can_play_animation() ? "work" : "none"
    building.set_animation(animkey)
}
