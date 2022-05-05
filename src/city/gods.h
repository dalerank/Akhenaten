#ifndef CITY_GODS_H
#define CITY_GODS_H

#define MAX_GODS 5

void city_gods_reset(void);

int god_known_status(int god);

enum {
    GOD_EVENT_MAJOR_BLESSING = 1,
    GOD_EVENT_MINOR_BLESSING = 2,
    GOD_EVENT_MAJOR_CURSE = 3,
    GOD_EVENT_MINOR_CURSE = 4
};

void update_curses_and_blessings(int randm_god, int FORCE_EVENT = -1);

void city_gods_update(bool mood_calc_only);
bool city_gods_calculate_least_happy(void);
int city_god_happiness(int god_id);
int city_god_wrath_bolts(int god_id);
int city_god_happy_angels(int god_id);
/**
 * @return God ID or -1 if no single god is the least happy
 */
int city_god_least_happy(void);

int city_god_months_since_festival(int god_id);

int city_god_spirit_of_mars_power(void);
void city_god_spirit_of_mars_mark_used(void);

int city_god_neptune_create_shipwreck_flotsam(void);

void city_god_blessing_cheat(int god_id);

#endif // CITY_GODS_H
