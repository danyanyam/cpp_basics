/**
 * Чтобы использовать свой тип в ключах словарей,
 * нужно определить оператор сравнения, потому
 * что словарь хранит ключи в отсортированном виде
 */

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

struct Date {
    int year = 1970;
    int month = 1;
    int day = 1;

    Date(){};
    Date(int nday, int nmonth, int nyear) {
        year = nyear;
        month = nmonth;
        day = nday;
    };

    auto get_rank() { return tie(year, month, day); }
};

bool operator<(Date& lhs, Date& rhs) {
    // в кортежах доступно упорядоченное сравнение
    return lhs.get_rank() < rhs.get_rank();
}

int main(int argc, char const* argv[]) {
    Date lhs(2021, 1, 3);
    Date rhs(2021, 1, 2);
    cout << (lhs < rhs);
}
