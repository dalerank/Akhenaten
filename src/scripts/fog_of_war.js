log_info("akhenaten: fog of war started")

city_fog_of_war {
    update_every_ticks : 5
    soft_edge_tiles : 2
    fogged_mask : 0xff606060
    edge_mask : 0xffa0a0a0
    initial_reveal_radius : 12
    default_building_radius : 3

    building_radius_by_size : [
        { size: 1, radius: 3, hint: "shrine, well, small house" }
        { size: 2, radius: 4, hint: "bazaar, workshop" }
        { size: 3, radius: 5, hint: "temple, big house" }
        { size: 4, radius: 6, hint: "palace, mansion" }
        { size: 5, radius: 6, hint: "large buildings" }
    ]

    building_radius : [
        { building: BUILDING_MUD_TOWER, radius: 10, hint: "watch tower" }
        { building: BUILDING_BRICK_TOWER, radius: 10, hint: "watch tower" }
        { building: BUILDING_TOWER, radius: 10, hint: "watch tower" }
        { building: BUILDING_FORT_INFANTRY, radius: 8, hint: "fort" }
        { building: BUILDING_FORT_ARCHERS, radius: 8, hint: "fort" }
        { building: BUILDING_FORT_CHARIOTEERS, radius: 8, hint: "fort" }
        { building: BUILDING_VILLAGE_PALACE, radius: 8, hint: "palace" }
        { building: BUILDING_TOWN_PALACE, radius: 8, hint: "palace" }
        { building: BUILDING_CITY_PALACE, radius: 8, hint: "palace" }
        { building: BUILDING_FERRY, radius: 6, hint: "ferry sees across the river" }
        { building: BUILDING_DOCK, radius: 6, hint: "dock sees the river" }
        { building: BUILDING_BURNING_RUIN, radius: -1, hint: "ruins do not see" }
    ]

    figure_radius_by_category : [
        { category: figure_category_inactive, radius: -1, hint: "not on the map" }
        { category: figure_category_citizen, radius: 1, hint: "walkers" }
        { category: figure_category_armed, radius: 6, hint: "player soldiers" }
        { category: figure_category_hostile, radius: -1, hint: "enemies" }
        { category: figure_category_criminal, radius: -1, hint: "robbers, rioters" }
        { category: figure_category_native, radius: -1, hint: "natives" }
        { category: figure_category_animal, radius: -1, hint: "animals" }
        { category: figure_category_missile, radius: -1, hint: "arrows, spears" }
        { category: figure_category_military, radius: 6, hint: "player military" }
        { category: figure_category_transport, radius: 1, hint: "cart pushers, boats" }
        { category: figure_category_worker, radius: 1, hint: "service workers" }
        { category: figure_category_entertainer, radius: 1, hint: "entertainers" }
        { category: figure_category_religious, radius: 1, hint: "priests" }
        { category: figure_category_merchant, radius: -1, hint: "foreign traders and ships" }
        { category: figure_category_special, radius: 1, hint: "player special walkers" }
    ]

    figure_radius : [
        { figure: FIGURE_TOWER_SENTRY, radius: 8, hint: "sentry on the tower" }
        { figure: FIGURE_WARSHIP, radius: 6, hint: "warship" }
    ]
}
