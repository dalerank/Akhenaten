#include "building/building_pottery.h"

#include "building/building_workshop.h"

void building_pottery::on_create() {
    data.industry.first_material_id = RESOURCE_CLAY;
    base.output_resource_first_id = RESOURCE_POTTERY;
}

void building_pottery::window_info_background(object_info& c) {
    e_resource output_resource = RESOURCE_POTTERY;

    building_workshop_draw_info(c, 1, "pottery_workshop", 126, output_resource, RESOURCE_CLAY);
}