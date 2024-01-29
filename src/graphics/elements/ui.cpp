#include "ui.h"

#include "button.h"
#include "generic_button.h"
#include "arrow_button.h"
#include "image_button.h"
#include "lang_text.h"
#include "panel.h"
#include "graphics/text.h"
#include "game/game.h"
#include "graphics/boilerplate.h"
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

generic_button &ui::button(pcstr label, vec2i pos, vec2i size, e_font font) {
    const vec2i offset = g_state.offset();

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    button_border_draw(offset.x + pos.x, offset.y + pos.y, size.x, size.y, focused ? 1 : 0);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 4, 20, font, 0);

    return g_state.buttons.back();
}

generic_button &ui::large_button(pcstr label, vec2i pos, vec2i size, e_font font) {
    const vec2i offset = g_state.offset();

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    large_label_draw(offset.x + pos.x, offset.y + pos.y, size.x / 16, focused ? 1 : 0);
    int letter_height = get_letter_height((uint8_t *)"A", font);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 2 + (size.y - letter_height) / 2, size.x, font, 0);

    return g_state.buttons.back();
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

int ui::label(int group, int number, vec2i pos, e_font font, UiFlags_ flags, int box_width) {
    pcstr str = (pcstr)lang_get_string(group, number);
    return label(str, pos, font, flags, box_width);
}

int ui::label(pcstr label, vec2i pos, e_font font, UiFlags_ flags, int box_width) {
    const vec2i offset = g_state.offset();
    if (!!(flags & UiFlags_LabelCentered)) {
        lang_text_draw_centered(label, offset.x + pos.x, offset.y + pos.y, box_width, font);
        return box_width;
    } else {
        return lang_text_draw(label, offset + pos, font);
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

void ui::eimage(e_image_id img, vec2i pos) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, image_group(img), pos);
}

void ui::panel(vec2i pos, vec2i size, UiFlags_ flags) {
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

void ui::outer_panel::draw() {
    ui::panel(pos, size, UiFlags_PanelOuter);
}

void ui::outer_panel::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "outer_panel"));
}

void ui::inner_panel::draw() {
    ui::panel(pos, size, UiFlags_PanelInner);
}

void ui::inner_panel::load(archive arch) {
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
            elm = std::make_shared<outer_panel>();
        } else if (!strcmp(type, "inner_panel")) {
            elm = std::make_shared<inner_panel>();
        } else if (!strcmp(type, "image")) {
            elm = std::make_shared<image>();
        } else if (!strcmp(type, "label")) {
            elm = std::make_shared<elabel>();
        } else if (!strcmp(type, "text")) {
            elm = std::make_shared<etext>();
        } else if (!strcmp(type, "generic_button")) {
            elm = std::make_shared<egeneric_button>();
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

void ui::image::draw() {
    ui::eimage(img, pos);
}

void ui::image::load(archive arch) {
    element::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "image"));
    img = arch.r_image("image");
}

void ui::elabel::draw() {
    if (_body.x > 0) {
        label_draw(pos.x, pos.y, _body.x, _body.y);
    }
    ui::label(_text.c_str(), pos + ((_body.x > 0) ? vec2i{8, 4} : vec2i{0, 0}), _font);
}

void ui::elabel::load(archive arch) {
    element::load(arch);

    _text = arch.r_string("text");
    _font = (e_font)arch.r_int("font", FONT_NORMAL_BLACK_ON_LIGHT);
    _body = arch.r_size2i("body");
}

void ui::elabel::text(pcstr v) {
    _text = v;
    enabled = strlen(v) > 0;
}

void ui::etext::load(archive arch) {
    elabel::load(arch);

    pcstr type = arch.r_string("type");
    assert(!strcmp(type, "text"));
}

void ui::etext::draw() {
    text_draw((uint8_t*)_text.c_str(), pos.x, pos.y, _font, 0);
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
