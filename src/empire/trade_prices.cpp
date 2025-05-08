#include "trade_prices.h"
#include "io/io_buffer.h"
#include "city/city.h"

static auto &city_data = g_city;
struct trade_price {
    int32_t buy;
    int32_t sell;
};

static const struct trade_price DEFAULT_PRICES[RESOURCES_MAX] = {
  {0, 0},
  {28, 21},   // grain
  {47, 35},   // meat
  {33, 25},   // lettuce
  {33, 25},   // chickpeas
  {33, 25},   // pomegranates
  {33, 25},   // figs
  {42, 33},   // fish
  {44, 34},   // gamemeat

  {21, 16},   // straw
  {325, 275}, // weapons
  {38, 29},   // clay
  {150, 120}, // bricks
  {140, 105}, // pottery
  {48, 37},   // barley
  {185, 140}, // beer
  {54, 42},   // flax
  {210, 160}, // linen
  {120, 92},  // gems
  {310, 150}, // luxury goods
  {225, 170}, // wood
  {0, 0},     // gold
  {31, 23},   // reeds
  {200, 165}, // papyrus
  {38, 29},   // stone
  {46, 35},   // limestone
  {60, 45},   // granite
  {0, 0},     // unused12
  {375, 315}, // chariots
  {240, 185}, // copper
  {40, 32},   // sandstone
  {110, 85},  // oil
  {40, 30},   // henna
  {155, 116}, // paint
  {250, 190}, // lamps
  {72, 54},   // marble
};

static struct trade_price prices[RESOURCES_MAX];

void trade_prices_reset(void) {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        prices[i] = DEFAULT_PRICES[i];
    }
}

int trade_price_change(int resource, int amount) {
    if (amount < 0 && prices[resource].sell <= 0) {
        // cannot lower the price to negative
        return 0;
    }
    if (amount < 0 && prices[resource].sell <= -amount) {
        prices[resource].buy = 2;
        prices[resource].sell = 0;
    } else {
        prices[resource].buy += amount;
        prices[resource].sell += amount;
    }
    return 1;
}

int trade_price_buy(int resource) {
    return prices[resource].buy;
}

int trade_price_sell(int resource, int bonus_inclusion) {
    switch (bonus_inclusion) {
    case PRICE_WITH_BONUS: return prices[resource].sell * (city_data.religion.ra_150_export_profits_months_left > 0 ? 1.5f : 1.0f);
    case PRICE_ONLY_BASE: return prices[resource].sell;
    case PRICE_ONLY_BONUS: return prices[resource].sell * (city_data.religion.ra_150_export_profits_months_left > 0 ? 0.5f : 0.0f);
    }

    return 999;
}

io_buffer* iob_trade_prices = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].buy);
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].sell);
    }
});