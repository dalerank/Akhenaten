#include "window/window_figure_info.h"

#include "figure/figure.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"
#include "js/js_game.h"

struct figure_enemy_info_window : public figure_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        figure *f = c.figure_get_id() ? figure_get(c) : nullptr;
        return (f && f->type >= FIGURE_ENEMY43_SPEAR
                    && f->type <= FIGURE_ENEMY53_AXE);
    }
};

figure_enemy_info_window figure_enemy_infow;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_enemy_window_info) {
    figure_enemy_infow.load("info_window_figure_enemy");
}

void figure_enemy_info_window::window_info_background(object_info &c) {
    figure_info_window::window_info_background(c);

    figure *f = figure_get(c);
    int formation_id = f->formation_id;

    int image_id = FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[f->type];
    int enemy_type = formation_get(formation_id)->enemy_type;
    switch (f->type) {
    case FIGURE_ENEMY43_SPEAR:
        switch (enemy_type) {
        case ENEMY_5_PERGAMUM:
            image_id = 44;
            break;
        case ENEMY_6_SELEUCID:
            image_id = 46;
            break;
        case ENEMY_7_ETRUSCAN:
            image_id = 32;
            break;
        case ENEMY_8_GREEK:
            image_id = 36;
            break;
        }
        break;
    case FIGURE_ENEMY44_SWORD:
        switch (enemy_type) {
        case ENEMY_5_PERGAMUM:
            image_id = 45;
            break;
        case ENEMY_6_SELEUCID:
            image_id = 47;
            break;
        case ENEMY_9_EGYPTIAN:
            image_id = 29;
            break;
        }
        break;
    case FIGURE_ENEMY45_SWORD:
        switch (enemy_type) {
        case ENEMY_7_ETRUSCAN:
            image_id = 31;
            break;
        case ENEMY_8_GREEK:
            image_id = 37;
            break;
        case ENEMY_10_CARTHAGINIAN:
            image_id = 22;
            break;
        }
        break;
    case FIGURE_ENEMY49_FAST_SWORD:
        switch (enemy_type) {
        case ENEMY_0_BARBARIAN:
            image_id = 21;
            break;
        case ENEMY_1_NUMIDIAN:
            image_id = 20;
            break;
        case ENEMY_4_GOTH:
            image_id = 35;
            break;
        }
        break;
    case FIGURE_ENEMY50_SWORD:
        switch (enemy_type) {
        case ENEMY_2_GAUL:
            image_id = 40;
            break;
        case ENEMY_3_CELT:
            image_id = 24;
            break;
        }
        break;
    case FIGURE_ENEMY51_SPEAR:
        switch (enemy_type) {
        case ENEMY_1_NUMIDIAN:
            image_id = 20;
            break;
        }
        break;
    }

    ui["bigimage"].image(image_id - 1);
    ui["name"] = ui::str(254, f->name);
    ui["type"] = ui::str(37, scenario_property_enemy() + 20);
}
