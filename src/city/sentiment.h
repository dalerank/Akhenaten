#pragma once

int city_sentiment();

int city_sentiment_low_mood_cause();

bool city_can_create_mugger();
bool city_can_create_protestor();

void city_set_can_create_mugger(bool v);
void city_set_can_create_protestor(bool v);

void city_show_message_criminal(int message_id, int money_stolen, int tile_offset);

void city_sentiment_change_happiness(int amount);

void city_sentiment_set_max_happiness(int max);

void city_sentiment_reset_protesters_criminals();

void city_sentiment_add_protester();
void city_sentiment_add_criminal();

int city_sentiment_protesters();
int city_sentiment_criminals();

void city_sentiment_update();
void city_sentiment_update_day();
void city_criminals_update_day();
void city_plague_update_day();