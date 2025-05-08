#include "game/tutorial.h"

#include "io/gamefiles/lang.h"
#include "building/building_house.h"
#include "building/building_menu.h"
#include "building/building_storage_yard.h"
#include "game/game.h"
#include "city/city_message.h"
#include "city/city.h"
#include "game/game_events.h"

struct tutorial_6 : public tutorial_t {
    virtual int missionid() const override { return 6; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring s) override;
    virtual xstring goal_text() override;
};

tutorial_6 g_tutorial_6;

void tutorial_6::init() {
    for (int adv = ADVISOR_NONE; adv < ADVISOR_MAX; ++adv) {
        g_city.set_advisor_available((e_advisor)adv, AVAILABLE);
    }
}

void tutorial_6::reset() {
    g_tutorials_flags.tutorial_6.started = 0;
}

void tutorial_6::update_step(xstring s) {

}

xstring tutorial_6::goal_text() {
    return "???";
}