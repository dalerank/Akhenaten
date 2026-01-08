#pragma once

#include <cstdint>
#include <memory>
#include <functional>

#include "core/archive.h"
#include "core/variant.h"

#include "input/hotkey.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/elements/ui_scope_property.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/elements/rich_text.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/button.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/menu.h"
#include "graphics/image_groups.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/image.h"
#include "graphics/text.h"

struct mouse;
struct tooltip_context;

enum UiFlags_ {
    UiFlags_None = 0,
    UiFlags_Darkened = 1 << 1,
    UiFlags_Grayscale = 1 << 2,
    UiFlags_PanelInner = 1 << 3,
    UiFlags_LabelMultiline = 1 << 4,
    UiFlags_AlignYCentered = 1 << 5,
    UiFlags_NoBody = 1 << 6,
    UiFlags_Rich = 1 << 7,
    UiFlags_Selected = 1 << 8,
    UiFlags_AlignCentered = 1 << 9,
    UiFlags_NoScroll = 1 << 10,
    UiFlags_AlignLeft = 1 << 11,
    UiFlags_AlignXCentered = 1 << 12,
    UiFlags_Readonly = 1 << 13,
    UiFlags_NoBorder = 1 << 14,
    UiFlags_Outline = 1 << 15,
    UiFlags_SplitText = 1 << 16,
    UiFlags_PanelSmall = 1 << 17,
    UiFlags_PanelOuter = 1 << 18,
    UiFlags_ThinBorder = 1 << 19,
};
using UiFlags = int;

namespace ui {

struct img_button_offsets { int data[4] = {0, 1, 2, 3}; };

const tooltip_context &get_tooltip();
void set_tooltip(const xstring &text);
void begin_frame();
void end_frame();
void begin_widget(vec2i offset, bool relative = false);
void end_widget();
bool handle_mouse(const mouse *m);
void clear_active_elements();

int label(int group, int number, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags flags = UiFlags_None, int box_width = 0);
int label(pcstr, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags flags = UiFlags_None, int box_width = 0);

template<typename ... Args>
inline int label(vec2i offset, e_font font, int box_width, UiFlags flags, pcstr fmt, const Args&... args) {
    bstring1024 s;
    s.printf(fmt, args...);
    return label(s.c_str(), offset, font, flags , box_width);
}

int label_amount(int group, int number, int amount, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, pcstr postfix = "");
int label_percent(int amount, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT);
int label_colored(textid tx, vec2i pos, e_font font, color color, int box_width = 0);
int label_colored(pcstr tx, vec2i pos, e_font font, color color, int box_width = 0);
const image_t *eimage(int imgid, vec2i pos);
const image_t *eimage(image_desc img, vec2i pos);
void panel(vec2i pos, vec2i size, UiFlags flags);
void border(vec2i pos, vec2i size, int type, int color, UiFlags flags);
void rect(vec2i pos, vec2i size, int fill, int color, UiFlags flags);
void icon(vec2i pos, e_resource img, UiFlags flags = UiFlags_None);
void icon(vec2i pos, e_advisor advisor);
int button_hover(const mouse *m);

inline fonts_vec fonts_def() { return { FONT_NORMAL_BLACK_ON_LIGHT, FONT_INVALID }; }
generic_button &button(pcstr label, vec2i pos, vec2i size, fonts_vec fonts = fonts_def(), UiFlags flags = UiFlags_None, std::function<void(int, int)> cb = {});
generic_button &link(pcstr label, vec2i pos, vec2i size, e_font font = FONT_NORMAL_WHITE_ON_DARK, UiFlags flags = UiFlags_None, std::function<void(int, int)> cb = {});
generic_button &large_button(pcstr label, vec2i pos, vec2i size, e_font font = FONT_NORMAL_BLACK_ON_LIGHT);
generic_button &button(uint32_t id);
pcstr button_tooltip(uint32_t id);
image_button &img_button(image_desc desc, vec2i pos, vec2i size, const img_button_offsets offsets = {}, UiFlags flags = UiFlags_None);
image_button &imgok_button(vec2i pos, std::function<void(int, int)> cb);
image_button &imgcancel_button(vec2i pos, std::function<void(int, int)> cb);
arrow_button &arw_button(vec2i pos, bool down, bool tiny = false, UiFlags_ flags = UiFlags_None);
scrollbar_t &scrollbar(scrollbar_t &scrollbar, vec2i pos, int &value, vec2i size = {-1, -1});
void fill_rect(vec2i offset, vec2i size, color c);
vec2i current_offset();

pcstr str(int group, int id);
pcstr str_from_key(pcstr key);

template<typename ... Args>
pcstr str_from_key(pcstr fmt, Args ... args) {
    bstring64 key;
    key.printf(fmt, args...);
    return str_from_key(key.c_str());
}

inline pcstr str(std::pair<int, int> r) { return str(r.first, r.second); }
inline pcstr str(textid r) { return str(r.group, r.id); }
pcstr resource_name(e_resource r);

struct emenu_header;
struct eimage_button;
struct escrollable_list;

template<typename T>
bstring1024 format(const T *o, pcstr fmt) {
    if (!fmt || !*fmt) {
        return {};
    }

    struct kv {
        bstring64 key;
        bstring1024 value;
        pstr data() { return key.data(); }
        kv &operator=(pcstr v) { key = v; return *this; }
        void resize(size_t s) { key.resize(s); }
        pcstr c_str() const { return key.c_str(); }
    };
    svector<kv, 32> items;

    const char *start = fmt;
    while ((start = strstr(start, "${")) != NULL) {  // Find the start of "${"
        const char *end = ::strchr(start, '}'); // Find the closing '}'
        if (end != NULL) {
            const int length = end - start + 1;

            auto &item = items.emplace_back();
            item.key.ncat(start, length);

            // Move the pointer past the current block
            start = end + 1;
        } else {
            break; // Exit if no closing '}' is found
        }
    }

    for (auto &item : items) {
        if (strncmp(item.key, "${", 2) != 0) {
            continue;
        }

        pcstr scopeend = item.key.strchr('}');
        if (scopeend == nullptr) {
            continue;
        }

        item.key.resize(scopeend - item.key + 1);

        int group, id;
        uint32_t args_handled = sscanf(item.key.c_str(), "${%d.%d}", &group, &id);
        if (args_handled == 2) {
            item.value = ui::str(group, id);
            continue;
        }

        bstring128 loc("#");
        args_handled = sscanf(item.key.c_str(), "${loc.%[^}]}", loc.data() + 1);
        if (args_handled == 1) {
            item.value = ui::str_from_key(loc.c_str());
            continue;
        }

        bstring128 domain, prop;
        args_handled = sscanf(item.key.c_str(), "${%[^.].%[^}]}", domain.data(), prop.data());
        if (args_handled == 2) {
            bvariant bvar = o ? o->get_property(xstring(domain), xstring(prop)) : bvariant{};
            if (bvar.is_empty()) {
                ui_scope_property dummy;
                bvar = dummy.get_property(xstring(domain), xstring(prop));
            }

            if (!bvar.is_empty()) {
                item.value = bvar.to_str();
            }
        }
    }

    bstring1024 result = fmt;
    for (const auto &item : items) {
        if (item.value.len()) {
            result.replace_str(item.key, item.value);
        }
    }

    return result;
}

struct margini {
    static constexpr int nomargin = -99999;
    int left = nomargin;
    int top = nomargin;
    int right = nomargin;
    int bottom = nomargin;
    int centerx = nomargin;
    int centery = nomargin;
};

struct element {
    using ptr = std::shared_ptr<element>;
    using items = std::vector<ptr>;
    using draw_callback = std::function<void(element*, UiFlags)>;

    int debug_tag;
    xstring id;
    xstring parent_id;
    vec2i pos;
    vec2i size;
    margini margin = {};
    bool readonly = false;
    bool enabled = true;
    uint8_t darkened = 0;
    draw_callback _draw_callback;
    bool fill_width = false;
    bool fill_height = false;

    virtual ~element() {}

    virtual void draw(UiFlags flags) {}
    virtual void load(archive, element* parent, items &elems);
    virtual void text(pcstr) {}
    inline void text(textid t) { text(ui::str(t)); }
    virtual void tooltip(textid t) {}
    virtual void tooltip(const xstring &t) {}
    virtual int text_width() { return 0; }
    virtual vec2i pxsize() const {
        return vec2i { 
            fill_width ? screen_width() : size.x,
            fill_height ? screen_height() : size.y,
        };
    }
    inline void text(int font, pcstr v) { this->font(font); this->text(v); }
    virtual void text_color(color) {}
    virtual void image(int) {}
    virtual void image(const animation_t&) {}
    virtual void image(const image_desc&) {}
    virtual image_desc image() const { return {}; }
    virtual void font(int) {}
    virtual e_font font() const { return FONT_INVALID; }
    virtual e_font font_hover() const { return FONT_INVALID; }
    virtual void set_enabled(bool v) { enabled = v; }
    virtual void width(int v) { size.x = v; }
    virtual int value() const { return 0; }
    virtual void select(bool v) {}
    virtual bool selected() const { return false; }
    virtual void max_value(int v) {}
    virtual const xstring &tooltip() const { static xstring dummy;  return dummy; }
    virtual const xstring &format() const { static xstring dummy; return dummy; }
    virtual const xstring &text() const { static xstring dummy; return dummy; }
    virtual element &onclick(std::function<void(int, int)>) { return *this; }
            element &onclick(std::function<void()> f) { onclick([f] (int, int) { f(); });  return *this; }
    virtual void onevent(std::function<void()>) { }
    virtual element &onrclick(std::function<void(int, int)>) { return *this; }
            element &onrclick(std::function<void()> f) { onrclick([f] (int, int) { f(); }); return *this;}
    virtual void ondraw(draw_callback f) { _draw_callback = f;};

    virtual emenu_header *dcast_menu_header() { return nullptr; }
    virtual eimage_button *dcast_image_button() { return nullptr; }
    virtual escrollable_list *dcast_scrollable_list() { return nullptr; }

    pcstr text_from_key(pcstr key);

    inline void operator=(pcstr t) { text(t); }
    inline void operator=(const bstring512 &t) { text(t); }
    inline void operator=(const xstring &t) { text(t.c_str()); }
    inline void operator=(const textid &t) { text(ui::str(t.group, t.id)); }
    inline void operator=(const image_desc &t) { image(t); }
    inline void operator=(const animation_t &t) { image(t); }
    void update_pos(const margini &r);
    vec2i screen_pos() const;

    template<class T>
    void preformat_text(T& str) {
        T result;
        bool inSubstr = false;
        bstring128 replacement;

        pcstr ptr = str.c_str();
        for (; *ptr != '\0'; ++ptr) {
            if (*ptr == '#') {
                inSubstr = true;
                replacement.append(*ptr);
                continue;
            }

            if (inSubstr) {
                if (*ptr == ' ') {
                    inSubstr = false;
                    result.append(text_from_key(replacement.c_str()));
                    replacement.clear();
                } else {
                    replacement.append(*ptr);
                }
            }

            if (!inSubstr) {
                result.append(*ptr);
            }
        }

        if (inSubstr) {
            result.append(text_from_key(replacement.c_str()));
        }

        str = result;
    }

    template<class ... Args> 
    inline void text_var(pcstr fmt, const Args&... args) {
        bstring512 formated_text;
        formated_text.printf(fmt, args...);
        preformat_text(formated_text);
        text(formated_text);
    }
};

struct eimg : public element {
    image_desc img_desc;
    bool isometric;
    vec2i centering;

    virtual void draw(UiFlags flags) override;
    virtual void load(archive elem, element *parent, items &elems) override;
    virtual void image(const image_desc& image) override;
    virtual void image(const animation_t& image) override;
    virtual void image(int image) override;
    virtual image_desc image() const override { return img_desc; }
};

struct ebackground : public element {
    image_desc img_desc;
    float scale = 1.f;

    virtual void draw(UiFlags flags) override;
    virtual void load(archive elem, element *parent, items &elems) override;
    virtual image_desc image() const override { return img_desc; }
};

struct eborder : public element {
    int border;
    int colori;

    virtual void load(archive elem, element *parent, items &elems) override;
    virtual void draw(UiFlags flags) override;
};

struct eresource_icon : public element {
    e_resource res;
    xstring prop;

    virtual void draw(UiFlags flags) override;
    virtual void image(int image) override;
    virtual void text(pcstr) override;
    virtual const xstring &format() const override { return prop; }
    virtual void load(archive elem, element *parent, items &elems) override;
};

struct eouter_panel : public element {
    virtual void draw(UiFlags flags) override;
    virtual vec2i pxsize() const override { return size * 16; }
    virtual void load(archive elem, element *parent, items &elems) override;
};

struct einner_panel : public element {
    virtual void draw(UiFlags flags) override;
    virtual vec2i pxsize() const override { return size * 16; }
    virtual void load(archive elem, element *parent, items &elems) override;
};

struct elabel : public element {
    xstring _text;
    xstring _js_textfn_ref;

    xstring _tooltip;
    xstring _format;

    rich_text_t::margin_t _text_margin;

    e_font _font;
    e_font _font_hover;
    e_font _font_link;
    vec2i _body;
    color _color;
    color _shadow_color;
    UiFlags _flags;
    int _wrap;
    bool _clip_area;

    ~elabel() override;

    virtual void draw(UiFlags flags) override;
    virtual void load(archive elem, element *parent, items &elems) override;
    virtual void text(pcstr) override;
    virtual void text_color(color) override;
    virtual void font(int) override;
    virtual e_font font_hover() const override { return _font_hover; }
    virtual e_font font() const override { return _font; }
    virtual const xstring &tooltip() const override { return _tooltip; }
    virtual const xstring &format() const override { return _format; }
    virtual const xstring &text() const override { return _text; }
    virtual void width(int) override;
};

struct etext : public elabel {
    // here need todo rich_text_pool
    std::unique_ptr<rich_text_t> rich_text;

    virtual void draw(UiFlags flags) override;
    virtual void load(archive elem, element *parent, items &elems) override;
};

struct escrollbar : public element {
    scrollbar_t scrollbar;

    virtual int value() const override { return scrollbar.scroll_position; }
    virtual void max_value(int v) override { scrollbar.max_scroll_position = v; }
    virtual void onevent(std::function<void()> func) override { scrollbar.onscroll(func); }
    virtual void draw(UiFlags flags) override;
    virtual void load(archive elem, element *parent, items &elems) override;
};

struct escrollable_list : public element {
    using entry_data = scrollable_list::entry_data;
    using entry_data_vec = std::vector<entry_data>;
    using refill_callback = std::function<void(entry_data_vec &)>;
    using onclick_callback = scrollable_list::onclick_callback;
    using onclick_ex_callback = scrollable_list::onclick_ex_callback;
    using onclick_double_ex_callback = scrollable_list::onclick_double_ex_callback;
    using custom_text_render_func = scrollable_list::custom_text_render_func;

    scrollable_list_ui_params params;
    std::unique_ptr<scrollable_list> panel;

    refill_callback _refill_cb;
    onclick_callback _onclick_cb;
    onclick_ex_callback _onclick_ex_cb;
    onclick_double_ex_callback _onclick_dbl_ex_cb;
    custom_text_render_func _custom_render_cb;

    virtual void draw(UiFlags flags) override;
    virtual void load(archive elem, element *parent, items &elems) override;
    virtual ~escrollable_list();

    void clear();
    void add_entry(pcstr item);
    void select_entry(pcstr item);
    void onclick_item(onclick_callback lmb) { _onclick_cb = lmb; }
    void onclick_ex_item(onclick_ex_callback lmb) { _onclick_ex_cb = lmb; }
    void onclick_double_ex_item(onclick_double_ex_callback lmb) { _onclick_dbl_ex_cb = lmb; }
    void onrender_item(custom_text_render_func f) { _custom_render_cb = f; }
    void onrefill(refill_callback f) { _refill_cb = f; }
    void refill();

    virtual escrollable_list *dcast_scrollable_list() override { return this; }

    scrollable_list* get_panel() { return panel.get(); }
    const scrollable_list* get_panel() const { return panel.get(); }
};

struct emenu_header_item_proxy : public element {
    menu_item* impl;

    virtual void text(pcstr text) override { if (impl) { impl->text = text; } }
    virtual void set_enabled(bool v) override { if (impl) { impl->hidden = !v; enabled = v; } }
};

struct emenu_header : public element {
    menu_header impl;
    xstring _tooltip;
    e_font _font;

    ~emenu_header();

    virtual void load(archive elem, element *parent, items &elems) override;
            void load_items(archive elem, pcstr section, element::items& elements);
    virtual void draw(UiFlags flags) override;
    virtual void font(int v) override { _font = (e_font)v; }
    virtual void text(pcstr text) override { impl.text = text; }
    virtual const xstring &tooltip() const override { return _tooltip; }
    virtual int text_width() override;
            menu_item &item(int i) { static menu_item dummy; return i < impl.items.size() ? impl.items[i] : dummy; }
            menu_item &item(pcstr key);
            void onclick(std::function<void(menu_item&)> f) { impl._onclick = f; }
    virtual emenu_header *dcast_menu_header() override { return this; }
};

struct egeneric_button : public elabel {
    int mode = 0;
    int param1 = 0;
    int param2 = 0;
    std::function<void(int, int)> _func, _rfunc;
    xstring _tooltip;
    xstring _js_onclick_ref;  // JS function reference for onclick
    xstring _js_textfn_ref;  // JS function reference for text generation
    uint8_t _border;
    bool _hbody;
    bool _split;
    bool _selected = false;

    virtual ~egeneric_button();
    virtual void draw(UiFlags flags) override;
    virtual void load(archive arch, element *parent, items &elems) override;
    virtual void tooltip(textid t) override { _tooltip = ui::str(t); }
    virtual void tooltip(const xstring &t) override { _tooltip = t; }
    virtual void select(bool v) override { _selected = v; }

    virtual element &onclick(std::function<void(int, int)> func) override { _func = func; return *this; }
    virtual element &onrclick(std::function<void(int, int)> func) override { _rfunc = func; return *this; }
};

struct earrow_button : public element {
    bool down;
    bool tiny;

    std::function<void(int, int)> _func;
    xstring _js_onclick_ref;  // JS function reference for onclick
    
    virtual ~earrow_button();
    virtual void load(archive elem, element *parent, items &elems) override;
    virtual void draw(UiFlags flags) override;
    virtual element &onclick(std::function<void(int, int)> func) override { _func = func; return *this; }
};

struct eimage_button : public element {
    float scale = 1.f;
    image_desc img_desc;
    void *icon_texture = nullptr;
    int param1 = 0;
    int param2 = 0;
    img_button_offsets offsets;
    bool _selected = false;
    uint8_t border = 0;
    int texture_id = -1;
    xstring _tooltip;

    std::function<void(int, int)> _func, _rfunc;
    xstring _js_onclick_ref;  // JS function reference for onclick

    virtual ~eimage_button();
    virtual void load(archive elem, element* parent, items &elems) override;
    virtual void select(bool v) override { _selected = v; }
    virtual bool selected() const override { return _selected; }
    virtual void draw(UiFlags flags) override;

    using element::onclick;
    virtual element &onclick(std::function<void(int, int)> func) override { _func = func; return *this; }
    virtual element &onrclick(std::function<void(int, int)> func) override { _rfunc = func; return *this; }
    virtual void tooltip(textid t) override { _tooltip = ui::str(t); }
    virtual void tooltip(const xstring& t) override { _tooltip = t; }
    virtual void image(const image_desc& d) override { img_desc = d; }
    virtual void image(const animation_t& d) override;
    virtual void image(int v) override { img_desc.offset = v; }

    virtual eimage_button *dcast_image_button() override { return this; }
};

struct widget {
    vec2i pos;
    bool check_errors;
    e_font default_font = FONT_INVALID;
    element::items elements;
    widget &ui;
    g_archive_section io;

    virtual void draw(UiFlags flags = UiFlags_None);
    virtual void archive_load(archive arch);
    void load(pcstr section);

    widget() : ui(*this) {}

    bool contains(const xstring &id) const;
    element& operator[](pcstr id);
    inline element &operator[](const bstring32 &id) { return (*this)[id.c_str()]; }
    inline element &operator[](const xstring &id) { return (*this)[id.c_str()]; }

    template<typename ... Args> int label(const Args ... args) { return ui::label(args...); }
    template<typename ... Args> generic_button &button(const Args ... args) { return ui::button(args...); }
    template<typename ... Args> void icon(const Args ... args) { return ui::icon(args...); }
    template<typename ... Args> void img_button(const Args ... args) { return ui::img_button(args...); }
    template<typename ... Args> arrow_button &arw_button(const Args ... args) { return ui::arw_button(args...); }
    inline void image(image_desc img, vec2i pos) { ui::eimage(img, pos); }
    inline void icon(vec2i pos, e_resource img) { ui::icon(pos, img); }

    template<typename T>
    inline void event(const T &ev);
    void event(pcstr evname, const bvariant_map &js_j);

    inline void begin_widget(vec2i offset, bool relative = false) { check_errors = true; ui::begin_widget(offset, relative); }
    inline void end_widget() { ui::end_widget(); }
    void set_clip_rectangle(vec2i pos, vec2i size);
    void set_clip_rectangle(const element &e);
    void reset_clip_rectangle();
    virtual void begin_frame() { ui::begin_frame(); }
    void line(bool hline, vec2i pos, int size, color c = COLOR_BLACK);
    inline void hline(vec2i pos, int size, color c = COLOR_BLACK) { line(true, pos, size, c); }
    inline void vline(vec2i pos, int size, color c = COLOR_BLACK) { line(false, pos, size, c); }
    void rect(vec2i pos, vec2i size, int fill, int color, UiFlags flags = UiFlags_None) { ui::rect(pos, size, fill, color, flags); }

    bool handle_mouse(const mouse *m) { return ui::handle_mouse(m); }

    template<typename T>
    void format_all(const T *o) {
        for (auto &w : elements) {
            bstring1024 formated_text;
            formated_text = format(o, w->format().c_str());
            if (!formated_text.empty()) {
                w->text(formated_text);
            }
        }
    }
};

widget *get_current_widget();

} // ui

ANK_CONFIG_STRUCT(rich_text_t::margin_t, left, top, right, bottom)

void ui_widget_load_elements(archive arch, pcstr section, ui::element *parent, ui::element::items &elements);

template<> 
inline void archive::r<ui::widget>(pcstr name, ui::widget &v) { 
    v.elements.clear();
    v.pos = r_vec2i("pos");
    e_font default_font = r_type<e_font>("default_font", FONT_NORMAL_BLACK_ON_LIGHT);

    ui_widget_load_elements(*this, name, nullptr, v.elements);

    for (auto &e : v.elements) {
        if (e->font() == FONT_INVALID) {
            e->font(default_font);
        }
    }
}
ANK_CONFIG_STRUCT(ui::widget, pos)