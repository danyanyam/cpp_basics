#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

tuple<string, int> check_existence(const vector<string>& v, string city) {
    if (count_if(v.begin(), v.end(), [city](auto i) {return i == city;})) {
        return make_tuple(city, 1);
    } else {
        return make_tuple("Not found", 0);
    }
}

int main(int argc, char const* argv[]) {
    int x = 0, y = 1, z = 2;

    // использует ссылки на переменные
    auto t = tie(x, y, z);

    // использует значения переменных
    auto t1 = make_tuple(0, 1, 2);

    // в новом стандарте c++ можно не перечислять типы элементов кортежа
    tuple t2 = tuple(0, 1, 2);

    // достали по первому значению из кортежей
    cout << (get<0>(t) == get<0>(t1) and get<0>(t) == get<0>(t2)) << endl << endl;

    // ============ возврат из функции нескольких значений ============
    int result_code;
    string result_msg;
    vector<string> cities = {"Moscow", "Volgograd"};
    tie(result_msg, result_code) = check_existence(cities, "moscow");
    cout << result_msg << endl;

    // или аналогично в новом стандарте плюсов:
    auto [msg, code] = check_existence(cities, "moscow");
    cout << msg;
}
