#include "city_animals.h"

#include "city/city.h"
#include "js/js_game.h"
#include "core/profiler.h"

void __city_remove_animals() { g_city.animals.remove_all(); }
ANK_FUNCTION(__city_remove_animals);

void __city_add_animals_point(int index, int x, int y, int ftype, int num) {
    g_city.animals.add_animals_point(index, x, y, (e_figure_type)ftype, num);
}
ANK_FUNCTION_5(__city_add_animals_point)

void __city_set_animals_area(int index, int radius) {
    g_city.animals.set_animals_area(index, radius);
}
ANK_FUNCTION_2(__city_set_animals_area)

bool __city_animals_breeding_ground_at(tile2i tile, int size) {
    return g_city.animals.breeding_ground_at(tile, size);
}
ANK_FUNCTION_2(__city_animals_breeding_ground_at)
