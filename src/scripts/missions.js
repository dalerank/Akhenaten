log_info("akhenaten: missions started")

// 0: no traders, less 1500: 1 trader, less 2500: 2 traders, less 4000: 3 traders, less 10000: 4 traders
default_trade_limits = [0, 1500, 2500, 4000, 10000]

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
    if (scenario.scmode == e_scenario_custom_map) {
        log_info("mission_end_compute_next: custom map, ending campaign")
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

function mission_show_start_message(mission, message_id) {
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

import mission.mission_favour_events
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
