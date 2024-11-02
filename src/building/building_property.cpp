#include "building_property.h"

static id_property_t g_tags;
const id_property_t &tags() {
    return g_tags;
}

const xstring id_property_t::stored = "stored";