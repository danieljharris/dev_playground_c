#include "questions.h"

string tolower(string word) {
    string lowerWord = "";

    for (char c : word) {
        lowerWord += tolower(c);
    }

    return lowerWord;
}

Questions::Questions() {
    // tut1();
    tut2();
}

void Questions::tut1() {
    vector<string> words = {
        "Kayak", "Hannah", "Computer", "RaceCar", "radar", "programming"
    };

    for (string word : words) {
        bool result = isPalindrome(word);
        spdlog::info("Word \"{}\" == Palindrome {}", word, result ? "✅" : "❌");
    }

    int i = 5; 
    int j = i++;
    int x = ++i;
    spdlog::info("i: {} | j: {} | x: {}", i, j, x);
}

bool Questions::isPalindrome(string wordIn) {
    if (wordIn.empty()) return false;
    if (wordIn.length() == 1) return true;

    string word = tolower(wordIn);

    int left = 0;
    int right = word.length() - 1;

    while (true) {
        spdlog::debug("left: {} & right: {}", left, right);
        if (word[left] != word[right]) return false;
        if (left >= right) return true;

        left++;
        right--;
    }
}

void Questions::tut2() {
    int firstvalue, secondvalue; 
    int * mypointer; 
    mypointer = &firstvalue; 
    *mypointer = 10; 
    mypointer = &secondvalue; 
    *mypointer = 20; 
    spdlog::info("firstvalue is {}", firstvalue);
    spdlog::info("secondvalue is {}", secondvalue);

    vector<tuple<int, string>> replace = {
        {3, "Fizz"},
        {5, "Buzz"},
        {9, "Bang"}
    };
    vector<int> values;
    for (int i = 1; i <= 100; i++) {
        values.push_back(i);
    }

    string result = fizzBuzz(values, replace);
    spdlog::info("result: {}", result);
}

/*
Write a program in C++ that prints the numbers from 1 to 100
- for multiples of ‘3’ print "Fizz" 
- instead of the number and
- for the multiples of ‘5’ print "Buzz"
- If the number is a multiple of ‘3’ & ‘5’ then print “FizzBuzz”.
*/

string Questions::fizzBuzz(vector<int> values, vector<tuple<int, string>> replace) {
    string result = "";

    for (int value : values) {
        bool replaced = false;
        for (const auto [num, word] : replace) {
            if (value % num == 0) {
                result += word;
                replaced = true;
            }
        }

        if (!replaced) result += to_string(value);
        result += "\n";
    }

    return result;
}
