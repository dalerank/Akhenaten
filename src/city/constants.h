#pragma once

#include <cstdint>
#include "core/tokenum.h"

enum e_advisor : uint8_t {
    ADVISOR_NONE = 0,
    ADVISOR_LABOR = 1,
    ADVISOR_MILITARY = 2,
    ADVISOR_IMPERIAL = 3,
    ADVISOR_RATINGS = 4,
    ADVISOR_TRADE = 5,
    ADVISOR_POPULATION = 6,
    ADVISOR_HEALTH = 7,
    ADVISOR_EDUCATION = 8,
    ADVISOR_ENTERTAINMENT = 9,
    ADVISOR_RELIGION = 10,
    ADVISOR_FINANCIAL = 11,
    ADVISOR_CHIEF = 12,
    ADVISOR_MONUMENTS = 13,
    ADVISOR_WATER = 14,
    ADVISOR_FOOD = 15,
    ADVISOR_PRODUCTION = 16,
    ADVISOR_ENVIRONMENT = 17,
    ADVISOR_SECURITY = 18,
    ADVISOR_HOUSING = 19,
    ADVISOR_TRANSPORT = 20,
    ADVISOR_FOREIGN = 21,
    ADVISOR_DIPLOMACY = 22,
    ADVISOR_MAX
};

enum e_low_mood_reason : uint8_t {
    LOW_MOOD_NONE = 0,
    LOW_MOOD_NO_FOOD = 1,
    LOW_MOOD_NO_JOBS = 2,
    LOW_MOOD_HIGH_TAXES = 3,
    LOW_MOOD_LOW_WAGES = 4,
    LOW_MOOD_MANY_TENTS = 5,
};

enum e_no_immigration_reason : uint8_t {
    NO_IMMIGRATION_LOW_WAGES = 0,
    NO_IMMIGRATION_NO_JOBS = 1,
    NO_IMMIGRATION_NO_FOOD = 2,
    NO_IMMIGRATION_HIGH_TAXES = 3,
    NO_IMMIGRATION_MANY_TENTS = 4,
    NO_IMMIGRATION_LOW_MOOD = 5
};

enum e_trade_status : uint8_t {
    TRADE_STATUS_NONE = 0,
    TRADE_STATUS_IMPORT = 1,
    TRADE_STATUS_EXPORT = 2,
    TRADE_STATUS_IMPORT_AS_NEEDED = 3,
    TRADE_STATUS_EXPORT_SURPLUS = 4,
};

enum e_availability : int8_t {
    NOT_AVAILABLE_YET = -1,
    NOT_AVAILABLE = 0,
    AVAILABLE = 1,
};

enum e_permission : uint8_t {
    epermission_none = 0,
    epermission_maintenance = 1,
    epermission_priest = 2,
    epermission_market = 3,
    epermission_entertainer = 4,
    epermission_education = 5,
    epermission_medicine = 6,
    epermission_tax_collector = 7,

    epermission_count
};
using e_permission_tokens_t = token_holder<e_permission, epermission_none, epermission_count>;

enum e_rating_change : uint8_t {
    e_rating_dropping = 0,
    e_rating_stalling,
    e_rating_rising
};