log_info("akhenaten: city_monuments.js started")

var MONUMENT_WEIGHTS = {}
MONUMENT_WEIGHTS[BUILDING_PYRAMID]                        = 44
MONUMENT_WEIGHTS[BUILDING_MUDBRICK_PYRAMID_COMPLEX]       = 44
MONUMENT_WEIGHTS[BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX] = 44
MONUMENT_WEIGHTS[BUILDING_STEPPED_PYRAMID_COMPLEX]        = 44
MONUMENT_WEIGHTS[BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX]  = 44
MONUMENT_WEIGHTS[BUILDING_PYRAMID_COMPLEX]                = 44
MONUMENT_WEIGHTS[BUILDING_GRAND_PYRAMID_COMPLEX]          = 44
MONUMENT_WEIGHTS[BUILDING_SMALL_MASTABA]                  = 2
MONUMENT_WEIGHTS[BUILDING_MEDIUM_MASTABA]                 = 2
MONUMENT_WEIGHTS[BUILDING_LARGE_MASTABA]                  = 3
MONUMENT_WEIGHTS[BUILDING_SPHINX]                         = 1
MONUMENT_WEIGHTS[BUILDING_MAUSOLEUM]                      = 3
MONUMENT_WEIGHTS[BUILDING_ALEXANDRIA_LIBRARY]             = 2
MONUMENT_WEIGHTS[BUILDING_CAESAREUM]                      = 0
MONUMENT_WEIGHTS[BUILDING_PHAROS_LIGHTHOUSE]              = 0
MONUMENT_WEIGHTS[BUILDING_SMALL_ROYAL_TOMB]               = 4
MONUMENT_WEIGHTS[BUILDING_ABU_SIMBEL]                     = 2
MONUMENT_WEIGHTS[BUILDING_MEDIUM_ROYAL_TOMB]              = 1
MONUMENT_WEIGHTS[BUILDING_LARGE_ROYAL_TOMB]               = 1
MONUMENT_WEIGHTS[BUILDING_GRAND_ROYAL_TOMB]               = 4

var MONUMENT_RATING_MULT = 6.32
var MONUMENT_RATING_OFFSET = 0.5

[es=event_advance_month]
function city_update_monthly_monument_rating(ev) {
	var n = __city_monuments_list_refresh()
	if (n == 0) {
		__city_ratings_set_monument(0)
		return
	}

	var sum = 0
	for (var i = 0; i < n; i++) {
		var bid = __city_monuments_list_id_at(i)
		if (!bid) {
			continue
		}
		var bt = __building_type(bid)
		var w = MONUMENT_WEIGHTS[bt]
		if (!w) {
			continue
		}
		var phase = __building_monument_phase_code(bid)
		var phases = __building_monument_phases_total(bid)
		var mat = __building_monument_material_pct_min(bid)

		var progress = 0
		if (phase == -1) {
			progress = 100
		} else if (phases > 0) {
			progress = ((phase - 1) * 100 + mat) / phases
			if (progress < 0) {
				progress = 0
			}
			if (progress > 100) {
				progress = 100
			}
		}

		sum += (w * progress) / 100
	}

	var rating = MONUMENT_RATING_MULT * Math.sqrt(sum) + MONUMENT_RATING_OFFSET
	if (rating < 0) {
		rating = 0
	}
	if (rating > 100) {
		rating = 100
	}
	__city_ratings_set_monument(rating | 0)
}
