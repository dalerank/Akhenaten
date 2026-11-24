#include "message_dialog_emigration.h"
#include "city/city_sentiment.h"

#include "city/city.h"
#include "io/gamefiles/lang.h"
#include "core/string.h"

void ui::message_dialog_emigration::draw_city_message_text(const lang_message& msg) {
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    bstring1024 full_text;
    int low_mood_cause = city_sentiment().low_mood_cause;
    if (low_mood_cause >= 1 && low_mood_cause <= 5) {
        full_text.printf("%s @P%s @P%s", header.c_str(), text.c_str(), ui::str(12, low_mood_cause + 2));
    } else {
        full_text.printf("%s @P%s", header.c_str(), text.c_str());
    }

    ui["content_text"] = full_text;
}
