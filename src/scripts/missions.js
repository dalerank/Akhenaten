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

import mission_0_nubt
import mission_1_thinis
import mission_2_perwadjyt
import mission_3_nekhen
import mission_4_mennefer
import mission_5_timna
import mission_6_behdet
import mission_7_abydos
import mission_8_selima
import mission_9_abu
import mission_10_saqqara
import mission_128_alexandria
import mission_129_bridges
import mission_130_sandbox
import mission_131_cataract
import mission_132_chariot_blitz
import mission_133_empire
import mission_134_default
import mission_135_enkomi