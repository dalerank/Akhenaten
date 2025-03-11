#include "advisor_health.h"

#include "building/count.h"
#include "city/coverage.h"
#include "city/city_health.h"
#include "city/city.h"
#include "city/city_population.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "game/game.h"

ui::advisor_health_window g_advisor_health_window;

static int get_health_advice() {
    house_demands &demands = g_city.houses;
    switch (demands.health) {
    case 1: return demands.requiring.water_supply ? 1 : 0;
    case 2: return demands.requiring.dentist ? 3 : 2;
    case 3: return demands.requiring.physician ? 5 : 4;
    case 4: return 6;
    }

    return 7;
}

int ui::advisor_health_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    ui["city_health"] = (city_population() >= 200) 
                            ? ui::str(56, g_city.health.value / 10 + 16)
                            : ui::str(56, 15);

    // apothecary
    ui["apothecary_total"].text_var("%u %s", building_count_total(BUILDING_APOTHECARY), ui::str(8, 29));
    ui["apothecary_active"] = bstring32(building_count_active(BUILDING_APOTHECARY));
    ui["apothecary_care"].text_var("%u %s", 1000 * building_count_active(BUILDING_APOTHECARY), ui::str(56, 6));
    ui["apothecary_covg"] = ui::str(57, g_coverage.apothecary / 10 + 11);

    // dentist
    ui["dentist_total"].text_var("%u %s", building_count_total(BUILDING_DENTIST), ui::str(8, 27));
    ui["dentist_active"] = bstring32(building_count_active(BUILDING_DENTIST));
    ui["dentist_care"].text_var("%u %s", 1000 * building_count_active(BUILDING_DENTIST), ui::str(56, 6));
    ui["dentist_covg"] = ui::str(57, g_coverage.dentist / 10 + 11);

    // physicians
    ui["physicians_total"].text_var("%u %s", building_count_total(BUILDING_PHYSICIAN), ui::str(8, 25));
    ui["physicians_active"] = bstring32(building_count_active(BUILDING_PHYSICIAN));
    ui["physicians_care"].text_var("%u %s", 1000 * building_count_active(BUILDING_PHYSICIAN), ui::str(56, 6));
    ui["physicians_covg"] = ui::str(57, g_coverage.physician / 10 + 11);

    // mortuary
    ui["mortuary_total"].text_var("%u %s", building_count_total(BUILDING_MORTUARY), ui::str(8, 31));
    ui["mortuary_active"] = bstring32(building_count_active(BUILDING_MORTUARY));
    ui["mortuary_care"].text_var("%u %s", 1000 * building_count_active(BUILDING_MORTUARY), ui::str(56, 6));
    ui["mortuary_covg"] = ui::str(57, g_coverage.mortuary / 10 + 11);

    ui["health_advice"] = ui::str(56, 6 + get_health_advice());
    return 0;
}

advisor_window* ui::advisor_health_window::instance() {
    return &g_advisor_health_window;
}
