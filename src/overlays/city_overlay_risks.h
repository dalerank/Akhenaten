#pragma once

struct city_overlay;
class building;

void overlay_problems_prepare_building(building* b);

city_overlay* city_overlay_for_problems();

city_overlay* city_overlay_for_native();