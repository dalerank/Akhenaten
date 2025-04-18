#include "game/tutorial.h"

#include "io/gamefiles/lang.h"
#include "building/building_house.h"
#include "building/building_menu.h"
#include "building/building_storage_yard.h"
#include "game/game.h"
#include "city/city_message.h"
#include "city/city.h"
#include "city/city_events.h"

void tutorial_6::reset() {
    g_tutorials_flags.tutorial_6.started = 0;
}

void tutorial_6::update_step(xstring s) {

}

xstring tutorial_6::goal_text() {
    return "???";
}