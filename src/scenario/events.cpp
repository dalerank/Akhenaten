#include <core/lang.h>
#include <game/time.h>
#include <ios>
#include <core/random.h>
#include "data.h"
#include "event_phrases.h"
#include "city/message.h"
#include "core/io.h"
#include "core/log.h"
#include "core/string.h"

#define MAX_EVENTS 150
#define NUM_AUTO_PHRASE_VARIANTS 54
#define NUM_PHRASES 601
#define MAX_EVENTMSG_TEXT_DATA NUM_PHRASES * 200

struct {
    event_ph_t event_list[MAX_EVENTS];
    int16_t *num_of_events = nullptr;
    int auto_phrases[NUM_AUTO_PHRASE_VARIANTS][36];

    uint8_t eventmsg_phrases_data[MAX_EVENTMSG_TEXT_DATA];
    int eventmsg_line_offsets[NUM_PHRASES];
    int eventmsg_group_offsets[NUM_PHRASES];
} data;

const int get_scenario_events_num() {
    return *data.num_of_events;
}

static void update_randomized_values(event_ph_t *event) {
    int seed = 1; // not sure what this is used for...
    randomize_event_fields(event->item_fields, &seed);
    randomize_event_fields(event->amount_fields, &seed);
    randomize_event_fields(event->time_fields, &seed);
    randomize_event_fields(event->location_fields, &seed);
    randomize_event_fields(event->route_fields, &seed);

    // some other unknown stuff also happens here.........
    random_generate_next();
    random_generate_next();
}

event_ph_t *create_scenario_event(const event_ph_t *donor) {
    if (*data.num_of_events < MAX_EVENTS) {
        (*data.num_of_events)++;
        int event_id = *data.num_of_events - 1;
        event_ph_t *new_event = &data.event_list[event_id];

        // if parent event is supplied, clone it into the new event
        if (donor != nullptr)
            memcpy(new_event, donor, sizeof(event_ph_t));
        new_event->event_id = event_id;
        return new_event;
    }
    return nullptr;
}
static bool create_triggered_active_event(const event_ph_t *master, const event_ph_t *parent, int trigger_type) {
    event_ph_t *child = create_scenario_event(master);
    if (child) {

        child->event_state = EVENT_STATE_INITIAL;
        child->event_trigger_type = trigger_type;

        update_randomized_values(child);

        // calculate date of activation
        int month_abs_parent = parent->time_fields[0] * 12 + parent->month; // field is YEARS in parent
        int month_abs_child = month_abs_parent + child->time_fields[0]; // field is MONTHS in child
        child->time_fields[0] = month_abs_child / 12; // relinquish previous field (the child needs this for storing the YEAR)
        child->month = month_abs_child % 12; // update proper month value relative to the year
        child->quest_months_left = month_abs_child - month_abs_parent;

        return true;
    }
    return false;
}

const event_ph_t *get_scenario_event(int id) {
    return &data.event_list[id];
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

static void event_process(int id, bool via_event_trigger, int chain_action_parent, int caller_event_id = -1, int caller_event_var = EVENT_VAR_AUTO) {
    if (!is_valid_event_index(id))
        return;

    event_ph_t *event = &data.event_list[id];

    // must be a valid event type;
    // also, can not invoke event from an event if trigger is set to global update;
    // also, can not invoke from global update if trigger is set to event only;
    // also, events with 'EVENT_TRIGGER_ALREADY_FIRED' can not fire again.
    if (event->type == EVENT_TYPE_NONE)
        return;
    if (event->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT && !via_event_trigger)
        return;
    if (event->event_trigger_type != EVENT_TRIGGER_ONLY_VIA_EVENT && via_event_trigger)
        return;
    if (event->event_trigger_type == EVENT_TRIGGER_ALREADY_FIRED)
        return;

    // create follow-up "actual" active events when triggered
    // (very convoluted and annoying way in which Pharaoh events work...)
    if (event->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT) {
        if (!is_valid_event_index(caller_event_id))
            return;
        if (event->type == EVENT_TYPE_REQUEST)
            create_triggered_active_event(event, get_scenario_event(caller_event_id), EVENT_TRIGGER_ACTIVATED_8);
        else
            create_triggered_active_event(event, get_scenario_event(caller_event_id), EVENT_TRIGGER_ACTIVATED_12);
        return;
    }

    // check if the trigger time has come, if not return.
    // for ACTIVE EVENTS (requests?): ignore specific time of the year IF quest is active
    if (!event->is_active &&
        (event->time_fields[0] != game_time_year_since_start() || event->month != game_time_month()))
        return;

    // ------ MAIN EVENT HANDLER
    int chain_action_next = EVENT_ACTION_COMPLETED; // default action to fire next (determined by handler)
    switch (event->type) {
        case EVENT_TYPE_REQUEST: {
            // advance time
            if (event->quest_months_left > 0)
                event->quest_months_left--;

            // the event is coming, but hasn't fired yet. this is always a slave / proper event object.
            // the "facade" event is taken care of the VIA_EVENT check from above - it will never fire.
            if (!event->is_active) {
                event->quest_months_left = event->months_initial;
                event->is_active = 1;
            }
            // handle request event immediately after activation!
            if (event->is_active) {
                chain_action_next = EVENT_ACTION_NONE;
                int pharaoh_alt_shift = event->sender_faction == EVENT_FACTION_REQUEST_FROM_CITY ? 1 : 0;
                if (event->event_state == EVENT_STATE_INITIAL) {
                    if (event->quest_months_left == event->months_initial) {
                        // initial quest message
                        city_message_post_full(true, MESSAGE_TEMPLATE_REQUEST, id, caller_event_id,
                                               PHRASE_general_request_title_P + pharaoh_alt_shift,
                                               PHRASE_general_request_initial_announcement_P + pharaoh_alt_shift,
                                               PHRASE_general_request_no_reason_P_A + pharaoh_alt_shift * 3, id, 0);
                    } else if (event->quest_months_left == 6) {
                        // reminder of 6 months left
                        city_message_post_full(true, MESSAGE_TEMPLATE_REQUEST, id, caller_event_id,
                                               PHRASE_general_request_title_P + pharaoh_alt_shift,
                                               PHRASE_general_request_reminder_P + pharaoh_alt_shift,
                                               PHRASE_general_request_no_reason_P_A + pharaoh_alt_shift * 3, id, 0);
                    } else if (event->quest_months_left == 0) {
                        event->event_state = EVENT_STATE_OVERDUE;
                        event->quest_months_left = 24; // hardcoded
                        // reprimand message
                        city_message_post_full(true, MESSAGE_TEMPLATE_REQUEST, id, caller_event_id,
                                               PHRASE_general_request_title_P + pharaoh_alt_shift,
                                               PHRASE_general_request_overdue_P + pharaoh_alt_shift,
                                               PHRASE_general_request_no_reason_P_A + pharaoh_alt_shift * 3, id, 0);
                    }
                } else if (event->event_state == EVENT_STATE_OVERDUE) {
                    if (event->quest_months_left == 6) {
                        // angry reminder of 6 months left?
//                        city_message_post_full(true, MESSAGE_TEMPLATE_REQUEST, id, caller_event_id,
//                                               PHRASE_general_request_title_P + faction_mod,
//                                               PHRASE_general_request_warning_P + faction_mod,
//                                               PHRASE_general_request_no_reason_P_A + faction_mod * 3, id, 0);
                    } else if (event->quest_months_left == 0) {
                        event->event_state = EVENT_STATE_FAILED;
                        chain_action_next = EVENT_ACTION_REFUSED;
                        // final reprimand is the "kingdom rating" messages???
                        // -- these are handled SEPARATELY by the chained scenario events! --
                    }
                }
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
            city_message_post_full(true, MESSAGE_TEMPLATE_GENERAL, id, caller_event_id,
                                   PHRASE_rating_change_title_I, PHRASE_rating_change_initial_announcement_I,
                                   PHRASE_rating_change_reason_I_A,
                                   id, 0);
            break;
        case EVENT_TYPE_REPUTATION_DECREASE:
        case EVENT_TYPE_CITY_STATUS_CHANGE:
            break;
        case EVENT_TYPE_MESSAGE: {
//            int title_id = -1;
//            int body_id = -1;
            int phrase_id = -1; // TODO
            switch (event->subtype) {
                case EVENT_SUBTYPE_MSG_CITY_SAVED:
                    city_message_post_full(true, MESSAGE_TEMPLATE_CITY_SAVED, id, caller_event_id,
                                           PHRASE_eg_city_saved_title, PHRASE_eg_city_saved_initial_announcement,
                                           PHRASE_eg_city_saved_reason_A, id, 0);
                    break;
                case EVENT_SUBTYPE_MSG_DISTANT_BATTLE_WON:
                    city_message_post_full(true, MESSAGE_TEMPLATE_DISTANT_BATTLE_WON, id, caller_event_id,
                                           PHRASE_battle_won_title, PHRASE_battle_won_initial_announcement,
                                           PHRASE_battle_won_reason_A, id, 0);
                    break;
                case EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST:
                    city_message_post_full(true, MESSAGE_TEMPLATE_DISTANT_BATTLE_WON, id, caller_event_id,
                                           PHRASE_battle_lost_title, PHRASE_battle_lost_initial_announcement,
                                           PHRASE_battle_lost_reason_A, id, 0);
                    break;
                case EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT:
                    city_message_post_full(true, MESSAGE_TEMPLATE_GENERAL, id, caller_event_id,
                                           PHRASE_acknowledgement_title, PHRASE_acknowledgement_initial_announcement,
                                           PHRASE_acknowledgement_no_reason_A, id, 0);
                    break;
            }
            break;
        }
        case EVENT_TYPE_FAILED_FLOOD:
        case EVENT_TYPE_PERFECT_FLOOD:
        case EVENT_TYPE_GIFT:
        case EVENT_TYPE_LOCUSTS:
        case EVENT_TYPE_FROGS:
        case EVENT_TYPE_HAILSTORM:
        case EVENT_TYPE_BLOOD_RIVER:
        case EVENT_TYPE_CRIME_WAVE:
            break;
    }

    // propagate trigger events
    switch (chain_action_next) {
        case EVENT_ACTION_COMPLETED:
            event_process(event->on_completed_action, true, EVENT_ACTION_COMPLETED, id);
            break;
        case EVENT_ACTION_REFUSED:
            event_process(event->on_refusal_action, true, EVENT_ACTION_REFUSED, id);
            break;
        case EVENT_ACTION_TOOLATE:
            event_process(event->on_tooLate_action, true, EVENT_ACTION_TOOLATE, id);
            break;
        case EVENT_ACTION_DEFEAT:
            event_process(event->on_defeat_action, true, EVENT_ACTION_DEFEAT, id);
            break;
    }

    // disable if already done
    if (event->event_trigger_type == EVENT_TRIGGER_ONCE)
        event->event_state = EVENT_TRIGGER_ALREADY_FIRED;
}
void scenario_event_process() {
    // main event update loop
    for (int i = 0; i < *data.num_of_events; i++)
        event_process(i, false, -1);

    // secondly, update random value fields for recurring events
    for (int i = 0; i < *data.num_of_events; i++) {
        auto event = &data.event_list[i];
        if (event->event_trigger_type == EVENT_TRIGGER_RECURRING)
            update_randomized_values(event);
    }
}

///////

void scenario_events_save_state(buffer *buf) {

}
void scenario_events_load_state(buffer *buf) {

    // the first event's header always contains the total number of events
    data.num_of_events = &(data.event_list[0].num_total_header);

    for (int i = 0; i < MAX_EVENTS; i++) {
        event_ph_t *event = &data.event_list[i];
        event->num_total_header = buf->read_i16();
        if (!is_valid_event_index(i))
            return;
            event->__unk01 = buf->read_i16();
        event->event_id = buf->read_i16();
        event->type = buf->read_i8();
        event->month = buf->read_i8();
        event->item_fields[0] = buf->read_i16();
        event->item_fields[1] = buf->read_i16();
        event->item_fields[2] = buf->read_i16();
        event->item_fields[3] = buf->read_i16();
        event->amount_fields[0] = buf->read_i16();
        event->amount_fields[1] = buf->read_i16();
        event->amount_fields[2] = buf->read_i16();
        event->amount_fields[3] = buf->read_i16();
        event->time_fields[0] = buf->read_i16();
        event->time_fields[1] = buf->read_i16();
        event->time_fields[2] = buf->read_i16();
        event->time_fields[3] = buf->read_i16();
        event->location_fields[0] = buf->read_i16();
        event->location_fields[1] = buf->read_i16();
        event->location_fields[2] = buf->read_i16();
        event->location_fields[3] = buf->read_i16();
        event->on_completed_action = buf->read_i16();
        event->on_refusal_action = buf->read_i16();
        event->event_trigger_type = buf->read_i16();
            event->__unk07 = buf->read_i16();
        event->months_initial = buf->read_i16();
        event->quest_months_left = buf->read_i16();
        event->event_state = buf->read_i16();
        event->is_active = buf->read_i16();
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
        event->sender_faction = buf->read_i8();
            event->__unk13_i8 = buf->read_i8();
        event->route_fields[0] = buf->read_i16();
        event->route_fields[1] = buf->read_i16();
        event->route_fields[2] = buf->read_i16();
        event->route_fields[3] = buf->read_i16();
        event->subtype = buf->read_i8();
            event->__unk15_i8 = buf->read_i8(); // 07 --> 05
            event->__unk16 = buf->read_i16();
            event->__unk17 = buf->read_i16();
            event->__unk18 = buf->read_i16();
            event->__unk19 = buf->read_i16();
        event->on_completed_msgAlt = buf->read_i8();
        event->on_refusal_msgAlt = buf->read_i8();
        event->on_tooLate_msgAlt = buf->read_i8();
        event->on_defeat_msgAlt = buf->read_i8();
            event->__unk20a = buf->read_i16();
            event->__unk20b = buf->read_i16();
            event->__unk20c = buf->read_i16();
            event->__unk21 = buf->read_i16();
            event->__unk22 = buf->read_i16();
    }
}

///////

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