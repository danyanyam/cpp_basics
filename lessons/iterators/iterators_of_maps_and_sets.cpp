#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

void first_example(set<string> data) {
    // как получить индекс элемента вектора
    auto result = data.find("C++");
    cout << distance(data.begin(), result) << endl;
};

int main() {
    set<string> ages = {"Python", "C++", "C", "Java", "C#"};
    first_example(ages);
}
