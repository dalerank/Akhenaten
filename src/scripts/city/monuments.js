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
// Stepped pyramids: heavier than mastaba (2), lighter than true pyramid complex (44).
MONUMENT_WEIGHTS[BUILDING_SMALL_STEPPED_PYRAMID]           = 8
MONUMENT_WEIGHTS[BUILDING_MEDIUM_STEPPED_PYRAMID]         = 16
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

// Monument rating is APPROXIMATE and additive, not concave. The original Pharaoh
// aggregates monument points roughly linearly across the built monuments; the old
// concave `6.32*sqrt(sum)+0.5` under-counted multiple monuments (3 small mastabas
// gave 15 instead of the original 18). These constants reproduce the known anchor
// points with the current weights:
//   1 small mastaba   (sum 2)  -> 2.25*2 +4.5 = 9   (missions 4/13/16, and On x1)
//   3 small mastabas  (sum 6)  -> 2.25*6 +4.5 = 18  (mission 17 On)
//   1 medium stepped  (sum 16) -> 2.25*16+4.5 = 40  (>= Saqqara verified goal 19)
// The exact per-monument point table is NOT yet taken from the original (task F3):
// the weights below are placeholders and will be moved to per-building configs and
// recalibrated against the real .pak data later. Until then mission monument goals
// are derived from these constants (see each m_0xx script comment).
var MONUMENT_RATING_MULT = 2.25
var MONUMENT_RATING_OFFSET = 4.5

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
		var monument = city.get_monument(bid)
		if (!monument) {
			continue
		}
		var phase = monument.phase()
		var phases = monument.phases_total()
		var mat = monument.material_pct_min()

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

	// Additive: base offset for having any monument at all, plus a linear term.
	// No monument progress -> rating 0 (avoid the offset leaking in on an
	// unbuilt/zero-progress foundation).
	var rating = 0
	if (sum > 0) {
		rating = MONUMENT_RATING_MULT * sum + MONUMENT_RATING_OFFSET
	}
	if (rating < 0) {
		rating = 0
	}
	if (rating > 100) {
		rating = 100
	}
	__city_ratings_set_monument(rating | 0)
}
