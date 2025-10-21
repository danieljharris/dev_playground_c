#pragma once
#include <spdlog/spdlog.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <expected>
#include <optional>
#include <tuple>

using std::vector;
using std::string;
using std::optional;
using std::nullopt;
using std::tuple;
using std::make_tuple;
using std::tie;
using std::expected;
using std::unexpected;

enum class Side { BUY, SELL };

struct Order {
    Side side;
    double price;
    int quantity;
    int id;

    // void operator=(const Order& other) noexcept {
    //     side = other.side;
    //     price = other.price;
    //     quantity = other.quantity;
    //     id = other.id;
    // }

    bool operator<(const Order& other) const noexcept {
        if (price < other.price) return side == Side::BUY;
        if (price > other.price) return side == Side::SELL;
        return false;
    }
};

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {
        return a.price < b.price; // higher price = higher priority
    }
};

struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {
        return a.price > b.price; // lower price = higher priority
    }
};

class OrderBook {
private:
    std::priority_queue<Order, std::vector<Order>, BuyComparator> buys;
    std::priority_queue<Order, std::vector<Order>, SellComparator> sells;
    optional<tuple<int, int>> compareOrders(const Order& buy, const Order& sell);
    
public:
    OrderBook() = default;
    void addOrder(const Order& order);
    void printState() const;
};