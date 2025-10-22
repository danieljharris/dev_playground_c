#include "api.h"

void OrderBook::printState() const {
    spdlog::info("State:");
    spdlog::info("Buy Orders:");

    auto buysCopy = buys;
    while (!buysCopy.empty()) {
        auto buy = buysCopy.top();
        spdlog::info("Buy {}# {} x {}", buy.id, buy.price, buy.quantity);
        buysCopy.pop();
    }

    spdlog::info("Sell Orders:");

    auto sellsCopy = sells;
    while (!sellsCopy.empty()) {
        auto sell = sellsCopy.top();
        spdlog::info("Sell {}# {} x {}", sell.id, sell.price, sell.quantity);
        sellsCopy.pop();
    }
}

void OrderBook::addOrder(const Order& order) {
    if (order.quantity <= 0 || order.price <= 0 || order.id <= 0) {
        spdlog::error("Invalid order: {} @ {} x {}", order.id, order.price, order.quantity);
    }

    spdlog::info("Adding {} {}# {} x {}", order.side == Side::BUY ? "BUY" : "SELL", order.id, order.price, order.quantity);

    if (order.side == Side::BUY) buys.push(order);
    else sells.push(order);

    tryMatch();
}

void OrderBook::tryMatch() {
    int amountBought = 0;
    do {
        if (buys.empty() || sells.empty()) return;

        Order inBuy = buys.top();
        Order inSell = sells.top();

        spdlog::debug("? BUY {}# @ {} x {} | SELL {}# @ {} x {}", inBuy.id, inBuy.price, inBuy.quantity, inSell.id, inSell.price, inSell.quantity);
        auto result = compareOrders(inBuy, inSell);
        if(!result) return;
    
        spdlog::debug("Old Buy Quantity: {} | Old Sell Quantity: {}", inBuy.quantity, inSell.quantity);
        auto [newBuyQuantity, newSellQuantity] = *result;
        spdlog::debug("New Buy Quantity: {} | New Sell Quantity: {}", newBuyQuantity, newSellQuantity);
        
        amountBought = inBuy.quantity - newBuyQuantity;
        spdlog::debug("amountBought: {}", amountBought);
        if (amountBought > 0) {
            spdlog::info("Transaction of from {}# to {}# @ {} x {}", inSell.id, inBuy.id, inSell.price, amountBought);
        }
        
        if (newSellQuantity == 0) sells.pop();
        else {
            sells.pop();
            inSell.quantity = newSellQuantity;
            sells.push(inSell);
        }
        
        if (newBuyQuantity == 0) buys.pop();
        else {
            buys.pop();
            inBuy.quantity = newBuyQuantity;
            buys.push(inBuy);
        }

    } while (amountBought > 0);

    spdlog::warn("No transation found");
}

optional<tuple<int, int>> OrderBook::compareOrders(const Order& buy, const Order& sell) {
    spdlog::debug("Compairing: BUY {} @ {} x {} with SELL {} @ {} x {}", buy.id, buy.price, buy.quantity, sell.id, sell.price, sell.quantity);

    if (buy.price < sell.price) return nullopt;

    if (buy.quantity == sell.quantity) return make_tuple(0, 0);
    if (buy.quantity > sell.quantity) return make_tuple(buy.quantity - sell.quantity, 0);
    if (buy.quantity < sell.quantity) return make_tuple(0, sell.quantity - buy.quantity);

    spdlog::error("Error: compareOrders with: buy {} @ {} x {} with sell {} @ {} x {}", buy.id, buy.price, buy.quantity, sell.id, sell.price, sell.quantity);
    assert(false);
}