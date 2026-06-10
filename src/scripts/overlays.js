log_info("akhenaten: overlays started")

import overlays.apothecary
import overlays.health

overlays = [
  {
  	id:OVERLAY_RELIGION_OSIRIS
  	title: "#overlay_osiris"
  	walkers:[FIGURE_PRIEST]
  	buildings:[BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_ROADBLOCK]
  	tooltip_base:0
  	tooltips:[]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
  	id:OVERLAY_RELIGION_RA
  	title: "#overlay_ra"
  	walkers:[FIGURE_PRIEST]
  	buildings:[BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA, BUILDING_ROADBLOCK]
  	tooltip_base:0
  	tooltips:[]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION_SETH
    title: "#overlay_seth"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_SHRINE_SETH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_NATIVE
    title: "#overlay_native"
    walkers:[FIGURE_INDIGENOUS_NATIVE, FIGURE_MISSIONARY]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION_PTAH
    title: "#overlay_ptah"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_SHRINE_PTAH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION_BAST
    title: "#overlay_bast"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_WATER
    title: "#overlay_menu_water"
    walkers:[FIGURE_WATER_CARRIER]
    buildings:[BUILDING_WELL, BUILDING_MENU_BEAUTIFICATION, BUILDING_WATER_LIFT, BUILDING_WATER_SUPPLY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION
    title: "#overlay_menu_religion"
    walkers:[FIGURE_PRIEST]
    buildings:[ BUILDING_FESTIVAL_SQUARE,
                BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA,
                BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS,
                BUILDING_ROADBLOCK ]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_BANDSTAND
    title: "#overlay_bandstand"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_CONSERVATORY, BUILDING_BANDSTAND, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}

    tooltips {
      low { values:[ "#bandstand_none" ] }
      usual { values:[ "#bandstand_low" ] }
      medium { values:[ "#bandstand_medium" ] }
      high { values:[ "#bandstand_high" ] }
    }
  }

  {
    id:OVERLAY_BAZAAR_ACCESS
    title: "#overlay_bazaar_access"
    walkers:[FIGURE_MARKET_BUYER, FIGURE_MARKET_TRADER]
    buildings:[BUILDING_BAZAAR, BUILDING_ROADBLOCK, BUILDING_GRANARY]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}

    tooltips {
      not_provided { values:[ "#food_stocks_not_provided" ] }
      none { values:[ "#food_stocks_none" ] }
      low { values:[ "#food_stocks_low" ] }
      medium { values:[ "#food_stocks_medium" ] }
      high { values:[ "#food_stocks_high" ] }
    }
  }

  {
    id:OVERLAY_COUTHOUSE
    title: "#overlay_magistrate"
    walkers:[FIGURE_MAGISTRATE]
    buildings:[BUILDING_COURTHOUSE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_CRIME
    title: "#overlay_crime"
    walkers:[FIGURE_CONSTABLE, FIGURE_PROTESTER, FIGURE_ROBBER, FIGURE_TOMB_ROBER]
    buildings:[BUILDING_POLICE_STATION, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_PROBLEMS
    title: "#overlay_problems"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_ROUTING
    title: "#overlay_routing"
    walkers:[],
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_DAMAGE
    title: "#overlay_damage"
    walkers:[FIGURE_ARCHITECT]
    buildings:[BUILDING_ARCHITECT_POST, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_DENTIST
    title: "#overlay_dentist"
    walkers:[FIGURE_DENTIST]
    buildings:[BUILDING_DENTIST, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FERTILITY
    title: "#overlay_fertility"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_LIBRARY
    title: "#overlay_library"
    walkers:[FIGURE_LIBRARIAN]
    buildings:[BUILDING_LIBRARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_ACADEMY
    title: "#overlay_academy"
    walkers:[FIGURE_LIBRARIAN]
    buildings:[BUILDING_LIBRARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_EDUCATION
    title: "#overlay_education"
    walkers:[FIGURE_SCRIBER, FIGURE_LIBRARIAN, FIGURE_TEACHER]
    buildings:[BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ACADEMY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_ENTERTAINMENT
    title: "#overlay_entertainment"
    walkers:[FIGURE_JUGGLER, FIGURE_MUSICIAN, FIGURE_DANCER, FIGURE_SENET_PLAYER, FIGURE_CHARIOR_RACER]
    buildings:[ BUILDING_JUGGLER_SCHOOL, BUILDING_BOOTH, BUILDING_CONSERVATORY,
                BUILDING_BANDSTAND, BUILDING_DANCE_SCHOOL, BUILDING_PAVILLION,
                BUILDING_BULLFIGHT_SCHOOL, BUILDING_SENET_HOUSE,
                BUILDING_ROADBLOCK ]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_SENET_HOUSE
    title: "#overlay_senet_house"
    walkers:[FIGURE_CHARIOR_RACER]
    buildings:[BUILDING_BULLFIGHT_SCHOOL, BUILDING_SENET_HOUSE, BUILDING_ROADBLOCK]
    column_type:COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FIRE
    title: "#overlay_fire"
    walkers[FIGURE_FIREMAN]
    buildings[BUILDING_FIREHOUSE, BUILDING_BURNING_RUIN, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim {pack:PACK_GENERAL, id:103}

    building_tooltips [
      {
        building_type : BUILDING_FIREHOUSE
        tooltips [
          "This month:\t${building.buildings_served_this_month}",
          "This year:\t${building.buildings_served_this_year}",
          "Total served:\t${building.total_buildings_served}",
          "Months active:\t${building.months_active}"
        ]
      }
    ]
  }

  {
    id:OVERLAY_MALARIA_RISK
    title: "#overlay_malaria_risk"
    walkers:[FIGURE_HERBALIST]
    buildings:[BUILDING_APOTHECARY, BUILDING_WATER_SUPPLY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_LABOR
    title: "#overlay_labor"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_BOOTH
    title: "#overlay_booth"
    walkers:[FIGURE_JUGGLER]
    buildings:[BUILDING_JUGGLER_SCHOOL, BUILDING_BOOTH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_MORTUARY
    title: "#overlay_mortuary"
    walkers:[FIGURE_EMBALMER]
    buildings:[BUILDING_MORTUARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FOOD_STOCKS
    title: "#overlay_food_stocks"
    walkers:[FIGURE_EMBALMER]
    buildings:[BUILDING_BAZAAR, BUILDING_FISHING_WHARF, BUILDING_GRANARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}

    tooltips {
      not_provided { values:[ "#food_stocks_not_provided" ] }
      none { values:[ "#food_stocks_none" ] }
      low { values:[ "#food_stocks_low" ] }
      medium { values:[ "#food_stocks_medium" ] }
      high { values:[ "#food_stocks_high" ] }
    }
  }

  {
    id:OVERLAY_PAVILION
    title: "#overlay_pavilion"
    walkers:[]
    buildings:[BUILDING_CONSERVATORY, BUILDING_DANCE_SCHOOL, BUILDING_PAVILLION, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_PHYSICIAN
    title: "#overlay_physician"
    walkers:[FIGURE_PHYSICIAN]
    buildings:[BUILDING_PHYSICIAN, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_SCRIBAL_SCHOOL
    title: "#overlay_scribal_school"
    walkers:[FIGURE_TEACHER]
    buildings:[BUILDING_SCRIBAL_SCHOOL, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_DESIRABILITY
    title: "#overlay_desirability"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_TAX_INCOME
    title: "#overlay_tax_income"
    walkers:[FIGURE_TAX_COLLECTOR]
    buildings:[BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED, BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_LABOR_ACCESS
    title: "#overlay_labor_access"
    walkers:[FIGURE_LABOR_SEEKER]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_CRIMINAL
    title: "#overlay_criminal"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }
]
