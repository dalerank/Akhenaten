#include "request.h"

#include "js/js_game.h"
#include "scenario/scenario.h"

void __city_create_good_request(int tag, int type, int amount, int months_initial) {
    g_scenario.events.create_good_request(tag, (e_resource)type, amount, months_initial);
}
ANK_FUNCTION_4(__city_create_good_request)

void __city_request_set_reasons(int tag, int r1, int r2, int r3, int r4) {
    g_scenario.events.set_request_reasons(tag, r1, r2, r3, r4);
}
ANK_FUNCTION_5(__city_request_set_reasons)
