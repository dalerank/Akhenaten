#include "window/window_figure_info.h"

#include "figuretype/figure_cartpusher.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"

struct figure_carrier_info_window : public figure_info_window_t<figure_carrier_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_cartpusher>();
    }
};

figure_carrier_info_window figure_carrier_infow;

void figure_carrier_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure_cartpusher *f = c.figure_get<figure_cartpusher>();
    
    if (f->action_state() != FIGURE_ACTION_132_DOCKER_IDLING && f->base.resource_id) {
        int resource_img = image_id_resource_icon(f->base.resource_id);
        ui["items"].text_var("@I%u& %u %s %s", resource_img, f->base.resource_amount_full, ui::str(129, 20), ui::str(23, f->base.resource_id));
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
    case ACTION_27_CARTPUSHER_RETURNING:
    case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
    case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
    case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
    case FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE:
    case FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING:
    case FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING:
        is_returning = true;
        break;
    }

    if (c.nfigure.phrase.valid()) {
        pcstr phrase = ui::str(c.nfigure.phrase);
        ui["phrase"] = phrase;
    }
}
