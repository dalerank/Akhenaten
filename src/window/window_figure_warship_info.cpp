#include "window/window_figure_info.h"

#include "figuretype/figure_war_ship.h"

struct figure_warship_info_window : public figure_info_window_t<figure_warship_info_window> {
    virtual void init(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_warship>();
    }
};

figure_warship_info_window figure_warship_infow;

pcstr button_ids[] = { "hold_position", "engage_nearby", "seek_and_destroy", "repair", "return_to_wharf" };
void figure_warship_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure_warship *f = c.figure_get<figure_warship>();

    for (const pcstr id : button_ids) {
        ui[id].onclick([f, this] (int p1, int p2) {
            const auto &params = f->params();
            f->runtime_data().active_order = p1;
        });
    }
}

void figure_warship_info_window::window_info_background(object_info &c) {
    figure_info_window::window_info_background(c);

    figure_warship *f = c.figure_get<figure_warship>();
    const short order = f->runtime_data().active_order;

    ui["repair"].darkened = (f->base.damage == 0) ? UiFlags_Grayscale : UiFlags_None;
    ui["return_to_wharf"].darkened = (f->base.action_state == FIGURE_ACTION_203_WARSHIP_MOORED) ? UiFlags_Grayscale : UiFlags_None;

    for (const pcstr id : button_ids) {
        auto imgbtn = ui[id].dcast_image_button();
        imgbtn->select(order == imgbtn->param1);
    }

    const auto &orders_info = f->current_params().orders_info;
    auto it = std::find_if(orders_info.begin(), orders_info.end(), [order] (auto &p) { return p.second.id == order; });
    ui["action_header"] = ui::str(c.group_id, it->second.text);
    ui["action_text"] = ui::str(c.group_id, it->second.text + 1);
}