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