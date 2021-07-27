#include <core/lang.h>
#include "events.h"
#include "event_phrases.h"
#include "city/message.h"
#include "core/io.h"
#include "core/log.h"
#include "core/string.h"

#define MAX_EVENTS 150
#define NUM_AUTO_PHRASE_VARIANTS 54
#define NUM_PHRASES 601
#define MAX_EVENTMSG_TEXT_DATA NUM_PHRASES * 200

// City under attack,
// Distant Battle,
// General Request,
// Great Festival,
// Construction Project,
// Famine Relief,
// Threat,
// Eg. City falls,
// Foreign city conquered,
// Trade available,
// Trade shuts down,
// Trade city under siege,
// Eg. City saved,
// Distant Battle won,
// Distant battle lost,
// Acknowledgement,
// Pharaoh Attacks,
// Eg. Army attacks,
// Foreign army attacks,
// Kingdom increase,
// Kingdom decrease,
// Demand increase,
// Demand decrease,
// Price increase,
// Price decrease,
// Wage increase,
// Wage decrease,
// Earthquake,
// (revolt),
// stormy seas,
// sandstorm,
// cont. water,
// gold mine collapse,
// Gift,,,,,,,,,
struct {
    event_ph_t events[MAX_EVENTS];
    int *num_of_events = nullptr;
    int auto_phrases[NUM_AUTO_PHRASE_VARIANTS][36];

    uint8_t eventmsg_phrases_data[MAX_EVENTMSG_TEXT_DATA];
    int eventmsg_line_offsets[NUM_PHRASES];
    int eventmsg_group_offsets[NUM_PHRASES];
} data;

const event_ph_t *get_scenario_event(int id) {
    return &data.events[id];
}
static bool is_valid_event_index(int id) {
    if (id >= MAX_EVENTS || id >= *data.num_of_events)
        return false;
    return true;
}


static int get_auto_reason_phrase_id(int param_1, int param_2) {
    return data.auto_phrases[param_1][param_2];
}
uint8_t *get_eventmsg_text(int group_id, int index) {
    int eventmsg_id = data.eventmsg_group_offsets[group_id] + index;
    return &data.eventmsg_phrases_data[data.eventmsg_line_offsets[eventmsg_id]];
}

static void post_event_message(int event_id, int caller_event_id) {

    auto event = get_scenario_event(event_id);

//    auto s = lang_get_string(9, 2);
    auto s = get_eventmsg_text(0, 0);
    auto l = string_length(s);

    int p;
    p = PHRASE_egyptian_city_attacked_title_P; // 0
    p = PHRASE_acknowledgement_reason_C; // 160
    p = PHRASE_acknowledgement_no_reason_A; // 161
    p = PHRASE_acknowledgement_no_reason_B; // 162

    // temp for debugging
    city_message_post(true, MESSAGE_WORKERS_NEEDED, 0, 0);
}
static void event_fire(int id, bool via_event_trigger, int action_status, int caller_event_id = -1) {
    if (!is_valid_event_index(id))
        return;

    event_ph_t *event = &data.events[id];

    // can not invoke event from an event if trigger is set to global update
    // also, can not invoke from global update if trigger is set to event only
    if (event->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT && !via_event_trigger)
        return;
    if (event->event_trigger_type != EVENT_TRIGGER_ONLY_VIA_EVENT && via_event_trigger)
        return;

    // Pharaoh duplicates the fired events and sets trigger to "12" for some reason. I have no idea why.
    if (!via_event_trigger) {
        // TODO: create copy of events?...
    }

    // main event handler!!!
    switch (event->type) {
        case EVENT_TYPE_REQUEST: {

            // advance trigger state...
            switch (event->timer_trigger_state) {
                case EVENT_TIMER_STATE_INITIAL:
                    if (!event->in_progress) {
                        event->in_progress = true;
                        event->months_left = event->months_initial;
                        // TODO: send message, enable request
                    } else {
                        event->timer_trigger_state = EVENT_TIMER_STATE_MISSED_ONCE;
                        event->months_left = 24; // hardcoded
                        // TODO: send reprimand
                    }
                    break;
                case EVENT_TIMER_STATE_MISSED_ONCE:
                    event->in_progress = false;
                    event->timer_trigger_state = EVENT_TIMER_STATE_MISSED_COMPLETELY;
                    action_status = EVENT_ACTION_REFUSED;
                    break;
            }
            break;
        }
        case EVENT_TYPE_INVASION:
            // TODO
            break;
        case EVENT_TYPE_SEA_TRADE_PROBLEM:
        case EVENT_TYPE_LAND_TRADE_PROBLEM:
        case EVENT_TYPE_WAGE_INCREASE:
        case EVENT_TYPE_WAGE_DECREASE:
        case EVENT_TYPE_CONTAMINATED_WATER:
        case EVENT_TYPE_GOLD_MINE_COLLAPSE:
        case EVENT_TYPE_CLAY_PIT_FLOOD:
        case EVENT_TYPE_DEMAND_INCREASE:
        case EVENT_TYPE_DEMAND_DECREASE:
        case EVENT_TYPE_PRICE_INCREASE:
        case EVENT_TYPE_PRICE_DECREASE:
        case EVENT_TYPE_REPUTATION_INCREASE:
        case EVENT_TYPE_REPUTATION_DECREASE:
        case EVENT_TYPE_CITY_STATUS_CHANGE:
        case EVENT_TYPE_MESSAGE:
        case EVENT_TYPE_FAILED_FLOOD:
        case EVENT_TYPE_PERFECT_FLOOD:
        case EVENT_TYPE_GIFT:
        case EVENT_TYPE_LOCUSTS:
        case EVENT_TYPE_FROGS:
        case EVENT_TYPE_HAILSTORM:
        case EVENT_TYPE_BLOOD_RIVER:
        case EVENT_TYPE_CRIME_WAVE:
            action_status = EVENT_ACTION_COMPLETED;
            break;
    }

    // post event message, if it has one (it always does?)
    post_event_message(id, caller_event_id);

    // propagate trigger events
    switch (action_status) {
        case EVENT_ACTION_COMPLETED:
            event_fire(event->on_completed_action, true, action_status, id);
            break;
        case EVENT_ACTION_REFUSED:
            event_fire(event->on_refusal_action, true, action_status, id);
            break;
        case EVENT_ACTION_TOOLATE:
            event_fire(event->on_tooLate_action, true, action_status, id);
            break;
        case EVENT_ACTION_DEFEAT:
            event_fire(event->on_defeat_action, true, action_status, id);
            break;
    }

    // disable if already done
    if (event->event_trigger_type == EVENT_TRIGGER_ONCE)
        event->timer_trigger_state = EVENT_TRIGGER_ALREADY_FIRED;
}
void scenario_event_process() {
    for (int i = 0; i < *data.num_of_events; i++) {
        event_ph_t *event = &data.events[i];
        if (event->type == EVENT_TYPE_NONE)
            continue;
        switch (event->event_trigger_type) {
            case EVENT_TRIGGER_ONCE:
            case EVENT_TRIGGER_RECURRING:
                if (event->months_left >= 0)
                    event->months_left--;
                if (event->months_left <= 0)
                    event_fire(i, false, -1);
                break;
            case EVENT_TRIGGER_BY_RATING:
                // TODO
                break;
        }
    }
}

void scenario_events_save_state(buffer *buf) {

}
void scenario_events_load_state(buffer *buf) {

    // the first event's header always contains the total number of events
    data.num_of_events = &(data.events[0].num_total_header);

    for (int i = 0; i < MAX_EVENTS; i++) {
        event_ph_t *event = &data.events[i];
        event->num_total_header = buf->read_i16();
        if (!is_valid_event_index(i))
            return;
            event->__unk01 = buf->read_i16();
        event->event_id = buf->read_i16();
        event->type = buf->read_i8();
        event->month = buf->read_i8();
            event->__unk03 = buf->read_i16();
        event->item_1 = buf->read_i16();
        event->item_2 = buf->read_i16();
        event->item_3 = buf->read_i16();
            event->__unk04 = buf->read_i16(); // 07 --> 08
        event->amount_FIXED = buf->read_i16();
        event->amount_MIN = buf->read_i16();
        event->amount_MAX = buf->read_i16();
            event->__unk05 = buf->read_i16();
        event->year_or_month_FIXED = buf->read_i16();
        event->year_or_month_MIN = buf->read_i16();
        event->year_or_month_MAX = buf->read_i16();
            event->__unk06 = buf->read_i16(); // 03 --> 07
        event->city_or_marker_FIXED = buf->read_i16();
        event->city_or_marker_MIN = buf->read_i16();
        event->city_or_marker_MAX = buf->read_i16();
        event->on_completed_action = buf->read_i16();
        event->on_refusal_action = buf->read_i16();
        event->event_trigger_type = buf->read_i16();
            event->__unk07 = buf->read_i16();
        event->months_initial = buf->read_i16();
        event->months_left = buf->read_i16(); // 0B 00 ......   XX 00 --> 0C 00
        event->timer_trigger_state = buf->read_i16();
        event->in_progress = buf->read_i16();
            event->__unk11 = buf->read_i16();
        event->festival_deity = buf->read_i8();
            event->__unk12_i8 = buf->read_i8();
        event->invasion_attack_target = buf->read_i8();
            // ...
            // ...
            // ...
            buf->skip(25);
        event->on_tooLate_action = buf->read_i16();
        event->on_defeat_action = buf->read_i16();
        event->event_source_faction = buf->read_i8();
            event->__unk13_i8 = buf->read_i8();
            event->__unk14 = buf->read_i16();
        event->route_FIXED = buf->read_i16();
        event->route_MIN = buf->read_i16();
        event->route_MAX = buf->read_i16();
        event->subtype = buf->read_i8();
            event->__unk15_i8 = buf->read_i8(); // 08 --> 05
            event->__unk16 = buf->read_i16();
            event->__unk17 = buf->read_i16();
            event->__unk18 = buf->read_i16();
            event->__unk19 = buf->read_i16();
        event->on_completed_msgAlt = buf->read_i8();
        event->on_refusal_msgAlt = buf->read_i8();
        event->on_tooLate_msgAlt = buf->read_i8();
        event->on_defeat_msgAlt = buf->read_i8();
            event->__unk20_FIXED = buf->read_i16();
            event->__unk20_MIN = buf->read_i16();
            event->__unk20_MAX = buf->read_i16();
            event->__unk21 = buf->read_i16();
            event->__unk22 = buf->read_i16();
    }
}

#define TMP_BUFFER_SIZE 100000
static const uint8_t PHRASE[] = {'P', 'H', 'R', 'A', 'S', 'E', '_', 0};

static int strings_equal(const uint8_t *a, const uint8_t *b, int len) {
    for (int i = 0; i < len; i++, a++, b++) {
        if (*a != *b)
            return 0;

    }
    return 1;
}
static int index_of_string(const uint8_t *haystack, const uint8_t *needle, int haystack_length) {
    int needle_length = string_length(needle);
    for (int i = 0; i < haystack_length; i++) {
        if (haystack[i] == needle[0] && strings_equal(&haystack[i], needle, needle_length))
            return i + 1;
    }
    return 0;
}
static int index_of(const uint8_t *haystack, uint8_t needle, int haystack_length) {
    for (int i = 0; i < haystack_length; i++) {
        if (haystack[i] == needle)
            return i + 1;
    }
    return 0;
}
static const uint8_t *skip_non_digits(const uint8_t *str) {
    int safeguard = 0;
    while (1) {
        if (++safeguard >= 1000)
            break;

        if ((*str >= '0' && *str <= '9') || *str == '-')
            break;

        str++;
    }
    return str;
}
static const uint8_t *get_value(const uint8_t *ptr, const uint8_t *end_ptr, int *value) {
    ptr = skip_non_digits(ptr);
    *value = string_to_int(ptr);
    ptr += index_of(ptr, ',', (int) (end_ptr - ptr));
    return ptr;
}

//uint8_t _P[] = "_P";
//uint8_t _P_A[] = "_P_A";
//uint8_t _P_B[] = "_P_B";
//uint8_t _P_C[] = "_P_C";
//uint8_t _C[] = "_C";
//uint8_t _C_A[] = "_C_A";
//uint8_t _C_B[] = "_C_B";
//uint8_t _C_C[] = "_C_C";

static int next_skipping_lines_counter = 0;
static bool is_line_standalone_group(const uint8_t *start_of_line, int size) {
    if (next_skipping_lines_counter > 0) {
        next_skipping_lines_counter--;
        return false;
    }
    if (index_of_string(start_of_line, (const uint8_t*)"_A", size)) {
        next_skipping_lines_counter = 2;
        return true;
    }
    return true;

//        int i_P = index_of_string(start_of_line, term_1, ptr - start_of_line);
//        int i_P_A = index_of_string(start_of_line, term_2, ptr - start_of_line);
//        int i_P_xx = index_of_string(start_of_line, term_3, ptr - start_of_line);

//    int i_P_B = index_of_string(start_of_line, _P_B, size);
//    int i_P_C = index_of_string(start_of_line, _P_C, size);
//    int i_C_B = index_of_string(start_of_line, _C_B, size);
//    int i_C_C = index_of_string(start_of_line, _C_C, size);
//
//    if (i_P_B > 0 || i_P_C > 0 || i_C_B > 0 || i_C_C > 0)
//        return false;
//
//    if (index_of_string(start_of_line, (const uint8_t*)"_A", size))
//        return true;
//
//    if (index_of_string(start_of_line, (const uint8_t*)"_P", size))
//        return true;
//
//    if (index_of_string(start_of_line, (const uint8_t*)"_C", size))
//        return true;
//
//    if (index_of_string(start_of_line, (const uint8_t*)"_B", size))
//        return false;
//    if (index_of_string(start_of_line, (const uint8_t*)"_C", size))
//        return false;
//
//    return true;
}
bool eventmsg_load(void) {
    buffer buf(TMP_BUFFER_SIZE);

    int filesize = io_read_file_into_buffer("eventmsg.txt", NOT_LOCALIZED, &buf, TMP_BUFFER_SIZE);
    if (filesize == 0) {
        log_error("Eventmsg.txt not found", 0, 0);
        return false;
    }

    // go through the file to assert number of lines
    int num_lines = 0;
    int guard = NUM_PHRASES;
    int line_start_index;
    const uint8_t *haystack = buf.get_data();
    const uint8_t *ptr = haystack;
    do {
        guard--;
        line_start_index = index_of_string(ptr, PHRASE, filesize);
        if (line_start_index) {
            ptr += line_start_index;
            num_lines++;
        }
    } while (line_start_index && guard > 0);
    if (num_lines != NUM_PHRASES) {
        log_error("Eventmsg.txt has incorrect no of lines ", 0, num_lines + 1);
        return false;
    }

    // parse phrase data
    buffer buf2(TMP_BUFFER_SIZE);
    int offset = 0;
    int group_offset = 0;
    int group_offset_extra = 0;
    ptr = haystack;
    const uint8_t *ptr2 = haystack;
    const uint8_t *end_ptr = &haystack[filesize];
    for (int i = 0; i < NUM_PHRASES; i++) {
        ptr += index_of_string(ptr, PHRASE, filesize);
        const uint8_t *start_of_line = ptr - 1;

        ptr += index_of(ptr, '"', filesize);
        ptr2 = ptr + index_of(ptr, '"', filesize);
        int size = ptr2 - ptr;

        buf2.write_raw(ptr, size - 1);
        buf2.write_u8(0);

        data.eventmsg_line_offsets[i] = offset;
        offset += size;
        if (offset >= MAX_EVENTMSG_TEXT_DATA - 300) {
            log_error("Eventmsg data size too big to fit container. ", 0, offset);
            return false;
        }

        // check if line is part of a new "group"
        if (is_line_standalone_group(start_of_line, ptr - start_of_line)){
            if (group_offset < 298)
                data.eventmsg_group_offsets[group_offset] = i;
            else // Pyramid & extra messages
                data.eventmsg_group_offsets[i] = i;
//                data.eventmsg_group_offsets[group_offset + 252] = i;
            group_offset++;
        } else {
            data.eventmsg_group_offsets[group_offset_extra + 298] = i;
            group_offset_extra++;
        }
    }
    buf2.reset_offset();
    buf2.read_raw(&data.eventmsg_phrases_data, offset);
//    data.eventmsg_phrases_data = buf2.read_raw();

    log_info("Event phrases loaded --", "Data size:", offset);
    return true;
}
bool eventmsg_auto_phrases_load(void) {
    buffer buf(TMP_BUFFER_SIZE);

    int filesize = io_read_file_into_buffer("auto reason phrases.txt", NOT_LOCALIZED, &buf, TMP_BUFFER_SIZE);
    if (filesize == 0) {
        log_error("Event auto phrases file not found", 0, 0);
        return false;
    }

    // go through the file to assert number of lines
    int num_lines = 0;
    int guard = NUM_AUTO_PHRASE_VARIANTS;
    int brace_index;
    const uint8_t *haystack = buf.get_data();
    const uint8_t *ptr = haystack;
    do {
        guard--;
        brace_index = index_of(ptr, '{', filesize);
        if (brace_index) {
            ptr += brace_index;
            num_lines++;
        }
    } while (brace_index && guard > 0);
    if (num_lines != NUM_AUTO_PHRASE_VARIANTS) {
        log_error("Event auto phrases file has incorrect no of lines ", 0, num_lines + 1);
        return false;
    }

    // parse phrase data
    ptr = haystack;
    const uint8_t *end_ptr = &haystack[filesize];
    for (int i = 0; i < NUM_AUTO_PHRASE_VARIANTS; i++) {
        ptr += index_of(ptr, '{', filesize);

        for (int a = 0; a < 36; a++)
            ptr = get_value(ptr, end_ptr, &data.auto_phrases[i][a]);
    }

    log_info("Event auto phrases loaded", 0, 0);
    return true;
}