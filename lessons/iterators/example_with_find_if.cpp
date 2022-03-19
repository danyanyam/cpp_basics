#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Lang {
    string name;
    int age;
};

void second_example() {
    vector<Lang> ages = {
        {"Python", 26}, {"C++", 34}, {"C", 45}, {"Java", 22}, {"C#", 17}};

    // найдем языки, старше 20 лет
    auto result = find_if(begin(ages), end(ages),
                          [](const Lang& lang) { return lang.age > 20; });

    // на самом деле begin указывают на начало
    cout << begin(ages) -> age << endl;

    // если результат найден
    if (result != end(ages)) {
        // вернули указатель на объект, а не сам объект
        cout << (*result).age << endl;
        cout << result->age << endl;
    };
};

void first_example() {
    vector<string> lenghts = {"python", "C++", "C", "Java", "C#"};

    // найдем языки, начинающиеся с буквы С
    auto result = find_if(begin(lenghts), end(lenghts),
                          [](const string& lang) { return lang[0] == 'C'; });

    // ссылка на найденный элемент
    cout << *result << endl;  // c++
};

int main() {
    first_example();
    second_example();
}
