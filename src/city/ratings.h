#pragma once

#include <cstdint>

enum e_selected_rating {
    SELECTED_RATING_NONE = 0,
    SELECTED_RATING_CULTURE = 1,
    SELECTED_RATING_PROSPERITY = 2,
    SELECTED_RATING_MONUMENT = 3,
    SELECTED_RATING_KINGDOM = 4
};

struct city_ratings_t {
    int32_t culture;
    int32_t prosperity;
    int32_t monument; // peace
    int32_t kingdom;  // favor
    struct {
        int32_t entertainment;
        int32_t religion;
        int32_t school;
        int32_t library;
        int32_t academy;
    } culture_points;
    int32_t prosperity_treasury_last_year;
    int32_t prosperity_max;
    int32_t monument_destroyed_buildings;
    int32_t monument_years_of_monument;
    int32_t monument_num_criminals;
    int32_t monument_num_rioters;
    int32_t monument_riot_cause;
    int32_t kingdom_salary_penalty;
    int32_t kingdom_milestone_penalty;
    int32_t kingdom_ignored_request_penalty;
    int32_t kingdom_last_year;
    int32_t kingdom_change; // 0 = dropping, 1 = stalling, 2 = rising

    int32_t selected;
    int32_t culture_explanation;
    int32_t prosperity_explanation;
    int32_t monument_explanation;
    int32_t kingdom_explanation;
    
    int selected_explanation();
    void reduce_prosperity_after_bailout();
    void monument_building_destroyed(int type);
    void monument_record_criminal();
    void monument_record_rioter();
    void change_kingdom(int amount);
    void reset_kingdom();
    void reduce_kingdom_missed_request(int penalty);
    void limit_kingdom(int max_kingdom);

    void update_culture_explanation();
    void update_monument_explanation();
    void update_kingdom_explanation();
    void update_culture_rating();
    void update_monument_rating();
    void update_kingdom_rating(int is_yearly_update);
};