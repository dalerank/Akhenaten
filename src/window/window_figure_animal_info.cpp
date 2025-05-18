#include "window/window_figure_info.h"

#include "figure/figure.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"
#include "js/js_game.h"

struct figure_animal_info_window : public figure_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.figure_get_id() && figure_get(c)->is_herd();
    }
};

figure_animal_info_window figure_animal_infow;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_animal_window_info) {
    figure_animal_infow.load("info_window_figure_animal");
}

void figure_animal_info_window::window_info_background(object_info &c) {
    figure_info_window::window_info_background(c);

    int figure_id = map_figure_id_get(c.grid_offset);
    figure *f = ::figure_get(figure_id);

    ui["bigimage"].image(f->type);
    ui["type"] = ui::str(64, f->type);
}