#include "city_message.h"

#include "io/io_buffer.h"
#include "scenario/scenario_event_manager.h"
#include "content/vfs.h"
#include "core/encoding.h"
#include "core/string.h"
#include "city/city_religion.h"
#include "figure/formation.h"
#include "graphics/window.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "sound/sound.h"
#include "window/message_dialog.h"
#include "game/game_events.h"
#include "game/game.h"

message_manager_t g_message_manager;
auto& g_message_data = g_message_manager;

static bool should_play_sound = true;

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

    next_message_sequence = 0;
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

    events::subscribe([this] (event_message ev) {
        post_common(ev.use_popup, ev.message_id, ev.param1, ev.param2, GOD_UNKNOWN, 0);
    });

    events::subscribe([this] (event_message_god ev) {
        post_common(true, ev.message_id, 0, 0, ev.god, 0);
    });

    events::subscribe([this] (event_message_population ev) {
        post_common(ev.use_popup, ev.message_id, 0, 0, GOD_UNKNOWN, -1);
    });
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

static bool has_video(const lang_message& template_id) {
    if (template_id.video.text.empty()) {
        return false;
    }

    return vfs::file_exists(template_id.video.text.c_str());
}

static void enqueue_message(int sequence) {
    auto& data = g_message_data;
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
    auto& data = g_message_data;
    city_message& msg = data.messages[index];
    data.consecutive_message_delay = 5;
    msg.is_read = true;
    const auto& message_template = lang_get_message(msg.MM_text_id);
    if (!has_video(message_template)) {
        play_sound(message_template);
    }

    int advisor = city_message_get_advisor(msg.MM_text_id);
    xstring message_uid = lang_get_message_id(msg.MM_text_id);
    window_message_dialog_show_city_message(message_uid, index, msg.year, msg.month, msg.param1, msg.param2, advisor, true);
}

void city_message_disable_sound_for_next_message(void) {
    should_play_sound = false;
}

void city_message_apply_sound_interval(int category) {
    auto& data = g_message_data;
    time_millis now = time_get_millis();
    if (now - data.last_sound_time[category] <= 15000) {
        city_message_disable_sound_for_next_message();
    } else {
        data.last_sound_time[category] = now;
    }
}

void city_message_post_full(bool use_popup, xstring template_id, const event_ph_t *event, int parent_event_id, int title_id, int body_id, int phrase_id, int param1, int param2) {
    auto& data = g_message_data;
    int id = data.new_message_id();

    if (id < 0)
        return;

    data.total_messages++;
    data.current_message_id = id;

    city_message* msg = &data.messages[id];
    msg->MM_text_id = lang_get_message_uid(template_id);
    msg->eventmsg_title_id = title_id;
    msg->eventmsg_body_id = body_id;
    msg->eventmsg_phrase_id = phrase_id;
    msg->is_read = 0;
    msg->god = GOD_UNKNOWN;
    msg->year = game.simtime.year;
    msg->month = game.simtime.month;
    msg->param1 = param1;
    msg->param2 = param2;
    msg->sequence = data.next_message_sequence++;
    msg->sender_faction = event->sender_faction;

    msg->req_resource = event->item.value;
    msg->req_amount = event->amount.value; 
    if (msg->req_amount < 100) {
        msg->req_amount *= 100;
    }
    msg->req_city = event->location_fields[0] - 1;

    if (event->is_active) {
        msg->req_months_left = event->quest_months_left;
    } else {
        //        msg->req_resource = event->item_1; // TODO
        //        msg->req_amount = event->amount_FIXED; // TODO
        msg->req_months_left = event->months_initial;
    }

    if (parent_event_id >= 0) {
        const event_ph_t *parent_event = g_scenario.events.at(parent_event_id);
        msg->req_resource_past = parent_event->item.value;
        msg->req_amount_past = parent_event->amount.value;
        msg->req_city_past = parent_event->location_fields[0] - 1;
    } else {
        msg->req_resource_past = -1;
        msg->req_amount_past = -1;
        msg->req_city_past = -1;
    }

    // default for sound info / template

    if (use_popup && window_is(WINDOW_CITY))
        show_message_popup(id);
    else if (use_popup) {
        // add to queue to be processed when player returns to city
        enqueue_message(msg->sequence);
    } else if (should_play_sound) {
        const lang_message &mm_template = lang_get_message(template_id);
        play_sound(mm_template);
    }

    should_play_sound = true;
}

city_message &message_manager_t::post_common(bool use_popup, xstring mm_text, int param1, int param2, int god, int bg_img) {
    int id = new_message_id();
    if (id < 0) {
        static city_message dummy;
        return dummy;
    }

    total_messages++;
    current_message_id = id;

    city_message &msg = messages[id];

    // TODO: remove this hack += 99
    //message_id += 99;

    msg.MM_text_id = lang_get_message_uid(mm_text);
    msg.is_read = 0;
    msg.year = game.simtime.year;
    msg.month = game.simtime.month;
    msg.param1 = param1;
    msg.param2 = param2;
    msg.sequence = next_message_sequence++;
    msg.god = god;
    msg.hide_img = false;
    msg.background_img = bg_img;

    const lang_message &mm_template = lang_get_message(mm_text);
    int lang_msg_type = mm_template.message_type;
    if (lang_msg_type == MESSAGE_TYPE_DISASTER || lang_msg_type == MESSAGE_TYPE_INVASION) {
        problem_count = 1;
    }

    if (use_popup && window_is(WINDOW_CITY)) {
        show_message_popup(id);
    } else if (use_popup) { 
        // add to queue to be processed when player returns to city
        enqueue_message(msg.sequence);
    } else if (should_play_sound) {
        play_sound(mm_template);
    }

    should_play_sound = true;

    return msg;
}

city_message &city_message_post_with_popup_delay(e_mesage_category category, bool force_popup, xstring text, int param1, short param2) {
    auto& data = g_message_data;
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
    auto& data = g_message_data;
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

void city_message_process_queue(void) {
    auto& data = g_message_data;
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
    auto& data = g_message_data;
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
int city_message_get_advisor(int message_type) {
    message_type -= 99;
    switch (message_type) {
    //case MESSAGE_LOCAL_UPRISING:
    //case MESSAGE_BARBARIAN_ATTACK:
    //case MESSAGE_KINGDOME_ARMY_ATTACK:
    //case MESSAGE_DISTANT_BATTLE:
    //case MESSAGE_ENEMIES_CLOSING:
    //case MESSAGE_ENEMIES_AT_THE_DOOR:
        return MESSAGE_ADVISOR_MILITARY;

    //case MESSAGE_KINGDOME_REQUESTS_GOODS:
    //case MESSAGE_KINGDOME_REQUESTS_MONEY:
    //case MESSAGE_KINGDOME_REQUESTS_ARMY:
    //case MESSAGE_REQUEST_REMINDER:
    //case MESSAGE_REQUEST_RECEIVED:
   // case MESSAGE_REQUEST_REFUSED:
    //case MESSAGE_REQUEST_REFUSED_OVERDUE:
    //case MESSAGE_REQUEST_RECEIVED_LATE:
    //case MESSAGE_REQUEST_CAN_COMPLY:
        return MESSAGE_ADVISOR_IMPERIAL;

    //case MESSAGE_UNEMPLOYMENT:
    //case MESSAGE_WORKERS_NEEDED:
    //case MESSAGE_KINGDOME_LOWERS_WAGES:
    //case MESSAGE_KINGDOME_RAISES_WAGES:
        return MESSAGE_ADVISOR_LABOR;

    //case MESSAGE_NOT_ENOUGH_FOOD:
    //case MESSAGE_FOOD_NOT_DELIVERED:
        return MESSAGE_ADVISOR_POPULATION;

    //case MESSAGE_HEALTH_MALARIA_PROBLEM:
    //case MESSAGE_HEALTH_DISEASE:
    //case MESSAGE_HEALTH_PLAGUE:
    //    return MESSAGE_ADVISOR_HEALTH;

    default:
        return MESSAGE_ADVISOR_NONE;
    }
}

void city_message_reset_category_count(e_mesage_category category) {
    auto& data = g_message_data;
    data.message_count[category] = 0;
}
void city_message_increase_category_count(e_mesage_category category) {
    auto& data = g_message_data;
    data.message_count[category]++;
}
int city_message_get_category_count(e_mesage_category category) {
    auto& data = g_message_data;
    return data.message_count[category];
}

void city_message_decrease_delays(void) {
    auto& data = g_message_data;
    for (int i = 0; i < MESSAGE_CAT_SIZE; i++) {
        if (data.message_delay[i] > 0)
            data.message_delay[i]--;
    }
}

bool city_message_mark_population_shown(int population) {
    auto& data = g_message_data;
    bool lastv = false;
    switch (population) {
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
    const auto& data = g_message_data;
    return data.messages[message_id];
}

int city_message_set_current(int message_id) {
    auto& data = g_message_data;
    return data.current_message_id = message_id;
}

void city_message_mark_read(int message_id) {
    auto& data = g_message_data;
    data.messages[message_id].is_read = 1;
}

void city_message_delete(int message_id) {
    auto& data = g_message_data;
    data.messages[message_id].MM_text_id = 0;
    city_message_sort_and_compact();
}

int city_message_count() {
    auto& data = g_message_data;
    return data.total_messages;
}

int city_message_problem_area_count() {
    auto& data = g_message_data;
    return data.problem_count;
}

static int has_problem_area(const city_message* msg, int lang_msg_type) {
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
    auto& data = g_message_data;
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
    auto& data = g_message_data;
    data.scroll_position = 0;
}
int city_message_scroll_position(void) {
    auto& data = g_message_data;
    return data.scroll_position;
}
void city_message_set_scroll_position(int scroll_position) {
    auto& data = g_message_data;
    data.scroll_position = scroll_position;
}

io_buffer* iob_messages = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_message_data;
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
    auto& data = g_message_data;
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