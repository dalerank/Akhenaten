#include "message_dialog_new.h"
#include "message_dialog_disaster.h"
#include "message_dialog_imperial.h"
#include "message_dialog_emigration.h"
#include "message_dialog_tutorial.h"
#include "message_dialog_trade_change.h"
#include "message_dialog_price_change.h"
#include "message_dialog_invasion.h"

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
#include "message_dialog.h"
#include "core/string.h"

static ui::message_dialog_base* g_message_dialog_instance = nullptr;

ui::message_dialog_base::message_dialog_base(pcstr config_name) : autoconfig_window(config_name), config_name(config_name) {
    num_history = 0;
    text_id = 0;
    message_id = -1;
    is_eventmsg = false;
    title_text = nullptr;
    body_template = nullptr;
    phrase_template = nullptr;
    background_callback = nullptr;
    show_video = false;
    background = false;
    background_img = 0;
    god = GOD_UNKNOWN;
    pos = {0, 0};
    x_text = 0;
    y_text = 0;
    text_height_blocks = 0;
    text_width_blocks = 0;
    focus_button_id = 0;
    player_msg.year = 0;
    player_msg.month = 0;
    player_msg.param1 = 0;
    player_msg.param2 = 0;
    player_msg.message_advisor = 0;
    player_msg.use_popup = false;
    subtitle_text = "";
    subtitle_pos = {0, 0};
    
    for (auto &item : history) {
        item.text_id = 0;
        item.scroll_position = 0;
    }
}

pcstr ui::message_dialog_base::get_section() const {
    return config_name.c_str();
}

void ui::message_dialog_base::init_widgets(xstring text_id) {
    const lang_message &msg = lang_get_message(text_id);
    
    ui["button_close"].onclick([this] { button_close(); });
    //ui["button_back"].onclick([this] { button_back(); });
    ui["button_help"].onclick([this] { button_help(); });

    // Advisor button will be set dynamically
    ui["button_advisor"].onclick([this] {
        int advisor = player_msg.message_advisor;
        if (advisor == 0) {
            advisor = MESSAGE_ADVISOR_LABOR;
        }
        button_advisor(advisor);
    });

    // button_go_to_problem is set up in derived classes that need it
}

void ui::message_dialog_base::init() {
    autoconfig_window::init();
}

void ui::message_dialog_base::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    init_widgets(text_id);

    scroll_drag_end();
    for (auto &item : history) {
        item.text_id = 0;
        item.scroll_position = 0;
    }
    num_history = 0;

    this->message_id = message_id;
    god = GOD_UNKNOWN;
    background_img = 0;

    if (message_id != -1) {
        const city_message& city_msg = city_message_get(this->message_id);
        if (city_msg.eventmsg_body_id != -1) {
            is_eventmsg = true;
            title_text = g_scenario.events.msg_text(city_msg.eventmsg_title_id, 0);
            body_template = g_scenario.events.msg_text(city_msg.eventmsg_body_id, 0);
            phrase_template = g_scenario.events.msg_text(city_msg.eventmsg_phrase_id, 0);
            eventmsg_template_combine(phrase_template, phrase_text.data(), true);
            eventmsg_template_combine(body_template, body_text.data(), false);
        } else {
            is_eventmsg = false;
        }

        if (city_msg.god != GOD_UNKNOWN) {
            god = (e_god)city_msg.god;
        }

        if (city_msg.background_img) {
            background_img = city_msg.background_img;
        }
    } else {
        is_eventmsg = false;
    }

    const lang_message& msg = lang_get_message(text_id);
    this->text_id = msg.id;
    this->background_callback = background_callback;
    show_video = false;
    background = false;
    
    // Setup subtitle from message
    subtitle_text = msg.subtitle.text;
    subtitle_pos = msg.subtitle.pos;
    if (!subtitle_text.empty() && subtitle_pos.x) {
        ui["subtitle"].text(subtitle_text.c_str());
        ui["subtitle"].pos = {0, subtitle_pos.y};
        ui["subtitle"].enabled = true;
    } else {
        ui["subtitle"].enabled = false;
    }

    pos = msg.pos;

    // Update UI element positions
    ui["background"].pos = pos;
    ui["background"].size = { msg.size.x, msg.size.y };
    ui["background"].enabled = true;

    ui["title"].pos = { pos.x, pos.y + 14 };
    ui["title"].size = { 16 * msg.size.x, 20 };
    ui["title"].enabled = true;


    // Config is already loaded by the derived class constructor
    _is_inited = false;

    if (!player_msg.use_popup) {
        return;
    }

    if (!msg.video.text.empty() && video_start(msg.video.text.c_str())) {
        show_video = true;
        video_init();
    } else if ((god != GOD_UNKNOWN) || background_img) {
        background = true;
    }
}

void ui::message_dialog_base::set_city_message(int year, int month, int param1, int param2, int message_advisor, bool use_popup) {
    player_msg.year = year;
    player_msg.month = month;
    player_msg.param1 = param1;
    player_msg.param2 = param2;
    player_msg.message_advisor = message_advisor;
    player_msg.use_popup = use_popup;
}

void ui::message_dialog_base::eventmsg_template_combine(pcstr template_ptr, pstr out_ptr, bool phrase_modifier) {
    const auto& msg = city_message_get(message_id);

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
      {"[reason_phrase]", phrase_text.c_str()},
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

void text_fill_in_tags(pcstr src, pstr dst, text_tag_substitution* tag_templates, int num_tags) {
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

int ui::message_dialog_base::resource_image(int resource) {
    int image_id = image_id_resource_icon(resource);
    image_id += resource_image_offset(resource, RESOURCE_IMAGE_ICON);
    return image_id;
}


int ui::message_dialog_base::get_message_image_id(const lang_message& msg) {
    if (!msg.image.id) {
        return 0;
    } else if (text_id == 0) {
        // message id = 0 ==> "about": fixed image position
        return image_id_from_group(PACK_UNLOADED, 25);
    } else {
        return image_id_from_group(GROUP_MESSAGE_IMAGES) + msg.image.id - 1;
    }
}

image_button* ui::message_dialog_base::get_advisor_button() {
    static image_button image_button_labor = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 0, nullptr, button_none, ADVISOR_LABOR, 0, 1};
    static image_button image_button_trade = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 12, nullptr, button_none, ADVISOR_TRADE, 0, 1};
    static image_button image_button_population = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 15, nullptr, button_none, ADVISOR_POPULATION, 0, 1};
    static image_button image_button_imperial = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 6, nullptr, button_none, ADVISOR_IMPERIAL, 0, 1};
    static image_button image_button_military = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 3, nullptr, button_none, ADVISOR_MILITARY, 0, 1};
    static image_button image_button_health = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 18, nullptr, button_none, ADVISOR_HEALTH, 0, 1};
    static image_button image_button_religion = {0, 0, 27, 27, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 27, nullptr, button_none, ADVISOR_RELIGION, 0, 1};
    static image_button image_button_help = {0, 0, 18, 27, IB_NORMAL, GROUP_CONTEXT_ICONS, 0, nullptr, button_none, 1, 0, 1};

    switch (player_msg.message_advisor) {
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

void ui::message_dialog_base::draw_image(const lang_message& msg) {
    const city_message& city_msg = city_message_get(message_id);
    
    int image_id = get_message_image_id(msg);
    const image_t* img = image_id ? image_get(image_id) : 0;

    // picture
    if (img && !city_msg.hide_img) {
        int image_x = msg.image.pos.x;
        int image_y = msg.image.pos.y;
        ui::eimage(image_id, vec2i{pos.x + image_x, pos.y + image_y});
    }
}

void ui::message_dialog_base::draw_city_message_text(const lang_message& msg) {
    xstring text = msg.content.text;
    painter ctx = game.painter();
 
    if (is_eventmsg) {
        text = body_text;
    }
    
    if (!text) {
        return;
    }
    

    bstring1024 header;
    header.printf("%s %d %s %s", ui::str(25, player_msg.month), player_msg.year, ui::str(63, 5), city_player_name());

    const auto &city_msg = city_message_get(message_id);
    bstring1024 full_text;
    int resource_image = image_id_resource_icon(city_msg.req_resource);
    full_text.printf("%s\n %s", header.c_str(), text.c_str());

    ui["content_text"] = full_text;
}

void ui::message_dialog_base::draw_content(const lang_message& msg) {
    xstring text = msg.content.text;
    if (is_eventmsg) {
        text = body_text;
    }

    if (!text) {
        return;
    }

    if (msg.type == TYPE_MESSAGE) {
        draw_city_message_text(msg);
    } else {
        ui["content_text"] = text;
    }
    
    graphics_reset_clip_rectangle();
}

void ui::message_dialog_base::draw_background_normal() {
    const lang_message& msg = lang_get_message(text_id);

    draw_image(msg);
    draw_content(msg);
}

void ui::message_dialog_base::draw_background_image() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    ui["content_text"] = msg.content.text;

    const image_t *img = nullptr;
    if (god != GOD_UNKNOWN) {
        int image_id = image_id_from_group(GROUP_PANEL_GODS_DIALOGDRAW) + 19 + god;
        img = image_get(image_id);
    } else if (background) {
        int image_id = background_img;
        if (image_id == messages::IMAGE_FROM_SCHEME) {
            int img_pack = msg.image.pack > 0 ? msg.image.pack : PACK_UNLOADED;
            img = image_get({ img_pack, msg.image.id, msg.image.offset });
        } else {
            img = image_get(image_id);
        }
    } 

    if (img) {
        int current_x = (500 - img->width) / 2;
        ctx.img_generic(img, vec2i{ current_x, 96 });
    }

    draw_foreground_image();
}

void ui::message_dialog_base::draw_background_video() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    graphics_draw_rect(pos + vec2i{7, 7}, vec2i{402, 294}, COLOR_BLACK);

    ui["content_text"] = msg.content.text;

    draw_foreground_video();
}

int ui::message_dialog_base::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    if (background_callback) {
        background_callback();
    } else {
        window_draw_underlying_window(0);
    }

    graphics_set_to_dialog();
    if (show_video) {
        draw_background_video();
    } else if (background) {
        draw_background_image();
    } else {
        draw_background_normal();
    }

    graphics_reset_dialog();
    return 0;
}

void ui::message_dialog_base::draw_foreground_normal() {
    const lang_message& msg = lang_get_message(text_id);

    if (msg.type == TYPE_MANUAL && num_history > 0) {
        ui["button_close"].enabled = true;
        ui["button_close"].pos = {pos.x + 16, pos.y + 16 * msg.size.y - 36};
        lang_text_draw(12, 0, pos.x + 52, pos.y + 16 * msg.size.y - 31, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        ui["button_close"].enabled = false;
    }

    if (msg.type == TYPE_MESSAGE) {
        ui["button_advisor"].enabled = true;
        ui["button_advisor"].pos = {pos.x + 16, pos.y + 16 * msg.size.y - 40};
    } else {
        ui["button_advisor"].enabled = false;
    }
    
    ui["button_close"].enabled = true;
    ui["button_close"].pos = {pos.x + 16 * msg.size.x - 38, pos.y + 16 * msg.size.y - 36};
}

void ui::message_dialog_base::draw_foreground_image() {
    ui["button_advisor"].enabled = true;
    ui["button_advisor"].pos = {pos.x + 16, pos.y + 408};
    ui["button_close"].enabled = true;
    ui["button_close"].pos = {pos.x + 372, pos.y + 410};
}

void ui::message_dialog_base::draw_foreground_video() {
    video_draw(pos.x + 8, pos.y + 8);
    ui["button_advisor"].enabled = true;
    ui["button_advisor"].pos = {pos.x + 16, pos.y + 408};
    ui["button_close"].enabled = true;
    ui["button_close"].pos = {pos.x + 372, pos.y + 410};
}

bool ui::message_dialog_base::handle_input_normal(const mouse* m_dialog, const lang_message& msg) {
    if (msg.type == TYPE_MANUAL && num_history > 0) {
        vec2i btn_pos = {pos.x + 16, pos.y + 16 * msg.size.y - 36};
        if (m_dialog->left.went_down && 
            m_dialog->x >= btn_pos.x && m_dialog->x < btn_pos.x + 31 &&
            m_dialog->y >= btn_pos.y && m_dialog->y < btn_pos.y + 20) {
            button_back();
            return true;
        }
    }

    if (msg.type == TYPE_MESSAGE) {
        vec2i btn_pos = {pos.x + 16, pos.y + 16 * msg.size.y - 40};
        if (m_dialog->left.went_down && 
            m_dialog->x >= btn_pos.x && m_dialog->x < btn_pos.x + 27 &&
            m_dialog->y >= btn_pos.y && m_dialog->y < btn_pos.y + 27) {
            button_advisor(player_msg.message_advisor);
            return true;
        }
    }

    vec2i btn_pos = {pos.x + 16 * msg.size.x - 38, pos.y + 16 * msg.size.y - 36};
    if (m_dialog->left.went_down && 
        m_dialog->x >= btn_pos.x && m_dialog->x < btn_pos.x + 24 &&
        m_dialog->y >= btn_pos.y && m_dialog->y < btn_pos.y + 24) {
        button_close();
        return true;
    }

    // int text_id = rich_text.get_clicked_link(m_dialog);
    // if (text_id >= 0) {
    //     if (num_history < MAX_HISTORY - 1) {
    //         history[num_history].text_id = this->text_id;
    //         history[num_history].scroll_position = rich_text.scroll_position();
    //         num_history++;
    //     }
    //     this->text_id = text_id;
    //     rich_text.reset(0);
    //     return true;
    // }
    return false;
}

bool ui::message_dialog_base::handle_input_video(const mouse* m_dialog, const lang_message& msg) {
    vec2i btn_pos = {pos.x + 16, pos.y + 408};
    if (m_dialog->left.went_down && 
        m_dialog->x >= btn_pos.x && m_dialog->x < btn_pos.x + 27 &&
        m_dialog->y >= btn_pos.y && m_dialog->y < btn_pos.y + 27) {
        button_advisor(player_msg.message_advisor);
        return true;
    }

    btn_pos = {pos.x + 372, pos.y + 410};
    if (m_dialog->left.went_down && 
        m_dialog->x >= btn_pos.x && m_dialog->x < btn_pos.x + 24 &&
        m_dialog->y >= btn_pos.y && m_dialog->y < btn_pos.y + 24) {
        button_close();
        return true;
    }

    return false;
}

bool ui::message_dialog_base::handle_input_godmsg(const mouse* m_dialog, const lang_message& msg) {
    return handle_input_video(m_dialog, msg);
}

int ui::message_dialog_base::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    const mouse* m_dialog = mouse_in_dialog(m);
    const lang_message& msg = lang_get_message(text_id);
    
    bool handled = false;
    if (show_video) {
        handled = handle_input_video(m_dialog, msg);
    } else if (background) {
        handled = handle_input_godmsg(m_dialog, msg);
    } else {
        handled = handle_input_normal(m_dialog, msg);
    }

    if (!handled) {
        ui.begin_widget(pos);
        handled = ui::handle_mouse(m) != 0;
        ui.end_widget();
    }

    if (!handled && input_go_back_requested(m, h)) {
        button_close();
        return 1;
    }

    return handled ? 1 : 0;
}

int ui::message_dialog_base::handle_mouse(const mouse *m) {
    return 0;
}

void ui::message_dialog_base::cleanup() {
    if (show_video) {
        video_stop();
        show_video = false;
    }
    player_msg.message_advisor = 0;
}

void ui::message_dialog_base::button_back() {
    // if (num_history > 0) {
    //     num_history--;
    //     text_id = history[num_history].text_id;
    //     rich_text.reset(history[num_history].scroll_position);
    // }
}

void ui::message_dialog_base::button_close() {
    cleanup();
    window_go_back();
}

void ui::message_dialog_base::button_help() {
    button_close();
    if (!help_id.empty()) {
        g_message_dialog_instance->show(help_id, -1, background_callback);
    } else {
        g_message_dialog_instance->show("message_dialog_help", -1, background_callback);
    }
}

void ui::message_dialog_base::button_advisor(int advisor) {
    cleanup();
    if (!window_advisors_show_advisor((e_advisor)advisor))
        window_city_show();
}

void ui::message_dialog_base::show(xstring text_id, int message_id, void (*background_callback)(void)) {
    init_data(text_id, message_id, background_callback);
    
    static window_type instance = {
        WINDOW_MESSAGE_DIALOG,
        [] (int flags) { g_message_dialog_instance->draw_background(flags); },
        [] (int flags) { g_message_dialog_instance->draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_message_dialog_instance->ui_handle_mouse(m); }
    };

    window_show(&instance);
}

void ui::message_dialog_base::show_city_message(xstring text_id, int message_id, int year, int month, int param1, int param2, int message_advisor, bool use_popup) {
    set_city_message(year, month, param1, param2, message_advisor, use_popup);
    show(text_id, message_id, window_city_draw_all);
}

void ui::message_dialog_base::setup_help_id(xstring helpid) {
    help_id = helpid;
}

ui::message_dialog_general message_dialog_general_window;
ui::message_dialog_disaster message_dialog_disaster_window;
ui::message_dialog_imperial message_dialog_imperial_window;
ui::message_dialog_emigration message_dialog_emigration_window;
ui::message_dialog_tutorial message_dialog_tutorial_window;
ui::message_dialog_trade_change message_dialog_trade_change_window;
ui::message_dialog_price_change message_dialog_price_change_window;
ui::message_dialog_invasion message_dialog_invasion_window;

static ui::message_dialog_base* create_message_dialog(xstring text_id) {
    const lang_message& msg = lang_get_message(text_id);
    
    // Determine which class to create based on message type
    ui::message_dialog_base *window;

    switch (msg.message_type) {
        case MESSAGE_TYPE_GENERAL:
            window = &message_dialog_general_window;
            break;
        case MESSAGE_TYPE_DISASTER:
            window = &message_dialog_disaster_window;
            break;
        case MESSAGE_TYPE_IMPERIAL:
            window = &message_dialog_imperial_window;
            break;
        case MESSAGE_TYPE_EMIGRATION:
            window = &message_dialog_emigration_window;
            break;
        case MESSAGE_TYPE_TUTORIAL:
            window = &message_dialog_tutorial_window;
            break;
        case MESSAGE_TYPE_TRADE_CHANGE:
            window = &message_dialog_trade_change_window;
            break;
        case MESSAGE_TYPE_PRICE_CHANGE:
            window = &message_dialog_price_change_window;
            break;
        case MESSAGE_TYPE_INVASION:
            window = &message_dialog_invasion_window;
            break;
        default:
            window = &message_dialog_general_window;
            break;
    }

    return window;
}

void window_message_dialog_show(xstring text_id, int message_id, void (*background_callback)(void)) {
    if (g_message_dialog_instance) {
        delete g_message_dialog_instance;
    }
    g_message_dialog_instance = create_message_dialog(text_id);
    g_message_dialog_instance->show(text_id, message_id, background_callback);
}

void window_message_dialog_show_city_message(xstring text_id, int message_id, int year, int month, int param1, int param2, int message_advisor, bool use_popup) {
    if (g_message_dialog_instance) {
        delete g_message_dialog_instance;
    }
    g_message_dialog_instance = create_message_dialog(text_id);
    g_message_dialog_instance->show_city_message(text_id, message_id, year, month, param1, param2, message_advisor, use_popup);
}

void window_message_setup_help_id(xstring helpid) {
    if (!g_message_dialog_instance) {
        g_message_dialog_instance = &message_dialog_general_window;
    }
    g_message_dialog_instance->setup_help_id(helpid);
}

void window_show_help() {
    auto &data = g_window_manager;
    auto &current_window = data.window_queue[data.queue_index];
    if (g_message_dialog_instance && !g_message_dialog_instance->help_id.empty()) {
        window_message_dialog_show(g_message_dialog_instance->help_id.c_str(), -1, nullptr);
    }
}

// Derived class implementations
int ui::message_dialog_general::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_general::draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
    graphics_reset_dialog();
}








