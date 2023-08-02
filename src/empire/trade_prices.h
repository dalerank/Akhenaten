#ifndef EMPIRE_TRADE_PRICES_H
#define EMPIRE_TRADE_PRICES_H

#include "core/buffer.h"
#include "game/resource.h"

/**
 * @file
 * Trade prices.
 */

/**
 * Reset trade prices to the default
 */
void trade_prices_reset(void);

/**
 * Get the buy price for the resource
 * @param resource Resource
 */
int trade_price_buy(int resource);

enum { PRICE_WITH_BONUS,
       PRICE_ONLY_BASE,
       PRICE_ONLY_BONUS };

/**
 * Get the sell price for the resource
 * @param resource Resource
 */
int trade_price_sell(int resource, int bonus_inclusion = PRICE_WITH_BONUS);

/**
 * Change the trade price for resource by amount
 * @param resource Resource to change
 * @param amount Amount to change, can be positive or negative
 * @return True if the price has been changed
 */
int trade_price_change(int resource, int amount);

#endif // EMPIRE_TRADE_PRICES_H
