// RAII (Resource Acquisition Is Initialization)
#pragma once
#include <spdlog/spdlog.h>
#include <expected>
#include <string>

using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::optional;
using std::nullopt;
using std::tuple;
using std::make_tuple;
using std::tie;
using std::expected;
using std::unexpected;
using std::tolower;
using std::to_string;

class Raii {
private:
    Raii();
public:
    static expected<Raii, string> create(int initValue);
};