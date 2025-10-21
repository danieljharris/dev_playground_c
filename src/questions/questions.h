#pragma once
#include <spdlog/spdlog.h>
#include <expected>
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
using std::expected;
using std::unexpected;
using std::tolower;
using std::to_string;

class Questions {
private:
    void tut1();
    bool isPalindrome(string wordIn);
    void tut2();
    string fizzBuzz(vector<int> values, vector<tuple<int, string>> replace);
public:
    Questions();
};