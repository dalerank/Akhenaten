#include "city/city_labor.h"

#include "city/city.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

void __city_labor_set_priority(int category, int new_priority) {
    city_labor().set_priority(category, new_priority);
}
ANK_FUNCTION_2(__city_labor_set_priority)

int __city_labor_max_selectable_priority(int category) {
    return city_labor().max_selectable_priority(category);
}
ANK_FUNCTION_1(__city_labor_max_selectable_priority)

int __city_labor_priority_rank_max() {
    return city_labor().priority_rank_max();
}
ANK_FUNCTION(__city_labor_priority_rank_max)

bool __city_labor_category_split_enabled() {
    return labor_category_split_enabled();
}
ANK_FUNCTION(__city_labor_category_split_enabled)

int __city_labor_calc_fixed_workers_available(int num_plebs) {
    return city_labor_t::calc_fixed_workers_available(num_plebs);
}
ANK_FUNCTION_1(__city_labor_calc_fixed_workers_available)

void __city_labor_calculate_workers(int num_plebs, int num_patricians) {
    city_labor().calculate_workers(num_plebs, num_patricians);
}
ANK_FUNCTION_2(__city_labor_calculate_workers)

void __city_labor_update() {
    city_labor().update();
}
ANK_FUNCTION(__city_labor_update)

ANK_GLOBAL_OBJECT(city_labor(), __city_labor, workers_available, workers_employed, workers_unemployed, workers_needed,
  unemployment_percentage_for_goverment, unemployment_percentage);
