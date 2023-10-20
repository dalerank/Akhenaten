log_info("akhenaten: overlays started")

overlays = [
  {
  	id:OVERLAY_RELIGION_OSIRIS,
  	caption:"Osiris",
  	walkers:[FIGURE_PRIEST],
  	buildings:[BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS],
  	tooltip_base:0,
  	tooltips:[]
  },

  {
  	id:OVERLAY_RELIGION_RA,
  	caption:"Ra",
  	walkers:[FIGURE_PRIEST],
  	buildings:[BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA],
  	tooltip_base:0,
  	tooltips:[]
  }
]
