log_info("akhenaten: city warnings started")

var city_warning_delays = {}

city.warnings.add = function (id) {
    if ((city_warning_delays[id] || 0) > 0) {
        return
    }

    city.warnings.show(id)
    city_warning_delays[id] = window_warnings.message_interval
}

[es=event_advance_day]
function city_warnings_tick_delays(ev) {
    for (var id in city_warning_delays) {
        if (city_warning_delays[id] > 0) {
            city_warning_delays[id]--
        }
    }
}

[es=event_advance_month]
function city_warnings_on_month(ev) {
    __city_warnings_run("city_warnings", "update_monthly")
}

[console_command=show_warning]
function console_command_show_warning(args) {
    var force = false
    var start = 0
    if (args && args.length > 0 && args[0] === "force") {
        force = true
        start = 1
    }

    var text = ""
    for (var i = start; i < (args ? args.length : 0); i++) {
        if (text.length > 0) {
            text += " "
        }
        text += args[i]
    }
    if (text.length === 0) {
        text = "Test warning"
    }

    if (force) {
        city.warnings.show(text)
    } else {
        city.warnings.add(text)
    }
}
