#include "window/window_figure_info.h"

#include "figuretype/figure_cartpusher.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"

struct figure_carrier_info_window : public figure_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return figure_get(c)->dcast_cartpusher();
    }
};

figure_carrier_info_window figure_carrier_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_carrier_window_info);
void config_load_figure_carrier_window_info() {
    figure_carrier_infow.load("info_window_figure_carrier");
}

void figure_carrier_info_window::window_info_background(object_info &c) {
    figure_info_window::window_info_background(c);

    figure_cartpusher *f = c.figure_get()->dcast_cartpusher();
    
    bstring256 home_text;
    if (f->base.has_home()) {
        home_text = ui::str(41, f->home()->type);
    }
    bstring256 type_str = ui::str(64, f->type());
    ui["type"].text_var("%s %s", home_text.c_str(), type_str.c_str());

    if (f->action_state() != FIGURE_ACTION_132_DOCKER_IDLING && f->base.resource_id) {
        int resource_img = image_id_resource_icon(f->base.resource_id);
        ui["items"].text_var("@Y%u& %u %s %s", resource_img, f->base.resource_amount_full, ui::str(129, 20), ui::str(23, f->base.resource_id));
    }

    //    int phrase_height = lang_text_draw_multiline(130, 21 * c->figure.sound_id + c->figure.phrase_id + 1,
    //                                                 c->offset.x + 90, c->offset.y + 160, 16 * (c->width_blocks - 8),
    //                                                 FONT_NORMAL_GREEN);

    if (!f->base.has_home()) {
        return;
    }

    building *source_building = f->home();
    building *target_building = f->destination();
    bool is_returning = false;
    switch (f->action_state()) {
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_27_CARTPUSHER_RETURNING:
    case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
    case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
    case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
    case FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE:
    case FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING:
    case FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING:
        is_returning = true;
        break;
    }

    if (c.nfigure.phrase_group > 0 && c.nfigure.phrase_id >= 0) {
        ui["phrase"] = ui::str(c.nfigure.phrase_group, c.nfigure.phrase_id);
    }
}
