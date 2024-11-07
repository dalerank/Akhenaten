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

    building *b = c.building_get();
    const auto &params = b->dcast()->params();

    window_building_play_sound(&c, b->get_sound());

    textid workers_desc = { c.group_id, 0 };
    if (!c.has_road_access) {
        workers_desc = { 69, 25 };
    } else if (b->num_workers <= 0) {
        workers_desc.id = 10;
    } else if (!b->data.entertainment.num_shows) {
        workers_desc.id = 2;
    } else if (b->data.entertainment.num_shows == 2) {
        workers_desc.id = 3;
    } else if (b->data.entertainment.dancer_visited && b->data.entertainment.juggler_visited && !b->data.entertainment.musician_visited) {
        workers_desc.id = 5;
    } else if (b->data.entertainment.dancer_visited && b->data.entertainment.musician_visited && !b->data.entertainment.juggler_visited) {
        workers_desc.id = 4;
    } else if (!b->data.entertainment.dancer_visited && b->data.entertainment.musician_visited && b->data.entertainment.juggler_visited) {
        workers_desc.id = 6;
    } else if (b->data.entertainment.juggler_visited && !b->data.entertainment.dancer_visited && !b->data.entertainment.musician_visited) {
        workers_desc.id = 7;
    } else if (b->data.entertainment.musician_visited && (!b->data.entertainment.dancer_visited || !b->data.entertainment.juggler_visited)) {
        workers_desc.id = 8;
    } else if (b->data.entertainment.musician_visited && !b->data.entertainment.juggler_visited) {
        workers_desc.id = 9;
    }

    if (b->data.entertainment.juggler_visited > 0) {
        ui["play_text"].text_var("%s %s %d", ui::str(c.group_id, 12), ui::str(8, 44), b->data.entertainment.juggler_visited);
    } else {
        ui["play_text"] = ui::str(c.group_id, 11);
    }

    if (b->data.entertainment.musician_visited > 0) {
        ui["play2_text"].text_var("%s %s %d\n%s", ui::str(c.group_id, 14), ui::str(8, 44), b->data.entertainment.musician_visited, ui::str(72, 7 + b->data.entertainment.play_index));
    } else {
        ui["play2_text"] = ui::str(c.group_id, 13);
    }

    if (b->data.entertainment.dancer_visited > 0) {
        ui["play3_text"].text_var("%s %s %d", ui::str(c.group_id, 16), ui::str(8, 44), b->data.entertainment.musician_visited);
    } else {
        ui["play3_text"] = ui::str(c.group_id, 15);
    }

    ui["workers_desc"] = workers_desc;
    fill_employment_details(c);
}
