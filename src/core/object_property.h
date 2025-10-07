#pragma once

#include "core/xstring.h"

struct id_property_t {
    static const xstring stored;
    static const xstring building;
    static const xstring figure;
    static const xstring city;
    static const xstring finance;
    static const xstring rating;
    static const xstring model;
    static const xstring farm;
    static const xstring name;
    static const xstring class_name;
    static const xstring city_name;
    static const xstring action_tip;
    static const xstring home;
    static const xstring laborers;
    static const xstring house;
    static const xstring level_name;
    static const xstring text;
    static const xstring industry;
    static const xstring progress;
    static const xstring tax_income_or_storage;
    static const xstring num_workers;
    static const xstring output_resource;
    static const xstring second_output_resource;
    static const xstring first_material;
    static const xstring second_material;
    static const xstring second_material_stored;
    static const xstring first_material_stored;
    static const xstring tax_percentage;
    static const xstring total_stored;
    static const xstring free_space;
    static const xstring treasury;
    static const xstring culture;
    static const xstring prosperity;
    static const xstring monument;
    static const xstring kingdom;
    static const xstring fertility;
    static const xstring player;
    static const xstring capacity;
};

const id_property_t &tags();