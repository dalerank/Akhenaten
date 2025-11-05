#include "window_building_info.h"

#include "building/building_bandstand.h"
#include "city/object_info.h"
#include "window/building/common.h"

struct info_window_entertainment : public building_info_window_t<info_window_entertainment>{
    virtual void init(object_info &c) override;
};

struct info_window_bandstand : public building_info_window_t<info_window_bandstand>{
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_bandstand();
    }
};

struct info_window_booth : public building_info_window_t<info_window_booth> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return c.building_get()->dcast_booth();
    }
};

info_window_entertainment entertainment_infow;
info_window_bandstand bandstand_infow;
info_window_booth booth_infow;

void info_window_entertainment::init(object_info &c) {
    c.go_to_advisor.first = ADVISOR_ENTERTAINMENT;

    building_info_window::init(c);

    building *b = c.building_get();

    textid reason = {c.group_id, 0};
    if (!b->has_road_access) { reason = {69, 25}; }
    else if (b->num_workers <= 0) { reason.id = 7; }

    int workers_text = approximate_value(b->worker_percentage() / 100.f, make_array(5, 4, 3, 2));
    ui["workers_desc"] = ui::str(c.group_id, workers_text);

    bstring256 warning_text = ui::str(c.group_id, 1);
    if (reason.id) {
        warning_text.append(ui::str(reason));
    }
    ui["warning_text"] = warning_text;
}

void info_window_bandstand::init(object_info &c) {
    building_info_window::init(c);

    auto band = c.building_get<building_bandstand>();
    const auto &d = band->runtime_data();

    textid reason{ c.group_id, 1 };
    if (!band->has_road_access()) { reason = { 69, 25 }; } 
    else if (band->num_workers() <= 0) { reason.id = 6; } 
    else if (!d.num_shows) { reason.id = 2; }
    else if (d.num_shows == 2) { reason.id = 3; } 
    else if (d.juggler_visited) { reason.id = 5; } 
    else if (d.musician_visited) { reason.id = 4; }

    ui["warning_text"] = ui::str(reason);

    if (d.juggler_visited > 0) {
        ui["play_text"].text_var("%s %s %d", ui::str(c.group_id, 10), ui::str(8, 44), d.juggler_visited);
    } else {
        ui["play_text"] = ui::str(c.group_id, 9);
    }
  
    if (d.musician_visited > 0) {
        ui["play2_text"].text_var("%s %s %d\n%s", ui::str(c.group_id, 8), ui::str(8, 44), d.musician_visited, ui::str(72, 7 + d.play_index));
    } else {
        ui["play2_text"] = ui::str(c.group_id, 7);
    }
}

void info_window_booth::init(object_info &c) {
    building_info_window::init(c);

    auto band = c.building_get<building_bandstand>();
    if (!band) {
        return;
    }

    const auto &d = band->runtime_data();

    textid reason{ c.group_id, 1 };
    if (!band->has_road_access()) { reason = {69, 25}; } 
    else if (band->num_workers() <= 0) { reason.id = 4; }
    else if (!d.num_shows) { reason.id = 2; }
    else if (d.juggler_visited) { reason.id = 3; }

    ui["warning_text"] = ui::str(reason);

    if (d.juggler_visited > 0) {
        ui["play_text"].text_var("%s %s %d", ui::str(c.group_id, 6), ui::str(8, 44), d.juggler_visited);
    } else {
        ui["play_text"] = ui::str(c.group_id, 5);
    }
}
