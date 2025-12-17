#include "window/window_figure_info.h"

#include "figure/figure.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"
#include "js/js_game.h"

struct figure_enemy_info_window : public figure_info_window_t<figure_enemy_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        figure *f = c.figure_get();
        return f && f->is_enemy();
    }
};

figure_enemy_info_window figure_enemy_infow;

void figure_enemy_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure *f = figure_get(c);
    int formation_id = f->formation_id;

    ui["bigimage"].image(f->anim(animkeys().big_image));
}
