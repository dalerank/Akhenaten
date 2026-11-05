log_info("akhenaten: building_pottery started")

[es=building_industry]
building_pottery {
    type: BUILDING_POTTERY_WORKSHOP
    animations {
        preview { pos[-1, -1], pack:PACK_GENERAL, id:125 }
        base { pos[-1, -1], pack:PACK_GENERAL, id:125 }
        work { pos[36, -4], pack:PACK_GENERAL, id:125, offset:1, max_frames:18, duration:12 }
    }
    overlay_anims {
        clay {
            pos: [60, 30]
            pack: PACK_GENERAL
            id: 205
            offset: 9
            resource: RESOURCE_CLAY
            stack: true
            step: [5, -5]
            max_count: 8
            default_active: true
        }
    }

    input {
        resource : RESOURCE_CLAY
    }

    output {
        resource : RESOURCE_POTTERY
    }

    production_rate : 20
    production_rate_dcy : [100, 80, 70, 60, 50]
    labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
    building_size : 2
    meta { text_id:126, help_link:"message_potter_history" }
    info_sound : "Wavs/pottery.wav"
    sound_channel : SOUND_CHANNEL_CITY_POTTERY_WORKSHOP
    cost [ 12, 20, 30, 40, 50 ]
    desirability {
        value[-4]
        step[1]
        step_size[1]
        range[4]
    }
    laborers[12]
    fire_risk[4]
    damage_risk[3]
    info_advisors [ADVISOR_LABOR]
    flags {
        is_workshop: true
        is_industry: true
        work_anim: true
    }
}

[es=(building_pottery, on_place_checks)]
function building_pottery_on_place_checks(ev) {
    var clay = city.resources.clay
    var pottery = city.resources.pottery
    var has_supply = (clay.count_active_industry > 0) || (clay.yards_stored > 0) || (pottery.yards_stored > 0)
    if (!has_supply) {
        city.warnings.show("#building_needs_clay")
        if (clay.can_produce) {
            city.warnings.show("#build_clay_pit")
        } else if (clay.can_import) {
            city.warnings.show_if_not(clay.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
        } else if (clay.could_import) {
            city.warnings.show("#setup_trade_route_to_import")
        }
    }
}

[es=(building_pottery, update_graphic)]
function building_pottery_on_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}

[es=(building_pottery, update_animation)]
function building_pottery_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_CLAY) < 100) {
        b.play_animation = false
    }
}
