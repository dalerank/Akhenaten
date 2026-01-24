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

#include <stack>

namespace ui {
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
            case generic: return !!generic_buttons_handle_mouse(m, offset, &g_button, 1, &tmp_btn);
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
        widget* current_widget = nullptr;

        void reset() {
            while (!_offset.empty()) {
                _offset.pop();
            };
            buttons.clear();
            scrollbars.clear();
            scrollable_lists.clear();
            current_widget = nullptr;
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
    case _("image_button"): elm = std::make_shared<ui::eimage_button>(); break;
    case _("resource_icon"): elm = std::make_shared<ui::eresource_icon>(); break;
    case _("arrow_button"): elm = std::make_shared<ui::earrow_button>(); break;
    case _("border"): elm = std::make_shared<ui::eborder>(); break;
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
    painter ctx = game.painter();
    const vec2i goffset = g_state.offset();
    ctx.fill_rect(goffset + offset, size, c);
}

vec2i ui::current_offset() {
    return g_state.offset();
}

void ui::begin_frame() {
    assert(g_state.buttons.size() < 1000);
    //assert(g_state._offset.size() == 0);
    g_state.reset();
    tooltipctx.set(0, "");
}

void ui::end_frame() {
    
}

void ui::end_widget() {
    if (!g_state._offset.empty()) {
        g_state._offset.pop();
    }
}

ui::widget* ui::get_current_widget() {
    return g_state.current_widget;
}

bool ui::handle_mouse(const mouse *m) {
    bool handle = false;
    for (int i = g_state.buttons.size() - 1; i >= 0 && !handle; --i) {
        handle |= !!g_state.buttons[i].handle_mouse(m, g_state.offset());
    }

    for (int i = g_state.scrollbars.size() - 1; i >= 0 && !handle; --i) {
        handle |= !!scrollbar_handle_mouse(g_state.offset(), g_state.scrollbars[i], m);
    }

    for (int i = g_state.scrollable_lists.size() - 1; i >= 0 && !handle; --i) {
        auto panel = g_state.scrollable_lists[i];
        mouse m_relative = *m;
        m_relative -= g_state.offset();
        handle |= !!panel->input_handle(&m_relative);
    }

    return handle;
}

void ui::clear_active_elements() {
    g_state.buttons.clear();
    g_state.scrollbars.clear();
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
        int mask = darkened ? 0xffe0e0e0 : 0xffffffff;
        small_panel_draw_colored(offset + pos, (size.x / 16), gbutton.hovered ? 1 : 2, mask);
    } else if (hasbody) {
        if (thinborder) {
            graphics_draw_rect(offset + pos, size, 0xff00000);
        } else {
            button_border_draw(offset + pos, size, gbutton.hovered && !darkened);
        }
    } else if (hasborder) {
        if (gbutton.hovered && !darkened) {
            if (thinborder) {
                graphics_draw_rect(offset + pos, size, 0xff000000);
            } else {
                button_border_draw(offset + pos, size, true);
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
            if (alingxcenter) {
                text_draw_centered((uint8_t *)str.c_str(), offset.x + pos.x + 1, starty, size.x, font, 0);
            } else {
                text_draw((uint8_t *)str.c_str(), offset.x + pos.x + 8, starty, font, 0);
            }
            starty += symbolh + 2;
        }
    } else if (label) {
        const bool alingycenter = !!(flags & UiFlags_AlignYCentered);
        const bool rich = !!(flags & UiFlags_Rich);
        if (rich) {
            int symbolw = text_get_width("H", font);
            int lines_num = std::max<int>(1, (int)strlen(label) * symbolw / size.x);
            int centering_y_offset = (size.y - lines_num * symbolh) / 2;
            rich_text_t rich_text;
            rich_text.set_fonts(font, FONT_NORMAL_YELLOW);
            rich_text.draw(label, offset + pos + vec2i(0, centering_y_offset), size.x, lines_num, false, true);
        } else if (alingycenter) {
            text_draw((uint8_t *)label, offset.x + pos.x + 8, offset.y + pos.y + (size.y - symbolh) / 2 + 2, font, 0);
        } else if (alignleft) {
            text_draw((uint8_t *)label, offset.x + pos.x + 8, offset.y + pos.y + 8, font, 0);
        } else if (alingxcenter) {
            text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 4, size.x, font, 0);
        } else {
            text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + (size.y - symbolh) / 2, size.x, font, 0);
        }
    }    

    if (darkened) {
        graphics_shade_rect(offset + pos, size, 0x80);
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

    large_label_draw(offset.x + pos.x, offset.y + pos.y, size.x / 16, focused ? 1 : 0);
    const int letter_height = font_definition_for(font)->line_height;
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + (size.y - letter_height) / 2, size.x, font, 0);

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

        painter ctx = game.painter();
        ImgFlags imgflags = grayscaled ? ImgFlag_Grayscale : ImgFlag_None;
        ctx.img_generic(image_id, state_offset + pos, COLOR_WHITE, 1.0f, imgflags);
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
        text_draw_centered(label, offset.x + pos.x, offset.y + pos.y, box_width, font, 0);
        return box_width;
    } else if (!!(flags & UiFlags_LabelMultiline)) {
        return text_draw_multiline(label, offset + pos, box_width, font, 0);
    } else if (!!(flags & UiFlags_Rich)) {
        rich_text_t rich_text;
        rich_text.set_fonts(font, FONT_NORMAL_YELLOW);
        return rich_text.draw(label, offset, box_width, 10, false);
    } else {
        return lang_text_draw(label, offset + pos, font, box_width);
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
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();

    if (box_width > 0) {
        lang_text_draw_centered_colored(tx.group, tx.id, offset.x + pos.x, offset.y + pos.y, box_width, font, color);
        return box_width;
    } else {
        return lang_text_draw_colored(tx.group, tx.id, offset.x + pos.x, offset.y + pos.y, font, color);
    }
}

int ui::label_colored(pcstr tx, vec2i pos, e_font font, color color, int box_width) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    if (box_width > 0) {
        text_draw_centered((const uint8_t*)tx, offset.x + pos.x, offset.y + pos.y, box_width, font, color);
        return box_width;
    } else {
        return lang_text_draw_colored(tx, offset.x + pos.x, offset.y + pos.y, font, color);
    }
}

const image_t *ui::eimage(int imgid, vec2i pos) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    return ctx.img_generic(imgid, pos + offset);
}

const image_t *ui::eimage(image_desc imgd, vec2i pos) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    return ctx.img_generic(imgd.tid(), pos + offset);
}

void ui::panel(vec2i pos, vec2i size, UiFlags flags) {
    const vec2i offset = g_state.offset();
    if (!!(flags & UiFlags_PanelOuter)) {
        outer_panel_draw(offset + pos, size.x, size.y);
    } else if (!!(flags & UiFlags_PanelInner)) {
        inner_panel_draw(offset + pos, size);
    }
}

void ui::line(bool hline, vec2i npos, int size, color c) {
    const vec2i offset = g_state.offset();
    if (hline) {
        graphics_draw_horizontal_line(npos + offset, size, c);
    } else {
        graphics_draw_vertical_line(npos + offset, size, c);
    }
}

void ui::border(vec2i pos, vec2i size, int type, int color, UiFlags flags) {
    const vec2i offset = g_state.offset();
    graphics_draw_rect(offset + pos, size, color);
}

void ui::rect(vec2i pos, vec2i size, int fill, int color, UiFlags flags) {
    const vec2i offset = g_state.offset();
    if (fill) {
        ui::fill_rect(offset + pos, size, fill);
    } else {
        graphics_draw_rect(offset + pos, size, color);
    }
}

void ui::icon(vec2i pos, e_resource res, UiFlags flags) {
    const vec2i offset = g_state.offset();
    painter ctx = game.painter();
    const image_t *img = ctx.img_generic(image_id_resource_icon(res), offset + pos);
    if (!!(flags & UiFlags_Outline)) {
        graphics_draw_inset_rect(pos - vec2i{1, 1}, vec2i{ img->width, img->height } + vec2i{2, 2});
    }
}

void ui::icon(vec2i pos, e_advisor adv) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    ctx.img_generic(advisor_icons.tid() + (adv - 1), offset + pos);
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

void ui::widget::load(pcstr section) {
    io.name = section;
    g_config_arch.r(section, *this);
}

bool ui::widget::contains(const xstring &id) const {
    auto it = std::find_if(elements.begin(), elements.end(), [xid = xstring(id)] (const auto &e) { return e->id == xid; });
    return (it != elements.end());
}

ui::element& ui::widget::operator[](pcstr id) {
    auto it = std::find_if(elements.begin(), elements.end(), [xid = xstring(id)] (const auto &e) { return e->id == xid; });
    if (check_errors && it == elements.end()) {
        logs::error("No element with id:%s", id);
    }
    return (it != elements.end() ? **it : ui::dummy_element);
}

void ui::widget::event(pcstr evname, const bvariant_map &js_j) {
    widget* prev_widget = g_state.current_widget;
    g_state.current_widget = this;
    
    bvariant_map enhanced_js_j = js_j;
    for (const auto &elem : elements) {
        if (!elem->id.empty()) {
            bstring64 elmid("__ui_elem_", elem->id.c_str());
            bstring64 elmkey("__ui_elem:", elem->id.c_str());
            enhanced_js_j[elmid.c_str()] = bvariant(elmkey.c_str());
        }
    }
    
    js_call_event_handlers(evname, enhanced_js_j);
    
    // Restore previous widget
    g_state.current_widget = prev_widget;
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

ui::elabel::~elabel() {
    js_unref_function(_js_textfn_ref);
}

void ui::elabel::draw(UiFlags flags) {
    const vec2i offset = g_state.offset();

    if (!_js_textfn_ref.empty()) {
        pcstr dynamic_text = js_call_function_with_result(_js_textfn_ref, 0, 0);
        if (dynamic_text && *dynamic_text) {
            ui_scope_property holder;
            _text = ui::format(&holder, dynamic_text);
        }
    }

    if (_body.x > 0) {
        small_panel_draw(pos + offset, _body.x, _body.y);
    }

    auto dpos = pos + ((_body.x > 0) ? vec2i{ 8, 4 } : vec2i{ 0, 0 });
    auto box_width = size.x;

    if (!!(_flags & UiFlags_AlignCentered)) {
        ::text_draw_centered(_text.c_str(), offset.x + dpos.x, offset.y + dpos.y, box_width, _font, 0);
    } else if (!!(_flags & UiFlags_LabelMultiline)) {
        text_draw_multiline(_text.c_str(), offset + dpos, box_width, _font, 0);
    } else if (!!(_flags & UiFlags_Rich)) {
        rich_text_t rich_text;
        rich_text.set_fonts(_font, FONT_NORMAL_YELLOW);
        rich_text.set_margin(_text_margin);
        rich_text.draw(_text.c_str(), offset, box_width, 10, false);
    } else {
        lang_text_draw(_text.c_str(), offset + dpos, _font, box_width);
    }

    if (_draw_callback) {
        _draw_callback(this, flags);
    }
}

void ui::elabel::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    _text = arch.r_string("text");
    _js_textfn_ref = arch.r_function("textfn");
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
    _js_onclick_ref = arch.r_function("onclick");

    pcstr name_icon_texture = arch.r_string("icon_texture");
    if (name_icon_texture && *name_icon_texture) {
        vec2i tmp_size;
        icon_texture = load_icon_texture(name_icon_texture, tmp_size);
    }
}

ui::eimage_button::~eimage_button() {
    js_unref_function(_js_onclick_ref);
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

    // Set up click handler - prefer JS callback if available, otherwise use C++ callback
    if (!_js_onclick_ref.empty()) {
        btn->onclick([js_ref = _js_onclick_ref](int, int) {
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

void ui::escrollable_list::add_entry(pcstr item) {
    if (!panel) {
        return;
    }

    panel->add_entry(item);
}

void ui::escrollable_list::select_entry(pcstr item) {
    if (!panel) {
        return;
    }

    panel->select(item);
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
    g_state.remove_scrollable_list(panel.get());
    // panel will be automatically destroyed by unique_ptr
}

void ui::escrollable_list::draw(UiFlags flags) {
    if (!panel) {
        panel = std::make_unique<scrollable_list>(
            button_none,  // left_click_callback
            button_none,  // right_click_callback
            button_none,  // double_click_callback
            button_none,  // focus_change_callback
            params
        );

        refill();

        panel->set_onclick_entry(_onclick_cb);
        panel->set_onclick_entry(_onclick_ex_cb);
        panel->set_onclick_dbl_entry(_onclick_dbl_ex_cb);
        panel->set_custom_render_func(_custom_render_cb);
    }

    vec2i screen_pos = this->screen_pos();
    panel->ui_params.pos = screen_pos;
    panel->draw();
    
    g_state.scrollable_lists.push_back(panel.get());
}

void ui::escrollable_list::load(archive arch, element *parent, items &elems) {
    element::load(arch, parent, elems);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "scrollable_list"));

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

    if (!_js_textfn_ref.empty()) {
        pcstr dynamic_text = js_call_function_with_result(_js_textfn_ref, 0, 0);
        if (dynamic_text && *dynamic_text) {
            ui_scope_property holder;
            _text = ui::format(&holder, dynamic_text);
        }
    }

    if (!!(_flags & UiFlags_AlignCentered)) {
        int additionaly = 0;
        if (pxsize().y > 0) {            
            const int symbolh = font_definition_for(_font)->line_height;
            additionaly = ((size.y - symbolh) * 0.5f);
        }
        if (_shadow_color) {
            text_draw_centered((uint8_t *)_text.c_str(), offset.x + pos.x + 1, offset.y + pos.y + additionaly, size.x, _font, _shadow_color);
        }
        text_draw_centered((uint8_t *)_text.c_str(), offset.x + pos.x, offset.y + pos.y + additionaly, size.x, _font, _color);
    } else if (!!(_flags & UiFlags_LabelMultiline)) {
        text_draw_multiline(_text, offset + pos, _wrap, _font, _color);
    } else if (!!(_flags & UiFlags_AlignYCentered)) {
        const int symbolh = font_definition_for(_font)->line_height;
        if (_shadow_color) {
            text_draw((uint8_t *)_text.c_str(), offset.x + pos.x + 1, offset.y + pos.y + (size.y - symbolh) / 2, _font, _shadow_color);
        }
        text_draw((uint8_t *)_text.c_str(), offset.x + pos.x, offset.y + pos.y + (size.y - symbolh) / 2, _font, _color);
    } else if (!!(_flags & UiFlags_Rich)) {
        if (_clip_area) {
            graphics_set_clip_rectangle(offset + pos, pxsize());
        }

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
        rich_text->draw(_text.c_str(), offset + pos, rwrap, maxlines, false);
        
        if (_clip_area) {
            graphics_reset_clip_rectangle();
        }

        if (!(_flags & UiFlags_NoScroll)) {
            rich_text->draw_scrollbar(vec2i{-16, 0});
            g_state.scrollbars.push_back(rich_text->scrollbar());
        }
    } else {
        if (_shadow_color) {
            text_draw((uint8_t *)_text.c_str(), offset.x + pos.x + 1, offset.y + pos.y, _font, _shadow_color);
        }
        text_draw((uint8_t *)_text.c_str(), offset.x + pos.x, offset.y + pos.y, _font, _color);
    }

    if (_draw_callback) {
        _draw_callback(this, flags);
    }
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

    _onclick_js = arch.r_function("onclick");
    _textfn_js = arch.r_function("textfn");

    impl.text = arch.r_string("text");

    if (!!_onclick_js) {
        impl._onclick = [jsref = _onclick_js] (auto &item) {
            js_call_function_with_result(jsref, item.parameter, 0);
        };
    }

    if (!!_textfn_js) {
        impl._textfn = [jsref = _textfn_js] () {
            return js_call_function_with_result(jsref, 0, 0);
        };
    }

    if (!!impl.text && impl.text[0u] == '#') {
        impl.text = lang_text_from_key(impl.text.c_str());
    }
}

void ui::emenu_header::load_items(archive arch, pcstr section, element::items& elements) {
    impl.items.clear();

    arch.r_objects(section, [&] (pcstr key, archive elem) {
        pcstr type = elem.r_string("type");
        assert(!strcmp(type, "menu_item"));

        _onclick_js = elem.r_function("onclick");
        _textfn_js = elem.r_function("textfn");

        menu_item& item = impl.items.emplace_back();
        item.id = key;
        item.text = elem.r_string("text");
        if (!!item.text && item.text[0u] == '#') {
            item.text = lang_text_from_key(item.text.c_str());
        }
        item.parameter = elem.r_int("parameter");
        item.hidden = elem.r_bool("hidden");
        auto proxy_item = std::make_shared<emenu_header_item_proxy>();
        proxy_item->id = item.id;
        proxy_item->impl = &impl.items.back();
        elements.push_back(proxy_item);

        if (!!_onclick_js) {
            item._onclick = [jsref = _onclick_js] (int param) {
                js_call_function_with_result(jsref, param, 0);
            };
        }

        if (!!_textfn_js) {
            item._textfn = [jsref = _textfn_js] (int param) {
                return js_call_function_with_result(jsref, param, 0);
            };
        }
    });
}

void ui::emenu_header::draw(UiFlags flags) {
    pcstr text = impl.text.c_str();
    if (impl._textfn) {
        text = impl._textfn();
    }

    lang_text_draw(text, pos, _font);
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
    _js_onclick_ref = arch.r_function("onclick");
}

ui::earrow_button::~earrow_button() {
    js_unref_function(_js_onclick_ref);
}

void ui::earrow_button::js_call() {
    js_call_function(_js_onclick_ref);
}

void ui::earrow_button::draw(UiFlags flags) {
    auto &btn = ui::arw_button(pos, down, tiny);
    
    // Set up click handler - prefer JS callback if available, otherwise use C++ callback
    if (!_js_onclick_ref.empty()) {
        btn.onclick([this] { this->js_call(); });
    } else if (_func || _sfunc) {
        btn.onclick(_func);
        btn.onclick(_sfunc);
    } 
}

ui::egeneric_button::~egeneric_button() {
    js_unref_function(_js_onclick_ref);
    js_unref_function(_js_onrclick_ref);
    js_unref_function(_js_textfn_ref);
}

void ui::egeneric_button::draw(UiFlags gflags) {
    UiFlags flags = _flags | gflags
                      | ((darkened == 1) ? UiFlags_Darkened : UiFlags_None)
                      | (!_border ? UiFlags_NoBorder : UiFlags_None)
                      | (!_hbody ? UiFlags_NoBody : UiFlags_None)
                      | (_split ? UiFlags_SplitText : UiFlags_None)
                      | (_selected ? UiFlags_Selected : UiFlags_None)
                      | (readonly ? UiFlags_Readonly : UiFlags_None);

    pcstr button_text = _text.c_str();
    if (!_js_textfn_ref.empty()) {
        pcstr dynamic_text = js_call_function_with_result(_js_textfn_ref, param1, param2);
        if (dynamic_text && *dynamic_text) {
            ui_scope_property holder;
            button_text = ui::format(&holder, dynamic_text);
        }
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
    
    // Set up click handler - prefer JS callback if available, otherwise use C++ callback
    if (clickable && !!_js_onclick_ref) {
        btn->onclick([this] { this->js_call(); });
    }

    if (clickable && !!_js_onrclick_ref) {
        btn->onrclick([this] { this->js_call(); });
    }

    if (clickable && _func && !_js_onclick_ref) { btn->onclick(_func); }
    if (clickable && _sfunc && !_js_onclick_ref) { btn->onclick(_sfunc); }

    if (clickable && _rfunc && !_js_onrclick_ref) { btn->onrclick(_rfunc); }
    if (clickable && _srfunc && !_js_onrclick_ref) { btn->onrclick(_srfunc); }

    const vec2i offset = g_state.offset();
    if (clickable && is_button_hover(*btn, offset)) {
        ui::set_tooltip(_tooltip);
    }
}

void ui::egeneric_button::js_call() {
    if (!_js_onclick_ref.empty()) {
        js_call_function(_js_onclick_ref);
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
    _js_onclick_ref = arch.r_function("onclick");
    _js_onrclick_ref = arch.r_function("onrclick");
    _js_textfn_ref = arch.r_function("textfn");
    param1 = arch.r_int("param1");
    param2 = arch.r_int("param2");
}