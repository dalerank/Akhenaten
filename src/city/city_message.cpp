#include "city_message.h"
#include "game/sim_schedule.h"
#include "city/city.h"
#include "core/system_time.h"

#include "io/io_buffer.h"
#include "scenario/scenario_event_manager.h"
#include "content/vfs.h"
#include "core/encoding.h"
#include "core/log.h"
#include "core/string.h"
#include "city/city_message_chunks.h"
#include "city/city_religion.h"
#include "core/app_module.h"
#include "core/archive.h"
#include "core/svector.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"
#include "city/city_warnings.h"
#include "figure/formation.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_events.h"
#include "game/sound_effect.h"
#include "game/simulation.h"
#include "game/game_config.h"
#include "scenario/scenario.h"

message_manager_t& message_manager() {
    return xvalue<message_manager_t>::ref();
}

struct popup_message_category_t {
    e_popup_message_category category;
    xstring hint;
    svector<xstring, 16> messages;
};
ANK_CONFIG_STRUCT(popup_message_category_t, category, hint, messages)
svector<popup_message_category_t, POPUP_MSG_MAX> ANK_VARIABLE(popup_message_categories);

e_popup_message_category popup_message_category_for_key(xstring message_key) {
    if (message_key.empty()) {
        return POPUP_MSG_NONE;
    }
    for (const auto& category : popup_message_categories) {
        for (const xstring& key : category.messages) {
            if (message_key == key) {
                return category.category;
            }
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
}

void message_manager_t::subscribe_events() {
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

static void message_manager_subscribe_events() {
    message_manager().subscribe_events();
}
static events::session_subscriber g_message_manager_session(&message_manager_subscribe_events);

class messages_system : public sim_system {
public:
    const char* name() const override { return "messages"; }
    void register_steps() override {
        sim_schedule_add(
          {SIM_PHASE_MONTH, -1, 100, "messages", SIM_AREA_MESSAGES, [] { message_manager().decrease_delays(); }});
    }

    void push_save_sections(int file_version) override {
        g_chunk_io.push_chunk<messages_chunk>(48000, false);
        g_chunk_io.push_chunk<message_extra_chunk>(182, false);
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_messages_system) {
    static messages_system system;
    g_simulation.register_system(&system);
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
    msg = city_message{};
    // Non-event list UI treats unset eventmsg ids as "no eventmsg".
    msg.eventmsg_body_id = -1;
    msg.eventmsg_title_id = -1;
    msg.eventmsg_phrase_id = -1;

    msg.MM_text_id = lang_get_message_uid(template_id);
    msg.is_read = 0;
    msg.year = g_simulation.simtime.year;
    msg.month = g_simulation.simtime.month;
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

    const event_ph_t* parent_event = parent_event_id >= 0 ? g_scenario.events.at(parent_event_id) : nullptr;
    if (parent_event) {
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

static void play_sound(const lang_message &template_id) {
    if (template_id.urgent) {
        events::emit(event_sound_effect{SOUND_EFFECT_FANFARE_URGENT});
    } else {
        events::emit(event_sound_effect{SOUND_EFFECT_FANFARE});
    }
}

void message_manager_t::mark_shown(int index) {
    consecutive_message_delay = 5;
    messages[index].is_read = true;
}

void message_manager_t::enqueue(int sequence) {
    for (int i = 0; i < MAX_MESSAGES_QUEUE; i++) {
        if (!queue[i]) {
            queue[i] = sequence;
            break;
        }
    }
}

int message_manager_t::find_index_by_sequence(int sequence) {
    if (sequence < 0) {
        return -1;
    }
    for (int i = 0; i < MAX_MESSAGES; i++) {
        if (messages[i].MM_text_id && messages[i].sequence == sequence) {
            return i;
        }
    }
    return -1;
}

void message_manager_t::show_message_banner_for_index(int index) {
    city_message& msg = messages[index];
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
    events::emit(event_city_message_banner{title.c_str(), msg.sequence});
}

void message_manager_t::apply_popup_delivery(bool use_popup, e_popup_message_category popup_cat, int message_index,
  xstring sound_template_key) {
    if (use_popup && popup_messages_want_banner(popup_cat)) {
        show_message_banner_for_index(message_index);
        // I3: quiet UI chime instead of fanfare on banner path.
        events::emit(event_sound_effect{SOUND_EFFECT_ICON});
        should_play_sound = true;
        return;
    }
    if (use_popup) {
        events::emit(event_city_message_popup{message_index});
    } else if (should_play_sound) {
        const lang_message &mm_template = lang_get_message(sound_template_key);
        play_sound(mm_template);
    }
    should_play_sound = true;
}

void message_manager_t::disable_sound_for_next_message() {
    should_play_sound = false;
}

void message_manager_t::apply_sound_interval(int category) {
    time_millis now = time_get_millis();
    if (now - last_sound_time[category] <= 15000) {
        disable_sound_for_next_message();
    } else {
        last_sound_time[category] = now;
    }
}

void message_manager_t::post_full(bool use_popup, xstring template_id, const event_ph_t* event, int parent_event_id,
  int title_id, int body_id, int phrase_id, int param1, int param2, e_popup_message_category popup_cat,
  city_message_gift gift) {
    int id = alloc_message(template_id);
    if (id < 0) {
        return;
    }

    city_message& msg = messages[id];
    msg.eventmsg_title_id = title_id;
    msg.eventmsg_body_id = body_id;
    msg.eventmsg_phrase_id = phrase_id;
    msg.param1 = param1;
    msg.param2 = param2;
    msg.god = GOD_UNKNOWN;
    fill_from_event(msg, event, parent_event_id);
    msg.delivered_amount = gift.delivered_amount;
    msg.gift_buttons = gift.buttons;

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

city_message& message_manager_t::post_with_popup_delay(e_mesage_category category, bool force_popup, xstring text,
  int param1, short param2) {
    bool use_popup = false;

    if (message_delay[category] <= 0) {
        use_popup = true;
        message_delay[category] = 12;
    }
    use_popup |= force_popup;

    city_message& message = post_common(use_popup, text, param1, param2, GOD_UNKNOWN, 0);
    message_count[category]++;

    return message;
}

void message_manager_t::post_with_message_delay(e_mesage_category category, int use_popup, xstring message_type,
  int delay) {
    if (category == MESSAGE_CAT_FISHING_BLOCKED || category == MESSAGE_CAT_NO_WORKING_DOCK) {
        // bug in the original game: delays for 'fishing blocked' and 'no working dock'
        // are stored in message_count with manual countdown
        if (message_count[category] > 0) {
            message_count[category]--;
        } else {
            message_count[category] = delay;
            post_common(use_popup, message_type, 0, 0, GOD_UNKNOWN, 0);
        }
    } else {
        if (message_delay[category] <= 0) {
            message_delay[category] = delay;
            post_common(use_popup, message_type, 0, 0, GOD_UNKNOWN, 0);
        }
    }
}

int message_manager_t::take_queued() {
    if (consecutive_message_delay > 0) {
        consecutive_message_delay--;
        return -1;
    }
    int sequence = 0;
    for (int i = 0; i < MAX_MESSAGES_QUEUE; i++) {
        if (queue[i]) {
            sequence = queue[i];
            queue[i] = 0;
            break;
        }
    }
    if (sequence == 0)
        return -1;
    int message_id = -1;
    for (int i = 0; i < 999; i++) {
        if (!messages[i].MM_text_id)
            return -1;
        if (messages[i].sequence == sequence) {
            message_id = i;
            break;
        }
    }
    if (message_id >= 0) {
        mark_shown(message_id);
    }
    return message_id;
}

void message_manager_t::sort_and_compact() {
    for (int i = 0; i < MAX_MESSAGES; i++) {
        for (int a = 0; a < MAX_MESSAGES - 1; a++) {
            int swap = 0;
            if (messages[a].MM_text_id) {
                if (messages[a].sequence < messages[a + 1].sequence) {
                    if (messages[a + 1].MM_text_id)
                        swap = 1;
                }
            } else if (messages[a + 1].MM_text_id)
                swap = 1;

            if (swap) {
                city_message tmp_message = messages[a];
                messages[a] = messages[a + 1];
                messages[a + 1] = tmp_message;
            }
        }
    }
    total_messages = 0;
    for (int i = 0; i < MAX_MESSAGES; i++) {
        if (messages[i].MM_text_id)
            total_messages++;
    }
}

int message_manager_t::get_text_id(int message_id) {
    return message_id;
}

void message_manager_t::reset_category_count(e_mesage_category category) {
    message_count[category] = 0;
}
void message_manager_t::increase_category_count(e_mesage_category category) {
    message_count[category]++;
}
int message_manager_t::get_category_count(e_mesage_category category) {
    return message_count[category];
}

void message_manager_t::decrease_delays() {
    for (int i = 0; i < MESSAGE_CAT_SIZE; i++) {
        if (message_delay[i] > 0)
            message_delay[i]--;
    }
}

bool message_manager_t::mark_population_shown(int population) {
    bool lastv = false;
    switch (population) {
    case 100:
        lastv = population_shown.pop500;
        population_shown.pop100 = true;
        return lastv;
    case 500:
        lastv = population_shown.pop500;
        population_shown.pop500 = true;
        return lastv;
    case 1000:
        lastv = population_shown.pop1000;
        population_shown.pop1000 = true;
        return lastv;
    case 2000:
        lastv = population_shown.pop2000;
        population_shown.pop2000 = true;
        return lastv;
    case 3000:
        lastv = population_shown.pop3000;
        population_shown.pop3000 = true;
        return lastv;
    case 5000:
        lastv = population_shown.pop5000;
        population_shown.pop5000 = true;
        return lastv;
    case 10000:
        lastv = population_shown.pop10000;
        population_shown.pop10000 = true;
        return lastv;
    case 15000:
        lastv = population_shown.pop15000;
        population_shown.pop15000 = true;
        return lastv;
    case 20000:
        lastv = population_shown.pop20000;
        population_shown.pop20000 = true;
        return lastv;
    case 25000:
        lastv = population_shown.pop25000;
        population_shown.pop25000 = true;
        return lastv;
    default:
        return false;
    }
}

const city_message& message_manager_t::get(int message_id) const {
    return messages[message_id];
}

void message_manager_t::mark_read(int message_id) {
    messages[message_id].is_read = 1;
}

void message_manager_t::remove(int message_id) {
    messages[message_id].MM_text_id = 0;
    sort_and_compact();
}

int message_manager_t::count() {
    return total_messages;
}

int message_manager_t::problem_area_count() {
    return problem_count;
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
        return (msg->month + 1) % simulation_time_t::months_in_year == g_simulation.simtime.month
               && msg->year + (msg->month + 1) / simulation_time_t::months_in_year == g_simulation.simtime.year;
    }
    return 0;
}

int message_manager_t::next_problem_area_grid_offset() {
    time_millis now = time_get_millis();
    if (now - problem_last_click_time > 3000)
        problem_index = 0;

    problem_last_click_time = now;

    sort_and_compact();
    problem_count = 0;
    for (int i = 0; i < 999; i++) {
        city_message* msg = &messages[i];
        if (msg->MM_text_id && msg->year >= g_simulation.simtime.year - 1) {
            const lang_message& lang_msg = lang_get_message(get_text_id(msg->MM_text_id));
            int lang_msg_type = lang_msg.message_type;
            if (has_problem_area(msg, lang_msg_type))
                problem_count++;
        }
    }
    if (problem_count <= 0) {
        problem_index = 0;
        return 0;
    }
    if (problem_index >= problem_count)
        problem_index = 0;

    int index = 0;
    int current_year = g_simulation.simtime.year;
    for (int i = 0; i < 999; i++) {
        city_message* msg = &messages[i];
        if (msg->MM_text_id && msg->year >= current_year - 1) {
            int text_id = get_text_id(msg->MM_text_id);
            int lang_msg_type = lang_get_message(text_id).message_type;
            if (has_problem_area(msg, lang_msg_type)) {
                index++;
                if (problem_index < index) {
                    problem_index++;
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

void message_manager_t::clear_scroll() {
    scroll_position = 0;
}
int message_manager_t::get_scroll_position() {
    return scroll_position;
}
void message_manager_t::set_scroll_position(int scroll_position) {
    scroll_position = scroll_position;
}
