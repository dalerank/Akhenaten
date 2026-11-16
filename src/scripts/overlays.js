log_info("akhenaten: overlays started")

import overlays.apothecary
import overlays.health
import overlays.tax_income
import overlays.booth
import overlays.bandstand
import overlays.bazaar_access
import overlays.goods_stock
import overlays.goods_by_type
import overlays.brewery
import overlays.disease
import overlays.infected_housing
import overlays.malaria
import overlays.water_crossings
import overlays.empty_housing
import overlays.city_defenses
import overlays.irrigation
import overlays.hide_cliffs
import overlays.flood_basin
import overlays.entertainment
import overlays.senet_house
import overlays.zoo
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
import overlays.courthouse
import overlays.fire
import overlays.crime
import overlays.criminal
import overlays.desirability
import overlays.fertility
import overlays.labor_access
import overlays.food_stocks
import overlays.architect_reach

overlays = [
  {
    id:OVERLAY_NATIVE
    title: "#overlay_native"
    walkers:[FIGURE_INDIGENOUS_NATIVE]
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
    id:OVERLAY_CRIME
    title: "#overlay_crime"
    walkers:[FIGURE_CONSTABLE, FIGURE_MAGISTRATE, FIGURE_PROTESTER, FIGURE_ROBBER, FIGURE_TOMB_ROBER]
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
    id:OVERLAY_DESIRABILITY
    title: "#overlay_desirability"
    walkers:[]
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

  {
    id:OVERLAY_ARCHITECT_REACH
    title: "#overlay_architect_reach"
    walkers:[FIGURE_ARCHITECT]
    buildings:[BUILDING_ARCHITECT_POST, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_IRRIGATION
    title: "#overlay_irrigation"
    walkers:[]
    buildings:[BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_HIDE_CLIFFS
    title: "#overlay_hide_cliffs"
    walkers:[]
    buildings:[]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FLOOD_BASIN
    title: "#overlay_flood_basin"
    walkers:[]
    buildings:[BUILDING_DIKE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }
]
