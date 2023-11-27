#include "city/education.h"

#include "building/building.h"
#include "core/calc.h"

void city_education_handle_month_change() {
    buildings_valid_do([] (building &b) {
        if (b.stored_full_amount <= 0) {
            return;
        }
        
        short want_spent = calc_adjust_with_percentage<short>(b.num_workers, 50);
        short spent = std::min(b.stored_full_amount, want_spent);
        b.stored_full_amount -= spent;
    }, BUILDING_SCRIBAL_SCHOOL);
}