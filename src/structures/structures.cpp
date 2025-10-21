#include "structures.h"

Structures::Structures() {
    spdlog::info("Entering Structures...");

    // Linear
    // fnVector();
    // fnList();
    // fnDeque();
    // fnQueue();
    // fnStack();

    // Hash
    // fnHashMap();
    // fnHashSet();

    // Tree
    fnTree();

    spdlog::info("Exiting Structures.\n\n");
}

template <typename Iterable>
void print(Iterable iteratable, string preText = "", string postText = "") {
    string values = "";
    for (int i : iteratable) values += to_string(i) + " ";
    spdlog::info("{}{}{}", preText, values, postText);
}

template <typename Iterable>
void printHashMap(Iterable iteratable, string preText = "", string postText = "") {
    string values = "";
    for (const auto& [key, i] : iteratable) values += key + ":" + to_string(i) + "\n";
    spdlog::info("{}\n{}{}", preText, values, postText);
}

void Structures::fnVector() {
    spdlog::info("Entering fnVector...");
    vector<int> vec;

    spdlog::info("push_back: {}", 10);
    vec.push_back(10);

    spdlog::info("push_back: {}", 20);
    vec.push_back(20);

    spdlog::info("push_back: {}\n", 30);
    vec.push_back(30);

    spdlog::info("{} <- first value", vec.front());
    spdlog::info("{} <- last value\n", vec.back());
    
    vec.pop_back();
    spdlog::info("{} <- first value after pop_back", vec.front());
    spdlog::info("{} <- last value after pop_back\n", vec.back());
    
    vec.pop_back();
    spdlog::info("{} <- first value after pop_back", vec.front());
    spdlog::info("{} <- last value after pop_back\n", vec.back());

    spdlog::info("Exiting fnVector.\n\n");
}

void Structures::fnList() {
    spdlog::info("Entering fnList...");
    list<int> lst;

    spdlog::info("push_back: {}", 10);
    lst.push_back(10);

    spdlog::info("push_back: {}", 20);
    lst.push_back(20);

    spdlog::info("push_front: {}", 5);
    lst.push_front(5);

    spdlog::info("insert: {} at pos 2", 15);
    auto it1 = lst.begin();
    advance(it1, 2);
    lst.insert(it1, 15);
    print(lst, "Values: ");
        
    lst.pop_front();
    print(lst, "Values: ", "after pop_front");
    
    auto it2 = lst.begin();
    advance(it2, 1);
    lst.erase(it2);
    print(lst, "Values: ", "after erase at pos 1");

    lst.pop_back();
    print(lst, "Values: ", "after pop_back");

    spdlog::info("Exiting fnList.\n\n");
}

void Structures::fnDeque() {
    spdlog::info("Entering fnDeque...");
    deque<int> deq;

    spdlog::info("push_back: {}", 10);
    deq.push_back(10);
    print(deq, "Values: ");

    spdlog::info("push_back: {}", 20);
    deq.push_back(20);
    print(deq, "Values: ");

    spdlog::info("push_front: {}", 5);
    deq.push_front(5);
    print(deq, "Values: ");

    deq.pop_front();
    print(deq, "Values: ", "after pop_front");
    
    deq.pop_back();
    print(deq, "Values: ", "after pop_back");

    spdlog::info("Exiting fnDeque.\n\n");
}

void Structures::fnQueue() {
    spdlog::info("Entering fnQueue...");
    queue<int> que;

    spdlog::info("push: {}", 10);
    que.push(10);

    spdlog::info("push: {}", 20);
    que.push(20);

    spdlog::info("push: {}", 30);
    que.push(30);
    spdlog::info("Value at front: {}", que.front());
    
    que.pop();
    spdlog::info("Value at front: {}. after pop", que.front());
    
    que.pop();
    spdlog::info("Value at front: {}. after pop", que.front());

    spdlog::info("Exiting fnQueue.\n\n");
}

void Structures::fnStack() {
    spdlog::info("Entering fnStack...");
    stack<int> stk;

    spdlog::info("push: {}", 10);
    stk.push(10);

    spdlog::info("push: {}", 20);
    stk.push(20);

    spdlog::info("push: {}", 30);
    stk.push(30);
    spdlog::info("Value at top: {}", stk.top());
    
    stk.pop();
    spdlog::info("Value at top: {}. after pop", stk.top());
    
    stk.pop();
    spdlog::info("Value at top: {}. after pop", stk.top());

    spdlog::info("Exiting fnStack.\n\n");
}

void Structures::fnHashMap() {
    spdlog::info("Entering fnHashMap...");
    unordered_map<string, int> hashMap;

    spdlog::info("emplace(): {}:{}", "bird", 10);
    hashMap.emplace("bird", 10);

    spdlog::info("insert(): {}:{}", "cat", 10);
    hashMap.insert({"cat", 10});
    
    spdlog::info("insert[]: {}:{}", "dog", 20);
    hashMap["dog"] = 20;
    
    spdlog::info("insert_or_assign: {}:{}", "fish", 30);
    hashMap.insert_or_assign("fish", 30);
    
    printHashMap(hashMap, "Values:");
    
    hashMap.erase("dog");
    printHashMap(hashMap, "Values after erase dog:");
    
    spdlog::info("Try to emplace duplicate:");
    // auto [_, success] = hashMap.insert({"cat", 10});
    auto [_, success] = hashMap.emplace("cat", 10);
    spdlog::info("success: {}", success);
    printHashMap(hashMap, "Values:");

    spdlog::info("Exiting fnHashMap.\n\n");
}

void Structures::fnHashSet() {
    spdlog::info("Entering fnHashSet...");
    unordered_set<int> hashSet; // Unordered, Unique, Non-Indexable, Fast Existence Checks vs std::set

    spdlog::info("insert: {}", 10);
    hashSet.insert(10);
    
    spdlog::info("insert: {}", 20);
    hashSet.insert(20);

    spdlog::info("insert: {}", 30);
    hashSet.insert(30);

    print(hashSet, "Values: ");
    
    hashSet.erase(20);
    print(hashSet, "Values: ", "after erase 20");

    spdlog::info("Try to insert duplicate:");
    auto [_, success] = hashSet.insert(30);
    spdlog::info("success: {}", success);

    spdlog::info("Exiting fnHashSet.\n\n");
}

template <typename Type>
class Tree {
    unique_ptr<Tree<Type>> left = nullptr;
    unique_ptr<Tree<Type>> right = nullptr;
    Type data;

public:
    explicit Tree(Type data) : data(data) {}

    bool insert(Type inData) {
        if(inData < data) {
            if (!left) left = make_unique<Tree<Type>>(inData);
            else return left->insert(inData);
        }
        if(inData > data) {
            if (!right) right = make_unique<Tree<Type>>(inData);
            else return right->insert(inData);
        }
        return false;
    }

    bool find(Type inData) {
        if(data == inData) return true;
        if(inData < data) {
            if (!left) return false;
            else return left->find(inData);
        }
        if(inData > data) {
            if (!right) return false;
            else return right->find(inData);
        }
        return false;
    }

    void print() {
        if (left) left->print();
        spdlog::info("{}", data);
        if (right) right->print();
    }
};

void Structures::fnTree() {
    spdlog::info("Entering fnTree...");

    Tree<int> tree(5);
    tree.insert(3);
    tree.insert(7);

    tree.print();

    spdlog::info("Try to insert duplicate:");
    bool success = tree.insert(5);
    spdlog::info("success: {}", success);

    spdlog::info("Exiting fnTree.\n\n");
}