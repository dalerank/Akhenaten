log_info("Ozymandias: load modules started")

var modules = [
    "math",
    "common",
    "city_sounds",
    "mission_sounds",
    "walker_sounds",
    "building_sounds"
]

for (var i in modules) {
    log_info("Loading module " + modules[i])
    load_js_module(":" + modules[i] + ".js")
}
