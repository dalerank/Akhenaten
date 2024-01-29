#pragma once

#include <cstdint>
#include <memory>

#include "core/vec2i.h"
#include "city/resource.h"

#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"

#include "js/js_game.h"

struct mouse;

enum UiFlags_ {
    UiFlags_None = 0,
    UiFlags_LabelCentered = 1 << 1,
    UiFlags_PanelOuter = 1 << 2,
    UiFlags_PanelInner = 1 << 3,
};

namespace ui {

void begin_frame();
void begin_widget(vec2i offset, bool relative = false);
void end_widget();
bool handle_mouse(const mouse *m);

int label(int group, int number, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_ flags = UiFlags_None, int box_width = 0);
int label(pcstr, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_ flags = UiFlags_None, int box_width = 0);
int label_amount(int group, int number, int amount, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT, pcstr postfix = "");
int label_percent(int amount, vec2i pos, e_font font = FONT_NORMAL_BLACK_ON_LIGHT);
void eimage(e_image_id img, vec2i pos);
void panel(vec2i pos, vec2i size, UiFlags_ flags);
void icon(vec2i pos, e_resource img);
void icon(vec2i pos, e_advisor advisor);

pcstr str(int group, int id);

struct element {
    bstring64 id;
    vec2i pos;
    vec2i size;
    bool enabled = true;

    virtual void draw() {}
    virtual void load(archive);
    virtual void text(pcstr) {}

    template<class ... Args>
    inline void text_var(pcstr fmt, const Args&... args) { text(bstring512().printf(fmt, args...)); }

    using ptr = std::shared_ptr<element>;
};

struct image : public element {
    e_image_id img;

    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct outer_panel : public element {
    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct inner_panel : public element {
    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct elabel : public element {
    std::string _text;
    e_font _font;
    vec2i _body;

    virtual void draw() override;
    virtual void load(archive elem) override;
    virtual void text(pcstr) override;
};

struct etext : public elabel {
    virtual void draw() override;
    virtual void load(archive elem) override;
};

struct widget {
    std::vector<element::ptr> elements;

    virtual void draw();
    virtual void load(archive arch);

    element& operator[](pcstr id);
};

} // ui