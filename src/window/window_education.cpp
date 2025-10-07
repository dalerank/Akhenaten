#include "window/window_building_info.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"

struct info_window_education : building_info_window_t<info_window_education> {
    using building_info_window::load;
    virtual void load(archive arch, pcstr section) override {
        common_info_window::load(arch, section);
    }

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return building_type_any_of(*b, { BUILDING_ACADEMY, BUILDING_LIBRARY });
    }
};

void info_window_education::init(object_info &c) {
    building_info_window::init(c);

    e_figure_type ftype = FIGURE_NONE;
    e_resource resource = RESOURCE_NONE;

    building *b = c.building_get();
    switch (b->type) {
    case BUILDING_ACADEMY: ftype = FIGURE_SCRIBER; break;
    case BUILDING_LIBRARY: ftype = FIGURE_LIBRARIAN; break;
    }

    vec2i text_res{ 0, 0 };
    vec2i icon_res{ 0, 0 };

    painter ctx = game.painter();

    const auto &meta = b->dcast()->get_info();
    c.help_id = meta.help_id;

    ui["resource_icon"].image(b->input.resource);
    ui["resource_stored"] = bstring32(b->stored_amount());

    textid text{ meta.text_id, 1 };
    if (ftype != FIGURE_NONE && b->has_figure_of_type(BUILDING_SLOT_SERVICE, ftype)) {
        text.id = 1;
    } else if (!b->has_road_access) {
        text = { e_text_building, e_text_building_no_roads };
    } else if (b->num_workers <= 0) {
        text.id = 2;
    } else {
        text.id = 3;
    }

    ui["warning_text"] = text;
}