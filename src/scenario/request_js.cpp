#include "request.h"

#include "js/js_game.h"
#include "scenario/scenario.h"

void __city_create_good_request(int tag, int type, int amount, int months_initial) {
    g_scenario.events.create_good_request(tag, (e_resource)type, amount, months_initial);
}
ANK_FUNCTION_4(__city_create_good_request)
