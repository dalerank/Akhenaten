log_info("akhenaten: overlays started")

import overlays.apothecary
import overlays.health
import overlays.tax_income
import overlays.booth
import overlays.bandstand
import overlays.bazaar_access
import overlays.brewery
import overlays.entertainment
import overlays.senet_house
import overlays.mortuary
import overlays.dentist
import overlays.damage
import overlays.education
import overlays.academy
import overlays.library
import overlays.scribal_school
import overlays.physician
import overlays.religion
import overlays.pavilion
import overlays.labor
import overlays.malaria_risk

overlays = [
  {
    id:OVERLAY_NATIVE
    title: "#overlay_native"
    walkers:[FIGURE_INDIGENOUS_NATIVE, FIGURE_MISSIONARY]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
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
    id:OVERLAY_FERTILITY
    title: "#overlay_fertility"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
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
    id:OVERLAY_DESIRABILITY
    title: "#overlay_desirability"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
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
