#pragma once

#include "window_info.h"
#include "core/typename.h"

class building;

struct building_info_window : public common_info_window {
    e_advisor first_advisor = ADVISOR_NONE;
    svector<e_building_type, 8> related_buildings;
    xstring help_id;

    building_info_window();

    using widget::archive_load;
    virtual void archive_load(archive arch) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual textid get_tooltip(object_info &c) override;
    
    virtual void init(object_info &c) override;
    virtual void update_buttons(object_info &c) override;
    virtual bool check(object_info &c) override {
        auto b = c.building_get();
        return building_type_any_of(b->type, related_buildings);
    }

    building *building_get(object_info &c);

    void common_info_background(object_info& c);
};

template<typename T>
struct building_info_window_t : public building_info_window {
    virtual pcstr section() const override {
        static type_name_holder<T> _impl;
        static pcstr _section = type_simplified_name(_impl.value.data());
        return _section;
    }
};