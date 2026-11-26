#include "city/city_message_chunks.h"

#include "city/city_message.h"
#include "io/io_buffer.h"

void messages_chunk::bind_data(io_buffer* iob) {
    auto& data = message_manager();
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
        iob->bind_i16(msg.sender_faction);    // FF FF

        iob->bind(BIND_SIGNATURE_INT16, &msg.req_city);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_amount);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_resource);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_months_left);
        iob->bind(BIND_SIGNATURE_INT16, &msg.unk_07);

        iob->bind(BIND_SIGNATURE_INT16, &msg.eventmsg_phrase_id);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_city_past);    // enum?
        iob->bind(BIND_SIGNATURE_INT16, &msg.delivered_amount); // OG phrases[EVENT_PHRASE_DELIVERED_AMOUNT]
        iob->bind(BIND_SIGNATURE_UINT8, &msg.gift_buttons);     // OG phrases[EVENT_PHRASE_BUTTONS], low byte
        iob->bind(BIND_SIGNATURE_UINT8, &msg.hide_img);         // 00 00

        iob->bind(BIND_SIGNATURE_INT16, &msg.req_amount_past);
        iob->bind(BIND_SIGNATURE_INT16, &msg.req_resource_past);
        iob->bind(BIND_SIGNATURE_INT8, &msg.unk_11a_i8);       // FF
        iob->bind(BIND_SIGNATURE_UINT8, &msg.god);             // FF
        iob->bind(BIND_SIGNATURE_UINT16, &msg.background_img); // 00 00
    }
}

void message_extra_chunk::bind_data(io_buffer* iob) {
    auto& data = message_manager();
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
}
