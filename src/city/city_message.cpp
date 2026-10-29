#include "city_message.h"

#include "io/io_buffer.h"
#include "scenario/scenario_event_manager.h"
#include "content/vfs.h"
#include "core/encoding.h"
#include "core/log.h"
#include "core/string.h"
#include "city/city_religion.h"
#include "city/city_warnings.h"
#include "figure/formation.h"
#include "graphics/window.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "sound/sound.h"
#include "window/message_dialog.h"
#include "game/game_events.h"
#include "game/game.h"
#include "game/game_config.h"
#include "scenario/scenario.h"

message_manager_t g_message_manager;

static bool should_play_sound = true;

struct popup_key_map_entry {
    pcstr key;
    e_popup_message_category cat;
};

// Exact message keys → OG Popup Messages category (group 310).
static const popup_key_map_entry POPUP_KEY_MAP[] = {
    { "message_perfect_inundation", POPUP_MSG_FLOOD },
    { "message_excellent_inundation", POPUP_MSG_FLOOD },
    { "message_good_inundation", POPUP_MSG_FLOOD },
    { "message_mediocre_inundation", POPUP_MSG_FLOOD },
    { "message_poor_inundation", POPUP_MSG_FLOOD },
    { "message_no_inundation", POPUP_MSG_FLOOD },
    { "message_mediocre_inundation_seers", POPUP_MSG_FLOOD },
    { "message_poor_inundation_seers", POPUP_MSG_FLOOD },

    { "message_population_milestone_100", POPUP_MSG_POPULATION },
    { "message_population_milestone_500", POPUP_MSG_POPULATION },
    { "message_population_milestone_1000", POPUP_MSG_POPULATION },
    { "message_population_milestone_2000", POPUP_MSG_POPULATION },
    { "message_population_milestone_3000", POPUP_MSG_POPULATION },
    { "message_population_milestone_5000", POPUP_MSG_POPULATION },
    { "message_population_milestone_10000", POPUP_MSG_POPULATION },
    { "message_population_milestone_15000", POPUP_MSG_POPULATION },
    { "message_population_milestone_20000", POPUP_MSG_POPULATION },
    { "message_population_milestone_25000", POPUP_MSG_POPULATION },

    { "message_compliance_now_possible", POPUP_MSG_COMPLIANCE },
    // Actual goods/deben "can fulfill request" post (request.cpp); same OG category.
    { "message_storage_yards_ready_to_fulfill_request", POPUP_MSG_COMPLIANCE },

    { "message_common_festival", POPUP_MSG_FESTIVALS },
    { "message_lavish_festival", POPUP_MSG_FESTIVALS },
    { "message_grand_festival", POPUP_MSG_FESTIVALS },

    { "message_small_blessing_from_osiris", POPUP_MSG_MINOR_BLESSINGS },
    { "message_minor_blessing_from_ra", POPUP_MSG_MINOR_BLESSINGS },
    { "message_minor_blessing_from_ptah", POPUP_MSG_MINOR_BLESSINGS },
    { "message_minor_blessing_from_seth", POPUP_MSG_MINOR_BLESSINGS },
    { "message_small_blessing_from_bast", POPUP_MSG_MINOR_BLESSINGS },
    { "message_minor_blessing_trading_from_ra", POPUP_MSG_MINOR_BLESSINGS },

    { "message_price_increased", POPUP_MSG_PRICE },
    { "message_price_decreased", POPUP_MSG_PRICE },

    { "message_increased_trading", POPUP_MSG_TRADE_LEVEL },
    { "message_decreased_trading", POPUP_MSG_TRADE_LEVEL },
    { "message_trade_stopped", POPUP_MSG_TRADE_LEVEL },

    { "message_kingdome_raises_wages", POPUP_MSG_WAGE },
    { "message_kingdome_lowers_wages", POPUP_MSG_WAGE },

    { "message_disease", POPUP_MSG_DISEASE },
    { "message_disease_strikes", POPUP_MSG_DISEASE },
    { "message_malaria", POPUP_MSG_MALARIA },
    { "malaria_problem", POPUP_MSG_MALARIA }, // legacy key from city_health
    { "message_employees_needed", POPUP_MSG_EMPLOYEES },
};

e_popup_message_category popup_message_category_for_key(xstring message_key) {
    if (message_key.empty()) {
        return POPUP_MSG_NONE;
    }
    for (const auto &e : POPUP_KEY_MAP) {
        if (message_key == e.key) {
            return e.cat;
        }
    }
    return POPUP_MSG_NONE;
}

bool popup_messages_bit_set(e_popup_message_category cat) {
    if (cat < 0 || cat >= POPUP_MSG_MAX) {
        return false;
    }
    const int mask = game_features::gameopt_popup_messages.to_int();
    return (mask & (1 << (int)cat)) != 0;
}

bool popup_messages_want_banner(e_popup_message_category cat) {
    return popup_messages_bit_set(cat);
}

void popup_messages_set_banner(e_popup_message_category cat, bool banner) {
    if (cat < 0 || cat >= POPUP_MSG_MAX) {
        return;
    }
    int mask = game_features::gameopt_popup_messages.to_int();
    if (banner) {
        mask |= (1 << (int)cat);
    } else {
        mask &= ~(1 << (int)cat);
    }
    game_features::gameopt_popup_messages.set(mask);
}

void messages::popup(xstring message_id, int param1, int param2) {
    events::emit(event_message{ true, message_id, param1, param2 });
}

void messages::god(int god, xstring message_id) {
    events::emit(event_message_god{ god, message_id });
}

void message_manager_t::init() {
    for (int i = 0; i < MAX_MESSAGES; i++) {
        messages[i].MM_text_id = 0;
    }
    for (int i = 0; i < MAX_MESSAGES_QUEUE; i++) {
        queue[i] = 0;
    }
    consecutive_message_delay = 0;

    // Queue slots use 0 as empty sentinel — sequences must start at 1.
    next_message_sequence = 1;
    total_messages = 0;
    current_message_id = 0;

    for (int i = 0; i < MESSAGE_CAT_SIZE; i++) {
        message_count[i] = 0;
        message_delay[i] = 0;
    }
    // population
    population_shown.pop500 = 0;
    population_shown.pop1000 = 0;
    population_shown.pop2000 = 0;
    population_shown.pop3000 = 0;
    population_shown.pop5000 = 0;
    population_shown.pop10000 = 0;
    population_shown.pop15000 = 0;
    population_shown.pop20000 = 0;
    population_shown.pop25000 = 0;

    for (int i = 0; i <= MESSAGE_CAT_RIOT_COLLAPSE; i++) {
        last_sound_time[i] = 0;
    }

    init_problem_areas();

    static bool subscriptions_initialized = false;
    if (!subscriptions_initialized) {
        subscriptions_initialized = true;

        events::subscribe([this] (event_message ev) {
            auto& msg = post_common(ev.use_popup, ev.message_id, ev.param1, ev.param2, GOD_UNKNOWN, 0);
            msg.src_location = ev.src_location;
        });

        events::subscribe([this] (event_message_god ev) {
            post_common(true, ev.message_id, 0, 0, ev.god, 0);
        });

        events::subscribe([this] (event_message_population ev) {
            post_common(ev.use_popup, ev.message_id, 0, 0, GOD_UNKNOWN, messages::IMAGE_FROM_SCHEME);
        });
    }
}

void message_manager_t::init_problem_areas() {
    problem_count = 0;
    problem_index = 0;
    problem_last_click_time = time_get_millis();
}

int message_manager_t::new_message_id() {
    for (int i = 0; i < MAX_MESSAGES; i++) {
        if (!messages[i].MM_text_id)
            return i;
    }
    return -1;
}

int message_manager_t::alloc_message(xstring template_id) {
    int id = new_message_id();
    if (id < 0) {
        return -1;
    }

    if (lang_get_message_uid(template_id) == 0) {
        logs::info("messages::alloc: unknown message id '%s' - popup suppressed", template_id.c_str());
        return -1;
    }

    total_messages++;
    current_message_id = id;

    city_message &msg = messages[id];
    memset(&msg, 0, sizeof(city_message));
    // Non-event list UI treats unset eventmsg ids as "no eventmsg".
    msg.eventmsg_body_id = -1;
    msg.eventmsg_title_id = -1;
    msg.eventmsg_phrase_id = -1;

    msg.MM_text_id = lang_get_message_uid(template_id);
    msg.is_read = 0;
    msg.year = game.simtime.year;
    msg.month = game.simtime.month;
    // Queue slots use 0 as empty sentinel — sequences must start at 1.
    if (next_message_sequence <= 0) {
        next_message_sequence = 1;
    }
    msg.sequence = next_message_sequence++;

    return id;
}

static void fill_from_event(city_message &msg, const event_ph_t *event, int parent_event_id) {
    if (!event) {
        return;
    }

    msg.sender_faction = event->sender_faction;
    msg.req_resource = event->item.value;
    msg.req_amount = event->amount.value;
    if (msg.req_amount < 100) {
        msg.req_amount *= 100;
    }
    msg.req_city = event->city_id > 0 ? event->city_id : event->location_fields[0] - 1;

    if (event->is_active) {
        msg.req_months_left = event->quest_months_left;
    } else {
        msg.req_months_left = event->months_initial;
    }

    if (parent_event_id >= 0) {
        const event_ph_t *parent_event = g_scenario.events.at(parent_event_id);
        msg.req_resource_past = parent_event->item.value;
        msg.req_amount_past = parent_event->amount.value;
        msg.req_city_past = parent_event->location_fields[0] - 1;
    } else {
        msg.req_resource_past = -1;
        msg.req_amount_past = -1;
        msg.req_city_past = -1;
    }

    if (event->image.valid()) {
        image_desc tmp_img = event->image;
        int image_id = tmp_img.tid();
        if (image_id >= 0) {
            msg.background_img = image_id;
        }
    }
}

static bool has_video(const lang_message& template_id) {
    bstring256 path = ui::message_dialog_base::resolve_message_video_path(template_id);
    return !path.empty() && vfs::file_exists(path);
}

static void enqueue_message(int sequence) {
    auto& data = g_message_manager;
    for (int i = 0; i < MAX_MESSAGES_QUEUE; i++) {
        if (!data.queue[i]) {
            data.queue[i] = sequence;
            break;
        }
    }
}

static void play_sound(const lang_message &template_id) {
    if (template_id.urgent) {
        g_sound.play_effect(SOUND_EFFECT_FANFARE_URGENT);
    } else {
        g_sound.play_effect(SOUND_EFFECT_FANFARE);
    }
}

static void show_message_popup(int index) {
    auto& data = g_message_manager;
    city_message& msg = data.messages[index];
    data.consecutive_message_delay = 5;
    msg.is_read = true;
    const lang_message& message_template = lang_get_message(msg.MM_text_id);
    if (!has_video(message_template)) {
        play_sound(message_template);
    }

    xstring message_uid = lang_get_message_id(msg.MM_text_id);
    window_message_dialog_show_city_message(message_uid, index, msg.year, msg.month, msg.param1, msg.param2, message_template.advisor, true);
}

int city_message_find_index_by_sequence(int sequence) {
    if (sequence < 0) {
        return -1;
    }
    for (int i = 0; i < MAX_MESSAGES; i++) {
        if (g_message_manager.messages[i].MM_text_id && g_message_manager.messages[i].sequence == sequence) {
            return i;
        }
    }
    return -1;
}

void city_message_show_from_archive(int message_index) {
    if (message_index < 0 || message_index >= MAX_MESSAGES) {
        return;
    }
    if (!g_message_manager.messages[message_index].MM_text_id) {
        return;
    }
    show_message_popup(message_index);
}

static void show_message_banner_for_index(int index) {
    city_message &msg = g_message_manager.messages[index];
    xstring title;
    if (msg.eventmsg_title_id >= 0) {
        title = g_scenario.events.msg_text(msg.eventmsg_title_id, 0);
    } else {
        const lang_message &tmpl = lang_get_message(msg.MM_text_id);
        title = tmpl.title.text;
    }
    if (title.empty()) {
        title = lang_get_message_id(msg.MM_text_id);
    }
    g_warning_manager.show_message_banner(title.c_str(), msg.sequence);
}

static void apply_popup_delivery(bool use_popup, e_popup_message_category popup_cat, int message_index, xstring sound_template_key) {
    if (use_popup && popup_messages_want_banner(popup_cat)) {
        show_message_banner_for_index(message_index);
        // I3: quiet UI chime instead of fanfare on banner path.
        g_sound.play_effect(SOUND_EFFECT_ICON);
        should_play_sound = true;
        return;
    }
    if (use_popup && g_window_manager.window_is("window_city")) {
        show_message_popup(message_index);
    } else if (use_popup) {
        enqueue_message(g_message_manager.messages[message_index].sequence);
    } else if (should_play_sound) {
        const lang_message &mm_template = lang_get_message(sound_template_key);
        play_sound(mm_template);
    }
    should_play_sound = true;
}

void city_message_disable_sound_for_next_message(void) {
    should_play_sound = false;
}

void city_message_apply_sound_interval(int category) {
    auto& data = g_message_manager;
    time_millis now = time_get_millis();
    if (now - data.last_sound_time[category] <= 15000) {
        city_message_disable_sound_for_next_message();
    } else {
        data.last_sound_time[category] = now;
    }
}

void city_message_post_full(bool use_popup, xstring template_id, const event_ph_t *event, int parent_event_id, int title_id, int body_id, int phrase_id, int param1, int param2, e_popup_message_category popup_cat) {
    auto& data = g_message_manager;
    int id = data.alloc_message(template_id);
    if (id < 0) {
        return;
    }

    city_message &msg = data.messages[id];
    msg.eventmsg_title_id = title_id;
    msg.eventmsg_body_id = body_id;
    msg.eventmsg_phrase_id = phrase_id;
    msg.param1 = param1;
    msg.param2 = param2;
    msg.god = GOD_UNKNOWN;
    fill_from_event(msg, event, parent_event_id);

    if (popup_cat == POPUP_MSG_NONE) {
        popup_cat = popup_message_category_for_key(template_id);
    }
    apply_popup_delivery(use_popup, popup_cat, id, template_id);
}

city_message &message_manager_t::post_common(bool use_popup, xstring mm_text, int param1, int param2, int god, int bg_img) {
    int id = alloc_message(mm_text);
    if (id < 0) {
        static city_message dummy;
        return dummy;
    }

    city_message &msg = messages[id];
    msg.param1 = param1;
    msg.param2 = param2;
    msg.god = god;
    msg.hide_img = false;
    msg.background_img = bg_img;

    const lang_message &mm_template = lang_get_message(mm_text);
    int lang_msg_type = mm_template.message_type;
    if (lang_msg_type == MESSAGE_TYPE_DISASTER || lang_msg_type == MESSAGE_TYPE_INVASION) {
        problem_count = 1;
    }

    apply_popup_delivery(use_popup, popup_message_category_for_key(mm_text), id, mm_text);

    return msg;
}

city_message &city_message_post_with_popup_delay(e_mesage_category category, bool force_popup, xstring text, int param1, short param2) {
    auto& data = g_message_manager;
    bool use_popup = false;

    if (data.message_delay[category] <= 0) {
        use_popup = true;
        data.message_delay[category] = 12;
    }
    use_popup |= force_popup;

    city_message &message = data.post_common(use_popup, text, param1, param2, GOD_UNKNOWN, 0);
    data.message_count[category]++;

    return message;
}

void city_message_post_with_message_delay(e_mesage_category category, int use_popup, xstring message_type, int delay) {
    auto& data = g_message_manager;
    if (category == MESSAGE_CAT_FISHING_BLOCKED || category == MESSAGE_CAT_NO_WORKING_DOCK) {
        // bug in the original game: delays for 'fishing blocked' and 'no working dock'
        // are stored in message_count with manual countdown
        if (data.message_count[category] > 0) {
            data.message_count[category]--;
        } else {
            data.message_count[category] = delay;
            data.post_common(use_popup, message_type, 0, 0, GOD_UNKNOWN, 0);
        }
    } else {
        if (data.message_delay[category] <= 0) {
            data.message_delay[category] = delay;
            data.post_common(use_popup, message_type, 0, 0, GOD_UNKNOWN, 0);
        }
    }
}

void city_message_process_queue() {
    auto& data = g_message_manager;
    if (data.consecutive_message_delay > 0) {
        data.consecutive_message_delay--;
        return;
    }
    int sequence = 0;
    for (int i = 0; i < MAX_MESSAGES_QUEUE; i++) {
        if (data.queue[i]) {
            sequence = data.queue[i];
            data.queue[i] = 0;
            break;
        }
    }
    if (sequence == 0)
        return;
    int message_id = -1;
    for (int i = 0; i < 999; i++) {
        if (!data.messages[i].MM_text_id)
            return;
        if (data.messages[i].sequence == sequence) {
            message_id = i;
            break;
        }
    }
    if (message_id >= 0)
        show_message_popup(message_id);
}

void city_message_sort_and_compact(void) {
    auto& data = g_message_manager;
    for (int i = 0; i < MAX_MESSAGES; i++) {
        for (int a = 0; a < MAX_MESSAGES - 1; a++) {
            int swap = 0;
            if (data.messages[a].MM_text_id) {
                if (data.messages[a].sequence < data.messages[a + 1].sequence) {
                    if (data.messages[a + 1].MM_text_id)
                        swap = 1;
                }
            } else if (data.messages[a + 1].MM_text_id)
                swap = 1;

            if (swap) {
                city_message tmp_message = data.messages[a];
                data.messages[a] = data.messages[a + 1];
                data.messages[a + 1] = tmp_message;
            }
        }
    }
    data.total_messages = 0;
    for (int i = 0; i < MAX_MESSAGES; i++) {
        if (data.messages[i].MM_text_id)
            data.total_messages++;
    }
}

int city_message_get_text_id(int message_id) {
    return message_id;
}

void city_message_reset_category_count(e_mesage_category category) {
    auto& data = g_message_manager;
    data.message_count[category] = 0;
}
void city_message_increase_category_count(e_mesage_category category) {
    auto& data = g_message_manager;
    data.message_count[category]++;
}
int city_message_get_category_count(e_mesage_category category) {
    auto& data = g_message_manager;
    return data.message_count[category];
}

void city_message_decrease_delays(void) {
    auto& data = g_message_manager;
    for (int i = 0; i < MESSAGE_CAT_SIZE; i++) {
        if (data.message_delay[i] > 0)
            data.message_delay[i]--;
    }
}

bool city_message_mark_population_shown(int population) {
    auto& data = g_message_manager;
    bool lastv = false;
    switch (population) {
    case 100: lastv = data.population_shown.pop500; data.population_shown.pop100 = true; return lastv;
    case 500: lastv = data.population_shown.pop500; data.population_shown.pop500 = true; return lastv;
    case 1000: lastv = data.population_shown.pop1000; data.population_shown.pop1000 = true; return lastv;
    case 2000: lastv = data.population_shown.pop2000; data.population_shown.pop2000 = true; return lastv;
    case 3000: lastv = data.population_shown.pop3000; data.population_shown.pop3000 = true; return lastv;
    case 5000: lastv = data.population_shown.pop5000; data.population_shown.pop5000 = true; return lastv;
    case 10000: lastv = data.population_shown.pop10000; data.population_shown.pop10000 = true; return lastv;
    case 15000: lastv = data.population_shown.pop15000; data.population_shown.pop15000 = true; return lastv;
    case 20000: lastv = data.population_shown.pop20000; data.population_shown.pop20000 = true; return lastv;
    case 25000: lastv = data.population_shown.pop25000; data.population_shown.pop25000 = true; return lastv;
    default:
        return false;
    }
}

const city_message& city_message_get(int message_id) {
    const auto& data = g_message_manager;
    return data.messages[message_id];
}

void city_message_mark_read(int message_id) {
    auto& data = g_message_manager;
    data.messages[message_id].is_read = 1;
}

void city_message_delete(int message_id) {
    auto& data = g_message_manager;
    data.messages[message_id].MM_text_id = 0;
    city_message_sort_and_compact();
}

int city_message_count() {
    auto& data = g_message_manager;
    return data.total_messages;
}

int city_message_problem_area_count() {
    auto& data = g_message_manager;
    return data.problem_count;
}

int has_problem_area(const city_message* msg, int lang_msg_type) {
    if (lang_msg_type == MESSAGE_TYPE_DISASTER)
        return 1;

    if (lang_msg_type == MESSAGE_TYPE_INVASION) {
        if (formation_grid_offset_for_invasion(msg->param1))
            return 1;

        // Formations have not been updated yet because the invasion just started.
        // Invasions always start at the end of the month: return true when we're in
        // the next month
        return (msg->month + 1) % simulation_time_t::months_in_year == game.simtime.month && msg->year + (msg->month + 1) / simulation_time_t::months_in_year == game.simtime.year;
    }
    return 0;
}

int city_message_next_problem_area_grid_offset() {
    auto& data = g_message_manager;
    time_millis now = time_get_millis();
    if (now - data.problem_last_click_time > 3000)
        data.problem_index = 0;

    data.problem_last_click_time = now;

    city_message_sort_and_compact();
    data.problem_count = 0;
    for (int i = 0; i < 999; i++) {
        city_message* msg = &data.messages[i];
        if (msg->MM_text_id && msg->year >= game.simtime.year - 1) {
            const lang_message& lang_msg = lang_get_message(city_message_get_text_id(msg->MM_text_id));
            int lang_msg_type = lang_msg.message_type;
            if (has_problem_area(msg, lang_msg_type))
                data.problem_count++;
        }
    }
    if (data.problem_count <= 0) {
        data.problem_index = 0;
        return 0;
    }
    if (data.problem_index >= data.problem_count)
        data.problem_index = 0;

    int index = 0;
    int current_year = game.simtime.year;
    for (int i = 0; i < 999; i++) {
        city_message* msg = &data.messages[i];
        if (msg->MM_text_id && msg->year >= current_year - 1) {
            int text_id = city_message_get_text_id(msg->MM_text_id);
            int lang_msg_type = lang_get_message(text_id).message_type;
            if (has_problem_area(msg, lang_msg_type)) {
                index++;
                if (data.problem_index < index) {
                    data.problem_index++;
                    int grid_offset = msg->param2;
                    if (lang_msg_type == MESSAGE_TYPE_INVASION) {
                        int formation_grid_offset = formation_grid_offset_for_invasion(msg->param1);
                        if (formation_grid_offset)
                            grid_offset = formation_grid_offset;
                    }
                    return grid_offset;
                }
            }
        }
    }
    return 0;
}

void city_message_clear_scroll(void) {
    auto& data = g_message_manager;
    data.scroll_position = 0;
}
int city_message_scroll_position(void) {
    auto& data = g_message_manager;
    return data.scroll_position;
}
void city_message_set_scroll_position(int scroll_position) {
    auto& data = g_message_manager;
    data.scroll_position = scroll_position;
}

io_buffer* iob_messages = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_message_manager;
    for (int i = 0; i < MAX_MESSAGES; i++) {
        city_message& msg = data.messages[i];
       
        iob->bind(BIND_SIGNATURE_INT32, &msg.param1);
        iob->bind(BIND_SIGNATURE_INT32, &msg.param2);
        iob->bind(BIND_SIGNATURE_INT16, &msg.year);
        
        iob->bind_u16(msg.MM_text_id);
        iob->bind(BIND_SIGNATURE_INT16, &msg.sequence);
        iob->bind(BIND_SIGNATURE_UINT8, &msg.is_read);
        iob->bind(BIND_SIGNATURE_UINT8, &msg.month);

        iob->bind_i16(msg.eventmsg_body_id);  // FF FF
        iob->bind_i16(msg.eventmsg_title_id); // FF FF
        iob->bind_i16(msg.sender_faction);            // FF FF

        iob->bind(BIND_SIGNATURE_INT16, &msg.req_city);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_amount);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_resource);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_months_left);
        iob->bind(BIND_SIGNATURE_INT16, &msg.unk_07);

        iob->bind(BIND_SIGNATURE_INT16, &msg.eventmsg_phrase_id);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_city_past); // enum?
        iob->bind(BIND_SIGNATURE_INT16, &msg.unk_09);        // 00 00
        iob->bind(BIND_SIGNATURE_UINT8, &msg.unk_10);        // 00 00
        iob->bind(BIND_SIGNATURE_UINT8, &msg.hide_img);        // 00 00

        iob->bind(BIND_SIGNATURE_INT16, &msg.req_amount_past);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_resource_past);
        iob->bind(BIND_SIGNATURE_INT8 , &msg.unk_11a_i8); // FF
        iob->bind(BIND_SIGNATURE_UINT8, &msg.god); // FF
        iob->bind(BIND_SIGNATURE_UINT16,&msg.background_img);    // 00 00
    }
});

io_buffer* iob_message_extra = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_message_manager;
    iob->bind(BIND_SIGNATURE_INT32, &data.next_message_sequence);
    iob->bind(BIND_SIGNATURE_UINT16, &data.total_messages);
    iob->bind(BIND_SIGNATURE_UINT16, &data.reserved_1);
    iob->bind(BIND_SIGNATURE_UINT16, &data.current_message_id);
    iob->bind(BIND_SIGNATURE_UINT16, &data.reserved_2);

    // population
    iob->bind(BIND_SIGNATURE_UINT8, &data.reserved_7);
    iob->bind(BIND_SIGNATURE_UINT16, &data.population_shown.popmiles);
    iob->bind(BIND_SIGNATURE_UINT16, &data.reserved_3);
    iob->bind(BIND_SIGNATURE_UINT16, &data.reserved_4);
    iob->bind(BIND_SIGNATURE_UINT16, &data.reserved_5);
    iob->bind(BIND_SIGNATURE_UINT8, &data.reserved_6);

    for (int i = 0; i < MESSAGE_CAT_SIZE; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.message_count[i]);
    }

    for (int i = 0; i < MESSAGE_CAT_SIZE; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.message_delay[i]);
    }
});