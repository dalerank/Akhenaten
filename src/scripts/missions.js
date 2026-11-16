log_info("akhenaten: missions started")

default_marshland_grow {
	random_max : 10
	random_min : 5
}

default_tree_grow {
	random_max : 2
	random_min : 1
}

custom_missions = [
	{
		filename: "data/default.map"
		mission_id: 127
	}
	{
		filename: "Alexandria.map"
		mission_id: 128
	}
	{
		filename: "Bridges.map"
		mission_id: 129
	}
	{
		filename: "Sandbox.map"
		mission_id: 130
	}
	{
		filename: "Cataract.map"
		mission_id: 131
	}
	{
		filename: "Chariot Blitz.map"
		mission_id: 132
	}
	{
		filename: "Empire.map"
		mission_id: 133
	}
	{
		filename: "Default.map"
		mission_id: 134
	}
	{
		filename: "Enkomi.map"
		mission_id: 135
	}
]

function get_mission_config(scenario_id) {
    return __js_global("mission" + scenario_id)
}

function mission_is_playable(scenario_id) {
    if (get_mission_config(scenario_id) === undefined) {
        return false
    }
    // --no-resource skips campaign.txt; JS mission configs are enough in hermetic runs.
    if (!__game_has_campaign_data()) {
        return true
    }
    return __game_mission_is_valid(scenario_id)
}

function mission_get_visible_choices(mission_config, completed_id) {
    if (!mission_config || !mission_config.choice || mission_config.choice.length === 0) {
        return []
    }

    var out = []
    var seen = {}
    for (var i = 0; i < mission_config.choice.length; i++) {
        var pt = mission_config.choice[i]
        if (!pt || pt.id === undefined || pt.id === null) {
            continue
        }
        if (pt.after !== undefined && pt.after !== null && pt.after !== completed_id) {
            continue
        }
        if (!mission_is_playable(pt.id)) {
            log_info("mission_choice: dropping choice target " + pt.id + " — not a scripted/playable mission yet (B5)")
            continue
        }
        if (seen[pt.id]) {
            continue
        }
        seen[pt.id] = true
        out.push(pt)
    }
    return out
}

function mission_has_post_victory_choice(completed_id) {
    var src = get_mission_config(completed_id)
    return mission_get_visible_choices(src, completed_id).length > 0
}

function mission_end_compute_next_scenario_id(completed_id) {
    if (scenario.scmode == e_scenario_custom_map || scenario.scmode == e_scenario_selected) {
        log_info("mission_end_compute_next: free/custom play, ending session")
        return -1
    }
    var src = get_mission_config(completed_id)
    var next_id = (src && src.next_mission) ? src.next_mission : 0

    if (!next_id) {
        if (src && src.choice && src.choice.length > 0) {
            log_info("mission_end_compute_next: completed=" + completed_id
                + " has choice[] and no next_mission -> end of game (no completed+1)")
            return -1
        }
        next_id = completed_id + 1
    }
    if (next_id < 0 || !mission_is_playable(next_id)) {
        log_info("mission_end_compute_next: completed=" + completed_id
            + " scmode=" + scenario.scmode + " next_id=" + next_id
            + " not a scripted/playable campaign step -> end of game")
        return -1
    }
    log_info("mission_end_compute_next: completed=" + completed_id + " scmode=" + scenario.scmode + " -> next_scenario_id=" + next_id)
    return next_id
}

function mission_should_reshow_start_message() {
    if (game.session_last_loaded_kind != e_session_save) {
        return false
    }
    return game.simtime.year == scenario.start_year && game.simtime.month == 0
}

function mission_show_start_message(mission, message_id) {
    if (mission.start_message_shown && mission_should_reshow_start_message()) {
        mission.start_message_shown = false
        log_info("mission_start_message: cleared for early save load m=" + game.simtime.month)
    }

    if (mission.start_message_shown) {
        return
    }

    if (!message_id || message_id.length == 0) {
        return
    }

    ui.popup_message(message_id)
    mission.start_message_shown = true
}

// Recurring request cadence (pak): do not start the next cycle while a request for
// this resource is still active; after it clears, wait ≥1 month before firing again.
// Call update_idle every month; may_fire at the calendar slot (e.g. month 7).
// Mission vars (prefix = e.g. "pharaoh_copper_recurring"):
//   {prefix}_was_busy, {prefix}_idle_since_abs
function mission_recurring_request_update_idle(mission, resource, prefix, abs_month) {
    var was_busy_key = prefix + "_was_busy"
    var idle_key = prefix + "_idle_since_abs"
    if (city.has_active_request(resource)) {
        mission[was_busy_key] = true
        return
    }
    if (mission[was_busy_key]) {
        mission[was_busy_key] = false
        mission[idle_key] = abs_month
    }
}

function mission_recurring_request_may_fire(mission, resource, prefix, abs_month) {
    mission_recurring_request_update_idle(mission, resource, prefix, abs_month)
    if (city.has_active_request(resource)) {
        return false
    }
    var idle = mission[prefix + "_idle_since_abs"]
    if (typeof idle === "number" && idle >= 0 && abs_month <= idle) {
        return false
    }
    return true
}

// OG invasion.c invasion_land_point: invasion_points_land[location - 1] or the next point set after it,
// else the map exit.
function mission_raid_land_tile(config, location) {
	var lands = config.invasion_points_land || []
	for (var i = 0; i < 8; i++) {
		var p = lands[(location - 1 + i) % 8]
		if (p) {
			return p
		}
	}
	return config.exit_point || [-1, -1]
}

// Raids from mission JS for the invasions of the original's events[], vs OG scenario_events.c
// scenario_event_process_invasion: from the event's date the OG warnings (the announcement, then the reminders at
// 24 / 12 / 6 / 1 months left), and the attack months_initial months later. A raid (the OG event's fields):
//   key, invader (EVENT_INVADER_*, picks the phrases), enemy (ENEMY_*), amount, months_initial,
//   location [value, fixed, min, max] (OG location_fields, rolled when the raid is scheduled), warships,
//   attack_target; what its on_completed chains as it attacks: chain_tag (an events[] tag), chain_event (the
//   city.create_chain_event options of that event), on_attack(seq) (a longer chain), then [{ key, delay }]
//   (raids, due `delay` months later: the child's time.year); year + month (a calendar event), recurring
//   (OG EVENT_FLAG_RECURRING).
// The state lives in the mission var `raids` (JSON): key -> { date, loc, seq, done }.
function mission_raids_state(mission) {
	var text = mission.raids
	return text ? JSON.parse(text) : {}
}

function mission_months_since_start() {
	return (game.simtime.year - scenario.start_year) * 12 + game.simtime.month
}

function mission_raid_roll_location(raid) {
	var l = raid.location
	return l.length ? __city_roll_event_value(l[0], l[1], l[2], l[3]) : l
}

function mission_raid_find(raids, key) {
	for (var i = 0; i < raids.length; i++) {
		if (raids[i].key == key) {
			return raids[i]
		}
	}
	return null
}

function mission_raid_arm(state, raid, date) {
	state[raid.key] = { date: date, loc: mission_raid_roll_location(raid), seq: 0, done: false }
	log_info("akhenaten: mission raid " + raid.key + " due m" + date + " location " + state[raid.key].loc)
}

// A chain or a cleared request sends raid `key`: its event date is `delay` months from now.
function mission_raid_schedule(mission, raids, key, delay) {
	var state = mission_raids_state(mission)
	mission_raid_arm(state, mission_raid_find(raids, key), mission_months_since_start() + delay)
	mission.raids = JSON.stringify(state)
}

function mission_raid_over(seq) {
	if (!seq) {
		return true
	}
	var n = city.invasion_history_count()
	for (var i = 0; i < n; i++) {
		var h = city.invasion_history_at(i)
		if (h.seq == seq) {
			return h.outcome != 0
		}
	}
	return true
}

// The attack, vs OG invasion.c scenario_invasion_start: location 9 and up sails from sea point location - 9 with
// `warships`, the Persians always land by the map entry, others at mission_raid_land_tile. Returns the sequence.
function mission_start_raid(config, raid, location) {
	var opts = {
		invasion_id: raid.invasion_id,
		invader: raid.invader,
		enemy: raid.enemy,
		size: raid.amount,
		months_initial: raid.months_initial,
		location: location,
		invasion_attack_target: raid.attack_target
	}
	if (location >= 9) {
		opts.via_sea = 1
		opts.sea_point = location - 9
		opts.warships = raid.warships || 0
	} else if (raid.enemy != ENEMY_9_PERSIAN) {
		var tile = mission_raid_land_tile(config, location)
		opts.tilex = tile[0]
		opts.tiley = tile[1]
	}
	var seq = city.start_foreign_army_invasion(opts)
	log_info("akhenaten: mission raid " + raid.key + " id=" + raid.invasion_id + " enemy=" + raid.enemy
		+ " size=" + raid.amount + " location=" + location + " warships=" + (opts.warships || 0) + " seq=" + seq)
	return seq
}

// One raid's month: the warning due since its date, or the attack; returns the raids its on_completed chains.
function mission_raid_month(config, raid, st, now) {
	var since = now - st.date
	if (since < 0) {
		return []
	}
	if (since > raid.months_initial) {
		// OG scenario_event_is_running: past its months the event never runs.
		st.done = true
		return []
	}
	if (since < raid.months_initial) {
		__city_invasion_warning({ invasion_id: raid.invasion_id, invader: raid.invader, size: raid.amount,
			months_initial: raid.months_initial, location: st.loc, months_since: since })
		return []
	}
	st.seq = mission_start_raid(config, raid, st.loc)
	st.done = true
	if (raid.chain_event) {
		city.create_chain_event(raid.chain_event)
		__city_event_fire_chain(raid.chain_event.tag_id)
	}
	if (raid.chain_tag) {
		__city_event_fire_chain(raid.chain_tag)
	}
	if (raid.on_attack) {
		raid.on_attack(st.seq)
	}
	return raid.then || []
}

// Monthly: arms the calendar raids in their month, posts the warnings and starts the attacks that are due,
// rearms a recurring raid once its army is gone (OG scenario_events_rearm: its year plus the years since start).
function mission_raids_month(mission, config, ev, raids) {
	var state = mission_raids_state(mission)
	var now = ev.years_since_start * 12 + ev.month
	var chained = []
	for (var i = 0; i < raids.length; i++) {
		var raid = raids[i]
		var st = state[raid.key]
		if (!st && raid.year !== undefined && now == raid.year * 12 + raid.month) {
			mission_raid_arm(state, raid, now)
			st = state[raid.key]
		}
		if (!st) {
			continue
		}
		if (!st.done) {
			chained = chained.concat(mission_raid_month(config, raid, st, now))
		} else if (raid.recurring && mission_raid_over(st.seq)) {
			mission_raid_arm(state, raid, (raid.year + ev.years_since_start) * 12 + raid.month)
		}
	}
	// OG scenario_event_chain: a chained invasion is due `delay` months on; an undelayed one runs at once.
	while (chained.length) {
		var link = chained.shift()
		var child = mission_raid_find(raids, link.key)
		mission_raid_arm(state, child, now + link.delay)
		if (link.delay == 0) {
			chained = chained.concat(mission_raid_month(config, child, state[child.key], now))
		}
	}
	mission.raids = JSON.stringify(state)
}

// Derive ok/late/refuse from factual event_request_cleared (no KR read).
function mission_request_outcome(ev) {
	if (!ev || !ev.fulfilled) {
		return "refuse"
	}
	if (ev.was_overdue) {
		return "late"
	}
	return "ok"
}

import mission.m_000_nubt
import mission.m_001_thinis
import mission.m_002_perwadjyt
import mission.m_003_nekhen
import mission.m_004_mennefer
import mission.m_005_timna
import mission.m_006_behdet
import mission.m_007_abydos
import mission.m_008_selima
import mission.m_009_abu
import mission.m_010_saqqara
import mission.m_011_serabit_khadim
import mission.m_012_meidum
import mission.m_013_buhen
import mission.m_014_south_dahshur
import mission.m_015_north_dahshur
import mission.m_016_iunet
import mission.m_017_on
import mission.m_018_rostja
import mission.m_019_bahariya
import mission.m_020_djedu
import mission.m_021_dunqul
import mission.m_022_dakhla
import mission.m_023_thinis
import mission.m_024_waset
import mission.m_025_kebet
import mission.m_026_menat_khufu
import mission.m_027_itjtawy
import mission.m_028_iken
import mission.m_029_sawu
import mission.m_030_heh
import mission.m_031_bubastis
import mission.m_032_khmun
import mission.m_033_sauty
import mission.m_034_byblos
import mission.m_035_baki
import mission.m_036_rowarty
import mission.m_037_hetepsensusret
import mission.m_038_valley_thutmose
import mission.m_039_valley_tut
import mission.m_040_valley_seti
import mission.m_041_sumur
import mission.m_042_qadesh
import mission.m_043_abu_simbel
import mission.m_044_ramses_in_the_valley
import mission.m_045_pi_yer
import mission.m_046_migdol
import mission.m_047_tanis
import mission.m_048_alexandria_1
import mission.m_049_alexandria_2
import mission.m_050_maritis
import mission.m_051_alexandria_3
import mission.m_052_actium
import mission.m_128_alexandria
import mission.m_129_bridges
import mission.m_130_sandbox
import mission.m_131_cataract
import mission.m_132_chariot_blitz
import mission.m_133_empire
import mission.m_134_default
import mission.m_135_enkomi
