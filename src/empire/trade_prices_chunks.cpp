#include "empire/trade_prices_chunks.h"

#include "empire/trade_prices.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

void trade_prices_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& prices = xvalue<trade_prices_t>::ref().prices;
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].buy);
        iob->bind(BIND_SIGNATURE_INT32, &prices[i].sell);
    }
}
