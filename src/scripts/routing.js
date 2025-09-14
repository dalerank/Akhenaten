log_info("akhenaten: routing rules started")

routing_amphibia = [
	{ type: BUILDING_STORAGE_YARD, penalty: -1 },
	{ type: BUILDING_STORAGE_ROOM, penalty: -1 },
	{ type: BUILDING_FESTIVAL_SQUARE, penalty: 0 },
	{ type: BUILDING_FORT_GROUND, penalty: 0 },
	{ type: BUILDING_BARLEY_FARM, penalty: 0 },
	{ type: BUILDING_FLAX_FARM, penalty: 0 },
	{ type: BUILDING_GRAIN_FARM, penalty: 0 },
	{ type: BUILDING_LETTUCE_FARM, penalty: 0 },
	{ type: BUILDING_POMEGRANATES_FARM, penalty: 0 },
	{ type: BUILDING_CHICKPEAS_FARM, penalty: 0 },
]

routing_citizen = [
	{ type: BUILDING_MUD_GATEHOUSE, penalty: 0 },
	{ type: BUILDING_ROADBLOCK, penalty: 0 },
	{ type: BUILDING_FERRY, penalty: 0 },

	{ type: BUILDING_FORT_GROUND, penalty: 2 },
	{ type: BUILDING_FESTIVAL_SQUARE, penalty: 2 },
]

routing_noncitizen = [
	{ type: BUILDING_STORAGE_YARD, penalty: -1 },
	{ type: BUILDING_STORAGE_ROOM, penalty: -1 },
	{ type: BUILDING_FORT_GROUND, penalty: 0 },

	{ type: BUILDING_FORT_CHARIOTEERS, penalty: 5 },
	{ type: BUILDING_FORT_INFANTRY, penalty: 5 },
	{ type: BUILDING_FORT_ARCHERS, penalty: 5 },
]