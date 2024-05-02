#pragma once

#include "building/building_type.h"

enum e_selected_rating {
    SELECTED_RATING_NONE = 0,
    SELECTED_RATING_CULTURE = 1,
    SELECTED_RATING_PROSPERITY = 2,
    SELECTED_RATING_MONUMENT = 3,
    SELECTED_RATING_KINGDOM = 4
};

int city_rating_culture();
int city_rating_prosperity();
int city_rating_monument();
int city_rating_kingdom();

int city_rating_selected();
void city_rating_select(int rating);
int city_rating_selected_explanation();

void city_ratings_reduce_prosperity_after_bailout();

void city_ratings_monument_building_destroyed(int type);

void city_ratings_monument_record_criminal();

void city_ratings_monument_record_rioter();

void city_ratings_change_kingdom(int amount);

void city_ratings_reset_kingdom_emperor_change();

void city_ratings_reduce_kingdom_missed_request(int penalty);

void city_ratings_limit_kingdom(int max_kingdom);

void city_ratings_update_kingdom_explanation();