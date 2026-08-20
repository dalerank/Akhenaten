log_info("akhenaten: industry office window started")

function industry_office_info_window_refresh(bid) {
    var window = city.object_info
    if (!window || window.bid != bid) {
        return
    }
    industry_office_info_window_init(window)
}

[es=building_info_window]
industry_office_info_window {
    related_buildings [BUILDING_INDUSTRY_OFFICE]
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 18]}),
        resource_icon  : resource_icon({pos: [32, 100] }),
        resource_stored : text({pos: [60, 100], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        managed_text   : text({pos: [32, 120], size: [px(27), 20], font : FONT_NORMAL_BLACK_ON_LIGHT }),
        mothball_all   : button({pos: [32, 230], size: [px(12), 25], text: "#industry_office_mothball_all" }),
        unmothball_all : button({pos: [px(15), 230], size: [px(12), 25], text: "#industry_office_unmothball_all" }),
        inner_panel    : inner_panel({pos : [16, 145], size: [27, 5],
            ui : {
                workers_img  : image({pack:PACK_GENERAL, id:134, offset:14, pos:[20, 10] }),
                workers_text : text({pos: [50, 16], text:"${building.num_workers} ${8.12} (${model.laborers} ${69.0}", font: FONT_NORMAL_BLACK_ON_DARK}),
                workers_desc : text({pos: [50, 32], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
            }
        }),
    })
}

[es=(industry_office_info_window, mothball_all)]
function industry_office_info_window_on_mothball_all(window) {
    var office = city.get_industry_office(window.bid)
    if (!office || !office.is_management_active()) {
        return
    }
    office.mothball_all()
    industry_office_info_window_refresh(window.bid)
}

[es=(industry_office_info_window, unmothball_all)]
function industry_office_info_window_on_unmothball_all(window) {
    var office = city.get_industry_office(window.bid)
    if (!office || !office.is_management_active()) {
        return
    }
    office.unmothball_all()
    industry_office_info_window_refresh(window.bid)
}

[es=(industry_office_info_window, init)]
function industry_office_info_window_init(window) {
    var b = city.get_building(window.bid)
    var office = city.get_industry_office(window.bid)
    var papyrus_stored = b.stored_resource(RESOURCE_PAPYRUS)

    window.warning_text.text = __loc("#building_industry_office_info")
    window.resource_icon.image = RESOURCE_PAPYRUS
    window.resource_stored.text = __loc(23, 77) + " " + papyrus_stored

    var managed = office ? office.managed_count() : 0
    var active = office && office.is_management_active()
    if (active) {
        window.managed_text.text = __loc("#industry_office_managing") + " " + managed
    } else if (papyrus_stored <= 0) {
        window.managed_text.text = __loc("#industry_office_needs_papyrus")
    } else if (b.num_workers <= 0) {
        window.managed_text.text = __loc("#industry_office_needs_workers")
    } else {
        window.managed_text.text = __loc("#industry_office_inactive")
    }

    if (window.mothball_all) {
        window.mothball_all.enabled = !!active
    }
    if (window.unmothball_all) {
        window.unmothball_all.enabled = !!active
    }

    var reason = { key: "#industry_office_working" }
    if (b.has_road_access == false) {
        reason = { key: "#building_no_road_access" }
    } else if (!active) {
        if (papyrus_stored <= 0) {
            reason = { key: "#industry_office_needs_papyrus" }
        } else if (b.num_workers <= 0) {
            reason = { key: "#industry_office_needs_workers" }
        } else {
            reason = { key: "#industry_office_inactive" }
        }
    }
    window.workers_desc.text = __loc(reason)
}
