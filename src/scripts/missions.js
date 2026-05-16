log_info("akhenaten: missions started")

mission_sounds = []
// 0: no traders, less 1500: 1 trader, less 2500: 2 traders, less 4000: 3 traders, less 10000: 4 traders
default_trade_limits = [0, 1500, 2500, 4000, 10000]

for (var i = 0; i < 38; i++) {
	mission_sounds[i] = {
		mission: i
		briefing: _format("Voice/Mission/{0}_mission.mp3", (i + 200).toString())
		victory: _format("Voice/Mission/{0}_victory.mp3", (i + 200).toString())
	}
}

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
		filename: "Alexandria.map"
		mission_id: 128		
	}
	{
		filaneme : "Bridges.map"
		mission_id: 129
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
