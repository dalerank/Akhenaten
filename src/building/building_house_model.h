#pragma once

#include "building/building_type.h"
#include "game/difficulty.h"

/**
 * House model
 */
struct model_house {
    int8_dcy devolve_desirability; /**< Desirability at which the house devolves */
    int8_dcy evolve_desirability;  /**< Desirability at which the house evolves */
    int8_dcy entertainment;        /**< Entertainment points required */
    int8_dcy water;                /**< Water required: 1 = well, 2 = fountain */
    int8_dcy religion;             /**< Number of gods required */
    int8_dcy education;            /**< Education required: 1 = school or library, 2 = school and library, 3 = school, library and academy */
    int8_dcy food;                 /**< Food required (boolean) */
    int8_dcy dentist;              /**< dentist required (boolean) */
    int8_dcy physician;            /**< physician required (boolean) */
    int8_dcy health;               /**< Health required: 1 = dentist or physician, 2 = dentist and physician, 3 = dentist, physician and mortuary */
    int8_dcy food_types;           /**< Number of food types required */
    int8_dcy food_consumption_percentage; /**< Percentage of food consumption */
    int8_dcy pottery;              /**< Pottery required */
    int8_dcy linen;                /**< Linen required */
    int8_dcy jewelry;              /**< Jewelry required */
    int8_dcy beer;                 /**< Beer types required: 1 = any wine, 2 = two types of wine */
    int8_dcy food_storage_multiplier;      /**< Multiplier for stored goods */

    // pharaoh
    int8_dcy crime_risk;
    int8_dcy crime_risk_base;

    //
    int8_dcy prosperity;           /**< Prosperity contribution */
    int8_dcy max_people;           /**< Maximum people per tile (medium insula and lower) or per house (large insula and up) */
    int8_dcy tax_multiplier;       /**< Tax rate multiplier */

    // pharaoh
    int8_dcy malaria_risk;
    int8_dcy disease_risk;

    int8_t fancy_bazaar;
    int8_dcy devolve_delay;        /**< Number of ticks before house devolves (delay) */
};
ANK_CONFIG_STRUCT(model_house, devolve_desirability,
    evolve_desirability, entertainment, water, religion,
    education, food, dentist, physician, health, 
    food_types, food_consumption_percentage,
    pottery, linen, jewelry, beer, food_storage_multiplier,
    crime_risk, crime_risk_base,
    prosperity, max_people, tax_multiplier, malaria_risk, disease_risk,
    fancy_bazaar, devolve_delay)