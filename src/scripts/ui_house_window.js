log_info("akhenaten: ui house window started")

info_window_house {
    help_id : "message_housing_and_desirability"
    ui {
        background : outer_panel({size [29, 23] }) // pos/size setup from code
        title      : text({pos[0, 16], text:"${house.level_name}", size[px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        evolve_reason : text({pos[32, 40], size[px(27), -1], font : FONT_NORMAL_BLACK_ON_LIGHT, rich:true, wrap:px(27), scroll:false })
        food0_icon : resource_icon({pos[32, 95] })
        food0_text : text({pos[64, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food1_icon : resource_icon({pos[142, 95] })
        food1_text : text({pos[174, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food2_icon : resource_icon({pos[252, 95] })
        food2_text : text({pos[284, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food3_icon : resource_icon({pos[362, 95] })
        food3_text : text({pos[394, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good0_icon : resource_icon({pos[32, 120] })
        good0_text : text({pos[64, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good1_icon : resource_icon({pos[142, 120] })
        good1_text : text({pos[174, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good2_icon : resource_icon({pos[252, 120] })
        good2_text : text({pos[284, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good3_icon : resource_icon({pos[362, 120] })
        good3_text : text({pos[394, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })

        tenants_panel: inner_panel({pos [16, 148], size[27, 10] })
        people_icon  : image({pos[34, 154], pack:PACK_GENERAL, id:134, offset:13, })
        people_text  : text({pos[64, 164], font: FONT_NORMAL_BLACK_ON_DARK, })
        tax_info     : text({pos[36, 194], font: FONT_NORMAL_BLACK_ON_DARK, })
        happiness_info  : text({pos[36, 214], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) })
        additional_info : text({pos[36, 234], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) })

        button_close : close_button({})
        button_help  : help_button({})
    }
}

function house_has_road_nearby(bid) {
    return __map_road_within_radius(house.tile, 1, 2)
}

function house_people_text(bid) {
    var pop = __house_population(bid)
    var room = __house_population_room(bid)
    var people_str = pop + " " + __loc(127, 20)
    var adv_str
    if (room < 0)
        adv_str = (-room) + " " + __loc(127, 21)
    else if (room > 0)
        adv_str = __loc(127, 22) + " " + room
    else
        adv_str = "no rooms"
    return people_str + " ( " + adv_str + " )"
}

[es=info_window_house_init]
function info_window_house_init_fill(window) {
    var house = city.get_house(window.bid)
    if (house.population <= 0)
        return

    __house_prepare_evolve_info(window.bid)
    window.evolve_reason.text = __house_get_evolve_reason(window.bid)

    var resource1 = city.allowed_foods(0)
    window.food0_icon.image = resource1
    window.food0_text.text = (resource1 != RESOURCE_NONE) ? (" " + house.food(0)) : ""
    var resource2 = city.allowed_foods(1)
    window.food1_icon.image = resource2
    window.food1_text.text = (resource2 != RESOURCE_NONE) ? (" " + house.food(1)) : ""
    var resource3 = city.allowed_foods(2)
    window.food2_icon.image = resource3
    window.food2_text.text = (resource3 != RESOURCE_NONE) ? (" " + house.food(2)) : ""
    var resource4 = city.allowed_foods(3)
    window.food3_icon.image = resource4
    window.food3_text.text = (resource4 != RESOURCE_NONE) ? (" " + house.food(3)) : ""

    window.good0_icon.image = RESOURCE_POTTERY
    window.good0_text.text = "" + house.inv(0)
    window.good1_icon.image = RESOURCE_LUXURY_GOODS
    window.good1_text.text = "" + house.inv(1)
    window.good2_icon.image = RESOURCE_LINEN
    window.good2_text.text = "" + house.inv(2)
    window.good3_icon.image = RESOURCE_BEER
    window.good3_text.text = "" + house.inv(3)

    window.people_text.text = house_people_text(window.bid)
    window.tax_info.text = __house_get_tax_info(window.bid)
    window.happiness_info.text = __loc(127, __house_get_happiness_text_id(window.bid))

    var addInfo = __house_get_additional_info(window.bid)
    if (addInfo) {
        window.additional_info.text = addInfo
    }
}

[es=info_window_vacant_lot_init]
function info_window_vacant_lot_init_fill(window) {
    var textId = house_has_road_nearby(window.bid) ? 1 : 2
    window.describe.text = __loc(128, textId)
}