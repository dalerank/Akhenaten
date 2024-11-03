#include "building_property.h"

static id_property_t g_tags;
const id_property_t &tags() {
    return g_tags;
}

const xstring id_property_t::stored = "stored";
const xstring id_property_t::building = "building";
const xstring id_property_t::name = "name";
const xstring id_property_t::house = "house";
const xstring id_property_t::level_name = "level_name";
const xstring id_property_t::text = "text";
const xstring id_property_t::industry = "industry";
const xstring id_property_t::progress = "progress";
const xstring id_property_t::tax_income_or_storage = "tax_income_or_storage";