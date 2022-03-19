#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Lang {
    string name;
    int age;
};

using LangIt = vector<Lang>::iterator;

void second_example(const vector<Lang>& ages) {
    // [begin end) - полуинтервал
    for (auto it = begin(ages); it != end(ages); ++it) {
        cout << it->name << endl;
    }
};

void print(LangIt range_begin, LangIt range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << it->name << endl;
    }
};

void third_example(auto ages) { print(ages.begin(), ages.end()); }

void first_example() {
    // на самом деле строки могут быть проитерированы символами
    string example = "C++";
    auto it = example.begin();
    // cout << *it;
    ++it;  // так можно прогуляться по итератору на шаг вперед
    // cout << *it;
};

int main() {
    vector<Lang> ages = {
        {"Python", 26}, {"C++", 34}, {"C", 45}, {"Java", 22}, {"C#", 17}};

    first_example();
    second_example(ages);
    third_example(ages);
}
