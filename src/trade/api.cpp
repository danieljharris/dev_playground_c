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

    spdlog::debug("Adding {} {}# {} x {}", order.side == Side::BUY ? "BUY" : "SELL", order.id, order.price, order.quantity);

    Order inBuy;
    Order inSell;
    if (order.side == Side::BUY) {
        if (sells.empty()) {
            buys.push(order);
            return;
        }
        inBuy = order;
        inSell = sells.top();
    }
    else {
        if (buys.empty()) {
            sells.push(order);
            return;
        }
        inBuy = buys.top();
        inSell = order;
    }

    spdlog::debug("About to compare: BUY {} @ {} x {} with SELL {} @ {} x {}", inBuy.id, inBuy.price, inBuy.quantity, inSell.id, inSell.price, inSell.quantity);
    auto result = compareOrders(inBuy, inSell);
    if(!result) {
        spdlog::debug("Here 0");
        buys.push(inBuy);
        return;
    }

    spdlog::debug("Here 1");
    
    auto [newBuyQuantity, newSellQuantity] = *result;
    
    int amountBought = inBuy.quantity - newBuyQuantity;
    if (amountBought > 0) {
        spdlog::info("Transaction from {} to {} @ {} x {}", inSell.id, inBuy.id, inSell.price, amountBought);
    }

    spdlog::debug("Here 2");

    if (newSellQuantity == 0 && order.side == Side::BUY) sells.pop();
    else if (newSellQuantity != 0) {
        if (order.side == Side::BUY) sells.pop();
        inSell.quantity = newSellQuantity;
        sells.push(inSell);
    }

    if (newBuyQuantity == 0 && order.side == Side::SELL) buys.pop();
    else if (newSellQuantity != 0) {
        if (order.side == Side::SELL) buys.pop();
        inBuy.quantity = newBuyQuantity;
        buys.push(inBuy);
    }


    // else {
    //     Order sellOrder = order;
    //     spdlog::debug("Add Sell {}# {} x {}", sellOrder.id, sellOrder.price, sellOrder.quantity);

    //     if (buys.empty()) {
    //         sells.push(sellOrder);
    //         return;
    //     }

    //     Order topBuy = buys.top();
    //     if (topBuy.price < sellOrder.price) {
    //         sells.push(sellOrder);
    //         return;
    //     }

    //     if (sellOrder.quantity == topBuy.quantity) {
    //         buys.pop();
    //         spdlog::info("Executing trade: BUY #{} {} x {} @ {}", topBuy.id, topBuy.price, sellOrder.quantity, sellOrder.price);
    //         return;
    //     }
    //     else if (sellOrder.quantity < topBuy.quantity) {
    //         spdlog::info("Executing trade: BUY #{} {} x {} @ {}", topBuy.id, topBuy.price, sellOrder.quantity, sellOrder.price);
    //         buys.pop();
    //         topBuy.quantity -= sellOrder.quantity;
    //         buys.push(topBuy);
    //         return;
    //     }
    //     else {
    //         spdlog::info("Executing trade: BUY #{} {} x {} @ {}", topBuy.id, topBuy.price, topBuy.quantity, sellOrder.price);
    //         sellOrder.quantity -= topBuy.quantity;
    //         sells.push(sellOrder);
    //         buys.pop();
    //         return;
    //     }
    // }
}

optional<tuple<int, int>> OrderBook::compareOrders(const Order& buy, const Order& sell) {
    spdlog::debug("Compairing: BUY {} @ {} x {} with SELL {} @ {} x {}", buy.id, buy.price, buy.quantity, sell.id, sell.price, sell.quantity);

    if (buy.price < sell.price) return nullopt;

    spdlog::debug("Here: 00");

    if (buy.quantity == sell.quantity) return make_tuple(0, 0);
    if (buy.quantity > sell.quantity) return make_tuple(buy.quantity - sell.quantity, 0);
    if (buy.quantity < sell.quantity) return make_tuple(0, sell.quantity - buy.quantity);

    spdlog::error("compareOrders with: buy {} @ {} x {} with sell {} @ {} x {}", buy.id, buy.price, buy.quantity, sell.id, sell.price, sell.quantity);
    assert(false);
}