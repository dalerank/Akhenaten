#include "city/city_local_cults.h"

#include "city/city.h"
#include "core/profiler.h"
#include "game/local_cults.h"
#include "js/js_game.h"

ANK_GLOBAL_OBJECT(g_city.local_cults, __city_local_cults,
    farm_bonus_months,
    war_bonus_months,
    craft_bonus_months,
    planned_theme,
    planned_cult,
    mission_restricts,
    last_rite_month,
    last_rite_year,
    last_rite_index);

void __city_local_cults_refresh() {
    g_city.local_cults_sys().refresh_active();
}
ANK_FUNCTION(__city_local_cults_refresh)

void __city_local_cults_unlock_all() {
    g_city.local_cults_sys().unlock_all();
}
ANK_FUNCTION(__city_local_cults_unlock_all)

void __city_local_cults_set_unlocked(int cult_id, bool unlocked) {
    g_city.local_cults_sys().set_unlocked((e_local_cult)cult_id, unlocked);
}
ANK_FUNCTION_2(__city_local_cults_set_unlocked)

bool __city_local_cults_is_unlocked(int cult_id) {
    return g_city.local_cults.is_unlocked((e_local_cult)cult_id);
}
ANK_FUNCTION_1(__city_local_cults_is_unlocked)

bool __city_local_cults_is_active(int cult_id) {
    return g_city.local_cults.is_active((e_local_cult)cult_id);
}
ANK_FUNCTION_1(__city_local_cults_is_active)

int __city_local_cults_appeased_months(int cult_id) {
    return g_city.local_cults.appeased_months((e_local_cult)cult_id);
}
ANK_FUNCTION_1(__city_local_cults_appeased_months)

xstring __city_local_cults_name(int cult_id) {
    return local_cult_name((e_local_cult)cult_id);
}
ANK_FUNCTION_1(__city_local_cults_name)

int __city_local_cults_host_god(int cult_id) {
    return (int)local_cult_static((e_local_cult)cult_id).host_major_god;
}
ANK_FUNCTION_1(__city_local_cults_host_god)

int __city_local_cults_building_type(int cult_id) {
    return (int)local_cult_static((e_local_cult)cult_id).building_type;
}
ANK_FUNCTION_1(__city_local_cults_building_type)

int __city_local_cults_count() {
    return LOCAL_CULT_REGISTRY_COUNT;
}
ANK_FUNCTION(__city_local_cults_count)

void __city_local_cults_apply_theme(int theme, int months) {
    g_city.local_cults_sys().apply_theme((e_festival_theme)theme, months);
}
ANK_FUNCTION_2(__city_local_cults_apply_theme)

void __city_local_cults_apply_cult_festival(int cult_id, int theme) {
    g_city.local_cults_sys().apply_cult_festival((e_local_cult)cult_id, (e_festival_theme)theme);
}
ANK_FUNCTION_2(__city_local_cults_apply_cult_festival)

void __city_local_cults_advance_month() {
    g_city.local_cults_sys().advance_month();
}
ANK_FUNCTION(__city_local_cults_advance_month)

xstring __city_local_cults_next_rite_id(int month) {
    return g_city.local_cults.next_calendar_rite_id(month);
}
ANK_FUNCTION_1(__city_local_cults_next_rite_id)

int __city_local_cults_next_rite_theme(int month) {
    return (int)g_city.local_cults.next_calendar_theme(month);
}
ANK_FUNCTION_1(__city_local_cults_next_rite_theme)
