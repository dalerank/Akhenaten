#include "city/city_festival.h"

#include "city/city.h"
#include "core/profiler.h"
#include "js/js_game.h"

std::optional<bvariant> __city_get_festival_property(pcstr property) {
    return archive_helper::get(g_city.festival, property, true);
}
ANK_FUNCTION_1(__city_get_festival_property)

bool __city_festival_is_planned() {
    return g_city.festival.is_planned();
}
ANK_FUNCTION(__city_festival_is_planned)

int __city_festival_months_till_next() {
    return g_city.festival.months_till_next();
}
ANK_FUNCTION(__city_festival_months_till_next)

int __city_festival_selected_size() {
    return (int)g_city.festival.selected_size;
}
ANK_FUNCTION(__city_festival_selected_size)

void __city_festival_select_god(int god) {
    g_city.festival.select_god((e_god)god);
}
ANK_FUNCTION_1(__city_festival_select_god)

void __city_festival_select_size(int size) {
    g_city.festival.select_size((e_festival_type)size);
}
ANK_FUNCTION_1(__city_festival_select_size)

void __city_festival_schedule(int god, int festival_size, int months_until_festival, int festival_cost, int beer_to_remove) {
    g_city.festival.schedule((e_god)god, (e_festival_type)festival_size, months_until_festival, festival_cost, beer_to_remove);
}
ANK_FUNCTION_5(__city_festival_schedule)