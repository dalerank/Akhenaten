#pragma once

void map_water_supply_update_houses();
void map_update_canals(void);
void map_update_wells_range(void);

enum e_well_status {
    WELL_NECESSARY = 0,
    WELL_UNNECESSARY_FOUNTAIN = 1,
    WELL_UNNECESSARY_NO_HOUSES = 2
};

e_well_status map_water_supply_is_well_unnecessary(int well_id, int radius);
