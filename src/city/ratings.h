#pragma once

#include "building/building_type.h"

enum e_selected_rating {
    SELECTED_RATING_NONE = 0,
    SELECTED_RATING_CULTURE = 1,
    SELECTED_RATING_PROSPERITY = 2,
    SELECTED_RATING_MONUMENT = 3,
    SELECTED_RATING_KINGDOM = 4
};

int city_rating_culture(void);
int city_rating_prosperity(void);
int city_rating_monument(void);
int city_rating_kingdom(void);

int city_rating_selected(void);
void city_rating_select(int rating);
int city_rating_selected_explanation(void);

void city_ratings_reduce_prosperity_after_bailout(void);

void city_ratings_monument_building_destroyed(int type);

void city_ratings_monument_record_criminal(void);

void city_ratings_monument_record_rioter(void);

void city_ratings_change_kingdom(int amount);

void city_ratings_reset_kingdom_emperor_change(void);

void city_ratings_reduce_kingdom_missed_request(int penalty);

void city_ratings_limit_kingdom(int max_kingdom);

void city_ratings_update_kingdom_explanation(void);

void city_ratings_update_explanations(void);

void city_ratings_update(int is_yearly_update);

int city_ratings_prosperity_max(void);