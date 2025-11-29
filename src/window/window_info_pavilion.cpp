#include "window/window_building_info.h"

#include "building/building_pavilion.h"
#include "window/building/common.h"
#include "city/object_info.h"

struct info_window_pavilion : public building_info_window_t<info_window_pavilion> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_pavilion();
    }
};

info_window_pavilion pavilion_infow;

void info_window_pavilion::init(object_info &c) {
    building_info_window::init(c);

    auto ent = c.building_get<building_entertainment>();
    const auto &params = ent->current_params();

    window_building_play_sound(&c, ent->get_sound());

    textid workers_desc = { c.group_id, 0 };
    auto &d = ent->runtime_data();
    if (!ent->has_road_access()) {
        workers_desc = { 69, 25 };
    } else if (ent->num_workers() <= 0) {
        workers_desc.id = 10;
    } else if (!d.num_shows) {
        workers_desc.id = 2;
    } else if (d.num_shows == 2) {
        workers_desc.id = 3;
    } else if (d.dancer_visited && d.juggler_visited && !d.musician_visited) {
        workers_desc.id = 5;
    } else if (d.dancer_visited && d.musician_visited && !d.juggler_visited) {
        workers_desc.id = 4;
    } else if (!d.dancer_visited && d.musician_visited && d.juggler_visited) {
        workers_desc.id = 6;
    } else if (d.juggler_visited && !d.dancer_visited && !d.musician_visited) {
        workers_desc.id = 7;
    } else if (d.musician_visited && (!d.dancer_visited || !d.juggler_visited)) {
        workers_desc.id = 8;
    } else if (d.musician_visited && !d.juggler_visited) {
        workers_desc.id = 9;
    }

    if (d.juggler_visited > 0) {
        ui["play_text"].text_var("%s %s %d", ui::str(c.group_id, 12), ui::str(8, 44), d.juggler_visited);
    } else {
        ui["play_text"] = ui::str(c.group_id, 11);
    }

    if (d.musician_visited > 0) {
        ui["play2_text"].text_var("%s %s %d\n%s", ui::str(c.group_id, 14), ui::str(8, 44), d.musician_visited, ui::str(72, 7 + d.play_index));
    } else {
        ui["play2_text"] = ui::str(c.group_id, 13);
    }

    if (d.dancer_visited > 0) {
        ui["play3_text"].text_var("%s %s %d", ui::str(c.group_id, 16), ui::str(8, 44), d.dancer_visited);
    } else {
        ui["play3_text"] = ui::str(c.group_id, 15);
    }

    ui["workers_desc"] = workers_desc;
}
