#pragma once
#include <spdlog/spdlog.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>
#include <tuple>

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

struct map {
    int source, dest, length;
    explicit map(int source, int dest, int length):
        source(source), dest(dest), length(length) {};
};
using maps = vector<map>;
using mapOmaps = vector<maps>;

class Seed {
public:
    Seed();
    tuple<vector<int>, mapOmaps> ingest();
};