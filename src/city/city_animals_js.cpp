#include "city_animals.h"

#include "js/js_game.h"

void __city_remove_animals() {
    g_city_animals.remove_all();
}
ANK_FUNCTION(__city_remove_animals);

void __city_add_animals_point(int index, int x, int y, int ftype, int num) {
    g_city_animals.add_animals_point(index, x, y, (e_figure_type)ftype, num);
}
ANK_FUNCTION_5(__city_add_animals_point)

void __city_set_animals_area(int index, int radius) {
    g_city_animals.set_animals_area(index, radius);
}
ANK_FUNCTION_2(__city_set_animals_area)