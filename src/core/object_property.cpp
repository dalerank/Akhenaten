#include "object_property.h"

static id_property_t g_tags;
const id_property_t &tags() {
    return g_tags;
}

const xstring id_property_t::stored = "stored";
const xstring id_property_t::building = "building";
const xstring id_property_t::city = "city";
const xstring id_property_t::figure = "figure";
const xstring id_property_t::model = "model";
const xstring id_property_t::name = "name";
const xstring id_property_t::class_name = "class_name";
const xstring id_property_t::laborers = "laborers";
const xstring id_property_t::house = "house";
const xstring id_property_t::level_name = "level_name";
const xstring id_property_t::text = "text";
const xstring id_property_t::industry = "industry";
const xstring id_property_t::progress = "progress";
const xstring id_property_t::tax_income_or_storage = "tax_income_or_storage";
const xstring id_property_t::num_workers = "num_workers";
const xstring id_property_t::output_resource = "output_resource";
const xstring id_property_t::first_material = "first_material";
const xstring id_property_t::first_material_stored = "first_material_stored";
const xstring id_property_t::tax_percentage = "tax_percentage";
const xstring id_property_t::total_stored = "total_stored";
const xstring id_property_t::free_space = "free_space";