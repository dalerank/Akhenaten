#pragma once

#include "core/buffer.h"
#include "game/resource.h"
#include "core/archive.h"

struct trade_price {
    e_resource res;
    int32_t buy;
    int32_t sell;

    inline e_resource key() const { return res; }
};
ANK_CONFIG_STRUCT(trade_price, res, buy, sell)

template<>
struct std::hash<trade_price> {
    [[nodiscard]] size_t operator()(const trade_price &price) const noexcept {
        return price.res;
    }
};

enum e_price_rule { 
    PRICE_WITH_BONUS, 
    PRICE_ONLY_BASE, 
    PRICE_ONLY_BONUS 
};

void trade_prices_reset();
int trade_price_buy(e_resource resource);
int trade_price_sell(e_resource resource, int bonus_inclusion = PRICE_WITH_BONUS);
bool trade_price_change(e_resource resource, int amount);