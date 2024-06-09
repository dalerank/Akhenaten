#pragma once

#include <cstdint>
#include <memory>

#include "core/vec2i.h"
#include "city/resource.h"

#include "input/hotkey.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/button.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"

#include "js/js_game.h"
#include <functional>

struct mouse;

enum UiFlags_ {
    UiFlags_None = 0,
    UiFlags_LabelCentered = 1 << 1,
    UiFlags_PanelOuter = 1 << 2,
    UiFlags_PanelInner = 1 << 3,
    UiFlags_LabelMultiline = 1 << 4,
};
using UiFlags = int;

namespace ui {

void begin_frame();
void begin_widget(vec2i offset, bool relative = false);
void end_widget();
bool handle_mouse(const mouse *m);

int label(int group, int number, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags flags = UiFlags_None, int box_width = 0);
int label(pcstr, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags flags = UiFlags_None, int box_width = 0);
int label_amount(int group, int number, int amount, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, pcstr postfix = "");
int label_percent(int amount, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT);
void eimage(e_image_id img, vec2i pos, int offset = 0);
void eimage(image_desc img, vec2i pos);
void panel(vec2i pos, vec2i size, UiFlags flags);
void icon(vec2i pos, e_resource img);
void icon(vec2i pos, e_advisor advisor);
int button_hover(const mouse *m);
generic_button &button(pcstr label, vec2i pos, vec2i size, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, std::function<void(int, int)> cb = {});
generic_button &link(pcstr label, vec2i pos, vec2i size, e_font font = FONT_NORMAL_WHITE_ON_DARK, std::function<void(int, int)> cb = {});
generic_button &large_button(pcstr label, vec2i pos, vec2i size, e_font font = FONT_NORMAL_BLACK_ON_LIGHT);
generic_button &button(uint32_t id);
image_button &img_button(uint32_t group, uint32_t id, vec2i pos, vec2i size, int offset = 0);
image_button &imgok_button(vec2i pos, std::function<void(int, int)> cb);
image_button &imgcancel_button(vec2i pos, std::function<void(int, int)> cb);
image_button &img_button(e_image_id img, vec2i pos, vec2i size, int offset = 0);
arrow_button &arw_button(vec2i pos, bool up, bool tiny = false);


pcstr str(int group, int id);
inline pcstr str(std::pair<int, int> r) { return str(r.first, r.second); }

struct element {
    bstring64 id;
    vec2i pos;
    vec2i size;
    bool enabled = true;

    virtual void draw() {}
    virtual void load(archive);
    virtual void text(pcstr) {}
    inline void text(int font, pcstr v) { this->font(font);  this->text(v); }
    virtual void color(int) {}
    virtual void image(int) {}
    virtual image_desc image() const { return {}; }
    virtual void font(int) {}
    virtual void width(int) {}
    virtual void onclick(std::function<void(int, int)>) {}

    pcstr text_from_key(pcstr key);

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

    using ptr = std::shared_ptr<element>;
};

struct eimg : public element {
    e_image_id img;
    image_desc img_desc;

    virtual void draw() override;
    virtual void load(archive elem) override;
    virtual image_desc image() const override { return img_desc; }
};

struct eresource_icon : public element {
    e_resource res;

    virtual void draw() override;
    virtual void image(int image) override;
    virtual void load(archive elem) override;
};

struct eouter_panel : public element {
    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct einner_panel : public element {
    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct elabel : public element {
    std::string _text;
    e_font _font;
    vec2i _body;
    uint32_t _color;
    UiFlags _flags;
    int _wrap;

    virtual void draw() override;
    virtual void load(archive elem) override;
    virtual void text(pcstr) override;
    virtual void color(int) override;
    virtual void font(int) override;
    virtual void width(int) override;
};

struct etext : public elabel {
    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct egeneric_button : public elabel {
    int mode = 0;
    int param1 = 0;
    int param2 = 0;
    std::function<void(int, int)> _func;

    virtual void draw() override;
    virtual void load(archive arch) override;
    virtual void onclick(std::function<void(int, int)> func) override { _func = func; }
};

struct eimage_button : public element {
    e_image_id img;
    int offset;
    std::function<void(int, int)> _func;

    virtual void load(archive elem) override;
    virtual void draw() override;
    virtual void onclick(std::function<void(int, int)> func) override { _func = func; }
};

struct widget {
    std::vector<element::ptr> elements;

    virtual void draw();
    virtual void load(archive arch);

    element& operator[](pcstr id);
    inline element &operator[](const bstring32 &id) { return (*this)[id.c_str()]; }

    inline int label(int group, int number, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags flags = UiFlags_None, int box_width = 0) { return ui::label(group, number, pos, font, flags, box_width); }
    inline void image(image_desc img, vec2i pos) { ui::eimage(img, pos); }
    inline void begin_widget(vec2i offset, bool relative = false) { ui::begin_widget(offset, relative); }
    inline void begin_frame() { ui::begin_frame(); }
};

struct info_window : public widget {
    int resource_text_group;

    void load(pcstr key);
};

} // ui