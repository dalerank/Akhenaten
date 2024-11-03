#pragma once

#include "core/xstring.h"

struct id_property_t {
    static const xstring stored;
    static const xstring building;
    static const xstring name;
    static const xstring house;
    static const xstring level_name;
};

const id_property_t &tags();