#include "graphics/elements/ui.h"

#include "window/building/common.h"
#include "window/window_building_info.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"

struct workshop_info_window : public building_info_window_t<workshop_info_window> {
    virtual void init(object_info &c) override {
        building_info_window::init(c);

        building *b = c.building_get();
        if (!b->is_workshop()) {
            return;
        }
    
        window_building_play_sound(&c, b->get_sound());

        textid trouble_text{ c.group_id, 0 };
        if (!b->has_road_access) { trouble_text = {69, 25}; }
        else if (g_city.resource.is_mothballed(b->output.resource)) { trouble_text.id = 4; }
        else if (b->num_workers <= 0) { trouble_text.id = 5; }
        else if (!b->workshop_has_resources()) { trouble_text.id = 11; }
        else { trouble_text.id = approximate_value(b->worker_percentage() / 100.f, make_array(10, 9, 8, 7, 6)); }

        ui["workers_desc"].text(trouble_text);
    }
};

struct brickworks_info_window : public building_info_window_t<brickworks_info_window> {
    virtual void init(object_info &c) override {
        building_info_window::init(c);

        building *b = c.building_get();
        if (!b->is_workshop()) {
            return;
        }
    
        window_building_play_sound(&c, b->get_sound());

        textid trouble_text{ c.group_id, 0 };
        if (!b->has_road_access) { trouble_text = {69, 25}; }
        else if (g_city.resource.is_mothballed(b->output.resource)) { trouble_text.id = 4; }
        else if (b->num_workers <= 0) { trouble_text.id = 5; }
        else if (!b->workshop_has_resources()) { trouble_text.id = 11; }
        else { trouble_text.id = approximate_value(b->worker_percentage() / 100.f, make_array(10, 9, 8, 7, 6)); }

        ui["workers_desc"].text(trouble_text);

        if (b->stored_amount(RESOURCE_CLAY) <= 0) {
            ui["warning_text"] = textid{ c.group_id, 11 };
        } else if (b->stored_amount(RESOURCE_STRAW) <= 0) {
            ui["warning_text"] = textid{ c.group_id, 11 };
        } else {
            ui["warning_text"] = textid{ c.group_id, 1 };
        }
    }
};

workshop_info_window workshop_infow;
brickworks_info_window brickworks_infow;

void building_workshop_draw_foreground(object_info &c) {
    workshop_infow.draw();
    window_building_draw_employment(&c, 142);
}
