#pragma once

#include "building/building_type.h"

/**
 * Building model
 */
struct model_building {
    int cost;                   /**< Cost of structure or of one tile of a structure (for walls) */
    int desirability_value;     /**< Initial desirability value */
    int desirability_step;      /**< Desirability step (in tiles) */
    int desirability_step_size; /**< Desirability step size */
    int desirability_range;     /**< Max desirability range */
    int laborers;               /**< Number of people a building employs */
    // pharaoh
    int fire_risk;
    int damage_risk;
};

/**
 * House model
 */
struct model_house {
    int devolve_desirability; /**< Desirability at which the house devolves */
    int evolve_desirability;  /**< Desirability at which the house evolves */
    int entertainment;        /**< Entertainment points required */
    int water;                /**< Water required: 1 = well, 2 = fountain */
    int religion;             /**< Number of gods required */
    int education;            /**< Education required: 1 = school or library, 2 = school and library, 3 = school, library and academy */
    int food;                 /**< Food required (boolean) */
    int dentist;              /**< dentist required (boolean) */
    int physician;            /**< physician required (boolean) */
    int health;               /**< Health required: 1 = dentist or physician, 2 = dentist and physician, 3 = dentist, physician and mortuary */
    int food_types;           /**< Number of food types required */
    int pottery;              /**< Pottery required */
    int linen;                /**< Linen required */
    int jewelry;              /**< Jewelry required */
    int beer;                 /**< Beer types required: 1 = any wine, 2 = two types of wine */

    // pharaoh
    int crime_risk;
    int crime_risk_base;
    
    //
    int prosperity;           /**< Prosperity contribution */
    int max_people;           /**< Maximum people per tile (medium insula and lower) or per house (large insula and up) */
    int tax_multiplier;       /**< Tax rate multiplier */

    // pharaoh
    int malaria_risk;
    int disease_risk;
};

bool model_load();
const model_building* model_get_building(int type);
const model_house& model_get_house(int level);
