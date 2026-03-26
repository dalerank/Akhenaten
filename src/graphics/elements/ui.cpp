#include "ui.h"

#include "button.h"
#include "core/string.h"
#include "generic_button.h"
#include "arrow_button.h"
#include "image_button.h"
#include "rich_text.h"
#include "lang_text.h"
#include "panel.h"
#include "graphics/text.h"
#include "core/svector.h"
#include "core/log.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/elements/tooltip.h"
#include "graphics/image.h"
#include "resource/icons.h"
#include "io/gamefiles/lang.h"
#include "core/crc32.h"
#include "js/js_game.h"
#include "js/js.h"
#include "ui_scope_property.h"
#include "graphics/elements/scroll_list_panel.h"
#include "game/game_pool.h"
#include "core/profiler.h"
#include "widget/input_box.h"
#include "core/encoding.h"
#include "input/mouse.h"
#include "graphics/screen.h"

#include <stack>

using namespace ui::opt;

namespace ui {

    const xstring element::ONCLICK{"onclick"};
    const xstring element::ONRCLICK{"onrclick"};
    const xstring element::TEXTFN{"textfn"};
    const xstring element::CHECKEDFN{"checkedfn"};
    const xstring element::ONINPUT{"oninput"};
    const xstring element::ONDRAW{"ondraw"};
    const xstring element::EMPTY_JS_REF{};

    tooltip_context tooltipctx;

    const tooltip_context &get_tooltip() {
        return tooltipctx;
    }

    void set_tooltip(const xstring &text) {
        tooltipctx.text = text;
    }

    struct universal_button {
        enum e_btn_type {
            unknown = -1,
            generic = 0,
            image,
            arrow
        };
        e_btn_type type = unknown;
        generic_button g_button;
        image_button i_button;
        arrow_button a_button;

        bool handle_mouse(const mouse *m, vec2i offset) {
            int tmp_btn;
            switch (type) {
            case generic: return !!generic_buttons_handle_mouse(m, offset, &g_button, 1, &tmp_btn, nullptr);
            case image: return !!image_buttons_handle_mouse(m, offset, &i_button, 1, &tmp_btn);
            case arrow: return !!arrow_buttons_handle_mouse(m, &a_button, 1, &tmp_btn);
            default:
                assert(false);
            }

            return false;
        }

        pcstr tooltip() const {
            switch (type) {
            case generic: return g_button._tooltip.c_str();
            case image: return i_button._tooltip.c_str();
            case arrow: return a_button._tooltip.c_str();
            default:
                assert(false);
            }

            return "";
        }

        vec2i pos() const {
            switch (type) {
            case generic: return { g_button.x, g_button.y };
            case image: return { i_button.x, i_button.y };
            case arrow: return { a_button.x, a_button.y };
            default:
                assert(false);
            }

            return {0, 0};
        }

        vec2i size() const {
            switch (type) {
            case generic: return g_button.size();
            case image: return { i_button.width, i_button.height };
            case arrow: return a_button.size();
            default:
                assert(false);
            }

            return {0, 0};
        }

        template<class Func> void onclick(Func f) {
            switch (type) {
            case generic: g_button.onclick(f); break;
            case image: i_button.onclick(f); break;
            case arrow: a_button.onclick(f); break;
            default:
                assert(false);
            }
        }

        universal_button() {}
        ~universal_button() {}

        universal_button(const universal_button &o) {
            type = o.type;
            switch (type) {
            case generic: g_button = o.g_button; break;
            case image: i_button = o.i_button; break;
            case arrow: a_button = o.a_button; break;
            default:
                assert(false);
            }
        }

        universal_button(const generic_button &b) {
            type = generic;
            g_button = b;
        }

        universal_button(const image_button &b) {
            type = image;
            i_button = b;
        }

        universal_button(const arrow_button &b) {
            type = arrow;
            a_button = b;
        }
    };

    struct state {
        std::stack<vec2i> _offset;
        hvector<universal_button, 32> buttons;
        hvector<scrollbar_t*, 4> scrollbars;
        hvector<scrollable_list*, 4> scrollable_lists;
        hvector<input_box*, 4> input_boxes;
        einput* active_input = nullptr;
        std::stack<widget*> current_widget_stack;

        void reset() {
            while (!_offset.empty()) {
                _offset.pop();
            };
            while (!current_widget_stack.empty()) {
                current_widget_stack.pop();
            }
            buttons.clear();
            scrollbars.clear();
            scrollable_lists.clear();
            input_boxes.clear();
        }

        void remove_scrolbar(scrollbar_t *p) {
            auto it = std::find(scrollbars.begin(), scrollbars.end(), p);
            if (it != scrollbars.end()) {
                scrollbars.erase(it);
            }
        }

        void remove_scrollable_list(scrollable_list* p) {
            auto it = std::find(scrollable_lists.begin(), scrollable_lists.end(), p);
            if (it != scrollable_lists.end()) {
                scrollable_lists.erase(it);
            }
        }

        inline const vec2i offset() { return _offset.empty() ? vec2i{0, 0} : _offset.top(); }
    };

    state g_state;
    generic_button dummy;
    element dummy_element;

    image_desc resource_icons;
    image_desc advisor_icons;

    hvector<cmd_t, 256> g_ui_commands;

    void push_cmd(cmd_t &&cmd) {
        g_ui_commands.push_back(std::move(cmd));
    }

    bool push_widget(widget* w) {
        if (get_current_widget() == w) {
            return false;
        }
        g_state.current_widget_stack.push(w);
        return true;
    }

    void pop_widget(bool pushed) {
        if (pushed) {
            g_state.current_widget_stack.pop();
        }
    }

    void execute_ui_command(painter &ctx, const cmd_t &cmd) {
        switch (cmd.type) {
        case cmd_t::image:
            ctx.img_generic(cmd.image_id, cmd.pos, cmd.mask, cmd.scale, cmd.img_flags);
            break;

        case cmd_t::fill_rect:
            ctx.fill_rect(cmd.pos, cmd.size, cmd.clr);
            break;

        case cmd_t::draw_rect:
            ctx.draw_rect(cmd.pos, cmd.size, cmd.clr);
            break;

        case cmd_t::h_line:
            graphics_draw_horizontal_line(cmd.pos, cmd.box_width, cmd.clr);
            break;

        case cmd_t::v_line:
            graphics_draw_vertical_line(cmd.pos, cmd.box_width, cmd.clr);
            break;

        case cmd_t::panel_outer:
            outer_panel_draw(cmd.pos, cmd.size.x, cmd.size.y);
            break;

        case cmd_t::panel_inner:
            inner_panel_draw(cmd.pos, cmd.size);
            break;

        case cmd_t::text:
            if (!!(cmd.flags & UiFlags_LabelMultiline)) {
                text_draw_multiline(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.font, 0);
            } else {
                lang_text_draw(cmd.str.c_str(), cmd.pos, cmd.font, cmd.box_width);
            }
            break;

        case cmd_t::text_centered:
            text_draw_centered(cmd.str.c_str(), cmd.pos.x, cmd.pos.y, cmd.box_width, cmd.font, cmd.clr);
            break;

        case cmd_t::text_multiline:
            text_draw_multiline(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.font, cmd.clr);
            break;

        case cmd_t::text_colored:
            if (cmd.box_width > 0) {
                text_draw_centered(cmd.str.c_str(), cmd.pos.x, cmd.pos.y, cmd.box_width, cmd.font, cmd.clr);
            } else if (text_cursor_capture_active()) {
                text_draw((const uint8_t*)cmd.str.c_str(), cmd.pos.x, cmd.pos.y + 3, cmd.font, cmd.clr);
            } else {
                lang_text_draw_colored(cmd.str.c_str(), cmd.pos.x, cmd.pos.y, cmd.font, cmd.clr);
            }
            break;

        case cmd_t::text_rich:
        {
            rich_text_t rich_text;
            rich_text.set_fonts(cmd.font, FONT_NORMAL_YELLOW);
            const bool centered = !!(cmd.flags & UiFlags_AlignCentered);
            rich_text.draw(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.size.y, false, centered);
            break;
        }

        case cmd_t::clip_set:
            graphics_set_clip_rectangle(cmd.pos, cmd.size);
            break;

        case cmd_t::clip_reset:
            graphics_reset_clip_rectangle();
            break;

        case cmd_t::button_border:
            button_border_draw(cmd.pos, cmd.size, cmd.img_flags != 0);
            break;

        case cmd_t::small_panel:
            small_panel_draw_colored(cmd.pos, cmd.box_width, cmd.image_id, cmd.mask);
            break;

        case cmd_t::shade_rect:
            graphics_shade_rect(cmd.pos, cmd.size, cmd.image_id);
            break;

        case cmd_t::large_label:
        {
            large_label_draw(cmd.pos.x, cmd.pos.y, cmd.box_width, cmd.image_id);
            const int letter_height = font_definition_for(cmd.font)->line_height;
            text_draw_centered((uint8_t *)cmd.str.c_str(), cmd.pos.x + 1, cmd.pos.y + (cmd.size.y - letter_height) / 2, cmd.size.x, cmd.font, 0);
            break;
        }

        case cmd_t::rich_draw:
            if (cmd.rt) {
                cmd.rt->draw(cmd.str.c_str(), cmd.pos, cmd.box_width, cmd.size.y, false);
                if (!(cmd.flags & UiFlags_NoScroll)) {
                    cmd.rt->draw_scrollbar(vec2i{ -16, 0 });
                }
            }
            break;

        case cmd_t::cursor_capture:
            text_capture_cursor(cmd.pos.x, cmd.pos.y, cmd.box_width);
            break;

        case cmd_t::cursor_consume:
            text_cursor_consume_capture();
            break;

        case cmd_t::cursor_insert: {
            const vec2i c = cmd.pos + vec2i{text_cursor_x_offset(), text_cursor_y_offset()};
            graphics_draw_horizontal_line(vec2i{c.x - 3, c.x + 1}, c.y - 3, COLOR_WHITE);
            graphics_draw_vertical_line(vec2i{c.x - 1, c.y - 3}, c.y + 13, COLOR_WHITE);
            graphics_draw_horizontal_line(vec2i{c.x - 3, c.x + 1}, c.y + 14, COLOR_WHITE);
            text_cursor_consume_capture();
            break;
        }
        case cmd_t::cursor_block: {
            const int w = cmd.box_width > 0 ? cmd.box_width : text_cursor_width();
            graphics_fill_rect(cmd.pos + vec2i{text_cursor_x_offset(), 14}, vec2i{w, 2}, COLOR_WHITE);
            text_cursor_consume_capture();
            break;
        }

        default:
            break;
        }
    }
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_ui_options) {
    g_config_arch.r_section("uioptions", [] (archive arch) {
        arch.r_desc("resource_icons", ui::resource_icons);
        arch.r_desc("advisor_icons", ui::advisor_icons);
    });
}

static ui::element::ptr create_element(const xstring type) {
    ui::element::ptr elm;
#define _ crc32_str
    switch (type.crc()) {
    case _("outer_panel"): elm = std::make_shared<ui::eouter_panel>(); break;
    case _("scrollbar"): elm = std::make_shared<ui::escrollbar>(); break;
    case _("scrollable_list"): elm = std::make_shared<ui::escrollable_list>(); break;
    case _("menu_header"): elm = std::make_shared<ui::emenu_header>(); break;
    case _("inner_panel"): elm = std::make_shared<ui::einner_panel>(); break;
    case _("background"):  elm = std::make_shared<ui::ebackground>(); break;
    case _("image"): elm = std::make_shared<ui::eimg>(); break;
    case _("label"): elm = std::make_shared<ui::elabel>(); break;
    case _("text"):  elm = ui::etext::acquire(); break;
    case _("generic_button"): elm = std::make_shared<ui::egeneric_button>(); break;
    case _("checkbox"): elm = std::make_shared<ui::echeckbox>(); break;
    case _("image_button"): elm = std::make_shared<ui::eimage_button>(); break;
    case _("resource_icon"): elm = std::make_shared<ui::eresource_icon>(); break;
    case _("arrow_button"): elm = std::make_shared<ui::earrow_button>(); break;
    case _("border"): elm = std::make_shared<ui::eborder>(); break;
    case _("input"): elm = std::make_shared<ui::einput>(); break;
    case _("large_button"):
        auto btn = std::make_shared<ui::egeneric_button>();
        btn->mode = 1;
        elm = btn;
    }

    return elm;
}

void ui_widget_load_elements(archive arch, pcstr section, ui::element *parent, ui::element::items &elements) {
    e_font default_font = arch.r_type<e_font>("default_font", FONT_INVALID);

    const int last_index = elements.size();
    arch.r_objects(section, [&elements, parent] (pcstr key, archive elem) {
        const xstring type = elem.r_string("type");
        ui::element::ptr elm = create_element(type);

        if (elm) {
            elm->id = key;
            elements.push_back(elm);
            elm->load(elem, parent, elements);
        }
    });

    if (default_font != FONT_INVALID) {
        for (size_t i = last_index; i < elements.size(); ++i) {
            if (elements[i]->font() == FONT_INVALID) {
                elements[i]->font(default_font);
            }
        }
    }
}

void ui::begin_widget(vec2i offset, bool relative) {
    if (relative) {
        vec2i top = g_state._offset.empty() ? vec2i{0, 0} : g_state._offset.top();
        offset += top;
    }
    g_state._offset.push(offset);
}

void ui::fill_rect(vec2i offset, vec2i size, color c) {
    const vec2i goffset = g_state.offset();
    push(cmd_t::fill_rect, Pos{goffset + offset}, Size{size}, TextColor{c});
}

void ui::draw_rect(vec2i pos, vec2i size, color c) {
    const vec2i goffset = g_state.offset();
    push(cmd_t::draw_rect, Pos{goffset + pos}, Size{size}, TextColor{c});
}

void ui::image_abs(int image_id, vec2i abs_pos) {
    push(cmd_t::image, Pos{abs_pos}, ImageId{image_id});
}

void ui::panel_abs(vec2i pos, vec2i size_blocks, UiFlags flags) {
    push(!!(flags & UiFlags_PanelInner) ? cmd_t::panel_inner : cmd_t::panel_outer, Pos{pos}, Size{size_blocks});
}

void ui::text_abs(pcstr str, vec2i pos, e_font font, color clr) {
    push(cmd_t::text_colored, Pos{pos}, Font{font}, TextColor{clr}, BoxWidth{0}, Caption{str});
}

void ui::text_multiline(pcstr text, vec2i pos, int width, e_font font, color clr) {
    const vec2i goffset = g_state.offset();
    push(cmd_t::text_multiline, Pos{goffset + pos}, BoxWidth{width}, Font{font}, TextColor{clr}, Caption{text});
}

vec2i ui::current_offset() {
    return g_state.offset();
}

void ui::begin_frame() {
    text_cursor_consume_capture();
    assert(g_state.buttons.size() < 1000);
    //assert(g_state._offset.size() == 0);
    g_state.reset();
    g_ui_commands.clear();
    tooltipctx.set(0, "");
}


void ui::end_frame() {

}

void ui::flush_commands() {
    painter ctx = game.painter();
    for (size_t i = 0; i < g_ui_commands.size(); ++i) {
        execute_ui_command(ctx, g_ui_commands[i]);
    }
    g_ui_commands.clear();
}

void ui::end_widget() {
    if (!g_state._offset.empty()) {
        g_state._offset.pop();
    }
}

ui::widget* ui::get_current_widget() {
    return g_state.current_widget_stack.empty() ? nullptr : g_state.current_widget_stack.top();
}

void ui::dispatch_autoconfig_es_event(widget* root, xstring sub_event, const bvariant_map& payload) {
    if (!root || !sub_event || !*sub_event) {
        return;
    }
    const xstring& sec = root->get_section();
    if (sec.empty()) {
        return;
    }
    xstring ev = js_helpers::es_hash_str<64>(sec, sub_event).c_str();
    root->event(ev, payload);
}

bool ui::handle_mouse(const mouse *m) {
    bool handle = false;
    for (int i = g_state.buttons.size() - 1; i >= 0 && !handle; --i) {
        handle |= !!g_state.buttons[i].handle_mouse(m, g_state.offset());
    }

    for (int i = g_state.scrollbars.size() - 1; i >= 0 && !handle; --i) {
        handle |= !!scrollbar_handle_mouse(g_state.scrollbars[i], m);
    }

    for (int i = g_state.scrollable_lists.size() - 1; i >= 0 && !handle; --i) {
        auto panel = g_state.scrollable_lists[i];
        handle |= !!panel->input_handle(m);
    }

    const mouse* m_dialog = mouse_in_dialog(m);
    for (int i = (int)g_state.input_boxes.size() - 1; i >= 0 && !handle; --i) {
        handle |= !!input_box_handle_mouse(m_dialog, g_state.input_boxes[i]);
    }

    return handle;
}

void ui::clear_active_elements() {
    g_state.buttons.clear();
    g_state.scrollbars.clear();
    // Underlying windows register scroll lists / inputs during draw; they must not
    // remain in the hit-test list for the window drawn on top (see window_draw_underlying_window).
    g_state.scrollable_lists.clear();
    g_state.input_boxes.clear();
    stop_active_input();
}

void ui::stop_active_input() {
    if (g_state.active_input) {
        g_state.active_input->stop_input();
        g_state.active_input = nullptr;
    }
}

pcstr ui::str(int group, int id) {
    return (pcstr)lang_get_string(group, id);
}

pcstr ui::str_from_key(pcstr key) {
    return lang_text_from_key(key);
}

pcstr ui::resource_name(e_resource r) {
    return (pcstr)lang_get_string(23, r);
}

int ui::button_hover(const mouse *m) {
    for (auto &btn : g_state.buttons) {
        if (is_button_hover(btn, g_state.offset())) {
            return (std::distance(&g_state.buttons.front(), &btn) + 1);
        }
    }

    return 0;
}

generic_button &ui::link(pcstr label, vec2i pos, vec2i size, e_font font, UiFlags flags, button_onclick_cb cb) {
    const vec2i offset = g_state.offset();

    g_state.buttons.push_back(generic_button{pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    auto &gbutton = g_state.buttons.back().g_button;
    int focused = is_button_hover(gbutton, offset);

    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y, size.x, focused ? FONT_NORMAL_YELLOW : font, 0);

    if (!!cb) {
        gbutton.onclick(cb);
    }
    return gbutton;
}

template<typename T>
void splitStringByNewline(const std::string &str, T &result) {
    size_t start = 0;
    size_t end = str.find('\n');

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find('\n', start);
    }

    result.push_back(str.substr(start));
}

generic_button &ui::button(pcstr label, vec2i pos, vec2i size, fonts_vec fonts, UiFlags flags, button_onclick_cb cb) {
    const bool darkened = !!(flags & UiFlags_Darkened);
    const bool hasbody = !(flags & UiFlags_NoBody);
    const bool hasborder = !(flags & UiFlags_NoBorder);
    const bool thinborder = !!(flags & UiFlags_ThinBorder);
    const bool splittext = !!(flags & UiFlags_SplitText);
    const bool alingxcenter = !!(flags & UiFlags_AlignXCentered);
    const bool alignleft = !!(flags & UiFlags_AlignLeft);
    const bool readonly = !!(flags & UiFlags_Readonly);
    const bool small_panel = !!(flags & UiFlags_PanelSmall);
    const bool selected = !!(flags & UiFlags_Selected);

    const vec2i offset = g_state.offset();

    g_state.buttons.push_back(generic_button{ pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0 });
    generic_button &gbutton = g_state.buttons.back().g_button;
    gbutton.hovered = (is_button_hover(gbutton, offset) || selected) && !readonly;
    gbutton.clip = graphics_clip_rectangle();

    if (small_panel) {
        push(cmd_t::small_panel, Pos{offset + pos}, BoxWidth{size.x / 16}, ImageId{gbutton.hovered ? 1 : 2}, Mask{darkened ? 0xffe0e0e0u : 0xffffffffu});
    } else if (hasbody) {
        if (thinborder) {
            push(cmd_t::draw_rect, Pos{offset + pos}, Size{size}, TextColor{0xff00000});
        } else {
            push(cmd_t::button_border, Pos{offset + pos}, Size{size}, ImgFlagsTag{((gbutton.hovered && !darkened) ? ImgFlag_Alpha : ImgFlag_None)});
        }
    } else if (hasborder) {
        if (gbutton.hovered && !darkened) {
            if (thinborder) {
                push(cmd_t::draw_rect, Pos{offset + pos}, Size{size}, TextColor{0xff000000});
            } else {
                push(cmd_t::button_border, Pos{offset + pos}, Size{size}, ImgFlagsTag{ ImgFlag_Alpha });
            }
        }
    }

    e_font font = fonts[gbutton.hovered ? 1 : 0];
    if (font == FONT_INVALID) {
        font = fonts[0];
    }

    const int symbolh = font_definition_for(font)->line_height;
    if (splittext) {
        svector<bstring128, 4> labels;
        string_to_array_t(labels, label, '\n');

        int labels_num = labels.size();
        int starty = offset.y + pos.y + (size.y - (symbolh + 2) * labels_num) / 2 + 4;

        for (const auto &str : labels) {
            push(alingxcenter ? cmd_t::text_centered : cmd_t::text, Font{font}, Caption{str.c_str()}, Pos{vec2i{offset.x + pos.x + (alingxcenter ? 1 : 8), starty}}, BoxWidth{alingxcenter ? size.x : 0});
            starty += symbolh + 2;
        }
    } else if (label) {
        const bool alingycenter = !!(flags & UiFlags_AlignYCentered);
        const bool rich = !!(flags & UiFlags_Rich);
        if (rich) {
            int symbolw = text_get_width("H", font);
            int lines_num = std::max<int>(1, (int)strlen(label) * symbolw / size.x);
            int centering_y_offset = (size.y - lines_num * symbolh) / 2;
            push(cmd_t::text_rich, Font{font}, Caption{label}, Pos{offset + pos + vec2i(0, centering_y_offset)}, BoxWidth{size.x}, Size{vec2i(0, lines_num)}, Flags{(UiFlags)UiFlags_AlignCentered});
        } else {
            const bool left_aligned = alingycenter || alignleft;
            vec2i txt_pos;
            int bw = 0;
            if (alingycenter) {
                txt_pos = { offset.x + pos.x + 8, offset.y + pos.y + (size.y - symbolh) / 2 + 2 };
            } else if (alignleft) {
                txt_pos = { offset.x + pos.x + 8, offset.y + pos.y + 8 };
            } else if (alingxcenter) {
                txt_pos = { offset.x + pos.x + 1, offset.y + pos.y + 4 };
                bw = size.x;
            } else {
                txt_pos = { offset.x + pos.x + 1, offset.y + pos.y + (size.y - symbolh) / 2 };
                bw = size.x;
            }
            push(left_aligned ? cmd_t::text : cmd_t::text_centered, Font{font}, Caption{label}, Pos{txt_pos}, BoxWidth{bw});
        }
    }

    if (darkened) {
        push(cmd_t::shade_rect, Pos{offset + pos}, Size{size}, ImageId{0x80});
    }

    if (!(darkened || readonly) && !!cb) {
        gbutton.onclick(cb);
    }
    return gbutton;
}

generic_button &ui::large_button(pcstr label, vec2i pos, vec2i size, e_font font) {
    const vec2i offset = g_state.offset();

    g_state.buttons.push_back(generic_button{pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    auto &gbutton = g_state.buttons.back().g_button;
    int focused = is_button_hover(gbutton, offset);

    push(cmd_t::large_label, Pos{offset + pos}, Size{size}, BoxWidth{size.x / 16}, ImageId{focused ? 1 : 0}, Font{font}, Caption{label});

    return gbutton;
}

generic_button &ui::button(uint32_t id) {
    return (id < g_state.buttons.size()) ? g_state.buttons[id].g_button : dummy;
}

pcstr ui::button_tooltip(uint32_t id) {
    return (id < g_state.buttons.size()) ? g_state.buttons[id].tooltip() : "";
}

image_button &ui::img_button(image_desc desc, vec2i pos, vec2i size, const img_button_offsets offsets, UiFlags flags) {
    const vec2i state_offset = g_state.offset();
    const mouse& m = mouse::get();

    g_state.buttons.push_back(image_button{pos.x, pos.y, size.x + 4, size.y + 4, IB_NORMAL, (uint32_t)desc.pack, (uint32_t)desc.id, offsets.data[0], button_none, button_none, 0, 0, true});
    auto &ibutton = g_state.buttons.back().i_button;

    const bool grayscaled = !!(flags & UiFlags_Grayscale);
    const bool darkened = !!(flags & UiFlags_Darkened);
    const bool force_pressed = !!(flags & UiFlags_Selected);
    ibutton.hovered = !(darkened || grayscaled) && is_button_hover(ibutton, state_offset);
    ibutton.pressed = (ibutton.hovered && m.left.is_down);
    ibutton.enabled = !(flags & UiFlags_Readonly);

    time_millis current_time = time_get_millis();
    if (ibutton.pressed) {
        if (current_time - ibutton.pressed_since > 100) {
            if (ibutton.button_type != IB_BUILD && ibutton.button_type != IB_OVERSEER && !mouse::get().left.is_down)
                ibutton.pressed = false;
        }
    }

    int image_id = image_id_from_group(ibutton.image_collection, ibutton.image_group) + ibutton.image_offset;
    if (image_id > 0) {
        if (ibutton.enabled) {
            const int offset = (ibutton.pressed || force_pressed) ? 2 :
                               ibutton.hovered ? 1 : 0;
            image_id += offset ? offsets.data[offset] : 0;
        } else {
            image_id += offsets.data[3];
        }

        push(cmd_t::image, Pos{state_offset + pos}, ImageId{image_id}, Mask{COLOR_WHITE}, Scale{1.0f}, ImgFlagsTag{grayscaled ? ImgFlag_Grayscale : ImgFlag_None});
    }

    return ibutton;
}

image_button &ui::imgok_button(vec2i pos, ui::button_onclick_cb cb) {
    auto &btn = img_button({ PACK_GENERAL, 96 }, pos, { 39, 26 });
    btn.onclick(cb);
    return btn;
}

image_button &ui::imgcancel_button(vec2i pos, ui::button_onclick_cb cb) {
    auto &btn = img_button({ PACK_GENERAL, 96 }, pos, { 39, 26 }, { 4, 1, 2, 3 });
    btn.onclick(cb);
    return btn;
}

int ui::label(int group, int number, vec2i pos, e_font font, UiFlags flags, int box_width) {
    pcstr str = (pcstr)lang_get_string(group, number);
    return label(str, pos, font, flags, box_width);
}

int ui::label(pcstr label, vec2i pos, e_font font, UiFlags flags, int box_width) {
    const vec2i offset = g_state.offset();
    if (!!(flags & UiFlags_AlignCentered)) {
        push(cmd_t::text_centered, Pos{offset + pos}, Font{font}, Flags{flags}, BoxWidth{box_width}, Caption{label ? label : ""});
        return box_width;
    } else if (!!(flags & UiFlags_LabelMultiline)) {
        // keep immediate: returns line count, complex to measure ahead of time
        return text_draw_multiline(label, offset + pos, box_width, font, 0);
    } else if (!!(flags & UiFlags_Rich)) {
        rich_text_t rich_text;
        rich_text.set_fonts(font, FONT_NORMAL_YELLOW);
        const int measured = rich_text.draw(label, offset + pos, box_width, 10, /*measure_only*/true);
        push(cmd_t::text_rich, Pos{offset + pos}, Font{font}, BoxWidth{box_width}, Size{vec2i(0, 10)}, Caption{label ? label : ""});
        return measured;
    } else {
        push(cmd_t::text, Pos{offset + pos}, Font{font}, Flags{flags}, BoxWidth{box_width}, Caption{label ? label : ""});
        return text_get_width(label, font);
    }
}

int ui::label_amount(int group, int number, int amount, vec2i pos, e_font font, pcstr postfix) {
    const vec2i offset = g_state.offset();
    return lang_text_draw_amount(group, number, amount, offset.x + pos.x, offset.y + pos.y, font, postfix);
}

int ui::label_percent(int amount, vec2i pos, e_font font) {
    const vec2i offset = g_state.offset();
    return text_draw_percentage(amount, offset.x + pos.x, offset.y + pos.y, font);
}

int ui::label_colored(textid tx, vec2i pos, e_font font, color color, int box_width) {
    const vec2i offset = g_state.offset();
    pcstr str = lang_get_string(tx);
    push(cmd_t::text_colored, Pos{offset + pos}, Font{font}, TextColor{color}, BoxWidth{box_width}, Caption{str ? str : ""});
    return box_width > 0 ? box_width : text_get_width(str, font);
}

int ui::label_colored(pcstr tx, vec2i pos, e_font font, color color, int box_width) {
    const vec2i offset = g_state.offset();
    push(cmd_t::text_colored, Pos{offset + pos}, Font{font}, TextColor{color}, BoxWidth{box_width}, Caption{tx ? tx : ""});
    return box_width > 0 ? box_width : text_get_width(tx, font);
}

const image_t *ui::eimage(int imgid, vec2i pos) {
    const vec2i offset = g_state.offset();
    push(cmd_t::image, Pos{pos + offset}, ImageId{imgid});
    return image_get(imgid);
}

const image_t *ui::eimage(image_desc imgd, vec2i pos) {
    const vec2i offset = g_state.offset();
    const int tid = imgd.tid();
    push(cmd_t::image, Pos{pos + offset}, ImageId{tid});
    return image_get(tid);
}

void ui::panel(vec2i pos, vec2i size, UiFlags flags) {
    const vec2i offset = g_state.offset();
    if (!!(flags & UiFlags_PanelOuter)) {
        push(cmd_t::panel_outer, Pos{offset + pos}, Size{size});
    } else if (!!(flags & UiFlags_PanelInner)) {
        push(cmd_t::panel_inner, Pos{offset + pos}, Size{size});
    }
}

void ui::button_border(vec2i pos, vec2i size, bool focused) {
    const vec2i offset = g_state.offset();
    push(cmd_t::button_border, Pos{offset + pos}, Size{size}, ImgFlagsTag{focused ? ImgFlag_Alpha : ImgFlag_None});
}

void ui::line(bool hline, vec2i npos, int size, color c) {
    const vec2i offset = g_state.offset();
    push(hline ? cmd_t::h_line : cmd_t::v_line, Pos{npos + offset}, BoxWidth{size}, TextColor{c});
}

void ui::border(vec2i pos, vec2i size, int type, color c, UiFlags flags) {
    const vec2i offset = g_state.offset();
    push(cmd_t::draw_rect, Pos{offset + pos}, Size{size}, TextColor{c});
}

void ui::rect(vec2i pos, vec2i size, int fill, int color, UiFlags flags) {
    const vec2i offset = g_state.offset();
    if (fill) {
        ui::fill_rect(offset + pos, size, fill);
    } else {
        graphics_draw_rect(offset + pos, size, color);
    }
}

void ui::cursor_capture(int cursor_position, int offset_start, int offset_end) {
    push(cmd_t::cursor_capture, Pos{vec2i{cursor_position, offset_start}}, BoxWidth{offset_end});
}

void ui::cursor_consume() {
    push_cmd(cmd_t(cmd_t::cursor_consume));
}

void ui::draw_cursor_insert(vec2i screen_pos) {
    push(cmd_t::cursor_insert, Pos{screen_pos});
}

void ui::draw_cursor_block(vec2i screen_pos, int width) {
    push(cmd_t::cursor_block, Pos{screen_pos}, BoxWidth{width});
}

void ui::icon(vec2i pos, e_resource res, UiFlags flags) {
    const vec2i offset = g_state.offset();
    const int image_id = image_id_resource_icon(res);
    push(cmd_t::image, Pos{offset + pos}, ImageId{image_id});
    if (!!(flags & UiFlags_Outline)) {
        const image_t *img = image_get(image_id);
        ui::draw_rect(pos - vec2i{1, 1}, vec2i{img->width, img->height} + vec2i{2, 2}, COLOR_BLACK);
    }
}

void ui::icon(vec2i pos, e_advisor adv) {
    const vec2i offset = g_state.offset();
    push(cmd_t::image, Pos{offset + pos}, ImageId{advisor_icons.tid() + (adv - 1)});
}

arrow_button &ui::arw_button(vec2i pos, bool down, bool tiny, UiFlags_ flags) {
    const vec2i offset = g_state.offset();
    const mouse& m = mouse::get();

    int size = tiny ? 17 : 24;
    g_state.buttons.push_back(arrow_button{offset.x + pos.x, offset.y + pos.y, -1, size, button_none, 0, 0});
    auto &abutton = g_state.buttons.back().a_button;

    const bool hovered = !(flags & UiFlags_Darkened) && (is_button_hover(abutton, {0, 0}) || !!(flags & UiFlags_Selected));
    abutton.pressed = hovered && m.left.is_down;
    abutton.state = (hovered ? (abutton.pressed ? 2 : 1) : 0);
    abutton.state |= (down ? 0x10 : 0);

    arrow_buttons_draw(abutton, tiny);
    const bool darkened = !!(flags & UiFlags_Darkened);

    if (darkened) {
        graphics_shade_rect(pos, vec2i{ size, size }, 0x80);
    }

    return abutton;
}

scrollbar_t &ui::scrollbar(scrollbar_t &scr, vec2i pos, int &value, vec2i size) {
    const vec2i offset = g_state.offset();

    g_state.scrollbars.push_back(&scr);
    scrollbar_draw(offset, &scr);

    return scr;
}

xstring ui_element_props[] = { "text", "enabled", "readonly", "font", "text_color", "image", "selected", "tooltip", "onclick", "textfn", "ondraw" };
xspan<xstring> ui::element::prop_names() const {
    return make_span(ui_element_props);
}

ui::element::~element() {
    for (auto &kv : _js_refs) {
        if (!kv.second.empty()) {
            js_unref_function(kv.second);
        }
    }
    _js_refs.clear();
}

void ui::element::invoke_draw_callbacks(UiFlags flags) {
    const xstring& js = js_ref(ONDRAW);
    if (!js.empty()) {
        const vec2i sp = screen_pos();
        const vec2i psz = pxsize();
        bvariant_map::scoped m;
        (*m)["x"] = (int32_t)sp.x;
        (*m)["y"] = (int32_t)sp.y;
        (*m)["sizex"] = (int32_t)psz.x;
        (*m)["sizey"] = (int32_t)psz.y;
        (*m)["flags"] = (int32_t)flags;
        (*m)["id"] = bvariant(id.c_str());
        js_call_function(js, *m);
    } else if (_draw_callback) {
        _draw_callback(this, flags);
    }
}

void ui::element::set_ref(const xstring &key, const xstring &ref) {
    auto it = _js_refs.find(key);
    xstring old;
    if (it != _js_refs.end()) {
        old = it->second;
    }
    if (ref == old) {
        return;
    }
    if (!old.empty()) {
        js_unref_function(old);
    }
    if (ref.empty()) {
        if (it != _js_refs.end()) {
            _js_refs.erase(it);
        }
    } else if (it != _js_refs.end()) {
        it->second = ref;
    } else {
        _js_refs.insert({key, ref});
    }
}

const xstring &ui::element::js_ref(const xstring &key) const {
    auto it = _js_refs.find(key);
    if (it == _js_refs.end()) {
        return EMPTY_JS_REF;
    }
    return it->second;
}

void ui::element::load(archive arch, element *parent, element::items &items) {
    debug_tag = arch.r_int("debug_tag");
    parent_id = parent ? parent->id : xstring();
    pos = arch.r_vec2i("pos");
    size = arch.r_size2i("size");
    enabled = arch.r_bool("enabled", true);
    fill_width = arch.r_bool("fill_width", false);
    fill_height = arch.r_bool("fill_height", false);

    arch.r_section("margin", [this] (archive m) {
        margin.bottom = m.r_int("bottom", margini::nomargin);
        margin.left = m.r_int("left", margini::nomargin);
        margin.right = m.r_int("right", margini::nomargin);
        margin.top = m.r_int("top", margini::nomargin);
        margin.centerx = m.r_int("centerx", margini::nomargin);
        margin.centery = m.r_int("centery", margini::nomargin);
        int i = 0;
    });

    ui_widget_load_elements(arch, "ui", this, items);
}

pcstr ui::element::text_from_key(pcstr key) {
    return lang_text_from_key(key);
}

void ui::element::update_pos(const margini &r) {
    if (margin.left > margini::nomargin) { pos.x = r.left + margin.left; }
    if (margin.bottom > margini::nomargin) { pos.y = r.bottom + margin.bottom; }
    if (margin.right > margini::nomargin) { pos.x = r.right + margin.right; }
    if (margin.top > margini::nomargin) { pos.y = r.top + margin.top; }
    if (margin.centerx > margini::nomargin) { pos.x = (r.right - r.left) / 2 + margin.centerx; }
    if (margin.centery > margini::nomargin) { pos.y = (r.bottom - r.top) / 2 + margin.centery; }
}

vec2i ui::element::screen_pos() const {
    const vec2i offset = g_state.offset();
    return offset + pos;
}

void ui::eouter_panel::draw(UiFlags flags) {
    ui::panel(pos, size, UiFlags_PanelOuter);
}

void ui::eouter_panel::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "outer_panel"));
}

void ui::einner_panel::draw(UiFlags flags) {
    ui::panel(pos, size, UiFlags_PanelInner);
}

void ui::einner_panel::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "inner_panel"));
}

void ui::widget::draw(UiFlags flags) {
    vec2i bsize = ui["background"].pxsize();
    for (auto &e : elements) {
        if (!e->enabled) {
            continue;
        }

        margini current_margin{ 0, 0, bsize.x, bsize.y };
        vec2i poffset = { 0, 0 };
        bool use_poffset = false;
        if (!e->parent_id.empty()) {
            const auto &parent = ui[e->parent_id];
            const vec2i ebsize = parent.pxsize();
            const vec2i top_offset = g_state._offset.empty() ? vec2i{ 0, 0 } : g_state._offset.top();
            poffset = top_offset + parent.pos;
            use_poffset = true;
            current_margin = { 0, 0, ebsize.x, ebsize.y };
        }

        e->update_pos(current_margin);
        if (use_poffset) {
            g_state._offset.push(poffset);
        }

        e->draw(flags);   

        if (use_poffset) {
            g_state._offset.pop();
        }
    }
}

void ui::widget::archive_load(archive arch) {
    elements.clear();
    pos = arch.r_vec2i("pos");
    e_font default_font = arch.r_type<e_font>("default_font", FONT_NORMAL_BLACK_ON_LIGHT);

    ui_widget_load_elements(arch, "ui", nullptr, elements);

    for (auto &e:  elements) {
        if (e->font() == FONT_INVALID) {
            e->font(default_font);
        }
    }
}

void ui::widget::load(xstring section) {
    io.name = section;
    g_config_arch.r(section.c_str(), *this);
}

bool ui::widget::contains(const xstring &id) const {
    auto it = std::find_if(elements.begin(), elements.end(), [xid = xstring(id)] (const auto &e) { return e->id == xid; });
    return (it != elements.end());
}

ui::element& ui::widget::operator[](const xstring& id) {
    auto it = std::find_if(elements.begin(), elements.end(), [xid = id] (const auto &e) { return e->id == xid; });
    if (check_errors && it == elements.end()) {
        logs::error("No element with id:%s", id.c_str());
    }
    return (it != elements.end() ? **it : ui::dummy_element);
}

void ui::widget::event(xstring evname, const bvariant_map &js_j) {
    OZZY_PROFILER_SECTION(_, evname.c_str())

    const bool pushed_current_layer = push_widget(this);

    bvariant_map::scoped enhanced_js_j_scoped;
    bvariant_map &enhanced_js_j = *enhanced_js_j_scoped;

    {
        OZZY_PROFILER_SECTION(_, "prepare table")
        enhanced_js_j = js_j;
        for (const auto &elem : elements) {
            if (!elem->id.empty()) {
                bstring64 elmid("__ui_elem_", elem->id.c_str());
                bstring64 elmkey("__ui_elem:", elem->id.c_str());
                enhanced_js_j[elmid.c_str()] = bvariant(elmkey.c_str());
            }
        }
    }
    js_call_event_handlers(evname, enhanced_js_j);

    pop_widget(pushed_current_layer);
}

void ui::widget::begin_widget(vec2i offset, bool relative) {
    OZZY_PROFILER_FUNCTION();

    check_errors = true;
    g_state.current_widget_stack.push(this);
    ui::begin_widget(offset, relative);
}

void ui::widget::end_widget() {
    ui::end_widget();
    if (!g_state.current_widget_stack.empty()) {
        g_state.current_widget_stack.pop();
    }
}

void ui::widget::set_clip_rectangle(vec2i pos, vec2i size) {
    const vec2i offset = g_state.offset();
    graphics_set_clip_rectangle(pos + offset, size);
}

void ui::widget::set_clip_rectangle(const element &e) {
    const vec2i offset = g_state.offset();
    graphics_set_clip_rectangle(e.pos + offset, e.pxsize());
}

void ui::widget::reset_clip_rectangle() {
    graphics_reset_clip_rectangle();
}

void ui::widget::line(bool hline, vec2i npos, int size, color c) {
    const vec2i offset = g_state.offset();
    if (hline) {
        graphics_draw_horizontal_line(npos + offset, size, c);
    } else {
        graphics_draw_vertical_line(npos + offset, size, c);
    }
}

void ui::eimg::draw(UiFlags flags) {
    if (isometric) {
        const vec2i offset = g_state.offset();
        painter ctx = game.painter();
        ctx.img_isometric(img_desc.tid(), offset + pos, COLOR_MASK_NONE);
    } else {
        vec2i rpos = pos;
        if (centering.x > -1000 || centering.y > -1000) {
            const image_t *img = image_get(img_desc);
            if (img) {
                const vec2i psize = pxsize();  
                rpos.x += (centering.x > -1000) ? ((psize.x - img->width) / 2 + centering.x) : 0;
                rpos.y += (centering.y > -1000) ? ((psize.y - img->height) / 2 + centering.y) : 0;
            }
        }
        ui::eimage(img_desc, rpos);
    }
}

void ui::eimg::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "image"));
    img_desc.pack = arch.r_int("pack");
    img_desc.id = arch.r_int("id");
    img_desc.offset = arch.r_int("offset");
    isometric = arch.r_bool("isometric");
    centering = arch.r_vec2i("centering", { -1001, -1001 });
}

void ui::eimg::image(const image_desc& image) {
    img_desc = image;
}

void ui::eimg::image(const animation_t& anim) {
    img_desc = anim.to_desc();
}

void ui::eimg::image(int image) {
    img_desc.offset = image;
}

void ui::ebackground::draw(UiFlags flags) {
    painter ctx = game.painter();
    ImageDraw::img_background(ctx, img_desc.tid(), 1.f, pos);
}

void ui::ebackground::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "background"));
    scale = arch.r_float("scale", 1.f);
    img_desc.pack = arch.r_int("pack");
    img_desc.id = arch.r_int("id");
    img_desc.offset = arch.r_int("offset");
    img_desc.path = arch.r_string("path");
}

void ui::eborder::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    border = arch.r_int("border");
    colori = arch.r_int("color");
}

void ui::eborder::draw(UiFlags flags) {
    const vec2i offset = g_state.offset();
    switch (border) {
    default: //fallthrought
    case 0:
        button_border_draw(offset + pos, size, false);
        break;

    case 1:
        graphics_draw_rect(offset + pos, size, colori);
        break;
    }
}

static xstring ui_einput_value_props[] = { "value" };
xspan<xstring> ui::einput::prop_names() const {
    return make_span(ui_einput_value_props);
}

void ui::einput::stop_input() {
    if (_started) {
        input_box_stop(&_box);
        _started = false;
    }
    if (g_state.active_input == this) {
        g_state.active_input = nullptr;
    }
}

void ui::einput::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);
    _box.font = (e_font)arch.r_type<e_font>("font", FONT_NORMAL_WHITE_ON_DARK);
    if (size.x <= 0) { size.x = 20; }
    if (size.y <= 0) { size.y = 2; }
    _box.width_blocks = size.x;
    _box.height_blocks = size.y;
    _box.max_length = arch.r_int("max_length", MAX_PLAYER_NAME - 1);
    _allow_punctuation = arch.r_int("allow_punctuation", 1);
    set_ref(ONINPUT, arch.r_function("oninput"));
}

void ui::einput::draw(UiFlags flags) {
    const vec2i offset = g_state.offset();
    const vec2i screen_pos = offset + pos;
    _box.x = screen_pos.x - screen_dialog_offset_x();
    _box.y = screen_pos.y - screen_dialog_offset_y();
    _box.text = _buffer;
    if (!_started) {
        input_box_start(&_box, _buffer, _box.max_length, _allow_punctuation);
        _started = true;
        g_state.active_input = this;
        memcpy(_last_buffer, _buffer, sizeof(_buffer));
    }

    g_state.input_boxes.push_back(&_box);
    input_box_draw(&_box);

    if (!js_ref(ONINPUT).empty() && memcmp(_buffer, _last_buffer, sizeof(_buffer)) != 0) {
        memcpy(_last_buffer, _buffer, sizeof(_buffer));
        xstring value(get_value());
        js_call_function(js_ref(ONINPUT), bvariant_map{{ "value", bvariant_map_val(value.c_str()) }});
    }
}

pcstr ui::einput::get_value() const {
    static char utf8_buf[MAX_PLAYER_NAME * 4];
    encoding_to_utf8(_buffer, utf8_buf, (int)sizeof(utf8_buf), encoding_system_uses_decomposed());
    return utf8_buf;
}

void ui::einput::set_value(pcstr utf8) {
    encoding_from_utf8(utf8 ? utf8 : "", _buffer, MAX_PLAYER_NAME);
    if (_started) {
        input_box_refresh_text(&_box);
        memcpy(_last_buffer, _buffer, sizeof(_last_buffer));
    }
}

void ui::eresource_icon::draw(UiFlags flags) {
    ui::eimage(resource_icons + res, pos);
}

int image_id_resource_icon(int resource) {
    return ui::resource_icons.tid() + resource;
}

void ui::eresource_icon::image(int image) {
    res = (e_resource)image;
}

void ui::eresource_icon::text(pcstr v) {
    if (v && *v) {
        res = resource_type(v);
    }
}

void ui::eresource_icon::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "resource_icon"));
    res = arch.r_type<e_resource>("resource");
    prop = arch.r_string("prop");
}

void ui::elabel::draw(UiFlags flags) {
    const vec2i offset = g_state.offset();

    if (!js_ref(TEXTFN).empty()) {
        bvariant dyn = js_call_function(js_ref(TEXTFN), 0, 0);
        ui_scope_property holder;
        _text = ui::sformat<1024>(&holder, dyn.to_str().c_str());
    }

    if (_body.x > 0) {
        push(cmd_t::small_panel, Pos{offset + pos}, BoxWidth{_body.x}, ImageId{_body.y}, Mask{0xffffffffu});
    }

    auto dpos = pos + ((_body.x > 0) ? vec2i{ 8, 4 } : vec2i{ 0, 0 });
    auto box_width = size.x;
    const vec2i text_pos = offset + dpos;

    if (!!(_flags & UiFlags_AlignCentered)) {
        push(cmd_t::text_centered, Pos{text_pos}, BoxWidth{box_width}, Font{_font}, Caption{_text.c_str()});
    } else if (!!(_flags & UiFlags_LabelMultiline)) {
        push(cmd_t::text_multiline, Pos{text_pos}, BoxWidth{box_width}, Font{_font}, Caption{_text.c_str()});
    } else if (!!(_flags & UiFlags_Rich)) {
        rich_text_t rich_text;
        rich_text.set_fonts(_font, FONT_NORMAL_YELLOW);
        rich_text.set_margin(_text_margin);
        rich_text.draw(_text.c_str(), offset, box_width, 10, false);
    } else {
        push(cmd_t::text, Pos{text_pos}, BoxWidth{box_width}, Font{_font}, Caption{_text.c_str()});
    }

    invoke_draw_callbacks(flags);
}

void ui::elabel::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    _text = arch.r_string("text");
    set_ref(TEXTFN, arch.r_function("textfn"));
    set_ref(ONDRAW, arch.r_function("ondraw"));
    if (_text[0] == '#') {
        _text = lang_text_from_key(_text.c_str());
    }

    if (!_text.empty() && strchr(_text.c_str(), '{')) {
        _format = _text.c_str();
    }
    _font = arch.r_type<e_font>("font", FONT_INVALID);
    _font_link = arch.r_type<e_font>("font_link", FONT_NORMAL_YELLOW);
    _font_hover = arch.r_type< e_font>("font_hover", FONT_INVALID);
    _body = arch.r_size2i("body");
    _color = arch.r_uint("color");
    _wrap = arch.r_int("wrap");
    _clip_area = arch.r_bool("clip_area");
    _shadow_color = arch.r_uint("shadow");
    _tooltip = arch.r_string("tooltip");
    arch.r("text_margin", _text_margin);

    pcstr talign = arch.r_string("align");
    bool multiline = arch.r_bool("multiline");
    bool rich = arch.r_bool("rich");
    bool scroll = arch.r_bool("scroll", true);
    bool aligncenter = strcmp("center", talign) == 0;
    bool alignleft = strcmp("left", talign) == 0;
    bool alignycenter = strcmp("ycenter", talign) == 0;
    bool alignxcenter = strcmp("xcenter", talign) == 0;
    _flags = (aligncenter ? UiFlags_AlignCentered : UiFlags_None)
               | (alignycenter ? UiFlags_AlignYCentered : UiFlags_None)
               | (alignxcenter ? UiFlags_AlignXCentered : UiFlags_None)
               | (alignleft ? UiFlags_AlignLeft : UiFlags_None)
               | (multiline ? UiFlags_LabelMultiline : UiFlags_None)
               | (rich ? UiFlags_Rich : UiFlags_None)
               | (scroll ? UiFlags_None : UiFlags_NoScroll);
}

void ui::elabel::text(pcstr v) {
    _text = lang_text_from_key(v);
}

void ui::elabel::text_color(color v) {
    _color = v;
}

void ui::elabel::font(int v) {
    _font = (e_font)v;
}

void ui::elabel::width(int v) {
    size.x = v;
    _wrap = v;
}

void ui::eimage_button::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "image_button"));

    scale = arch.r_float("scale", 1.f);
    param1 = arch.r_int("param1");
    param2 = arch.r_int("param2");
    img_desc.pack = arch.r_int("pack");
    img_desc.id = arch.r_int("id");
    img_desc.offset = arch.r_int("offset");
    border = arch.r_int("border");
    offsets.data[0] = img_desc.offset;
    offsets.data[1] = arch.r_int("offset_focused", 1);
    offsets.data[2] = arch.r_int("offset_pressed", 2);
    offsets.data[3] = arch.r_int("offset_disabled", 3);
    _tooltip = arch.r_string("tooltip");
    set_ref(ONCLICK, arch.r_function("onclick"));
    _onclick_event = arch.r_string("onclick_event");

    pcstr name_icon_texture = arch.r_string("icon_texture");
    if (name_icon_texture && *name_icon_texture) {
        vec2i tmp_size;
        icon_texture = load_icon_texture(name_icon_texture, tmp_size);
    }
}

void ui::eimage_button::draw(UiFlags gflags) {
    const vec2i doffset = g_state.offset();
    UiFlags flags = gflags | (_selected ? UiFlags_Selected : UiFlags_None);
    flags |= (readonly ? UiFlags_Readonly : UiFlags_None);
    flags |= (!!(darkened & UiFlags_Grayscale) ? UiFlags_Grayscale : UiFlags_None);

    image_button *btn = nullptr;
    pcstr pid = id.c_str();

    vec2i tsize;
    if (img_desc.id || img_desc.offset) {
        int img_id = image_id_from_group(img_desc.pack, img_desc.id);
        const image_t *img_ptr = image_get(img_id + img_desc.offset);

        tsize.x = size.x > 0 ? size.x : img_ptr->width;
        tsize.y = size.y > 0 ? size.y : img_ptr->height;

        btn = &ui::img_button(img_desc, pos, tsize, offsets, flags);
    } else if (texture_id > 0) {
        graphics_draw_from_texture(texture_id, doffset + pos, size);
        tsize = size;
        btn = &ui::img_button({ 0, 0 }, pos, size, offsets, flags);
    } else if (icon_texture) {
        painter ctx = game.painter();
        ctx.draw((SDL_Texture*)icon_texture, pos, {0, 0}, size, 0xffffffff, scale, scale, 0, ImgFlag_Alpha);
        btn = &ui::img_button({ 0, 0 }, pos, size, offsets, UiFlags_None);
    }

    if (!btn) {
        return;
    }

    if (_selected) {
        switch (border) {
        case 1:
            button_border_draw(doffset + pos - vec2i{ 4, 4 }, tsize + vec2i{ 8, 8 }, true);
            break;

        case 2:
            graphics_draw_rect(pos, size, 0xff000000);
            break;
        }
    }

    if (!!(darkened & UiFlags_Darkened)) {
        graphics_shade_rect(doffset + pos, tsize, 0x80);
        return;
    }

    if (!!(darkened & UiFlags_Grayscale)) {
        return;
    }

    if (readonly) {
        return;
    }

    if (!_onclick_event.empty()) {
        btn->onclick([this](int, int) {
            bvariant_map::scoped s;
            dispatch_autoconfig_es_event(get_current_widget(), _onclick_event, *s);
        });
    } else if (!js_ref(ONCLICK).empty()) {
        const xstring js_onclick = js_ref(ONCLICK);
        btn->onclick([js_ref = js_onclick](int, int) {
            js_call_function(js_ref);
        });
    } else {
        if (_func) btn->onclick(_func);
        if (_sfunc) btn->onclick(_sfunc);
        if (_rfunc) btn->onrclick(_rfunc);
        if (_srfunc) btn->onrclick(_srfunc);
    }

    btn->tooltip(_tooltip);
    btn->parameter1 = param1;
    btn->parameter2 = param2;

    if (!_tooltip.empty() && btn->hovered) {
        tooltipctx.set(0, _tooltip);
    }
}

void ui::eimage_button::image(const animation_t &d) {
    img_desc = d.to_desc();
}

void ui::etext::load(archive arch, element* parent, items &elems) {
    elabel::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "text"));
}

void ui::etext::reset_scroll() {
    if (rich_text) {
        rich_text->reset(0);
    }
}

void ui::escrollbar::draw(UiFlags flags) {
    ui::scrollbar(this->scrollbar, pos, this->scrollbar.scroll_position);
}

void ui::escrollbar::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "scrollbar"));

    scrollbar.pos = pos;
    scrollbar.height = size.y;
}

void ui::escrollable_list::clear() {
    if (!panel) {
        return;
    }

    panel->clear_entry_list();
}

void ui::escrollable_list::on_dblclick_item(const scrollable_list::entry_data *entry) {
    if (!entry) {
        return;
    }
    if (!_ondoubleclick_event.empty()) {
        bvariant_map::scoped m;
        (*m)["text"] = bvariant(entry->text);
        dispatch_autoconfig_es_event(get_current_widget(), _ondoubleclick_event.c_str(), *m);
        return;
    }
    if (!_js_ondoubleclick_item_ref.empty()) {
        js_call_function(_js_ondoubleclick_item_ref, { { "text", entry->text } });
    }
}

void ui::escrollable_list::on_render_item(int index, int flags, const scrollable_list::entry_data &entry, vec2i pos, e_font font) {
    if (!_js_render_item_ref.empty()) {
        ensure_panel();
        const scrollable_list_ui_params &up = panel->ui_params;
        js_call_function(_js_render_item_ref, {
            { "index", (int32_t)index },
            { "flags", (int32_t)flags },
            { "hover", (flags & 2) != 0 },
            { "select", (flags & 1) != 0 },
            { "text", entry.text },
            { "x", (int32_t)pos.x },
            { "y", (int32_t)pos.y },
            { "sizex", (int32_t)up.buttons_size_x },
            { "sizey", (int32_t)up.buttons_size_y },
            { "font", (int32_t)font }
            });
        return;
    }

    if (_custom_render_cb) {
        _custom_render_cb(index, flags, entry, pos, font);
    }
}

void ui::escrollable_list::ensure_panel() {
    if (panel) {
        return;
    }

    panel = std::make_unique<scrollable_list>(button_none, button_none, button_none, button_none, params);
    refill();

    panel->set_onclick_entry(_onclick_cb);
    if (_custom_render_cb || !_js_render_item_ref.empty()) {
        panel->set_custom_render_func([&](int index, int flags, const scrollable_list::entry_data &entry, vec2i pos, e_font font) { 
            this->on_render_item(index, flags, entry, pos, font);
        });
    }

    if (_ondoubleclick_item_cb || !_js_ondoubleclick_item_ref.empty() || !_ondoubleclick_event.empty()) {
        panel->set_onclick_dbl_entry([&] (const scrollable_list::entry_data *entry) {
            this->on_dblclick_item(entry);
        });
    }

    if (_onclick_ex_cb || !_js_onclick_item_ref.empty() || !_onclick_event.empty()) {
        panel->set_onclick_entry([this] (scrollable_list::entry_data *e) {
            if (!e) {
                return;
            }
            if (!_onclick_event.empty()) {
                bvariant_map::scoped m;
                (*m)["text"] = bvariant(e->text);
                dispatch_autoconfig_es_event(get_current_widget(), _onclick_event.c_str(), *m);
                return;
            }
            if (!_js_onclick_item_ref.empty()) {
                js_call_function(_js_onclick_item_ref, { { "text", e->text } });
            }
        });
    }
}

void ui::escrollable_list::add_item(pcstr item) {
    ensure_panel();
    panel->add_entry(item);
}

void ui::escrollable_list::select_item(pcstr item) {
    if (panel) {
        panel->select(item);
    }
}

void ui::escrollable_list::select_entry(int index) {
    if (panel) {
        panel->select_entry(index);
    }
}

void ui::escrollable_list::refresh_file_finder() {
    if (panel) {
        panel->refresh_file_finder();
    }
}

void ui::escrollable_list::change_file_path(const xstring &dir, const xstring &ext) {
    params.files_dir = dir;
    params.file_ext = ext;
    ensure_panel();
    panel->change_file_path(dir, ext);
}

void ui::escrollable_list::append_files_with_extension(pcstr dir, pcstr ext) {
    ensure_panel();
    panel->append_files_with_extension(dir, ext);
}

void ui::escrollable_list::scroll_to_selected() {
    ensure_panel();
    const int idx = panel->get_selected_entry_idx();
    if (idx >= 0) {
        panel->scroll_to_entry(idx);
    }
}

xstring ui::escrollable_list::selected_entry_text(int filename_syntax) const {
    return panel ? panel->get_selected_entry_text(filename_syntax) : "";
}


int ui::escrollable_list::items_count() const { 
    return panel ? panel->items_count() : 0;
}

void ui::escrollable_list::refill() {
    if (!panel) {
        return;
    }

    if (_refill_cb) {
        entry_data_vec items;
        _refill_cb(items);
        for (const auto &it : items) {
            panel->add_entry(it.text, it.user_data);
        }
    }
}

ui::escrollable_list::~escrollable_list() {
    js_unref_function(_js_render_item_ref);
    js_unref_function(_js_onclick_item_ref);
    js_unref_function(_js_ondoubleclick_item_ref);
    g_state.remove_scrollable_list(panel.get());
    // panel will be automatically destroyed by unique_ptr
}


xstring escrollable_list_funcs[] = { "add_item", "clear", "select_item", "select_index", "refresh_file_finder", "change_file_path", "append_files_with_extension", "scroll_to_selected", "selected_text" };
xspan<xstring> ui::escrollable_list::func_names() const {
    return escrollable_list_funcs;
}

xstring escrollable_list_props[] = { "text", "enabled", "readonly", "font", "text_color", "selected", "tooltip", "items_count" };
xspan<xstring> ui::escrollable_list::prop_names() const {
    return escrollable_list_props;
}


void ui::escrollable_list::draw(UiFlags flags) {
    ensure_panel();

    vec2i screen_pos = this->screen_pos();
    panel->ui_params.pos = screen_pos;

    begin_widget(screen_pos);
    panel->draw();
    end_widget();

    g_state.scrollable_lists.push_back(panel.get());
}

void ui::escrollable_list::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "scrollable_list"));

    _js_render_item_ref = arch.r_function("onrender_item");
    _js_onclick_item_ref = arch.r_function("onclick_item");
    _js_ondoubleclick_item_ref = arch.r_function("ondoubleclick_item");
    _onclick_event = arch.r_string("onclick_event");
    _ondoubleclick_event = arch.r_string("ondoubleclick_event");

    params.files_dir = arch.r_string("dir");
    params.file_ext = arch.r_string("file_ext");
    params.use_file_finder = arch.r_bool("use_file_finder", false);
    params.view_items = arch.r_int("view_items", 10);
    params.pos = pos;
    params.blocks_x = size.x;
    params.blocks_y = size.y;
    params.buttons_size_x = arch.r_int("buttons_size_x", -1);
    params.buttons_size_y = arch.r_int("buttons_size_y", 16);
    params.buttons_margin_x = arch.r_int("buttons_margin_x", 2);
    params.buttons_margin_y = arch.r_int("buttons_margin_y", 10);
    params.text_padding_x = arch.r_int("text_padding_x", 6);
    params.text_padding_y = arch.r_int("text_padding_y", 0);
    params.text_max_width = arch.r_int("text_max_width", -1);
    params.text_centered = arch.r_bool("text_centered", false);
    params.scrollbar_margin_x = arch.r_int("scrollbar_margin_x", 0);
    params.scrollbar_margin_top = arch.r_int("scrollbar_margin_top", 0);
    params.scrollbar_margin_bottom = arch.r_int("scrollbar_margin_bottom", 0);
    params.scrollbar_dot_padding = arch.r_int("scrollbar_dot_padding", 0);
    params.thin_scrollbar = arch.r_bool("thin_scrollbar", false);
    params.draw_scrollbar_always = arch.r_bool("draw_scrollbar_always", false);
    params.draw_paneling = arch.r_bool("draw_paneling", true);
    params.font_asleep = (e_font)arch.r_int("font_asleep", FONT_NORMAL_BLACK_ON_DARK);
    params.font_focus = (e_font)arch.r_int("font_focus", FONT_NORMAL_YELLOW);
    params.font_selected = (e_font)arch.r_int("font_selected", FONT_NORMAL_WHITE_ON_DARK);
}

std::shared_ptr<ui::etext> ui::etext::acquire() {
    return std::make_shared<etext>();
}

void ui::etext::draw(UiFlags flags) {
    const vec2i offset = g_state.offset();

    if (!js_ref(TEXTFN).empty()) {
        bvariant dyn = js_call_function(js_ref(TEXTFN), 0, 0);
        ui_scope_property holder;
         _text = ui::sformat<1024>(&holder, dyn.to_str().c_str());
    }

    if (!!(_flags & UiFlags_AlignCentered)) {
        int additionaly = 0;
        if (pxsize().y > 0) {
            const int symbolh = font_definition_for(_font)->line_height;
            additionaly = ((size.y - symbolh) * 0.5f);
        }
        if (_shadow_color) {
            push(cmd_t::text_centered, Pos{offset + pos + vec2i(1, additionaly)}, BoxWidth{size.x}, Font{_font}, TextColor{_shadow_color}, Caption{_text.c_str()});
        }
        push(cmd_t::text_centered, Pos{ offset + pos + vec2i{0, additionaly} }, BoxWidth{ size.x }, Font{ _font }, TextColor{ _color }, Caption{ _text.c_str() });
    } else if (!!(_flags & UiFlags_LabelMultiline)) {
        push(cmd_t::text_multiline, Pos{offset + pos}, BoxWidth{_wrap}, Font{_font}, TextColor{_color}, Caption{_text.c_str()});
    } else if (!!(_flags & UiFlags_AlignYCentered)) {
        const int symbolh = font_definition_for(_font)->line_height;
        if (_shadow_color) {
            push(cmd_t::text_colored, Pos{ offset + pos + vec2i{ 1, (size.y - symbolh) / 2} }, Font{ _font }, TextColor{ _shadow_color }, Caption{ _text.c_str() });
        }
        push(cmd_t::text_colored, Pos{ offset + pos + vec2i{ 0,  (size.y - symbolh) / 2 } }, Font{ _font }, TextColor{ _color }, Caption{ _text.c_str() });
    } else if (!!(_flags & UiFlags_Rich)) {
        const int symbolh = font_definition_for(_font)->line_height;
        int maxlines = pxsize().y > 0
                        ? std::max(1, pxsize().y / symbolh)
                        : 0xff;

        int rwrap = _wrap <= 0 ? size.x : _wrap;
        rwrap = rwrap <= 0 ? 9999 : rwrap;

        if (!rich_text) {
            rich_text = std::make_unique<rich_text_t>();
        }

        rich_text->set_fonts(_font, _font_link);
        rich_text->set_margin(_text_margin);
        rich_text->init(_text.c_str(), offset + pos, size.x / 16, size.y / 16, /*adjust_width_on_no_scroll*/true);

        if (!(_flags & UiFlags_NoScroll)) {
            g_state.scrollbars.push_back(rich_text->scrollbar());
        }

        if (_clip_area) {
            push(cmd_t::clip_set, Pos{offset + pos}, Size{pxsize()});
        }

        push(cmd_t::rich_draw, RichTextPtr{rich_text.get()}, Caption{_text.c_str()}, Pos{offset + pos}, BoxWidth{rwrap}, Size{vec2i(0, maxlines)}, Flags{_flags & UiFlags_NoScroll});

        if (_clip_area) {
            push(cmd_t::clip_reset);
        }
    } else {
        if (_shadow_color) {
            push(cmd_t::text_colored, Pos{ offset + pos + vec2i{1, 0} }, Font{ _font }, TextColor{ _shadow_color }, Caption{ _text.c_str() });
        }
        push(cmd_t::text_colored, Pos{offset + pos}, Font{_font}, TextColor{_color}, Caption{_text.c_str()});
    }

    invoke_draw_callbacks(flags);
}

ui::emenu_header_item_proxy::~emenu_header_item_proxy() {
    js_unref_function(_onclick_js);
    js_unref_function(_textfn_js);
}

ui::emenu_header::~emenu_header() {
    js_unref_function(_onclick_js);
    js_unref_function(_textfn_js);
}

void ui::emenu_header::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "menu_header"));

    _font = arch.r_type<e_font>("font", FONT_NORMAL_BLACK_ON_LIGHT);
    _tooltip = arch.r_string("tooltip");

    const bool has_dyn_tooltip = (!!_tooltip && strstr(_tooltip.c_str(), "${") != nullptr);
    _tooltip_format = has_dyn_tooltip ? _tooltip : "";

    _onclick_js = arch.r_function("onclick");
    _textfn_js = arch.r_function("textfn");

    impl.text = arch.r_string("text");

    const bool has_dyn_text = (!!impl.text && strstr(impl.text.c_str(), "${") != nullptr);
    _text_format = has_dyn_text ? impl.text : "";

    if (!!_onclick_js) {
        impl._onclick = [jsref = _onclick_js] (auto &item) {
            js_call_function(jsref, item.parameter, 0);
        };
    }

    if (!!_textfn_js) {
        impl._textfn = [jsref = _textfn_js] () {
            return xstring(js_call_function(jsref, 0, 0).to_str());
        };
    }
}

void ui::emenu_header::load_items(archive arch, xstring section, element::items& elements) {
    impl.items.clear();

    arch.r_objects(section, [&] (pcstr key, archive elem) {
        pcstr type = elem.r_string("type");
        assert(!strcmp(type, "menu_item"));

        _onclick_js = elem.r_function("onclick");
        _textfn_js = elem.r_function("textfn");

        menu_item& item = impl.items.emplace_back();
        item.id = key;
        item.text = elem.r_string("text");

        const bool has_dyn_loc = (strstr(item.text.c_str(), "${") != nullptr);
        if (has_dyn_loc) {
            ui_scope_property holder;
            item.text = ui::sformat<128>(&holder, item.text);
        }

        item.parameter = elem.r_int("parameter");
        item.hidden = elem.r_bool("hidden");
        auto proxy_item = std::make_shared<emenu_header_item_proxy>();
        proxy_item->id = item.id;
        proxy_item->impl = &impl.items.back();
        elements.push_back(proxy_item);

        if (!!_onclick_js) {
            item._onclick = [jsref = _onclick_js] (int param) {
                js_call_function(jsref, param, 0);
            };
        }

        if (!!_textfn_js) {
            item._textfn = [jsref = _textfn_js] (int param) {
                return xstring(js_call_function(jsref, param, 0).to_str());
            };
        }
    });
}

void ui::emenu_header::draw(UiFlags flags) {
    if (impl._textfn) {
        impl.text = impl._textfn();
    } else if (!!_text_format) {
        ui_scope_property holder;
        impl.text = ui::sformat<128>(&holder, impl.text);
    }

    lang_text_draw(impl.text.c_str(), pos, _font);
}

const xstring &ui::emenu_header::tooltip() const {
    if (!!_tooltip_format) {
        ui_scope_property holder;
        _tooltip = ui::sformat<128>(&holder, _tooltip_format);
    }

    return _tooltip;
}

int ui::emenu_header::text_width() {
    return lang_text_get_width(impl.text.c_str(), _font);
}

menu_item &ui::emenu_header::item(pcstr key) {
    static menu_item dummy;
    auto it = std::find_if(impl.items.begin(), impl.items.end(), [key] (auto &it) { return it.id == key; });
    return it != impl.items.end() ? *it : dummy;
}

void ui::earrow_button::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    tiny = arch.r_bool("tiny");
    down = arch.r_bool("down");
    set_ref(ONCLICK, arch.r_function("onclick"));
}

void ui::earrow_button::js_call() {
    js_call_function(js_ref(ONCLICK));
}

void ui::earrow_button::draw(UiFlags flags) {
    auto &btn = ui::arw_button(pos, down, tiny);

    // Set up click handler - prefer JS callback if available, otherwise use C++ callback
    if (!js_ref(ONCLICK).empty()) {
        btn.onclick([this] { this->js_call(); });
    } else if (_func || _sfunc) {
        btn.onclick(_func);
        btn.onclick(_sfunc);
    }
}

void ui::egeneric_button::draw(UiFlags gflags) {
    UiFlags flags = _flags | gflags
                      | ((darkened == 1) ? UiFlags_Darkened : UiFlags_None)
                      | (!_border ? UiFlags_NoBorder : UiFlags_None)
                      | (!_hbody ? UiFlags_NoBody : UiFlags_None)
                      | (_split ? UiFlags_SplitText : UiFlags_None)
                      | (_selected ? UiFlags_Selected : UiFlags_None)
                      | (readonly ? UiFlags_Readonly : UiFlags_None);

    bstring256 button_text = _text.c_str();
    if (!js_ref(TEXTFN).empty()) {
        bvariant dyn = js_call_function(js_ref(TEXTFN), param1, param2);
        ui_scope_property holder;
        ui::format(button_text, &holder, dyn.to_str().c_str());
    }

    generic_button *btn = nullptr;
    switch (mode) {
    case 0:
        btn = &ui::button(button_text, pos, size, { _font, _font_hover }, flags);
        break;

    case 1:
        btn = &ui::large_button(button_text, pos, size, _font);
        break;
    }

    const bool clickable = !darkened && !readonly;

    // Set up click handler: ES sub-event, then JS onclick ref, then C++ callbacks
    if (clickable && !_onclick_event.empty()) {
        btn->onclick([this] {
            bvariant_map::scoped s;
            dispatch_autoconfig_es_event(get_current_widget(), _onclick_event.c_str(), *s);
        });
    } else if (clickable && !js_ref(ONCLICK).empty()) {
        btn->onclick([this] { this->js_call(); });
    }

    if (clickable && !js_ref(ONRCLICK).empty()) {
        btn->onrclick([this] { this->js_rcall(); });
    }

    if (clickable && _func && js_ref(ONCLICK).empty() && _onclick_event.empty()) { btn->onclick(_func); }
    if (clickable && _sfunc && js_ref(ONCLICK).empty() && _onclick_event.empty()) { btn->onclick(_sfunc); }

    if (clickable && _rfunc && js_ref(ONRCLICK).empty()) { btn->onrclick(_rfunc); }
    if (clickable && _srfunc && js_ref(ONRCLICK).empty()) { btn->onrclick(_srfunc); }

    const vec2i offset = g_state.offset();
    if (clickable && is_button_hover(*btn, offset)) {
        ui::set_tooltip(_tooltip);
    }
}

void ui::egeneric_button::js_call() {
    if (!js_ref(ONCLICK).empty()) {
        js_call_function(js_ref(ONCLICK));
    }
}

void ui::egeneric_button::js_rcall() {
    if (!js_ref(ONRCLICK).empty()) {
        js_call_function(js_ref(ONRCLICK));
    }
}

void ui::egeneric_button::load(archive arch, element *parent, items &elems) {
    elabel::load(arch, parent, elems);

    pcstr mode_str = arch.r_string("mode");
    if (mode_str && !strcmp(mode_str, "large")) {
        mode = 1;
    }
    _tooltip = arch.r_string("tooltip");
    _border = arch.r_int("border", 1);
    _hbody = arch.r_bool("hbody", true);
    _split = arch.r_bool("split", false);
    set_ref(ONCLICK, arch.r_function("onclick"));
    set_ref(ONRCLICK, arch.r_function("onrclick"));
    set_ref(TEXTFN, arch.r_function("textfn"));
    _onclick_event = arch.r_string("onclick_event");
    param1 = arch.r_int("param1");
    param2 = arch.r_int("param2");
}

static xstring ui_echeckbox_props[] = { "text", "enabled", "readonly", "font", "text_color", "selected", "tooltip", "onclick", "textfn", "checked", "checkedfn" };
xspan<xstring> ui::echeckbox::prop_names() const {
    return make_span(ui_echeckbox_props);
}

void ui::echeckbox::draw(UiFlags flags) {
    if (!js_ref(CHECKEDFN).empty()) {
        _checked = js_call_function(js_ref(CHECKEDFN), param1, param2).to_bool();
    }

    if (js_ref(TEXTFN).empty()) {
        _text = _checked ? _checked_text : _unchecked_text;
    } else {
        bvariant dyn = js_call_function(js_ref(TEXTFN), 0, 0);
        _text = dyn.to_str();
    }

    egeneric_button::draw(flags);
}

void ui::echeckbox::load(archive arch, element *parent, items &elems) {
    egeneric_button::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "checkbox"));

    _checked = arch.r_bool("checked", false);
    _checked_text = arch.r_string("checked_text", "x");
    _unchecked_text = arch.r_string("unchecked_text", "");
    set_ref(CHECKEDFN, arch.r_function("checkedfn"));
}