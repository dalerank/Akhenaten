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
import mission.m_128_alexandria
import mission.m_129_bridges
import mission.m_130_sandbox
import mission.m_131_cataract
import mission.m_132_chariot_blitz
import mission.m_133_empire
import mission.m_134_default
import mission.m_135_enkomi
