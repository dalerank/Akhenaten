#include "message_dialog.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "figure/formation.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/rich_text.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/video.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "input/scroll.h"
#include "io/gamefiles/lang.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/request.h"
#include "window/advisors.h"
#include "window/window_city.h"
#include "scenario/scenario_invasion.h"
#include "js/js_game.h"
#include "game/game.h"

#define MAX_HISTORY 200

static void draw_foreground_video();
static void draw_foreground_image();

static void button_back(int param1, int param2);
static void button_close(int param1, int param2);
static void button_help(int param1, int param2);
static void button_advisor(int advisor, int param2);
static void button_go_to_problem(int param1, int param2);

static image_button image_button_back = {0, 0, 31, 20, IB_NORMAL, PACK_GENERAL, 90, 8, button_back, button_none, 0, 0, 1};
static image_button image_button_close = {0, 0, 24, 24, IB_NORMAL, GROUP_CONTEXT_ICONS, 4, button_close, button_none, 0, 0, 1};
static image_button image_button_go_to_problem = {0, 0, 27, 27, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 52, button_go_to_problem, button_none, 1, 0, 1};
static image_button image_button_help = {0, 0, 18, 27, IB_NORMAL, GROUP_CONTEXT_ICONS, 0, button_help, button_none, 1, 0, 1};
static image_button image_button_labor = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 0, button_advisor, button_none, ADVISOR_LABOR, 0, 1};
static image_button image_button_trade = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 12, button_advisor, button_none, ADVISOR_TRADE, 0, 1};
static image_button image_button_population = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 15, button_advisor, button_none, ADVISOR_POPULATION, 0, 1};
static image_button image_button_imperial = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 6, button_advisor, button_none, ADVISOR_IMPERIAL, 0, 1};
static image_button image_button_military = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 3, button_advisor, button_none, ADVISOR_MILITARY, 0, 1};
static image_button image_button_health = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 18, button_advisor, button_none, ADVISOR_HEALTH, 0, 1};
static image_button image_button_religion = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 27, button_advisor, button_none, ADVISOR_RELIGION, 0, 1};

struct message_dialog_data_t {
    struct {
        int text_id;
        int scroll_position;
    } history[200];
    int num_history;

    uint16_t text_id;
    int message_id;
    bool is_eventmsg;
    pcstr title_text;
    pcstr body_template;
    bstring1024 body_text;
    pcstr phrase_template;
    bstring256 phrase_text;

    void (*background_callback)();
    bool show_video;
    bool background;
    uint16_t background_img;
    e_god god;

    vec2i pos;
    int x_text;
    int y_text;
    int text_height_blocks;
    int text_width_blocks;
    int focus_button_id;
    xstring help_id;
};

message_dialog_data_t g_message_dialog;

struct player_message {
    int year;
    int month;
    int param1;
    int param2;
    int message_advisor;
    bool use_popup;
};

player_message g_player_message_data;

static void write_to_body_text_buffer(pcstr in, pstr* out) {
    const size_t size = strlen(in);
    memcpy(*out, in, size);
    *out += size;
}

static void swap_tag(pcstr curr_byte, pstr* curr_byte_out, pcstr tag, pcstr content) {
    if (index_of_string(curr_byte, tag, 200) == 1) {
        write_to_body_text_buffer(content, curr_byte_out);
    }
}

void text_fill_in_tags(pcstr src, pstr dst, text_tag_substitution *tag_templates, int num_tags) {
    pstr curr_byte_out = dst;
    memset(curr_byte_out, 0, 1);
    for (int c = 0; c < 1000; c++) {
        pcstr curr_byte = src + c;

        if ((char)*curr_byte == '[') { // found an opening bracket
            pcstr tag_end_ptr = curr_byte + index_of((const uint8_t *)curr_byte, ']', 200);
            int size = static_cast<int>(tag_end_ptr - curr_byte - 1);

            // needs to go over all the possible tags...
            for (int i = 0; i < num_tags; ++i) {
                swap_tag(curr_byte, &curr_byte_out, tag_templates[i].tag.c_str(), tag_templates[i].content.c_str());
            }

            // go to the end of the tag, then resume
            curr_byte += size;
            c += size;
        } else {
            memcpy(curr_byte_out, curr_byte, 1);
            curr_byte_out++;
            if ((char)*curr_byte == '\0')
                return;
        }
    }
}

static void eventmsg_template_combine(pcstr template_ptr, pstr out_ptr, bool phrase_modifier) {
    auto &data = g_message_dialog;
    const auto& msg = city_message_get(data.message_id);

    bstring32 amount;
    bstring32 time; time.printf("%d", msg.req_months_left);
    int city_name_id = 0;

    if (phrase_modifier) {
        empire_city* city = g_empire.city(msg.req_city_past);
        if (city != nullptr) {
            city_name_id = city->name_id;
        }
        int value = stack_proper_quantity(msg.req_amount_past, msg.req_resource_past);
        amount.printf("%d", value);
    } else {
        empire_city *city = g_empire.city(msg.req_city);
        if (city != nullptr) {
            city_name_id = city->name_id;
        }
        int value = stack_proper_quantity(msg.req_amount, msg.req_resource);
        amount.printf("%d", value);
    }

    text_tag_substitution tags[] = {
      {"[greeting]", (pcstr)lang_get_string(32, 11 + g_scenario.settings.campaign_scenario_id)},
      {"[player_name]", (pcstr)city_player_name()},
      {"[reason_phrase]", data.phrase_text.c_str()},
      {"[city_name]", (pcstr)lang_get_string(195, city_name_id)},
      {"[a_foreign_army]", g_invasions.get_prop((e_enemy_type)msg.sender_faction).army_title},
      {"[amount]", amount.c_str()},
      {"[amount_granted]", ""}, // TODO
      {"[item]", (pcstr)lang_get_string(23, 54 + (phrase_modifier ? msg.req_resource_past : msg.req_resource))},
      {"[time_allotted]", time.c_str()},
      {"[time_until_attack]", ""}, // TODO
      {"[travel_time]", ""},       // TODO
      {"[god]", ""},               // TODO
    };
    text_fill_in_tags(template_ptr, out_ptr, tags, 12);
}

static void set_city_message(int year, int month, int param1, int param2, int message_advisor, int use_popup) {
    g_player_message_data.year = year;
    g_player_message_data.month = month;
    g_player_message_data.param1 = param1;
    g_player_message_data.param2 = param2;
    g_player_message_data.message_advisor = message_advisor;
    g_player_message_data.use_popup = use_popup;
}

static void init(xstring text_id, int message_id, void (*background_callback)()) {
    auto &data = g_message_dialog;
    scroll_drag_end();
    for (auto &item : data.history) {
        item.text_id = 0;
        item.scroll_position = 0;
    }
    data.num_history = 0;
    rich_text_reset(0);
    data.message_id = message_id;
    data.god = GOD_UNKNOWN;

    if (message_id != -1) {
        const city_message& city_msg = city_message_get(data.message_id);
        if (city_msg.eventmsg_body_id != -1) {
            data.is_eventmsg = true;
            data.title_text = g_scenario.events.msg_text(city_msg.eventmsg_title_id, 0);
            data.body_template = g_scenario.events.msg_text(city_msg.eventmsg_body_id, 0);
            data.phrase_template = g_scenario.events.msg_text(city_msg.eventmsg_phrase_id, 0);
            eventmsg_template_combine(data.phrase_template, data.phrase_text.data(), true);
            eventmsg_template_combine(data.body_template, data.body_text.data(), false);
        } else {
            data.is_eventmsg = false;
        }

        if (city_msg.god != GOD_UNKNOWN) {
            data.god = (e_god)city_msg.god;
        }

        if (city_msg.background_img) {
            data.background_img = city_msg.background_img;
        }
    } else {
        data.is_eventmsg = false;
    }

    const lang_message& msg = lang_get_message(text_id);
    data.text_id = msg.id;
    data.background_callback = background_callback;
    data.show_video = false;
    data.background = false;

    if (!g_player_message_data.use_popup) {
        return;
    }

    if (!msg.video.text.empty() && video_start(msg.video.text.c_str())) {
        data.show_video = true;
        video_init();
    } else if ((data.god != GOD_UNKNOWN) || (data.background_img > 0)) {
        data.background = true;
    } 
}

static int resource_image(int resource) {
    int image_id = image_id_resource_icon(resource);
    image_id += resource_image_offset(resource, RESOURCE_IMAGE_ICON);
    return image_id;
}

static int is_problem_message(const lang_message& msg) {
    return msg.type == TYPE_MESSAGE
           && (msg.message_type == MESSAGE_TYPE_DISASTER || msg.message_type == MESSAGE_TYPE_INVASION);
}

static int get_message_image_id(const lang_message& msg) {
    auto &data = g_message_dialog;
    if (!msg.image.id) {
        return 0;
    } else if (data.text_id == 0) {
        // message id = 0 ==> "about": fixed image position
        return image_id_from_group(PACK_UNLOADED, 25);
    } else {
        return image_id_from_group(GROUP_MESSAGE_IMAGES) + msg.image.id - 1;
    }
}

static void draw_city_message_text(const lang_message& msg) {
    auto &data = g_message_dialog;
    xstring text = msg.content.text;
    painter ctx = game.painter();
 
    if (data.is_eventmsg) {
        text = data.body_text;
    }
    
    if (!text) {
        return;
    }
    
    if (msg.message_type != MESSAGE_TYPE_TUTORIAL) {
        int width = lang_text_draw(25, g_player_message_data.month, data.x_text + 10, data.y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
        width += lang_text_draw_year(g_player_message_data.year, data.x_text + 12 + width, data.y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
        if (msg.message_type == MESSAGE_TYPE_DISASTER && g_player_message_data.param1) {
            if (data.text_id == MESSAGE_DIALOG_THEFT) {
                // param1 = denarii
                lang_text_draw_amount(8, 0, g_player_message_data.param1, data.pos.x + 240, data.y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
            } else {
                // param1 = building type
                lang_text_draw(41, g_player_message_data.param1, data.pos.x + 240, data.y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
            }
        } else {
            width += lang_text_draw(63, 5, data.x_text + width + 60, data.y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
            text_draw(city_player_name(), data.x_text + width + 60, data.y_text + 6, FONT_NORMAL_WHITE_ON_DARK, 0);
        }
    }

    switch (msg.message_type) {
        case MESSAGE_TYPE_DISASTER:
        case MESSAGE_TYPE_INVASION:
            lang_text_draw(12, 1, data.pos.x + 100, data.y_text + 44, FONT_NORMAL_WHITE_ON_DARK);
            rich_text_draw((const uint8_t*)text.c_str(), vec2i(data.x_text + 8, data.y_text + 86), 16 * data.text_width_blocks, data.text_height_blocks - 1, 0);
            break;

        case MESSAGE_TYPE_EMIGRATION: {
            int city_sentiment = g_city.sentiment.low_mood_cause;
            if (city_sentiment >= 1 && city_sentiment <= 5) {
                int max_width = 16 * (data.text_width_blocks - 1) - 64;
                lang_text_draw_multiline(12, city_sentiment + 2, vec2i{data.pos.x + 64, data.y_text + 44}, max_width, FONT_NORMAL_WHITE_ON_DARK);
            }
            rich_text_draw(text, vec2i(data.x_text + 8, data.y_text + 86), 16 * (data.text_width_blocks - 1), data.text_height_blocks - 1, 0);
            break;
        }
        case MESSAGE_TYPE_TUTORIAL:
            rich_text_draw(text, vec2i(data.x_text + 8, data.y_text + 6), 16 * data.text_width_blocks - 16, data.text_height_blocks - 1, 0);
            break;

        case MESSAGE_TYPE_TRADE_CHANGE:
            ImageDraw::img_generic(ctx, resource_image(g_player_message_data.param2), data.pos.x + 64, data.y_text + 40);
            lang_text_draw(21, g_empire.city(g_player_message_data.param1)->name_id, data.pos.x + 100, data.y_text + 44, FONT_NORMAL_WHITE_ON_DARK);
            rich_text_draw(text, vec2i(data.x_text + 8, data.y_text + 86), 16 * data.text_width_blocks - 16, data.text_height_blocks - 1, 0);
            break;

        case MESSAGE_TYPE_PRICE_CHANGE:
            ImageDraw::img_generic(ctx, resource_image(g_player_message_data.param2), data.pos.x + 64, data.y_text + 40);
            text_draw_money(g_player_message_data.param1, data.pos.x + 100, data.y_text + 44, FONT_NORMAL_WHITE_ON_DARK);
            rich_text_draw(text, vec2i(data.x_text + 8, data.y_text + 86), 16 * data.text_width_blocks - 16, data.text_height_blocks - 1, 0);
            break;

        default: {
            int lines = rich_text_draw(text, vec2i(data.x_text + 8, data.y_text + 56), 16 * data.text_width_blocks - 16, data.text_height_blocks - 1, 0);
            if (msg.message_type == MESSAGE_TYPE_IMPERIAL) {
                // in C3, the data is fetched from the request structure.
                // in Pharaoh, the data is stored with the message
                //                const scenario_request *request = scenario_request_get(player_message.param1);
                const auto& city_msg = city_message_get(data.message_id);
                int y_offset = data.y_text + 86 + lines * 16;
                ImageDraw::img_generic(ctx, resource_image(city_msg.req_resource), vec2i{data.x_text + 8, y_offset - 4});
                int width = text_draw_number(stack_proper_quantity(city_msg.req_amount, city_msg.req_resource), '@', " ", data.x_text + 28, y_offset, FONT_NORMAL_WHITE_ON_DARK);
                lang_text_draw(23, city_msg.req_resource, data.x_text + 26 + width, y_offset, FONT_NORMAL_WHITE_ON_DARK);
                //                if (request->state == REQUEST_STATE_NORMAL || request->state == REQUEST_STATE_OVERDUE) {
                width = lang_text_draw_amount(8, 4, city_msg.req_months_left, data.x_text + 200, y_offset, FONT_NORMAL_WHITE_ON_DARK);
                lang_text_draw(12, 2, data.x_text + 200 + width, y_offset, FONT_NORMAL_WHITE_ON_DARK);
                //                }
            }
            break;
        }
    }
}

static void draw_title(const lang_message& msg) {
    auto &data = g_message_dialog;

    painter ctx = game.painter();
    xstring text = msg.title.text;
    const city_message& city_msg = city_message_get(data.message_id);
    
    if (data.is_eventmsg)
        text = data.title_text;

    if (!text) {
        return;
    }

    int image_id = get_message_image_id(msg);
    const image_t* img = image_id ? image_get(image_id) : 0;
    // title
    if (msg.message_type == MESSAGE_TYPE_TUTORIAL) {
        text_draw_centered(text.c_str(), data.pos.x, data.pos.y + msg.title.pos.y, 16 * msg.size.x, FONT_LARGE_BLACK_ON_LIGHT, 0);
    } else {
        // Center title in the dialog but ensure it does not overlap with the
        // image: if the title is too long, it will start 8px from the image.
        int title_x_offset = img ? img->width + msg.image.pos.x + 8 : 0;
        text_draw_centered(text.c_str(), data.pos.x + title_x_offset, data.pos.y + 14, 16 * msg.size.x - 2 * title_x_offset, FONT_LARGE_BLACK_ON_LIGHT, 0);
    }
    data.y_text = data.pos.y + 48;

    // picture
    if (img && !city_msg.hide_img) {
        int image_x = msg.image.pos.x;
        int image_y = msg.image.pos.y;
        ImageDraw::img_generic(ctx, image_id, vec2i{data.pos.x + image_x, data.pos.y + image_y});

        if (data.pos.y + image_y + img->height + 8 > data.y_text)
            data.y_text = data.pos.y + image_y + img->height + 8;
    }
}
static void draw_subtitle(const lang_message& msg) {
    auto &data = g_message_dialog;
    if (msg.subtitle.pos.x && !msg.subtitle.text.empty()) {
        int width = 16 * msg.size.x - 16 - msg.subtitle.pos.x;
        int height = text_draw_multiline(msg.subtitle.text, data.pos.x + msg.subtitle.pos.x, data.pos.y + msg.subtitle.pos.y, width, FONT_NORMAL_BLACK_ON_LIGHT, 0);

        if (data.pos.y + msg.subtitle.pos.y + height > data.y_text)
            data.y_text = data.pos.y + msg.subtitle.pos.y + height;
    }
}
static void draw_content(const lang_message& msg) {
    auto &data = g_message_dialog;
    xstring text = msg.content.text;
    if (data.is_eventmsg) {
        text = data.body_text;
    }

    if (!text) {
        return;
    }
    
    int header_offset = msg.type == TYPE_MANUAL ? 48 : 32;
    data.text_height_blocks = msg.size.y - 1 - (header_offset + data.y_text - data.pos.y) / 16;
    data.text_width_blocks = rich_text_init(text, vec2i(data.x_text, data.y_text), msg.size.x - 4, data.text_height_blocks, /*adjust_width_on_no_scroll*/true);

    // content!
    inner_panel_draw({ data.x_text, data.y_text }, { data.text_width_blocks, data.text_height_blocks });
    graphics_set_clip_rectangle({data.x_text + 3, data.y_text + 3}, {16 * data.text_width_blocks - 6, 16 * data.text_height_blocks - 6});
    rich_text_clear_links();

    if (msg.type == TYPE_MESSAGE) {
        draw_city_message_text(msg);
    } else {
        rich_text_draw(text, vec2i(data.x_text + 8, data.y_text + 6), 16 * data.text_width_blocks - 16, data.text_height_blocks - 1, 0);
    }
    
    graphics_reset_clip_rectangle();
}

static void draw_background_normal() {
    auto &data = g_message_dialog;
    rich_text_set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    const lang_message& msg = lang_get_message(data.text_id);
    data.pos = msg.pos;
    data.x_text = data.pos.x + 16;
    outer_panel_draw(data.pos, msg.size.x, msg.size.y);

    draw_title(msg);
    draw_subtitle(msg);
    draw_content(msg);
}

static void draw_background_image() {
    auto &data = g_message_dialog;
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(data.text_id);
    data.pos = { 32, 28 };

    int small_font = 0;
    int lines_available = 4;
    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_IMPERIAL) {
        lines_available = 3;
    }

    rich_text_set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    rich_text_clear_links();
    int lines_required = rich_text_draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    if (lines_required > lines_available) {
        small_font = 1;
        rich_text_set_fonts(FONT_SMALL_PLAIN, FONT_SMALL_PLAIN);
        lines_required = rich_text_draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    }

    outer_panel_draw(data.pos, 26, 28);
    graphics_draw_rect(data.pos + vec2i{7, 7}, vec2i{402, 294}, COLOR_BLACK);

    int y_base = data.pos.y + 308;
    int inner_height_blocks = 6;
    if (lines_required > lines_available) {
        // create space to cram an extra line into the dialog
        y_base = y_base - 8;
        inner_height_blocks += 1;
    }
    inner_panel_draw({ data.pos.x + 8, y_base }, { 25, inner_height_blocks });
    text_draw_centered(msg.title.text, data.pos.x + 8, data.pos.y + 414, 400, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    int width = lang_text_draw(25, g_player_message_data.month, data.pos.x + 16, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw_year(g_player_message_data.year, data.pos.x + 18 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);

    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_DISASTER && data.text_id == MESSAGE_DIALOG_THEFT) {
        lang_text_draw_amount(8, 0, g_player_message_data.param1, data.pos.x + 90 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        width += lang_text_draw(63, 5, data.pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
        text_draw(city_player_name(), data.pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK, 0);
    }

    data.text_height_blocks = msg.size.y - 1 - (32 + data.y_text - data.pos.y) / 16;
    data.text_width_blocks = msg.size.x - 4;
    if (small_font) {
        // Draw in black and then white to create shadow effect
        rich_text_draw_colored(msg.content.text, vec2i(data.pos.x + 16 + 1, y_base + 24 + 1), 384, data.text_height_blocks - 1, COLOR_BLACK);
        rich_text_draw_colored(msg.content.text, vec2i(data.pos.x + 16, y_base + 24), 384, data.text_height_blocks - 1, COLOR_WHITE);
    } else {
        rich_text_draw(msg.content.text, vec2i(data.pos.x + 16, y_base + 24), 384, data.text_height_blocks - 1, 0);
    }

    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_IMPERIAL) {
        int y_text = data.pos.y + 384;
        if (lines_required > lines_available)
            y_text += 8;

        scenario_request request = scenario_request_get_visible(g_player_message_data.param1);
        if (request.is_valid()) {
            text_draw_number(request.amount, '@', " ", data.pos.x + 8, y_text, FONT_NORMAL_WHITE_ON_DARK);
            ImageDraw::img_generic(ctx, image_id_resource_icon(request.resource) + resource_image_offset(request.resource, RESOURCE_IMAGE_ICON), vec2i{data.pos.x + 70, y_text - 5});
            lang_text_draw(23, request.resource, data.pos.x + 100, y_text, FONT_NORMAL_WHITE_ON_DARK);
            if (request.state <= e_event_state_overdue) {
                width = lang_text_draw_amount(8, 4, request.months_to_comply, data.pos.x + 200, y_text, FONT_NORMAL_WHITE_ON_DARK);
                lang_text_draw(12, 2, data.pos.x + 200 + width, y_text, FONT_NORMAL_WHITE_ON_DARK);
            }
        }
    }

    const image_t *img = nullptr;
    if (data.god != GOD_UNKNOWN) {
        int image_id = image_id_from_group(GROUP_PANEL_GODS_DIALOGDRAW) + 19 + data.god;
        img = image_get(image_id);
    } else if (data.background) {
        int image_id = data.background_img;
        if (image_id == messages::IMAGE_FROM_SCHEME) {
            int img_pack = msg.image.pack > 0 ? msg.image.pack : PACK_UNLOADED;
            img = image_get({ img_pack, msg.image.id, msg.image.offset });
        } else {
            img = image_get(image_id);
        }
    } 

    if (img) {
        int current_x = (500 - img->width) / 2;
        ImageDraw::img_generic(ctx, img, vec2i{ current_x, 96 });
    }

    draw_foreground_image();
}

static void draw_background_video() {
    auto &data = g_message_dialog;
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(data.text_id);
    data.pos = { 32, 28 };

    int small_font = 0;
    int lines_available = 4;
    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_IMPERIAL)
        lines_available = 3;

    rich_text_set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    rich_text_clear_links();
    int lines_required = rich_text_draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    if (lines_required > lines_available) {
        small_font = 1;
        rich_text_set_fonts(FONT_SMALL_PLAIN, FONT_SMALL_PLAIN);
        lines_required = rich_text_draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    }

    outer_panel_draw(data.pos, 26, 28);
    graphics_draw_rect(data.pos + vec2i{7, 7}, vec2i{402, 294}, COLOR_BLACK);

    int y_base = data.pos.y + 308;
    int inner_height_blocks = 6;
    if (lines_required > lines_available) {
        // create space to cram an extra line into the dialog
        y_base = y_base - 8;
        inner_height_blocks += 1;
    }
    inner_panel_draw({ data.pos.x + 8, y_base }, { 25, inner_height_blocks });
    text_draw_centered(msg.title.text, data.pos.x + 8, data.pos.y + 414, 400, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    int width = lang_text_draw(25, g_player_message_data.month, data.pos.x + 16, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw_year(g_player_message_data.year, data.pos.x + 18 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);

    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_DISASTER
        && data.text_id == MESSAGE_DIALOG_THEFT) {
        lang_text_draw_amount(8, 0, g_player_message_data.param1, data.pos.x + 90 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        width += lang_text_draw(63, 5, data.pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
        text_draw(city_player_name(), data.pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK, 0);
    }

    data.text_height_blocks = msg.size.y - 1 - (32 + data.y_text - data.pos.y) / 16;
    data.text_width_blocks = msg.size.x - 4;
    if (small_font) {
        // Draw in black and then white to create shadow effect
        rich_text_draw_colored(msg.content.text, vec2i(data.pos.x + 16 + 1, y_base + 24 + 1), 384, data.text_height_blocks - 1, COLOR_BLACK);
        rich_text_draw_colored(msg.content.text, vec2i(data.pos.x + 16, y_base + 24), 384, data.text_height_blocks - 1, COLOR_WHITE);
    } else {
        rich_text_draw(msg.content.text, vec2i(data.pos.x + 16, y_base + 24), 384, data.text_height_blocks - 1, 0);
    }

    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_IMPERIAL) {
        int y_text = data.pos.y + 384;
        if (lines_required > lines_available)
            y_text += 8;

        scenario_request request = scenario_request_get_visible(g_player_message_data.param1);
        text_draw_number(request.amount, '@', " ", data.pos.x + 8, y_text, FONT_NORMAL_WHITE_ON_DARK);
        ImageDraw::img_generic(ctx, image_id_resource_icon(request.resource) + resource_image_offset(request.resource, RESOURCE_IMAGE_ICON), data.pos.x + 70, y_text - 5);
        lang_text_draw(23, request.resource, data.pos.x + 100, y_text, FONT_NORMAL_WHITE_ON_DARK);
        if (request.state <= e_event_state_overdue) {
            width = lang_text_draw_amount(8, 4, request.months_to_comply, data.pos.x + 200, y_text, FONT_NORMAL_WHITE_ON_DARK);
            lang_text_draw(12, 2, data.pos.x + 200 + width, y_text, FONT_NORMAL_WHITE_ON_DARK);
        }
    }

    draw_foreground_video();
}

static void draw_background(int) {
    auto &data = g_message_dialog;
    if (data.background_callback) {
        data.background_callback();
    } else {
        window_draw_underlying_window(0);
    }

    graphics_set_to_dialog();
    if (data.show_video) {
        draw_background_video();
    } else if (data.background) {
        draw_background_image();
    } else {
        draw_background_normal();
    }

    graphics_reset_dialog();
}

static image_button* get_advisor_button() {
    switch (g_player_message_data.message_advisor) {
    case MESSAGE_ADVISOR_LABOR:
        return &image_button_labor;
    case MESSAGE_ADVISOR_TRADE:
        return &image_button_trade;
    case MESSAGE_ADVISOR_POPULATION:
        return &image_button_population;
    case MESSAGE_ADVISOR_IMPERIAL:
        return &image_button_imperial;
    case MESSAGE_ADVISOR_MILITARY:
        return &image_button_military;
    case MESSAGE_ADVISOR_HEALTH:
        return &image_button_health;
    case MESSAGE_ADVISOR_RELIGION:
        return &image_button_religion;
    default:
        return &image_button_help;
    }
}

static void draw_foreground_normal() {
    auto &data = g_message_dialog;
    const lang_message& msg = lang_get_message(data.text_id);

    if (msg.type == TYPE_MANUAL && data.num_history > 0) {
        image_buttons_draw({data.pos.x + 16, data.pos.y + 16 * msg.size.y - 36}, &image_button_back, 1);
        lang_text_draw(12, 0, data.pos.x + 52, data.pos.y + 16 * msg.size.y - 31, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (msg.type == TYPE_MESSAGE) {
        image_buttons_draw({data.pos.x + 16, data.pos.y + 16 * msg.size.y - 40}, get_advisor_button(), 1);
        if (msg.message_type == MESSAGE_TYPE_DISASTER || msg.message_type == MESSAGE_TYPE_INVASION)
            image_buttons_draw({data.pos.x + 64, data.y_text + 36}, &image_button_go_to_problem, 1);
    }
    image_buttons_draw({data.pos.x + 16 * msg.size.x - 38, data.pos.y + 16 * msg.size.y - 36}, &image_button_close, 1);
    rich_text_draw_scrollbar(vec2i{0, 0});
}

static void draw_foreground_image() {
    auto &data = g_message_dialog;

    image_buttons_draw({data.pos.x + 16, data.pos.y + 408}, get_advisor_button(), 1);
    image_buttons_draw({data.pos.x + 372, data.pos.y + 410}, &image_button_close, 1);
    const lang_message& msg = lang_get_message(data.text_id);
    if (is_problem_message(msg)) {
        image_buttons_draw({data.pos.x + 48, data.pos.y + 407}, &image_button_go_to_problem, 1);
    }
}

static void draw_foreground_video() {
    auto &data = g_message_dialog;
    video_draw(data.pos.x + 8, data.pos.y + 8);
    image_buttons_draw({data.pos.x + 16, data.pos.y + 408}, get_advisor_button(), 1);
    image_buttons_draw({data.pos.x + 372, data.pos.y + 410}, &image_button_close, 1);
    const lang_message& msg = lang_get_message(data.text_id);
    if (is_problem_message(msg)) {
        image_buttons_draw({data.pos.x + 48, data.pos.y + 407}, &image_button_go_to_problem, 1);
    }
}

static void draw_foreground(int) {
    auto &data = g_message_dialog;
    graphics_set_to_dialog();
    if (data.show_video) {
        draw_foreground_video();
    } else if (data.background) {
        draw_foreground_image();
    } else {
        draw_foreground_normal();
    }

    graphics_reset_dialog();
}

static bool handle_input_video(const mouse* m_dialog, const lang_message& msg) {
    auto &data = g_message_dialog;
    if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 16, data.pos.y + 408}, get_advisor_button(), 1, 0)) {
        return true;
    }

    if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 372, data.pos.y + 410}, &image_button_close, 1, 0)) {
        return true;
    }

    if (is_problem_message(msg)) {
        if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 48, data.pos.y + 407}, &image_button_go_to_problem, 1, &data.focus_button_id)) {
            return true;
        }
    }
    return false;
}

static bool handle_input_godmsg(const mouse* m_dialog, const lang_message& msg) {
    auto &data = g_message_dialog;
    if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 16, data.pos.y + 408}, get_advisor_button(), 1, 0)) {
        return true;
    }

    if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 372, data.pos.y + 410}, &image_button_close, 1, 0)) {
        return true;
    }

    if (is_problem_message(msg)) {
        if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 48, data.pos.y + 407}, &image_button_go_to_problem, 1, &data.focus_button_id)) {
            return true;
        }
    }
    return false;
}

static bool handle_input_normal(const mouse* m_dialog, const lang_message& msg) {
    auto &data = g_message_dialog;
    if (msg.type == TYPE_MANUAL && image_buttons_handle_mouse(m_dialog, {data.pos.x + 16, data.pos.y + 16 * msg.size.y - 36}, &image_button_back, 1, 0)) {
        return true;
    }

    if (msg.type == TYPE_MESSAGE) {
        if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 16, data.pos.y + 16 * msg.size.y - 40}, get_advisor_button(), 1, 0)) {
            return true;
        }

        if (msg.message_type == MESSAGE_TYPE_DISASTER || msg.message_type == MESSAGE_TYPE_INVASION) {
            if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 64, data.y_text + 36}, &image_button_go_to_problem, 1, 0))
                return true;
        }
    }

    if (image_buttons_handle_mouse(m_dialog, {data.pos.x + 16 * msg.size.x - 38, data.pos.y + 16 * msg.size.y - 36}, &image_button_close, 1, 0)) {
        return true;
    }

    rich_text_handle_mouse(m_dialog, vec2i{0, 0});
    int text_id = rich_text_get_clicked_link(m_dialog);
    if (text_id >= 0) {
        if (data.num_history < MAX_HISTORY - 1) {
            data.history[data.num_history].text_id = data.text_id;
            data.history[data.num_history].scroll_position = rich_text_scroll_position();
            data.num_history++;
        }
        data.text_id = text_id;
        rich_text_reset(0);
        return true;
    }
    return false;
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_message_dialog;
    data.focus_button_id = 0;
    const mouse* m_dialog = mouse_in_dialog(m);
    const lang_message& msg = lang_get_message(data.text_id);
    bool handled;
    if (data.show_video) {
        handled = handle_input_video(m_dialog, msg);
    } else if (data.background) {
        handled = handle_input_godmsg(m_dialog, msg);
    } else {
        handled = handle_input_normal(m_dialog, msg);
    }

    if (!handled && input_go_back_requested(m, h)) {
        button_close(0, 0);
    }
}

static void cleanup() {
    auto &data = g_message_dialog;
    if (data.show_video) {
        video_stop();
        data.show_video = false;
    }
    g_player_message_data.message_advisor = 0;
}

static void button_back(int /* param1 */, int /* param2 */) {
    auto &data = g_message_dialog;
    if (data.num_history > 0) {
        data.num_history--;
        data.text_id = data.history[data.num_history].text_id;
        rich_text_reset(data.history[data.num_history].scroll_position);
    }
}

static void button_close(int param1, int param2) {
    cleanup();
    window_go_back();
}

static void button_help(int param1, int param2) {
    auto &data = g_message_dialog;
    button_close(0, 0);
    window_message_dialog_show("message_dialog_help", -1, data.background_callback);
}

static void button_advisor(int advisor, int param2) {
    cleanup();
    if (!window_advisors_show_advisor((e_advisor)advisor))
        window_city_show();
}

static void button_go_to_problem(int param1, int param2) {
    auto &data = g_message_dialog;
    cleanup();
    const lang_message& msg = lang_get_message(data.text_id);
    int grid_offset = g_player_message_data.param2;
    if (msg.message_type == MESSAGE_TYPE_INVASION) {
        int invasion_grid_offset = formation_grid_offset_for_invasion(g_player_message_data.param1);
        if (invasion_grid_offset > 0)
            grid_offset = invasion_grid_offset;
    }

    if (grid_offset > 0 && grid_offset < 26244) {
        camera_go_to_mappoint(tile2i(grid_offset));
    }

    window_city_show();
}

void window_message_setup_help_id(xstring helpid) {
    g_message_dialog.help_id = helpid;
}

void window_show_help() {
    auto &data = g_window_manager;
    auto &current_window = data.window_queue[data.queue_index];
    if (!g_message_dialog.help_id.empty()) {
        window_message_dialog_show(g_message_dialog.help_id, -1, nullptr);
    }
}
ANK_FUNCTION(window_show_help)

void window_message_dialog_show(xstring text_id, int message_id, void (*background_callback)(void)) {
    static window_type window = {
        WINDOW_MESSAGE_DIALOG,
        draw_background,
        draw_foreground,
        handle_input,
        nullptr
    };

    init(text_id, message_id, background_callback);
    window_show(&window);
}

void window_message_dialog_show_city_message(xstring text_id, int message_id, int year, int month, int param1, int param2, int message_advisor, bool use_popup) {
    set_city_message(year, month, param1, param2, message_advisor, use_popup);
    window_message_dialog_show(text_id, message_id, window_city_draw_all);
}
