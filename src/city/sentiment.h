#pragma once

int city_sentiment(void);

int city_sentiment_low_mood_cause();

bool city_can_create_mugger();
bool city_can_create_protestor();

void city_set_can_create_mugger(bool v);
void city_set_can_create_protestor(bool v);

void city_show_message_criminal(int message_id, int money_stolen, int tile_offset);

void city_sentiment_change_happiness(int amount);

void city_sentiment_set_max_happiness(int max);

void city_sentiment_reset_protesters_criminals(void);

void city_sentiment_add_protester(void);
void city_sentiment_add_criminal(void);

int city_sentiment_protesters(void);
int city_sentiment_criminals(void);

void city_sentiment_update();
void city_sentiment_update_day();
void city_criminals_update_day();