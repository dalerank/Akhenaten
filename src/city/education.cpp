#include "city/education.h"

#include "building/building.h"

void city_education_handle_month_change() {
    buildings_valid_do([] (building &b) {
        if (b.stored_full_amount <= 0) {
            return;
        }
        
        int spent = std::min(b.stored_full_amount, b.num_workers);
        b.stored_full_amount -= spent;
    }, BUILDING_SCRIBAL_SCHOOL);
}