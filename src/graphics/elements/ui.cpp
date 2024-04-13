#include "ui.h"

#include "button.h"
#include "generic_button.h"
#include "arrow_button.h"
#include "image_button.h"
#include "lang_text.h"
#include "panel.h"
#include "graphics/text.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"

#include <stack>

namespace ui {
    struct state {
        std::stack<vec2i> _offset;
        std::vector<generic_button> buttons;
        std::vector<image_button> img_buttons;
        std::vector<arrow_button> arw_buttons;

        inline const vec2i offset() { return _offset.empty() ? vec2i{0, 0} : _offset.top(); }
    };

    state g_state;
    generic_button dummy;
    element dummy_element;
}

void ui::begin_widget(vec2i offset, bool relative) {
    if (relative) {
        vec2i top = g_state._offset.empty() ? vec2i{0, 0} : g_state._offset.top();
        offset += top;
    }
    g_state._offset.push(offset);
}

void ui::begin_frame() {
    g_state._offset = {};
    g_state.buttons.clear();
    g_state.img_buttons.clear();
    g_state.arw_buttons.clear();
}

void ui::end_widget() {
    if (!g_state._offset.empty()) {
        g_state._offset.pop();
    }
}

bool ui::handle_mouse(const mouse *m) {
    bool handle = false;
    int tmp_btn = 0;
    handle |= !!generic_buttons_handle_mouse(m, g_state.offset(), g_state.buttons, tmp_btn);
    handle |= !!image_buttons_handle_mouse(m, g_state.offset(), g_state.img_buttons, tmp_btn);
    handle |= !!arrow_buttons_handle_mouse(m, g_state.offset(), g_state.arw_buttons, tmp_btn);

    return handle;
}

pcstr ui::str(int group, int id) {
    return (pcstr)lang_get_string(group, id);
}

int ui::button_hover(const mouse *m) {
    for (auto &btn : g_state.buttons) {
        if (is_button_hover(btn, g_state.offset())) {
            return (std::distance(&g_state.buttons.front(), &btn) + 1);
        }
    }

    return 0;
}

generic_button &ui::button(pcstr label, vec2i pos, vec2i size, e_font font, std::function<void(int, int)> cb) {
    const vec2i offset = g_state.offset();

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    button_border_draw(offset.x + pos.x, offset.y + pos.y, size.x, size.y, focused ? 1 : 0);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 4, 20, font, 0);

    auto &btn = g_state.buttons.back();
    if (!!cb) {
        btn.onclick(cb);
    }
    return btn;
}

generic_button &ui::large_button(pcstr label, vec2i pos, vec2i size, e_font font) {
    const vec2i offset = g_state.offset();

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    large_label_draw(offset.x + pos.x, offset.y + pos.y, size.x / 16, focused ? 1 : 0);
    int letter_height = get_letter_height((uint8_t *)"A", font);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 2 + (size.y - letter_height) / 2, size.x, font, 0);

    auto &btn = g_state.buttons.back();
    return btn;
}

generic_button &ui::button(uint32_t id) {
    return (id < g_state.buttons.size()) ? g_state.buttons[id] : dummy;
}

image_button &ui::img_button(uint32_t group, uint32_t id, vec2i pos, vec2i size, int offset) {
    const vec2i img_offset = g_state.offset();
    const mouse *m = mouse_get();

    g_state.img_buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, IB_NORMAL, group, id, offset, button_none, button_none, 0, 0, true});
    auto &button = g_state.img_buttons.back();
    button.focused = is_button_hover(g_state.img_buttons.back(), img_offset);
    button.pressed = button.focused && m->left.is_down;
    image_buttons_draw(img_offset, button);

    return g_state.img_buttons.back();
}

image_button &ui::imgok_button(vec2i pos, std::function<void(int, int)> cb) {
    auto &btn = img_button(PACK_GENERAL, 96, pos, {39, 26}, 0);
    btn.onclick(cb);
    return btn;
}

image_button &ui::imgcancel_button(vec2i pos, std::function<void(int, int)> cb) {
    auto &btn = img_button(PACK_GENERAL, 96, pos, {39, 26}, 4);
    btn.onclick(cb);
    return btn;
}

image_button &ui::img_button(e_image_id img, vec2i pos, vec2i size, int offset) {
    image_desc desc = get_image_desc(img);
    return img_button(desc.pack, desc.id, pos, size, desc.offset + offset);
}

int ui::label(int group, int number, vec2i pos, e_font font, UiFlags flags, int box_width) {
    pcstr str = (pcstr)lang_get_string(group, number);
    return label(str, pos, font, flags, box_width);
}

int ui::label(pcstr label, vec2i pos, e_font font, UiFlags flags, int box_width) {
    const vec2i offset = g_state.offset();
    if (!!(flags & UiFlags_LabelCentered)) {
        text_draw_centered((uint8_t*)label, offset.x + pos.x, offset.y + pos.y, box_width, font, 0);
        return box_width;
    } else if (!!(flags & UiFlags_LabelMultiline)) {
        return text_draw_multiline((uint8_t*)label, offset.x + pos.x, offset.y + pos.y, box_width, font, 0);
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

void ui::eimage(e_image_id group, vec2i pos, int img) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    ImageDraw::img_generic(ctx, image_group(group) + img, pos + offset);
}

void ui::eimage(image_desc imgd, vec2i pos) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    ImageDraw::img_generic(ctx, image_group(imgd), pos + offset);
}

void ui::panel(vec2i pos, vec2i size, UiFlags flags) {
    const vec2i offset = g_state.offset();
    if (!!(flags & UiFlags_PanelOuter)) {
        outer_panel_draw(offset + pos, size.x, size.y);
    } else if (!!(flags & UiFlags_PanelInner)) {
        inner_panel_draw(offset + pos, size);
    }
}

void ui::icon(vec2i pos, e_resource img) {
    const vec2i offset = g_state.offset();
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), offset.x + pos.x, offset.y + pos.y);
}

void ui::icon(vec2i pos, e_advisor adv) {
    painter ctx = game.painter();
    const vec2i offset = g_state.offset();
    ImageDraw::img_generic(ctx, image_group(IMG_ADVISOR_ICONS) + (adv - 1), offset.x + pos.x, offset.y + pos.y);
}

arrow_button &ui::arw_button(vec2i pos, bool up, bool tiny) {
    const vec2i offset = g_state.offset();

    g_state.arw_buttons.push_back({pos.x, pos.y, up ? 17 : 15, 24, button_none, 0, 0});
    arrow_buttons_draw(offset, g_state.arw_buttons.back(), tiny);

    return g_state.arw_buttons.back();
}

void ui::element::load(archive arch) {
    pos = arch.r_vec2i("pos");
    size = arch.r_size2i("size");
    enabled = arch.r_bool("enabled", true);
}

pcstr ui::element::text_from_key(pcstr key) {
    return lang_text_from_key(key);
}

void ui::eouter_panel::draw() {
    ui::panel(pos, size, UiFlags_PanelOuter);
}

void ui::eouter_panel::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "outer_panel"));
}

void ui::einner_panel::draw() {
    ui::panel(pos, size, UiFlags_PanelInner);
}

void ui::einner_panel::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "inner_panel"));
}

void ui::widget::draw() {
    for (auto &e : elements) {
        if (e->enabled) {
            e->draw();
        }
    }
}

void ui::widget::load(archive arch) {
    elements.clear();
    arch.r_objects("ui", [this] (pcstr key, archive elem) {
        pcstr type = elem.r_string("type");
        element::ptr elm;
        if (!strcmp(type, "outer_panel")) {
            elm = std::make_shared<eouter_panel>();
        } else if (!strcmp(type, "inner_panel")) {
            elm = std::make_shared<einner_panel>();
        } else if (!strcmp(type, "image")) {
            elm = std::make_shared<eimg>();
        } else if (!strcmp(type, "label")) {
            elm = std::make_shared<elabel>();
        } else if (!strcmp(type, "text")) {
            elm = std::make_shared<etext>();
        } else if (!strcmp(type, "generic_button")) {
            elm = std::make_shared<egeneric_button>();
        } else if (!strcmp(type, "image_button")) {
            elm = std::make_shared<eimage_button>();
        } else if (!strcmp(type, "resource_icon")) {
            elm = std::make_shared<eresource_icon>();
        } else if (!strcmp(type, "large_button")) {
            auto btn = std::make_shared<egeneric_button>();
            btn->mode = 1;
            elm = btn;
        }

        if (elm) {
            elm->id = key;
            elements.push_back(elm);
            elm->load(elem);
        }
    });
}

ui::element& ui::widget::operator[](pcstr id) {
    auto it = std::find_if(elements.begin(), elements.end(), [id] (const auto &e) { return e->id == id; });
    return (it != elements.end() ? **it : ui::dummy_element);
}

void ui::eimg::draw() {
    if (img > 0) {
        ui::eimage(img, pos);
    } else {
        ui::eimage(img_desc, pos);
    }
}

void ui::eimg::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "image"));
    img = arch.r_image("image");
    img_desc.pack = arch.r_int("pack");
    img_desc.id = arch.r_int("id");
    img_desc.offset = arch.r_int("offset");
}

void ui::eresource_icon::draw() {
    ui::eimage(IMG_RESOURCE_ICONS, pos, res);
}

void ui::eresource_icon::image(int image) {
    res = (e_resource)image;
}

void ui::eresource_icon::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "resource_icon"));
    res = arch.r_type<e_resource>("resource");
}

void ui::elabel::draw() {
    if (_body.x > 0) {
        label_draw(pos.x, pos.y, _body.x, _body.y);
    }
    ui::label(_text.c_str(), pos + ((_body.x > 0) ? vec2i{8, 4} : vec2i{0, 0}), _font, _flags, _wrap);
}

void ui::elabel::load(archive arch) {
    element::load(arch);

    _text = arch.r_string("text");
    if (_text[0] == '#') {
        _text = lang_text_from_key(_text.c_str());
    }
    _font = (e_font)arch.r_int("font", FONT_NORMAL_BLACK_ON_LIGHT);
    _body = arch.r_size2i("body");
    _color = arch.r_uint("color");
    _wrap = arch.r_int("wrap");
    pcstr talign = arch.r_string("align");
    bool multiline = arch.r_bool("multiline");
    _flags = (strcmp("center", talign) == 0 ? UiFlags_LabelCentered : UiFlags_None)
               | (multiline ? UiFlags_LabelMultiline : UiFlags_None);
}

void ui::elabel::text(pcstr v) {
    _text = lang_text_from_key(v);
    enabled = !_text.empty();
}

void ui::elabel::color(int v) {
    _color = v;
}

void ui::elabel::font(int v) {
    _font = (e_font)v;
}

void ui::elabel::width(int v) {
    _wrap = v;
}

void ui::eimage_button::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "image_button"));

    img = arch.r_image("image");
    offset = arch.r_int("offset");
}

void ui::eimage_button::draw() {
    ui::img_button(img, pos, size, offset)
        .onclick(_func);
}

void ui::etext::load(archive arch) {
    elabel::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "text"));
}

void ui::etext::draw() {
    const vec2i offset = g_state.offset();
    if (!!(_flags & UiFlags_LabelCentered)) {
        text_draw_centered((uint8_t *)_text.c_str(), offset.x + pos.x, offset.y + pos.y, size.x, _font, _color);
    } else if (!!(_flags & UiFlags_LabelMultiline)) {
        text_draw_multiline((uint8_t *)_text.c_str(), offset.x + pos.x, offset.y + pos.y, _wrap, _font, _color);
    } else {
        text_draw((uint8_t *)_text.c_str(), offset.x + pos.x, offset.y + pos.y, _font, _color);
    }
}

void ui::egeneric_button::draw() {
    switch (mode) {
    case 0:
        ui::button(_text.c_str(), pos, size)
            .onclick(_func);
        break;

    case 1:
        ui::large_button(_text.c_str(), pos, size)
            .onclick(_func);
        break;
    }
}

void ui::egeneric_button::load(archive arch) {
    elabel::load(arch);

    pcstr mode_str = arch.r_string("mode");
    if (mode_str && !strcmp(mode_str, "large")) {
        mode = 1;
    }
}
