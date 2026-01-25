#pragma once

#include "core/tokenum.h"

enum e_labor_category : int8_t {
    LABOR_CATEGORY_INVALID = -1,
    LABOR_CATEGORY_NONE = -1,
    LABOR_CATEGORY_FOOD_PRODUCTION = 0, // todo: wrong index...
    LABOR_CATEGORY_INDUSTRY_COMMERCE = 1,
    LABOR_CATEGORY_ENTERTAINMENT = 2,
    LABOR_CATEGORY_RELIGION = 3,
    LABOR_CATEGORY_EDUCATION = 4,
    LABOR_CATEGORY_WATER_HEALTH = 5,
    LABOR_CATEGORY_INFRASTRUCTURE = 6,
    LABOR_CATEGORY_GOVERNMENT = 7,
    LABOR_CATEGORY_MILITARY = 8,
    LABOR_CATEGORY_CULTURE = 9,
    LABOR_CATEGORY_HOUSE = 10,

    LABOR_CATEGORY_SIZE,
};

using e_labor_category_tokens_t = token_holder<e_labor_category, LABOR_CATEGORY_NONE, LABOR_CATEGORY_SIZE>;
extern const e_labor_category_tokens_t e_labor_category_tokens;