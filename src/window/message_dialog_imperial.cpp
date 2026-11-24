#include "message_dialog_imperial.h"

#include "city/city_message.h"
#include "city/city_resource_handle.h"
#include "io/gamefiles/lang.h"
#include "core/string.h"

void ui::message_dialog_imperial::draw_content(const lang_message &msg) {
    assert(msg.type == MESSAGE_ARCH_MESSAGE);
    draw_city_message_text(msg);
}

void ui::message_dialog_imperial::draw_city_message_text(const lang_message& msg) {
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    const auto& city_msg = message_manager().get(message_id);
    bstring1024 full_text;
    int resource_image_id = resource_image(city_msg.req_resource);

    city_resource_handle hresource{ (e_resource)city_msg.req_resource };
    full_text.printf("%s @P@P%s @P@P @I%d %d %s %s %d %s",
                     header.c_str(),
                     text.c_str(),
                     resource_image_id, hresource.stack_proper_quantity(city_msg.req_amount), hresource.name().c_str(),
                     ui::str(8, 4), city_msg.req_months_left, ui::str(12, 2));

    ui["content_text"] = full_text;
}
