#include "window/window_figure_info.h"
#include "window/window_city.h"

#include "figuretype/figure_war_ship.h"
#include "input/mouse.h"
#include "graphics/image.h"
#include "graphics/elements/button.h"

struct figure_warship_info_window : public figure_info_window_t<figure_warship_info_window> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_warship>();
    }
};

figure_warship_info_window figure_warship_infow;

pcstr button_ids[] = { "hold_position", "engage_nearby", "seek_and_destroy", "repair", "return_to_wharf" };

static int hull_strength_text_id(figure_warship *f) {
    const int max_dmg = f->base.max_damage();
    if (max_dmg <= 0) {
        return 3;
    }
    const int health_pct = 100 - (f->base.damage * 100 / max_dmg);
    if (health_pct >= 90) return 3; // Very strong
    if (health_pct >= 70) return 4; // Strong
    if (health_pct >= 50) return 5; // Good
    if (health_pct >= 30) return 6; // Average
    if (health_pct >= 10) return 7; // Fair
    return 8;                        // Weak
}

static vec2i resolve_button_size(ui::eimage_button *imgbtn) {
    if (imgbtn->size.x > 0 && imgbtn->size.y > 0) {
        return imgbtn->size;
    }
    const image_t *img = image_get(imgbtn->img_desc);
    if (img && img->width > 0 && img->height > 0) {
        return vec2i{img->width, img->height};
    }
    // Fallback: button slot width is 87 in the layout, height ~60 for command buttons.
    return vec2i{87, 60};
}

void figure_warship_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure_warship *f = c.figure_get<figure_warship>();

    for (const pcstr id : button_ids) {
        ui[id].onclick([f] (int p1, int p2) {
            f->runtime_data().active_order = p1;
            window_city_show();
        });
    }
}

void figure_warship_info_window::window_info_background(object_info &c) {
    figure_info_window::window_info_background(c);

    figure_warship *f = c.figure_get<figure_warship>();
    const short order = f->runtime_data().active_order;

    ui["repair"].darkened = (f->base.damage == 0) ? UiFlags_Grayscale : UiFlags_None;
    ui["return_to_wharf"].darkened = (f->base.action_state == ACTION_203_WARSHIP_MOORED) ? UiFlags_Grayscale : UiFlags_None;

    ui["hullstrength_val"].text_var("%s", ui::str(c.group_id, hull_strength_text_id(f)));
    // Crew fatigue mechanic isn't simulated yet — display "Rested" as a placeholder.
    ui["crewfatique_val"].text_var("%s", ui::str(c.group_id, 28));

    const mouse &m = mouse::get();
    int hovered_param1 = 0;
    for (const pcstr id : button_ids) {
        auto imgbtn = ui[id].dcast_image_button();
        imgbtn->select(order == imgbtn->param1);
        const vec2i sz = resolve_button_size(imgbtn);
        const vec2i btn_screen = c.offset + imgbtn->pos;
        if (m.x >= btn_screen.x && m.x < btn_screen.x + sz.x
            && m.y >= btn_screen.y && m.y < btn_screen.y + sz.y
            && !hovered_param1) {
            hovered_param1 = imgbtn->param1;
        }
    }

    // Show description for the hovered button if any, otherwise the active order's description.
    const int display_order = hovered_param1 ? hovered_param1 : order;
    const auto &orders_info = f->current_params().orders_info;
    auto it = std::find_if(orders_info.begin(), orders_info.end(), [display_order] (auto &p) { return p.second.id == display_order; });
    if (it != orders_info.end()) {
        ui["action_header"].text_var("%s", ui::str(c.group_id, it->second.text));
        ui["action_text"].text_var("%s", ui::str(c.group_id, it->second.text + 1));
    } else if (display_order == figure_warship::e_order_move_to_tile) {
        ui["action_header"].text_var("%s", "Moving to position");
        ui["action_text"].text_var("%s", "The ship is sailing to the position you designated and will hold there until ordered otherwise.");
    } else {
        ui["action_header"].text_var("%s", "");
        ui["action_text"].text_var("%s", "");
    }
}

void figure_warship_info_window::window_info_foreground(object_info &c) {
    figure_info_window::window_info_foreground(c);

    // Draw a focus border around whichever order button the cursor is over.
    // Queue via ui::push so it draws on top of the buttons during the deferred flush.
    const mouse &m = mouse::get();
    for (const pcstr id : button_ids) {
        auto imgbtn = ui[id].dcast_image_button();
        if (!imgbtn) {
            continue;
        }
        const vec2i sz = resolve_button_size(imgbtn);
        const vec2i btn_screen = c.offset + imgbtn->pos;
        const bool over = m.x >= btn_screen.x && m.x < btn_screen.x + sz.x
                       && m.y >= btn_screen.y && m.y < btn_screen.y + sz.y;
        if (over) {
            using namespace ui::opt;
            ui::push(ui::cmd_t::button_border,
                     Pos{btn_screen - vec2i{4, 4}},
                     Size{sz + vec2i{8, 8}},
                     ImgFlagsTag{ImgFlag_Alpha});
            break;
        }
    }
}