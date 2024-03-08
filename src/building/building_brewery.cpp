#include "building/building_brewery.h"

#include "building/building_workshop.h"

struct brewery_model : public buildings::model_t<BUILDING_BREWERY_WORKSHOP, building_brewery> {};
brewery_model brewery_m{"building_brewery"};

void building_brewery::on_create() {
    data.industry.first_material_id = RESOURCE_BARLEY;
    base.output_resource_first_id = RESOURCE_BEER;
}

void building_brewery::window_info_background(object_info& c) {
    e_resource input_resource = RESOURCE_BARLEY;
    e_resource output_resource = RESOURCE_BEER;

    building_workshop_draw_info(c, 96, "brewery", 122, output_resource, input_resource);
}