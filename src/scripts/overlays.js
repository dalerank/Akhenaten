log_info("akhenaten: overlays started")

overlays = [
  {
  	id:OVERLAY_RELIGION_OSIRIS
  	caption:"Osiris"
  	walkers:[FIGURE_PRIEST]
  	buildings:[BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_ROADBLOCK]
  	tooltip_base:0
  	tooltips:[]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
  	id:OVERLAY_RELIGION_RA
  	caption:"Ra"
  	walkers:[FIGURE_PRIEST]
  	buildings:[BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA, BUILDING_ROADBLOCK]
  	tooltip_base:0
  	tooltips:[]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION_SETH
    caption: "Seth"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_SHRINE_SETH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_NATIVE
    caption: "Native"
    walkers:[FIGURE_INDIGENOUS_NATIVE, FIGURE_MISSIONARY]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION_PTAH
    caption: "Ptah"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_SHRINE_PTAH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION_BAST
    caption: "Bast"
    walkers:[FIGURE_PRIEST]
    buildings:[BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_WATER
    walkers:[FIGURE_WATER_CARRIER]
    buildings:[BUILDING_WELL, BUILDING_MENU_BEAUTIFICATION, BUILDING_WATER_LIFT, BUILDING_WATER_SUPPLY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_APOTHECARY
    caption: "Apothecary"
    walkers:[FIGURE_HERBALIST]
    buildings:[BUILDING_APOTHECARY, BUILDING_ROADBLOCK],
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_RELIGION
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
    caption: "Bazaar access"
    walkers:[FIGURE_MARKET_BUYER, FIGURE_MARKET_TRADER]
    buildings:[BUILDING_BAZAAR, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_COUTHOUSE
    caption: "Magistrate"
    walkers:[FIGURE_MAGISTRATE]
    buildings:[BUILDING_COURTHOUSE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_CRIME
    walkers:[FIGURE_CONSTABLE, FIGURE_PROTESTER, FIGURE_ROBBER, FIGURE_TOMB_ROBER]
    buildings:[BUILDING_POLICE_STATION, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_PROBLEMS
    caption: "Problems"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_ROUTING
    caption: "Routing"
    walkers:[],
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_DAMAGE
    walkers:[FIGURE_ARCHITECT]
    buildings:[BUILDING_ARCHITECT_POST, BUILDING_FESTIVAL_SQUARE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_DENTIST
    caption: "Dentist"
    walkers:[FIGURE_DENTIST]
    buildings:[BUILDING_DENTIST, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FERTILITY
    caption: "Fertility"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_LIBRARY
    walkers:[FIGURE_LIBRARIAN]
    buildings:[BUILDING_LIBRARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_ACADEMY
    walkers:[FIGURE_LIBRARIAN]
    buildings:[BUILDING_LIBRARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_EDUCATION
    walkers:[FIGURE_SCRIBER, FIGURE_LIBRARIAN, FIGURE_TEACHER]
    buildings:[BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ACADEMY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_ENTERTAINMENT
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
    walkers:[FIGURE_CHARIOR_RACER]
    buildings:[BUILDING_BULLFIGHT_SCHOOL, BUILDING_SENET_HOUSE, BUILDING_ROADBLOCK]
    column_type:COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FIRE
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
    caption: "Malaria Risk"
    walkers:[FIGURE_HERBALIST]
    buildings:[BUILDING_APOTHECARY, BUILDING_WATER_SUPPLY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_HEALTH
    caption: "Health"
    walkers:[FIGURE_EMBALMER, FIGURE_HERBALIST, FIGURE_PHYSICIAN, FIGURE_DENTIST]
    buildings:[BUILDING_MORTUARY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_LABOR
    caption: "Labor"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_BOOTH
    walkers:[FIGURE_JUGGLER]
    buildings:[BUILDING_JUGGLER_SCHOOL, BUILDING_BOOTH, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_MORTUARY
    caption:  "Mortuary"
    walkers:[FIGURE_EMBALMER]
    buildings:[BUILDING_MORTUARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_POSITIVE
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_FOOD_STOCKS
    caption: "Food stocks"
    walkers:[FIGURE_EMBALMER]
    buildings:[BUILDING_BAZAAR, BUILDING_FISHING_WHARF, BUILDING_GRANARY, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_RISK
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_PAVILION
    walkers:[]
    buildings:[BUILDING_CONSERVATORY, BUILDING_DANCE_SCHOOL, BUILDING_PAVILLION, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_PHYSICIAN
    walkers:[FIGURE_PHYSICIAN]
    buildings:[BUILDING_PHYSICIAN, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_SCRIBAL_SCHOOL
    walkers:[FIGURE_TEACHER]
    buildings:[BUILDING_SCRIBAL_SCHOOL, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_DESIRABILITY
    caption: "Desirability"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_TAX_INCOME
    caption: "Tax income"
    walkers:[FIGURE_TAX_COLLECTOR]
    buildings:[BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED, BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_LABOR_ACCESS
    caption: "Labor access"
    walkers:[FIGURE_LABOR_SEEKER]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }

  {
    id:OVERLAY_CRIMINAL
    caption: "Criminal"
    walkers:[]
    buildings:[BUILDING_ROADBLOCK]
    column_type: COLUMN_TYPE_WATER_ACCESS
    column_anim: {pack:PACK_GENERAL, id:103}
  }
]
