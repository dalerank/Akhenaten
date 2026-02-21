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

function house_tax_info(house) {
    if (!house.tax_coverage)
        return __loc(127, 23)

    var pct = Math.floor((house.tax_income_or_storage / 2) * city.finance.tax_percentage / 100)
    return __loc(127, 24) + " " + pct + " " + __loc(127, 25)
}

function house_happiness_text_id(house) {
    var h = house.house_happiness
    if (h >= 50) return 26
    if (h >= 40) return 27
    if (h >= 30) return 28
    if (h >= 20) return 29
    if (h >= 10) return 30
    if (h >= 1) return 31
    return 32
}

function house_people_text(house) {
    var pop = house.population
    var room = house.population_room
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

function house_foodtypes_available(house) {
    var n = 0
    for (var i = 0; i < 8; i++)
        if (house.food(i) > 0) n++
    return n
}

function house_determine_evolve_text(house) {
    var bid = house.id
    var level = house.level
    var curDes = house.current_desirability
    var hasWater = house.has_water_access
    var hasWell = house.has_well_access
    var waterSupply = house.water_supply
    var entertainment = house.entertainment
    var bazaarAccess = house.bazaar_access
    var education = house.education
    var school = house.school
    var library = house.library
    var magistrate = house.magistrate
    var numGods = house.num_gods
    var dentist = house.dentist
    var health = house.health
    var mortuary = house.mortuary
    var physician = house.physician
    var worstDesBid = house.worst_desirability_building_id
    var fancyBazaarAccess = house.fancy_bazaar_access
    var noSpaceToExpand = house.no_space_to_expand

    var model = house.model
    function set(t) { house.evolve_text = t; return true }

    house.evolve_text = ""

    // devolve: desirability
    if (curDes <= model.devolve_desirability) return set("#house_low_desirabilty")
    // water
    var water = model.water
    if (water == 1 && !hasWater && !hasWell) return set("#lacks_access_primitive_water")
    if (water == 2 && (!hasWater || !waterSupply)) return set("#not_visited_by_water_carrier")
    // entertainment
    var entReq = model.entertainment
    if (entertainment < entReq) {
        if (!entertainment) return set("#no_entertainment_to_be_found")
        if (entReq < 10) return set("#any_entertainment_in_location")
        if (entReq < 25) return set("#too_little_entertainment_in_location")
        if (entReq < 50) return set("#some_entertainment_found_location")
        if (entReq < 80) return set("#good_entertainment_found_location")
        return set("#excellent_entertainment_found_location")
    }
    // food types
    var foodtypesRequired = model.food_types
    var foodtypesAvailable = house_foodtypes_available(house)
    var foodtypeText = ["empty", "#one_food_type_need", "#two_food_types_need", "#three_food_types_need"]
    if (foodtypesAvailable < foodtypesRequired) return set(foodtypeText[foodtypesRequired])
    // bazaar
    var needsBazaar = (model.food_types + model.pottery + model.linen + model.jewelry + model.beer) > 0
    if (needsBazaar && !bazaarAccess) return set("#no_bazaar_access")
    // education
    var eduReq = model.education
    if (education < eduReq) {
        if (eduReq == 1) return set("#lost_basic_educational_facilities")
        if (eduReq == 2) {
            if (school) return set("#lost_access_to_scribal_school")
            if (library) return set("#lost_access_to_library")
        }
        if (eduReq == 3) return set("#lost_access_to_higher_education")
    }
    // magistrate (model.physician)
    if (magistrate < model.physician) return set("#no_access_to_magistrates")
    // pottery (inv 0)
    if (house.inv(0) < model.pottery) return set("#run_out_of_pottery")
    // religion
    var religion = model.religion
    if (numGods < religion) {
        if (religion == 1) return set("#lost_all_access_to_local_religious")
        if (religion == 2) return set("#access_to_one_local_religious")
        if (religion == 3) return set("#access_to_two_local_religious")
    }
    // dentist
    if (dentist < model.dentist) return set("#lost_dentist_access")
    // health
    var healthNeed = model.health
    if (health < healthNeed) {
        if (healthNeed == 1) return set("#no_access_to_physician")
        if (mortuary) return set("#no_access_to_mortuary")
        return set("#hard_access_to_physician")
    }
    // linen (inv 2), beer (inv 3), jewelry (inv 1)
    if (house.inv(2) < model.linen) return set("#run_out_of_linen")
    if (house.inv(3) < model.beer) return set("#run_out_of_beer")
    if (house.inv(1) < model.jewelry) return set("#run_out_of_jewelry")

    if (level >= 19) return set("#dwellers_palace_are_pinnacle")

    // evolve: desirability
    if (curDes < model.evolve_desirability) {
        if (worstDesBid) return set("")
        return set("#cannot_evolve_cause_low_desirability")
    }

    var nextLevel = level + 1
    var nextModel = city.get_house_model(nextLevel)

    // water (next)
    water = nextModel.water
    if (water == 1 && !hasWater && !hasWell) return set("#cannot_evolve_most_primitive_water_source")
    if (water == 2 && !hasWater) return set("#cannot_evolve_access_to_water_carrier")
    // entertainment (next)
    entReq = nextModel.entertainment
    if (entertainment < entReq) {
        if (!entertainment) return set("#cannot_evolve_no_entertainment")
        if (entReq < 10) return set("#cannot_evolve_hardly_any_entertainment")
        if (entReq < 25) return set("#cannot_evolve_too_little_entertainment")
        if (entReq < 50) return set("#cannot_evolve_some_entertainment")
        if (entReq < 80) return set("#cannot_evolve_good_entertainment")
        return set("#cannot_evolve_excellent_entertainment")
    }
    // food types (next)
    foodtypesRequired = nextModel.food_types
    if (foodtypesAvailable < foodtypesRequired) {
        if (foodtypesRequired == 1) return set("#cannot_evolve_needs_supply_food")
        if (foodtypesRequired == 2) return set("#cannot_evolve_needs_second_type_food")
        if (foodtypesRequired == 3) return set("#cannot_evolve_needs_third_type_food")
    }
    if (nextModel.fancy_bazaar && fancyBazaarAccess <= 0) return set("#cannot_evolve_needs_access_bazaar")
    // education (next)
    eduReq = nextModel.education
    if (education < eduReq) {
        if (eduReq == 1) return set("#cannot_evolve_needs_basic_education")
        if (eduReq == 2) {
            if (school) return set("#cannot_evolve_needs_school_education")
            if (library) return set("#cannot_evolve_needs_library_education")
        }
    }
    // physician (next)
    if (physician < nextModel.physician) return set("#cannot_evolve_needs_physician")
    // pottery, religion, dentist, health, linen, jewelry, beer (next)
    if (house.inv(0) < nextModel.pottery) return set("#cannot_evolve_needs_pottery")
    religion = nextModel.religion
    if (numGods < religion) {
        if (religion == 1) return set("#cannot_evolve_needs_religious")
        if (religion == 2) return set("#cannot_evolve_needs_religious_two_gods")
        if (religion == 3) return set("#cannot_evolve_needs_religious_three_gods")
    }
    if (dentist < nextModel.dentist) return set("#cannot_evolve_needs_dentist")
    var modelHealthNeed = nextModel.health
    if (health < modelHealthNeed) {
        if (modelHealthNeed == 1) return set("#cannot_evolve_needs_physician")
        if (dentist) return set("#cannot_evolve_needs_mortuary_has_physician")
        return set("#cannot_evolve_needs_physician_mortuary_has")
    }
    if (house.inv(2) < nextModel.linen) return set("#cannot_evolve_needs_linen")
    if (house.inv(1) < nextModel.jewelry) return set("#cannot_evolve_needs_jewlery")
    if (house.inv(3) < nextModel.beer) return set("#cannot_evolve_needs_beer")

    set("#house_upgrade_inprogress")
    if (noSpaceToExpand == 1) set("#house_upgrade_nospace")
}

function house_get_additional_info(house) {
    if (house.model.food_types) return ""
    return __loc(127, 33)
}

function house_get_evolve_reason(house) {
    var et = house.evolve_text
    var worstId = house.worst_desirability_building_id
    if (!et && worstId > 0) {
        var worst = city.get_building(worstId)
        var typeId = worst ? worst.type : 0
        return __loc(127, 102) + " @Y" + __loc(41, typeId) + "&) " + __loc(127, 103)
    }
    return et
}

[es=info_window_house_init]
function info_window_house_init_fill(window) {
    var house = city.get_house(window.bid)
    if (house.population <= 0)
        return

    __house_prepare_evolve_info(window.bid)
    house_determine_evolve_text(house)
    window.evolve_reason.text = house_get_evolve_reason(house)

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

    window.people_text.text = house_people_text(house)
    window.tax_info.text = house_tax_info(house)
    window.happiness_info.text = __loc(127, house_happiness_text_id(house))

    var addInfo = house_get_additional_info(house)
    if (addInfo) {
        window.additional_info.text = addInfo
    }
}

[es=info_window_vacant_lot_init]
function info_window_vacant_lot_init_fill(window) {
    var textId = __map_road_within_radius(house.tile, 1, 2) ? 1 : 2
    window.describe.text = __loc(128, textId)
}