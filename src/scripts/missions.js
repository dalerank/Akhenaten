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
    var name = "mission" + scenario_id
    try {
        return eval(name)
    } catch (e) {
        return undefined
    }
}

// Returns choice entries visible after completing completed_id (optional after filter).
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
        next_id = completed_id + 1
    }
    if (next_id < 0 || !__game_mission_is_valid(next_id)) {
        log_info("mission_end_compute_next: completed=" + completed_id
            + " scmode=" + scenario.scmode + " next_id=" + next_id
            + " not a valid campaign step -> end of game")
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
import mission.m_128_alexandria
import mission.m_129_bridges
import mission.m_130_sandbox
import mission.m_131_cataract
import mission.m_132_chariot_blitz
import mission.m_133_empire
import mission.m_134_default
import mission.m_135_enkomi
