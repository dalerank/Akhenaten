#pragma once

#include "building/building.h"
#include "city/warning.h"

struct event_construction_warning { xstring id; };

struct city_warning_manager {
    bool has_warning = false;

    void init();
};

struct construction_warnings {
    svector<xstring, 8> warnings;

    template<typename... Args>
    construction_warnings(Args... args) : warnings{args...} {}

    ~construction_warnings();

    void add(xstring id) {
        warnings.push_back(id);
    }

    void add_if(bool condition, xstring id) {
        if (condition) {
            add(id);
        }
    }
};

extern city_warning_manager g_warning_manager;

void building_construction_warning_generic_checks(building *b, tile2i tile, int size, int orientation);