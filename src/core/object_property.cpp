#include "object_property.h"

static id_property_t g_tags;
const id_property_t &tags() {
    return g_tags;
}

const xstring id_property_t::stored = "stored";
const xstring id_property_t::building = "building";
const xstring id_property_t::city = "city";
const xstring id_property_t::finance = "finance";
const xstring id_property_t::rating = "rating";
const xstring id_property_t::figure = "figure";
const xstring id_property_t::model = "model";
const xstring id_property_t::farm = "farm";
const xstring id_property_t::name = "name";
const xstring id_property_t::class_name = "class_name";
const xstring id_property_t::city_name = "city_name";
const xstring id_property_t::action_tip = "action_tip";
const xstring id_property_t::home = "home";
const xstring id_property_t::laborers = "laborers";
const xstring id_property_t::house = "house";
const xstring id_property_t::level_name = "level_name";
const xstring id_property_t::text = "text";
const xstring id_property_t::industry = "industry";
const xstring id_property_t::progress = "progress";
const xstring id_property_t::tax_income_or_storage = "tax_income_or_storage";
const xstring id_property_t::num_workers = "num_workers";
const xstring id_property_t::output_resource = "output_resource";
const xstring id_property_t::second_output_resource = "second_output_resource";
const xstring id_property_t::first_material = "first_material";
const xstring id_property_t::second_material = "second_material";
const xstring id_property_t::first_material_stored = "first_material_stored";
const xstring id_property_t::second_material_stored = "second_material_stored";
const xstring id_property_t::tax_percentage = "tax_percentage";
const xstring id_property_t::total_stored = "total_stored";
const xstring id_property_t::free_space = "free_space";
const xstring id_property_t::culture = "culture";
const xstring id_property_t::prosperity = "prosperity";
const xstring id_property_t::monument = "monument";
const xstring id_property_t::kingdom = "kingdom";
const xstring id_property_t::fertility = "fertility";
const xstring id_property_t::player = "player";
const xstring id_property_t::capacity = "capacity";