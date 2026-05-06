log_info("akhenaten: discord_presence started")

var discord_egyptian_months = [
    "Thoth", "Paopi", "Hathor", "Choiak", "Tybi", "Mekhir", "Phamenoth",
    "Pharmuthi", "Pachons", "Payni", "Epiphi", "Mesore"
]

function discord_presence_city_details() {
    var n = __scenario_scenario_name()
    if (n && n.length > 0) {
        return n
    }
    return "Akhenaten"
}

/** After IO post_load (new mission, save, map); scenario name is valid. */
[es=event_level_post_load]
function discord_presence_on_level_post_load(ev) {
    __discord_rpc_set_activity(discord_presence_city_details(), "Starting up...")
}

[es=event_advance_month]
function discord_presence_on_advance_month(ev) {
    var details = discord_presence_city_details()
    var month = (ev.month >= 0 && ev.month < 12) ? discord_egyptian_months[ev.month] : ""
    var state = "Year " + (ev.years_since_start + 1) + ", " + month
    __discord_rpc_set_activity(details, state)
}
