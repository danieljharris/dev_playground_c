#include "trade.h"

Trade::Trade() {
    OrderBook book;

    vector<Order> orders = {
        // Phase 1: Basic book setup
        { Side::BUY, 100.0, 5, 1 },   // Buy waiting
        { Side::SELL, 101.0, 2, 2 },  // Above -> no match
        { Side::BUY, 102.0, 1, 3 },   // Matches SELL #2 (partial)
        { Side::SELL, 99.0, 4, 4 },   // Matches BUY #1 (partial)
        { Side::SELL, 100.0, 1, 5 },  // Matches remaining BUY #1

        // Phase 2: Edge cases
        { Side::BUY, 100.0, 10, 6 },  // Large buy that will consume multiple sells
        { Side::SELL, 100.0, 3, 7 },  // Identical-price sells (partially matched)
        { Side::SELL, 100.0, 3, 8 },
        { Side::SELL, 101.0, 2, 9 },  // Price gap sell (will remain)
        { Side::BUY, 99.0, 1, 10 },   // Below book -> stays open

        // Phase 3: Cascading multi-level match
        { Side::SELL, 99.0, 3, 11 },  // Adds deeper liquidity
        { Side::SELL, 98.0, 2, 12 },  // Lower price
        { Side::SELL, 97.0, 4, 13 },  // Even lower price
        { Side::BUY, 101.0, 9, 14 },  // Triggers cascading matches through 3 sell levels

        // Phase 4: Reverse cascade test
        { Side::BUY, 100.0, 2, 15 },  // Small resting buy
        { Side::SELL, 99.0, 5, 16 },   // Will partially fill #15, rest remains
    };


    for (const Order& order : orders) {
        book.addOrder(order);
    }

    book.printState();
}

/*
    🎯 Task Overview
    Implement a small C++ program that:

    Maintains two order books:
        Buy Orders (sorted by highest price first)
        Sell Orders (sorted by lowest price first)

    When a new order arrives:
        If it matches (a buy ≥ sell), execute a trade at the sell price (best available)
        Otherwise, store the order in the book for future matches

    Print out executed trades and the state of the order book after processing all orders
*/

/*
    Executing trade: BUY 102.00 x 1 @ 99.00
    Executing trade: BUY 100.00 x 3 @ 100.00

    Remaining BUY Orders:
    BUY 100.00 x 2
    Remaining SELL Orders:
    SELL 101.00 x 2
*/