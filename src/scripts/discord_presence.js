log_info("akhenaten: discord_presence started")

var discord_egyptian_months = [
    "Thoth", "Paopi", "Hathor", "Choiak", "Tybi", "Mekhir", "Phamenoth",
    "Pharmuthi", "Pachons", "Payni", "Epiphi", "Mesore"
]

/** Prefer localized mission title (same as briefing); else open-play player name; else raw scenario_name (often a filename like map10). */
function discord_presence_city_details(ev) {
    var sid
    if (ev && typeof ev.scenario_id !== "undefined") {
        sid = ev.scenario_id
    } else {
        sid = scenario.campaign_scenario_id
    }
    if (sid >= 0) {
        var loc = __lang_message_title_text(200 + sid)
        if (loc && loc.length > 0) {
            return loc
        }
    }
    if (scenario.is_open_play) {
        var pname = player.name
        if (pname && pname.length > 0) {
            return pname
        }
    }
    var n = scenario.scenario_name
    if (n && n.length > 0) {
        return n
    }
    return "Akhenaten"
}

/** After IO post_load (new mission, save, map); scenario name is valid. */
[es=event_level_post_load]
function discord_presence_on_level_post_load(ev) {
    var details = discord_presence_city_details(ev)
    __discord_rpc_set_activity(details, "")
}

[es=event_advance_month]
function discord_presence_on_advance_month(ev) {
    var details = discord_presence_city_details(null)
    var month = (ev.month >= 0 && ev.month < 12) ? discord_egyptian_months[ev.month] : ""
    var state = "Year " + (ev.years_since_start + 1) + ", " + month
    __discord_rpc_set_activity(details, state)
}
