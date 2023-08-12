#pragma once

struct city_overlay;
class building;

void overlay_problems_prepare_building(building* b);

const city_overlay* city_overlay_for_fire(void);

const city_overlay* city_overlay_for_damage(void);

const city_overlay* city_overlay_for_problems(void);

const city_overlay* city_overlay_for_native(void);