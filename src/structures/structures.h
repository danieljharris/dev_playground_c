#pragma once
#include <spdlog/spdlog.h>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>

#include <unordered_map>
#include <unordered_set>

#include <memory>

#include <iterator>  // Needed for std::advance
#include <string>

using std::vector;
using std::list;
using std::deque;
using std::queue;
using std::stack;

using std::unordered_map;
using std::unordered_set;

using std::unique_ptr;
using std::make_unique;

using std::advance; // Used to insert into middle of list
using std::string;
using std::to_string;

class Structures {
public:
    Structures();

private:
    void fnVector();
    void fnList();
    void fnDeque();
    void fnQueue();
    void fnStack();

    void fnHashMap();
    void fnHashSet();

    void fnTree();
};