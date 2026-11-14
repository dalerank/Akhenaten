log_info("akhenaten: construction warnings started")

// OG building/construction_warnings.c: hints shown after a building is placed. They never block it.
construction_warning_rules {
  min_population: 300
  min_workers_needed: 10
  max_unemployment_percent: 10
  min_food_produced_percent: 96
  max_problem_messages: 3

  road_access: "#needs_road_access"
  shrine_road_access: "#shrines_near_road_required"
  workers: "#city_needs_more_workers"
  no_troops: "#no_troops_for_defense"
  wall_patrol: "#must_be_next_to_wall_for_patrol"
  eating_more_than_produced: "#people_eating_more_than_produced"
  too_few_jobs: "#too_few_jobs_for_population"
  low_food: "#low_food_levels"

  road_access_exempt [
    BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_WELL, BUILDING_WATER_LIFT,
    BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
    BUILDING_MUD_GATEHOUSE, BUILDING_BRICK_GATEHOUSE, BUILDING_GATEHOUSE, BUILDING_MUD_GATEHOUSE_UP,
    BUILDING_BRICK_GATEHOUSE_UP, BUILDING_DECORATIVE_GATEHOUSE, BUILDING_TOWER_GATEHOUSE,
    BUILDING_RESERVED_TRIUMPHAL_ARCH_56, BUILDING_HOUSE_VACANT_LOT, BUILDING_HOUSE_CRUDE_HUT,
    BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
    BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST,
    BUILDING_TEMPLE_COMPLEX_ALTAR_AMON, BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, BUILDING_TEMPLE_COMPLEX_ALTAR_SEBEK,
    BUILDING_TEMPLE_COMPLEX_ALTAR_MAAT, BUILDING_TEMPLE_COMPLEX_ALTAR_ISIS,
    BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH, BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET, BUILDING_TEMPLE_COMPLEX_ORACLE_MIN,
    BUILDING_TEMPLE_COMPLEX_ORACLE_HORUS, BUILDING_TEMPLE_COMPLEX_ORACLE_HATHOR,
    BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID, BUILDING_LARGE_STEPPED_PYRAMID,
    BUILDING_STEPPED_PYRAMID_COMPLEX, BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX,
    BUILDING_SMALL_BENT_PYRAMID, BUILDING_MEDIUM_BENT_PYRAMID,
    BUILDING_SMALL_PYRAMID, BUILDING_MEDIUM_PYRAMID, BUILDING_LARGE_PYRAMID, BUILDING_PYRAMID_COMPLEX,
    BUILDING_GRAND_PYRAMID_COMPLEX,
    BUILDING_SMALL_MUDBRICK_PYRAMID, BUILDING_MEDIUM_MUDBRICK_PYRAMID, BUILDING_LARGE_MUDBRICK_PYRAMID,
    BUILDING_MUDBRICK_PYRAMID_COMPLEX, BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX,
    BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA, BUILDING_LARGE_MASTABA,
    BUILDING_SPHINX, BUILDING_CAESAREUM, BUILDING_ALEXANDRIA_LIBRARY, BUILDING_ABU_SIMBEL, BUILDING_PHAROS_LIGHTHOUSE,
    BUILDING_MAUSOLEUM, BUILDING_SMALL_OBELISK, BUILDING_LARGE_OBELISK, BUILDING_SUN_TEMPLE,
    BUILDING_SMALL_ROYAL_TOMB, BUILDING_MEDIUM_ROYAL_TOMB, BUILDING_LARGE_ROYAL_TOMB, BUILDING_GRAND_ROYAL_TOMB,
    BUILDING_ROAD, BUILDING_MUD_WALL, BUILDING_BRICK_WALL, BUILDING_WALL, BUILDING_IRRIGATION_DITCH, BUILDING_DIKE,
    BUILDING_PLAZA, BUILDING_GARDENS, BUILDING_LOW_BRIDGE, BUILDING_UNUSED_SHIP_BRIDGE_83, BUILDING_FESTIVAL_SQUARE
  ]

  road_access_area [
    { building: BUILDING_STORAGE_YARD, size: 3 }
    { building: BUILDING_STORAGE_YARD_UP, size: 3 }
  ]

  shrines [BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST]

  workers_exempt [BUILDING_WELL]

  defense [
    BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
    BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST,
    BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_BAST,
    BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST,
    BUILDING_BANDSTAND, BUILDING_BOOTH, BUILDING_SENET_HOUSE, BUILDING_PAVILLION, BUILDING_CONSERVATORY,
    BUILDING_DANCE_SCHOOL, BUILDING_JUGGLER_SCHOOL, BUILDING_POLICE_STATION,
    BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION, BUILDING_DYNASTY_MANSION, BUILDING_ARCHITECT_POST,
    BUILDING_TAX_COLLECTOR, BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_COURTHOUSE,
    BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_VILLAGE_PALACE_UP, BUILDING_TOWN_PALACE_UP,
    BUILDING_CITY_PALACE, BUILDING_ZOO
  ]

  wall_patrol_types [BUILDING_MUD_TOWER, BUILDING_BRICK_TOWER, BUILDING_TOWER]

  requires_building [
    { building: BUILDING_GRANARY, needs: BUILDING_BAZAAR, warning: "#build_bazaars_to_distribute_food" }
    { building: BUILDING_FORT_CHARIOTEERS, needs: BUILDING_RECRUITER, warning: "#needs_recruiter_to_conscript" }
    { building: BUILDING_FORT_ARCHERS, needs: BUILDING_RECRUITER, warning: "#needs_recruiter_to_conscript" }
    { building: BUILDING_FORT_INFANTRY, needs: BUILDING_RECRUITER, warning: "#needs_recruiter_to_conscript" }
  ]

  requires_stock [
    { building: BUILDING_RECRUITER, resource: RESOURCE_WEAPONS, warning: "#soldiers_need_supplies_of_weapons" }
  ]

  // Venues are placed by the intersection tool: they get only these hints.
  venue_schools [
    { building: BUILDING_BOOTH, school: BUILDING_JUGGLER_SCHOOL, warning: "#build_jugglers_school" }
    { building: BUILDING_BANDSTAND, school: BUILDING_JUGGLER_SCHOOL, warning: "#build_jugglers_school" }
    { building: BUILDING_BANDSTAND, school: BUILDING_CONSERVATORY, warning: "#venue_build_conservatory" }
    { building: BUILDING_PAVILLION, school: BUILDING_JUGGLER_SCHOOL, warning: "#build_jugglers_school" }
    { building: BUILDING_PAVILLION, school: BUILDING_CONSERVATORY, warning: "#venue_build_conservatory" }
    { building: BUILDING_PAVILLION, school: BUILDING_DANCE_SCHOOL, warning: "#venue_build_dance_school" }
  ]

  // Nothing produced, nothing in the yards: "needs X", then build the producer, or a trade route, or the overseer.
  raw_materials [
    { buildings: [BUILDING_BREWERY_WORKSHOP], industry: RESOURCE_BARLEY, stock: RESOURCE_BARLEY, product: RESOURCE_BEER
      warning: "#needs_barley", produce: RESOURCE_BARLEY, build: "#build_barley_farm", import_res: RESOURCE_BARLEY
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_WEAVER_WORKSHOP], industry: RESOURCE_FLAX, stock: RESOURCE_FLAX, product: RESOURCE_LINEN
      warning: "#building_needs_flax", produce: RESOURCE_FLAX, build: "#build_flax_farm", import_res: RESOURCE_FLAX
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_JEWELS_WORKSHOP], industry: RESOURCE_GEMS, stock: RESOURCE_GEMS, product: RESOURCE_LUXURY_GOODS
      warning: "#needs_gems", produce: RESOURCE_GEMS, build: "#build_gem_mine", import_res: RESOURCE_GEMS
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_POTTERY_WORKSHOP], industry: RESOURCE_CLAY, stock: RESOURCE_CLAY, product: RESOURCE_POTTERY
      warning: "#building_needs_clay", produce: RESOURCE_CLAY, build: "#build_clay_pit", import_res: RESOURCE_CLAY
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_PAPYRUS_WORKSHOP], industry: RESOURCE_REEDS, stock: RESOURCE_REEDS, product: RESOURCE_PAPYRUS
      warning: "#building_needs_reeds", produce: RESOURCE_REEDS, build: "#build_reed_gatherer", import_res: RESOURCE_REEDS
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_PAINT_WORKSHOP], industry: RESOURCE_HENNA, stock: RESOURCE_HENNA, product: RESOURCE_PAINT
      warning: "#building_needs_henna", produce: RESOURCE_HENNA, build: "#build_henna_farm", import_res: RESOURCE_HENNA
      no_route: "#import_henna_trade_route", not_imported: "#import_henna_overseer" }
    { buildings: [BUILDING_CATTLE_RANCH], industry: RESOURCE_GRAIN, stock: RESOURCE_STRAW
      warning: "#building_needs_straw", produce: RESOURCE_GRAIN, build: "#build_grain_farm", import_res: RESOURCE_STRAW
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_CARPENTERS_GUILD], industry: RESOURCE_TIMBER, stock: RESOURCE_TIMBER
      warning: "#building_needs_wood", produce: RESOURCE_TIMBER, build: "#build_wood_cutter", import_res: RESOURCE_TIMBER
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_SUN_TEMPLE, BUILDING_MAUSOLEUM], industry: RESOURCE_SANDSTONE, stock: RESOURCE_SANDSTONE
      warning: "#monument_needs_sandstone", produce: RESOURCE_SANDSTONE, build: "#build_sandstone_quarry"
      import_res: RESOURCE_SANDSTONE
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID, BUILDING_LARGE_STEPPED_PYRAMID,
                  BUILDING_STEPPED_PYRAMID_COMPLEX, BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX]
      industry: RESOURCE_STONE, stock: RESOURCE_STONE
      warning: "#monument_needs_plain_stone", produce: RESOURCE_STONE, build: "#build_stone_quarry", import_res: RESOURCE_STONE
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA, BUILDING_LARGE_MASTABA]
      industry: RESOURCE_BRICKS, stock: RESOURCE_BRICKS
      warning: "#monument_needs_bricks", produce: RESOURCE_BRICKS, build: "#build_brickworks", import_res: RESOURCE_BRICKS
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_PHAROS_LIGHTHOUSE, BUILDING_CAESAREUM, BUILDING_ALEXANDRIA_LIBRARY], stock: RESOURCE_MARBLE
      warning: "#monument_needs_marble", import_res: RESOURCE_MARBLE
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_ALEXANDRIA_LIBRARY], industry: RESOURCE_COPPER, stock: RESOURCE_COPPER
      warning: "#monument_needs_copper", import_res: RESOURCE_COPPER
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
    { buildings: [BUILDING_CAESAREUM], industry: RESOURCE_GRANITE, stock: RESOURCE_GRANITE
      warning: "#monument_needs_granite", import_res: RESOURCE_GRANITE
      no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import" }
  ]

  // With both inputs missing the hints name the resource (the lamp maker swaps the oil and pottery texts).
  two_inputs [
    { buildings: [BUILDING_BRICKS_WORKSHOP], product: RESOURCE_BRICKS, warning: "#building_needs_clay_and_straw"
      first: { industry: RESOURCE_CLAY, stock: RESOURCE_CLAY, warning: "#building_needs_clay"
               produce: RESOURCE_CLAY, build: "#build_clay_pit", import_res: RESOURCE_CLAY
               no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
               both_no_route: "#import_clay_trade_route", both_not_imported: "#import_clay_overseer" }
      second: { industry: RESOURCE_GRAIN, stock: RESOURCE_STRAW, warning: "#building_needs_straw"
                produce: RESOURCE_GRAIN, build: "#build_grain_farm", import_res: RESOURCE_STRAW
                no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
                both_no_route: "#import_straw_trade_route", both_not_imported: "#import_straw_overseer" } }
    { buildings: [BUILDING_LAMP_WORKSHOP], product: RESOURCE_LAMPS, warning: "#building_needs_oil_and_pottery"
      first: { industry: RESOURCE_OIL, stock: RESOURCE_OIL, warning: "#building_needs_oil", import_res: RESOURCE_OIL
               no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
               both_no_route: "#import_oil_overseer", both_not_imported: "#import_oil_trade_route" }
      second: { industry: RESOURCE_POTTERY, stock: RESOURCE_POTTERY, warning: "#building_needs_pottery"
                produce: RESOURCE_POTTERY, build: "#build_potter", import_res: RESOURCE_POTTERY
                no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
                both_no_route: "#import_pottery_overseer", both_not_imported: "#import_pottery_trade_route" } }
    { buildings: [BUILDING_SMALL_BENT_PYRAMID, BUILDING_MEDIUM_BENT_PYRAMID, BUILDING_SMALL_PYRAMID,
                  BUILDING_MEDIUM_PYRAMID, BUILDING_LARGE_PYRAMID, BUILDING_PYRAMID_COMPLEX, BUILDING_GRAND_PYRAMID_COMPLEX]
      warning: "#monument_needs_stone_and_limestone"
      first: { industry: RESOURCE_STONE, stock: RESOURCE_STONE, warning: "#monument_needs_plain_stone"
               produce: RESOURCE_STONE, build: "#build_stone_quarry", import_res: RESOURCE_STONE
               no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
               both_no_route: "#import_stone_trade_route", both_not_imported: "#import_stone_overseer" }
      second: { industry: RESOURCE_LIMESTONE, stock: RESOURCE_LIMESTONE, warning: "#monument_needs_limestone"
                produce: RESOURCE_LIMESTONE, build: "#build_limestone_quarry", import_res: RESOURCE_LIMESTONE
                no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
                both_no_route: "#import_limestone_trade_route", both_not_imported: "#import_limestone_overseer" } }
    { buildings: [BUILDING_SMALL_MUDBRICK_PYRAMID, BUILDING_MEDIUM_MUDBRICK_PYRAMID, BUILDING_LARGE_MUDBRICK_PYRAMID,
                  BUILDING_MUDBRICK_PYRAMID_COMPLEX, BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX]
      warning: "#monument_needs_bricks_and_limestone"
      first: { industry: RESOURCE_BRICKS, stock: RESOURCE_BRICKS, warning: "#monument_needs_bricks"
               produce: RESOURCE_BRICKS, build: "#build_brickworks", import_res: RESOURCE_BRICKS
               no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
               both_no_route: "#import_bricks_trade_route", both_not_imported: "#import_bricks_overseer" }
      second: { industry: RESOURCE_LIMESTONE, stock: RESOURCE_LIMESTONE, warning: "#monument_needs_limestone"
                produce: RESOURCE_LIMESTONE, build: "#build_limestone_quarry", import_res: RESOURCE_LIMESTONE
                no_route: "#setup_trade_route_to_import", not_imported: "#overseer_of_commerce_to_import"
                both_no_route: "#import_limestone_trade_route", both_not_imported: "#import_limestone_overseer" } }
  ]
}
