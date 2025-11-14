#include "window/window_figure_info.h"

#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_storageyard_cart.h"
#include "figuretype/figure_docker.h"
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
    
    if (f->action_state() != ACTION_132_DOCKER_IDLING && f->base.resource_id) {
        int resource_img = image_id_resource_icon(f->base.resource_id);
        ui["items"].text_var("@I%u& %u %s %s", resource_img, f->base.resource_amount_full, ui::str(129, 20), ui::str(23, f->base.resource_id));
    }

    if (!f->base.has_home()) {
        return;
    }

    building *source_building = f->home();
    building *target_building = f->destination();

    ui["phrase"] = f->phrase_key();
}
