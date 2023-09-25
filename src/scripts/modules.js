log_info("Ozymandias: load modules started")

var modules = [
    "math",
    "city_sounds",
    // "main_menu"
]

for (var i in modules) {
    log_info("Loading module " + modules[i])
    load_js_module(":" + modules[i] + ".js")
}
